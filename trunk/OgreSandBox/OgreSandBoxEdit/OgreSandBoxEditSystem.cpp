#include "stdafx.h"
#include "OgreSandBoxEditSystem.h"

namespace Ogre
{
	template<>	EditSystem*	Singleton<EditSystem>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditSystem&		EditSystem::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditSystem*		EditSystem::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	EditSystem::EditSystem() 
		: m_pSandBox(NULL)
	{
		m_pSandBox	= new SandBox();
	}

	/**
	 *
	 * \return 
	 */
	EditSystem::~EditSystem()
	{
		SAFE_DELETE(m_pSandBox);
	}

	/**
	 *
	 * \param pluginFileName 
	 * \param resourceFileName 
	 * \param bAutoCreateWindow 
	 * \return 
	 */
	bool			EditSystem::createEditSystem(const String& pluginFileName, 
		const String& resourceFileName, bool bAutoCreateWindow)
	{
		if (!m_pSandBox->createSandBox(pluginFileName, resourceFileName, bAutoCreateWindow))
		{
			OGRE_EXCEPT(Exception::ERR_RT_ASSERTION_FAILED, "Can't create SandBox core system", 
				"EditSystem::createEditSystem");
		}

		return true;
	}

	/**
	 *
	 */
	/**
	 *
	 */
	void			EditSystem::go()
	{
		m_pSandBox->go();
	}

	/**
	 *
	 */
	void			EditSystem::clearUp()
	{
		m_pSandBox->clearUp();
	}

	/**
	 *
	 * \param name 
	 * \param hWnd 
	 * \param w 
	 * \param h 
	 * \param bFullScreen 
	 * \return 
	 */
	bool			EditSystem::createWindow(const String& name, HWND hWnd, int w, int h, bool bFullScreen)
	{
		return m_pSandBox->createWindow(name, hWnd, w, h, bFullScreen);
	}

	/**
	 *
	 * \return 
	 */
	RenderWindow*	EditSystem::getWindow() const
	{
		return m_pSandBox->getWindow();
	}

	/**
	 *
	 * \param name 
	 */
	void			EditSystem::loadPlugin(const String& name)
	{
		m_pSandBox->loadPlugin(name);
	}

	/**
	 *
	 * \param name 
	 */
	void			EditSystem::unloadPlugin(const String& name)
	{
		m_pSandBox->unloadPlugin(name);
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void			EditSystem::installPlugin(Plugin* pPlugin)
	{
		m_pSandBox->installPlugin(pPlugin);
	}

	/**
	 *
	 * \param name 
	 */
	void			EditSystem::uninstallPlugin(Plugin* pPlugin)
	{
		m_pSandBox->uninstallPlugin(pPlugin);
	}

	/**
	 *
	 */
	void			EditSystem::destoryAllPlugin()
	{
		m_pSandBox->destoryAllPlugin();
	}
}