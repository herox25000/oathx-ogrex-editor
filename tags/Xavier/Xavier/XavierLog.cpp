#include "StdAfx.h"
#include "XavierLog.h"
#include "MainFrm.h"

using namespace Ogre;

/**
 *
 * \param void 
 * \return 
 */
XavierLog::XavierLog(void)
:m_nLine(0)
{
}

/**
 *
 * \param void 
 * \return 
 */
XavierLog::~XavierLog(void)
{
}

/**
 *
 * \param message 
 * \param lml 
 * \param maskDebug 
 * \param &logName 
 * \param skipThisMessage 
 */
void XavierLog::messageLogged( const Ogre::String& message, 
												 Ogre::LogMessageLevel lml, 
												 bool maskDebug, 
												 const Ogre::String &logName, 
												 bool& skipThisMessage )
{
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		Ogre::String msg;
		
		m_nLine ++;

		char szTmp[32];
		sprintf(szTmp, "%d> ", m_nLine);
		msg = msg + szTmp + message;

		switch (lml)
		{
		case Ogre::LML_TRIVIAL:
			pMainFrame->OutputLogMessage(msg.c_str(), RGB(192, 192, 192));
			break;
		case Ogre::LML_NORMAL:
			pMainFrame->OutputLogMessage(msg.c_str(), RGB(0, 0, 0));
			break;
		case Ogre::LML_CRITICAL:
			pMainFrame->OutputLogMessage(msg.c_str(), RGB(255, 0, 0));
			break;
		}
	}
}
