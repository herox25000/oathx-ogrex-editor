#include "OgreSystemPrerequisites.h"
#include "OgreServerWorldSpace.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	WorldSpaceServer::WorldSpaceServer(const String& typeName, const String& name, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight)
		:Server(typeName), m_name(name)
	{
		// 创建场景管理器
		m_pSceneManager = Root::getSingleton().createSceneManager(typeMask, name);
		
		// 设置环境光
		m_pSceneManager->setAmbientLight(clrAmbientLight);
	}

	/**
	 *
	 * \return 
	 */
	WorldSpaceServer::~WorldSpaceServer()
	{
		Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);
	}

	/**
	 *
	 * \param name 
	 */
	void			WorldSpaceServer::setName(const String& name)
	{
		m_name = name;
	}

	/**
	 *
	 * \return 
	 */
	String			WorldSpaceServer::getName() const
	{
		return m_name;
	}

	SceneManager*	WorldSpaceServer::getSceneManager() const
	{
		return m_pSceneManager;
	}
	
	//////////////////////////////////////////////////////////////////////////
	const String	WorldSpaceServerFactory::FactoryTypeName = "System/WorldSpaceServerFactory";

	//////////////////////////////////////////////////////////////////////////
	// class WorldSpaceFactory
	//////////////////////////////////////////////////////////////////////////
	WorldSpaceServerFactory::WorldSpaceServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	WorldSpaceServerFactory::~WorldSpaceServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String	WorldSpaceServerFactory::getTypeName() const
	{
		return WorldSpaceServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param pAdp 
	 * \param pParent 
	 * \return 
	 */
	Server*	WorldSpaceServerFactory::createServer(const SSAdp& ssadp)
	{
		const SWorldSpaceServerAdp& adp = static_cast<const SWorldSpaceServerAdp&>(ssadp);

#ifdef _OUTPUT_LOG
		TKLogEvent("create server " + adp.typeName + " dependencie server " + (adp.depServerName.empty() ? "NULL" : adp.depServerName));
#endif
		// create world space
		return new WorldSpaceServer(adp.typeName, 
			adp.name, adp.typeMask, adp.clrAmbientLight);
	}
}