#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
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
	
};

extern CGamePlazaApp theApp;
