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
		addProperty(PV_TERRAINPAGE_POSTION, Any(vPos),			PVT_VECTOR3);
		addProperty(PV_TERRAINPAGE_X,		Any(nPageX),		PVT_INT);
		addProperty(PV_TERRAINPAGE_Y,		Any(nPageY),		PVT_INT);
		addProperty(PV_MINBATCHSIZE,		Any(nMinBatchSize), PVT_INT);
		addProperty(PV_MAXBATCHSIZE,		Any(nMaxBatchSize), PVT_INT);

		TerrainGroupServer* pGroup = static_cast<TerrainGroupServer*>(
			System::getSingletonPtr()->getServer(m_depGroupName)
			);
		if (pGroup)
		{
			Terrain::ImportData dmp;
			dmp.worldSize		= pGroup->getTerrainGroup()->getTerrainWorldSize();

			int nValue;
			pGroup->getPropertyValue(PV_TERRAINSIZE, nValue);
			dmp.terrainSize		= nValue;

			dmp.inputScale		= 0;
			dmp.minBatchSize	= nMinBatchSize;
			dmp.minBatchSize	= nMaxBatchSize;

			dmp.layerList.resize(1);
			for (int i=0; i<dmp.layerList.size(); i++)
			{
				dmp.layerList[i].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
			}

			TerrainGroup* pTerrain = pGroup->getTerrainGroup();
			if (pTerrain)
			{
				pTerrain->defineTerrain(nPageX, nPageY, &dmp);
				pTerrain->loadTerrain(nPageX, nPageY, true);
				pTerrain->freeTemporaryResources();
			}
		}
	}

	/**
	 *
	 * \return 
	 */
	TerrainPageServer::~TerrainPageServer()
	{
		TerrainGroupServer* pGroup = static_cast<TerrainGroupServer*>(
			System::getSingletonPtr()->getServer(m_depGroupName)
			);
		if (pGroup)
		{
			int nPageX;
			getPropertyValue(PV_TERRAINPAGE_X, nPageX);
			
			int nPageY;
			getPropertyValue(PV_TERRAINPAGE_Y, nPageY);

			TerrainGroup* pTerrain = pGroup->getTerrainGroup();
			if (pTerrain)
			{
				pTerrain->removeTerrain(nPageX, nPageY);
			}
		}
	}

	/**
	 *
	 * \param name 
	 * \param flipX 
	 * \param flipY 
	 * \param image 
	 */
	void	TerrainPageServer::getTerrainImage(const String& name, bool flipX, bool flipY, Image& image)
	{
		image.load(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		if (flipX)
			image.flipAroundY();
		if (flipY)
			image.flipAroundX();
	}

	/**
	 *
	 * \param name 
	 * \param x 
	 * \param y 
	 * \param flat 
	 */
	void	TerrainPageServer::defineTerrain(const String& name, long x, long y, bool flat)
	{
		TerrainGroupServer* pGroup = static_cast<TerrainGroupServer*>(
			System::getSingleton().getServer(m_depGroupName)
			);
		if (pGroup)
		{
			if (flat)
			{
				pGroup->getTerrainGroup()->defineTerrain(x, y, 0.0f);
			}
			else
			{
				String filename = pGroup->getTerrainGroup()->generateFilename(x, y);
				if (ResourceGroupManager::getSingleton().resourceExists(pGroup->getTerrainGroup()->getResourceGroup(), filename))
				{
					pGroup->getTerrainGroup()->defineTerrain(x, y);
				}
				else
				{
					Image image;
					getTerrainImage(name, x % 2 != 0, y % 2 != 0, image);

					pGroup->getTerrainGroup()->defineTerrain(x, y,
						&image);
				}
			}
		}
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