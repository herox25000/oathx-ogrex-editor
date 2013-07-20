#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"

class CGamePlazaApp : public CWinApp
{
public:
	CGamePlazaApp();

public:
	virtual BOOL	InitInstance();
	virtual int		ExitInstance();

	DECLARE_MESSAGE_MAP()
	
protected:
	ULONG_PTR		m_gdiplusToken;
};

extern CGamePlazaApp theApp;
