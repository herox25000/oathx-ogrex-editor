// SmallNine.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CSmallNineApp:
// �йش����ʵ�֣������ SmallNine.cpp
//

class CSmallNineApp : public CWinApp
{
public:
	CSmallNineApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSmallNineApp theApp;
