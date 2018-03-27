
// mySupportDlg.cpp : 实现文件
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
	//计算char *数组大小，以字节为单位，一个汉字占两个字节  
	int charLen = strlen(szBuf);
	//计算多字节字符的大小，按字符计算。  
	int len = MultiByteToWideChar(CP_ACP, 0, szBuf, charLen, NULL, 0);
	//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小  
	TCHAR *buf = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, szBuf, charLen, buf, len);
	buf[len] = '\0';
	//添加字符串结尾，注意不是len+1  
	//将TCHAR数组转换为CString  
	CString pWideChar;  pWideChar.Append(buf);    //把字符串加到后尾  
	//删除缓冲区  
	delete[]buf;
	return pWideChar;
}

char * CSt2char(CString str)
{
	//注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的  
	int n = str.GetLength();
	//获取宽字节字符的大小，大小是按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	//为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小  
	char * buff = new char[len + 1]; //以字节为单位  
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength() + 1, buff, len + 1, NULL, NULL);
	buff[len + 1] = '\0';     //多字节字符以'\0'结束  
	return buff;
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CmySupportDlg 对话框



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


// CmySupportDlg 消息处理程序

BOOL CmySupportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	mysql_init(&m_mysql);        // 初始化MYSQL对象
	mysql_options(&m_mysql, MYSQL_SET_CHARSET_NAME, "gb2312");   // 设置客户端支持中文字符集
	if (!mysql_real_connect(&m_mysql, "localhost", "root", "ydlhsbm1997", "supply", 3306, NULL, 0)) // 连接MYSQL后台数据库
	{
		MessageBoxW(_T("数据库连接失败！"));
		return FALSE;
	}
	else
		MessageBoxW(_T("数据库连接成功！"));

	// list 的初始化
	m_list.InsertColumn(0, _T("零件号"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(1, _T("零件名"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(2, _T("颜色"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(3, _T("重量"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(4, _T("项目号"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(5, _T("项目名"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(6, _T("项目城市"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(7, _T("供应商号"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(8, _T("供应商名"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(9, _T("状态"), LVCFMT_CENTER, 70);
	m_list.InsertColumn(10, _T("供应商城市"), LVCFMT_CENTER, 100);
	m_list.InsertColumn(11, _T("交易量"), LVCFMT_CENTER, 70);

	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//选择节点的时 
	//候选中整行 

	ShowData();//显示表格数据

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmySupportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmySupportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmySupportDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码

	mysql_close(&m_mysql);   // 关闭链接，释放资源
	CDialogEx::OnCancel();
}


void CmySupportDlg::ShowData()
{
	m_list.DeleteAllItems();//清空原有数据   
	char  sql[2000];
	sprintf_s(sql, "select * from fullSupplier");//设计sql语言   
	if (mysql_real_query(&m_mysql, sql, (unsigned long)strlen(sql)))//执行sql语言   
	{
		MessageBoxW(_T("读取表格失败"));
		return;
	}
	MYSQL_RES *result;
	MYSQL_ROW row;
	if (!(result = mysql_use_result(&m_mysql)))//获取数据   
	{
		MessageBoxW(_T("读取数据集失败"));
		return;
	}
	int i = 0;
	while (row = mysql_fetch_row(result))
	{
		//第一步是取数据，第二步是判断是否为空    
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
	mysql_free_result(result);//释放资源
}


void CmySupportDlg::OnLvnItemchangedListShow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}
