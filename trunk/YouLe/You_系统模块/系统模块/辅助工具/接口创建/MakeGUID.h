#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "Resource.h"		// ������

//////////////////////////////////////////////////////////////////////////

//Ӧ�ó�����
class CMakeGUIDApp : public CWinApp
{
	//��������
public:
	//���캯��
	CMakeGUIDApp();

	//���غ���
public:
	//��ʼ������
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

extern CMakeGUIDApp theApp;

//////////////////////////////////////////////////////////////////////////
