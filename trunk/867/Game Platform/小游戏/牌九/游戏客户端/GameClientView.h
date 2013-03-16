#ifndef GAME_CLIENT_VIEW_HEAD_FILE
#define GAME_CLIENT_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
//#include "CardControl.h"
#include "RecordGameList.h"
#include "ApplyUserList.h"
#include "GameLogic.h"
#include "DrawCard.h"


#define JETTON_COUNT				9									//������Ŀ
#define JETTON_RADII				54									//����뾶
#define JETTON_WIDTH				59
#define JETTON_HEIGHT				51

//��Ϣ����
#define IDM_PLACE_JETTON			WM_USER+200							//��ס��Ϣ
#define IDM_APPLY_BANKER			WM_USER+201							//������Ϣ
#define IDM_CUOPAI					WM_USER+202							
#define IDM_ONBANK					WM_USER+203					

#define INDEX_BANKER				0									//ׯ������
#define INDEX_PLAYER1				1									//�м�1����
#define INDEX_PLAYER2				2									//�м�1����
#define INDEX_PLAYER3				3									//�м�1����
#define INDEX_PRECARD				4									

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
	BYTE							cbPlayerCount;						//�мҵ���
	BYTE							cbBankerCount;						//ׯ�ҵ���

	WORD							wWinner;							//ʤ�����
	__int64							lMeTianMenScore;					//��ƽ��ע
	__int64							lMeDaoMenScore;						//��ׯ��ע
	__int64							lMeShunMenScore;					//������ע
	__int64							lMeQiaoScore;						//ͬ��ƽע
	__int64							lMeZuoJiaoScore;					//������ע
	__int64							lMeYouJiaoScore;					//ׯ����ע

};

//////////////////////////////////////////////////////////////////////////


enum {
	JBST_NORMAL,
	JBST_OVER,
	JBST_PUSHDOWN,
	JBST_PUSHUP,
	JBST_DISABLE,
};

class JettonButton
{
public:
	JettonButton();
	virtual ~JettonButton();

	virtual	void					Create(const CRect& rect, UINT uIDResource, HINSTANCE hResourceDLL);
	virtual	void					SetImageResource(UINT uIDResource, HINSTANCE hResourceDLL);

	virtual	void					SetState(int nState);
	virtual int						GetState() const;

	virtual	void					SetClientRect(const CRect& rect);
	virtual CRect					GetClientRect() const;

	virtual	void					Draw(CDC* pDC);

	virtual	void					Enabled(BOOL bEnabled);
protected:
	CSkinImage						m_SkinImage;
	int								m_nState;
	CRect							m_SkinRect;
};

//��Ϸ��ͼ
class CGameClientView : public CGameFrameView
{
public:
	CDrawCard						m_DrawCard[5];
	bool							m_bAutoCard;
	bool							m_bCanGo;
	bool							m_bSet;
	//��ע��Ϣ
protected:
	__int64							m_lMeMaxScore;						//�����ע
	__int64							m_lMeTianMenScore;					//��������ע		
	__int64							m_lMeDaoMenScore;					//������ע
	__int64							m_lMeShunMenScore;					//��˳����ע
	__int64							m_lMeQiaoScore;						//ƽ��ע
	__int64							m_lMeYouJiaoScore;					//�ҽ�ע
	__int64							m_lMeZuoJiaoScore;					//���ע
	//-

	//ȫ����ע
protected:
	__int64							m_lAllTieScore;						//��ƽ��ע
	__int64							m_lAllBankerScore;					//��ׯ��ע
	__int64							m_lAllPlayerScore;					//������ע
	__int64							m_lAllTieSamePointScore;			//ƽ����ע
	__int64							m_lAllBankerKingScore;				//ׯ����ע
	__int64							m_lAllPlayerKingScore;				//������ע

	//λ����Ϣ
protected:
	int								m_nWinFlagsExcursionX;				//ƫ��λ��
	int								m_nWinFlagsExcursionY;				//ƫ��λ��
	int								m_nWinPointsExcursionX;				//ƫ��λ��
	int								m_nWinPointsExcursionY;				//ƫ��λ��
	int								m_nScoreHead;						//�ɼ�λ��

	//��ʷ��Ϣ
protected:
	WORD							m_wDrawCount;						//��Ϸ����
	__int64							m_lMeResultCount;					//��Ϸ�ɼ�
	tagClientGameRecord				m_GameRecordArrary[MAX_SCORE_HISTORY];//��Ϸ��¼
	int								m_nRecordFirst;						//��ʼ��¼
	int								m_nRecordLast;						//����¼

	//״̬����
protected:
	WORD							m_wMeChairID;						//�ҵ�λ��
	WORD							m_cbWinnerSide;						//ʤ�����
	WORD							m_cbWinnerFlash;					//ʤ�����
	__int64							m_lCurrentJetton;					//��ǰ����
	CString							m_strGameCardResult;				//��Ϸ���
	BYTE							m_cbPreJettonArea;					//֮ǰ����
	bool							m_bDispatchCard;					//���Ʊ�ʶ
	CString							m_strDispatchCardTips;				//������ʾ

	//ׯ����Ϣ
public:
	bool							m_bShowChangeBanker;				//�ֻ�ׯ��
	WORD							m_wCurrentBankerChairID;			//��ǰׯ��
	BYTE							m_cbBankerTime;						//��ׯ����
	__int64							m_lBankerScore;						//ׯ�ҳɼ�
	__int64							m_lBankerTreasure;					//ׯ�ҽ��

	//���ֳɼ�
public:
	__int64							m_lMeCurGameScore;					//�ҵĳɼ�
	__int64							m_lMeCurGameReturnScore;			//�ҵĳɼ�
	__int64							m_lBankerCurGameScore;				//��������
	bool							m_bShowGameResult;					//��ʾ����

	//���ݱ���
protected:
	CPoint							m_PointJetton[6];					//����λ��
	CJettonInfoArray				m_JettonInfoArray[6];				//��������

	//�ؼ�����
public:	
	CSkinButton						m_btApplyBanker;					//����ׯ��
	CSkinButton						m_btCancelBanker;					//ȡ��ׯ��

	CSkinButton						m_btScoreMoveL;						//�ƶ��ɼ�
	CSkinButton						m_btScoreMoveR;						//�ƶ��ɼ�

	CSkinButton						m_btnZiDongCuoPai;						
	CSkinButton						m_btnShouDongCuoPai;	
	CSkinButton						m_btnShengyin;						
	CSkinButton						m_btnNoShengyin;
	CSkinButton						m_btnQuqian;						
	CSkinButton						m_btnCunqian;						

	JettonButton					m_JettonButton[7];
	BOOL							m_JettonButtonPushDown;
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
	CSkinImage						m_ImageFrameXianJia;				//�߿�ͼƬ
	CSkinImage						m_ImageFrameZhuangJia;				//�߿�ͼƬ
	CSkinImage						m_ImageFrameXianTianWang;			//�߿�ͼƬ
	CSkinImage						m_ImageFrameZhuangTianWang;			//�߿�ͼƬ
	CSkinImage						m_ImageFramePingJia;				//�߿�ͼƬ
	CSkinImage						m_ImageFrameTongDianPing;			//�߿�ͼƬ

	CSkinImage						m_ImageFrameXianJia1;				//�߿�ͼƬ
	CSkinImage						m_ImageFrameZhuangJia1;				//�߿�ͼƬ
	CSkinImage						m_ImageFrameXianTianWang1;			//�߿�ͼƬ
	CSkinImage						m_ImageFrameZhuangTianWang1;			//�߿�ͼƬ
	CSkinImage						m_ImageFramePingJia1;				//�߿�ͼƬ
	CSkinImage						m_ImageFrameTongDianPing1;			//�߿�ͼƬ

	CSkinImage						m_ImageMeBanker;					//�л�ׯ��
	CSkinImage						m_ImageChangeBanker;				//�л�ׯ��
	CSkinImage						m_ImageNoBanker;					//�л�ׯ��
	//������Դ
protected:
	CSkinImage						m_ImageGameEnd;						//�ɼ�ͼƬ
	CSkinImage						m_ImageGameEndFrame;				//�߿�ͼƬ
	CSkinImage						m_ImageGamePoint;					//����ͼƬ
	CSkinImage						m_ImageCard;						//ͼƬ��Դ
protected:
	CPngImage						m_pngc;			
	CPngImage						m_pngp;

public:	
	bool							m_bJettonstate;						//�Ƿ�����ע״̬
	//��������

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
	void SetMeTieScore(__int64 lMeTieScore);
	//������Ϣ
	void SetMeBankerScore(__int64 lMeBankerScore);
	//������Ϣ
	void SetMePlayerScore(__int64 lMePlayerScore);
	//������Ϣ
	void SetMePlayerKingScore(__int64 lMePlayerKingScore);
	//������Ϣ
	void SetMeBankerKingScore(__int64 lMeBankerKingScore);
	//������Ϣ
	void SetMeTieSamePointScore(__int64 lMeTieSamePointScore);

	//���ó���
	void SetCurrentJetton(__int64 lCurrentJetton);
	//��ʷ�ɼ�
	void SetHistoryScore(WORD wDrawCount,__int64 lMeResultCount);
	//��ʷ��¼
	void SetGameHistory(enOperateResult OperateResult, BYTE cbPlayerCount, BYTE cbBankerCount,WORD wWinner);
	//�ֻ�ׯ��
	void ShowChangeBanker( bool bChangeBanker );
	//ׯ����Ϣ
	void SetBankerInfo( WORD wChairID, BYTE cbBankerTime, __int64 lScore );
	//ׯ�ҽ��
	void SetBankerTreasure(__int64 lBankerTreasure);

	//�ɼ�����
	void SetGameScore(__int64 lMeCurGameScore, __int64 lMeCurGameReturnScore, __int64 lBankerCurGameScore);
	//���ñ�ʶ
	void SetShowGameFlag(bool bShowGameResult);
	//���Ʊ�ʶ
	void SetDispatchCardFalg(bool bDispatchCard){ m_bDispatchCard = bDispatchCard; UpdateGameView(NULL);};
	//������ʾ
	void SetDispatchCardTips(CString const &strTips) { m_strDispatchCardTips = strTips; UpdateGameView(NULL);};


	//��������
protected:
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


	//���溯��
public:
	//�������
	void CleanUserJetton();
	//���ó���
	void PlaceUserJetton(BYTE cbViewIndex, __int64 lScoreCount);
	//����ʤ��
	void SetWinnerSide(LPCTSTR pszGameResult, WORD cbWinnerSide);
	//��������
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);
	//�滭����
	void DrawMeJettonNumber(CDC *pDC);
	//���ֻ���Ϊ�ַ���
	CString ChangNumber(__int64 iNumber);
	CString ChangNumber(int iNumber);
	//����������ע�ܺ�
	__int64 CalcAllJetton();
	//��������
public:
	//��ǰ����
	inline __int64 GetCurrentJetton() { return m_lCurrentJetton; }
	//�ҵ�λ��
	inline void SetMeChairID(WORD wMeChairID) { m_wMeChairID=wMeChairID; }
	inline WORD GetMeChairID() const {return m_wMeChairID;}
	//�ڲ�����
private:
	//��ȡ����
	BYTE GetJettonArea(CPoint MousePoint);
	//�滭����
	void DrawNumberString(CDC * pDC, __int64 lNumber, INT nXPos, INT nYPos, bool bMeScore = false);
	//�滭��ʶ
	void DrawWinFlags(CDC * pDC);
	//��ʾ���
	void ShowGameResult(CDC *pDC, int nWidth, int nHeight);
	//͸���滭
	bool DrawAlphaRect(CDC* pDC, LPRECT lpRect, COLORREF clr, FLOAT fAlpha);

	//��ť��Ϣ
protected:	
	//���밴ť
	afx_msg void OnJettonButton1000();
	//���밴ť
	afx_msg void OnJettonButton10000();
	//���밴ť
	afx_msg void OnJettonButton100000();
	//���밴ť
	afx_msg void OnJettonButton500000();
	afx_msg void OnJettonButton1000000();
	afx_msg void OnJettonButton5000000();
	afx_msg void OnJettonButton10000000();
	//��ׯ��ť
	afx_msg void OnApplyBanker();
	//��ׯ��ť
	afx_msg void OnCancelBanker();
	//�ƶ���ť
	afx_msg void OnScoreMoveL();
	//�ƶ���ť
	afx_msg void OnScoreMoveR();

	afx_msg void OnCuoPaiModel();
	afx_msg void OnBank();
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
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////

#endif