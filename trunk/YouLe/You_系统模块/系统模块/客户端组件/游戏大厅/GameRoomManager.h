#pragma once
#include "GameRoomSocket.h"

struct TableInfo 
{
	WORD	wTableID;			//���Ӻ���
	BYTE	bTableLock;			//����״̬
	BYTE	bPlayStatus;		//��Ϸ״̬
	int		lPlayerCount;		//�������
	WORD	wChairCount;		//������Ŀ
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
	bool	CreateGameTable(int lTableCount,CListServer* ListServer);
	//��������
	void	RequestSitdown(WORD wTableID,WORD wChairID,LPCTSTR pszTablePass);
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
	CGameRoomSocket			m_RoomSocket;
	CTableArray				m_PtrArrayTable;	//�����б�
};
