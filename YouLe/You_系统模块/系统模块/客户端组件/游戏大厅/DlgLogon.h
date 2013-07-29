#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "PasswordControl.h"
#include "GdipButton.h"
#include "MemDC.h"
#include "LogonFramSheet.h"


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
	bool                           m_cbChecked;                        //记住密码
	CWnd *                         m_pParentSink;                      //父类指针

	//位置变量
protected:
	CPoint                         m_ptControlBenchmark;               //基准位置

	//资源变量
protected:
	CPngImage		m_ImageBack;
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
	//获取状态
	inline bool  GetButtonChecked() { return m_cbChecked; };
	//设置状态
	inline VOID  SetButtonChecked(bool cbChecked);
	//创建(只能添加PNG资源)
	void CreatCheckButton(CWnd* pParentWnd,HINSTANCE hInstance, LPCTSTR pszResourceName,INT nXPos,INT nYPos);

	//事件函数
public:
	//绘制控件
	VOID  OnDrawControl(CDC * pDC);
	//点击事件
	bool  OnClickControl(CPoint Point);

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
	CPngImage							m_ImageBack;
	CPngImage							m_ImagePasswordLevel;

	TCHAR*		m_StrSheng[36];
	TCHAR*		m_StrDiqu[36][21];
	//控件变量
public:
	CGdipButton							m_btEixt;
	CGdipButton							m_btRegisterOk;
	CControlCheckButton					m_btMan;
	CControlCheckButton					m_btWoman;

	CSkinEditEx				m_NameEdit;
	CSkinEditEx				m_SfzEdit;
	CSkinComboBox			m_BoxChengshi;
	CSkinComboBox			m_BoxDiqu;

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

	void InitChengShiDiQu();
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
	afx_msg void OnCbnSelchangeComboChengshi();
	afx_msg void OnCbnSelchangeComboDiqu();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//登录对话框
class CDlgLogon : public CDialog
{
public:
	CWnd*		m_pPlatformFrame;
	//登录信息
protected:
	WORD								m_wFaceID;						//头像标识
	BYTE								m_cbGender;						//用户性别
	DWORD								m_dwUserID;						//用户 I D
	TCHAR								m_szAccounts[NAME_LEN];			//游戏帐号
	TCHAR								m_szPassword[PASS_LEN];			//游戏密码
	TCHAR								m_szLikeName[NAME_LEN];			//昵称
	TCHAR								m_szAddress[32];				//地址
	TCHAR								m_szName[NAME_LEN];				//
	TCHAR								m_szSFZ[PASS_LEN];				//身份证号码
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
	
	//连接信息
protected:
	CString								m_strLogonServer;				//服务器地址
	CPngImage							m_ImageBack;
	CPngImage							m_ImageLimitprompt;
	CPngImage							m_ImageEighteen;
	//按钮变量
public:
	CGdipButton							m_btCancel;						//取消按钮
	CGdipButton							m_btLogon;
	CGdipButton							m_btWebhome;
	CGdipButton							m_btRegister;
	CGdipButton							m_btChongzhi;
	CGdipButton							m_btBanben;

	CSkinEditEx							m_edAccounts;						//登录帐号
	CSkinEditEx							m_edPassWord;
	CControlCheckButton					m_RemPwdControl;

	//软件键盘
	CGdipButton							m_btNumber[10];		//数字按钮
	CGdipButton							m_btAlphabet[26];	//字母按钮
	CGdipButton							m_btOther[2];		//删除和大写
	//
public:
	TCHAR								m_szKeyboradNumber[2][11];			//键盘字符
	TCHAR								m_szKeyboradChar[2][27];			//键盘字符
	bool								m_bCaps;	//是否大写
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

public:
	YouLe::UILogonFramSheet				m_LogonFramSheet;
	bool								m_bCreateUI;
	bool								m_bHandCur;
	bool								m_bLimit;
	//函数定义
public:
	//构造函数
	CDlgLogon();
	//析构函数
	virtual ~CDlgLogon();
	//设置大厅指针
	void SetPlatFormPointer(CWnd* pPointer)	{m_pPlatformFrame = pPointer;}
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

	//辅助函数
private:
	//更新密码
	//void UpdateUserPassWord(DWORD dwUserDBID);
	//代理模式
	//void SwitchNetOption(bool bNetOption);
	//更新选择
	//void UpdateUserComboBox(UINT uComboBoxID);
	//查找字符
	//int ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString);
	//获取代理
	//void GetProxyInfo(enProxyServerType &ProxyServerType, tagProxyServerInfo &ProxyServerInfo);
	//代理判断
	bool EnableProxy() { return m_bNetOption;}

	//消息函数
public:
	//注册帐号
	afx_msg void OnRegisterAccounts();
	afx_msg void OnWebhome();
	afx_msg void OnChongzhi();
	afx_msg void OnBanben();
	//响应软键盘
	afx_msg void OnKeyBoard(UINT uID);
	//密码改变
	//afx_msg void OnEnChangePassword();
	//选择改变
	//afx_msg void OnSelchangeAccounts();
	//选择改变
	//afx_msg void OnSelchangeUserID();
	//控件改变
//	void OnEnChangeAccounts();
	//重画消息
	afx_msg void OnPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//鼠标弹起
	void OnLButtonUp(UINT nFlags, CPoint point);
	//
	void OnMouseMove(UINT nFlags, CPoint point);
	//光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif