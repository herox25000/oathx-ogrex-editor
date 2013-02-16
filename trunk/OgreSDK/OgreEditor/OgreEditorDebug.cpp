#include "StdAfx.h"
#include "OgreEditorDebug.h"
#include "MainFrm.h"

namespace Ogre
{
	/**
	 *
	 * \param void 
	 * \return 
	 */
	EditorDebug::EditorDebug(void)
		:m_nLine(0)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	EditorDebug::~EditorDebug(void)
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
	void EditorDebug::messageLogged( const Ogre::String& message, 
													 Ogre::LogMessageLevel lml, 
													 bool maskDebug, 
													 const Ogre::String &logName, 
													 bool& skipThisMessage )
	{
		String debugMessage;

		m_nLine ++;

		char szTmp[32];
		sprintf(szTmp, "%d> ", m_nLine);
		debugMessage = debugMessage + szTmp + message;
		m_DequeString.push_back(debugMessage);

		while (!m_DequeString.empty())
		{
			CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
			if (pMainFrame == NULL)
				break;

			debugMessage = m_DequeString.front();
			switch (lml)
			{
			case LML_TRIVIAL:
				pMainFrame->AddDebugMessage(debugMessage.c_str(), RGB(0, 0, 255));
				break;
			case LML_NORMAL:
				pMainFrame->AddDebugMessage(debugMessage.c_str(), RGB(0, 0, 0));
				break;
			case LML_CRITICAL:
				pMainFrame->AddDebugMessage(debugMessage.c_str(), RGB(255, 0, 0));
				break;
			}
			m_DequeString.pop_front();
		}
	}
}

