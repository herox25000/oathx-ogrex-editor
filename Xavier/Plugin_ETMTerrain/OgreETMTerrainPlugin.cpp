#include "OgreETMTerrainPluginPrerequisites.h"
#include "OgreETMTerrainPlugin.h"
#include "OgreSystem.h"
#include "OgreETMServerTerrain.h"


namespace Ogre
{
	const String	ETMTerrainPlugin::TerrainPluginName = "TerrainPlugin";

	/**
	 *
	 * \param void 
	 * \return 
	 */
	ETMTerrainPlugin::ETMTerrainPlugin(void)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	ETMTerrainPlugin::~ETMTerrainPlugin(void)
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	ETMTerrainPlugin::getName() const
	{
		return ETMTerrainPlugin::TerrainPluginName;
	}

	/**
	 *
	 */
	void			ETMTerrainPlugin::install()
	{
		System::getSingletonPtr()->registerServerFactory(new ETMTerrainServerFactory());
	}

	/**
	 *
	 */
	void			ETMTerrainPlugin::initialise()
	{

	}

	/**
	 *
	 */
	void			ETMTerrainPlugin::uninstall()
	{
		ServerFactory* pServerFactory = System::getSingletonPtr()->getServerFactory(
			ETMTerrainServerFactory::FactoryTypeName
			);
		if (pServerFactory)
			System::getSingletonPtr()->unregisterServerFactory(pServerFactory);
	}

	/**
	 *
	 */
	void			ETMTerrainPlugin::shutdown()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	static ETMTerrainPlugin* gpTerrainEditorPlugin = NULL;
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStartPlugin( void )
	{
		gpTerrainEditorPlugin = new ETMTerrainPlugin();
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
