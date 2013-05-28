#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h" 

namespace Ogre
{
	class SandBox;
}

/**
* \ingroup : OgreSandBox
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-05-28
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class COgreSandBoxApp : public CWinAppEx
{
public:
	/**
	 *
	 * \return 
	 */
	COgreSandBoxApp();

	UINT					m_nAppLook;
	BOOL					m_bHiColorIcons;
	Ogre::SandBox*			m_pSandBox;
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

extern COgreSandBoxApp theApp;
