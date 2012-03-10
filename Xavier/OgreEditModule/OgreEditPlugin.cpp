#include "stdafx.h"
#include "OgreEditPlugin.h"

namespace Ogre
{
	EditPlugin::EditPlugin(void)
	{
	}

	EditPlugin::~EditPlugin(void)
	{
	}

	void		EditPlugin::setName(const String& sName)
	{
		m_sName = sName;
	}

	String		EditPlugin::getName() const
	{
		return m_sName;
	}

}
