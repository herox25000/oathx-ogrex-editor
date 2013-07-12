#ifndef MIDDLE_FRAME_CONTROL_HEAD_FILE
#define MIDDLE_FRAME_CONTROL_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//用户信息
class CMiddleFrameControl
{
	//控制变量
protected:
	bool						m_bAfficheTitle;			    //标题标识

	//区域变量
protected:
	CRect                       m_rcControl;					//控件区域

	//函数定义
public:
	//构造函数
	CMiddleFrameControl();
	//析构函数
	virtual ~CMiddleFrameControl();

	//消息函数
public:
	//设置标识
	VOID SetAfficheTitleFlag(bool bAfficheTitle) { m_bAfficheTitle=bAfficheTitle; };
	//获取区域
	VOID GetControlRect(CRect & rcControl) { rcControl=m_rcControl; }
	//设置区域
	VOID SetControlRect(CRect rcControl) { m_rcControl=rcControl; }
	//设置区域
	VOID SetControlRect(INT nLeftPos,INT nTopPos,INT nRightPos,INT nBottomPos);
	//绘画背景
	BOOL OnDrawFrameControl(CDC * pDC);
};

//////////////////////////////////////////////////////////////////////////////////

#endif