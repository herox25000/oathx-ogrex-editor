#pragma once

#include "Stdafx.h"

//��Ϸ��ͼ
class CGameClientView : public CGameFrameView
{
	//��������
public:
	//���캯��
	CGameClientView();
	//��������
	virtual ~CGameClientView();

	//��Ϸ�滭
	virtual bool		DrawAll();
protected:
	video::ITexture*	m_pImage;
	//��Ϣӳ��
protected:
	//ʱ����Ϣ
	afx_msg void		OnTimer(UINT nIDEvent);
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
