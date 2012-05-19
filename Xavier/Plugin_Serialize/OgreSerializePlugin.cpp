#include "OgreSerialzePluginPrerequisites.h"
#include "OgreSerializePlugin.h"

namespace Ogre
{
	const String	SerializePlugin::SerializePluginName = "TerrainPlugin";

	/**
	 *
	 * \param void 
	 * \return 
	 */
	SerializePlugin::SerializePlugin(void)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	SerializePlugin::~SerializePlugin(void)
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	SerializePlugin::getName() const
	{
		return SerializePlugin::SerializePluginName;
	}

	/**
	 *
	 */
	void			SerializePlugin::install()
	{

	}

	/**
	 *
	 */
	void			SerializePlugin::initialise()
	{

	}

	/**
	 *
	 */
	void			SerializePlugin::uninstall()
	{

	}

	/**
	 *
	 */
	void			SerializePlugin::shutdown()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	static SerializePlugin* gpSerializePlugin = NULL;
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStartPlugin( void )
	{
		gpSerializePlugin = new SerializePlugin();
		System::getSingletonPtr()->installPlugin(gpSerializePlugin);
	}

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStopPlugin( void )
	{
		System::getSingletonPtr()->uninstallPlugin(gpSerializePlugin);
		if (gpSerializePlugin != NULL)
			delete gpSerializePlugin;

		gpSerializePlugin = NULL;
	}

}
