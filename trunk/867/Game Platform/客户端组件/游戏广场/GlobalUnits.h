#ifndef GLOBAL_UNITS_HEAD_FILE
#define GLOBAL_UNITS_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgStatus.h"
#include "RoomViewItem.h"
#include "PlazaViewItem.h"
#include "ServerItemView.h"

//////////////////////////////////////////////////////////////////////////

//全局用户资料
struct tagGlobalUserData
{
	WORD								wFaceID;						//头像索引
	BYTE								cbGender;						//用户性别
	BYTE								cbMember;						//会员等级
	BYTE								cbMoorMachine;					//账号是否锁定
	DWORD								dwUserID;						//用户 I D
	DWORD								dwGameID;						//游戏 I D
	DWORD								dwExperience;					//用户经验
	TCHAR								szAccounts[NAME_LEN];			//登录帐号
	TCHAR								szPassWord[PASS_LEN];			//登录密码
	TCHAR								szGroupName[GROUP_LEN];			//社团信息
	TCHAR								szUnderWrite[UNDER_WRITE_LEN];	//个性签名
	DWORD								dwCustomFaceVer;				//头像版本
};


//扩展资料
struct tagIndividualUserData
{
	//用户信息
	DWORD							dwUserID;							//用户 I D
	TCHAR							szUserNote[USER_NOTE_LEN];			//用户说明
	TCHAR							szCompellation[COMPELLATION_LEN];	//真实名字
	TCHAR							szSFZ[IDCARD_LEN];					//身份证
	//电话号码
	TCHAR							szMobilePhone[MOBILE_PHONE_LEN];	//移动电话
	//联系资料
	TCHAR							szQQ[QQ_LEN];						//Q Q 号码
	TCHAR							szEMail[EMAIL_LEN];					//电子邮件
	TCHAR							szDwellingPlace[DWELLING_PLACE_LEN];//联系地址
};

//全局信息类
class CGlobalUnits
{
	//信息变量
protected:
	TCHAR								m_szStationPage[32];			//站点页面
	tagGlobalUserData					m_GloblaUserData;				//用户信息
	tagIndividualUserData				m_IndividualUserData;			//扩展资料
	//系统变量
protected:
	DWORD								m_dwPlazaVersion;				//大厅版本
	TCHAR								m_szDirSkin[MAX_PATH];			//皮肤目录
	TCHAR								m_szDirWork[MAX_PATH];			//工作目录

	//组件变量
public:
	CServerListManager					m_ServerListManager;			//列表管理
public:
	LPCTSTR								m_LogonServerIP;				//登陆服务器地址
	WORD								m_LogonServerPort;				//登陆服务器端口

	//资源变量
public:
	tagPlazaViewImage					m_PlazaViewImage;				//广场资源
	tagServerViewImage					m_ServerViewImage;				//房间资源
	tagWhisperViewImage					m_WhisperViewImage;				//私聊资源
	tagControlViewImage					m_ControlViewImage;				//控件资源
	tagPlatformFrameImage				m_PlatformFrameImage;			//框架资源
	tagChatExpViewImage					m_ChatExpViewImage;				//表情资源
	tagPropertyViewImage				m_PropertyViewImage;			//道具资源

	//组件定义
public:
	CUserFaceResHelper					m_UserFaceRes;					//头像组件
	CDownLoadServiceHelper				m_DownLoadService;				//下载服务
	CCompanionManagerHelper				m_CompanionManager;				//关闭管理
	CPlatformResourceHelper				m_PlatformResourceModule;		//资源组件

	//函数定义
public:
	//构造函数
	CGlobalUnits(void);
	//析构函数
	virtual ~CGlobalUnits(void);

	//功能函数
public:
	//初始化函数
	bool InitGlobalUnits();
	//拷贝字符
	bool CopyToClipboard(LPCTSTR pszString);
	//获取序列
	void GetClientSerial(tagClientSerial & ClientSerial);
	//注册热键
	bool RegisterHotKey(HWND hWnd, UINT uKeyID, WORD wHotKey);
	//记录登陆服务器端口和地址
	void SetLogonServerInfo(LPCTSTR IP,WORD Port){m_LogonServerIP=IP;m_LogonServerPort=Port;}
	//查询函数
public:
	//大厅版本
	DWORD GetPlazaVersion() { return m_dwPlazaVersion; }
	//工作目录
	LPCTSTR GetWorkDirectory() { return m_szDirWork; }
	//界面目录
	LPCTSTR GetSkinDirectory() { return m_szDirSkin; }

	//状态函数
public:
	//设置主站地址
	LPCTSTR SetStationPage(LPCTSTR pszStationPage);
	//获取主站地址
	LPCTSTR GetStationPage() { return m_szStationPage; }
	//获取用户信息
	tagGlobalUserData & GetGolbalUserData() { return m_GloblaUserData; }
	//获得用户信息地址
	tagGlobalUserData*  GetGolbalUserDataEx() { return &m_GloblaUserData; }
	//扩展资料
	tagIndividualUserData * GetIndividualUserData() { return &m_IndividualUserData; }
	//组件函数
public:
	//头像接口
	IUserFaceRes * GetUserFaceRes() { return m_UserFaceRes.GetInterface(); }

	//甜饼信息
public:
	//记录甜饼
	bool WriteUserCookie();
	//删除甜饼
	bool DeleteUserCookie();

	//内部函数
private:
	//网卡地址
	WORD GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
	//读取大厅版本
	DWORD ReadPlazaVersion();
};

//////////////////////////////////////////////////////////////////////////

//全局调度类
class CGlobalAttemper
{
	//控件变量
protected:
	CDlgStatus							m_DlgStatus;					//状态窗口

	//函数定义
public:
	//构造函数
	CGlobalAttemper(void);
	//析构函数
	virtual ~CGlobalAttemper(void);

	//功能函数
public:
	//显示提示
	bool ShowStatusMessage(LPCTSTR pszMessage, CWnd * pNotifyWnd);
	//关闭提示
	bool DestroyStatusWnd(CWnd * pNotifyWnd);
	//下载游戏
	bool DownLoadClient(LPCTSTR pszKindName, WORD wKindID, bool bDisplay);
};

//////////////////////////////////////////////////////////////////////////

//全局信息 
extern	CGlobalUnits					g_GlobalUnits;					//信息组件			
extern	CGlobalAttemper					g_GlobalAttemper;				//全局调度

//////////////////////////////////////////////////////////////////////////

#endif