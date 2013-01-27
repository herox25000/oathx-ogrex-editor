#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorTerrain.h"
#include "EditorPluginManager.h"
#include "EditorTerrainPage.h"

namespace Ogre
{
	enum {
		TERRAINPAGE_PLUGIN_NAME,
		TERRAINPAGE_LAYERCOUNT,
		TERRAINPAGE_PAGEX,
		TERRAINPAGE_PAGEY,
		TERRAINPAGE_MINBATCHSIZE,
		TERRAINPAGE_MAXBATCHSIZE,

		TERRAINPAGE_COUNT
	};

	static const String		terrainPageName[] = {
		"Name",
		"LayerCount",
		"PageX",
		"PageY",
		"MinBatchSize",
		"MaxBatchSize",
	};

	static const String		terrainPageDesc[] = {
		"Name",
		"LayerCount",
		"PageX",
		"PageY",
		"MinBatchSize",
		"MaxBatchSize",
	};

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
			addProperty(terrainPageName[TERRAINPAGE_PLUGIN_NAME],
				Any(pluginName), PVT_STRING, 0, terrainPageDesc[TERRAINPAGE_PLUGIN_NAME]);
			addProperty(terrainPageName[TERRAINPAGE_LAYERCOUNT],
				Any(nLayerCount), PVT_USHORT, true, terrainPageDesc[TERRAINPAGE_LAYERCOUNT]);
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

				if (!m_pTerrain)
				{
					m_pTerrain = pTerrainGroup->getTerrain(nPageX, nPageY);
				}
				
				return true;
			}
		}
		else
		{
			TKLogEvent("Can't find terrain plugin : " + EDITOR_TERRAIN, LML_CRITICAL);
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Terrain*		EditorTerrainPage::getTerrain() const
	{
		return m_pTerrain;
	}
	
	/**
	 *
	 * \param texture 
	 * \return 
	 */
	int				EditorTerrainPage::getLayerID(const String& texture)
	{
		TerrainLayerSamplerList vSampler = m_pTerrain->getLayerDeclaration().samplers;
		for (int nSamplerID=0; nSamplerID<vSampler.size(); nSamplerID++)
		{
			for (int nLayerID=0; nLayerID<m_pTerrain->getLayerCount(); nLayerID++)
			{
				String name = m_pTerrain->getLayerTextureName(nLayerID, nSamplerID);
				if (name == texture)
				{
					return nLayerID;
				}
			}
		}

		return INVALID_LAYER;

/*		int nSamplerID = -1;

		TerrainLayerSamplerList vSampler = m_pTerrain->getLayerDeclaration().samplers;
		for(int i=0; i<vSampler.size(); i++)
		{
			if(vSampler[i].alias == "albedo_specular")
			{
				nSamplerID = i;
				break;
			}
		}

		if(nSamplerID == -1) 
			return -1;

		int nLayerID = -1;
		for (int i=0; i<m_pTerrain->getLayerCount(); i++)
		{
			String name = m_pTerrain->getLayerTextureName(i, nSamplerID);
			if (name == texture)
			{
				nLayerID  = i;
				break;
			}
		}
		
		return nLayerID*/;
	}

	/**
	 *
	 * \param texture 
	 * \param normal 
	 * \param fWorldSize 
	 * \return 
	 */
	int				EditorTerrainPage::addLayer(const String& texture, const String& normal,
		float fWorldSize)
	{
		int nLayerCount = m_pTerrain->getLayerCount();
		if (nLayerCount < MAX_LAYERS_ALLOWED)
		{
			StringVector vTexture;
			vTexture.push_back(texture);
			vTexture.push_back(normal);
			
			m_pTerrain->addLayer(nLayerCount, 
				fWorldSize, 
				&vTexture);

			return m_pTerrain->getLayerCount() - 1;
		}

		return -1;
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

			TKLogEvent("Create editor plugin : " + adp.pluginName, LML_NORMAL);

			if (pParent)
				pParent->registerPlugin(pEditorTerrainPage);

			return pEditorTerrainPage;
		}

		return NULL;
	}
}