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
	// С�Ż�����ʵ��
	//////////////////////////////////////////////////////////////////////////
	class SmallNineAndroid : public IAndroid
	{
	public:
		/*
		* ���캯��
		*/
		SmallNineAndroid(DWORD dwUserID, double fOnlineTime);
		/*
		* ��������
		*/		
		virtual ~SmallNineAndroid();
		
	public:
		/*
		* ��Ϸ����
		*/
		virtual bool			Update(float fElapsed);
		/*
		* ��ȡ��ע��Ǯ
		*/
		virtual INT64			GetRandScore(INT64 nLeftJettonScore, BYTE nJettonArea);
		/*
		* �Ƿ�������
		*/
		virtual bool			CanOffline();
				/*
		* ��ȡ��ע��
		*/
		virtual BYTE			GetRandArea();
	public:
		/*
		* ������ׯ
		*/
		virtual bool			OnUpBankerRequest(float fElapsed);
		/*
		* ������ׯ
		*/
		virtual bool			OnDownBankerRequest();
		
		/*
		* ����������
		*/
		virtual bool			OnReset();

		/*
		* ѡ����λ
		*/
		virtual	bool			OnSwitchTable();

		/*
		*��Ϸ״̬
		*/
		virtual bool			OnGameSceneMessage(BYTE cbGameStation, void * pBuffer, 
			WORD wDataSize);
		
		/*
		*��Ϸ��Ϣ
		*/
		virtual bool			OnGameMessage(WORD wSubCmdID, const void * pBuffer=NULL, 
			WORD wDataSize=0);
		
		/*
		* �������в���
		*/
		virtual bool			OnUpdateBank();

		/*
		*��Ӧ��Ǯ
		*/
		virtual bool			OnBanker();

		/*
		*��ӦѺע
		*/
		virtual bool			OnChipIn(float fElapsed);
		/*
		*��������ʱ��
		*/
		virtual bool			OnUpdateTime(float fElapsed);
	protected:
		/*
		*��Ӧ������ׯ
		*/
		virtual	bool			OnApplyBanker(const void* pBuffer, WORD wDataSize);
		/*
		*�л�ׯ��
		*/
		virtual bool			OnChangeBanker(const void* pBuffer, WORD wDataSize);
		/*
		*��Ϸ��ʼ
		*/
		virtual bool			OnGameStart(const void* pBuffer, WORD wDataSize);
		/*
		*��Ҹ���
		*/
		virtual bool			OnGameScore(const void* pBuffer, WORD wDataSize);
		/*
		*��Ϸ����
		*/
		virtual bool			OnGameEnd(const void* pBuffer, WORD wDataSize);
		/*
		*Ѻע��ʼ
		*/
		virtual	bool			OnStartJetton(const void* pBuffer, WORD wDataSize);
		virtual bool			OnSubPlaceJetton(const void* pBuffer, WORD wDataSize);
		INT64					GetPutJettonScore(BYTE nArea);
	protected:
		// ��ǰׯ��
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

		__int64					m_lAllBigTigerScore;						//�����ע
		__int64					m_lAllSmlTigerScore;						//��С����ע
		__int64					m_lAllBigBogScore;							//�����ע
		__int64					m_lAllSmlBogScore;							//�����ע
		__int64					m_lAllBigHorseScore;						//�������ע
		__int64					m_lAllSmlHorseScore;						//��С����ע
		__int64					m_lAllBigSnakeScore;						//�������ע
		__int64					m_lAllSmlSnakeScore;						//��С����ע
	};

	//////////////////////////////////////////////////////////////////////////
	// С�Ż����˴�������
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