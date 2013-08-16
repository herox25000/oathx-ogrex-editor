#ifndef _____Platform_H
#define _____Platform_H

const TCHAR SZ_PLAZACLASS[]	=	TEXT("GamePlaza");				//广场类名
const TCHAR SZ_PLAZANAME[]	=	TEXT("YouLe");


#define CAPTION_SIZE						35							//标题大小

#define LESS_SCREEN_CY			738									//最小高度
#define LESS_SCREEN_CX			1024								//最小宽度
//#define CAPTION_SIZE			79									//标题大小

//圆角大小
#define ROUND_CX				5									//圆角宽度
#define ROUND_CY				5									//圆角高度

#define WM_SHOW_FRAMECLOSE		WM_USER + 101
#define WM_CLOSE_FRAME			WM_USER + 102
#define WM_SWITCH_ACCOUNT		WM_USER + 103

// 视图页面创建的个数
#define MAX_GICOL			3
#define MAX_GIROW			3
#define GTP_OFFSETX			0
#define GTP_OFFSETY			40
#define GTP_WITH			580
#define	GTP_HEIGHT			591

//按钮ID 对应相应page
#define IDC_BT_GAME							100							//游戏专区
#define IDC_BT_MATCH						101							//比赛专区
#define IDC_BT_PROPERTY						102							//道具商城
#define IDC_BT_PRIZE						103							//奖品中心
#define IDC_BT_RECHARGE						104							//充值中心

#define IDC_BT_USERSET						105							//用户信息

// 返回按钮ID
#define IDB_GPRETURN		45535

#endif