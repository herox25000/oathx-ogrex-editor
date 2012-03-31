#include "OgreAppEditPrerequisites.h"
#include "OgreTerrainEditorPlugin.h"
#include "OgreTerrainEditorFactory.h"
#include "OgreTerrainEditor.h"
#include "OgreAppEdit.h"

namespace Ogre
{
	const String	TerrainEditorPlugin::PluginTerrainEditorName = "TerrainEditorPlugin";

	/**
	 *
	 * \param void 
	 * \return 
	 */
	TerrainEditorPlugin::TerrainEditorPlugin(void)
	{
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
		return PluginTerrainEditorName;
	}
	/**
	 *
	 * \return 
	 */
	bool			TerrainEditorPlugin::install()
	{
		AppEdit::getSingletonPtr()->registerEditorFactory(new TerrainEditorFactory());
		return true;
	}

	/**
	 *
	 */
	void			TerrainEditorPlugin::uninstall()
	{
		BaseEditorFactory* pFactory = AppEdit::getSingletonPtr()->getEditorFactory(FACTORY_TERRAIN);
		AppEdit::getSingletonPtr()->unregisterEditorFactory(pFactory);
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
	void			TerrainEditorPlugin::shutdown()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	TerrainEditorPlugin* gpTerrainEditorPlugin = NULL;
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStartPlugin( void )
	{
		gpTerrainEditorPlugin = new TerrainEditorPlugin();
		AppEdit::getSingletonPtr()->installPlugin(gpTerrainEditorPlugin);
	}

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStopPlugin( void )
	{
		AppEdit::getSingletonPtr()->uninstallPlugin(gpTerrainEditorPlugin);
		if (gpTerrainEditorPlugin != NULL)
			delete gpTerrainEditorPlugin;

		gpTerrainEditorPlugin = NULL;
	}
}
