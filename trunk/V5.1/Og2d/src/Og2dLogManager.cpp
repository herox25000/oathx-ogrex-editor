#include "Og2dLogManager.h"
#include "Og2dDebug.h"

namespace Og2d
{
	template<>	LogManager*	Singleton<LogManager>::mpSingleton = 0;
	/**
	 *
	 * \return 
	 */
	LogManager&		LogManager::getSingleton()
	{
		assert(mpSingleton != NULL); return (*mpSingleton);
	}

	/**
	 *
	 * \return 
	 */
	LogManager*		LogManager::getSingletonPtr()
	{
		assert(mpSingleton != NULL); return mpSingleton;
	}

	/**
	 *
	 * \param szDefaultLogName 
	 * \return 
	 */
	LogManager::LogManager(const String& szDefaultLogName, bool bAppend)
		: m_pDefaultLogFile(NULL)
	{
		m_pDefaultLogFile = createLogFile(szDefaultLogName,
			bAppend);
		assert(m_pDefaultLogFile != NULL);
	}

	/**
	 *
	 * \return 
	 */
	LogManager::~LogManager()
	{
		MapLogFile::iterator it = m_vLog.begin();
		while( it != m_vLog.end() )
		{
			delete it->second; it = m_vLog.erase(it);
		}

		m_pDefaultLogFile = NULL;
	}

	/**
	 *
	 * \param name 
	 * \param bApped 
	 * \return 
	 */
	Log*	LogManager::createLogFile(const String& name, bool bApped)
	{
		MapLogFile::iterator it = m_vLog.find(name);
		if ( it == m_vLog.end() )
		{
			/*
			* create log file and insert log manager
			*/
			Log* pLog = new Log(name, bApped);
			if (pLog)
			{
				m_vLog.insert(MapLogFile::value_type(name, pLog));
				return pLog;
			}
		}
		
		return NULL;
	}

	/**
	 *
	 * \param name 
	 */
	void	LogManager::removeLogFile(const String& name)
	{
		MapLogFile::iterator it = m_vLog.find(name);
		if ( it != m_vLog.end() )
		{
			// if the log file is default log
			if ( it->second == m_pDefaultLogFile)
			{
				m_pDefaultLogFile = NULL;
			}

			// delete log
			delete it->second; m_vLog.erase(it);
		}
	}

	/**
	 *
	 * \param pDefaultLog 
	 */
	void	LogManager::setDefaultLogFile(Log* pDefaultLog)
	{
		m_pDefaultLogFile = pDefaultLog;
	}

	/**
	 *
	 * \return 
	 */
	Log*	LogManager::getDefaultLogFile() const
	{
		return m_pDefaultLogFile;
	}

	/**
	 *
	 * \param lml 
	 * \param msg 
	 */
	void	LogManager::logMessage(LogMessageLevel lml, const String& msg)
	{
		if (m_pDefaultLogFile)
			m_pDefaultLogFile->logMessage(lml, msg);
	}
}