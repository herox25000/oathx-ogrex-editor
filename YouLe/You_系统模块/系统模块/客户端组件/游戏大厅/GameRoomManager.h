#pragma once
#include "GameRoomSocket.h"

struct TableInfo 
{
	WORD		wTableID;				//桌子号码
	bool		bTableLock;				//锁定状态
	bool		bPlayStatus;			//游戏状态
	int			lPlayerCount;			//玩家数量
	WORD		wChairCount;			//椅子数目
	IUserItem*	pIUserItem[MAX_CHAIR];	//用户信息
};

typedef CArrayTemplate<TableInfo *> CTableArray;

class CGameRoomManager
{
public:
	CGameRoomManager(void);
	~CGameRoomManager(void);

	//函数
public:
	//进入房间
	void	EnterRoom(CListServer * pListServer);
	//退出房间
	void	QuitRoom();
	//创建桌子
	bool	CreateGameTable(WORD wTableCount, WORD wChairCount, CListServer* ListServer);
	//申请入座
	void	RequestSitdown(WORD wTableID,WORD wChairID);
	//快速入座
	bool	OnFastJoin();
	//设置用户信息
	bool	SetUserInfo(WORD wTableID, WORD wChairID, IUserItem * pIUserItem);
	//获取用户信息
	IUserItem* GetUserInfo(WORD wTableID, WORD wChairID);
	//设置桌子是否加锁
	void	SetPassFlag(WORD wTableID, bool bPass);
	//设置桌子是否游戏状态
	void	SetPlayFlag(WORD wTableID, bool bPlay);
	//查询桌子游戏状态
	bool	QueryPlayFlag(WORD wTableID);
	//删除所有桌子
	void 	RemoveAllTable();
	//枚举桌子
	TableInfo* EnumTableItem(INT_PTR nIndex);

	//变量
public:
	CGameRoomSocket					m_RoomSocket;
	CTableArray						m_PtrArrayTable;					//桌子列表
	IUserItem*						m_pMeUserItem;						//自己信息
	CClientUserManager				m_ClientUserManager;				//用户管理
	WORD							m_wTableCount;						//桌子数量
	WORD							m_wChairCount;						//椅子数量
	CListServer*					m_pListServer;						//房间信息
};
