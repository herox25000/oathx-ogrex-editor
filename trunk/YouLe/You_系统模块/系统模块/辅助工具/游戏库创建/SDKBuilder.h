#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "Resource.h"

//////////////////////////////////////////////////////////////////////////

//Ӧ�ó�����
class CSDKBuilderApp : public CWinApp
{
	//��������
//public:
//	CSkinRecordFile							m_SkinRecordFile;				//��������

	//��������
public:
	//���캯��
	CSDKBuilderApp();

	//���غ���
public:
	//��ʼ��
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

//Ӧ�ó������
extern CSDKBuilderApp theApp;

//////////////////////////////////////////////////////////////////////////
