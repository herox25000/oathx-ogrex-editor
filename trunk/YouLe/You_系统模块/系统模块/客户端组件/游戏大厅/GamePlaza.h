// GamePlaza.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CGamePlazaApp:
// �йش����ʵ�֣������ GamePlaza.cpp
//

class CGamePlazaApp : public CWinApp
{
public:
	CGamePlazaApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGamePlazaApp theApp;
