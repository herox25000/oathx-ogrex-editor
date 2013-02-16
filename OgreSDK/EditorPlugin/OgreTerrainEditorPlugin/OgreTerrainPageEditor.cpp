#include "OgreTerrainEditorPluginStdAfx.h"
#include "OgreTerrainPageEditor.h"
#include "OgreTerrainEditor.h"

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
	TerrainPageEditor::TerrainPageEditor(const String& pluginName, int nPageX, int nPageY, const Vector3& vPos, uint16 nMinBatchSize, uint16 nMaxBatchSize,
		uint16 nLayerCount, const STerrainPageLayer& tpl, bool bAtOnceLoad)
		: EditorPlugin(pluginName), m_pTerrain(NULL), m_pSaveHeight(NULL)
	{
		m_AlterRect = Rect(0, 0, 0, 0);

		if (configure(nPageX, nPageY, vPos, nMinBatchSize, nMaxBatchSize, nLayerCount, tpl, bAtOnceLoad))
		{
			addProperty(terrainPageName[TERRAINPAGE_PLUGIN_NAME],
				Any(pluginName), PVT_STRING, 0, terrainPageDesc[TERRAINPAGE_PLUGIN_NAME]);
			addProperty(terrainPageName[TERRAINPAGE_LAYERCOUNT],
				Any(nLayerCount), PVT_USHORT, true, terrainPageDesc[TERRAINPAGE_LAYERCOUNT]);
			addProperty(terrainPageName[TERRAINPAGE_PAGEX],
				Any(nPageX), PVT_INT, true, terrainPageDesc[TERRAINPAGE_PAGEX]);
			addProperty(terrainPageName[TERRAINPAGE_PAGEY],
				Any(nPageY), PVT_INT, true, terrainPageDesc[TERRAINPAGE_PAGEY]);
		}
	}

	/**
	 *
	 * \return 
	 */
	TerrainPageEditor::~TerrainPageEditor()
	{
		if (m_pSaveHeight)
		{
			delete [] m_pSaveHeight;
			m_pSaveHeight = NULL;
		}
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
	bool		TerrainPageEditor::configure(int nPageX, int nPageY, const Vector3& vPos, uint16 nMinBatchSize, uint16 nMaxBatchSize, uint16 nLayerCount,
		const STerrainPageLayer& tpl, bool bAtOnceLoad)
	{
		TerrainEditor* pPlugin = static_cast<TerrainEditor*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(CPN::EDITOR_TERRAIN_GROUP)
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
				dmp.inputScale		= 0.0f;
				
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
			LogManager::getSingleton().logMessage("Can't find terrain plugin : " + CPN::EDITOR_TERRAIN_GROUP, LML_CRITICAL);
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Terrain*		TerrainPageEditor::getTerrain() const
	{
		return m_pTerrain;
	}
	
	/**
	 *
	 * \param texture 
	 * \return 
	 */
	int				TerrainPageEditor::getLayerID(const String& texture)
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
	}

	/**
	 *
	 * \param texture 
	 * \param normal 
	 * \param fWorldSize 
	 * \return 
	 */
	int				TerrainPageEditor::addLayer(const String& texture, const String& normal,
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

	/**
	 *
	 * \param area 
	 * \param pData 
	 */
	void			TerrainPageEditor::swapHeight(Rect area, float* pData)
	{
		if (m_pTerrain)
		{
			float*	pCurHeightData	= m_pTerrain->getHeightData();
			int		nRowSize		= m_pTerrain->getSize();

			int		nPos = 0;
			for(int y = area.top;y < area.bottom;y++)
			{
				for(int x = area.left;x < area.right;x++)
				{
					float fVal	= pCurHeightData[y * nRowSize + x];
					pCurHeightData[y * nRowSize + x] = pData[nPos];
					pData[nPos] = fVal;

					++ nPos;
				}
			}

			m_pTerrain->dirtyRect(area);
			m_pTerrain->update();
		}
	}

	/**
	 *
	 * \param nValue 
	 */
	void			TerrainPageEditor::alterStart(int nValue, const Rect& area)
	{
		switch( nValue )
		{
		case 0:
			{
				if (m_pSaveHeight == NULL)
				{
					uint32 nSize	= m_pTerrain->getSize() * m_pTerrain->getSize();
					m_pSaveHeight = new float[nSize];

					float* pData	= m_pTerrain->getHeightData();
					memcpy(m_pSaveHeight, pData, sizeof(float) * nSize);
				}
			}
			break;
		}

		m_AlterRect.merge(area);
	}

	/**
	 *
	 * \param nValue 
	 * \param area 
	 */
	void			TerrainPageEditor::alterEnd(int nValue)
	{
		switch( nValue )
		{
		case 0:
			{
				uint32 nSize = m_AlterRect.width() * m_AlterRect.height();
				if(nSize && m_pSaveHeight)
				{
					float*	pData	= new float[nSize];
					int		nPos	= 0;	
					int		nRowSize= m_pTerrain->getSize();

					for(int y=m_AlterRect.top; y<m_AlterRect.bottom; y++)
					{
						for(int x=m_AlterRect.left; x<m_AlterRect.right; x++)
						{
							pData[nPos] = m_pSaveHeight[y * nRowSize + x];

							++ nPos;
						}
					}

					String name;
					getPropertyValue(terrainPageName[TERRAINPAGE_PLUGIN_NAME], name);
					int nPageX;
					getPropertyValue(terrainPageName[TERRAINPAGE_PAGEX], nPageX);
					int nPageY;
					getPropertyValue(terrainPageName[TERRAINPAGE_PAGEY], nPageY);
					
					delete [] pData;
					delete [] m_pSaveHeight;
					m_pSaveHeight = NULL;
					
					m_AlterRect = Rect(0, 0, 0, 0);
				}
			}
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	TerrainPageEditorFactory::TerrainPageEditorFactory(const String& factoryName)
		: EditorPluginFactory(factoryName)
	{

	}

	/**
	 *
	 * \return 
	 */
	TerrainPageEditorFactory::~TerrainPageEditorFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*		TerrainPageEditorFactory::createPlugin(const SEditorPluginAdp& ssadp, 
		EditorPlugin* pParent)
	{
		const STerrainPageEditorAdp& adp = static_cast<const STerrainPageEditorAdp&>(ssadp);

		TerrainPageEditor* pTerrainPageEditor = new TerrainPageEditor(adp.pluginName, adp.nPageX, adp.nPageY, adp.vPos, adp.nMinBatchSize, 
			adp.nMaxBatchSize, adp.nLayerCount, adp.tpl, adp.bAtOnceLoad);
		if (pTerrainPageEditor)
		{
			// 设置删除优先级
			pTerrainPageEditor->setPriority(PRIORITY_NORMAL);

			LogManager::getSingleton().logMessage("Create editor plugin : " + adp.pluginName, LML_NORMAL);

			if (pParent)
				pParent->registerPlugin(pTerrainPageEditor);

			return pTerrainPageEditor;
		}

		return NULL;
	}
}