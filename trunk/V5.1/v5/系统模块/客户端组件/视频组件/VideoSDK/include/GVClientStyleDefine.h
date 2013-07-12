// GVClientStyleDefine.h: interface for the Client Interface.
//
//////////////////////////////////////////////////////////////////////

#if !defined(GV_CLIENTSTYLE_DEFINE__)
#define GV_CLIENTSTYLE_DEFINE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(push, 1)

/**
 *	��Ƶ���ڹ�������ť����
 */
#define GV_VFT_BTN_BTN_VIDEOCTRL	0x00000001L	///< ��Ƶ���ư�ť
#define GV_VFT_BTN_BTN_AUDIOCTRL	0x00000002L	///< ��Ƶ���ư�ť
#define GV_VFT_BTN_BTN_CLONEVIDEO	0x00000004L	///< ������Ƶ���ڰ�ť
#define GV_VFT_BTN_BTN_FORTUNE		0x00000008L	///< �Ƹ��˵���ť
#define GV_VFT_BTN_BTN_SNAPSHOT		0x00000010L	///< ���տ��ư�ť
#define GV_VFT_BTN_BTN_RECORDFILE	0x00000020L	///< ¼����ư�ť
#define GV_VFT_BTN_BTN_PLAYRECORD	0x00000040L	///< ����¼����ư�ť
#define GV_VFT_BTN_BTN_EXTEND		0x00000080L	///< ��չ���ư�ť���û������Զ���ð�ť����Ӧ�¼�����ť�����µ��¼�����ͨ����Ϣ֪ͨ�ϲ�Ӧ��


/**
 *	��Ƶ���幤������ʾģʽ
 */
typedef enum{
	GV_VFTDM_AUTOSHOW = 0,						///< �Զ�ģʽ�������ʱ��ʾ����������
	GV_VFTDM_STILLSHOW,							///< ��ֹģʽ��ʼ����ʾ��������
	GV_VFTDM_VIDEOHIDE,							///< ��Ƶ����ģʽ������Ƶ֮ǰʼ����ʾ����ֹģʽ��������Ƶ֮��Ϊ�Զ�ģʽ
	GV_VFTDM_STILLHIDE,							///< һֱ���أ�����ʾ
}GV_VFT_DISPMODE;

/**
 *	��Ƶ���幤������ť���뷽ʽ
 */
typedef enum{
	GV_VFTBA_LEFT = 0,							///< ������루Ĭ�ϣ�
	GV_VFTBA_RIGHT,								///< ���Ҷ���
}GV_VFT_BTNALIGN;

/**
 *	��Ƶ���幤�������ṹ�嶨��
 */
typedef struct  
{
	DWORD		cbSize;							///< �ṹ���С
	COLORREF	bkColor;						///< ������������ɫ
	DWORD		maxTransPercent;				///< ���������͸���ȣ�0-!00��Ĭ��Ϊ70��ֵԽС��������Խ͸����
	DWORD		animateDuration;				///< �������仯�������ص���ʾ��������ʾ�����أ�ʱ������λ���룬Ĭ��ֵ3000
	DWORD		dwBtnMark;						///< �ڹ���������ʾ��Щ��ť����GV_VFT_BTN_BTN_XXXX��϶���
	DWORD		dwBtnSpacePix;					///< ��ť֮��ļ�������ص㣬Ĭ��Ϊ5��ֵԽС����ť����Խ��
	GV_VFT_DISPMODE		vftDispMode;			///< ��Ƶ���幤������ʾģʽ
	GV_VFT_BTNALIGN		vftBtnAlign;			///< ��������ť����ģʽ
	BYTE		szExtendBtnTooltip[32];			///< ��������չ��ť��ʾ��Ϣ
	DWORD		dwEBtnTooltipSize;				///< ��������չ��ť��ʾ��Ϣ�ַ�������
}GV_VFT_STYLE,*LPGV_VFT_STYLE;


/**
 *	��Ƶ���ڱ߿�����
 */
typedef enum{
	GV_VF_STYLE_HIDEFRAME = 0,					///< �ޱ߿�
	GV_VF_STYLE_SMALLFRAME,						///< С�߿�
	GV_VF_STYLE_TOOLBAR							///< ������������ʾ�ı߿�
}GV_VFS;

/**
 *	��Ƶ����Ƥ����ʽ����
 */
typedef enum{
	GV_VF_SKIN_DEFAULT = 0,						///< Ĭ��Ƥ����ʽ
	GV_VF_SKIN_CRYSTALBLUE,						///< ˮ����Ƥ��
	GV_VF_SKIN_CLASSIC,							///< �ŵ�Ƥ��
	GV_VF_SKIN_CRYSTALGREEN,					///< ˮ����Ƥ��
	GV_VF_SKIN_MDMSTYLEDEFAULT,					///< �������Ĭ��Ƥ����ʽ
	GV_VF_SKIN_PEARLBLACK,						///< �����Ƥ��
	GV_VF_SKIN_MDMSTYLEYELLOW,					///< ��������ɫƤ����ʽ
	GV_VF_SKIN_MDMSTYLECLASSIC,					///< �������ŵ�Ƥ����ʽ
}GV_VF_SKIN;


/**
 *	��Ƶ������ṹ�嶨��
 */
typedef struct  
{
	DWORD		cbSize;							///< �ṹ��Ĵ�С
	COLORREF	bkColor;						///< ��Ƶ���屳����ɫ
	COLORREF	selfTitleColor;					///< �Լ��ı�����ɫ
	COLORREF	otherTitleColor;				///< �����˵ı�����ɫ
	GV_VFS		vfStyle;						///< �߿���ʾ���
	BOOL		bMoveWindow;					///< �Ƿ�����ƶ���Ƶ����
	BOOL		bShowTitle;						///< �Ƿ���ʾ���⣬ͨ��Ϊ�û���
	BOOL		bShowVolume;					///< �Ƿ���ʾ����
	GV_VF_SKIN	vfSkin;							///< ��Ƶ����Ƥ����ʽ��ע�������߿�������Ϊ��GV_VF_STYLE_SMALLFRAME ʱ��Ч��
}GV_VW_STYLE,*LPGV_VW_STYLE;




#pragma pack(pop)

#endif // !defined(GV_CLIENTSTYLE_DEFINE__)
