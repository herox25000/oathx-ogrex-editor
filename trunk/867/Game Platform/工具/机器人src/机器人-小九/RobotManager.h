// RobotManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CRobotManagerApp:
// �йش����ʵ�֣������ RobotManager.cpp
//

class CRobotManagerApp : public CWinApp
{
public:
	CRobotManagerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRobotManagerApp theApp;
