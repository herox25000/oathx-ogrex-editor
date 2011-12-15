#include "OgreExplorerPlugin.h"
#include "OgreExplorerPrerequisites.h"
#include "OgreRoot.h"

#ifndef OGRE_STATIC_LIB

namespace Ogre
{
	const String ms_PluginName = "Explorer Plugin Factory";

	//////////////////////////////////////////////////////////////////////////
	ExplorerPlugin::ExplorerPlugin(void)
		:m_pExplorerManager(NULL)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	ExplorerPlugin::~ExplorerPlugin(void)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	const String&	ExplorerPlugin::getName() const
	{
		return ms_PluginName;
	}

	//////////////////////////////////////////////////////////////////////////
	void			ExplorerPlugin::install()
	{
		m_pExplorerManager = new ExplorerManager();
		ExplorerManager::getSingleton().create("a","s");
	}

	//////////////////////////////////////////////////////////////////////////
	void			ExplorerPlugin::initialise()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void			ExplorerPlugin::shutdown()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void			ExplorerPlugin::uninstall()
	{
		if (m_pExplorerManager != NULL)
		{
			delete m_pExplorerManager;
			m_pExplorerManager = NULL;
		}
	}

	ExplorerPlugin* plugin;

	//-----------------------------------------------------------------------
	extern "C" void _OgreExplorerExport dllStartPlugin(void) throw()
	{
		plugin = OGRE_NEW ExplorerPlugin();
		Root::getSingleton().installPlugin(plugin);
	}

	//-----------------------------------------------------------------------
	extern "C" void _OgreExplorerExport dllStopPlugin(void)
	{
		Root::getSingleton().uninstallPlugin(plugin);
		OGRE_DELETE plugin;
	}
}

#endif