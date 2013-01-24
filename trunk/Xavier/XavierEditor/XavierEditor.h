#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"
#include "EditorDebugMessage.h"

namespace Ogre
{
	class EditorSystem;
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
	Ogre::EditorSystem*		m_pAppSystem;
	EditorDebugMessage*		m_pDebugLog;
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
