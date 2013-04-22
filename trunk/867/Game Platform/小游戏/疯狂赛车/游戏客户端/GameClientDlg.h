#pragma once

#include "Stdafx.h"
#include "GameClientView.h"
#include "DirectSound.h"

//////////////////////////////////////////////////////////////////////////

#define GS_SHOW_RESULT	101

//游戏对话框
class CGameClientDlg : public CGameFrameDlg
{
	//限制信息
protected:
	__int64							m_lMeMaxScore;						//最大下注
	__int64							m_lCellScore;						//最大单元分数
	//下注信息
protected:
	__int64							m_lMeBigTigerScore;					//我买大虎总注
	__int64							m_lMeSmlTigerScore;					//我买小虎总注
	__int64							m_lMeBigBogScore;					//我买大狗总注
	__int64							m_lMeSmlBogScore;					//我买大狗总注
	__int64							m_lMeBigHorseScore;					//我买大马总注
	__int64							m_lMeSmlHorseScore;					//我买小马总注
	__int64							m_lMeBigSnakeScore;					//我买大蛇总注
	__int64							m_lMeSmlSnakeScore;					//我买小蛇总注

	//状态变量
protected:
	bool							m_bPlaying;							//游戏状态
//	int								m_nShowResultTime;					//显示时间
	__int64							m_lBeginTime;
	__int64							m_lTotalTime;

	//历史信息
protected:
	WORD							m_wDrawCount;						//游戏局数
	__int64							m_lMeResultCount;					//游戏成绩

	//庄家信息
protected:
	__int64							m_lApplyBankerCondition;			//申请条件
	__int64							m_lBankerWinScore;					//庄家输赢
	WORD							m_wCurrentBanker;					//当前庄家
	bool							m_bMeApplyBanker;					//申请标识
	__int64							m_lBankerTreasure;					//庄家金币

	//控件变量
protected:
	CGameClientView					m_GameClientView;					//游戏视图

	int								m_iTimerStep;
	int								m_iTotoalRun;
	int								m_iRunIndex;
	
	//声音资源
protected:
	CDirectSound					m_DTSDBackground;					//背景音乐
	CDirectSound					m_DTSDCheer[3];						//背景音乐

	//函数定义
public:
	//构造函数
	CGameClientDlg();
	//析构函数
	virtual ~CGameClientDlg();

	//常规继承
private:
	//初始函数
	virtual bool InitGameFrame();
	//重置框架
	virtual void ResetGameFrame();
	//游戏设置
	virtual void OnGameOptionSet();
	//时间消息
	virtual bool OnTimerMessage(WORD wChairID, UINT nElapse, UINT nTimerID);
	//旁观状态
	virtual void OnLookonChanged(bool bLookonUser, const void * pBuffer, WORD wDataSize);
	//网络消息
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
	//游戏场景
	virtual bool OnGameSceneMessage(BYTE cbGameStatus, bool bLookonOther, const void * pBuffer, WORD wDataSize);
	//取消消息
	virtual void OnCancel();
	//刷新下
	virtual bool UpdateView();
	//消息处理
protected:
	//游戏开始
	bool OnSubGameStart(const void * pBuffer, WORD wDataSize);
	//用户加注
	bool OnSubPlaceJetton(const void * pBuffer, WORD wDataSize);
	//游戏结束
	bool OnSubGameEnd(const void * pBuffer, WORD wDataSize);
	//申请做庄
	bool OnUserApplyBanker(const void * pBuffer, WORD wDataSize);
	//切换庄家
	bool OnChangeBanker(const void * pBuffer, WORD wDataSize);
	//更新积分
	bool OnChangeUserScore(const void * pBuffer, WORD wDataSize);
	//游戏记录
	bool OnSubGameRecord(const void * pBuffer, WORD wDataSize);
	//游戏积分
	bool OnSubGameScore(const void * pBuffer, WORD wDataSize);
	//开始下注
	bool OnSubStartJetton(const void * pBuffer, WORD wDataSize);

	//功能函数
protected:
	//更新控制
	void UpdateButtonContron();
	//开始显示动画
	bool DispatchUserCard(BYTE cbAnimalBox,int TimeLeave);
	//推断赢家
	BYTE DeduceWinner();
	
	void StartRunCar(int iTimer);
	void RuningCar(int iTimer);
	void FinishDispatchCard();

	//消息映射
protected:
	//定时器消息
	afx_msg void OnTimer(UINT nIDEvent);
	//加注消息
	LRESULT OnPlaceJetton(WPARAM wParam, LPARAM lParam);
	//申请消息
	LRESULT OnApplyBanker(WPARAM wParam, LPARAM lParam);

	LRESULT OnBank(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
