
#ifndef CMD_LLK_HEAD_FILE
#define CMD_LLK_HEAD_FILE

//公共宏定义-----------------------------------------------------------------------
#define KIND_ID							1									//游戏 I D
#define GAME_PLAYER						4									//游戏人数
#define GAME_NAME						TEXT("工具箱")						//游戏名字
#define GAME_GENRE						(GAME_GENRE_GOLD|GAME_GENRE_MATCH)  //游戏类型

//-----------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////
//命令码定义

#define		SUB_C_MODIFY_LOGIN_PASSWORD		10
#define		SUB_C_MODIFY_BANK_PASSWORD		11
#define		SUB_C_MODIFY_NICKNAME			12
#define		SUB_C_BANK						13
#define		SUB_C_TRANSFER_MONEY			14
#define		SUB_C_QUERY_TRANSFER_LOG		15

struct CMS_Return
{
	BYTE cbErrorCode;
};

//修改密码
struct CMD_Modify_Login_Password
{
	TCHAR								szOLDPassword[PASS_LEN];			//旧密码
	TCHAR								szNEWPassword[PASS_LEN];			//新密码
};

//修改银行密码
struct CMD_Modify_Bank_Password
{
	TCHAR								szOLDPassword[PASS_LEN];			//旧银行密码
	TCHAR								szNEWPassword[PASS_LEN];			//新银行密码
};

//修改昵称
struct CMD_Modify_Nickname
{
	TCHAR								szNickname[NAME_LEN];			//新昵称
};

//修改昵称
struct CMD_Transfer_Money
{
	__int64								sfMoneyNumber;
	DWORD								dwUserID;						//对方的ID号
	TCHAR								szAccount[NAME_LEN];			//新昵称
};


#endif //CMD_LLK_HEAD_FILE