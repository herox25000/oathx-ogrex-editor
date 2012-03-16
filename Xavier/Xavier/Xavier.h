#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "OgreEditor.h"
#include "XavierLog.h"

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-03-08
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CXavierApp : public CWinAppEx
{
public:
	/**
	 *
	 * \return 
	 */
	CXavierApp();

	UINT					m_nAppLook;
	BOOL					m_bHiColorIcons;
	Ogre::AppEdit*			m_pAppEdit;
	XavierLog*				m_pXavierLog;
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

extern CXavierApp theApp;
