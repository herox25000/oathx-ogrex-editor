#include "Og2dLog.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param void 
	 * \return 
	 */
	Log::Log(void)
		: m_pLogFile(NULL),m_szFileName(NULL),m_nLev(INFO_NORMAL)
	{
		memset(m_logFileBuffer,0, sizeof(m_logFileBuffer));
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	Log::~Log(void)
	{
		// clear log listener
		VectorLogListener::iterator it = m_vLog.begin();
		while( it != m_vLog.end() )
		{
			delete (*it); it = m_vLog.erase(it);
		}

		// write end
		if(m_pLogFile)
		{
			char szBuffer[128];
			strcpy(szBuffer, "</body></html>\n");
			fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
			fclose(m_pLogFile);
		}
	}

	/**
	 *
	 * \param strLogFileName 
	 * \param isAppend/* 
	 * \return 
	 */
	Log::Log(const String& szLogFileName, bool isAppend/* =true */)
		:m_pLogFile(NULL),m_szFileName(szLogFileName),m_nLev(INFO_NORMAL)
	{
		memset(m_logFileBuffer,0, sizeof(m_logFileBuffer));
		createLogFile(szLogFileName,isAppend);
	}

	/**
	 *
	 * \param strFileName 
	 * \param isAppend/* 
	 * \return 
	 */
	bool	Log::createLogFile(const String& szFileName, bool isAppend/* =true */)
	{
		if(szFileName.empty()) return 0;

		if(m_pLogFile)
		{
			fclose(m_pLogFile);
			m_pLogFile = NULL;
		}
		if(isAppend)
		{
			m_pLogFile = fopen(szFileName.c_str(), "a+");
			if(m_pLogFile==NULL)
			{
				printf("Open file failed!<Log::StartLog>\n");
				return 0;
			}
			fseek(m_pLogFile, 0, SEEK_END);
			unsigned filesize = ftell(m_pLogFile);
			fseek(m_pLogFile, 0, SEEK_SET);
			if(filesize >= MAXLOGFILESIZE)
			{
				fclose(m_pLogFile);
				m_pLogFile = fopen(szFileName.c_str(), "w");
				if(m_pLogFile==NULL)
				{
					printf("Open file failed!<Log::StartLog>\n");
					return 0;
				}
			}
		}
		else
		{
			m_pLogFile = fopen(szFileName.c_str(), "w");
			if(m_pLogFile==NULL)
			{
				printf("Open file failed!<Log::StartLog>\n");
				return 0;
			}
		}

		char szBuffer[128];
		char szCurTime[32];
		char szCurDate[32];

		_strtime(szCurTime);
		_strdate(szCurDate);

		strcpy(szBuffer, "<html><head><title>Log File</title></head><body>\n");
		fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
		sprintf(szBuffer, "============================================================================</br>\r\n", szCurDate, szCurTime);
		fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
		sprintf(szBuffer, "= Og2d Engine															  =</br>\r\n", szCurDate, szCurTime);
		fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
		sprintf(szBuffer, "= Copyright (c) 2012 lp All rights reserved.  =</br>\r\n", szCurDate, szCurTime);
		fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
		sprintf(szBuffer, "============================================================================</br>\r\n", szCurDate, szCurTime);
		fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);

		strcpy(szBuffer, "<font face=\"Arial\" size=\"4\" color=\"#ff0000\"><b><u>");
		fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
		sprintf(szBuffer, "Log File Create At [%s %s]</u></b></font><br>\r\n", szCurDate, szCurTime);
		fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);

		fflush(m_pLogFile);

		return true;
	}
	
	/**
	 *
	 * \param pListener 
	 */
	void		Log::addListener(LogListener* pListener)
	{
		VectorLogListener::iterator it = find(m_vLog.begin(), m_vLog.end(), pListener);
		if ( it == m_vLog.end() )
			m_vLog.push_back(pListener);
	}

	/**
	 *
	 * \param pListener 
	 */
	void		Log::removeListener(LogListener* pListener)
	{
		VectorLogListener::iterator it = find(m_vLog.begin(), m_vLog.end(), pListener);
		if ( it != m_vLog.end() )
		{
			delete (*it); m_vLog.erase(it);
		}
	}


	/**
	 *
	 * \param level 
	 * \param msg 
	 * \param ... 
	 * \return 
	 */
	void		Log::logMessage(LogMessageLevel lml, const String& msg)
	{
		int pos = 0;
			
		// warite current tiem
		char szTime[32];
		_strtime(szTime);
		pos += sprintf(m_logFileBuffer+pos, "[%s]", szTime);

		// parse param
		va_list args;
		va_start(args, msg);
		pos += _vsnprintf(m_logFileBuffer+pos, LOGBUFFERSIZE-30, msg.c_str(), args);
		va_end(args);

		// send log message
		for (VectorLogListener::iterator it=m_vLog.begin(); it!=m_vLog.end(); it++)
			(*it)->messageLogged(m_logFileBuffer, lml, m_szFileName);

		printf("%s\n", m_logFileBuffer);

		char szBuffer[128];
		switch (lml)
		{
		case INFO_ERROR:
			{
				m_logFileBuffer[pos] = '\0';

				if(m_pLogFile)
				{
					strcpy(szBuffer, "<font face=\"Arial\" size=\"2\" color=\"#ff0000\">");
					fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
					strcpy(&m_logFileBuffer[pos], "</font><br>\r\n");
					fwrite(m_logFileBuffer, strlen(m_logFileBuffer), 1, m_pLogFile);
				}
			}
			break;
		case INFO_WARNING:
			{
				m_logFileBuffer[pos] = '\r';
				m_logFileBuffer[pos+1] = '\n';
				m_logFileBuffer[pos+2] = '\0';

				if(m_nLev <= INFO_WARNING && m_pLogFile)
				{
					strcpy(szBuffer, "<font face=\"Arial\" size=\"2\" color=\"#0000ff\">");
					fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
					strcpy(&m_logFileBuffer[pos], "</font><br>\r\n");
					fwrite(m_logFileBuffer, strlen(m_logFileBuffer), 1, m_pLogFile);
				}
			}
			break;
		case INFO_NORMAL:
			{
				if(m_nLev <= INFO_NORMAL && m_pLogFile)
				{
					strcpy(szBuffer, "<font face=\"Arial\" size=\"2\" color=\"#ff00ff\">");
					fwrite(szBuffer, strlen(szBuffer), 1, m_pLogFile);
					strcpy(&m_logFileBuffer[pos], "</font><br>\r\n");
					fwrite(m_logFileBuffer, strlen(m_logFileBuffer), 1, m_pLogFile);
				}
			}
		}
	
		fflush(m_pLogFile);
	}


	/**
	 *
	 * \return 
	 */
	int				Log::getLogLevel() const
	{
		return m_nLev;
	}

	/**
	 *
	 * \param level 
	 */
	void			Log::setLogLevel(int level)
	{
		m_nLev = level;
	}

	/**
	 *
	 * \return 
	 */
	bool			Log::isOpen() const
	{
		return m_pLogFile != NULL;
	}

	/**
	 *
	 * \return 
	 */
	const String&	Log::getLogFileName() const
	{
		return m_szFileName;
	}
}