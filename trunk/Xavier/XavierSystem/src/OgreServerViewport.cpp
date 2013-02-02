#include "OgreSystemStdAfx.h"
#include "OgreServer.h"
#include "OgreServerFactory.h"
#include "OgreServerSceneManager.h"
#include "OgreServerCamera.h"
#include "OgreServerViewport.h"
#include "OgreServerManager.h"
#include "OgreServerFactoryManager.h"
#include "OgreSystem.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param pluginName 
	 * \param background 
	 * \param adp 
	 * \return 
	 */
	ServerViewport::ServerViewport(const String& name, const ColourValue& background, const SServerCameraAdp& adp)
		: Server(name), m_pViewport(NULL), m_pActiveCamera(NULL)
	{
		ServerFactory* pCameraServerFactory = ServerFactoryManager::getSingletonPtr()->getServerFactory(SERVER_CAMERA);
		if (pCameraServerFactory)
		{
			m_pActiveCamera = static_cast<ServerCamera*>(pCameraServerFactory->createServer(adp, this));
			if (m_pActiveCamera == NULL)
			{
				LogManager::getSingleton().logMessage(LML_CRITICAL, 
					"Can't create server : " + adp.name);
			}

			if (!configure(name, background, adp))
			{
				LogManager::getSingleton().logMessage(LML_CRITICAL, 
					"configure viewport server error : " + adp.name);
			}
		}
	}

	/**
	 *
	 * \return 
	 */
	ServerViewport::~ServerViewport()
	{
		if (m_pActiveCamera)
			m_pActiveCamera->drop();
	}

	/**
	 *
	 * \param name 
	 * \param background 
	 * \param adp 
	 * \return 
	 */
	bool	ServerViewport::configure(const String& name, const ColourValue& background, const SServerCameraAdp& adp)
	{	
		Camera* p = m_pActiveCamera->getCamera();
		if (p)
		{
			m_pViewport = System::getSingletonPtr()->getRenderWindow()->addViewport(p);
			if (m_pViewport)
			{

				System::getSingletonPtr()->getRenderWindow()->windowMovedOrResized();
				p->setAspectRatio(
					Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight())
					);

				/*
				* ÉèÖÃ±³¾°ÑÕÉ«
				*/
				m_pViewport->setBackgroundColour(background);

				return true;
			}
		}	
		
		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Viewport*		ServerViewport::getViewport() const
	{
		return m_pViewport;
	}
	
	/**
	 *
	 */
	void			ServerViewport::windowMovedOrResized()
	{
		RenderWindow* pRenderWindow = System::getSingleton().getRenderWindow();
		if (m_pActiveCamera != NULL && pRenderWindow != NULL)
		{
			pRenderWindow->windowMovedOrResized();

			m_pActiveCamera->getCamera()->setAspectRatio(
				Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight())
				);
		}
	}

	/**
	 *
	 * \param pActiveCamera 
	 */
	void			ServerViewport::setActiveCamera(ServerCamera* pActiveCamera)
	{
		if (m_pActiveCamera)
			m_pActiveCamera->drop();

		m_pActiveCamera = pActiveCamera;

		if (m_pActiveCamera)
			m_pActiveCamera->grab();
	}

	/**
	 *
	 * \return 
	 */
	ServerCamera*	ServerViewport::getActiveCamera() const
	{
		return m_pActiveCamera;
	}

	/**
	 *
	 * \param vPos 
	 * \param ray 
	 * \return 
	 */
	bool			ServerViewport::getMouseRay(const Vector2& vPos, Ray& ray)
	{
		if (m_pActiveCamera == NULL || m_pViewport == NULL)
			return 0;
		
		Camera* pActive = m_pActiveCamera->getCamera();
		if (pActive)
		{
			ray = pActive->getCameraToViewportRay(vPos.x / m_pViewport->getActualWidth(), 
				vPos.y / m_pViewport->getActualHeight());

			return true;
		}
	
		return 0;
	}
}