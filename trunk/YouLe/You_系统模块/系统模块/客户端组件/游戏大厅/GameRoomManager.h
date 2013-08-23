#pragma once
#include "GameRoomSocket.h"

struct TableInfo 
{
	WORD		wTableID;				//���Ӻ���
	bool		bTableLock;				//����״̬
	bool		bPlayStatus;			//��Ϸ״̬
	int			lPlayerCount;			//�������
	WORD		wChairCount;			//������Ŀ
	IUserItem*	pIUserItem[MAX_CHAIR];	//�û���Ϣ
};

typedef CArrayTemplate<TableInfo *> CTableArray;

class CGameRoomManager
{
public:
	CGameRoomManager(void);
	~CGameRoomManager(void);

	//����
public:
	//���뷿��
	void	EnterRoom(CListServer * pListServer);
	//�˳�����
	void	QuitRoom();
	//��������
	bool	CreateGameTable(WORD wTableCount, WORD wChairCount, CListServer* ListServer);
	//��������
	void	RequestSitdown(WORD wTableID,WORD wChairID);
	//��������
	bool	OnFastJoin();
	//�����û���Ϣ
	bool	SetUserInfo(WORD wTableID, WORD wChairID, IUserItem * pIUserItem);
	//��ȡ�û���Ϣ
	IUserItem* GetUserInfo(WORD wTableID, WORD wChairID);
	//���������Ƿ����
	void	SetPassFlag(WORD wTableID, bool bPass);
	//���������Ƿ���Ϸ״̬
	void	SetPlayFlag(WORD wTableID, bool bPlay);
	//��ѯ������Ϸ״̬
	bool	QueryPlayFlag(WORD wTableID);
	//ɾ����������
	void 	RemoveAllTable();
	//ö������
	TableInfo* EnumTableItem(INT_PTR nIndex);

	//����
public:
	CGameRoomSocket					m_RoomSocket;
	CTableArray						m_PtrArrayTable;					//�����б�
	IUserItem*						m_pMeUserItem;						//�Լ���Ϣ
	CClientUserManager				m_ClientUserManager;				//�û�����
	WORD							m_wTableCount;						//��������
	WORD							m_wChairCount;						//��������
	CListServer*					m_pListServer;						//������Ϣ
};
