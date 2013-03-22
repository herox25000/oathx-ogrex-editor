#pragma once

#include "../GameBase.h"
#include "CMD_XiaoJiu.h"

// struct tagJetInfo
// {
// 	tagJetInfo(BYTE cbJ, __int64 lJet)
// 	{
// 		cbJettonArea = cbJ;
// 		lJettonScore = lJet;
// 	}
// 	BYTE	cbJettonArea;
// 	__int64 lJettonScore;
// };
// 
// typedef std::vector<tagJetInfo> JecVec;

class CPaiJiu : public CGameBase
{
public:
	CPaiJiu(DWORD dwUserID);
	~CPaiJiu();

	DWORD							GetUserID() const {return m_MeUserInfo.dwUserID;}
	//������Ϣ
protected:
	__int64							m_lMeMaxScore;						//�����ע

	__int64							m_lMeTianMenScore;					//��������ע		
	__int64							m_lMeDaoMenScore;					//������ע
	__int64							m_lMeShunMenScore;					//��˳����ע
	__int64							m_lMeQiaoScore;						//ƽ��ע
	__int64							m_lMeYouJiaoScore;					//�ҽ�ע
	__int64							m_lMeZuoJiaoScore;					//���ע

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

protected:
	int								m_nMaxBankerCount;					//�����ׯ����
	__int64							m_nUnBankerForWin;					//Ӯ�˶����Զ���ׯ
	__int64							m_nOfflineForWin;					//Ӯ�˶����Զ�����
	int								m_nJettonMaxNum;					//�����ע����

	__int64							m_nBeforeJettonScore;				//��עǰ���

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
	//�����ע
	__int64 GetMaxPlayerScore();
	//�����ע
	__int64 GetMaxPlayerKingScore();
	//�����ע
	__int64 GetMaxBankerScore();
	//�����ע
	__int64 GetMaxBankerKingScore();
	//�����ע
	__int64 GetMaxTieScore();
	//�����ע
	__int64 GetMaxTieKingScore();
	__int64 GetNowJettonScore();
};