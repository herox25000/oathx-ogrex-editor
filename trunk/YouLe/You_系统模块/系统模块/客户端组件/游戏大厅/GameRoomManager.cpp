#include "StdAfx.h"
#include ".\gameroommanager.h"

CGameRoomManager::CGameRoomManager(void)
{
	
}

CGameRoomManager::~CGameRoomManager(void)
{
}

//������Ϸ����
bool CGameRoomManager::CreateGameTable()
{
	return true;
}

//�رշ���Ի���
void CGameRoomManager::CloserRoomFram()
{

}

//��������
void CGameRoomManager::RequestSitdown(WORD wTableID,WORD wChairID,LPCTSTR pszTablePass)
{
	m_RoomSocket.SendSitDownPacket(wTableID,wChairID,pszTablePass);
}

//���������Ƿ����
void CGameRoomManager::SetPassFlag(WORD wTableID, bool bPass)
{

}

//���������Ƿ���Ϸ״̬
void CGameRoomManager::SetPlayFlag(WORD wTableID, bool bPlay)
{

}

//��ѯ������Ϸ״̬
bool CGameRoomManager::QueryPlayFlag(WORD wTableID)
{
	return false;
}