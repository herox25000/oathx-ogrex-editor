#ifndef SERVICE_INDIVIDUAL_HEAD_FILE
#define SERVICE_INDIVIDUAL_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgServiceItem.h"

//////////////////////////////////////////////////////////////////////////////////

//修改资料
class CDlgServiceIndividual : public CDlgServiceItem, public ITCPSocketSink
{
	//友元定义
	friend class CDlgService;

	//变量定义
protected:
	bool							m_bQueryMission;						//查询任务
	bool							m_bModifyMission;						//修改任务

	//网络接口
protected:
	CTCPSocketHelper                m_SocketHelper;
	//帐号资料
protected:
	BYTE							m_cbGender;								//用户性别
	int								m_cbFaceID;								//头像ID
	TCHAR							m_szAccounts[NICKNAME_LEN];				//用户名
	TCHAR							m_szPassword[PASS_LEN];					//用户密码
	TCHAR							m_szUnderWrite[UNDER_WRITE_LEN];		//个性签名

	//详细资料
protected:
	TCHAR							m_szQQ[QQ_LEN];							//Q Q 号码
	TCHAR							m_szEMail[EMAIL_LEN];					//电子邮件
	TCHAR							m_szUserNote[USER_NOTE_LEN];			//用户说明
	TCHAR							m_szSFZ[IDCARD_LEN];					//身份证
	TCHAR							m_szMobilePhone[MOBILE_PHONE_LEN];		//移动电话
	TCHAR							m_szCompellation[COMPELLATION_LEN];		//真实名字
	TCHAR							m_szDwellingPlace[DWELLING_PLACE_LEN];	//联系地址

	//控件变量
protected:
	CSkinEdit						m_edGameID;								//游戏ID
	CSkinEdit						m_edAccounts;							//用户名
	CSkinEdit						m_edPassword;							//修改密码
	CSkinEdit						m_edUnderWrite;							//个性签名

	//控件变量
protected:
	CSkinEdit						m_edQQ;									//Q Q 号码
	CSkinEdit						m_edEMail;								//电子邮件
	CSkinEdit						m_edUserNote;							//用户说明
	CSkinEdit						m_edSFZ	;								//身份证
	CSkinEdit						m_edMobilePhone;						//移动电话
	CSkinEdit						m_edCompellation;						//真实名字
	CSkinEdit						m_edDwellingPlace;						//联系地址

	//控件变量
protected:
	CSkinButton						m_btOk;									//修改按钮
	//头像控件
	CImageList							m_ImageList;
	CComboBoxEx							m_FaceSelect;

	//函数定义
public:
	//构造函数
	CDlgServiceIndividual();
	//析构函数
	virtual ~CDlgServiceIndividual();

	//重载函数
protected:
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//创建函数
	virtual BOOL OnInitDialog();
	//确定函数
	virtual VOID OnOK();
	//取消消息
	virtual VOID OnDestroy();

	//重载函数
public:
	//获取标题
	virtual LPCTSTR GetServiceItemName() { return TEXT("用户资料"); }

	//基础接口
public:
	//释放对象
	virtual void __cdecl Release() { delete this; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//网络事件
private:
	//连接事件
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);

	//事件处理
protected:
	//开始任务
	VOID OnMissionStart();
	//终止任务
	VOID OnMissionConclude();

	//功能函数
private:
	//连接到服务器
	bool ConnetToServer();
	//发送信息查询消息
	void SendQueryIndividualInfoMsg();
	//发送修改信息消息
	void SendModifyIndividualInfoMsg();
	//加载函数
protected:
	//帐号信息
	VOID LoadAccountsInfo();
	//查询资料
	VOID QueryIndividualInfo();
	//更新资料
	VOID UpdateIndividualInfo();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif