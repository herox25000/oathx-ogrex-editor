#ifndef WND_USER_INFO_CTRL_HEAD_FILE
#define WND_USER_INFO_CTRL_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//用户信息
class CWndUserInfoCtrl : public CWnd
{
	//控件变量
public:
	CSkinButton						m_btUserInfo1;						//用户按钮
	CSkinButton						m_btUserInfo2;						//用户按钮
	CSkinButton						m_btUserInfo3;						//用户按钮

	//控件变量
public:
	CDlgInsurePlaza *               m_pDlgInsurePlaza;                 //大厅银行

	//函数定义
public:
	//构造函数
	CWndUserInfoCtrl();
	//析构函数
	virtual ~CWndUserInfoCtrl();

	//重载函数
protected:
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//界面函数
private:
	//调整控件
	VOID RectifyControl(INT nWidth, INT nHeight);
	//转换字符
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, UINT uDecimalCount, LPTSTR pszBuffer, WORD wBufferSize);

	//消息函数
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//创建消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	//自定消息
protected:
	//事件消息
	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif