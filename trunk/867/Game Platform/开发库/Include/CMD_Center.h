#ifndef CMD_CENTER_HEAD_FILE
#define CMD_CENTER_HEAD_FILE


// 主ID
#define MDM_CS_SERVER_LIST				1								//游戏列表
#define MDM_CS_SERVER_MANAGER			2								//房间管理
#define MDM_CS_USER_MANAGER				3								//玩家管理
//游戏列表命令码（主ID MDM_CS_SERVER_LIST）
#define SUB_CS_GET_SERVER_LIST			1								//请求列表
#define SUB_CS_LIST_INFO				100								//列表信息
#define SUB_CS_LIST_TYPE				101								//类型列表
#define SUB_CS_LIST_KIND				102								//种类列表
#define SUB_CS_LIST_STATION				103								//站点列表
#define SUB_CS_LIST_SERVER				104								//房间列表
#define SUB_CS_LIST_FINISH				105								//列表完成
//房间管理命令码 （主ID MDM_CS_SERVER_MANAGER）
#define SUB_CS_REG_GAME_SERVER			1								//注册房间
#define SUB_CS_UNREG_GAME_SERVER		2								//注销房间
#define SUB_CS_SERVER_ONLINE_COUNT		3								//房间人数
//玩家管理命令码（主ID MDM_CS_USER_MANAGER）
#define SUB_CS_FLASHUSERINFO			1								//刷新用户信息


//列表信息
struct CMD_CS_ListInfo
{
	DWORD								dwTypeCount;					//类型数目
	DWORD								dwKindCount;					//种类数目
	DWORD								dwServerCount;					//房间数目
	DWORD								dwStationCount;					//站点数目
};


//注册房间
struct CMD_CS_RegGameServer
{
	tagGameServer						GameServer;						//房间信息
};

//注销房间
struct CMD_CS_UnRegGameServer
{
	WORD								wKindID;						//名称号码
	WORD								wServerID;						//房间号码
};

//房间人数
struct CMD_CS_ServerOnLineCount
{
	WORD								wKindID;						//名称号码
	WORD								wServerID;						//房间号码
	DWORD								dwOnLineCount;					//在线人数
};

//刷新用户信息
struct CMD_CS_FLASHUSERINFO
{
	LONG								lUserID;						//要刷新的用户
};


#endif

//-----------------------------------------------
//					the end
//-----------------------------------------------
