#include "StdAfx.h"
#include "OgreEditorLogListener.h"
#include "MainFrm.h"

using namespace Ogre;

OgreEditorLogListener::OgreEditorLogListener(void)
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
		Ogre::String msg("");

		switch (lml)
		{
		case Ogre::LML_TRIVIAL:
			msg += "LML_TRIVIAL::";
			break;
		case Ogre::LML_NORMAL:
			msg += "LML_NORMAL::";
			break;
		case Ogre::LML_CRITICAL:
			msg += "LML_CRITICAL::";
			break;
		}
		
		msg += message;

		pMainFrame->GetOutputWnd()->GetBuildLogListWindow()->AddString(msg.c_str());
	}
}
