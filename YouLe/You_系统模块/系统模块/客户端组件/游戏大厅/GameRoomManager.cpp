#include "StdAfx.h"
#include ".\gameroommanager.h"

CGameRoomManager::CGameRoomManager(void)
{
	
}

CGameRoomManager::~CGameRoomManager(void)
{
}

//创建游戏桌子
bool CGameRoomManager::CreateGameTable()
{
	return true;
}

//关闭房间对话框
void CGameRoomManager::CloserRoomFram()
{

}

//申请入座
void CGameRoomManager::RequestSitdown(WORD wTableID,WORD wChairID,LPCTSTR pszTablePass)
{
	m_RoomSocket.SendSitDownPacket(wTableID,wChairID,pszTablePass);
}

//设置桌子是否加锁
void CGameRoomManager::SetPassFlag(WORD wTableID, bool bPass)
{

}

//设置桌子是否游戏状态
void CGameRoomManager::SetPlayFlag(WORD wTableID, bool bPlay)
{

}

//查询桌子游戏状态
bool CGameRoomManager::QueryPlayFlag(WORD wTableID)
{
	return false;
}