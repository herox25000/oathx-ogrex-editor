#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "GlobalUnits.h"

//////////////////////////////////////////////////////////////////////////

//Ӧ�ó������
class CGamePlazaApp : public CWinApp
{
//	//��������
//public:
//	CSkinRecordFile							m_SkinRecordFile;				//��������
	ULONG_PTR m_gdiplusToken;
	//��������
public:
	//���캯��
	CGamePlazaApp();

	//���غ���
public:
	//��ʼ������
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//Ӧ�ó������˵��
extern CGamePlazaApp theApp;

//////////////////////////////////////////////////////////////////////////
