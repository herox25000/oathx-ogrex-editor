#ifndef _____Og2dLog_H
#define _____Og2dLog_H

#include "Og2dTypes.h"
#include <time.h>
#include <stdarg.h>

namespace Og2d
{
	/*<文件缓冲区>*/
	const unsigned int LOGBUFFERSIZE = 1024;

	/*<最大文件字节数>*/
	const unsigned int MAXLOGFILESIZE = 1024*1024;

	//! 定一log等级
	enum LogMessageLevel
	{
		INFO_NORMAL		= 0x00000001,
		INFO_WARNING	= 0x00000002,
		INFO_ERROR		= 0x00000003
	};

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
    * \Desc    : 
    *
    * \bug     : 
    *
    * \Copyright (c) 2012 lp All rights reserved.
    */
    class Og2d_Export_API LogListener
    {
	public:
        /**
         *
         * \return 
         */
        virtual ~LogListener() {}

        /**
         *
         * \param message 
         * \param lml 
         * \param &logName 
         */
        virtual void messageLogged(const String& message, LogMessageLevel lml,
			const String &logName ) = 0;
    };

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Log
	{
		// log listener
		typedef vector<LogListener*>::type	VectorLogListener;
	public:
		/**
		 *
		 * \return 
		 */
		Log();

		/**
		 *
		 * \param logFileName 
		 * \param isAppend 
		 * \return 
		 */
		Log(const String& szFileName, bool isAppend=true);

		/** 
		*
		* \return 
		*/
		virtual ~Log();

		/** 打开文件
		*
		* \param strFileName 文件名，可用html格式
		* \param isAppend 是否连接到上次的输出
		* \return 
		*/
		virtual bool			createLogFile(const String& szFileName, bool isAppend=true);

		/**
		 *
		 * \param pListener 
		 */
		virtual	void			addListener(LogListener* pListener);

		/**
		 *
		 * \param pListener 
		 */
		virtual	void			removeListener(LogListener* pListener);

		/** 写入信息到文件
		*
		* \param level 信息等级
		* \param msg   写入的信息
		* \param ...   
		* \return 
		*/
		virtual void			logMessage(LogMessageLevel lml, const String& msg);

		/** 获取log等级
		*
		* \return 
		*/
		virtual int				getLogLevel() const;

		/** 设置long等级
		*
		* \param level 
		*/
		virtual void			setLogLevel(int nLev); 

		/** 是否已经打开
		*
		* \return 
		*/
		virtual bool			isOpen() const;

		/** 获取log文件名
		*
		* \return 
		*/
		virtual const String&	getLogFileName() const;
	protected:
		FILE*					m_pLogFile;
		char					m_logFileBuffer[LOGBUFFERSIZE];
		String					m_szFileName;
		int						m_nLev;
		VectorLogListener		m_vLog;
	};
}

#endif