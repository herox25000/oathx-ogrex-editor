// Editor.h : Editor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

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
