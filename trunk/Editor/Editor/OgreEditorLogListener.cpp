#include "StdAfx.h"
#include "OgreEditorLogListener.h"
#include "MainFrm.h"

using namespace Ogre;

OgreEditorLogListener::OgreEditorLogListener(void)
:m_nLine(0)
{
}

OgreEditorLogListener::~OgreEditorLogListener(void)
{
}

void OgreEditorLogListener::messageLogged( const Ogre::String& message, 
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
		msg += szTmp;

		COLORREF dwTextColour = 0;
		switch (lml)
		{
		case Ogre::LML_TRIVIAL:
			dwTextColour = RGB(192, 192, 192);
			break;
		case Ogre::LML_NORMAL:
			dwTextColour = RGB(0, 0, 0);
			break;
		case Ogre::LML_CRITICAL:
			dwTextColour = RGB(255,0, 0);
			break;
		}
		
		msg += message;

		pMainFrame->GetOutputWnd()->GetBuildLogListWindow()->AddString(msg.c_str(), dwTextColour);
	}
}
