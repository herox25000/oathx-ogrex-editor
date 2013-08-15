#pragma once

#include "Stdafx.h"

//游戏视图
class CGameClientView : public CGameFrameView
{
	//函数定义
public:
	//构造函数
	CGameClientView();
	//析构函数
	virtual ~CGameClientView();

	//游戏绘画
	virtual bool		DrawAll();
protected:
	video::ITexture*	m_pImage;
	//消息映射
protected:
	//时间消息
	afx_msg void		OnTimer(UINT nIDEvent);
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
