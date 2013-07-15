#pragma once
#include "Stdafx.h"
#include "GameLogic.h"
#define GAME_PLAYER 3
class CUserInterface :public CClientSocketHelper,public IClientSocketSink
{
public:
	bool    bIsExitByUser;
	CUserInterface(void);
	~CUserInterface(void);
protected:
	int     DelayTime;             //��ǰ״̬������Ҫ��ʱ��
	DWORD   UserID;                //�û�ID
	TCHAR   szPassword[33];        //�û�����
	BYTE	UserStatus;			   //�û���ǰ״̬���Լ����壩
	BYTE    GameStatus;            //�û���Ϸ״̬����Ϸ���壩
	BYTE    ExitGameStatus;        //�û��˳���Ϸ״̬
	BYTE    TableID;			   //�������Ӻ�
	BYTE    ChairID;			   //����λ�ú�
	BYTE    TableOldID;			   //�������Ӻ�
	BOOL    bIsInvite;
	int     m_TableNum;           //��������
	int     m_ChairNum;           //��������
	DWORD			dwIP;           //ip��ַ
	WORD			wPort;          //�˿�
	int          m_GameNum;         //��ľ���
	int          m_CurrentGameNum;   //������ľ���
	BOOL         bIsReSel;
	CGameLogic						m_GameLogic;						//��Ϸ�߼�
public:
	void   CreateSocketInstance();

	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CUserInterface))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//����������Ϣ
	virtual bool __cdecl OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke);
	//�����ȡ��Ϣ
	virtual bool __cdecl OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke);
	//����ر���Ϣ
	virtual bool __cdecl OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer);
	//�����û�����
	void   SetUserStatus(BYTE mUserStatus);
	void   SetUserID(DWORD mUserID);
	void   SetUserPass(TCHAR *mUserPass);
	void   SetTable(BYTE mTable,BYTE mChair);
	void   SetDealyTime(int mDelayTime);
	void   SetConnectInfo(DWORD	mIP,WORD mPort);
	//ȡ���û�����
	BYTE   GetUserStatus();
	DWORD  GetUserID();
	BYTE   GetTableID();
	BYTE   GetChairID();
	//ʱ��Ƭ����
	bool   ConnectSever();
	//�������ݰ�
	void   SendLogonData();
	//���ͺ���
	bool SendGameData(WORD wSubCmdID);
	//���ͺ���
	bool SendGameData(WORD wSubCmdID, void * pData, WORD wDataSize);
	//������Ϸ��Ϣ
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
	virtual bool SubDelayTime();
protected:
	//�������ݰ�
	void   SendReqSiteData();
	void   SendReqStandUpData();
	void   SendUserReadyData();
	bool   SearchTableChair();
public:
	BOOL          bIsMannageTableInfo;  //�������ӵ��û�
};