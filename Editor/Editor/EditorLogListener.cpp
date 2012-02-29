#include "StdAfx.h"
#include "EditorLogListener.h"
#include "MainFrm.h"

using namespace Ogre;

EditorLogListener::EditorLogListener(void)
:m_nLine(0)
{
}

EditorLogListener::~EditorLogListener(void)
{
}

void EditorLogListener::messageLogged( const Ogre::String& message, 
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
			pMainFrame->GetOutputWnd()->GetBuildLogListWindow()->AddString(msg.c_str(), RGB(192, 192, 192));
			break;
		case Ogre::LML_NORMAL:
			pMainFrame->GetOutputWnd()->GetBuildLogListWindow()->AddString(msg.c_str(), RGB(0, 0, 0));
			break;
		case Ogre::LML_CRITICAL:
			pMainFrame->GetOutputWnd()->GetBuildLogListWindow()->AddString(msg.c_str(), RGB(255, 0, 0));
			break;
		}
	}
}
