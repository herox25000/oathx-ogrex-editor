#pragma once
#include "DlgLogon.h"
class CPlatformSocket :public ITCPSocketSink
{
public:
	CPlatformSocket(void);
	~CPlatformSocket(void);
public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//�����¼�
public:
	//�����¼�
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);

public:
	//���ӵ�������
	void ConnectToServer(LPCTSTR ServerIP,WORD wPort);
	//������Ϣ
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);
	//��ʾ��Ϣ
	int ShowMessageBox(LPCTSTR pszMessage, UINT nType);

	//��Ӧ��������Ϣ����
public:
	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize);
	//�б���Ϣ
	bool OnSocketMainServerList(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//ϵͳ��Ϣ
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);

public:
	void  SetPlatFormPointer(CWnd* pPointer)	{m_pPlatformFrame = pPointer;}
	void  SetDlgLogonPointer(CDlgLogon* pPointer) {m_pDlgLogon = pPointer;}
public:
	CTCPSocketHelper				m_ClientSocket;						//��������
	CWnd*							m_pPlatformFrame;
	CDlgLogon*						m_pDlgLogon;
	bool							m_bLogonPlaza;
	
};
