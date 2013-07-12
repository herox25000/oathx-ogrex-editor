#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "PlatformPublicize.h"

//////////////////////////////////////////////////////////////////////////////////

//选择控制
class CWndLogonButton : public CWnd
{
	//活动信息
protected:
	bool							m_bHovering;						//盘旋标志
	WORD							m_wItemDown;						//按下子项
	WORD							m_wItemHover;						//盘旋子项
	WORD							m_wItemActive;						//激活子项

	//子项信息
protected:
	CSize							m_SizeButton;						//按钮大小

	//函数定义
public:
	//构造函数
	CWndLogonButton();
	//析构函数
	virtual ~CWndLogonButton();

	//内部函数
private:
	//索引切换
	WORD SwitchToButtonIndex(CPoint MousePoint);

	//消息函数
protected:
	//重画消息
	VOID OnPaint();
	//创建消息
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标移动
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标离开
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//单选控件
class  CControlCheckButton
{
	//状态变量
protected:
	BYTE                           m_cbChecked;                        //记住密码
	CWnd *                         m_pParentSink;                      //父类指针

	//位置变量
protected:
	CPoint                         m_ptControlBenchmark;               //基准位置

	//资源变量
protected:
	CBitImage                      m_ImageBtnBack;                     //背景资源

	//函数定义
public:
	//构造函数
	CControlCheckButton();
	//析构函数
	virtual ~CControlCheckButton();

	//辅助函数
public:
	//控件区域
	CRect GetControlRect();

	//辅助函数
public:
	//基准位置
	inline VOID  SetControlBenchmark(INT nXPos,INT nYPos) { m_ptControlBenchmark.SetPoint(nXPos,nYPos); };
	//获取状态
	inline BYTE  GetButtonChecked() { return m_cbChecked; };
	//设置状态
	inline VOID  SetButtonChecked(BYTE cbChecked);
	//设置父类
	inline VOID  SetParentWndSink(CWnd * pParentSink) { m_pParentSink=pParentSink; };

	//事件函数
public:
	//绘制控件
	VOID  OnDrawControl(CDC * pDC);
	//点击事件
	VOID  OnClickControl(CPoint Point);

};

//////////////////////////////////////////////////////////////////////////////////

//登录窗口
class CDlgLogon : public CDialog
{
	//配置变量
public:
	BYTE							m_cbRemPassword;					//记住密码

	//登录信息
public:
	TCHAR							m_szAccounts[LEN_ACCOUNTS];			//游戏帐号
	TCHAR							m_szPassword[LEN_PASSWORD];			//用户密码
	TCHAR							m_szLogonServer[LEN_SERVER];		//登录地址

	//控件变量
protected:
	CSkinButton						m_btQuit;							//退出按钮
	CSkinButton						m_btEnter;							//登录按钮

	//特殊控件
protected:
	CSkinEditEx						m_edAccounts;						//登录帐号
	CSkinComboBox					m_ServerControl;					//登录地址
	CPasswordControl				m_PasswordControl;					//用户密码
	CControlCheckButton             m_RemPwdControl;                    //记住密码

	//界面控件
protected:
	CBrush							m_brBrush;							//背景画刷
	CSkinLayered					m_SkinLayered;						//分层窗口
	CWndLogonButton					m_WndLogonButton;					//按钮控件
	CPlatformPublicize				m_PlatformPublicize;				//浏览控件

	//函数定义
public:
	//构造函数
	CDlgLogon();
	//析构函数
	virtual ~CDlgLogon();

	//重载函数
protected:
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();
	//取消消息
	virtual VOID OnCancel();

	//功能函数
public:
	//构造数据
	WORD ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize);

	//辅助函数
private:
	//获取信息
	bool GetInformation();
	//加载账号
	VOID LoadAccountsInfo();
	//地址信息
	VOID LoadLogonServerInfo();

	//按钮消息
protected:
	//注册帐号
	VOID OnBnClickedRegister();
	//编辑改变
	VOID OnCbnEditchangeAccounts();

	//系统消息
protected:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//控件颜色
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	//消息映射
public:
	afx_msg void OnEnChangeAccounts();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////////////

#endif