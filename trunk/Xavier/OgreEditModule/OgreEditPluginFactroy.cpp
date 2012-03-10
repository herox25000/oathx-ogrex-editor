#include "stdafx.h"
#include "OgreEditPluginFactroy.h"

namespace Ogre
{
	EditPluginFactroy::EditPluginFactroy(void)
	{
	}

	EditPluginFactroy::~EditPluginFactroy(void)
	{
	}

	void		EditPluginFactroy::setName(const String& sName)
	{
		m_sName = sName;
	}

	String		EditPluginFactroy::getName() const
	{
		return m_sName;
	}
}
