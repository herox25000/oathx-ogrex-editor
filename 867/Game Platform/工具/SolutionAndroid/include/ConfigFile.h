#pragma once

namespace O2
{
	// 应用配置
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
		WORD						wTenMillionRate1;	//5千万-1亿
		WORD						wTenMillionRate2;	//1千万-5千万

		WORD						wMaxPlaceRate;

		WORD						wExtraRate1;
		WORD						wExtraRate2;
	};
	
	//////////////////////////////////////////////////////////////////////////
	// 配置文件
	//////////////////////////////////////////////////////////////////////////
	class ConfigFile
	{
	public:
		/*
		* 构造函数
		*/
		static ConfigFile&			GetSingleton()
		{
			static ConfigFile instance;
			return instance;
		}

	public:
		/*
		* 构造函数
		*/
		ConfigFile(void);
		/*
		* 析构函数
		*/		
		virtual ~ConfigFile(void);

		/*
		* 加载配置
		*/
		virtual	bool				LoadConfig(LPCTSTR lpszFilePath);
		/*
		* 保存配置
		*/
		virtual bool				SaveConfig(LPCTSTR lpszFilePath);
		/*
		* 设置配置信息
		*/
		virtual void				SetAppConfig(SAppConfig* pApp);
		/*
		* 获取配置信息
		*/		
		virtual SAppConfig*			GetAppConfig() const;
		/*
		* 获取配置文件
		*/	
		virtual CString				GetFilePath() const;
	protected:
		CString						m_szFilePath;
		SAppConfig*					m_pConfig;
	};
}
