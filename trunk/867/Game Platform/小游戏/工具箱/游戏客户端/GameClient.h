#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "Resource.h"
#include "GameClientDlg.h"
#include "SkinControls.h"
#include "SkinResourceModule.h"


//Ӧ�ó�����
class CGameClientApp : public CWinApp
{
public:
	CGameClientApp();
	virtual ~CGameClientApp();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CGameClientApp theApp;

