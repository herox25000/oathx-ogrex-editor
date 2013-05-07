#ifndef PLAZA_USER_INFO_VIEW_HEAD_FILE
#define PLAZA_USER_INFO_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////

//编辑控件
class CEditUnderWrite : public CSkinEditEx, public ITCPSocketSink
{
	//友元定义
	friend class CUserInfoView;
	//变量定义
protected:
	bool							m_bNeedSend;						//请求标志
	TCHAR							m_szUnderWrite[UNDER_WRITE_LEN];	//个性签名

	//变量定义
protected:
	CWnd *							m_pParentWnd;						//窗口对象
	CTCPSocketHelper				m_SocketHelper;					//网络连接

	//基础接口
public:
	//释放对象
	virtual void __cdecl Release() { delete this; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//重载函数
public:
	//连接事件
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);


	//函数定义
public:
	//构造函数
	CEditUnderWrite();
	//析构函数
	virtual ~CEditUnderWrite();

	//重载函数
protected:
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//功能函数
public:
	//修改判断
	bool IsModifyStatus();
	//设置窗口
	VOID SetParentWindow(CWnd * pParentWnd);

	//内部函数
protected:
	//关闭控件
	VOID CloseUnderWrite();
	//更新签名
	VOID UpdateUnderWrite();

	//消息定义
protected:
	//消耗消息
	VOID OnDestroy();
	//失去焦点
	VOID OnKillFocus(CWnd * pNewWnd);

	DECLARE_MESSAGE_MAP()
};



//用户信息
class CUserInfoView : public CDialog
{
	//状态变量
protected:
	bool							m_bShowInfo;						//显示标志
	bool							m_bCreateFlag;						//创建标志
	UINT							m_nTitleHeight;						//标题高度

	//资源变量
protected:
	CSkinImage						m_ImageTitleL;						//位图对象
	CSkinImage						m_ImageTitleM;						//位图对象
	CSkinImage						m_ImageTitleR;						//位图对象

	//用户签名
public:
	bool							m_bHoverUnderWrite;					//盘旋标志
	CRect							m_rcUnderWrite;						//签名区域
	CEditUnderWrite					m_EditUnderWrite;					//编辑控件

	//函数定义
public:
	//构造函数
	CUserInfoView();
	//析构函数
	virtual ~CUserInfoView();

	//重载函数
protected:
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//初始化函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK() { return; };
	//取消函数
	virtual VOID OnCancel() { return; };

	//功能函数
public:
	//标题高度
	UINT GetTitleHeight();
	//更新信息
	VOID UpdateUserInfo();
	//显示信息
	VOID ShowUserInfo(bool bShowInfo);
	//更新资源
	bool UpdateSkinResource();

	//界面函数
private:
	//调整控件
	VOID RectifyControl(INT nWidth, INT nHeight);

	//消息函数
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint MousePoint);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint MousePoint);
	//光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	//自定消息
protected:
	//鼠标离开
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif