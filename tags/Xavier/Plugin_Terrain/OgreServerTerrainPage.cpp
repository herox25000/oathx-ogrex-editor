#include "OgreTerrainPluginPrerequisites.h"
#include "OgreServerTerrainPage.h"
#include "OgreServerTerrainGroup.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	TerrainPageServer::TerrainPageServer(const String& typeName, const String& depGroupName, const Vector3& vPos,
		int nPageX, int nPageY, int nMinBatchSize, int nMaxBatchSize) 
		: Server(typeName), m_depGroupName(depGroupName), m_pTerrain(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	TerrainPageServer::~TerrainPageServer()
	{

	}


	//////////////////////////////////////////////////////////////////////////
	const String	TerrainPageServerFactory::FactoryTypeName = "Terrain/TerrainPageServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	TerrainPageServerFactory::TerrainPageServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String	TerrainPageServerFactory::getTypeName() const
	{
		return TerrainPageServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*	TerrainPageServerFactory::createServer(const SSAdp& ssadp)
	{
		// 获取参数
		const STerrainPageServerAdp& adp = static_cast<const STerrainPageServerAdp&>(ssadp);
		
		// 创建地形页
		return new TerrainPageServer(adp.typeName, 
									adp.depServerName,
									adp.vPos,
									adp.nPageX, 
									adp.nPageY, 
									adp.nMinBatchSize, 
									adp.nMaxBatchSzie);
	}
}