#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"

namespace Barcelona
{
	class System;
}

/**
* \ingroup : Barcelona
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-06-22
*
* \Author  : lp
*
* \Desc    : 应用程序入口
*
* \bug     : 
*
*/
class CBarcelonaApp : public CWinAppEx
{
public:
	/** 构造函数
	 *
	 * \return 
	 */
	CBarcelonaApp();

	UINT				m_nAppLook;
	BOOL				m_bHiColorIcons;
	Barcelona::System*	m_pAppSystem;
public:
	/** 初始化应用程序(创建Ogre root 对象)
	 *
	 * \return 
	 */
	virtual BOOL		InitInstance();

	/** 销毁资源
	 *
	 * \return 
	 */
	virtual int			ExitInstance();

	/**
	 *
	 */
	virtual void		PreLoadState();

	/**
	 *
	 */
	virtual void		LoadCustomState();

	/**
	 *
	 */
	virtual void		SaveCustomState();


	/**
	 *
	 */
	virtual void		ShowSplashDialog();

	/**
	 *
	 */
	afx_msg void		OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
};

extern CBarcelonaApp theApp;
