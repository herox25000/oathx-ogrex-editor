#include "OgreSystemStdAfx.h"
#include "OgreServer.h"
#include "OgreServerFactory.h"
#include "OgreServerSceneManager.h"
#include "OgreServerCamera.h"
#include "OgreServerManager.h"

namespace Ogre
{
	/**
	 *
	 * \param pluginName 
	 * \param vPos 
	 * \param q 
	 * \param fNearClipDistance 
	 * \param fFarClipDistance 
	 * \param fFov 
	 * \param AutoAspectRatio 
	 * \param nQueryFlags 
	 * \return 
	 */
	ServerCamera::ServerCamera(const String& name, const Vector3& vPos, const Quaternion& q, float fNearClipDistance,
		float fFarClipDistance, float fFov, bool bAutoAspectRatio,
		uint32 nQueryFlags) : Server(name), m_pSceneManagerServer(NULL), m_pCamera(NULL)
	{
		m_pSceneManagerServer = static_cast<ServerSceneManager*>(
			ServerManager::getSingletonPtr()->getServer(Kernel.SERVER_SCENEMANAGER)
			);
		if (m_pSceneManagerServer)
		{
			if (!configure(name, vPos, q, fNearClipDistance, fFarClipDistance, fFov, bAutoAspectRatio, nQueryFlags))
			{
				LogManager::getSingleton().logMessage(LML_CRITICAL,
					"configure error");
			}

			m_pSceneManagerServer->grab();
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL,
				"Can't find scene server");
		}
	}

	/**
	 *
	 * \return 
	 */
	ServerCamera::~ServerCamera()
	{
		if (m_pSceneManagerServer)
			m_pSceneManagerServer->drop();
	}

	/**
	 *
	 * \param vPos 
	 * \param q 
	 * \param fNearClipDistance 
	 * \param fFarClipDistance 
	 * \param fFov 
	 * \param bAutoAspectRatio 
	 * \param nQueryFlags 
	 */
	bool		ServerCamera::configure(const String& name, const Vector3& vPos, const Quaternion& q, float fNearClipDistance, 
		float fFarClipDistance, float fFov, bool bAutoAspectRatio, uint32 nQueryFlags)
	{		
		// ´´½¨ÉãÏñ»ú
		m_pCamera = m_pSceneManagerServer->getSceneManager()->createCamera(name);
		if (m_pCamera)
		{
			m_pCamera->setPosition(vPos);
			m_pCamera->setOrientation(q);
			m_pCamera->setNearClipDistance(fNearClipDistance);
			m_pCamera->setFarClipDistance(fFarClipDistance);
			m_pCamera->setFOVy(Radian(fFov));
			m_pCamera->setAutoAspectRatio(bAutoAspectRatio);
			m_pCamera->setQueryFlags(0);

			return true;
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL,
				"Can't create ogre camera + " + name);
		}
		
		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Camera*			ServerCamera::getCamera() const
	{
		return m_pCamera;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	ServerCameraFactory::ServerCameraFactory(const String& typeName)
		: ServerFactory(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	ServerCameraFactory::~ServerCameraFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	Server*	ServerCameraFactory::createServer(const SServerAdp& ssadp, Server* pParent)
	{
		const SServerCameraAdp& adp = static_cast<const SServerCameraAdp&>(ssadp);
	
		ServerCamera* pCameraServer = new ServerCamera(adp.name, adp.vPos, adp.q, 
			adp.fNearClipDistance, adp.fFarClipDistance, adp.fFov, adp.bAutoAspectRatio, adp.nQueryFlags);
		if (pCameraServer)
		{
			if (Kernel.SERVER_CAMERA.empty())
			{
				Kernel.SERVER_CAMERA = ssadp.name;	
			}

			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Create editor plugin : " + adp.name);
			
			if (pParent == NULL)
				pParent = ServerManager::getSingleton().getRootServer();

			if (pParent)
				pParent->attachServer(pCameraServer);

			return pCameraServer;
		}

		return NULL;
	}
}