#pragma once

#include "../GameBase.h"
#include "CMD_Baccarat.h"

struct tagJetInfo
{
	tagJetInfo(BYTE cbJ, __int64 lJet)
	{
		cbJettonArea = cbJ;
		lJettonScore = lJet;
	}
	BYTE	cbJettonArea;
	__int64 lJettonScore;
};

typedef std::vector<tagJetInfo> JecVec;

class CBaccarat : public CGameBase
{
public:
	CBaccarat(DWORD dwUserID);
	~CBaccarat();

	//������Ϣ
	DWORD							GetUserID() const {return m_MeUserInfo.dwUserID;}
protected:
	__int64							m_lMeMaxScore;						//�����ע
	__int64							m_lCellScore;						//���Ԫ����

	//��ע��Ϣ
protected:
	__int64							m_lMeTieScore;						//��ƽ��ע
	__int64							m_lMeBankerScore;					//��ׯ��ע
	__int64							m_lMePlayerScore;					//������ע
	__int64							m_lMeTieSamePointScore;				//ͬ��ƽע
	__int64							m_lMePlayerKingScore;				//������ע
	__int64							m_lMeBankerKingScore;				//ׯ����ע

	//ȫ����ע
protected:
	__int64							m_lAllTieScore;						//��ƽ��ע
	__int64							m_lAllBankerScore;					//��ׯ��ע
	__int64							m_lAllPlayerScore;					//������ע
	__int64							m_lAllTieSamePointScore;			//ƽ����ע
	__int64							m_lAllBankerKingScore;				//ׯ����ע
	__int64							m_lAllPlayerKingScore;				//������ע

	//״̬����
protected:
	//��ʷ��Ϣ
protected:
	WORD							m_wDrawCount;						//��Ϸ����
	__int64							m_lMeResultCount;					//��Ϸ�ɼ�

	//ׯ����Ϣ
protected:
	__int64							m_lApplyBankerCondition;			//��������
	__int64							m_lBankerScore;						//ׯ�һ���
	WORD							m_wCurrentBanker;					//��ǰׯ��
	bool							m_bMeApplyBanker;					//�����ʶ
	__int64							m_lBankerTreasure;					//ׯ�ҽ��
	UserVec							m_ApplyBankerVec;					//����ׯ���б�

	bool							m_bMeIsBanker;						//�Լ��ǲ���ׯ��
	int								m_nBankerTimes;						//��ׯ����
	JecVec							m_JecVec;							//��ע��Ϣ
private:
	//��Ϸ״̬
	virtual bool OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize);
	//��Ϸ��Ϣ
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, WORD wDataSize=0);
	//��ʱ����Ϣ
	virtual void OnTimer(WORD wTimerID);
	//������Ϸ
	virtual void ResetGame();
	//Ѻע
	void OnPlaceJetton();

	__int64 GetMaxPlayerScore();

	__int64 GetMaxTieScore();

	__int64 GetMaxBankerScore();
};