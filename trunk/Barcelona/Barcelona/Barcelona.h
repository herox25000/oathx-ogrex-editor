#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
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
* \Desc    : Ӧ�ó������
*
* \bug     : 
*
*/
class CBarcelonaApp : public CWinAppEx
{
public:
	/** ���캯��
	 *
	 * \return 
	 */
	CBarcelonaApp();

	UINT				m_nAppLook;
	BOOL				m_bHiColorIcons;
	Barcelona::System*	m_pAppSystem;
public:
	/** ��ʼ��Ӧ�ó���(����Ogre root ����)
	 *
	 * \return 
	 */
	virtual BOOL		InitInstance();

	/** ������Դ
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
