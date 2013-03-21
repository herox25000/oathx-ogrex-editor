#ifndef CMD_TIGER_HEAD_FILE
#define CMD_TIGER_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//公共宏定义

static void SuperRand()
{
	srand(::GetTickCount());

	LONG count=rand()%30;

	for ( int i=0; i<count; i++ )
	{
		rand();
	}
}

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

#define SOCKET_PACKAGE				2048				//网络字节长度
#define KIND_ID						103					//游戏 I D
#define GAME_PLAYER					100					//游戏人数
#define GAME_NAME					TEXT("疯狂赛车")	//游戏名字
#define GAME_GENRE					(GAME_GENRE_GOLD)	//游戏类型

#define BANK_CONDITION_MONEY		20000000
#define ANIMAL_ROLL_SPEED			50					//虎虎财运旋转速度(毫秒)

//玩家索引
#define ID_BIG_TIGER				1					//大虎索引
#define ID_SML_TIGER				2					//小虎索引
#define ID_BIG_DOG					3					//大狗索引
#define ID_SML_DOG					4					//小狗索引
#define ID_BIG_HORSE				5					//大马索引
#define ID_SML_HORSE				6					//小马索引
#define ID_BIG_SNAKE				7					//大蛇索引
#define ID_SML_SNAKE				8					//小蛇索引

#define ID_FIRST_ANIMAL				1					//第一个动物索引

#define MAX_ANIMAL_COUNT			8					//动物数目

static const BYTE s_Multiple[MAX_ANIMAL_COUNT]={39, 4, 29, 4, 19, 4, 9, 4};

static const BYTE s_arJettonArea[MAX_ANIMAL_COUNT]={ID_BIG_TIGER, ID_SML_TIGER, ID_BIG_DOG, ID_SML_DOG, ID_BIG_HORSE, ID_SML_HORSE, ID_BIG_SNAKE, ID_SML_SNAKE};

#define LIMIT_VALUE(x, min, max) {if ((x)<(min)) (x)=(min); if ((x)>(max)) (x)=(max);}

//记录信息
struct tagServerGameRecord
{
	BYTE							cbWinner;							//胜利玩家
	__int64							lBigTigerScore;						//买大虎总注
	__int64							lSmlTigerScore;						//买小虎总注
	__int64							lBigBogScore;						//买大狗总注
	__int64							lSmlBogScore;						//买大狗总注
	__int64							lBigHorseScore;						//买大马总注
	__int64							lSmlHorseScore;						//买小马总注
	__int64							lBigSnakeScore;						//买大蛇总注
	__int64							lSmlSnakeScore;						//买小蛇总注
};

//////////////////////////////////////////////////////////////////////////
//服务器命令结构

#define SUB_S_GAME_START			100									//游戏开始
#define SUB_S_PLACE_JETTON			101									//用户下注
#define SUB_S_GAME_END				102									//游戏结束
#define SUB_S_APPLY_BANKER			103									//申请庄家
#define SUB_S_CHANGE_BANKER			104									//切换庄家
#define SUB_S_CHANGE_USER_SCORE		105									//更新积分
#define SUB_S_SEND_RECORD			106									//游戏记录
#define SUB_S_PLACE_JETTON_FAIL		107									//下注失败
#define SUB_S_GAME_SCORE			108									//发送积分

//失败结构
struct CMD_S_PlaceJettonFail
{
	__int64							lJettonArea;						//下注区域
	__int64							lPlaceScore;						//当前下注
	__int64							lMaxLimitScore;						//限制大小
	__int64							lFinishPlaceScore;					//已下注额
};

//更新积分
struct CMD_S_ChangeUserScore
{
	WORD							wChairID;							//椅子号码
	__int64							lScore;								//玩家积分

	//庄家信息
	WORD							wCurrentBankerChairID;				//当前庄家
	BYTE							cbBankerTime;						//庄家局数
	__int64							lCurrentBankerScore;				//庄家分数
};

//申请庄家
struct CMD_S_ApplyBanker
{
	CHAR							szAccount[ 32 ];					//申请玩家
	__int64							lScore;								//玩家金币
	bool							bApplyBanker;						//申请标识
};

//切换庄家
struct CMD_S_ChangeBanker
{
	WORD							wChairID;							//椅子号码
	BYTE							cbBankerTime;						//庄家局数
	__int64							lBankerWinScore;					//庄家分数
	__int64							lBankerTreasure;					//庄家金币
};

//游戏状态
struct CMD_S_StatusFree
{
	//全局信息
	BYTE							cbTimeLeave;						//剩余时间
	__int64							lCellScore;							//最大单元下注
	//下注信息
	__int64							lBigTigerScore;						//买大虎总注
	__int64							lSmlTigerScore;						//买小虎总注
	__int64							lBigBogScore;						//买大狗总注
	__int64							lSmlBogScore;						//买大狗总注
	__int64							lBigHorseScore;						//买大马总注
	__int64							lSmlHorseScore;						//买小马总注
	__int64							lBigSnakeScore;						//买大蛇总注
	__int64							lSmlSnakeScore;						//买小蛇总注

	//我的下注
	__int64							lMeMaxScore;						//最大下注
	
	__int64							lMeBigTigerScore;					//我买大虎总注
	__int64							lMeSmlTigerScore;					//我买小虎总注
	__int64							lMeBigBogScore;						//我买大狗总注
	__int64							lMeSmlBogScore;						//我买大狗总注
	__int64							lMeBigHorseScore;					//我买大马总注
	__int64							lMeSmlHorseScore;					//我买小马总注
	__int64							lMeBigSnakeScore;					//我买大蛇总注
	__int64							lMeSmlSnakeScore;					//我买小蛇总注

	//庄家信息
	WORD							wCurrentBankerChairID;				//当前庄家
	BYTE							cbBankerTime;						//庄家局数
	__int64							lCurrentBankerScore;				//庄家分数
	__int64							lApplyBankerCondition;				//申请条件
	__int64							lBankerTreasure;					//庄家金币
};

//游戏状态
struct CMD_S_StatusPlay
{
	BYTE							cbTimeLeave;						//剩余时间
	__int64							lCellScore;							//最大单元下注
	//下注信息
	__int64							lBigTigerScore;						//买大老虎总注
	__int64							lSmlTigerScore;						//买小老虎总注
	__int64							lBigBogScore;						//买大狗总注
	__int64							lSmlBogScore;						//买大狗总注
	__int64							lBigHorseScore;						//买大马总注
	__int64							lSmlHorseScore;						//买小马总注
	__int64							lBigSnakeScore;						//买大蛇总注
	__int64							lSmlSnakeScore;						//买小蛇总注

	//我的下注
	__int64							lMeMaxScore;						//最大下注
	
	__int64							lMeBigTigerScore;					//我买大老虎总注
	__int64							lMeSmlTigerScore;					//我买小老虎总注
	__int64							lMeBigBogScore;						//我买大狗总注
	__int64							lMeSmlBogScore;						//我买大狗总注
	__int64							lMeBigHorseScore;					//我买大马总注
	__int64							lMeSmlHorseScore;					//我买小马总注
	__int64							lMeBigSnakeScore;					//我买大蛇总注
	__int64							lMeSmlSnakeScore;					//我买小蛇总注

	//扑克信息
 	BYTE							cbAnimalBox;				//桌面扑克

	//庄家信息
	WORD							wCurrentBankerChairID;				//当前庄家
	BYTE							cbBankerTime;						//庄家局数
	__int64							lCurrentBankerScore;				//庄家分数
	__int64							lApplyBankerCondition;				//申请条件
	__int64							lBankerTreasure;					//庄家金币
};

//游戏开始
struct CMD_S_GameStart
{
	BYTE							cbAnimalBox;
	BYTE							cbTimeLeave;						//剩余时间
	__int64							lApplyBankerCondition;				//申请条件

	//庄家信息
	WORD							wBankerChairID;						//庄家号码
	__int64							lBankerWinScore;					//庄家积分
	BYTE							cbBankerTime;						//做庄次数
};

//用户下注
struct CMD_S_PlaceJetton
{
	WORD							wChairID;							//用户位置
	BYTE							cbJettonArea;						//筹码区域
	__int64							lJettonScore;						//加注数目
};

//游戏结束
struct CMD_S_GameEnd
{
	//下局信息
	BYTE							cbTimeLeave;						//剩余时间
	__int64							lMeMaxScore;						//最大下注
	__int64							lCellScore;							//最大下注

	//成绩记录
	BYTE							cbWinner;							//胜利玩家
	__int64							lBankerTreasure;					//庄家金币

	__int64							lBankerTotalScore;					//庄家成绩
	__int64							lBankerWinScore;					//庄家成绩
	INT								nBankerTime;						//做庄次数
};

//游戏得分
struct CMD_S_GameScore
{
	//成绩记录
	BYTE							cbWinner;							//胜利玩家
	__int64							lMeGameScore;						//我的成绩
	__int64							lMeReturnScore;						//返还注额
	__int64							lBankerWinScore;						//庄家成绩

	//下注信息
	__int64							lDrawBigTigerScore;					//买大老虎总注
	__int64							lDrawSmlTigerScore;					//买小老虎总注
	__int64							lDrawBigBogScore;					//买大狗总注
	__int64							lDrawSmlBogScore;					//买大狗总注
	__int64							lDrawBigHorseScore;					//买大马总注
	__int64							lDrawSmlHorseScore;					//买小马总注
	__int64							lDrawBigSnakeScore;					//买大蛇总注
	__int64							lDrawSmlSnakeScore;					//买小蛇总注

	//我的下注
	__int64							lMeBigTigerScore;					//我买大老虎总注
	__int64							lMeSmlTigerScore;					//我买小老虎总注
	__int64							lMeBigBogScore;						//我买大狗总注
	__int64							lMeSmlBogScore;						//我买大狗总注
	__int64							lMeBigHorseScore;					//我买大马总注
	__int64							lMeSmlHorseScore;					//我买小马总注
	__int64							lMeBigSnakeScore;					//我买大蛇总注
	__int64							lMeSmlSnakeScore;					//我买小蛇总注
};

//////////////////////////////////////////////////////////////////////////
//客户端命令结构

#define SUB_C_PLACE_JETTON			1									//用户下注
#define SUB_C_APPLY_BANKER			2									//申请庄家

//用户下注
struct CMD_C_PlaceJetton
{
	BYTE							cbJettonArea;						//筹码区域
	__int64							lJettonScore;						//加注数目
};

//申请庄家
struct CMD_C_ApplyBanker
{
	bool							bApplyBanker;						//申请标识
};

//////////////////////////////////////////////////////////////////////////

#endif //CMD_TIGER_HEAD_FILE