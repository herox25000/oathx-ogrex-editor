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
		: Server(typeName), m_pGroupServer(pGroupServer), m_pTerrain(0), m_nPageX(nPageX), m_nPageY(nPageY)
	{
		TerrainGroup* pGroup = pGroupServer->getTerrainGroup();
		if (pGroup)
		{
			// ��ȡ��������
			Terrain::ImportData dp = configureTerrainPage(pGroup, nMinBatchSize,
				nMaxBatchSize, diffuseTexture, normalheightTexture, 
				fLayerWorldSize);
			
			/*
			* �������(��OGRE�е��øýӿں�,��δʵ�ʼ��ص���)
			*/
			pGroup->defineTerrain(nPageX, nPageY, &dp);
			
			// �����첽���ص���
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
		
		// Ĭ��ֻ������0��
		dp.layerList.resize(DEF_LAYER_COUNT);
		dp.layerList[0].worldSize = fLayerWorldSize;
		dp.layerList[0].textureNames.push_back(diffuseTexture);
		dp.layerList[0].textureNames.push_back(normalheightTexture);

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
		// ��ȡ����
		const STerrainPageServerAdp& adp = static_cast<const STerrainPageServerAdp&>(ssadp);
		
		// ��ȡ���������
		TerrainGroupServer* pGroupServer = static_cast<TerrainGroupServer*>(
			System::getSingleton().getServer(adp.depServerName)
			);
		if (pGroupServer)
		{
			// ��������ҳ
			return new TerrainPageServer(adp.typeName, pGroupServer,
				adp.nPageX, adp.nPageY, adp.nMinBatchSize, adp.nMaxBatchSzie, adp.diffuseTexture, adp.normalheightTexture,
				adp.fLayerWorldSize);
		}
		
		return 0;
	}
}