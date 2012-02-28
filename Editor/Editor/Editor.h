#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"
#include "Ogre.h"

class CEditorApp : public CWinAppEx
{
public:
	CEditorApp();

	UINT				m_nAppLook;
	BOOL				m_bHiColorIcons;
	Ogre::Root*			m_pRoot;

public:
	virtual BOOL		InitInstance();
	virtual int			ExitInstance();

	virtual	void		InitOneTime();

	virtual void		PreLoadState();
	virtual void		LoadCustomState();
	virtual void		SaveCustomState();

	virtual void		ShowSplash();
	afx_msg void		OnAppAbout();

	DECLARE_MESSAGE_MAP()	
};

extern CEditorApp theApp;
