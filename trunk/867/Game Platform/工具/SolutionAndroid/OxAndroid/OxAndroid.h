// OxAndroid.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// COxAndroidApp:
// �йش����ʵ�֣������ OxAndroid.cpp
//

class COxAndroidApp : public CWinApp
{
public:
	COxAndroidApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COxAndroidApp theApp;
