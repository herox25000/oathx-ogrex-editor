#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorTerrain.h"
#include "EditorPluginManager.h"
#include "EditorTerrainPage.h"

namespace Ogre
{
	/**
	 *
	 * \param pluginName 
	 * \param nPageX 
	 * \param nPageY 
	 * \param vPos 
	 * \param nMinBatchSize 
	 * \param nMaxBatchSize 
	 * \param nLayerCount 
	 * \param tpl 
	 * \param bAtOnceLoad 
	 * \return 
	 */
	EditorTerrainPage::EditorTerrainPage(const String& pluginName, int nPageX, int nPageY, const Vector3& vPos, uint16 nMinBatchSize, uint16 nMaxBatchSize,
		uint16 nLayerCount, const STerrainPageLayer& tpl, bool bAtOnceLoad)
		: EditorPlugin(pluginName), m_pTerrain(NULL)
	{
		if (configure(nPageX, nPageY, vPos, nMinBatchSize, nMaxBatchSize, nLayerCount, tpl, bAtOnceLoad))
		{
			
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorTerrainPage::~EditorTerrainPage()
	{

	}

	/**
	 *
	 * \param nPageX 
	 * \param nPageY 
	 * \param vPos 
	 * \param nMinBatchSize 
	 * \param nMaxBatchSize 
	 * \param nLayerCount 
	 * \param tpl 
	 * \param bAtOnceLoad 
	 * \return 
	 */
	bool		EditorTerrainPage::configure(int nPageX, int nPageY, const Vector3& vPos, uint16 nMinBatchSize, uint16 nMaxBatchSize, uint16 nLayerCount,
		const STerrainPageLayer& tpl, bool bAtOnceLoad)
	{
		EditorTerrain* pPlugin = static_cast<EditorTerrain*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
			);
		if (pPlugin)
		{
			TerrainGroup* pTerrainGroup = pPlugin->getTerrainGroup();
			if (pTerrainGroup)
			{
				Terrain::ImportData dmp;
				dmp.terrainSize		= pTerrainGroup->getTerrainSize();
				dmp.worldSize		= pTerrainGroup->getTerrainWorldSize();

				dmp.pos				= vPos;
				dmp.inputImage		= 0;
				dmp.inputFloat		= 0;
				dmp.constantHeight	= 0;
				dmp.inputScale		= 1.0f;
				
				dmp.minBatchSize	= nMinBatchSize;
				dmp.maxBatchSize	= nMaxBatchSize;

				dmp.layerList.resize(nLayerCount);
				for (int i=0; i<nLayerCount; i++)
				{
					dmp.layerList[i].worldSize = tpl.fLayerWorldSize[i];
					dmp.layerList[i].textureNames.push_back(tpl.layerDiffuseTexture[i]);
					dmp.layerList[i].textureNames.push_back(tpl.layerNormalTexture[i]);
				}
			
				pTerrainGroup->defineTerrain(nPageX, nPageY, &dmp);

				if (bAtOnceLoad)
				{
					pTerrainGroup->loadTerrain(nPageX, nPageY, true);
				}

				return true;
			}
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL,
				"Can't find terrain plugin : " + EDITOR_TERRAIN);
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	EditorTerrainPageFactory::EditorTerrainPageFactory(const String& factoryName)
		: EditorPluginFactory(factoryName)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorTerrainPageFactory::~EditorTerrainPageFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*		EditorTerrainPageFactory::createPlugin(const SEditorPluginAdp& ssadp, 
		EditorPlugin* pParent)
	{
		const SEditorPluginTerrainPageAdp& adp = static_cast<const SEditorPluginTerrainPageAdp&>(ssadp);

		EditorTerrainPage* pEditorTerrainPage = new EditorTerrainPage(adp.pluginName, adp.nPageX, adp.nPageY, adp.vPos, adp.nMinBatchSize, 
			adp.nMaxBatchSize, adp.nLayerCount, adp.tpl, adp.bAtOnceLoad);
		if (pEditorTerrainPage)
		{
			// 设置删除优先级
			pEditorTerrainPage->setPriority(PRIORITY_LOW);

			LogManager::getSingleton().logMessage(LML_NORMAL,
				"Create editor plugin : " + adp.pluginName);

			if (pParent)
				pParent->registerPlugin(pEditorTerrainPage);

			return pEditorTerrainPage;
		}

		return NULL;
	}
}