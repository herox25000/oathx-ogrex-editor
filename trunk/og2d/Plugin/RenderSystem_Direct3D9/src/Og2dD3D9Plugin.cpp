#include "Og2dD3D9Prerequisites.h"
#include "Og2dSystem.h"
#include "Og2dD3D9Plugin.h"

namespace Og2d
{
	// D3D²å¼þÃû
	static const String		PLUGIN_NAME_D3D9	=	"Direct3D9";

	/**
	 *
	 * \return 
	 */
	D3D9Plugin::D3D9Plugin() : m_pRenderSystem(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	D3D9Plugin::~D3D9Plugin()
	{

	}

	/**
	 *
	 * \return 
	 */
	const String&	D3D9Plugin::getTypeName() const
	{
		return PLUGIN_NAME_D3D9;
	}

	/**
	 *
	 */
	void			D3D9Plugin::install()
	{
		m_pRenderSystem = new D3D9RenderSystem();
		if (m_pRenderSystem)
		{
			System::getSingleton().addRenderSystem(m_pRenderSystem);
		}
	}

	/**
	 *
	 */
	void			D3D9Plugin::uninstall()
	{
		if (m_pRenderSystem)
		{
			System::getSingleton().removeRenderSystem(m_pRenderSystem);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	static D3D9Plugin* mpD3DRenderSystemPlugin = NULL;
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStartPlugin( void )
	{
		mpD3DRenderSystemPlugin = new D3D9Plugin();
		System::getSingletonPtr()->installPlugin(mpD3DRenderSystemPlugin);
	}

	/**
	 *
	 * \param void 
	 */
	extern "C" void  __declspec (dllexport) dllStopPlugin( void )
	{
		System::getSingletonPtr()->uninstallPlugin(mpD3DRenderSystemPlugin);
		if (mpD3DRenderSystemPlugin != NULL)
			delete mpD3DRenderSystemPlugin;

		mpD3DRenderSystemPlugin = NULL;
	}
}