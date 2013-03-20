#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "Resource.h"
#include "GameClientDlg.h"
#include "SkinControls.h"
#include "SkinResourceModule.h"


//Ӧ�ó�����
class CGameClientApp : public CWinApp
{
public:
	CGameClientApp();
	virtual ~CGameClientApp();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	CPlatformResourceHelper			m_PlatformResourceModule;			//��Դ���
	tagChatExpViewImage				m_ChatExpViewImage;					//������Դ
	tagGameFrameImage				m_GameFrameImage;					//�����Դ
	tagPropertyViewImage			m_PropertyViewImage;				//������Դ
	tagVideoFrameImage				m_VideoFrameImage;					//��Ƶ��Դ
	tagPropertyMenuImage			m_PropertyMenuImage;				//�˵���Դ
	tagGiftFlashImage				m_GiftFlashImage;					//������Դ
};

extern CGameClientApp theApp;

