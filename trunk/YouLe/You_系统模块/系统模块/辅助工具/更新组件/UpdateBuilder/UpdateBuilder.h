// UpgradeBuilder.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CUpdateBuilderApp:
// See UpgradeBuilder.cpp for the implementation of this class
//

class CUpdateBuilderApp : public CWinApp
{
public:
	CUpdateBuilderApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CUpdateBuilderApp theApp;