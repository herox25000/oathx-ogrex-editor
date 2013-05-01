#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////

//服务器名称和登陆地址
struct SERVER_ITEM
{
	char szName[256];
	char szIPAddress[256];
};


//登录模式
enum enLogonMode
{
	LogonMode_Accounts,			//帐号登录
	LogonMode_UserID,			//I D 登录
};

//////////////////////////////////////////////////////////////////////////

//用户注册
class CDlgRegister : public CDialog
{
	friend class CDlgLogon;

	//登录信息
public:
	WORD								m_wFaceID;						//头像标识
	BYTE								m_cbGender;						//用户性别
	TCHAR								m_szSpreader[NAME_LEN];			//电子邮箱
	TCHAR								m_szAccounts[NAME_LEN];			//游戏帐号
	TCHAR								m_szPassword[PASS_LEN];			//游戏密码
	TCHAR								m_szBankPassword[PASS_LEN];		//银行密码
	TCHAR								m_szSFZ[PASS_LEN];				//身份证号码
	TCHAR								m_szPhone[PASS_LEN];			//电话号码

protected:
	CBrush							m_brBrush;							//背景画刷
	CSkinLayered					m_SkinLayered;						//分层窗口

	BYTE							m_cbLogonPassLevel;					//密码强度
	BYTE							m_cbInsurePassLevel;				//密码强度
	//控件变量
public:
	CImageList							m_ImageList;
	CComboBoxEx							m_FaceSelect;

	CSkinButtonEx							m_btLogon;						//登录按钮
	CSkinButtonEx							m_btCancel;						//取消按钮
	CSkinButtonEx							m_btClose;						//关闭按钮

	//函数定义
public:
	//构造函数
	CDlgRegister();
	//析构函数
	virtual ~CDlgRegister();
	//密码等级
	BYTE GetPasswordLevel(LPCTSTR pszPassword);
	//登陆密码输入
	VOID OnEnChangeLogonPass();
	//银行密码输入
	VOID OnEnChangeInsurePass();

	//重载函数
protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//初始化函数
	virtual BOOL OnInitDialog();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//确定函数
	virtual void OnOK();
	//取消消息
	virtual void OnCancel();
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//控件颜色
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);


	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//登录对话框
class CDlgLogon : public CDialog
{
	friend class CRoomViewItem;
	friend class CPlazaViewItem;

	//登录信息
protected:
	WORD								m_wFaceID;						//头像标识
	BYTE								m_cbGender;						//用户性别
	DWORD								m_dwUserID;						//用户 I D
	TCHAR								m_szSpreader[NAME_LEN];			//推广人名
	TCHAR								m_szAccounts[NAME_LEN];			//游戏帐号
	TCHAR								m_szPassword[PASS_LEN];			//游戏密码
	TCHAR								m_szBankPassword[PASS_LEN];		//银行密码
	TCHAR								m_szSFZ[PASS_LEN];		//身份证
	TCHAR								m_szPhone[PASS_LEN];		//电话

	//位置变量
protected:
	INT									m_nFullWidth;					//全部宽度
	INT									m_nFullHeight;					//全部高度
	bool								m_bNetOption;					//网络设置
	//CRect								m_rcNormalFrame;				//框架位置

	//登录模式
protected:
	enLogonMode							m_LogonMode;					//登录模式

	//辅助信息
protected:
	bool								m_bRegister;					//注册标志
	bool								m_bChangePassWord;				//改变标志

	//连接信息
protected:
	CString								m_strLogonServer;				//服务器地址

	//按钮变量
public:
	CSkinButtonEx							m_btLogon;						//登录按钮
	CSkinButtonEx							m_btCancel;						//取消按钮
	CSkinButtonEx							m_btDelete;						//删除按钮
	CSkinButtonEx							m_btRegister;					//注册按钮
	CSkinButtonEx							m_btNetOption;					//网络按钮
	CSkinButtonEx							m_btQuit;

	//控件变量
public:
	CSkinLayered						m_SkinLayered;						//分层窗口
	CWebBrowser							m_BrowerAD;							//浏览窗口
	CSkinTabCtrl						m_TabLogonMode;						//登录选择
	CBrush								m_brBrush;							//背景画刷

	CPngImage							m_BackImage;

	//函数定义
public:
	//构造函数
	CDlgLogon();
	//析构函数
	virtual ~CDlgLogon();

	//重载函数
protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//初始化函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual void OnOK();
	//取消消息
	virtual void OnCancel();

	//功能函数
public:
	//获取服务器
	LPCTSTR GetLogonServer() { return m_strLogonServer; }
	//发送登录包
	bool SendLogonPacket(ITCPSocket * pIClientSocke);
	//登录成功处理
	bool OnLogonSuccess();

	//内部函数
private:
	//加载服务器
	void LoadLogonServer();
	//读取帐号
	void LoadAccountsInfo();
	//效验输入
	bool CheckLogonInput(bool bShowError);
	//设置模式
	void SetLogonMode(enLogonMode LogonMode);

	//辅助函数
private:
	//更新密码
	void UpdateUserPassWord(DWORD dwUserDBID);
	//代理模式
	void SwitchNetOption(bool bNetOption);
	//更新选择
	void UpdateUserComboBox(UINT uComboBoxID);
	//查找字符
	int ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString);

	//消息函数
public:
	//注册帐号
	afx_msg void OnRegisterAccounts();
	//删除用户
	afx_msg void OnDeleteAccounts();
	//网络设置
	afx_msg void OnBnClickedNetOption();
	//密码改变
	afx_msg void OnEnChangePassword();
	//选择改变
	afx_msg void OnSelchangeAccounts();
	//选择改变
	afx_msg void OnSelchangeUserID();
	//类型改变
	afx_msg void OnTcnSelchangeLogonType(NMHDR * pNMHDR, LRESULT * pResult);
	//主页
	afx_msg void OnMainPage();
	//新手
	afx_msg void OnNewUser();
	//服务器条款
	afx_msg void OnServer();
	//找回密码
	afx_msg void OnFindPassWord();
	//显示消息
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//位置改变
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//重画消息
	afx_msg void OnPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//控件颜色
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif
