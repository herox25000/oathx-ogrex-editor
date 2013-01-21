#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"

namespace Ogre
{
	class System;
}

class CXavierEditorApp : public CWinAppEx
{
public:
	/**
	 *
	 * \return 
	 */
	CXavierEditorApp();

	UINT					m_nAppLook;
	BOOL					m_bHiColorIcons;
	Ogre::System*			m_pAppSystem;
public:
	/**
	 *
	 * \return 
	 */
	virtual BOOL			InitInstance();

	/**
	 *
	 * \return 
	 */
	virtual int				ExitInstance();

	/**
	 *
	 */
	virtual void			PreLoadState();

	/**
	 *
	 */
	virtual void			LoadCustomState();

	/**
	 *
	 */
	virtual void			SaveCustomState();

	/**
	 *
	 */
	virtual void			ShowSplashDialog();

	/**
	 *
	 */
	afx_msg void			OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CXavierEditorApp theApp;
