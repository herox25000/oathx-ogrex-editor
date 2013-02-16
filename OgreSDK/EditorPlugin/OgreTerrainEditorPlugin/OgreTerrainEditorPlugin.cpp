#include "OgreTerrainEditorPluginStdAfx.h"
#include "OgreTerrainEditorPlugin.h"

namespace Ogre
{
	/**
	 *
	 * \param void 
	 * \return 
	 */
	TerrainEditorPlugin::TerrainEditorPlugin(void)
	{
		m_Name = String("EditorPlugin/TerrainEditor");
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	TerrainEditorPlugin::~TerrainEditorPlugin(void)
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	TerrainEditorPlugin::getName() const
	{
		return m_Name;
	}

	/**
	 *
	 */
	void			TerrainEditorPlugin::install()
	{
		EditorPluginFactoryManager::getSingletonPtr()->registerEditorPluginFactory(
			new TerrrainEditorFactory("Factory/EditorTerrainGroup"));
	}

	/**
	 *
	 */
	void			TerrainEditorPlugin::initialise()
	{
		
	}

	/**
	 *
	 */
	void			TerrainEditorPlugin::uninstall()
	{
		EditorPluginFactoryManager::getSingletonPtr()->unregisterEditorPluginFactory("Factory/EditorTerrainGroup");
	}

	/**
	 *
	 */
	void			TerrainEditorPlugin::shutdown()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	static TerrainEditorPlugin* gpTerrainEditorPlugin = NULL;
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStartPlugin( void )
	{
		gpTerrainEditorPlugin = new TerrainEditorPlugin();
		EditorSystem::getSingletonPtr()->installPlugin(gpTerrainEditorPlugin);
	}

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStopPlugin( void )
	{
		EditorSystem::getSingletonPtr()->uninstallPlugin(gpTerrainEditorPlugin);
		if (gpTerrainEditorPlugin != NULL)
			delete gpTerrainEditorPlugin;

		gpTerrainEditorPlugin = NULL;
	}
}