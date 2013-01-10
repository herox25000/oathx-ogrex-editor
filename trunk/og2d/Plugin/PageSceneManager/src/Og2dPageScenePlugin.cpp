#include "Og2dPageScenePrerequisites.h"
#include "Og2dSystem.h"
#include "Og2dPageScenePlugin.h"
#include "Og2dDebug.h"

namespace Og2d
{
	static const String	PLUGIN_NAME_PAGESCENEMANAGER = "Page Scene Manager";

	/**
	 *
	 * \return 
	 */
	PageScenePlugin::PageScenePlugin()
	{

	}

	/**
	 *
	 * \return 
	 */
	PageScenePlugin::~PageScenePlugin()
	{

	}

	/** 获取插件名
	 *
	 * \return 
	 */
	const String&	PageScenePlugin::getTypeName() const
	{
		return PLUGIN_NAME_PAGESCENEMANAGER;
	}

	/** 安装插件
	 *
	 */
	void			PageScenePlugin::install()
	{
		// add page scene factory
		System::getSingletonPtr()->addSceneFactory( 
			new PageSceneFactory("PageSceneFactory"));
	}

	/** 卸载插件
	 *
	 */
	void			PageScenePlugin::uninstall()
	{
		SceneFactory* pFactory = System::getSingleton().getSceneFactory("PageSceneFactory");
		if (pFactory != NULL)
			System::getSingletonPtr()->removeFactory(pFactory);
	}

	//////////////////////////////////////////////////////////////////////////
	static PageScenePlugin* mpPageScenePlugin = NULL;
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStartPlugin( void )
	{
		mpPageScenePlugin = new PageScenePlugin();
		System::getSingletonPtr()->installPlugin(mpPageScenePlugin);
	}

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStopPlugin( void )
	{
		System::getSingletonPtr()->uninstallPlugin(mpPageScenePlugin);
		if (mpPageScenePlugin != NULL)
			delete mpPageScenePlugin;

		mpPageScenePlugin = NULL;
	}
}