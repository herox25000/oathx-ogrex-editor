#pragma once

#include "UserManager.h"
#include "TimeEngine.h"
#include "Nb30.h"

//״̬��Ϣ
struct tagAstatInfo
{
	ADAPTER_STATUS				AdapterStatus;						//����״̬
	NAME_BUFFER					NameBuff[32];						//���ֻ���
};

class CGameBase : public ITCPSocketSink
{
	friend class CTimerEngine;
public:
	CGameBase(DWORD dwUserID);
	virtual ~CGameBase(void);

public:
	//�ͷŶ���
	virtual void __cdecl Release() { }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

public:
	//������ַ
	WORD GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize);

	//��ȡ����
	void GetClientSerial(tagClientSerial & ClientSerial);

	//bool SetEventService(IUnknownEx * pIUnknownEx);

	void SetTimerEngine(CTimerEngine *pTimerEngine){m_pTimerEngine = pTimerEngine;}

	bool BeginServer(CString strIP, WORD wPort, CString strPsw);

	void EndServer();

	bool IsSitOk(){return m_bSitOk;}

	void		SetSmall(){m_bSmall = true;}
protected:
	bool OnSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	bool SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData=NULL, WORD wDataSize=0);

	int  ShowMessageBox(CString strMsg);

	void SendChatMessage(CString strMsg);
protected:
	CTCPSocketHelper		m_ClientSocket;				//��������
	//IEventService			* m_pIEventService;			//�¼�����
	CUserManager			m_RoomUserManager;			//��������ҹ���
	CUserManager			m_GameUserManager;			//��Ϸ����ҹ���
	tagUserInfo				m_MeUserInfo;				//�������Լ�����Ϣ
	BYTE					m_bGameStatus;				//��Ϸ״̬
	CString					m_strPsw;
	CTimerEngine			*m_pTimerEngine;			//��ʱ��
	bool					m_bPlaying;					//��Ϸ״̬
	bool					m_bSitOk;					//�ɹ�����
	bool					m_bSmall;					//ѹС
protected:
	bool SitDown();
	//���ö�ʱ��
	bool SetTimer(WORD wTimerID, DWORD dwElapse, DWORD dwRepeat);
	//ɾ����ʱ��
	bool KillTimer(WORD wTimerID);
	//ɾ����ʱ��
	bool KillAllTimer();
	//��ʱ����Ϣ
	virtual void OnTimer(WORD wTimerID) = NULL;
private:
	////����������Ϣ
	//bool __cdecl OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke);
	////�����ȡ��Ϣ
	//virtual bool __cdecl OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	////����ر���Ϣ
	//virtual bool __cdecl OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer);


	//�����¼�
	bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pBuffer, WORD wDataSize);


	//���������Ϣ
	void InsertTableUser(tagUserInfo *pUserInfo);
	//��Ϸ״̬����
	void OnUserStatus(DWORD dwUserID, BYTE cbUserStatus);

	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	bool OnSocketMainGameFrame(CMD_Command Command, void * pBuffer, WORD wDataSize);

	//��ͨ��
	bool OnMainSocket(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	//��Ϸ״̬
	virtual bool OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize)=NULL;
	//��Ϸ��Ϣ
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, WORD wDataSize=0)=NULL;
	//������Ϸ
	virtual void ResetGame()=NULL;
};
