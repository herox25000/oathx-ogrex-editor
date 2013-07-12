#ifndef PLATFORM_FRAME_HEAD_FILE
#define PLATFORM_FRAME_HEAD_FILE

#pragma once

//系统文件
#include "Stdafx.h"
#include "Resource.h"

//任务文件
#include "MissionList.h"
#include "MissionLogon.h"

//控件文件
#include "DlgWhisper.h"
#include "DlgCollocate.h"
#include "PlazaViewItem.h"
#include "ServerViewItem.h"
#include "ServerToolBar.h"

//窗口控件
#include "WndGameTypeCtrl.h"
#include "WndUserInfoCtrl.h"
#include "MiddleFrameControl.h"
#include "PlatformPublicize.h"
#include "DlgLockMachine.h"
#include "DlgCustomFace.h"

//列表状态
enum enServerListControl
{
	ServerListControl_Hide,			//隐藏列表
	ServerListControl_Show,			//显示列表
	ServerListControl_Turn,			//翻转列表
};

//////////////////////////////////////////////////////////////////////////////////

//热键定义
#define IDI_HOT_KEY_BOSS			0x0100								//老板热键

//////////////////////////////////////////////////////////////////////////////////

//平台框架
class CPlatformFrame : public CFrameWnd, public IServerListDataSink, public ICustomFaceEvent
{
	//状态变量
protected:
	bool							m_bMaxShow;							//最大标志
	bool							m_bRectify;							//调整标志
	bool							m_bWhisperIcon;						//私聊图标
	bool							m_bShowLeftPanel;					//隐藏标志
	CRect                           m_rcPlazaView;                      //大厅视图 
	CRect							m_rcServerView;						//视图大小
	CRect                           m_rcGameType;                       //游戏类型
	CRect                           m_rcToolBar;                        //工具栏  
	CRect							m_rcNormalSize;						//正常位置
	CSize                           m_ScreenMetrics;                    //屏幕尺寸 

	//控制按钮
public:
	CSkinButton						m_btMin;							//最小按钮
	CSkinButton                     m_btMax;                            //最大按钮
	CSkinButton						m_btClose;							//关闭按钮
	CSkinButton						m_btNavigation[7];					//导航按钮

	//框架控件
protected:
	CWndGameTypeCtrl				m_WndGameTypeCtrl;					//类型子项
	CWndUserInfoCtrl				m_WndUserInfoCtrl;					//用户信息
	CMiddleFrameControl             m_MiddleFrameControl;               //中间框架

	//控件变量
protected:
	CToolTipCtrl					m_ToolTipCtrl;						//提示控件
	CSkinLayered					m_SkinLayered;						//分层窗口
	CSkinSplitter					m_SkinSplitter;						//拆分控件
	CServerListData					m_ServerListData;					//游戏数据
	CSystemTrayIcon					m_SystemTrayIcon;					//任务图标
	CPlatformPublicize              m_PlatFormNoticePublicize;          //浏览控件 

	//任务组件
protected:
	CMissionList					m_MissionList;						//列表任务
	CMissionLogon					m_MissionLogon;						//登录任务
	CMissionManager					m_MissionManager;					//任务管理

	//控件数组
public:
	CPlazaViewItem					m_PlazaViewItem;					//游戏广场
	CServerViewItem	*				m_pServerViewItem;					//当前房间
	CServerToolBar                  m_ServerToolBar;                    //房间工具 
	CDlgWhisperItemArray			m_DlgWhisperItemArray;				//私聊数组

	//资源变量
protected:
	CBitImage						m_ImageFrame;						//框架图片
	CEncirclePNG					m_FrameEncircle;					//框架资源
	CEncircleBMP					m_AfficheEncircle;					//框架资源
	CEncircleBMP					m_ItemFrameEncircle;				//框架资源

	//静态变量
protected:
	static CPlatformFrame *			m_pPlatformFrame;					//框架指针

	//函数定义
public:
	//构造函数
	CPlatformFrame();
	//析构函数
	virtual ~CPlatformFrame();

	//基础接口
public:
	//释放对象
	virtual VOID Release() { delete this; }
	//接口查询
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//头像接口
protected:
	//下载失败
	virtual VOID OnEventSystemFace(DWORD dwUserID, WORD wFaceID);
	//头像数据
	virtual VOID OnEventCustomFace(DWORD dwUserID, DWORD dwCustomID, tagCustomFaceInfo & CustomFaceInfo);

	//状态通知
public:
	//获取通知
	virtual VOID OnGameItemFinish();
	//获取通知
	virtual VOID OnGameKindFinish(WORD wKindID);
	//更新通知
	virtual VOID OnGameItemUpdateFinish();

	//更新通知
public:
	//插入通知
	virtual VOID OnGameItemInsert(CGameListItem * pGameListItem);
	//更新通知
	virtual VOID OnGameItemUpdate(CGameListItem * pGameListItem);
	//删除通知
	virtual VOID OnGameItemDelete(CGameListItem * pGameListItem);

	//重载函数
protected:
	//消息过虑
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//界面函数
private:
	//调整控件
	VOID RectifyControl(INT nWidth, INT nHeight);
	//调整资源
	VOID RectifyResource(INT nWidth, INT nHeight);
	//绘画界面
	VOID DrawControlView(CDC * pDC, INT nWidth, INT nHeight);
	//修改分辨率
	VOID ChangeScreenSetting(INT nScreencx,INT nScreency,bool bRecordResol);

	//房间管理
public:
	//激活房间
	bool ActiveServerViewItem();
	//删除房间
	bool DeleteServerViewItem();
	//进入房间
	bool EntranceServerItem(CGameServerItem * pGameServerItem);

	//私聊函数
public:
	//提取私聊
	bool ShowWhisperItem();
	//插入私聊
	bool InsertWhisperItem(CDlgWhisper * pDlgWhisper);
	//删除私聊
	bool RemoveWhisperItem(CDlgWhisper * pDlgWhisper);

	//功能函数
public:
	//显示面板
	VOID ShowPlazaLeftPanel(bool bShowPanel);
	//最大窗口
	virtual bool MaxSizeWindow();
	//还原窗口
	virtual bool RestoreWindow();

	//消息函数
protected:
	//关闭消息
	VOID OnClose();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//位置消息
	VOID OnSize(UINT nType, INT cx, INT cy);
	//创建消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//时间消息
	VOID OnTimer(UINT_PTR nIDEvent);
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);

	//自定消息
protected:
	//事件消息
	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);
	//银行更新
	LRESULT OnMessageInsureUpdate(WPARAM wParam, LPARAM lParam);

	//功能函数
public:
	//获取实例
	static CPlatformFrame * GetInstance() { return m_pPlatformFrame; }

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif