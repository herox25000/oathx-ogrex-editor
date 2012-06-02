#include "OgreTerrainPluginPrerequisites.h"
#include "OgreTerrainPlugin.h"
#include "OgreSystem.h"
#include "OgreServerTerrainPage.h"
#include "OgreServerTerrainGroup.h"


namespace Ogre
{
	const String	TerrainPlugin::TerrainPluginName = "TerrainPlugin";

	/**
	 *
	 * \param void 
	 * \return 
	 */
	TerrainPlugin::TerrainPlugin(void)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	TerrainPlugin::~TerrainPlugin(void)
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	TerrainPlugin::getName() const
	{
		return TerrainPlugin::TerrainPluginName;
	}

	/**
	 *
	 */
	void			TerrainPlugin::install()
	{
		System::getSingletonPtr()->registerServerFactory(new TerrainPageServerFactory());
		System::getSingletonPtr()->registerServerFactory(new TerrainGroupServerFactory());
	}

	/**
	 *
	 */
	void			TerrainPlugin::initialise()
	{

	}

	/**
	 *
	 */
	void			TerrainPlugin::uninstall()
	{
		System::getSingletonPtr()->unregisterServerFactory(TerrainPageServerFactory::FactoryTypeName);
		System::getSingletonPtr()->unregisterServerFactory(TerrainGroupServerFactory::FactoryTypeName);
	}

	/**
	 *
	 */
	void			TerrainPlugin::shutdown()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	static TerrainPlugin* gpTerrainEditorPlugin = NULL;
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStartPlugin( void )
	{
		gpTerrainEditorPlugin = new TerrainPlugin();
		System::getSingletonPtr()->installPlugin(gpTerrainEditorPlugin);
	}

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStopPlugin( void )
	{
		System::getSingletonPtr()->uninstallPlugin(gpTerrainEditorPlugin);
		if (gpTerrainEditorPlugin != NULL)
			delete gpTerrainEditorPlugin;

		gpTerrainEditorPlugin = NULL;
	}
}
