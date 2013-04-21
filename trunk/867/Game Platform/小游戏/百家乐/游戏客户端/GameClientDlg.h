#pragma once

#include "Stdafx.h"
#include "GameClientView.h"
#include "DirectSound.h"
//////////////////////////////////////////////////////////////////////////

#define GS_SHOW_RESULT	101

//��Ϸ�Ի���
class CGameClientDlg : public CGameFrameDlg
{
	//������Ϣ
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

	//״̬����
protected:
	bool							m_bPlaying;							//��Ϸ״̬
	int								m_nShowResultTime;					//��ʾʱ��

	//�˿���Ϣ
protected:
	BYTE							m_cbCardCount[2];					//�˿���Ŀ
	BYTE							m_cbSendCount[2];					//�˿���Ŀ
    BYTE							m_cbTableCardArray[2][3];			//�����˿�
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
	//������Դ
protected:
	CDirectSound					m_DTSDBackground;					//��������
	CDirectSound					m_DTSDCheer[3];						//��������


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
	//ˢ����
	virtual bool UpdateView();
	//ȡ����Ϣ
	virtual void OnCancel();

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
	//Ѻע��Ϣ�ı� 
	bool OnSubJettonChange(const void * pBuffer, WORD wDataSize);
	//��ʼѺע
	bool OnStartJetton(const void * pBuffer, WORD wDataSize);

	//���ܺ���
public:
	//���¿���
	void UpdateButtonContron();
	//�ɷ��˿�
	bool DispatchUserCard(BYTE cbPlayerCard[], BYTE cbPlayerCount, BYTE cbBankerCard[], BYTE cbBankerCount);
	//������ʾ
	void SetDispatchCardTips();
	//�ƶ�Ӯ��
	void DeduceWinner(BYTE &cbWinner, BYTE &cbKingWinner);
	//�ڽ���״̬�����ʱ����ʾ�˿�
	void ShowCardOnEnd(BYTE cbPlayerCard[], BYTE cbPlayerCount, BYTE cbBankerCard[], BYTE cbBankerCount);

	//��Ϣӳ��
protected:
	//��ʱ����Ϣ
	afx_msg void OnTimer(UINT nIDEvent);
	//��ע��Ϣ
	LRESULT OnPlaceJetton(WPARAM wParam, LPARAM lParam);
	//������Ϣ
	LRESULT OnApplyBanker(WPARAM wParam, LPARAM lParam);
	LRESULT OnBank(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
