#pragma once
#include "GameRoomSocket.h"

class CGameRoomManager
{
public:
	CGameRoomManager(void);
	~CGameRoomManager(void);

	//函数
public:
	//创建桌子
	bool	CreateGameTable();
	//关闭房间对话框
	void	CloserRoomFram();
	//申请入座
	void	RequestSitdown(WORD wTableID,WORD wChairID,LPCTSTR pszTablePass);
	//设置桌子是否加锁
	void	SetPassFlag(WORD wTableID, bool bPass);
	//设置桌子是否游戏状态
	void	SetPlayFlag(WORD wTableID, bool bPlay);
	//查询桌子游戏状态
	bool	QueryPlayFlag(WORD wTableID);

	//变量
public:
	CGameRoomSocket			m_RoomSocket;

};
