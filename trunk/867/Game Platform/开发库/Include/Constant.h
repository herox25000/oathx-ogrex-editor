#ifndef CONSTANT_HEAD_FILE
#define CONSTANT_HEAD_FILE

/////////////////////////////////////////////////////////////////////////////////////////
//常量定义

const TCHAR	szProductName[]		=TEXT("541棋牌游戏");								//产品名字
const TCHAR szStationPage[]		=TEXT("www.game541.com");					//游戏主页
const TCHAR szCookieUrl[]		=TEXT("www.game541.com");	

//注册表均在 HKEY_CURRENT_USER 主键下
//服务器使用的注册表地址
const TCHAR szSystemRegKey[]	=TEXT("MGLGame541");								
//客户端使用的注册表地址
#define REG_OPTION_LOGON		TEXT("OptionLogon")
#define REG_USER_INFO			TEXT("Software\\MGLGame541\\GamePlaza\\UserInfo")
#define REG_LOGON_SERVER		TEXT("Software\\MGLGame541\\GamePlaza\\LogonServer")

/////////////////////////////////////////////////////////////////////////////////////////
//常量定义
#define MAIN_DLG_CLASSNAME		TEXT("MGLGame541Plaza")				//窗口类名

//////////////////////////////////////////////////////////////////////////

#endif
