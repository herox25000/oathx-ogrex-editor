#ifndef CMD_PLAZA_HEAD_FILE
#define CMD_PLAZA_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//广场版本
#define VER_PLAZA_LOW					1								//广场版本
#define VER_PLAZA_HIGH					3								//广场版本
#define VER_PLAZA_FRAME					MAKELONG(VER_PLAZA_LOW,VER_PLAZA_HIGH)

//////////////////////////////////////////////////////////////////////////
//登录错误标识

#define ERC_GP_LOGON_SUCCESS			0								//登陆成功
#define ERC_GP_ACCOUNTS_NOT_EXIST		1								//帐号不存在
#define ERC_GP_LONG_NULLITY				2								//禁止登录
#define ERC_GP_PASSWORD_ERCOR			3								//密码错误

//////////////////////////////////////////////////////////////////////////
//登录命令码

#define MDM_GP_LOGON					1								//广场登录

#define SUB_GP_LOGON_ACCOUNTS			1								//帐号登录
#define SUB_GP_LOGON_USERID				2								//I D 登录
#define SUB_GP_REGISTER_ACCOUNTS		3								//注册帐号
#define SUB_GP_UPLOAD_CUSTOM_FACE		4								//定义头像

#define SUB_GP_LOGON_SUCCESS			100								//登陆成功
#define SUB_GP_LOGON_ERROR				101								//登陆失败
#define SUB_GP_LOGON_FINISH				102								//登陆完成

//帐号登录
struct CMD_GP_LogonByAccounts
{
	DWORD								dwPlazaVersion;					//广场版本
	TCHAR								szAccounts[NAME_LEN];			//登录帐号
	TCHAR								szPassWord[PASS_LEN];			//登录密码
};

//I D 登录
struct CMD_GP_LogonByUserID
{
	DWORD								dwPlazaVersion;					//广场版本
	DWORD								dwUserID;						//用户 I D
	TCHAR								szPassWord[PASS_LEN];			//登录密码
};

//注册帐号
struct CMD_GP_RegisterAccounts
{
	WORD								wFaceID;						//头像标识
	BYTE								cbGender;						//用户性别
	DWORD								dwPlazaVersion;					//广场版本
	TCHAR								szSpreader[NAME_LEN];			//推广人名
	TCHAR								szAccounts[NAME_LEN];			//登录帐号
	TCHAR								szPassWord[PASS_LEN];			//登录密码
	TCHAR								szBankPassWord[PASS_LEN];		//银行密码		
	TCHAR								szSFZ[PASS_LEN];		//身份证
	TCHAR								szPhone[PASS_LEN];		//电话	
};

//登陆成功
struct CMD_GP_LogonSuccess
{
	WORD								wFaceID;						//头像索引
	BYTE								cbGender;						//用户性别
	BYTE								cbMember;						//会员等级
	BYTE								cbMoorMachine;					//账号是否锁定
	DWORD								dwUserID;						//用户 I D
	DWORD								dwGameID;						//游戏 I D
	DWORD								dwExperience;					//用户经验
	
	//扩展信息
	DWORD								dwCustomFaceVer;				//头像版本
};

//登陆失败
struct CMD_GP_LogonError
{
	LONG								lErrorCode;						//错误代码
	TCHAR								szErrorDescribe[128];			//错误消息
};

//////////////////////////////////////////////////////////////////////////
//游戏列表命令码

#define MDM_GP_SERVER_LIST				2								//列表信息

#define SUB_GP_LIST_TYPE				100								//类型列表
#define SUB_GP_LIST_KIND				101								//种类列表
#define SUB_GP_LIST_STATION				102								//站点列表
#define SUB_GP_LIST_SERVER				103								//房间列表
#define SUB_GP_LIST_FINISH				104								//发送完成
#define SUB_GP_LIST_CONFIG				105								//列表配置

//列表配置
struct CMD_GP_ListConfig
{
	BYTE								bShowOnLineCount;				//显示人数
};

//////////////////////////////////////////////////////////////////////////
//系统命令码
#define MDM_GP_SYSTEM					3								//系统命令
#define SUB_GP_VERSION					100								//版本通知
#define SUB_GP_MESSAGE					101								//系统消息

//消息类型
#define SMT_INFO					0x0001								//信息消息
#define SMT_EJECT					0x0002								//弹出消息
#define SMT_GLOBAL					0x0004								//全局消息
#define SMT_CLOSE_ROOM				0x1000								//关闭房间
#define SMT_INTERMIT_LINE			0x4000								//中断连接
//消息数据包
struct CMD_GP_Message
{
	WORD							wMessageType;						//消息类型
	WORD							wMessageLength;						//消息长度
	TCHAR							szContent[1024];					//消息内容
};

//版本通知
struct CMD_GP_Version
{
	BYTE								bNewVersion;					//更新版本
	BYTE								bAllowConnect;					//允许连接
};

//////////////////////////////////////////////////////////////////////////

#define MDM_GP_USER						4								//用户信息

#define SUB_GP_USER_UPLOAD_FACE			100								//上传头像
#define SUB_GP_USER_DOWNLOAD_FACE		101								//下载头像
#define SUB_GP_UPLOAD_FACE_RESULT		102								//上传结果
#define SUB_GP_DELETE_FACE_RESULT		103								//删除结果
#define SUB_GP_CUSTOM_FACE_DELETE		104								//删除头像
#define SUB_GP_MODIFY_INDIVIDUAL		105								//修改个人资料
#define SUB_GP_MODIFY_INDIVIDUAL_RESULT	106								//修改结果
#define SUB_GP_LOCKCOMPUTER				107								//锁定本机
#define SUB_GP_LOCKCOMPUTER_RESULT		108								//锁定本机
#define SUB_GP_TMODIFYUNDERWRITE		109								//修改个性签名
#define SUB_GP_TMODIFYUNDERWRITE_RESULT			110						//修改签名返回
#define SUB_GP_MODIFYPASSWORD			111								//修改密码	
#define SUB_GP_MODIFYPASSWORD_RESULT	112								//修改密码返回
#define SUB_GP_QUERYUSERINDIVIDUAL		113								//查询用户信息

//修改用户资料时候携带的数据
enum DTP
{
	DTP_GP_UI_ACCOUNTS		=1,		//用户名
	DTP_GP_UI_USER_NOTE		=2,		//用户说明
	DTP_GP_UI_UNDER_WRITE	=3,		//个性签名
	DTP_GP_UI_QQ			=4,		//Q Q 号码
	DTP_GP_UI_EMAIL			=5,		//电子邮件
	DTP_GP_UI_SFZ			=6,		//身份证
	DTP_GP_UI_MOBILE_PHONE	=7,		//移动电话
	DTP_GP_UI_COMPELLATION	=8,		//真实名字
	DTP_GP_UI_DWELLING_PLACE=9,		//联系地址
};

//定义头像
struct CMD_GP_UploadCustomFace
{
	DWORD								dwUserID;						//玩家 ID
	WORD								wCurrentSize;					//当前大小
	bool								bLastPacket;					//最后标识
	bool								bFirstPacket;					//第一个标识
	BYTE								bFaceData[2048];				//头像数据
};

//下载成功
struct CMD_GP_DownloadFaceSuccess
{
	DWORD							dwToltalSize;						//总共大小
	DWORD							dwCurrentSize;						//当前大小
	DWORD							dwUserID;							//玩家 ID
	BYTE							bFaceData[2048];					//头像数据
};

//下载头像
struct CMD_GP_DownloadFace
{
	DWORD							dwUserID;							//玩家 ID
};

//上传结果
struct CMD_GP_UploadFaceResult
{
	TCHAR							szDescribeMsg[128];					//描述信息
	DWORD							dwFaceVer;							//头像版本
	bool							bOperateSuccess;					//成功标识
};

//删除结果
struct CMD_GP_DeleteFaceResult
{
	TCHAR							szDescribeMsg[128];					//描述信息
	DWORD							dwFaceVer;							//头像版本
	bool							bOperateSuccess;					//成功标识
};

//删除消息
struct CMD_GP_CustomFaceDelete
{
	DWORD							dwUserID;							//玩家 ID
	DWORD							dwFaceVer;							//头像版本
};

//锁定本机
struct CMD_GP_LockComputer
{
	LONG							lUserID;
	TCHAR							szPassWord[PASS_LEN];			//登录密码
};

//锁定本机返回
struct CMD_GP_LockComputerResult
{
	BYTE								cbMoorMachine;					//账号是否锁定							
	TCHAR								szRetDescribe[128];				//返回消息
};

//修改签名
struct CMD_GP_ModifyUnderWrite
{
	DWORD							dwUserID;							//用户 I D
	TCHAR							szUnderWrite[UNDER_WRITE_LEN];		//个性签名
};

//修改签名返回
struct CMD_GP_ModifyUnderWrite_Ret
{
	LONG							lResultCode;						//返回状态，0、成功，!0、失败
	TCHAR							szDescribeString[128];				//描述消息
};

//修改密码
struct CMD_GP_ModifyPassword
{
	LONG							lUserID;
	LONG							lType;								//修改的类型，1、登陆密码，2、银行密码
	TCHAR							szOLDPassword[PASS_LEN];			//旧密码
	TCHAR							szNEWPassword[PASS_LEN];			//新密码
};

//修改密码返回
struct CMD_GP_ModifyPassword_Ret
{
	LONG							lResultCode;						//返回状态，0、成功，!0、失败
	TCHAR							szDescribeString[128];				//描述消息
};

//查询信息
struct CMD_GP_QueryIndividual
{
	DWORD							dwUserID;							//用户 I D
};

//修改个人资料
struct CMD_GP_ModifyIndividual
{
	DWORD							dwUserID;						//用户 I D
	BYTE							cbGender;						//用户性别
	int								cbFaceID;						//头像ID
	TCHAR							szPassword[PASS_LEN];			//用户密码
};

//修改个人资料返回结果
struct CMD_GP_ModifyIndividual_Ret
{
	LONG							lResultCode;						//返回状态，0、成功，!0、失败
	TCHAR							szDescribeString[128];				//描述消息
};

//////////////////////////////////////////////////////////////////////////

#endif