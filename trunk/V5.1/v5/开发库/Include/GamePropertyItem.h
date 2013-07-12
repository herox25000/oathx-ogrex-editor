#ifndef GAME_PROPERTY_ITEM_HEAD_FILE
#define GAME_PROPERTY_ITEM_HEAD_FILE

#pragma once

#include "GamePropertyHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyItem
{
	//��Ԫ����
	friend class CGamePropertyManager;

	//��������
protected:
	tagPropertyInfo					m_PropertyInfo;						//������Ϣ
	tagPropertyAttrib				m_PropertyAttrib;					//��������

	//��������
public:
	//���캯��
	CGamePropertyItem();
	//��������
	virtual ~CGamePropertyItem();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage)=NULL;
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);

	//���ܺ���
public:
	//��ȡ��Ϣ
	tagPropertyInfo * GetPropertyInfo() { return &m_PropertyInfo; }
	//��ȡ����
	tagPropertyAttrib * GetPropertyAttrib() { return & m_PropertyAttrib; }

	//���ܺ���
public:
	//ʹ�õ���
	VOID ShowBuyPropertyWnd(IGamePropertySink * pIGamePropertySink);
	//����ʱ��
	VOID OnEventPerformCommand(WORD wCommandID,VOID * pCmdData);
};

//////////////////////////////////////////////////////////////////////////////////
//���ﲿ��

//��������
class GAME_PROPERTY_CLASS CGamePropertyCar : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyCar();
	//��������
	virtual ~CGamePropertyCar();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyEgg : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyEgg();
	//��������
	virtual ~CGamePropertyEgg();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyClap : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyClap();
	//��������
	virtual ~CGamePropertyClap();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyKiss : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyKiss();
	//��������
	virtual ~CGamePropertyKiss();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//ơ������
class GAME_PROPERTY_CLASS CGamePropertyBeer : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyBeer();
	//��������
	virtual ~CGamePropertyBeer();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyCake : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyCake();
	//��������
	virtual ~CGamePropertyCake();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//�������
class GAME_PROPERTY_CLASS CGamePropertyRing : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyRing();
	//��������
	virtual ~CGamePropertyRing();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyBeat : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyBeat();
	//��������
	virtual ~CGamePropertyBeat();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//ը������
class GAME_PROPERTY_CLASS CGamePropertyBomb : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyBomb();
	//��������
	virtual ~CGamePropertyBomb();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertySmoke : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertySmoke();
	//��������
	virtual ~CGamePropertySmoke();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyVilla : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyVilla();
	//��������
	virtual ~CGamePropertyVilla();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//שͷ����
class GAME_PROPERTY_CLASS CGamePropertyBrick : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyBrick();
	//��������
	virtual ~CGamePropertyBrick();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//�ʻ�����
class GAME_PROPERTY_CLASS CGamePropertyFlower : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyFlower();
	//��������
	virtual ~CGamePropertyFlower();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////
//���߲���

//2������
class GAME_PROPERTY_CLASS CGamePropertyTwoScoreCard : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyTwoScoreCard();
	//��������
	virtual ~CGamePropertyTwoScoreCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//4������
class GAME_PROPERTY_CLASS CGamePropertyFourScoreCard : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyFourScoreCard();
	//��������
	virtual ~CGamePropertyFourScoreCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyScoreClear : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyScoreClear();
	//��������
	virtual ~CGamePropertyScoreClear();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class GAME_PROPERTY_CLASS CGamePropertyEscapeClear : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyEscapeClear();
	//��������
	virtual ~CGamePropertyEscapeClear();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//С����
class GAME_PROPERTY_CLASS CGamePropertyTrumpet  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyTrumpet();
	//��������
	virtual ~CGamePropertyTrumpet();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//������
class GAME_PROPERTY_CLASS CGamePropertyTyphon  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyTyphon();
	//��������
	virtual ~CGamePropertyTyphon();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//���߿�
class GAME_PROPERTY_CLASS CGamePropertyGuardKickCard  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyGuardKickCard();
	//��������
	virtual ~CGamePropertyGuardKickCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//�����
class GAME_PROPERTY_CLASS CGamePropertyPossess  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyPossess();
	//��������
	virtual ~CGamePropertyPossess();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};


//////////////////////////////////////////////////////////////////////////////////

//���꿨
class GAME_PROPERTY_CLASS CGamePropertyBlueRingCard  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyBlueRingCard();
	//��������
	virtual ~CGamePropertyBlueRingCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//���꿨
class GAME_PROPERTY_CLASS CGamePropertyYellowRingCard  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyYellowRingCard();
	//��������
	virtual ~CGamePropertyYellowRingCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//���꿨
class GAME_PROPERTY_CLASS CGamePropertyWhiteRingCard  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyWhiteRingCard();
	//��������
	virtual ~CGamePropertyWhiteRingCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////

//���꿨
class GAME_PROPERTY_CLASS CGamePropertyRedRingCard  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyRedRingCard();
	//��������
	virtual ~CGamePropertyRedRingCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};


//////////////////////////////////////////////////////////////////////////////////

//Vip����
class GAME_PROPERTY_CLASS CGamePropertyVipRoomCard  : public CGamePropertyItem
{
	//��������
public:
	//���캯��
	CGamePropertyVipRoomCard();
	//��������
	virtual ~CGamePropertyVipRoomCard();

	//���غ���
public:
	//ͼƬ��Ϣ
	virtual VOID GetImageInfo(tagPropertyImage & PropertyImage);
	//��ʾ��Ϣ
	virtual LPCTSTR GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage);
};

//////////////////////////////////////////////////////////////////////////////////


#endif