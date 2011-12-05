#pragma once

#include "Ogre.h"

class OgreEditorLogListener : public Ogre::LogListener
{
public:
	OgreEditorLogListener(void);
	virtual ~OgreEditorLogListener(void);

public:
	virtual void	messageLogged( const Ogre::String& message, 
		Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage );

private:
	int				m_nLine;
};
