#pragma once

namespace O2
{
#define  CARD_COUNT 5
	// ��������Ϣ�ṹ
	struct SUser
	{
		DWORD		dwUserID;				//���ID
		BYTE		cbUserStatus;			//��Ϸ״̬
		WORD		wTableID;				//����ID
		WORD		wChairID;				//����ID
		TCHAR		szName[32];				//�������
		INT64		nScore;					//�û�����
		DWORD		dwGameID;				//��ϷID
		INT64		nWinScore;				//Ӯȡ����
		char		chLoginTime[128];		//��¼ʱ��
		INT64		nSaveScore;
		INT64		nGetScore;
		BYTE		cbObscureCard;			//�����˿�
		BYTE		cbCardData[CARD_COUNT];	//�û��˿�

		SUser()
			: dwUserID(0), dwGameID(0), nScore(0), wTableID(INVALID_TABLE), wChairID(INVALID_CHAIR), cbUserStatus(US_NULL),nWinScore(0)
		{
			chLoginTime[0]	= '\0';
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
		* ��ȡͬһ���ӵ�������
		*/	
		virtual WORD			GetTableChairCount(WORD wTableID);
		/*
		* ��ȡ���ӵĿ�λ��
		*/	
		virtual WORD			GetEmptyChairID(WORD wTableID);
		/*
		* �������н�ɫ
		*/		
		virtual void			Clear(bool bDestroy=true);
	protected:
		UserRegister			m_UserRegister;
	};
}

