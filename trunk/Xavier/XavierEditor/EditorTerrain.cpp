#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorTerrain.h"
#include "EditorSceneManager.h"
#include "EditorPluginManager.h"

namespace Ogre
{
	static const uint16	MESH_BRSUH_SIZE	= 6;
	/**
	 *
	 * \param pSceneManager 
	 * \param fRaidus 
	 * \return 
	 */
	MeshBrush::MeshBrush(SceneManager* pSceneManager, TerrainGroup* pTerrainGroup, float fBrushSize, const String& materialName)
		: m_pSceneManager(pSceneManager), m_pTerrainGroup(pTerrainGroup), m_pDecalMesh(NULL), m_fBrushSize(fBrushSize)
	{
		createDecalMesh(materialName);
	}

	/**
	 *
	 * \return 
	 */
	MeshBrush::~MeshBrush()
	{
		m_pSceneManager->getRootSceneNode()->detachObject(m_pDecalMesh);
		SAFE_DELETE(m_pDecalMesh);
	}

	/**
	 *
	 * \param fRaidus 
	 */
	void	MeshBrush::createDecalMesh(const String& materialName)
	{
		m_pDecalMesh = new Ogre::ManualObject(BRUSH_MESH_NAME);
		m_pSceneManager->getRootSceneNode()->attachObject(m_pDecalMesh);

		int x_size = 6;
		int z_size = 6;

		m_pDecalMesh->begin(materialName, Ogre::RenderOperation::OT_TRIANGLE_LIST);
		for (int i=0; i<=x_size; i++)
		{
			for (int j=0; j<=z_size; j++)
			{
				m_pDecalMesh->position(Ogre::Vector3(i, 0, j));
				m_pDecalMesh->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
			}
		}

		for (int i=0; i<x_size; i++)
		{
			for (int j=0; j<z_size; j++)
			{
				m_pDecalMesh->quad( i * (x_size+1) + j,
					i * (x_size+1) + j + 1,
					(i + 1) * (x_size+1) + j + 1,
					(i + 1) * (x_size+1) + j);
			}
		}
		m_pDecalMesh->end();
	}

	/**
	 *
	 * \param x 
	 * \param z 
	 * \param fRaidus 
	 */
	void	MeshBrush::setPosition(const Vector3& vPos)
	{
		Ogre::Real x1 = vPos.x - m_fBrushSize;
		Ogre::Real z1 = vPos.z - m_fBrushSize;

		int x_size = 6;
		int z_size = 6;

		Ogre::Real x_step = m_fBrushSize * 2 / x_size;
		Ogre::Real z_step = m_fBrushSize * 2 / z_size;

		m_pDecalMesh->beginUpdate(0);

		for (int i=0; i<=x_size; i++)
		{
			for (int j=0; j<=z_size; j++)
			{
				m_pDecalMesh->position(Ogre::Vector3(x1, 0.5, z1));
				m_pDecalMesh->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
				z1 += z_step;
			}
			x1 += x_step;
			z1 = vPos.z - m_fBrushSize;
		}

		for (int i=0; i<x_size; i++)
		{
			for (int j=0; j<z_size; j++)
			{
				m_pDecalMesh->quad( i * (x_size+1) + j,
					i * (x_size+1) + j + 1,
					(i + 1) * (x_size+1) + j + 1,
					(i + 1) * (x_size+1) + j);
			}
		}
		m_pDecalMesh->end();
	}

	/**
	 *
	 * \param fRaidus 
	 */
	void	MeshBrush::setBrushSize(float fBrushSize)
	{
		m_fBrushSize = fBrushSize;
	}

	/**
	 *
	 * \return 
	 */
	float	MeshBrush::getBrushSize() const
	{
		return m_fBrushSize;
	}

	/**
	 *
	 * \param x 
	 * \param z 
	 * \return 
	 */
	float	MeshBrush::getTerrainHeight(const Vector3& vPos)
	{
		return 0;
	}

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
		: EditorPlugin(pluginName), m_pGlobalOptions(NULL), m_pTerrainGroup(NULL), m_pBrush(NULL)
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

				m_pBrush = new MeshBrush(pSceneManager, m_pTerrainGroup, 5, "System/BrushMesh");

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
				TerrainGroup::RayResult rayResult =	m_pTerrainGroup->rayIntersects(ray);
				if (rayResult.hit)
				{
					if (m_pBrush)
					{
						m_pBrush->setPosition(rayResult.position);
					}
				}
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
			// 设置删除优先级
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