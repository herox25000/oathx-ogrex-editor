#ifndef _____Og2dLogManager_H
#define _____Og2dLogManager_H

#include "Og2dSingleton.h"
#include "Og2dLog.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-28
	*
	* \Author  : lp
	*
	* \Desc    : 日志管理器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API LogManager : public Singleton<LogManager>
	{
		typedef map<String, Log*>::type	MapLogFile;
	public:
		/**
		 *
		 * \return 
		 */
		static	LogManager&			getSingleton();

		/**
		 *
		 * \return 
		 */
		static	LogManager*			getSingletonPtr();
	public:
		/**
		 *
		 * \param szDefaultLogName 
		 * \return 
		 */
		LogManager(const String& szDefaultLogName, bool bAppend);

		/**
		 *
		 * \return 
		 */
		virtual ~LogManager();

		/** 创建Log文件
		 *
		 * \param name		文件名
		 * \param bApped	是否连接
		 * \return 
		 */
		virtual	Log*				createLogFile(const String& name, bool bApped);
		
		/**
		 *
		 * \param name 
		 */
		virtual	void				removeLogFile(const String& name);

		/**
		 *
		 * \param pDefaultLog 
		 */
		virtual	void				setDefaultLogFile(Log* pDefaultLog);

		/**
		 *
		 * \return 
		 */
		virtual	Log*				getDefaultLogFile() const;

		/**
		 *
		 * \param lml 
		 * \param msg 
		 */
		virtual	void				logMessage(LogMessageLevel lml, const String& msg);
	protected:
		MapLogFile					m_vLog;
		Log*						m_pDefaultLogFile;
	};
}

#endif