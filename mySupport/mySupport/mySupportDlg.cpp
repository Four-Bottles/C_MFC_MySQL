
// mySupportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mySupport.h"
#include "mySupportDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString char2CSt(char * szBuf)
{
	//����char *�����С�����ֽ�Ϊ��λ��һ������ռ�����ֽ�  
	int charLen = strlen(szBuf);
	//������ֽ��ַ��Ĵ�С�����ַ����㡣  
	int len = MultiByteToWideChar(CP_ACP, 0, szBuf, charLen, NULL, 0);
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С  
	TCHAR *buf = new TCHAR[len + 1];
	//���ֽڱ���ת���ɿ��ֽڱ���  
	MultiByteToWideChar(CP_ACP, 0, szBuf, charLen, buf, len);
	buf[len] = '\0';
	//����ַ�����β��ע�ⲻ��len+1  
	//��TCHAR����ת��ΪCString  
	CString pWideChar;  pWideChar.Append(buf);    //���ַ����ӵ���β  
	//ɾ��������  
	delete[]buf;
	return pWideChar;
}

char * CSt2char(CString str)
{
	//ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ����  
	int n = str.GetLength();
	//��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����  
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С  
	char * buff = new char[len + 1]; //���ֽ�Ϊ��λ  
	//���ֽڱ���ת���ɶ��ֽڱ���  
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength() + 1, buff, len + 1, NULL, NULL);
	buff[len + 1] = '\0';     //���ֽ��ַ���'\0'����  
	return buff;
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmySupportDlg �Ի���



CmySupportDlg::CmySupportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmySupportDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmySupportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHOW, m_list);
}

BEGIN_MESSAGE_MAP(CmySupportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CmySupportDlg::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SHOW, &CmySupportDlg::OnLvnItemchangedListShow)
END_MESSAGE_MAP()


// CmySupportDlg ��Ϣ�������

BOOL CmySupportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	mysql_init(&m_mysql);        // ��ʼ��MYSQL����
	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gb2312");   // ���ÿͻ���֧�������ַ���
	if (!mysql_real_connect(&m_mysql, "localhost", "root", "ydlhsbm1997", "supply", 3306, NULL, 0)) // ����MYSQL��̨���ݿ�
	{
		MessageBoxW(_T("���ݿ�����ʧ�ܣ�"));
		return FALSE;
	}
	else
		MessageBoxW(_T("���ݿ����ӳɹ���"));

	// list �ĳ�ʼ��
	m_list.InsertColumn(0, _T("�����"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(1, _T("�����"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(2, _T("��ɫ"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(3, _T("����"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(4, _T("��Ŀ��"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(5, _T("��Ŀ��"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(6, _T("��Ŀ����"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(7, _T("��Ӧ�̺�"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(8, _T("��Ӧ����"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(9, _T("״̬"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(10, _T("��Ӧ�̳���"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(11, _T("������"), LVCFMT_CENTER, 70);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//ѡ��ڵ��ʱ 
	//��ѡ������ 

	ShowData();//��ʾ�������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmySupportDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmySupportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmySupportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmySupportDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	mysql_close(&m_mysql);   // �ر����ӣ��ͷ���Դ
	CDialogEx::OnCancel();
}


void CmySupportDlg::ShowData()
{
	m_list.DeleteAllItems();//���ԭ������   
	char  sql[2000];
	sprintf_s(sql, "select * from fullSupplier");//���sql����   
	if (mysql_real_query(&m_mysql, sql, (unsigned long)strlen(sql)))//ִ��sql����   
	{
		MessageBoxW(_T("��ȡ���ʧ��"));
		return;
	}
	MYSQL_RES *result;
	MYSQL_ROW row;
	if (!(result = mysql_use_result(&m_mysql)))//��ȡ����   
	{
		MessageBoxW(_T("��ȡ���ݼ�ʧ��"));
		return;
	}
	int i = 0;
	while (row = mysql_fetch_row(result))
	{
		//��һ����ȡ���ݣ��ڶ������ж��Ƿ�Ϊ��    
		m_list.InsertItem(i, char2CSt(row[0]));
		m_list.SetItemText(i, 1, char2CSt(row[1]));
		m_list.SetItemText(i, 2, char2CSt(row[2]));
		m_list.SetItemText(i, 3, char2CSt(row[3]));
		m_list.SetItemText(i, 4, char2CSt(row[4]));
		m_list.SetItemText(i, 5, char2CSt(row[5]));
		m_list.SetItemText(i, 6, char2CSt(row[6]));
		m_list.SetItemText(i, 7, char2CSt(row[7]));
		m_list.SetItemText(i, 8, char2CSt(row[8]));
		m_list.SetItemText(i, 9, char2CSt(row[9]));
		m_list.SetItemText(i, 10, char2CSt(row[10]));
		m_list.SetItemText(i, 11, char2CSt(row[11]));
		i++;
	}
	mysql_free_result(result);//�ͷ���Դ
}


void CmySupportDlg::OnLvnItemchangedListShow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
