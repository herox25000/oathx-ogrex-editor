// GameTableTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CGameTableToolApp:
// �йش����ʵ�֣������ GameTableTool.cpp
//

class CGameTableToolApp : public CWinApp
{
public:
	CGameTableToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGameTableToolApp theApp;
