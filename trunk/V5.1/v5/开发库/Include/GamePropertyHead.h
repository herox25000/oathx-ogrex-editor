#ifndef GAME_PROPERTY_HEAD_HEAD_FILE
#define GAME_PROPERTY_HEAD_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//�����ļ�

//MFC �ļ�
#include <Afxmt.h>
#include <AtlBase.h>
#include <AfxTempl.h>

//ƽ̨�ļ�
#include "Platform.h"

//����ļ�
#include "ServiceCoreHead.h"

//����ļ�
#include "WHImageHead.h"
#include "UserServiceHead.h"
#include "SkinControlHead.h"
#include "ShareControlHead.h"

//////////////////////////////////////////////////////////////////////////////////
//��������

//��������
#ifndef GAME_PROPERTY_CLASS
	#ifdef  GAME_PROPERTY_DLL
		#define GAME_PROPERTY_CLASS _declspec(dllexport)
	#else
		#define GAME_PROPERTY_CLASS _declspec(dllimport)
	#endif
#endif

//ģ�鶨��
#ifndef _DEBUG
	#define GAME_PROPERTY_DLL_NAME	TEXT("GameProperty.dll")			//�������
#else
	#define GAME_PROPERTY_DLL_NAME	TEXT("GamePropertyD.dll")			//�������
#endif

//////////////////////////////////////////////////////////////////////////////////

//���ߴ�С
#define PROPERTY_IMAGE_CX			30									//ͼ���С
#define PROPERTY_IMAGE_CY			30									//ͼ���С

//ͼ���С
#define PROPERTY_SYMBOL_CX			120									//ͼ���С
#define PROPERTY_SYMBOL_CY			120									//ͼ���С

//�����
#define CMD_CLOSE_WND   			200                                 //�ر�����
#define CMD_USER_CHANGE				201                                 //ѡ���û�

//////////////////////////////////////////////////////////////////////////////////
//�ṹ����

//����ͼƬ
struct tagPropertyImage
{
	LPCTSTR							pszFlash;							//����·��
	LPCTSTR							pszImageID;							//����ͼƬ
	LPCTSTR							pszSymbolID;						//��־ͼƬ
	HINSTANCE						hResInstance;						//��Դ���
};

//����ͼƬ
struct tagPropertyResource
{
	//��Դ����
	UINT							uImageL;							//ͼƬ��ʶ
	UINT							uImageM;							//ͼƬ��ʶ
	UINT							uImageR;							//ͼƬ��ʶ
	UINT							uImageItem;							//ͼƬ��ʶ
	HINSTANCE						hResInstance;						//��Դ���

	//λ����Ϣ
	SIZE							SizeExcursion;						//ƫ��λ��
	POINT							PointExcursion;						//ƫ��λ��
};

//////////////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IGamePropertySink INTERFACE_VERSION(1,1)
	static const GUID IID_IGamePropertySink={0xf9dcc979,0xce63,0x4fa5,0xab,0xa9,0xad,0x9e,0x16,0xa7,0x50,0xa6};
#else
	#define VER_IGamePropertySink INTERFACE_VERSION(1,1)
	static const GUID IID_IGamePropertySink={0xb7fb684b,0x4c23,0x4d47,0x9f,0xdb,0xed,0xad,0x05,0x44,0x7b,0x9e};
#endif

//���߽ӿ�
interface IGamePropertySink : public IUnknownEx
{
	//�������
	virtual bool OnEventBuyProperty(LPCTSTR pszNickName, WORD wItemCount, WORD wPropertyIndex)=NULL;
	//��ѯ�û�
	virtual IClientUserItem * OnQueryClientUserItem()=NULL;
	//��ǰ���
	virtual bool OnEventBuyPropertyPrep(LPCTSTR pszNickName,WORD wPropertyIndex,LPTSTR pszMessage)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IGamePropertyUseSink INTERFACE_VERSION(1,1)
	static const GUID IID_IGamePropertyUseSink={0xb1dfdc0b, 0x57dd, 0x43f6, 0xba, 0x8b, 0x6b, 0xac, 0xd, 0x4e, 0x1f, 0xfa};
#else
	#define VER_IGamePropertyUseSink INTERFACE_VERSION(1,1)
	static const GUID IID_IGamePropertyUseSink={0x1b0bad1a, 0x9694, 0x42a4, 0x9e, 0xf0, 0xf7, 0x35, 0x1e, 0x2d, 0x11, 0x34};
#endif

//���߽ӿ�
interface IGamePropertyUseSink : public IUnknownEx
{
	//ʹ�õ���
	virtual bool OnEventUseProperty(WORD wPropertyIndex)=NULL;	
};

//////////////////////////////////////////////////////////////////////////////////

//�����ļ�

#ifndef GAME_PROPERTY_DLL
	#include "DlgTrumpetItem.h"
	#include "GamePropertyCtrl.h"
	#include "GamePropertyItem.h"
	#include "GamePropertyManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////////

#endif