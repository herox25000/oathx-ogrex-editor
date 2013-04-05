#pragma once

namespace O2
{
	// ��������Ϣ�ṹ
	struct SUser
	{
		DWORD		dwUserID;		//���ID
		BYTE		cbUserStatus;	//��Ϸ״̬
		WORD		wTableID;		//����ID
		WORD		wChairID;		//����ID
		TCHAR		szName[32];		//�������
		INT64		nScore;			//�û�����
		DWORD		dwGameID;		//��ϷID

		SUser()
			: dwUserID(0), dwGameID(0), nScore(0), wTableID(INVALID_TABLE), wChairID(INVALID_CHAIR), cbUserStatus(US_NULL)
		{

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

