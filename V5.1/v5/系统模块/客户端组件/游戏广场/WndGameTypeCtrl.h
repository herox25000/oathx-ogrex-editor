#ifndef WND_GAME_TYPE_CTRL_HEAD_FILE
#define WND_GAME_TYPE_CTRL_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerListData.h"

//////////////////////////////////////////////////////////////////////////////////

//游戏类型
class CWndGameTypeCtrl : public CWnd
{
	//点击信息
protected:
	bool							m_bHovering;						//盘旋标志
	WORD							m_wItemDown;						//按下子项
	WORD							m_wItemHover;						//盘旋子项
	WORD							m_wItemActive;						//激活子项

	//配置信息
protected:
	CSize							m_SizeButton;						//按钮大小
	CGameTypeItemArray				m_GameTypeItemArray;				//类型数组

	//函数定义
public:
	//构造函数
	CWndGameTypeCtrl();
	//析构函数
	virtual ~CWndGameTypeCtrl();

	//功能函数
public:
	//获取大小
	VOID GetControlSize(CSize & ResultSize);
	//插入类型
	VOID InsertGameType(CGameTypeItem * pGameTypeItem);

	//内部函数
private:
	//对象索引
	WORD GetTypeItemIndex(WORD wTypeID);
	//对象索引
	WORD GetTypeItemIndex(CPoint MousePoint);

	//消息函数
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//鼠标移动
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标离开
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif