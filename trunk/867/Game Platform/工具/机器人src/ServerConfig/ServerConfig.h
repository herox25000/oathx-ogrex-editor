// ServerConfig.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CServerConfigApp:
// �йش����ʵ�֣������ ServerConfig.cpp
//

class CServerConfigApp : public CWinApp
{
public:
	CServerConfigApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServerConfigApp theApp;
