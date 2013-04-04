#pragma once

#include "Stdafx.h"
#include "GameClientView.h"

//////////////////////////////////////////////////////////////////////////

//��Ϸ�Ի���
class CGameClientDlg : public CGameFrameDlg
{
	//������Ϣ
protected:
	__int64							m_lMeMaxScore;						//�����ע

	//��ע��Ϣ
protected:

	//-jian
	__int64							m_lMeTianMenScore;					//��������ע		
	__int64							m_lMeDaoMenScore;					//������ע
	__int64							m_lMeShunMenScore;					//��˳����ע
	__int64							m_lMeQiaoScore;						//ƽ��ע
	__int64							m_lMeYouJiaoScore;					//�ҽ�ע
	__int64							m_lMeZuoJiaoScore;					//���ע
	//-

	//״̬����
protected:
	bool							m_bPlaying;							//��Ϸ״̬
	int								m_nShowResultTime;					//��ʾʱ��

	//�˿���Ϣ
protected:
	BYTE							m_cbCardCount[2];					//�˿���Ŀ
	BYTE							m_cbSendCount[4];					//�˿���Ŀ
	BYTE							m_cbWaitPre;

	BYTE							m_cbShowCount;

    BYTE							m_cbTableCardArray[5][2];			//�����˿�
	CString							m_strDispatchCardTips;				//������ʾ

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

	//�ؼ�����
protected:
	CGameLogic						m_GameLogic;						//��Ϸ�߼�
	CGameClientView					m_GameClientView;					//��Ϸ��ͼ
	
	//��������
public:
	//���캯��
	CGameClientDlg();
	//��������
	virtual ~CGameClientDlg();

	//����̳�
private:
	//��ʼ����
	virtual bool InitGameFrame();
	//���ÿ��
	virtual void ResetGameFrame();
	//��Ϸ����
	virtual void OnGameOptionSet();
	//ʱ����Ϣ
	virtual bool OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID);
	//�Թ�״̬
	virtual void OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize);
	//������Ϣ
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
	//��Ϸ����
	virtual bool OnGameSceneMessage(BYTE cbGameStatus, bool bLookonOther, const void * pBuffer, WORD wDataSize);
	//ȡ����Ϣ
	virtual void OnCancel();
	//ˢ����
	virtual bool UpdateView();
	//��Ϣ����
protected:
	//��Ϸ��ʼ
	bool OnSubGameStart(const void * pBuffer, WORD wDataSize);
	//�û���ע
	bool OnSubPlaceJetton(const void * pBuffer, WORD wDataSize);
	//��Ϸ����
	bool OnSubGameEnd(const void * pBuffer, WORD wDataSize);
	//������ׯ
	bool OnUserApplyBanker(const void * pBuffer, WORD wDataSize);
	//�л�ׯ��
	bool OnChangeBanker(const void * pBuffer, WORD wDataSize);
	//���»���
	bool OnChangeUserScore(const void * pBuffer, WORD wDataSize);
	//��Ϸ��¼
	bool OnSubGameRecord(const void * pBuffer, WORD wDataSize);
	//��Ϸ����
	bool OnSubGameScore(const void * pBuffer, WORD wDataSize);

	//���ܺ���
protected:
	//���¿���
	void UpdateButtonContron();
	//�ɷ��˿�
	bool DispatchUserCard(BYTE cbBankerCard[],BYTE cbPlayerCard1[],BYTE cbPlayerCard2[],BYTE cbPlayerCard3[],BYTE cbPreCard[]);
	//������ʾ
	void SetDispatchCardTips();
	//�ƶ�Ӯ��
	void DeduceWinner(WORD &cbWinner);

	//��Ϣӳ��
protected:
	//��ʱ����Ϣ
	afx_msg void OnTimer(UINT nIDEvent);
	//��ע��Ϣ
	LRESULT OnPlaceJetton(WPARAM wParam, LPARAM lParam);
	//������Ϣ
	LRESULT OnApplyBanker(WPARAM wParam, LPARAM lParam);

	LRESULT OnCuoPai(WPARAM wParam, LPARAM lParam);
	LRESULT OnBank(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
