#include "OgreSystemStdAfx.h"
#include "OgreTerrainSystem.h"
#include "OgreWorld.h"

namespace Ogre
{
	template<>	TerrainSystem*	Singleton<TerrainSystem>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	TerrainSystem&		TerrainSystem::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	TerrainSystem*		TerrainSystem::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \param name 
	 * \param fMaxPixelError 
	 * \param fCompositeMapDistance 
	 * \param clrCompositeMapDiffuse 
	 * \param nTerrainSize 
	 * \param fWorldSize 
	 * \param nMinBatchSize 
	 * \param nMaxBatchSize 
	 * \param fInputScale 
	 * \param texture 
	 * \param vOrigin 
	 * \return 
	 */
	TerrainSystem::TerrainSystem(float fMaxPixelError, 
		float fCompositeMapDistance, const ColourValue& clrCompositeMapDiffuse, int nTerrainSize, float fWorldSize, int nMinBatchSize, int nMaxBatchSize, 
		float fInputScale, const String& texture, const Vector3& vOrigin) : m_pGlobalOptions(NULL), m_pTerrainGroup(NULL)
	{
		SceneManager* pSceneManager = World::getSingletonPtr()->getSceneManager();
		if (pSceneManager)
		{
			// set terrain global config
			m_pGlobalOptions = new TerrainGlobalOptions();
			m_pGlobalOptions->setCompositeMapDiffuse(clrCompositeMapDiffuse);
			m_pGlobalOptions->setMaxPixelError(fMaxPixelError);
			m_pGlobalOptions->setCompositeMapDistance(fCompositeMapDistance);

			TerrainMaterialGeneratorA::SM2Profile* pProfile = static_cast<TerrainMaterialGeneratorA::SM2Profile*>(
				m_pGlobalOptions->getDefaultMaterialGenerator()->getActiveProfile()
				);
			pProfile->setReceiveDynamicShadowsEnabled(true);
			pProfile->setReceiveDynamicShadowsLowLod(false);
			pProfile->setReceiveDynamicShadowsDepth(true);
			
			ColourValue clrAmbientLinght = pSceneManager->getAmbientLight();
			m_pGlobalOptions->setCompositeMapAmbient(clrAmbientLinght);

			// create terrain group
			m_pTerrainGroup = new TerrainGroup(
				pSceneManager, Terrain::ALIGN_X_Z, nTerrainSize, fWorldSize
				);
			if (m_pTerrainGroup)
			{
				// init default config
				configureTerrainDefault(fWorldSize, nTerrainSize, fInputScale, 
					nMinBatchSize, nMaxBatchSize, texture);
				
				// set origin
				m_pTerrainGroup->setOrigin(vOrigin);
			}
		}
	}

	/**
	 *
	 * \return 
	 */
	TerrainSystem::~TerrainSystem()
	{
		if (m_pTerrainGroup != NULL)
		{
			delete m_pTerrainGroup;
			m_pTerrainGroup = NULL;
		}

		if (m_pGlobalOptions != NULL)
		{
			delete m_pGlobalOptions;
			m_pGlobalOptions = NULL;
		}
	}

	/**
	 *
	 * \param fWorldSize 
	 * \param nTerrainSize 
	 * \param fInputScale 
	 * \param nMinBatchSize 
	 * \param nMaxBatchSize 
	 * \param defaultTexture 
	 */
	void					TerrainSystem::configureTerrainDefault(float fWorldSize, int nTerrainSize, float fInputScale, 
		int nMinBatchSize, int nMaxBatchSize, const String& defaultTexture)
	{
		Terrain::ImportData& dmp = m_pTerrainGroup->getDefaultImportSettings();
		dmp.worldSize		= fWorldSize;
		dmp.terrainSize		= nTerrainSize;
		dmp.minBatchSize	= nMinBatchSize;
		dmp.maxBatchSize	= nMaxBatchSize;
		dmp.inputScale		= fInputScale;

		dmp.layerList.resize(1);
		for (int i=0; i<dmp.layerList.size(); i++)
		{
			dmp.layerList[i].worldSize = fWorldSize;
			dmp.layerList[i].textureNames.push_back(defaultTexture);
		}
	}

	/**
	 *
	 * \param nPageX 
	 * \param nPageY 
	 */
	void					TerrainSystem::defineTerrain(int nPageX, int nPageY, bool bLoad)
	{
		Terrain::ImportData& dmp = m_pTerrainGroup->getDefaultImportSettings();
		m_pTerrainGroup->defineTerrain(nPageX, nPageY, &dmp);

		if (bLoad)
		{
			m_pTerrainGroup->loadTerrain(nPageX, nPageY, true);
		}
	}

	/**
	 *
	 * \param ray 
	 * \param vPos 
	 * \return 
	 */
	Terrain*				TerrainSystem::rayIntersects(const Ray& ray, Vector3& vPos)
	{
		TerrainGroup::RayResult result = m_pTerrainGroup->rayIntersects(ray);
		LogManager::getSingleton().logMessage(LML_TRIVIAL, " hit :" + result.hit);
		if (result.hit)
		{
			vPos = result.position;
			return result.terrain;
		}

		return NULL;
	}

	/**
	 *
	 * \param nPageX 
	 * \param nPageY 
	 * \return 
	 */
	Terrain*				TerrainSystem::getTerrain(int nPageX, int nPageY)
	{
		return m_pTerrainGroup->getTerrain(nPageX, nPageY);
	}

	/**
	 *
	 * \return 
	 */
	TerrainGroup*			TerrainSystem::getTerrainGroup() const
	{
		return m_pTerrainGroup;
	}

	/**
	 *
	 * \return 
	 */
	TerrainGlobalOptions*	TerrainSystem::getTerrainGlobalOption() const
	{
		return m_pGlobalOptions;
	}
}