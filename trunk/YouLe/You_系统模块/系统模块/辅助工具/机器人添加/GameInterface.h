#pragma once
#include "userinterface.h"

class CGameInterface :
	public CUserInterface
{
public:
	CGameInterface(void);
	~CGameInterface(void);
private:
	//�ڿ���Ϸ����
	WORD							m_wCavernUser;						//�ڿ��û�
	BYTE							m_bHandCardCount;					//�˿���Ŀ
	BYTE							m_bHandCardData[20];				//�����˿�
	WORD                            m_wCurrentOutCard;                   //���Ƶ��û�
	BYTE                            m_wCurrentScore;                    //��ǰ�Ľз�
			//���Ʊ���
	BYTE							m_bTurnOutType;						//��������
	BYTE							m_bTurnCardCount;					//������Ŀ
	BYTE							m_bTurnCardData[20];				//�����б�
	bool							m_IsCanOut;
public:
	//�����˿�
	bool OnSubSendCard(const void * pBuffer, WORD wDataSize);
	//�û��з�
	bool OnSubCavernScore(const void * pBuffer, WORD wDataSize);
	//��Ϸ��ʼ
	bool OnSubGameStart(const void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSubOutCard(const void * pBuffer, WORD wDataSize);
	//��������
	bool OnSubPassCard(const void * pBuffer, WORD wDataSize);
	//��Ϸ����
	bool OnSubGameEnd(const void * pBuffer, WORD wDataSize);
	//�߼��ж�
	bool   SubDelayTime();
	bool   OnScore();
	bool   OnOutCard();
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
};
