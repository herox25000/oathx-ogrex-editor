#ifndef _____Platform_H
#define _____Platform_H

const TCHAR SZ_PLAZACLASS[]	=	TEXT("V5GamePlaza");				//广场类名
const TCHAR SZ_PLAZANAME[]	=	TEXT("v5");


#define CAPTION_SIZE						35							//标题大小

#define LESS_SCREEN_CY			738									//最小高度
#define LESS_SCREEN_CX			1024								//最小宽度
//#define CAPTION_SIZE			79									//标题大小

//圆角大小
#define ROUND_CX				5									//圆角宽度
#define ROUND_CY				5									//圆角高度

#define WM_SHOW_LOBBYSET		WM_USER + 100
#define WM_SHOW_FRAMECLOSE		WM_USER + 101
#define WM_CLOSE_FRAME			WM_USER + 102
#define WM_SWITCH_ACCOUNT		WM_USER + 103

// 视图页面创建的个数
#define MAX_GICOL			3
#define MAX_GIROW			3
#define GTP_OFFSETX			0
#define GTP_OFFSETY			40
#define GTP_WITH			540
#define	GTP_HEIGHT			520

// 返回按钮ID
#define IDB_GPRETURN		45535

#endif