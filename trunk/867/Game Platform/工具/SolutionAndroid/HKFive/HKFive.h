// HKFiveAndroid.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// COxApp:
// �йش����ʵ�֣������ HKFiveAndroid.cpp
//

class CHKFiveApp : public CWinApp
{
public:
	CHKFiveApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHKFiveApp theApp;
