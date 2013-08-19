#ifndef _____Platform_H
#define _____Platform_H

const TCHAR SZ_PLAZACLASS[]	=	TEXT("GamePlaza");						//�㳡����
const TCHAR SZ_PLAZANAME[]	=	TEXT("YouLe");


#define CAPTION_SIZE						35							//�����С

#define LESS_SCREEN_CY						738							//��С�߶�
#define LESS_SCREEN_CX						1024						//��С���
//#define CAPTION_SIZE						79							//�����С

//Բ�Ǵ�С
#define ROUND_CX							5							//Բ�ǿ��
#define ROUND_CY							5							//Բ�Ǹ߶�
//��Ӱ����
#define SHADOW_CX							1							//��Ӱ���
#define SHADOW_CY							1							//��Ӱ�߶�

// ��ͼҳ�洴���ĸ���
#define MAX_GICOL							3
#define MAX_GIROW							3

//GameItemƫ����
#define GTP_OFFSETX							5
#define GTP_OFFSETY							45

//��ťID ��Ӧ��Ӧpage
#define IDC_BT_GAME							100							//��Ϸר��
#define IDC_BT_MATCH						101							//����ר��
#define IDC_BT_PROPERTY						102							//�����̳�
#define IDC_BT_PRIZE						103							//��Ʒ����
#define IDC_BT_RECHARGE						104							//��ֵ����

//�û�����page��ť
#define IDC_BT_USERSET						105							//�û���Ϣ
#define IDC_BT_REFLASH						106							//��Ϣˢ��
#define IDC_BT_USERBAG						107							//��ɫ����
#define IDC_BT_SQUARE						108							
#define IDC_BT_TILL							109
#define IDC_BT_IM							110

//�û����ð�ť
#define IDC_BT_MODIFY_USER					300							//�����û�
#define IDC_BT_MODIFY_INFO					301							//��������
#define IDC_BT_MODIFY_PASSWORD				302							//��������

#define IDC_BT_MD_USERINFO_OK				303							//�޸��û�����ȷ��
#define IDC_BT_MD_USERINFO_CANCEL			304							//ȡ���û������޸�

#define IDC_BT_MD_PASSWORD_OK				305							//ȷ���޸��û�����
#define IDC_BT_MD_PASSWORD_CANCEL			306							//ȡ���޸��û�����

// ���ذ�ťID
#define IDB_GPRETURN						45535

//////////////////////////////////////////////////////////////////////////
//����UIλ��
#define PGP_OFFSETX							222
#define PGP_OFFSETY							147
#define PGP_WITH							580
#define	PGP_HEIGHT							591

//�û�UIλ��
#define PUP_OFFSETX							0
#define PUP_OFFSETY							147
#define PUP_WITH							222
#define PUP_HEIGHT							591


//////////////////////////////////////////////////////////////////////////
//UIָ��
#define WM_SHOW_USERSET						WM_USER + 1					//���û�����
#define WM_SHOW_FRAMECLOSE					WM_USER + 101
#define WM_CLOSE_FRAME						WM_USER + 102
#define WM_SWITCH_ACCOUNT					WM_USER + 103
#endif