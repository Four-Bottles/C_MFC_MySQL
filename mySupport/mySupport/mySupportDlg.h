
// mySupportDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CmySupportDlg 对话框
class CmySupportDlg : public CDialogEx
{
// 构造
public:
	CmySupportDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYSUPPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
