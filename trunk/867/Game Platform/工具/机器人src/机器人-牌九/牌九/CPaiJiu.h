#pragma once

#include "../GameBase.h"
#include "CMD_PaiJiu.h"

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

	DWORD							GetUserID() const;
	//限制信息
protected:
	__int64							m_lMeMaxScore;						//最大下注

	__int64							m_lMeTianMenScore;					//买天门总注		
	__int64							m_lMeDaoMenScore;					//买倒门总注
	__int64							m_lMeShunMenScore;					//买顺门总注
	__int64							m_lMeQiaoScore;						//平桥注
	__int64							m_lMeYouJiaoScore;					//右角注
	__int64							m_lMeZuoJiaoScore;					//左角注

	__int64							m_lAllTieScore;						//买平总注
	__int64							m_lAllBankerScore;					//买庄总注
	__int64							m_lAllPlayerScore;					//买闲总注
	__int64							m_lAllTieSamePointScore;			//平天王注
	__int64							m_lAllBankerKingScore;				//庄天王注
	__int64							m_lAllPlayerKingScore;				//闲天王注
	//状态变量
protected:
	//历史信息
protected:
	WORD							m_wDrawCount;						//游戏局数
	__int64							m_lMeResultCount;					//游戏成绩

	//庄家信息
protected:
	__int64							m_lApplyBankerCondition;			//申请条件
	__int64							m_lBankerScore;						//庄家积分
	WORD							m_wCurrentBanker;					//当前庄家
	bool							m_bMeApplyBanker;					//申请标识
	__int64							m_lBankerTreasure;					//庄家金币
	UserVec							m_ApplyBankerVec;					//申请庄家列表

	bool							m_bMeIsBanker;						//自己是不是庄家
	int								m_nBankerTimes;						//坐庄次数

protected:
	int								m_nMaxBankerCount;					//最大坐庄次数
	__int64							m_nUnBankerForWin;					//赢了多少自动下庄
	__int64							m_nOfflineForWin;					//赢了多少自动离线
	int								m_nJettonMaxNum;					//最多下注次数

	__int64							m_nBeforeJettonScore;				//下注前金额

private:
	//游戏状态
	virtual bool OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, WORD wDataSize);
	//游戏消息
	virtual bool OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, WORD wDataSize=0);
	//定时器消息
	virtual void OnTimer(WORD wTimerID);
	//重置游戏
	virtual void ResetGame();
	//押注
	void OnPlaceJetton();
	//最大下注
	__int64 GetMaxPlayerScore();
	//最大下注
	__int64 GetMaxPlayerKingScore();
	//最大下注
	__int64 GetMaxBankerScore();
	//最大下注
	__int64 GetMaxBankerKingScore();
	//最大下注
	__int64 GetMaxTieScore();
	//最大下注
	__int64 GetMaxTieKingScore();
	__int64 GetNowJettonScore();
};