#pragma once

namespace O2
{
	// Ӧ������
	struct SAppConfig
	{
		char						chIPAddrss[32];
		WORD						wPort;
		char						chMD5[128];
		DWORD						dwStartID;
		DWORD						dwEndID;
		DWORD						dwOnline;
		WORD						wMaxDeque;
		WORD						wMaxUpBanker;
		INT64						nMaxWinScore;
		WORD						wMinTime;
		WORD						wMaxTime;
		WORD						wMinPlaceTime;
		WORD						wMaxPlaceTime;
		INT64						nMinScore;
		INT64						nMaxScore;
		WORD						wPlaceRate;

		WORD						wShunMenRate;
		WORD						wTianMenRate;
		WORD						wDaoMenRate;
		WORD						wZuoJiaoRate;
		WORD						wYouJiaoRate;
		WORD						wQiaoRate;

		WORD						wHunMillionRate;
		WORD						wTenMillionRate1;	//5ǧ��-1��
		WORD						wTenMillionRate2;	//1ǧ��-5ǧ��

		WORD						wMaxPlaceRate;

		WORD						wExtraRate1;
		WORD						wExtraRate2;
	};
	
	//////////////////////////////////////////////////////////////////////////
	// �����ļ�
	//////////////////////////////////////////////////////////////////////////
	class ConfigFile
	{
	public:
		/*
		* ���캯��
		*/
		static ConfigFile&			GetSingleton()
		{
			static ConfigFile instance;
			return instance;
		}

	public:
		/*
		* ���캯��
		*/
		ConfigFile(void);
		/*
		* ��������
		*/		
		virtual ~ConfigFile(void);

		/*
		* ��������
		*/
		virtual	bool				LoadConfig(LPCTSTR lpszFilePath);
		/*
		* ��������
		*/
		virtual bool				SaveConfig(LPCTSTR lpszFilePath);
		/*
		* ����������Ϣ
		*/
		virtual void				SetAppConfig(SAppConfig* pApp);
		/*
		* ��ȡ������Ϣ
		*/		
		virtual SAppConfig*			GetAppConfig() const;
		/*
		* ��ȡ�����ļ�
		*/	
		virtual CString				GetFilePath() const;
	protected:
		CString						m_szFilePath;
		SAppConfig*					m_pConfig;
	};
}
