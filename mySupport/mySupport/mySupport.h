
// mySupport.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmySupportApp: 
// �йش����ʵ�֣������ mySupport.cpp
//

class CmySupportApp : public CWinApp
{
public:
	CmySupportApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmySupportApp theApp;