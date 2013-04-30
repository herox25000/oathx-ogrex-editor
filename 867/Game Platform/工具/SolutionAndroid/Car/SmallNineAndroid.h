#pragma once

#include "IAndroid.h"

namespace O2
{
#define US_BANKER					0x07
#define US_LINUP					0x08

#define MIN_UPBANKER				2
#define MIN_LINUP					2

#define MAX_PLACE_JETTON_TIME		20
#define MIN_PLACE_REMAIN			103000

	//////////////////////////////////////////////////////////////////////////
	// 小九机器人实现
	//////////////////////////////////////////////////////////////////////////
	class SmallNineAndroid : public IAndroid
	{
	public:
		/*
		* 构造函数
		*/
		SmallNineAndroid(DWORD dwUserID, double fOnlineTime);
		/*
		* 析构函数
		*/		
		virtual ~SmallNineAndroid();
		
	public:
		/*
		* 游戏更新
		*/
		virtual bool			Update(float fElapsed);
		/*
		* 获取下注金钱
		*/
		virtual INT64			GetRandScore(INT64 nLeftJettonScore, BYTE nJettonArea);
		/*
		* 是否能下线
		*/
		virtual bool			CanOffline();
				/*
		* 获取下注门
		*/
		virtual BYTE			GetRandArea();
	public:
		/*
		* 更新上庄
		*/
		virtual bool			OnUpBankerRequest(float fElapsed);
		/*
		* 更新下庄
		*/
		virtual bool			OnDownBankerRequest();
		
		/*
		* 机器人重置
		*/
		virtual bool			OnReset();

		/*
		* 选择座位
		*/
		virtual	bool			OnSwitchTable();

		/*
		*游戏状态
		*/
		virtual bool			OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, 
			WORD wDataSize);
		
		/*
		*游戏消息
		*/
		virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, 
			WORD wDataSize=0);
		
		/*
		* 更新银行操作
		*/
		virtual bool			OnUpdateBank();

		/*
		*响应存钱
		*/
		virtual bool			OnBanker();

		/*
		*响应押注
		*/
		virtual bool			OnChipIn(float fElapsed);
		/*
		*更新在线时间
		*/
		virtual bool			OnUpdateTime(float fElapsed);
	protected:
		/*
		*响应申请上庄
		*/
		virtual	bool			OnApplyBanker(const void* pBuffer, WORD wDataSize);
		/*
		*切换庄家
		*/
		virtual bool			OnChangeBanker(const void* pBuffer, WORD wDataSize);
		/*
		*游戏开始
		*/
		virtual bool			OnGameStart(const void* pBuffer, WORD wDataSize);
		/*
		*金币更新
		*/
		virtual bool			OnGameScore(const void* pBuffer, WORD wDataSize);
		/*
		*游戏结束
		*/
		virtual bool			OnGameEnd(const void* pBuffer, WORD wDataSize);
		/*
		*押注开始
		*/
		virtual	bool			OnStartJetton(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubPlaceJetton(const void* pBuffer, WORD wDataSize);
		INT64					GetPutJettonScore(BYTE nArea);
	protected:
		// 当前庄家
		WORD					m_wCurBanker;
		double					m_fRequestTime;
		double					m_fElapsedTime;
		double					m_fAddChipTime;
		INT64					m_nReqBankerScore;
		INT64					m_nChipInScore;
		INT64					m_nBankerWinScore;
		BOOL					m_bChipIn;
		float					m_fChipTime;
		int						m_nPlaceRate;

		INT64					m_nBankerScore;

		__int64					m_lAllBigTigerScore;						//买大虎总注
		__int64					m_lAllSmlTigerScore;						//买小虎总注
		__int64					m_lAllBigBogScore;							//买大狗总注
		__int64					m_lAllSmlBogScore;							//买大狗总注
		__int64					m_lAllBigHorseScore;						//买大马总注
		__int64					m_lAllSmlHorseScore;						//买小马总注
		__int64					m_lAllBigSnakeScore;						//买大蛇总注
		__int64					m_lAllSmlSnakeScore;						//买小蛇总注
	};

	//////////////////////////////////////////////////////////////////////////
	// 小九机器人创建工厂
	//////////////////////////////////////////////////////////////////////////
	class SmallNineFactroy : public IAndroidFactroy
	{
	public:
		SmallNineFactroy(DWORD dwTypeID)
			: IAndroidFactroy(dwTypeID)
		{

		}
		
		virtual ~SmallNineFactroy()
		{

		}

		virtual IAndroid*		Create(const DWORD dwUserID, double fOnlineTime)
		{
			return new SmallNineAndroid(dwUserID, fOnlineTime);
		}
	};
}