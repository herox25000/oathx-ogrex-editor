#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "Resource.h"
#include "GameClientDlg.h"
#include "SkinControls.h"
#include "SkinResourceModule.h"


//应用程序类
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

