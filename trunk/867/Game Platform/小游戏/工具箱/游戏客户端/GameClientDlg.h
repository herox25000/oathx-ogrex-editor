#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "TransDialog.h"
#include "Nb30.h"

//״̬��Ϣ
struct tagAstatInfo
{
	ADAPTER_STATUS				AdapterStatus;						//����״̬
	NAME_BUFFER					NameBuff[16];						//���ֻ���
};
//////////////////////////////////////////////////////////////////////////

//��Ϸ�Ի���
class CGameClientDlg : public CSkinDialogEx, public ITCPSocketSink
{
public:
	//���캯��
	CGameClientDlg();
	//��������
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
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//�ؼ���
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//�ں˱���
private:
	CTCPSocketHelper		m_ClientSocket;						//��������
public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//������ַ
	WORD GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);
	//��ȡ����
	void GetClientSerial(tagClientSerial & ClientSerial);
	//�����¼�
	bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pBuffer, WORD wDataSize);


	//����������
protected:
	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//ϵͳ��Ϣ
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//ס��Ϸ
	bool OnSocketMainGame(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketMainFrame(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�״̬
	bool OnSocketSubStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketMainInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketServerInfo(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketSubUserCome(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketSubSitFailed(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSocketSubScore(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSocketMainStatus(CMD_Command Command, void * pBuffer, WORD wDataSize);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
