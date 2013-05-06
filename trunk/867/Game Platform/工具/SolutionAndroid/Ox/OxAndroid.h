#pragma once

#include "IAndroid.h"

namespace O2
{
	//��ֵ����
#define	LOGIC_MASK_COLOR			0xF0								//��ɫ����
#define	LOGIC_MASK_VALUE			0x0F								//��ֵ����

#define MAX_COUNT					5
#define MIN_CHAIR_COUNT				2
#define MAX_WAIT_TIME				60

	//�˿�����
#define OX_VALUE0					0									//�������
#define OX_THREE_SAME				12									//��������
#define OX_FOUR_SAME				13									//��������
#define OX_FOURKING					14									//��������
#define OX_FIVEKING					15									//��������

	struct STimerItem
	{
		DWORD						dwID;
		float						fElapsed;
		BOOL						bActive;

		STimerItem(DWORD id, float fTime, BOOL bInvalid)
			: dwID(id), fElapsed(fTime), bActive(bInvalid)
		{

		}
	};
	
	typedef std::map<DWORD, STimerItem*> TimerItemRegister;

	struct SDesk{
		WORD						wChairID[4];
		WORD						wTableID;
		BYTE						bPlayStatus;
		BYTE						bTableLock;

		SDesk()
			: wTableID(INVALID_TABLE)
		{
			for (int i=0; i<4; i++)
			{
				wChairID[i] = INVALID_CHAIR;
			}

			bPlayStatus	= FALSE;
			bTableLock	= FALSE;
		}
	};

	//////////////////////////////////////////////////////////////////////////
	// ţţ������
	//////////////////////////////////////////////////////////////////////////
	class Ox : public IAndroid
	{
	public:
		// ���캯��
		Ox(DWORD dwUserID, double fOnlineTime);
		// ��������
		virtual ~Ox();
		
	public:
		// �����Ը���
		virtual bool			Update(float fElapsed);

	public:
		//��ȡ����
		virtual BYTE			GetCardType(BYTE cbCardData[], BYTE cbCardCount);
		//��ȡ��ֵ
		virtual BYTE			GetCardValue(BYTE cbCardData);
		//��ȡ��ɫ
		virtual BYTE			GetCardColor(BYTE cbCardData);
		//�߼���ֵ
		virtual BYTE			GetCardLogicValue(BYTE cbCardData);
		//��ȡ����ʱ��
		virtual WORD			GetWorkTime();
		//��ȡ����ID
		virtual bool			GetTableID(WORD& wTableID, WORD& wChairID);
	protected:
		/*
		* ���۷�����Ϣ
		*/
		virtual bool			OnSocketServerInfo(CMD_Command Command, void* pBuffer, 
			WORD wDataSize);
		/*
		* ���۷�����Ϣ
		*/
		virtual bool			OnGameStatus(CMD_Command Command, void* pBuffer, WORD wDataSize);

		/*
		* ���û���������
		*/	
		virtual bool			OnReset();

		/*
		* ѡ��������Ϣ
		*/	
		virtual bool			OnSwitchTable();

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
		*��Ӧ����
		*/
		virtual bool			OnBanker();
		/*
		*��Ϸ��Ϣ
		*/
		virtual bool			OnTimerEvent(DWORD dwID);
		/*
		*��������ʱ��
		*/
		virtual bool			UpdateOnline(float fElapsed);
		virtual bool			OnChange(float fElapsed);
	protected:
		//�û���ׯ
		virtual bool			OnSubCallBanker(const void * pBuffer, WORD wDataSize);
		//��Ϸ��ʼ
		virtual bool			OnSubGameStart(const void * pBuffer, WORD wDataSize);
		//�û���ע
		virtual bool			OnSubAddScore(const void * pBuffer, WORD wDataSize);
		//������Ϣ
		virtual bool			OnSubSendCard(const void * pBuffer, WORD wDataSize);
		//�û�̯��
		virtual bool			OnSubOpenCard(const void * pBuffer, WORD wDataSize);
		//�û�ǿ��
		virtual bool			OnSubPlayerExit(const void * pBuffer, WORD wDataSize);
		//��Ϸ����
		virtual bool			OnSubGameEnd(const void * pBuffer, WORD wDataSize);
		
	protected:
		//���ö�ʱ��
		virtual bool			SetTimer(DWORD dwID, double fElapsed);
		//ɾ����ʱ��
		virtual bool			KillTimer(DWORD dwID);
		//���¶�ʱ��
		virtual void			UpdateTimer(float fElapsed);
	protected:
		WORD					m_wTableCount;
		WORD					m_wChairCount;
		TimerItemRegister		m_TimerItemActive;
		INT64					m_nTurnMaxScore;
		BYTE					m_byCard[MAX_COUNT];
		WORD					m_wCurBanker;
		BOOL					m_bOffline;
		SDesk*					m_pDesk;
		float					m_fWaitTime;
	};

	class OxFactory : public IAndroidFactroy
	{
	public:
		OxFactory(DWORD dwTypeID)
			: IAndroidFactroy(dwTypeID)
		{

		}

		virtual ~OxFactory()
		{

		}

		virtual IAndroid*		Create(const DWORD dwUserID, double fOnlineTime)
		{
			return new Ox(dwUserID, fOnlineTime);
		}
	};
}
