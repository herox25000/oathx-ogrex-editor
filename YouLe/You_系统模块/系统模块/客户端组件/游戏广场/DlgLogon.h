#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "PasswordControl.h"
#include "GdipButton.h"
#include "MemDC.h"


//////////////////////////////////////////////////////////////////////////

//登录模式
enum enLogonMode
{
	LogonMode_Accounts,			//帐号登录
	LogonMode_UserID,			//I D 登录
};

//注册表项名
#define REG_OPTION_LOGON		TEXT("OptionLogon")
#define REG_USER_INFO			TEXT("Software\\WHQPGame\\GamePlaza\\UserInfo")
#define REG_LOGON_SERVER		TEXT("Software\\WHQPGame\\GamePlaza\\LogonServer")

//////////////////////////////////////////////////////////////////////////
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
	CBitmap						 m_ImageBtnBack;                     //背景资源

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
//////////////////////////////////////////////////////////////////////////

//用户注册
class CDlgRegister : public CDialog
{
	friend class CDlgLogon;
	enum passLevel
	{		
		PASSWORD_LEVEL_0=0,	
		PASSWORD_LEVEL_1,			
		PASSWORD_LEVEL_2,		
		PASSWORD_LEVEL_3		
	};
	//登录信息
public:
	WORD								m_wFaceID;						//头像标识
	BYTE								m_cbGender;						//用户性别
	TCHAR								m_szAccounts[NAME_LEN];			//游戏帐号
	TCHAR								m_szPassword[PASS_LEN];			//游戏密码
	TCHAR								m_szLikeName[NAME_LEN];			//昵称
	TCHAR								m_szAddress[32];				//地址
	TCHAR								m_szName[NAME_LEN];				//
	TCHAR								m_szSFZ[PASS_LEN];				//身份证号码

	BYTE								m_cbLogonPassLevel;					//密码强度
	CPngImage m_ImageBack;
	CPngImage m_ImagePasswordLevel;
	//控件变量
public:
	CGdipButton				m_btEixt;
	CGdipButton				m_btRegisterOk;
	CGdipButton				m_btMan;
	CGdipButton				m_btWoman;

	//函数定义
public:
	//构造函数
	CDlgRegister();
	//析构函数
	virtual ~CDlgRegister();
	//按钮函数
	void SetButtonBackGrounds(CDC *pDC);
	//密码等级
	BYTE GetPasswordLevel(LPCTSTR pszPassword);
	//登陆密码输入
	VOID OnEnChangeLogonPass();

	//重载函数
protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//初始化函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual void OnOK();
	//取消消息
	virtual void OnCancel();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标弹起
	void OnLButtonUp(UINT nFlags, CPoint point);


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

	//位置变量
protected:
	INT									m_nFullWidth;					//全部宽度
	INT									m_nFullHeight;					//全部高度
	bool								m_bNetOption;					//网络设置
	CRect								m_rcNormalFrame;				//框架位置

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
	CPngImage							m_ImageBack;
	//按钮变量
public:
	CSkinButton							m_btCancel;						//取消按钮
	CGdipButton							m_btLogon;
	CGdipButton							m_btWebhome;
	CGdipButton							m_btRegister;
	CGdipButton							m_btChongzhi;
	CGdipButton							m_btBanben;

	CSkinEditEx							m_edAccounts;						//登录帐号
	CPasswordControl					m_PasswordControl;					//用户密码
	CControlCheckButton					m_RemPwdControl;

	CSkinButton							m_btDelete;						//删除按钮

	CSkinButton							m_btNetOption;					//网络按钮
	CSkinButton							m_btProxyTest;					//测试按钮

	//控件变量
public:
	CWebBrowser							m_BrowerAD;						//浏览窗口
	CSkinHyperLink						m_LineMainPage;					//游戏主页
	CSkinHyperLink						m_LinePassWord;					//密码保护
	CSkinHyperLink						m_LineGetPassWord;				//取回密码

	//编辑控件
protected:
	CSkinEdit							m_edProxyPort;					//代理端口
	CSkinEdit							m_edProxyServer;				//代理地址
	CSkinEdit							m_edProxyUserName;				//代理用户
	CSkinEdit							m_edProxyPassword;				//代理密码
	CComboBox							m_cmProxyServerType;			//代理类型

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
	//代理信息
	void LoadProxyServerInfo();
	//效验输入
	bool CheckLogonInput(bool bShowError);

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
	//获取代理
	void GetProxyInfo(enProxyServerType &ProxyServerType, tagProxyServerInfo &ProxyServerInfo);
	//代理判断
	bool EnableProxy() { return m_bNetOption;}

public:
	//按钮函数
	void SetButtonBackGrounds(CDC *pDC);
	//消息函数
public:
	//注册帐号
	afx_msg void OnRegisterAccounts();
	afx_msg void OnWebhome();
	afx_msg void OnChongzhi();
	afx_msg void OnBanben();
	//密码改变
	afx_msg void OnEnChangePassword();
	//选择改变
	afx_msg void OnSelchangeAccounts();
	//选择改变
	afx_msg void OnSelchangeUserID();
	//控件改变
	void OnEnChangeAccounts();
	//重画消息
	afx_msg void OnPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标弹起
	void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif