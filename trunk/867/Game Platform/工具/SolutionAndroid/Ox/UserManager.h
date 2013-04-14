#pragma once

namespace O2
{
	// ��������Ϣ�ṹ
	struct SUser
	{
		DWORD		dwUserID;			//���ID
		BYTE		cbUserStatus;		//��Ϸ״̬
		WORD		wTableID;			//����ID
		WORD		wChairID;			//����ID
		TCHAR		szName[32];			//�������
		INT64		nScore;				//�û�����
		DWORD		dwGameID;			//��ϷID
		INT64		nWinScore;			//Ӯȡ����
		char		chLoginTime[128];	//��¼ʱ��
		DWORD		wBankerCount;		//��ׯ����
		WORD		wCurUpBanker;		//��ǰ��ׯ����
		INT64		nBankerCurWin;		//ׯ�ҵ�ǰ�ɼ�
		INT64		nBankerAllWin;		//ׯ�����гɼ�
		INT64		nSaveScore;
		INT64		nGetScore;

		SUser()
			: dwUserID(0), dwGameID(0), nScore(0), wTableID(INVALID_TABLE), wChairID(INVALID_CHAIR), cbUserStatus(US_NULL),wBankerCount(0),nWinScore(0)
		{
			chLoginTime[0]	= '\0';
			wCurUpBanker	= 0;
			nBankerCurWin	= 0;
			nBankerAllWin	= 0;
			nGetScore		= 0;
			nSaveScore		= 0;
		}
	};

	// �û�ӳ���
	typedef std::map<DWORD, SUser*>	UserRegister;

	//////////////////////////////////////////////////////////////////////////
	// ��������Ϣ������
	//////////////////////////////////////////////////////////////////////////
	class UserManager
	{
	public:
		/*
		* ���캯��
		*/
		UserManager(void);
		
		/*
		* ��������
		*/		
		virtual ~UserManager(void);

		/*
		* ����û�
		*/
		virtual void			Add(SUser* pUser);
		/*
		* �Ƴ��û�
		*/
		virtual void			Remove(DWORD dwUserID, bool bDestroy=true);
		/*
		* ���û�ID����
		*/		
		virtual SUser*			Search(DWORD dwID, bool bGameID=0);
		/*
		* ���û�������
		*/		
		virtual SUser*			Search(LPCTSTR lpszName);
		/*
		* �ɽ�ɫID����
		*/		
		virtual SUser*			Search(WORD wCharID);
		/*
		* �������н�ɫ
		*/		
		virtual void			Clear(bool bDestroy=true);
	protected:
		UserRegister			m_UserRegister;
	};
}

