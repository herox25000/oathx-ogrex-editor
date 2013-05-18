#ifndef SERVICE_PASSWORD_HEAD_FILE
#define SERVICE_PASSWORD_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "DlgServiceItem.h"

//////////////////////////////////////////////////////////////////////////////////

//修改资料
class CDlgServicePassword : public CDlgServiceItem, public ITCPSocketSink
{
	//变量定义
protected:
	bool							m_bLogonMission;				//是否为修改登录密码
	CTCPSocketHelper				m_SocketHelper;					//网络连接
	//密码强度
protected:
	BYTE							m_cbLogonPasswordLevel;				//密码强度
	BYTE							m_cbInsurePasswordLevel;			//密码强度

	//密码资料
protected:
	TCHAR							m_szSrcPassword[PASS_LEN];		//用户密码
	TCHAR							m_szDesPassword[PASS_LEN];		//用户密码

	//控件变量
protected:
	CPasswordControl				m_edLogonPassword1;					//帐号密码
	CPasswordControl				m_edLogonPassword2;					//帐号密码
	CPasswordControl				m_edLogonPassword3;					//帐号密码
	CPasswordControl				m_edInsurePassword1;				//二级密码
	CPasswordControl				m_edInsurePassword2;				//二级密码
	CPasswordControl				m_edInsurePassword3;				//二级密码

	//控件变量
protected:
	CSkinButton						m_btLogonPassword;					//修改按钮
	CSkinButton						m_btInsurePassword;					//修改按钮

	//函数定义
public:
	//构造函数
	CDlgServicePassword();
	//析构函数
	virtual ~CDlgServicePassword();

	//重载函数
protected:
	//控件绑定
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//重载函数
public:
	//获取标题
	virtual LPCTSTR GetServiceItemName() { return TEXT("修改密码"); }

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
public:
	//密码等级
	BYTE GetPasswordLevel(LPCTSTR pszPassword);
	//连接到服务器
	bool ConnetToServer();
	//消息映射
protected:
	//取消
	virtual VOID OnDestroy();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//密码输入
	VOID OnEnChangeLogonPassword();
	//密码输入
	VOID OnEnChangeInserePassword();
	//密码修改
	VOID OnBnClickedLogonPassword();
	//密码修改
	VOID OnBnClickedInsurePassword();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif