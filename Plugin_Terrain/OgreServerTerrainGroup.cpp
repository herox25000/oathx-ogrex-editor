#include "OgreTerrainPluginPrerequisites.h"
#include "OgreServerTerrainGroup.h"
#include "OgreServerWorldSpace.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	TerrainGroupServer::TerrainGroupServer(const String& typeName, const String& depWorldServerName,
		int nTerrainSize, float fWorldSize, const Vector3& vOrigin)
		: Server(typeName), m_pTerrainGroup(NULL)
	{
		// 构造地形组
		WorldSpaceServer* pWorldServer = static_cast<WorldSpaceServer*>(
			System::getSingletonPtr()->getServer(depWorldServerName)
			);
		m_pTerrainGroup = new TerrainGroup(
			pWorldServer->getSceneManager(), Terrain::ALIGN_X_Z, nTerrainSize, fWorldSize
			);
		if (m_pTerrainGroup)
		{
			m_pTerrainGroup->setOrigin(vOrigin);
		}
	}

	/**
	 *
	 * \return 
	 */
	TerrainGroupServer::~TerrainGroupServer()
	{
		if (m_pTerrainGroup)
			delete m_pTerrainGroup;

		m_pTerrainGroup = NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	const String	TerrainGroupServerFactory::FactoryTypeName = "Terrain/TerrainGroupServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	TerrainGroupServerFactory::TerrainGroupServerFactory()
	{
		
	}

	/**
	 *
	 * \return 
	 */
	String		TerrainGroupServerFactory::getTypeName() const
	{
		return TerrainGroupServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*		TerrainGroupServerFactory::createServer(const SSAdp& ssadp)
	{
		// 获取参数
		const STerrainGroupServerAdp& adp = static_cast<const STerrainGroupServerAdp&>(ssadp);
		
		// 创建地形组服务
		return new TerrainGroupServer(adp.typeName, adp.depServerName, 
			adp.nTerrainSize, adp.fWorldSize, adp.vOrigin);
	}
}