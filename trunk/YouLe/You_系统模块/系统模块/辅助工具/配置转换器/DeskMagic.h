// DeskMagic.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CDeskMagicApp:
// �йش����ʵ�֣������ DeskMagic.cpp
//

class CDeskMagicApp : public CWinApp
{
public:
	CDeskMagicApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDeskMagicApp theApp;
