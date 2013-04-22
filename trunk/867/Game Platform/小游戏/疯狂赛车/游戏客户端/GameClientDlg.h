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
	__int64							m_lMeBigTigerScore;					//�������ע
	__int64							m_lMeSmlTigerScore;					//����С����ע
	__int64							m_lMeBigBogScore;					//�������ע
	__int64							m_lMeSmlBogScore;					//�������ע
	__int64							m_lMeBigHorseScore;					//���������ע
	__int64							m_lMeSmlHorseScore;					//����С����ע
	__int64							m_lMeBigSnakeScore;					//���������ע
	__int64							m_lMeSmlSnakeScore;					//����С����ע

	//״̬����
protected:
	bool							m_bPlaying;							//��Ϸ״̬
//	int								m_nShowResultTime;					//��ʾʱ��
	__int64							m_lBeginTime;
	__int64							m_lTotalTime;

	//��ʷ��Ϣ
protected:
	WORD							m_wDrawCount;						//��Ϸ����
	__int64							m_lMeResultCount;					//��Ϸ�ɼ�

	//ׯ����Ϣ
protected:
	__int64							m_lApplyBankerCondition;			//��������
	__int64							m_lBankerWinScore;					//ׯ����Ӯ
	WORD							m_wCurrentBanker;					//��ǰׯ��
	bool							m_bMeApplyBanker;					//�����ʶ
	__int64							m_lBankerTreasure;					//ׯ�ҽ��

	//�ؼ�����
protected:
	CGameClientView					m_GameClientView;					//��Ϸ��ͼ

	int								m_iTimerStep;
	int								m_iTotoalRun;
	int								m_iRunIndex;
	
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
	//��ʼ��ע
	bool OnSubStartJetton(const void * pBuffer, WORD wDataSize);

	//���ܺ���
protected:
	//���¿���
	void UpdateButtonContron();
	//��ʼ��ʾ����
	bool DispatchUserCard(BYTE cbAnimalBox,int TimeLeave);
	//�ƶ�Ӯ��
	BYTE DeduceWinner();
	
	void StartRunCar(int iTimer);
	void RuningCar(int iTimer);
	void FinishDispatchCard();

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
