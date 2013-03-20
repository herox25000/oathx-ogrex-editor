#ifndef GAME_CLIENT_VIEW_HEAD_FILE
#define GAME_CLIENT_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
//#include "CardControl.h"
#include "RecordGameList.h"
#include "ApplyUserList.h"
#include "PngImage.h"


//消息定义
#define IDM_PLACE_JETTON			WM_USER+200							//加住信息
#define IDM_APPLY_BANKER			WM_USER+201							//申请信息
#define IDM_ONBANK					WM_USER+202
//历史记录
#define MAX_SCORE_HISTORY			256									//历史个数

//////////////////////////////////////////////////////////////////////////
//结构定义

//筹码信息
struct tagJettonInfo
{
	int								nXPos;								//筹码位置
	int								nYPos;								//筹码位置
	BYTE							cbJettonIndex;						//筹码索引
};

//筹码数组
typedef CArrayTemplate<tagJettonInfo,tagJettonInfo&> CJettonInfoArray;

//操作结果
enum enOperateResult
{
	enOperateResult_NULL,
	enOperateResult_Win,
	enOperateResult_Lost
};

//记录信息
struct tagClientGameRecord
{
	enOperateResult					enOperateFlags;						//操作标识
	BYTE							cbWinnerAnimal;							//动物
};

//游戏视图
class CGameClientView : public CGameFrameView
{
	//下注信息
protected:
	__int64							m_lMeMaxScore;						//最大下注
	__int64							m_lMeBigTigerScore;					//我买大虎总注
	__int64							m_lMeSmlTigerScore;					//我买小虎总注
	__int64							m_lMeBigBogScore;					//我买大狗总注
	__int64							m_lMeSmlBogScore;					//我买大狗总注
	__int64							m_lMeBigHorseScore;					//我买大马总注
	__int64							m_lMeSmlHorseScore;					//我买小马总注
	__int64							m_lMeBigSnakeScore;					//我买大蛇总注
	__int64							m_lMeSmlSnakeScore;					//我买小蛇总注

	//全体下注
protected:
	__int64							m_lAllBigTigerScore;				//买大虎总注
	__int64							m_lAllSmlTigerScore;				//买小虎总注
	__int64							m_lAllBigBogScore;					//买大狗总注
	__int64							m_lAllSmlBogScore;					//买大狗总注
	__int64							m_lAllBigHorseScore;				//买大马总注
	__int64							m_lAllSmlHorseScore;				//买小马总注
	__int64							m_lAllBigSnakeScore;				//买大蛇总注
	__int64							m_lAllSmlSnakeScore;				//买小蛇总注

	//位置信息
protected:
	LONG							m_nScoreHead;						//成绩位置

	//历史信息
protected:
	LONG							m_wDrawCount;						//游戏局数
	__int64							m_lMeResultCount;					//游戏成绩
	tagClientGameRecord				m_GameRecordArrary[MAX_SCORE_HISTORY];//游戏记录
	int								m_nRecordFirst;						//开始记录
	int								m_nRecordLast;						//最后记录

	//状态变量
protected:
	WORD							m_wMeChairID;						//我的位置
	BYTE							m_cbWinnerSide;						//胜利玩家
	BYTE							m_cbWinnerFlash;					//胜利玩家
	__int64							m_lCurrentJetton;					//当前筹码
	BYTE							m_cbPreJettonArea;					//之前区域

	//庄家信息
public:
	bool							m_bShowChangeBanker;				//轮换庄家
	WORD							m_wCurrentBankerChairID;			//当前庄家
	LONG							m_cbBankerTime;						//做庄次数
	__int64							m_lBankerWinScore;					//庄家成绩
	__int64							m_lBankerTreasure;					//庄家金币

	//当局成绩
public:
	__int64							m_lMeCurGameScore;					//我的成绩
	__int64							m_lMeCurGameReturnScore;			//我的成绩
	__int64							m_lBankerCurGameScore;				//返还积分
	bool							m_bShowGameResult;					//显示积分
	bool							m_bPlayAnimal;						//显示积分
	bool							m_bShowKXF;							//显示可下分
	__int64							m_cbAnimalBox;
	__int64							m_cbNowAnimalBox;

	//数据变量
protected:
	CPoint							m_PointJetton[MAX_ANIMAL_COUNT];	//筹码位置
	CJettonInfoArray				m_JettonInfoArray[MAX_ANIMAL_COUNT];//筹码数组

	//控件变量
public:
	HCURSOR							m_AllhCursor[6];
	CSkinButton						m_btJetton100;						//筹码按钮
	CSkinButton						m_btJetton1000;						//筹码按钮
	CSkinButton						m_btJetton10000;					//筹码按钮
	CSkinButton						m_btJetton100000;					//筹码按钮
	CSkinButton						m_btJetton1000000;					//筹码按钮
	CSkinButton						m_btJetton5000000;					//筹码按钮	
	CSkinButton						m_btApplyBanker;					//申请庄家
	CSkinButton						m_btCancelBanker;					//取消庄家
	CSkinButton						m_btScoreMoveL;						//移动成绩
	CSkinButton						m_btScoreMoveR;						//移动成绩

	CSkinButton						m_btApplyUp;						//上拉庄家列表
	CSkinButton						m_btApplyDown;						//下拉庄家列表

	CSkinButton						m_btGetMoney;						//取款按钮
	CSkinButton						m_btStoreMoney;						//存款按钮

	//控件变量
public:
	CApplyUser						m_ApplyUser;						//申请列表
	CGameRecord						m_GameRecord;						//记录列表

	//界面变量
protected:
	CSkinImage						m_ImageViewFill;					//背景位图
	CPngImage						m_ImageViewBack;					//背景位图
	CPngImage						m_ImageWinFlags;					//标志位图
	CSkinImage						m_ImageJettonView;					//筹码视图
	CSkinImage						m_ImageScoreNumber;					//数字视图
	CSkinImage						m_ImageMeScoreNumber;				//数字视图
	CPngImage						m_ImageTimeFlag;					//时间标识

	//边框资源
protected:
	CSkinImage						m_ImageFrame;						//边框图片
	CSkinImage						m_ImageMeBanker;					//切换庄家
	CSkinImage						m_ImageChangeBanker;				//切换庄家
	CSkinImage						m_ImageNoBanker;					//切换庄家

	//结束资源
protected:
	CPngImage						m_ImageGameEnd;						//成绩图片
	CSkinImage						m_ImageCard;						//图片资源
	CPngImage						m_pngCHART_XIAN;
	CPngImage						m_pngCHART_XIAN_EX;

	//函数定义
public:
	//构造函数
	CGameClientView();
	//析构函数
	virtual ~CGameClientView();

	//继承函数
private:
	//重置界面
	virtual void ResetGameView();
	//调整控件
	virtual void RectifyGameView(int nWidth, int nHeight);
	//绘画界面
	virtual void DrawGameView(CDC * pDC, int nWidth, int nHeight);

	//功能函数
public:
	//设置信息
	void SetMeMaxScore(__int64 lMeMaxScore);
	//设置信息
	void SetMeBigTigerScore(__int64 lMeBigTigerScore);
	void SetMeSmlTigerScore(__int64 lMeSmlTigerScore);
	void SetMeBigDogScore(__int64 lMeBigBogScore);
	void SetMeSmlDogScore(__int64 lMeSmlBogScore);
	void SetMeBigHorseScore(__int64 lMeBigHorseScore);
	void SetMeSmlHorseScore(__int64 lMeSmlHorseScore);
	void SetMeBigSnakeScore(__int64 lMeBigSnakeScore);
	void SetMeSmlSnakeScore(__int64 lMeSmlSnakeScore);

	//设置筹码
	void SetCurrentJetton(__int64 lCurrentJetton);
	//历史成绩
	void SetHistoryScore(WORD wDrawCount,__int64 lMeResultCount);
	//历史记录
	void SetGameHistory(enOperateResult OperateResult, BYTE cbWinner);
	//轮换庄家
	void ShowChangeBanker( bool bChangeBanker );
	//庄家信息
	void SetBankerInfo( WORD wChairID, BYTE cbBankerTime, __int64 lBankerWinScore );
	//庄家金币
	void SetBankerTreasure(__int64 lBankerTreasure);

	//成绩设置
	void SetGameScore(__int64 lMeCurGameScore, __int64 lMeCurGameReturnScore, __int64 lBankerCurGameScore);
	//设置标识
	void SetShowGameFlag(bool bShowGameResult);
	//发牌标识
	void SetPlayAnimalFalg(bool bPlayAnimal){ m_bPlayAnimal = bPlayAnimal; UpdateGameView(NULL);};

	//计算限制
protected:
	//最大下注
	__int64 GetMaxPutScore(BYTE cbJettonArea, BOOL bDebug=FALSE);
	//得到所有人下注的积分
	__int64 Get_ALL_MultiDesktopScore();
	//得到自己下注的积分
	__int64 Get_Me_DesktopJetton();

	//界面函数
public:
	//清理筹码
	void CleanUserJetton();
	//设置筹码
	void PlaceUserJetton(BYTE cbJettonArea, __int64 lScoreCount);
	//设置胜方
	void SetWinnerSide( BYTE cbWinnerSide);
	//艺术字体
	void DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos);
	//绘画数字
	void DrawMeJettonNumber(CDC *pDC);
	//绘画筹码
	void DrawDesktopJetton(CDC *pDC);
	//绘画界面
	void DrawFrame(CDC * pDC, BYTE cbJettonArea, int nWidth, int nHeight);
	//画最大下注
	void DrawMaxPutJetton(CDC * pDC);
	//画最大下注
	void DrawPlayAnimal(CDC *pDC, int nWidth, int nHeight);
	//画最大下注
	void DrawBankerInfo(CDC *pDC, int nWidth, int nHeight);
	//画最大下注
	void DrawMySelfInfo(CDC *pDC, int nWidth, int nHeight);
	void DrawFlashWinner(CDC *pDC, int nWidth, int nHeight);
	void DrawShowChangeBanker(CDC *pDC, int nWidth, int nHeight);
	void DrawTimeFlag(CDC *pDC, int nWidth, int nHeight);
	//画随机
	void DrawRandAnimal(CDC *pDC, int nWidth, int nHeight);

	//内联函数
public:
	//当前筹码
	inline __int64 GetCurrentJetton() { return m_lCurrentJetton; }
	//我的位置
	inline void SetMeChairID(WORD wMeChairID) { m_wMeChairID=wMeChairID; }
	inline WORD GetMeChairID() const {return m_wMeChairID;}
	//内部函数
private:
	//获取区域
	BYTE GetJettonArea(CPoint MousePoint);
	//绘画数字
	void DrawNumberString(CDC * pDC, __int64 lNumber, INT nXPos, INT nYPos, bool bMeScore = false);
	//绘画标识
	void DrawWinFlags(CDC * pDC, int nWidth, int nHeight);
	//显示结果
	void ShowGameResult(CDC *pDC, int nWidth, int nHeight);
	//透明绘画
	bool DrawAlphaRect(CDC* pDC, LPRECT lpRect, COLORREF clr, FLOAT fAlpha);

	//按钮消息
protected:
	//筹码按钮
	afx_msg void OnJettonButton100();
	//筹码按钮
	afx_msg void OnJettonButton1000();
	//筹码按钮
	afx_msg void OnJettonButton10000();
	//筹码按钮
	afx_msg void OnJettonButton100000();
	//筹码按钮
	afx_msg void OnJettonButton500000();
	//筹码按钮
	afx_msg void OnJettonButton1000000();
	//筹码按钮
	afx_msg void OnJettonButton5000000();
	//上庄按钮
	afx_msg void OnApplyBanker();
	//下庄按钮
	afx_msg void OnCancelBanker();
	//移动按钮
	afx_msg void OnScoreMoveL();
	//移动按钮
	afx_msg void OnScoreMoveR();
	//移动按钮
	afx_msg void OnApplyUp();
	//移动按钮
	afx_msg void OnApplyDown();
	//移动按钮
	afx_msg void OnGetMoneyFromBank();
	//移动按钮
	afx_msg void OnStoreMoneyToBank();

	//消息映射
protected:
	//定时器消息
	afx_msg void OnTimer(UINT nIDEvent);
	//建立函数
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//鼠标消息
	afx_msg void OnLButtonDown(UINT nFlags, CPoint Point);	
	//鼠标消息
	afx_msg void OnRButtonDown(UINT nFlags, CPoint Point);	
	//光标消息
	afx_msg BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif