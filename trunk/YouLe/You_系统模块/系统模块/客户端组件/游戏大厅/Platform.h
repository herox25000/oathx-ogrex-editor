#ifndef _____Platform_H
#define _____Platform_H

const TCHAR SZ_PLAZACLASS[]	=	TEXT("V5GamePlaza");				//�㳡����
const TCHAR SZ_PLAZANAME[]	=	TEXT("v5");


#define LESS_SCREEN_CY			738									//��С�߶�
#define LESS_SCREEN_CX			1024								//��С���
//#define CAPTION_SIZE			79									//�����С

//Բ�Ǵ�С
#define ROUND_CX				5									//Բ�ǿ��
#define ROUND_CY				5									//Բ�Ǹ߶�

#define WM_SHOW_LOBBYSET		WM_USER + 100
#define WM_SHOW_FRAMECLOSE		WM_USER + 101
#define WM_CLOSE_FRAME			WM_USER + 102
#define WM_SWITCH_ACCOUNT		WM_USER + 103

// ��ͼҳ�洴���ĸ���
#define MAX_GICOL			3
#define MAX_GIROW			3
#define GTP_OFFSETX			0
#define GTP_OFFSETY			40
#define GTP_WITH			540
#define	GTP_HEIGHT			520

// ���ذ�ťID
#define IDB_GPRETURN		45535

#endif