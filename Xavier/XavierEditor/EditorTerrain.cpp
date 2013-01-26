#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorTerrain.h"
#include "EditorSceneManager.h"
#include "EditorPluginManager.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param pluginName 
	 * \param fMaxPixelError 
	 * \param nCompositeMapSize 
	 * \param fCompositeMapDistance 
	 * \param nLightMapSize 
	 * \param nLayerBlendMapSize 
	 * \param fSkirtSize 
	 * \param clrCompositeMapDiffuse 
	 * \param nTerrainSize 
	 * \param fWorldSize 
	 * \return 
	 */
	EditorTerrain::EditorTerrain(const String& pluginName, float fMaxPixelError, uint16 nCompositeMapSize, float fCompositeMapDistance,
		uint16 nLightMapSize, uint16 nLayerBlendMapSize, float fSkirtSize,const ColourValue& clrCompositeMapDiffuse, uint16 nTerrainSize, float fWorldSize)
		: EditorPlugin(pluginName), m_pGlobalOptions(NULL), m_pTerrainGroup(NULL)
	{
		// get viewport plugin
		m_pViewporPlugin = static_cast<EditorViewport*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT)
			);
		if (m_pViewporPlugin == NULL)
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"Can't find editor plugin : " + EDITOR_VIEWPORT);
		}
		
		// configure all
		if (configure(fMaxPixelError, nCompositeMapSize, fCompositeMapDistance, nLightMapSize, nLayerBlendMapSize, fSkirtSize,
			clrCompositeMapDiffuse, nTerrainSize, fWorldSize))
		{
			
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorTerrain::~EditorTerrain()
	{
		SAFE_DELETE(m_pGlobalOptions);
		SAFE_DELETE(m_pTerrainGroup);
	}

	/**
	 *
	 * \param fMaxPixelError 
	 * \param nCompositeMapSize 
	 * \param fCompositeMapDistance 
	 * \param nLightMapSize 
	 * \param nLayerBlendMapSize 
	 * \param fSkirtSize 
	 * \param clrCompositeMapDiffuse 
	 * \param nTerrainSize 
	 * \param fWorldSize 
	 * \return 
	 */
	bool	EditorTerrain::configure(float fMaxPixelError, uint16 nCompositeMapSize, float fCompositeMapDistance, uint16 nLightMapSize,
		uint16 nLayerBlendMapSize, float fSkirtSize, const ColourValue& clrCompositeMapDiffuse, uint16 nTerrainSize, float fWorldSize)
	{
		EditorSceneManager* pPlugin = static_cast<EditorSceneManager*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_SCENEPLUGIN_NAME)
			);
		if (pPlugin)
		{
			SceneManager* pSceneManager = pPlugin->getSceneManager();
			if (pSceneManager)
			{
				// global options
				m_pGlobalOptions = new TerrainGlobalOptions();
				m_pGlobalOptions->setCompositeMapDiffuse(clrCompositeMapDiffuse);
				m_pGlobalOptions->setMaxPixelError(fMaxPixelError);
				m_pGlobalOptions->setCompositeMapDistance(fCompositeMapDistance);

				m_pGlobalOptions->setCompositeMapSize(nCompositeMapSize);
				m_pGlobalOptions->setCompositeMapDistance(fCompositeMapDistance);
				m_pGlobalOptions->setLightMapSize(nLightMapSize);

				m_pGlobalOptions->setLayerBlendMapSize(nLayerBlendMapSize);
				m_pGlobalOptions->setSkirtSize(fSkirtSize);

				ColourValue clrAmbientLinght = pSceneManager->getAmbientLight();
				m_pGlobalOptions->setCompositeMapAmbient(clrAmbientLinght);
				
				// create terrain group
				m_pTerrainGroup = new TerrainGroup(pSceneManager, Terrain::ALIGN_X_Z, nTerrainSize, fWorldSize);
				if (m_pTerrainGroup)
				{
					m_pTerrainGroup->setOrigin(Vector3::ZERO);
				}
			}
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	bool			EditorTerrain::configureBrush(SceneManager* pSceneManager)
	{
		if (pSceneManager == NULL)
			return 0;

		return true;
	}

	/**
	 *
	 * \return 
	 */
	TerrainGroup*	EditorTerrain::getTerrainGroup() const
	{
		return m_pTerrainGroup;
	}

	

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorTerrain::OnMouseMove(const Vector2& vPos)
	{
		EditorPlugin::OnMouseMove(vPos);
		
		if (m_pViewporPlugin)
		{
			Ray ray;
			if (m_pViewporPlugin->getMouseRay(vPos, ray))
			{

			}
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	EditorTerrrainFactory::EditorTerrrainFactory(const String& factoryName)
		: EditorPluginFactory(factoryName)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorTerrrainFactory::~EditorTerrrainFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*		EditorTerrrainFactory::createPlugin(const SEditorPluginAdp& ssadp, 
		EditorPlugin* pParent)
	{
		const SEditorPluginTerrainAdp& adp = static_cast<const SEditorPluginTerrainAdp&>(ssadp);

		EditorTerrain* pEditorTerrain = new EditorTerrain(adp.pluginName, adp.fMaxPixelError, adp.nCompositeMapSize, adp.fCompositeMapDistance,
			adp.nLightMapSize, adp.nLayerBlendMapSize, adp.fSkirtSize, adp.clrCompositeMapDiffuse, adp.nTerrainSize, adp.fWorldSize);
		if (pEditorTerrain)
		{
			// ����ɾ�����ȼ�
			pEditorTerrain->setPriority(PRIORITY_LOW);

			LogManager::getSingleton().logMessage(LML_NORMAL,
				"Create editor plugin : " + adp.pluginName);

			if (pParent)
				pParent->registerPlugin(pEditorTerrain);

			return pEditorTerrain;
		}

		return NULL;
	}
}