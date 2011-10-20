// Editor.h : Editor 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "AppMain.h"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class CEditorApp : public CWinAppEx
{
public:
	CEditorApp();

public:
	UINT				m_nAppLook;
	BOOL				m_bHiColorIcons;
	Ogre::AppMain*		m_pAppMain;
public:
	virtual BOOL		InitInstance();
	virtual int			ExitInstance();
	virtual void		PreLoadState();
	virtual void		LoadCustomState();
	virtual void		SaveCustomState();
	
	virtual void		ShowSplash();
	afx_msg void		OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
};

extern CEditorApp theApp;
