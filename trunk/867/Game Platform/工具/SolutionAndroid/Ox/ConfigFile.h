#pragma once

namespace O2
{
	// Ӧ������
	struct SAppConfig
	{
		char						chIPAddrss[32];
		WORD						wPort;
		char						chMD5[128];
		
		DWORD						dwOneStartID;
		DWORD						dwOneEndID;

		DWORD						dwTwoStartID;
		DWORD						dwTwoEndID;

		DWORD						dwThreeStartID;
		DWORD						dwThreeEndID;


		DWORD						dwOnline;
		WORD						wBankerRate;
		INT64						nMaxWinScore;
		WORD						wMinTime;
		WORD						wMaxTime;
		WORD						wMinWorkTime;
		WORD						wMaxWorkTime;
		INT64						nMinScore;
		INT64						nMaxScore;
		WORD						wPlaceRate;

		WORD						wOneMinID;
		WORD						wOneMaxID;
		INT64						nOneMinScore;
		INT64						nOneMaxScore;

		WORD						wTwoMinID;
		WORD						wTwoMaxID;
		INT64						nTwoMinScore;
		INT64						nTwoMaxScore;

		WORD						wThreeMinID;
		WORD						wThreeMaxID;
		INT64						nThreeMinScore;
		INT64						nThreeMaxScore;
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
