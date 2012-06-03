#include "OgreTerrainPluginPrerequisites.h"
#include "OgreServerTerrainPage.h"
#include "OgreServerTerrainGroup.h"

namespace Ogre
{
	static const unsigned int	DEF_LAYER_COUNT	= 3;

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	TerrainPageServer::TerrainPageServer(const String& typeName, TerrainGroupServer* pGroupServer,
		int nPageX, int nPageY, int nMinBatchSize, int nMaxBatchSize, const String& diffuseTexture, const String& normalheightTexture, float fLayerWorldSize) 
		: Server(typeName), m_pGroupServer(pGroupServer), m_nPageX(nPageX), m_nPageY(nPageY)
	{
		TerrainGroup* pGroup = pGroupServer->getTerrainGroup();
		if (pGroup)
		{
			// 获取地形配置
			Terrain::ImportData dp = configureTerrainPage(pGroup, nMinBatchSize,
				nMaxBatchSize, diffuseTexture, normalheightTexture, 
				fLayerWorldSize);
			
			/*
			* 定义地形(在OGRE中调用该接口后,并未实际加载地形)
			*/
			pGroup->defineTerrain(nPageX, nPageY, &dp);
			
			// 启动异步加载地形
			pGroup->loadTerrain(nPageX,
				nPageY,
				true);
		}
	}

	/**
	 *
	 * \return 
	 */
	TerrainPageServer::~TerrainPageServer()
	{
		m_pGroupServer->getTerrainGroup()->removeTerrain(m_nPageX, m_nPageY);
	}

	/**
	 *
	 * \return 
	 */
	Terrain*	TerrainPageServer::getTerrain() const
	{
		return m_pGroupServer->getTerrainGroup()->getTerrain(m_nPageX, m_nPageY);
	}

	/**
	 *
	 * \param pGroup 
	 * \param nMinBatchSize 
	 * \param nMaxBatchSize 
	 * \param diffuseTexture 
	 * \param normalheightTexture 
	 * \param fLayerWorldSize 
	 * \return 
	 */
	Terrain::ImportData	TerrainPageServer::configureTerrainPage(TerrainGroup* pGroup, int nMinBatchSize, int nMaxBatchSize, 
		const String& diffuseTexture, const String& normalheightTexture, float fLayerWorldSize)
	{
		Terrain::ImportData dp;
		dp.worldSize	= pGroup->getTerrainWorldSize();
		dp.terrainSize	= pGroup->getTerrainSize();

		dp.minBatchSize	= nMinBatchSize;
		dp.minBatchSize	= nMaxBatchSize;
		
		// 默认只创建第0层
		dp.layerList.resize(DEF_LAYER_COUNT);
		dp.layerList[0].worldSize = fLayerWorldSize;
		dp.layerList[0].textureNames.push_back(diffuseTexture);
		dp.layerList[0].textureNames.push_back(normalheightTexture);

		dp.layerList[1].worldSize = fLayerWorldSize;
		dp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
		dp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");

		dp.layerList[2].worldSize = fLayerWorldSize;
		dp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
		//dp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");

		return dp;
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
		
		// 获取地形组服务
		TerrainGroupServer* pGroupServer = static_cast<TerrainGroupServer*>(
			System::getSingleton().getServer(adp.depServerName)
			);
		if (pGroupServer)
		{
			// 创建地形页
			return new TerrainPageServer(adp.typeName, pGroupServer,
				adp.nPageX, adp.nPageY, adp.nMinBatchSize, adp.nMaxBatchSzie, adp.diffuseTexture, adp.normalheightTexture,
				adp.fLayerWorldSize);
		}
		
		return 0;
	}
}