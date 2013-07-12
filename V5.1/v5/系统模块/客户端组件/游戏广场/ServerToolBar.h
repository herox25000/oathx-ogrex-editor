#ifndef SERVER_TOOL_BAR_HEAD_FILE
#define SERVER_TOOL_BAR_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//游戏广场
class CServerToolBar : public CDialog, public IUnknownEx
{
	//标识变量
protected:
	bool                            m_bCreateFlag;                      //创建标识 

	//按钮变量
protected:
	CSkinButton						m_btQuitServer;						//离开房间
	CSkinButton						m_btTableButton1;					//桌子按钮
	CSkinButton						m_btTableButton2;					//桌子按钮
	CSkinButton						m_btTableButton3;					//桌子按钮
	CSkinButton						m_btTableButton4;					//桌子按钮
	CSkinButton						m_btTableButton5;					//桌子按钮

	//函数定义
public:
	//构造函数
	CServerToolBar();
	//析构函数
	virtual ~CServerToolBar();

	//基础接口
public:
	//释放对象
	virtual VOID Release() { delete this; }
	//接口查询
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//重载函数
protected:
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK() { return; };
	//取消函数
	virtual VOID OnCancel() { return; };	
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//内部函数
protected:
	//调整控件
	VOID RectifyControl(INT nWidth, INT nHeight);

	//自定消息
protected:
	//事件消息
	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);

	//消息函数
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);	

	DECLARE_MESSAGE_MAP()	
};

//////////////////////////////////////////////////////////////////////////////////

#endif