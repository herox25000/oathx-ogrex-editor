#ifndef GAME_CLIENT_VIEW_HEAD_FILE
#define GAME_CLIENT_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
//#include "CardControl.h"
#include "RecordGameList.h"
#include "ApplyUserList.h"


//��Ϣ����
#define IDM_PLACE_JETTON			WM_USER+200							//��ס��Ϣ
#define IDM_APPLY_BANKER			WM_USER+201							//������Ϣ

//��ʷ��¼
#define MAX_SCORE_HISTORY			256									//��ʷ����

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//������Ϣ
struct tagJettonInfo
{
	int								nXPos;								//����λ��
	int								nYPos;								//����λ��
	BYTE							cbJettonIndex;						//��������
};

//��������
typedef CArrayTemplate<tagJettonInfo,tagJettonInfo&> CJettonInfoArray;

//�������
enum enOperateResult
{
	enOperateResult_NULL,
	enOperateResult_Win,
	enOperateResult_Lost
};

//��¼��Ϣ
struct tagClientGameRecord
{
	enOperateResult					enOperateFlags;						//������ʶ
	BYTE							cbWinnerAnimal;							//����
};

//��Ϸ��ͼ
class CGameClientView : public CGameFrameView
{
	//��ע��Ϣ
protected:
	__int64							m_lMeMaxScore;						//�����ע
	__int64							m_lMeBigTigerScore;					//�������ע
	__int64							m_lMeSmlTigerScore;					//����С����ע
	__int64							m_lMeBigBogScore;					//�������ע
	__int64							m_lMeSmlBogScore;					//�������ע
	__int64							m_lMeBigHorseScore;					//���������ע
	__int64							m_lMeSmlHorseScore;					//����С����ע
	__int64							m_lMeBigSnakeScore;					//���������ע
	__int64							m_lMeSmlSnakeScore;					//����С����ע

	//ȫ����ע
protected:
	__int64							m_lAllBigTigerScore;				//�����ע
	__int64							m_lAllSmlTigerScore;				//��С����ע
	__int64							m_lAllBigBogScore;					//�����ע
	__int64							m_lAllSmlBogScore;					//�����ע
	__int64							m_lAllBigHorseScore;				//�������ע
	__int64							m_lAllSmlHorseScore;				//��С����ע
	__int64							m_lAllBigSnakeScore;				//�������ע
	__int64							m_lAllSmlSnakeScore;				//��С����ע

	//λ����Ϣ
protected:
	LONG							m_nScoreHead;						//�ɼ�λ��

	//��ʷ��Ϣ
protected:
	LONG							m_wDrawCount;						//��Ϸ����
	__int64							m_lMeResultCount;					//��Ϸ�ɼ�
	tagClientGameRecord				m_GameRecordArrary[MAX_SCORE_HISTORY];//��Ϸ��¼
	int								m_nRecordFirst;						//��ʼ��¼
	int								m_nRecordLast;						//����¼

	//״̬����
protected:
	WORD							m_wMeChairID;						//�ҵ�λ��
	BYTE							m_cbWinnerSide;						//ʤ�����
	BYTE							m_cbWinnerFlash;					//ʤ�����
	__int64							m_lCurrentJetton;					//��ǰ����
	BYTE							m_cbPreJettonArea;					//֮ǰ����

	//ׯ����Ϣ
protected:
	bool							m_bShowChangeBanker;				//�ֻ�ׯ��
	WORD							m_wCurrentBankerChairID;			//��ǰׯ��
	LONG							m_cbBankerTime;						//��ׯ����
	__int64							m_lBankerWinScore;					//ׯ�ҳɼ�
	__int64							m_lBankerTreasure;					//ׯ�ҽ��

	//���ֳɼ�
public:
	__int64							m_lMeCurGameScore;					//�ҵĳɼ�
	__int64							m_lMeCurGameReturnScore;			//�ҵĳɼ�
	__int64							m_lBankerCurGameScore;				//��������
	bool							m_bShowGameResult;					//��ʾ����
	bool							m_bPlayAnimal;						//��ʾ����
	bool							m_bShowKXF;							//��ʾ���·�
	__int64							m_cbAnimalBox;
	__int64							m_cbNowAnimalBox;

	//���ݱ���
protected:
	CPoint							m_PointJetton[MAX_ANIMAL_COUNT];	//����λ��
	CJettonInfoArray				m_JettonInfoArray[MAX_ANIMAL_COUNT];//��������

	//�ؼ�����
public:
	HCURSOR							m_AllhCursor[7];
	CSkinButton						m_btJetton100;						//���밴ť
	CSkinButton						m_btJetton1000;						//���밴ť
	CSkinButton						m_btJetton10000;					//���밴ť
	CSkinButton						m_btJetton100000;					//���밴ť
	CSkinButton						m_btJetton1000000;					//���밴ť
	CSkinButton						m_btJetton5000000;					//���밴ť	
	CSkinButton						m_btApplyBanker;					//����ׯ��
	CSkinButton						m_btCancelBanker;					//ȡ��ׯ��
	CSkinButton						m_btScoreMoveL;						//�ƶ��ɼ�
	CSkinButton						m_btScoreMoveR;						//�ƶ��ɼ�

	//�ؼ�����
public:
	CApplyUser						m_ApplyUser;						//�����б�
	CGameRecord						m_GameRecord;						//��¼�б�

	//�������
protected:
	CSkinImage						m_ImageViewFill;					//����λͼ
	CSkinImage						m_ImageViewBack;					//����λͼ
	CSkinImage						m_ImageWinFlags;					//��־λͼ
	CSkinImage						m_ImageJettonView;					//������ͼ
	CSkinImage						m_ImageScoreNumber;					//������ͼ
	CSkinImage						m_ImageMeScoreNumber;				//������ͼ
	CSkinImage						m_ImageTimeFlag;					//ʱ���ʶ

	//�߿���Դ
protected:
	CSkinImage						m_ImageFrame;						//�߿�ͼƬ
	CSkinImage						m_ImageMeBanker;					//�л�ׯ��
	CSkinImage						m_ImageChangeBanker;				//�л�ׯ��
	CSkinImage						m_ImageNoBanker;					//�л�ׯ��

	//������Դ
protected:
	CSkinImage						m_ImageGameEnd;						//�ɼ�ͼƬ
	CSkinImage						m_ImageCard;						//ͼƬ��Դ
	CPngImage						m_pngCHART_XIAN;
	CPngImage						m_pngCHART_XIAN_EX;

	//��������
public:
	//���캯��
	CGameClientView();
	//��������
	virtual ~CGameClientView();

	//�̳к���
private:
	//���ý���
	virtual void ResetGameView();
	//�����ؼ�
	virtual void RectifyGameView(int nWidth, int nHeight);
	//�滭����
	virtual void DrawGameView(CDC * pDC, int nWidth, int nHeight);

	//���ܺ���
public:
	//������Ϣ
	void SetMeMaxScore(__int64 lMeMaxScore);
	//������Ϣ
	void SetMeBigTigerScore(__int64 lMeBigTigerScore);
	void SetMeSmlTigerScore(__int64 lMeSmlTigerScore);
	void SetMeBigDogScore(__int64 lMeBigBogScore);
	void SetMeSmlDogScore(__int64 lMeSmlBogScore);
	void SetMeBigHorseScore(__int64 lMeBigHorseScore);
	void SetMeSmlHorseScore(__int64 lMeSmlHorseScore);
	void SetMeBigSnakeScore(__int64 lMeBigSnakeScore);
	void SetMeSmlSnakeScore(__int64 lMeSmlSnakeScore);

	//���ó���
	void SetCurrentJetton(__int64 lCurrentJetton);
	//��ʷ�ɼ�
	void SetHistoryScore(WORD wDrawCount,__int64 lMeResultCount);
	//��ʷ��¼
	void SetGameHistory(enOperateResult OperateResult, BYTE cbWinner);
	//�ֻ�ׯ��
	void ShowChangeBanker( bool bChangeBanker );
	//ׯ����Ϣ
	void SetBankerInfo( WORD wChairID, BYTE cbBankerTime, __int64 lBankerWinScore );
	//ׯ�ҽ��
	void SetBankerTreasure(__int64 lBankerTreasure);

	//�ɼ�����
	void SetGameScore(__int64 lMeCurGameScore, __int64 lMeCurGameReturnScore, __int64 lBankerCurGameScore);
	//���ñ�ʶ
	void SetShowGameFlag(bool bShowGameResult);
	//���Ʊ�ʶ
	void SetPlayAnimalFalg(bool bPlayAnimal){ m_bPlayAnimal = bPlayAnimal; UpdateGameView(NULL);};

	//��������
protected:
	//�����ע
	__int64 GetMaxPutScore(BYTE cbJettonArea, BOOL bDebug=FALSE);
	//�õ���������ע�Ļ���
	__int64 Get_ALL_MultiDesktopScore();
	//�õ��Լ���ע�Ļ���
	__int64 Get_Me_DesktopJetton();

	//���溯��
public:
	//�������
	void CleanUserJetton();
	//���ó���
	void PlaceUserJetton(BYTE cbJettonArea, __int64 lScoreCount);
	//����ʤ��
	void SetWinnerSide( BYTE cbWinnerSide);
	//��������
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);
	//�滭����
	void DrawMeJettonNumber(CDC *pDC);
	//�滭����
	void DrawDesktopJetton(CDC *pDC);
	//�滭����
	void DrawFrame(CDC * pDC, BYTE cbJettonArea, int nWidth, int nHeight);
	//�������ע
	void DrawMaxPutJetton(CDC * pDC);
	//�������ע
	void DrawPlayAnimal(CDC *pDC, int nWidth, int nHeight);
	//�������ע
	void DrawBankerInfo(CDC *pDC, int nWidth, int nHeight);
	//�������ע
	void DrawMySelfInfo(CDC *pDC, int nWidth, int nHeight);
	void DrawFlashWinner(CDC *pDC, int nWidth, int nHeight);
	void DrawShowChangeBanker(CDC *pDC, int nWidth, int nHeight);
	void DrawTimeFlag(CDC *pDC, int nWidth, int nHeight);

	//��������
public:
	//��ǰ����
	inline __int64 GetCurrentJetton() { return m_lCurrentJetton; }
	//�ҵ�λ��
	inline void SetMeChairID(WORD wMeChairID) { m_wMeChairID=wMeChairID; }

	//�ڲ�����
private:
	//��ȡ����
	BYTE GetJettonArea(CPoint MousePoint);
	//�滭����
	void DrawNumberString(CDC * pDC, __int64 lNumber, INT nXPos, INT nYPos, bool bMeScore = false);
	//�滭��ʶ
	void DrawWinFlags(CDC * pDC, int nWidth, int nHeight);
	//��ʾ���
	void ShowGameResult(CDC *pDC, int nWidth, int nHeight);
	//͸���滭
	bool DrawAlphaRect(CDC* pDC, LPRECT lpRect, COLORREF clr, FLOAT fAlpha);

	//��ť��Ϣ
protected:
	//���밴ť
	afx_msg void OnJettonButton100();
	//���밴ť
	afx_msg void OnJettonButton1000();
	//���밴ť
	afx_msg void OnJettonButton10000();
	//���밴ť
	afx_msg void OnJettonButton100000();
	//���밴ť
	afx_msg void OnJettonButton500000();
	//���밴ť
	afx_msg void OnJettonButton1000000();
	//���밴ť
	afx_msg void OnJettonButton5000000();
	//��ׯ��ť
	afx_msg void OnApplyBanker();
	//��ׯ��ť
	afx_msg void OnCancelBanker();
	//�ƶ���ť
	afx_msg void OnScoreMoveL();
	//�ƶ���ť
	afx_msg void OnScoreMoveR();

	//��Ϣӳ��
protected:
	//��ʱ����Ϣ
	afx_msg void OnTimer(UINT nIDEvent);
	//��������
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Point);	
	//�����Ϣ
	afx_msg void OnRButtonDown(UINT nFlags, CPoint Point);	
	//�����Ϣ
	afx_msg BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif