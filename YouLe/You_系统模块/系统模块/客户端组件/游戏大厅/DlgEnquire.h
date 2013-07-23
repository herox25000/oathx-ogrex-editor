#ifndef DLG_ENQUIRE_HEAD_FILE
#define DLG_ENQUIRE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////////////
#define  WM_BT_CLOSE				100
#define  WM_BT_CLOSE_PLAZA			101
#define  WM_BT_SWITCH_ACCOUNTS		102
#define  WM_BT_QUITE				103

//关闭窗口
class CDlgEnquire : public CDialog
{
	//控件变量
protected:
	CGdipButton						m_btCancel;							//取消操作
	CGdipButton						m_btClosePlaza;						//关闭大厅
	CGdipButton						m_btQuite;						//关闭房间
	CGdipButton						m_btSwitchAccounts;					//切换帐号

public:
	CPngImage						m_ImageBack;
	//函数定义
public:
	//构造函数
	CDlgEnquire();
	//析构函数
	virtual ~CDlgEnquire();

	//重载函数
protected:
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//配置函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();

	//按钮消息
protected:
	//关闭大厅
	VOID OnBnClickedClosePlaza();
	//关闭房间
	VOID OnBnClickedCloseServer();
	//切换帐号
	VOID OnBnClickedSwitchAccounts();

	//消息函数
public:
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif