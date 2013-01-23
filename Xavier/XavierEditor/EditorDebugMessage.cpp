#include "StdAfx.h"
#include "EditorDebugMessage.h"
#include "MainFrm.h"

/**
 *
 * \param void 
 * \return 
 */
EditorDebugMessage::EditorDebugMessage(void)
:m_nLine(0)
{
}

/**
 *
 * \param void 
 * \return 
 */
EditorDebugMessage::~EditorDebugMessage(void)
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
void EditorDebugMessage::messageLogged( const Ogre::String& message, 
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
			pMainFrame->AddLogMessage(msg.c_str(), RGB(192, 192, 192));
			break;
		case Ogre::LML_NORMAL:
			pMainFrame->AddLogMessage(msg.c_str(), RGB(0, 0, 0));
			break;
		case Ogre::LML_CRITICAL:
			pMainFrame->AddLogMessage(msg.c_str(), RGB(255, 0, 0));
			break;
		}
	}
}
