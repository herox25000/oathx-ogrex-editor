#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////
//����

enum emCardType
{
	CT_ERROR			=		0	,								//��������
	CT_POINT		 =			1	,								//��������
	CT_SPECIAL_NIU1		=		3	,								//��������
	CT_SPECIAL_NIU2		=		4,									//��������
	CT_SPECIAL_NIU3		=		5	,								//��������
	CT_SPECIAL_NIU4		=		6,									//��������
	CT_SPECIAL_NIU5		=		7,									//��������
	CT_SPECIAL_NIU6		=		8,									//��������
	CT_SPECIAL_NIU7		=		9,								//��������
	CT_SPECIAL_NIU8		=		10,									//��������
	CT_SPECIAL_NIU9		=	    11	,								//��������
	CT_SPECIAL_NIUNIUXW	=		12,									//��������
	CT_SPECIAL_NIUNIUDW	=		13,									//��������
	CT_SPECIAL_NIUNIU	=		14,									//��������
	CT_SPECIAL_NIUYING		=		15,									//��������
	CT_SPECIAL_NIUKING		=	    16	,								//��������
	CT_SPECIAL_BOMEBOME		=		17									//��������

};
//#define	CT_ERROR					0									//��������
//#define	CT_POINT					1									//��������
//#define	CT_SPECIAL_NIU1				3									//��������
//#define	CT_SPECIAL_NIU2				4									//��������
//#define	CT_SPECIAL_NIU3				5									//��������
//#define	CT_SPECIAL_NIU4				6									//��������
//#define	CT_SPECIAL_NIU5				7									//��������
//#define	CT_SPECIAL_NIU6				8									//��������
//#define	CT_SPECIAL_NIU7				9									//��������
//#define	CT_SPECIAL_NIU8				10									//��������
//#define	CT_SPECIAL_NIU9			    11									//��������
//#define CT_SPECIAL_NIUNIU			12								//��������
//#define CT_SPECIAL_NIUNIUXW			13									//��������
//#define CT_SPECIAL_NIUNIUDW			14									//��������
//
//#define CT_SPECIAL_NIUYING			15									//��������
//#define CT_SPECIAL_NIUKING			16								//��������
//#define CT_SPECIAL_BOMEBOME			17			
//��ֵ����
#define	LOGIC_MASK_COLOR			0xF0								//��ɫ����
#define	LOGIC_MASK_VALUE			0x0F								//��ֵ����

//��������
#define	ST_VALUE					1									//��ֵ����
#define	ST_NEW					    3									//��ֵ����
#define	ST_LOGIC					2									//�߼�����

//�˿���Ŀ
#define CARD_COUNT					54									//�˿���Ŀ
//////////////////////////////////////////////////////////////////////////

//��Ϸ�߼�
class CGameLogic
{
	//��������
private:
	static const BYTE				m_cbCardListData[CARD_COUNT];		//�˿˶���

	//��������
public:
	//���캯��
	CGameLogic();
	//��������
	virtual ~CGameLogic();

	//���ͺ���
public:
	//��ȡ��ֵ
	BYTE GetCardValue(BYTE cbCardData) 
	{ 
		return cbCardData&LOGIC_MASK_VALUE; 
	}
	//��ȡ��ɫ
	BYTE GetCardColor(BYTE cbCardData)
	{
		return (cbCardData&LOGIC_MASK_COLOR)>>4;
	}

	//���ƺ���
public:
	//�����˿�
	void RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount);
	//�����˿�
	void SortCardList(BYTE cbCardData[], BYTE cbCardCount, BYTE cbSortType);

	int RetType(int itype);

	//�߼�����
public:
	//��ȡ�Ƶ�
	BYTE GetCardListPip(const BYTE cbCardData[], BYTE cbCardCount);
	//��ȡ����
	BYTE GetCardType(const BYTE cbCardData[], BYTE cbCardCount,BYTE *bcOutCadData = NULL);
	//��С�Ƚ�
	int CompareCard(const BYTE cbFirstCardData[], BYTE cbFirstCardCount,const BYTE cbNextCardData[], BYTE cbNextCardCount,BYTE &Multiple);
	//�߼���С
	BYTE GetCardLogicValue(BYTE cbCardData);

	BYTE GetCardNewValue(BYTE cbCardData);
};

//////////////////////////////////////////////////////////////////////////

#endif
