#include "OgreSystemStdAfx.h"
#include "OgreServer.h"
#include "OgreServerFactory.h"
#include "OgreServerSceneManager.h"
#include "OgreServerManager.h"

namespace Ogre
{
	/**
	 *
	 * \param pluginName 
	 * \param typeMask 
	 * \return 
	 */
	ServerSceneManager::ServerSceneManager(const String& name, const SceneTypeMask& typeMask, 
		const ColourValue& clrAmbientLight, FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd)
		: Server(name)
	{
		if (!configure(name, typeMask, clrAmbientLight, fogMode, clrFog, expDensity, linearStart, linearEnd))
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL,
				"Server scene manager configure error");
		}
	}

	/**
	 *
	 * \return 
	 */
	ServerSceneManager::~ServerSceneManager()
	{
		if (m_pSceneManager)
		{
			Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);
		}
	}

	/**
	 *
	 * \param fogMode 
	 * \param clrFog 
	 * \param expDensity 
	 * \param linearStart 
	 * \param linearEnd 
	 */
	bool			ServerSceneManager::configure(const String& name, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
		FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd)
	{
		m_pSceneManager = Root::getSingletonPtr()->createSceneManager(typeMask);
		if (m_pSceneManager)
		{
			// ÉèÖÃÂþ·´Éä
			m_pSceneManager->setAmbientLight(clrAmbientLight);

			// ÉèÖÃÎí
			m_pSceneManager->setFog(fogMode, clrFog, 
				expDensity, linearStart, linearEnd);
			
			return true;
		}
		else
		{
			TKLogEvent("Can't create ogre scene manager : " + name,
				LML_CRITICAL);
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	SceneManager*	ServerSceneManager::getSceneManager() const
	{
		return m_pSceneManager;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	ServerSceneManagerFactory::ServerSceneManagerFactory(const String& typeName)
		: ServerFactory(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	ServerSceneManagerFactory::~ServerSceneManagerFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	Server*		ServerSceneManagerFactory::createServer(const SServerAdp& ssadp, Server* pParent)
	{
		const SServerSceneManagerAdp& adp = static_cast<const SServerSceneManagerAdp&>(ssadp);

		ServerSceneManager* pSceneManagerServer = new ServerSceneManager(adp.name, adp.typeMask, adp.clrAmbientLight, adp.fogMode, 
			adp.clrFog, adp.expDensity, adp.linearStart, adp.linearEnd);
		if (pSceneManagerServer)
		{
			if (Kernel.SERVER_SCENEMANAGER.empty())
			{
				Kernel.SERVER_SCENEMANAGER = ssadp.name;	
			}

			LogManager::getSingleton().logMessage("Create server : " + adp.name,
				LML_NORMAL);

			if (pParent == NULL)
				pParent = ServerManager::getSingleton().getRootServer();

			if (pParent)
			{
				pParent->attachServer(pSceneManagerServer);
			}
			
			return pSceneManagerServer;
		}

		return NULL;
	}
}