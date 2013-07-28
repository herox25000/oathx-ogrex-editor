#pragma once
#include "GameRoomSocket.h"

class CGameRoomManager
{
public:
	CGameRoomManager(void);
	~CGameRoomManager(void);

	//����
public:
	//��������
	bool	CreateGameTable();
	//�رշ���Ի���
	void	CloserRoomFram();
	//��������
	void	RequestSitdown(WORD wTableID,WORD wChairID,LPCTSTR pszTablePass);
	//���������Ƿ����
	void	SetPassFlag(WORD wTableID, bool bPass);
	//���������Ƿ���Ϸ״̬
	void	SetPlayFlag(WORD wTableID, bool bPlay);
	//��ѯ������Ϸ״̬
	bool	QueryPlayFlag(WORD wTableID);

	//����
public:
	CGameRoomSocket			m_RoomSocket;

};
