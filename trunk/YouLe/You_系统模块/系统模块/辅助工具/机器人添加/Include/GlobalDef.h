#ifndef GLOBAL_DEF_HEAD_FILE
#define GLOBAL_DEF_HEAD_FILE

#pragma once

/////////////////////////////////////////////////////////////////////////////////////////
//常量定义

const TCHAR	szProductName[]=TEXT("网狐游戏");							//产品名字
const TCHAR szSystemRegKey[]=TEXT("WHSZARGame");							//注册主键
const TCHAR szStationPage[]=TEXT("www.fox2046.com");						//游戏主页

/////////////////////////////////////////////////////////////////////////////////////////
//游戏标识

//通用游戏
#define ID_PLAZA						0									//大厅
#define ID_SHOWHAND						1									//梭哈
#define ID_CHINA_CHESS					2									//象棋
#define ID_GOBANG						3									//五子棋
#define ID_WEIQI						4									//围棋
#define ID_TRENCH						5									//挖坑
#define ID_CHESS						6									//国际象棋
#define ID_LAND							7									//斗地主
#define ID_SPARROW						8									//麻将
#define ID_RUN_FAST						9									//跑得快
#define ID_HOE							36									//锄大地
#define ID_HK_FIVE_CARD					18									//港式五张

//地方游戏
#define ID_LIANG_FU_TOU					10									//两副头
#define ID_PAO_HU_ZI					11									//跑胡子
#define ID_LIU_HU_QIANG					13									//六胡抢

//测试游戏
#define ID_BACK_JACK					30									//黑杰克
#define ID_DOUSHOUQI					31									//斗兽棋
#define ID_UPGRADE						32									//拖拉机
#define ID_FOURENSIGN					33									//四国军棋
#define ID_THREELEAF					34									//三张牌
#define ID_BILLIARDS					35									//台球
#define ID_UNCOVERPIG					37									//拱猪

/////////////////////////////////////////////////////////////////////////////////////////
//宏定义

#define MAX_CHAIR						8									//最大游戏者
#define MAX_CHAT_LEN					512									//聊天长度
#define INVALID_TABLE					((WORD)(-1))						//无效桌子号
#define INVALID_CHAIR					((WORD)(-1))						//无效椅子号
#define MAIN_DLG_CLASSNAME				TEXT("WHSZARGamePlaza")				//窗口注册名

//端口定义
#define PORT_LOGON_SERVER				9000								//登陆服务器
#define PORT_CENTER_SERVER				9010								//中心服务器

//网络数据定义
#define SOCKET_VER						68									//数据包版本
#define SOCKET_PACKAGE					2046								//最大网络包
#define SOCKET_BUFFER					(sizeof(CMD_Head)+SOCKET_PACKAGE+2*sizeof(DWORD))

/////////////////////////////////////////////////////////////////////////////////////////

//数据包结构信息
struct CMD_Info
{
	WORD								wDataSize;							//数据大小
	BYTE								cbCheckCode;						//效验字段
	BYTE								cbMessageVer;						//版本标识
};

//数据包命令信息
struct CMD_Command
{
	WORD								wMainCmdID;							//主命令码
	WORD								wSubCmdID;							//子命令码
};

//数据包传递包头
struct CMD_Head
{
	CMD_Info							CmdInfo;							//基础结构
	CMD_Command							CommandInfo;						//命令信息
};

//网络数据包缓冲
struct CMD_Buffer
{
	CMD_Head							Head;								//数据包头
	BYTE								cbBuffer[SOCKET_PACKAGE];			//数据缓冲
};

//内核命令码
#define MDM_KN_COMMAND					0									//内核命令
#define SUB_KN_DETECT_SOCKET			1									//检测命令

//检测结构信息
struct CMD_KN_DetectSocket
{
	DWORD								dwSendTickCount;					//发送时间
	DWORD								dwRecvTickCount;					//接收时间
};

/////////////////////////////////////////////////////////////////////////////////////////

//IPC 数据定义
#define IPC_VER							0x0001								//IPC 版本
#define IPC_IDENTIFIER					0x0001								//标识号码
#define IPC_PACKAGE						4096								//最大 IPC 包
#define IPC_BUFFER						(sizeof(IPC_Head)+IPC_PACKAGE)		//缓冲长度

//IPC 数据包头
struct IPC_Head
{
	WORD								wVersion;							//IPC 版本
	WORD								wDataSize;							//数据大小
	WORD								wMainCmdID;							//主命令码
	WORD								wSubCmdID;							//子命令码
};

//IPC 缓冲结构
struct IPC_Buffer
{
	IPC_Head							Head;								//数据包头
	BYTE								cbBuffer[IPC_PACKAGE];				//数据缓冲
};

//////////////////////////////////////////////////////////////////////////

//长度宏定义
#define TYPE_LEN						32									//种类长度
#define KIND_LEN						32									//类型长度
#define STATION_LEN						32									//站点长度
#define SERVER_LEN						32									//房间长度
#define MODULE_LEN						32									//进程长度

//游戏类型
#define GAME_GENRE_SCORE				0x0001								//点值类型
#define GAME_GENRE_GOLD					0x0002								//金币类型
#define GAME_GENRE_MATCH				0x0004								//比赛类型
#define GAME_GENRE_EDUCATE				0x0008								//训练类型

//游戏类型结构
struct tagGameType
{
	WORD								wSortID;							//排序号码
	WORD								wTypeID;							//种类号码
	TCHAR								szTypeName[TYPE_LEN];				//种类名字
};

//游戏名称结构
struct tagGameKind
{
	WORD								wSortID;							//排序号码
	WORD								wTypeID;							//类型号码
	WORD								wKindID;							//名称号码
	DWORD								dwMaxVersion;						//最新版本
	DWORD								dwOnLineCount;						//在线数目
	TCHAR								szKindName[KIND_LEN];				//游戏名字
	TCHAR								szProcessName[MODULE_LEN];			//进程名字
};

//游戏进程结构
struct tagGameProcess
{
	WORD								wSortID;							//排序号码
	WORD								wTypeID;							//类型号码
	WORD								wKindID;							//名称号码
	WORD								wServerPort;						//房间端口
	DWORD								dwServerAddr;						//房间地址
	DWORD								dwMaxVersion;						//最新版本
	DWORD								dwOnLineCount;						//在线数目
	TCHAR								szKindName[KIND_LEN];				//游戏名字
	TCHAR								szProcessName[MODULE_LEN];			//进程名字
};

//游戏站点结构
struct tagGameStation
{
	WORD								wSortID;							//排序号码
	WORD								wKindID;							//名称号码
	WORD								wJoinID;							//挂接号码
	WORD								wStationID;							//站点号码
	TCHAR								szStationName[STATION_LEN];			//站点名称
};

//游戏房间列表结构
struct tagGameServer
{
	WORD								wSortID;							//排序号码
	WORD								wKindID;							//名称号码
	WORD								wServerID;							//房间号码
	WORD								wStationID;							//站点号码
	WORD								wServerPort;						//房间端口
	DWORD								dwServerAddr;						//房间地址
	DWORD								dwOnLineCount;						//在线人数
	TCHAR								szServerName[SERVER_LEN];			//房间名称
};

//////////////////////////////////////////////////////////////////////////

//用户状态定义
#define US_NULL							0x00								//没有状态
#define US_FREE							0x01								//站立状态
#define US_SIT							0x02								//坐下状态
#define US_READY						0x03								//同意状态
#define US_LOOKON						0x04								//旁观状态
#define US_PLAY							0x05								//游戏状态
#define US_OFFLINE						0x06								//断线状态

//长度宏定义
#define NAME_LEN						32									//名字长度
#define PASS_LEN						33									//密码长度
#define GROUP_LEN						32									//社团长度

//用户积分信息
struct tagUserScore
{
	LONG								lGold;								//用户金币
	LONG								lScore;								//用户分数
	LONG								lWinCount;							//胜利盘数
	LONG								lLostCount;							//失败盘数
	LONG								lDrawCount;							//和局盘数
	LONG								lFleeCount;							//断线数目
	LONG								lExperience;						//用户经验
};

//用户状态信息
struct tagUserStatus
{
	WORD								wTableID;							//桌子号码
	WORD								wChairID;							//椅子位置
	WORD								wNetDelay;							//网络延时
	BYTE								cbUserStatus;						//用户状态
};

//用户基本信息结构
struct tagUserInfoHead
{
	//用户属性
	WORD								wFaceID;							//头像索引
	BYTE								cbGender;							//用户性别
	BYTE								cbMember;							//会员等级
	DWORD								dwUserID;							//用户 I D
	DWORD								dwGroupID;							//社团索引
	DWORD								dwUserRight;						//用户等级
	DWORD								dwMasterRight;						//管理权限

	//用户状态
	WORD								wTableID;							//桌子号码
	WORD								wChairID;							//椅子位置
	WORD								wNetDelay;							//网络延时
	BYTE								cbUserStatus;						//用户状态

	//用户积分
	tagUserScore						UserScoreInfo;						//积分信息
};

//用户信息结构
struct tagUserData
{
	//用户属性
	WORD								wFaceID;							//头像索引
	BYTE								cbGender;							//用户性别
	BYTE								cbMember;							//会员等级
	DWORD								dwUserID;							//用户 I D
	DWORD								dwGroupID;							//社团索引
	DWORD								dwUserRight;						//用户等级
	DWORD								dwMasterRight;						//管理权限
	TCHAR								szName[NAME_LEN];					//用户名字
	TCHAR								szGroupName[GROUP_LEN];				//社团名字

	//用户积分
	LONG								lGold;								//用户金币
	LONG								lScore;								//用户分数
	LONG								lWinCount;							//胜利盘数
	LONG								lLostCount;							//失败盘数
	LONG								lDrawCount;							//和局盘数
	LONG								lFleeCount;							//断线数目
	LONG								lExperience;						//用户经验

	//用户状态
	WORD								wTableID;							//桌子号码
	WORD								wChairID;							//椅子位置
	WORD								wNetDelay;							//网络延时
	BYTE								cbUserStatus;						//用户状态

	//其他信息
	BYTE								cbCompanion;						//用户关系
};

//////////////////////////////////////////////////////////////////////////

//机器序列号结构
struct tagClientSerial
{
	DWORD								dwComputerID[3];					//机器序列
};

//配置缓冲结构
struct tagOptionBuffer
{
	BYTE								cbBufferLen;						//数据长度
	BYTE								cbOptionBuf[32];					//设置缓冲
};

/////////////////////////////////////////////////////////////////////////////////////////

#endif