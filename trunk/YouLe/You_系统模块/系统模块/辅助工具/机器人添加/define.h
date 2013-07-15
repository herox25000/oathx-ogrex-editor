#pragma once
#define USER_NUM       500            //登陆的最大数量
#define TABLE_NUM      100          //桌子的最大数量
#define CHAIR_NUM      8			//桌子上座位的最大个数

//用户状态
#define NOCONNECT       0           //还没有连接好
#define NOREADY         1           //数据还没有设置好
#define STILLINROOM     2			//在房间大厅
#define SITINDESK       3			//坐在位子上
#define READYTOSIT      4			//已经同意开始
#define GAMEPLAYING     5			//在游戏状态
#define GAMEFINISH      6			//游戏结束状态
#define OFFLINE         7			//断线重入状态
#define CLOSECONNECT    8			//下线状态

//游戏状态
#define GAMESCORE       9			//叫分状态
#define OUTCARD         10			//出牌状态
#define OUTCARDPASS     11			//出牌状态
//桌子状态
#define TABLEFREE        0			//可以坐
#define TABLEPLAYING     1			//游戏开始，不能坐


//桌子信息
struct TableInfo
{
	TableInfo()
	{
		::memset(this, 0, sizeof(*this));
		TableStatus=TABLEFREE;
	}
	BYTE   TableStatus;				//桌子状态
	BYTE   FreeChairNum;			//空椅子的数量
	BYTE   ChairStatus[CHAIR_NUM];	//所有椅子的状态
	DWORD  ChairUserID[CHAIR_NUM];	//所有椅子的用户

};

//挖坑游戏状态



//游戏状态
#define GS_WK_FREE					GS_FREE								//等待开始
#define GS_WK_SCORE					GS_PLAYING							//叫分状态
#define GS_WK_PLAYING				GS_PLAYING+1						//游戏进行

//////////////////////////////////////////////////////////////////////////
#define SUB_S_SEND_CARD				100									//发牌命令
#define SUB_S_LAND_SCORE			101									//叫分命令
#define SUB_S_GAME_START			102									//游戏开始
#define SUB_S_OUT_CARD				103									//用户出牌
#define SUB_S_PASS_CARD				104									//放弃出牌
#define SUB_S_GAME_END				105									//游戏结束

//游戏状态
struct CMD_S_StatusFree
{
	LONG							lBaseScore;							//基础积分
};

//游戏状态
struct CMD_S_StatusScore
{
	BYTE							bLandScore;							//地主分数
	LONG							lBaseScore;							//基础积分
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bScoreInfo[3];						//叫分信息
	BYTE							bCardData[17];						//手上扑克
};

//游戏状态
struct CMD_S_StatusPlay
{
	WORD							wLandUser;							//坑主玩家
	WORD							wBombTime;							//炸弹倍数
	LONG							lBaseScore;							//基础积分
	BYTE							bLandScore;							//地主分数
	WORD							wLastOutUser;						//出牌的人
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bBackCard[3];						//底牌扑克
	BYTE							bCardData[20];						//手上扑克
	BYTE							bCardCount[3];						//扑克数目
	BYTE							bTurnCardCount;						//基础出牌
	BYTE							bTurnCardData[20];					//出牌列表
};

//发送扑克
struct CMD_S_SendCard
{
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bCardData[17];						//扑克列表
};

//用户叫分
struct CMD_S_LandScore
{
	WORD							bLandUser;							//叫分玩家
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bLandScore;							//上次叫分
	BYTE							bCurrentScore;						//当前叫分
};

//游戏开始
struct CMD_S_GameStart
{
	WORD				 			wLandUser;							//地主玩家
	BYTE							bLandScore;							//地主分数
	WORD				 			wCurrentUser;						//当前玩家
	BYTE							bBackCard[3];						//底牌扑克
};

//用户出牌
struct CMD_S_OutCard
{
	BYTE							bCardCount;							//出牌数目
	WORD				 			wCurrentUser;						//当前玩家
	WORD							wOutCardUser;						//出牌玩家
	BYTE							bCardData[20];						//扑克列表
};

//放弃出牌
struct CMD_S_PassCard
{
	BYTE							bNewTurn;							//一轮开始
	WORD				 			wPassUser;							//放弃玩家
	WORD				 			wCurrentUser;						//当前玩家
};

//游戏结束
struct CMD_S_GameEnd
{
	LONG							lGameTax;							//游戏税收
	LONG							lGameScore[3];						//游戏积分
	BYTE							bCardCount[3];						//扑克数目
	BYTE							bCardData[54];						//扑克列表 
};

//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_LAND_SCORE			1									//用户叫分
#define SUB_C_OUT_CART				2									//用户出牌
#define SUB_C_PASS_CARD				3									//放弃出牌

//用户叫分
struct CMD_C_LandScore
{
	BYTE							bLandScore;							//地主分数
};

//出牌数据包
struct CMD_C_OutCard
{
	BYTE							bCardCount;							//出牌数目
	BYTE							bCardData[20];						//扑克列表
};
