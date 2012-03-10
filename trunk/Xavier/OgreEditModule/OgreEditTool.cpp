#include "stdafx.h"
#include "OgreEditTool.h"

namespace Ogre
{
	template<> EditTool*	Singleton<EditTool>::msSingleton = NULL;
	EditTool&	EditTool::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	EditTool*	EditTool::getSingletonPtr()
	{
		return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	EditTool::EditTool(void)
	{
	}

	EditTool::~EditTool(void)
	{
	}

	void				EditTool::registerEditorFactory(void* pDescribe, EditPluginFactroy* pPluginFactroy)
	{

	}

	void				EditTool::registerEditorFactory(EditPluginFactroy* pPluginFactroy)
	{
		StrPluginFactroy::iterator it = m_StrPluginFactroy.find(pPluginFactroy->getName());
		if ( it == m_StrPluginFactroy.end() )
		{
			m_StrPluginFactroy[pPluginFactroy->getName()] = pPluginFactroy;
		}
	}

	EditPluginFactroy*	EditTool::getEditorFactory(const String& sName)
	{
		StrPluginFactroy::iterator it = m_StrPluginFactroy.find(sName);
		if ( it != m_StrPluginFactroy.end() )
		{
			return m_StrPluginFactroy[sName];
		}

		return NULL;
	}
}
