#ifndef _____Platform_H
#define _____Platform_H

const TCHAR SZ_PLAZACLASS[]	=	TEXT("GamePlaza");				//�㳡����
const TCHAR SZ_PLAZANAME[]	=	TEXT("YouLe");


#define CAPTION_SIZE						35							//�����С

#define LESS_SCREEN_CY			738									//��С�߶�
#define LESS_SCREEN_CX			1024								//��С���
//#define CAPTION_SIZE			79									//�����С

//Բ�Ǵ�С
#define ROUND_CX				5									//Բ�ǿ��
#define ROUND_CY				5									//Բ�Ǹ߶�

#define WM_SHOW_FRAMECLOSE		WM_USER + 101
#define WM_CLOSE_FRAME			WM_USER + 102
#define WM_SWITCH_ACCOUNT		WM_USER + 103

// ��ͼҳ�洴���ĸ���
#define MAX_GICOL			3
#define MAX_GIROW			3
#define GTP_OFFSETX			0
#define GTP_OFFSETY			40
#define GTP_WITH			580
#define	GTP_HEIGHT			591

//��ťID ��Ӧ��Ӧpage
#define IDC_BT_GAME							100							//��Ϸר��
#define IDC_BT_MATCH						101							//����ר��
#define IDC_BT_PROPERTY						102							//�����̳�
#define IDC_BT_PRIZE						103							//��Ʒ����
#define IDC_BT_RECHARGE						104							//��ֵ����

#define IDC_BT_USERSET						105							//�û���Ϣ

// ���ذ�ťID
#define IDB_GPRETURN		45535

#endif