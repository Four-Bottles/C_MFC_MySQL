
// mySupportDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CmySupportDlg �Ի���
class CmySupportDlg : public CDialogEx
{
// ����
public:
	CmySupportDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYSUPPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MYSQL m_mysql;
	afx_msg void OnBnClickedCancel();
	CListCtrl m_list;
	void ShowData();
	afx_msg void OnLvnItemchangedListShow(NMHDR *pNMHDR, LRESULT *pResult);
};
