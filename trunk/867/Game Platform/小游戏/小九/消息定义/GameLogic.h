#ifndef GAME_LOGIC_HEAD_FILE
#define GAME_LOGIC_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////
//�˿�����    CARDTYPE
#define CT_SINGLE					0	//����
#define CT_DOUBLE					1   //����

typedef struct 
{
	int nLevel;
	int nCardType;
}stCardType;

//��ֵ����
#define	LOGIC_MASK_COLOR			0xF0								//��ɫ����
#define	LOGIC_MASK_VALUE			0x0F								//��ֵ����

//////////////////////////////////////////////////////////////////////////
//��Ϸ�߼�
class CGameLogic
{
	//��������
private:
	static const BYTE	m_cbCardListData[40];		//�˿˶���

	//��������
public:
	//���캯��
	CGameLogic();
	//��������
	virtual ~CGameLogic();

	//���ͺ���
public:
	//��ȡ��ֵ
	BYTE GetCardValue(BYTE cbCardData) { return cbCardData&LOGIC_MASK_VALUE; }
	//��ȡ��ɫ
	BYTE GetCardColor(BYTE cbCardData) { return cbCardData&LOGIC_MASK_COLOR; }

	//���ƺ���
public:
	//�����˿�
	void RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount);

	//�߼�����
public:
	//��ȡ�Ƶ�
	BYTE GetCardPip(BYTE cbCardData);
	//��ȡ�Ƶ�
	BYTE GetCardListPip(const BYTE cbCardData[], BYTE cbCardCount);


	//--
	////�ж�����
	//BYTE GetCardType(BYTE bCardList[], BYTE bCardCount);
	//�߼���ֵ
	BYTE GetCardLogicValue(BYTE bCardData)
	{
		//�˿�����
		BYTE bCardColor=GetCardColor(bCardData);
		BYTE bCardValue=GetCardValue(bCardData);

		//ת����ֵ
		if(bCardValue==10)return 0;

		return bCardValue;
	}
	//�����˿�
	void SortCard(BYTE bCardList[], BYTE bCardCount);
	bool CompareCard(BYTE bFirstList[], BYTE bNextList[], BYTE bCardCount,bool &bTongdian);
	BYTE GetMaxColor(BYTE bCardList[]);
	int GetMaxSingleValue(BYTE bCardList[]);
	CString GetCardNick(BYTE bCardList[]);
	stCardType GetCardLevel(BYTE bCardList[]);
	int GetSingleTypeLevel(BYTE bSingleCard);
};

#endif