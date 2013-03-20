#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "TransDialog.h"
#include "Nb30.h"

//状态信息
struct tagAstatInfo
{
	ADAPTER_STATUS				AdapterStatus;						//网卡状态
	NAME_BUFFER					NameBuff[16];						//名字缓冲
};
//////////////////////////////////////////////////////////////////////////

//游戏对话框
class CGameClientDlg : public CSkinDialogEx, public ITCPSocketSink
{
public:
	//构造函数
	CGameClientDlg();
	//析构函数
	virtual ~CGameClientDlg();

public:
	CString			m_strIP;
	CString			m_strPort;
	CString			m_strUID;
	CString			m_strAccount;
	CString			m_strPlazaVersion;
	CString			m_strPasword;
	CString			m_strCPU;
	CString			m_strLockMyComputer;

	CTransDialog	m_TransDialog;
	CDialog			m_TipDialog;
public:
	void		Msg(LPCTSTR lpszText);
	void		ShowWaitWindow();
	void		UpdateUserData(tagUserData* pUserData);
	BOOL		IsValidPassword(CString str);
	__int64		GetDlgItemInt64(UINT uID);
	void		SetDlgItemInt64(UINT uID, __int64 value);
	void		OnModifyLoginPassword();
	void		OnModifyBankPassword();
	void		OnModifyNickname();
	void		OnBankQuery();
	void		OnBankDeposit();
	void		OnBankWithdraw();
	void		OnTransferMoney();
	void		OnQueryTransferLog();
	bool		SendLogonPacket();
	bool		SendUserRulePacket();
	bool		SendSitDownPacket();
	bool		OnLogonSuccess();

protected:
	//控件绑定
	virtual void DoDataExchange(CDataExchange * pDX);
	//控件绑定
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//内核变量
private:
	CTCPSocketHelper		m_ClientSocket;						//网络连接
public:
	//释放对象
	virtual void __cdecl Release() { delete this; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//网卡地址
	WORD GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
	//获取序列
	void GetClientSerial(tagClientSerial & ClientSerial);
	//连接事件
	bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pBuffer, WORD wDataSize);


	//网络主命令
protected:
	//登录消息
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//系统消息
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//住游戏
	bool OnSocketMainGame(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketMainFrame(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户状态
	bool OnSocketSubStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketMainInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketServerInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketSubUserCome(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//游戏消息
	bool OnSocketSubSitFailed(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户分数
	bool OnSocketSubScore(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户分数
	bool OnSocketMainStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);

	//重画消息
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
