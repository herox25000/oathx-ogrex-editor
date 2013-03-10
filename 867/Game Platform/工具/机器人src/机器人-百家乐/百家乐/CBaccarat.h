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

	//限制信息
	DWORD							GetUserID() const {return m_MeUserInfo.dwUserID;}
protected:
	__int64							m_lMeMaxScore;						//最大下注
	__int64							m_lCellScore;						//最大单元分数

	//下注信息
protected:
	__int64							m_lMeTieScore;						//买平总注
	__int64							m_lMeBankerScore;					//买庄总注
	__int64							m_lMePlayerScore;					//买闲总注
	__int64							m_lMeTieSamePointScore;				//同点平注
	__int64							m_lMePlayerKingScore;				//闲天王注
	__int64							m_lMeBankerKingScore;				//庄天王注

	//全体下注
protected:
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
	JecVec							m_JecVec;							//下注信息
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

	__int64 GetMaxPlayerScore();

	__int64 GetMaxTieScore();

	__int64 GetMaxBankerScore();
};