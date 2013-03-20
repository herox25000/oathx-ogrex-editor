#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "Resource.h"
#include "GameClientDlg.h"
#include "SkinControls.h"
#include "SkinResourceModule.h"


//应用程序类
class CGameClientApp : public CWinApp
{
public:
	CGameClientApp();
	virtual ~CGameClientApp();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	CPlatformResourceHelper			m_PlatformResourceModule;			//资源组件
	tagChatExpViewImage				m_ChatExpViewImage;					//表情资源
	tagGameFrameImage				m_GameFrameImage;					//框架资源
	tagPropertyViewImage			m_PropertyViewImage;				//道具资源
	tagVideoFrameImage				m_VideoFrameImage;					//视频资源
	tagPropertyMenuImage			m_PropertyMenuImage;				//菜单资源
	tagGiftFlashImage				m_GiftFlashImage;					//动画资源
};

extern CGameClientApp theApp;

