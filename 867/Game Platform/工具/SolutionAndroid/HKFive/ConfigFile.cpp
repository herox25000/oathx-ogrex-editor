#include "StdAfx.h"
#include "ConfigFile.h"

namespace O2
{
	//////////////////////////////////////////////////////////////////////////
	ConfigFile::ConfigFile(void)
	{
		m_pConfig = new SAppConfig;
	}

	//////////////////////////////////////////////////////////////////////////
	ConfigFile::~ConfigFile(void)
	{
		delete m_pConfig;
	}
	
	//////////////////////////////////////////////////////////////////////////
	bool		ConfigFile::LoadConfig(LPCTSTR lpszFilePath)
	{
		FILE* pFile	= fopen(lpszFilePath, "r+");
		if (pFile == NULL)
		{
			AfxMessageBox("找不到配置文件");
			return 0;
		}

		m_szFilePath = lpszFilePath;

		fread(m_pConfig, 1, sizeof(SAppConfig), pFile);
		fclose(pFile);

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void		ConfigFile::SetAppConfig(SAppConfig* pApp)
	{
		if (pApp)
		{
			memcpy(m_pConfig, pApp, 
				sizeof(SAppConfig));
		}
	}

	//////////////////////////////////////////////////////////////////////////
	SAppConfig*	ConfigFile::GetAppConfig() const
	{
		return m_pConfig;
	}
	
	//////////////////////////////////////////////////////////////////////////
	CString		ConfigFile::GetFilePath() const
	{
		return m_szFilePath;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		ConfigFile::SaveConfig(LPCTSTR lpszFilePath)
	{
		CString szFilePath = lpszFilePath ? lpszFilePath : m_szFilePath;
		if (szFilePath.IsEmpty())
			szFilePath = ".\\HKFiveAndroid.Config";

		FILE* pFile	= fopen(szFilePath, "w+");
		if (pFile == NULL)
		{
			AfxMessageBox("找不到配置文件");
			return 0;
		}

		m_szFilePath = szFilePath;
	
		fwrite(m_pConfig, 1, sizeof(SAppConfig), pFile);
		fclose(pFile);

		return true;
	}
}
