#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorTerrain.h"
#include "EditorTerrainPage.h"
#include "EditorSceneManager.h"
#include "EditorPluginManager.h"

namespace Ogre
{
	static const uint16		BRUSH_DATA_SIZE	= 128;

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
		: EditorPlugin(pluginName), m_pGlobalOptions(NULL), m_pTerrainGroup(NULL), m_fBrushSize(1), m_pBrushNode(NULL), m_nEtmValue(ETM_NONE)
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
		
		// add frame update
		Root::getSingleton().addFrameListener(this);
	}

	/**
	 *
	 * \return 
	 */
	EditorTerrain::~EditorTerrain()
	{
		if (m_pBrushData)
		{
			delete [] m_pBrushData;
			m_pBrushData = NULL;
		}

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
				
				// create brush node
				m_pBrushNode = pSceneManager->getRootSceneNode()->createChildSceneNode();
				if (m_pBrushNode)
				{
					// brush data
					m_pBrushData	= new float[BRUSH_DATA_SIZE * BRUSH_DATA_SIZE];
					m_pBrushTexture = TextureManager::getSingletonPtr()->createManual(BRUSH_MESH_NAME,ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
						TEX_TYPE_2D, 256, 256, 1, 1, PF_A8R8G8B8, TU_DYNAMIC_WRITE_ONLY);
				}

				setBrushSize(52);
				setBrushName("sharp_circular.png");
				setBlendTexture("ice_4_diffusespecular.dds", "ice_4_normalheight.dds");
				return true;
			}
		}

		return 0;
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
	 * \param nBrushSize 
	 */
	void			EditorTerrain::setBrushSize(float nBrushSize)
	{
		m_fBrushSize = nBrushSize;
	}

	/**
	 *
	 * \return 
	 */
	float			EditorTerrain::getBrushSize() const
	{
		return m_fBrushSize;
	}

	/**
	 *
	 * \param texture 
	 */
	void			EditorTerrain::setBrushName(const String& texture)
	{
		if(!m_pBrushTexture.isNull())
		{
			Image image;
			image.load(texture, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			uint8* pData = new uint8[image.getWidth() * image.getHeight() * 3];
			PixelBox resultBox(image.getWidth(), 
				image.getHeight(), 
				1, 
				PF_B8G8R8, 
				pData);
			PixelUtil::bulkPixelConversion(image.getPixelBox(), resultBox);

			resultBox.setConsecutive();

			for (uint32 i=0, idx=0; i<image.getWidth() * image.getHeight(); i++)
			{
				pData[idx + 0] = 0;
				pData[idx + 1] = 0;
				pData[idx + 2] = (pData[idx + 2] * 0.8f);

				idx += 3;
			}

			m_pBrushTexture->setWidth(
				image.getWidth());
			m_pBrushTexture->setHeight(image.getHeight());

			HardwarePixelBufferSharedPtr hps = m_pBrushTexture->getBuffer();
			hps->blitFromMemory(resultBox);
			delete [] pData;

			image.resize(BRUSH_DATA_SIZE, BRUSH_DATA_SIZE);
			uint32 nPos = 0;
			ColourValue c;
			for(uint32 y=0; y<BRUSH_DATA_SIZE; y++)
			{
				nPos = ((BRUSH_DATA_SIZE - 1) - y) * BRUSH_DATA_SIZE;
				for(uint32 x=0; x<BRUSH_DATA_SIZE; x++)
				{
					c = image.getColourAt(x,y,0);
					m_pBrushData[nPos] = c.r;
					nPos++;
				}
			}
		}
	}
	
	/**
	 *
	 * \param vPos 
	 */
	void			EditorTerrain::setBrushPosition(const Vector3& vPos)
	{
		m_pBrushNode->setPosition(vPos);
	}

	/**
	 *
	 * \return 
	 */
	Vector3			EditorTerrain::getBrushPosition() const
	{
		return m_pBrushNode->getPosition();
	}

	/**
	 *
	 * \param texture 
	 * \param normal 
	 */
	void			EditorTerrain::setBlendTexture(const String& texture, const String& normal)
	{
		m_BlendTexture	= texture;
		m_BlendNormal	= normal;
	}

	/**
	 *
	 * \param vPos 
	 * \param brushRect 
	 * \param mapRect 
	 * \param nSize 
	 * \return 
	 */
	bool			EditorTerrain::optRect(const Vector3& vPos, Rect& brushRect,
		Rect& mapRect, int nSize)
	{
		int mMapBrushSize	= (float)m_fBrushSize; 
		float halfSize		= (float)m_fBrushSize / 2.0f;

		float tx = vPos.x - halfSize;
		float ty = vPos.y - halfSize;

		int mapX = tx;
		mapX += (int)(tx * 2.0f) - (mapX * 2);

		int mapY = ty;
		mapY += (int)(ty * 2.0f) - (mapY * 2);

		mapRect		= Rect(mapX, mapY, mMapBrushSize + mapX, mMapBrushSize + mapY);
		brushRect	= Rect(0,0,m_fBrushSize,m_fBrushSize);

		if(mapRect.left < 0)
		{
			brushRect.left += (0 - mapRect.left);
			mapRect.left = 0;
		}

		if(mapRect.top < 0)
		{
			brushRect.top += (0 - mapRect.top);
			mapRect.top = 0;
		}

		if(mapRect.right > nSize)
		{
			brushRect.right -= (mapRect.right - nSize);
			mapRect.right = nSize;
		}

		if(mapRect.bottom > nSize)
		{
			brushRect.bottom -= (mapRect.bottom - nSize);
			mapRect.bottom = nSize;
		}

		if(((mapRect.right - mapRect.left) < 1) || ((mapRect.bottom - mapRect.top) < 1))
			return 0;

		brushRect.left *= (float)BRUSH_DATA_SIZE / (float)m_fBrushSize;
		brushRect.right *= (float)BRUSH_DATA_SIZE / (float)m_fBrushSize;
		brushRect.top *= (float)BRUSH_DATA_SIZE / (float)m_fBrushSize;
		brushRect.bottom *= (float)BRUSH_DATA_SIZE / (float)m_fBrushSize;

		return true;
	}

	/**
	 *
	 * \param pPage 
	 * \param vPos 
	 * \param timePassed 
	 */
	bool			EditorTerrain::optPaint(EditorTerrainPage* pPage, Vector3& vPos,
		float timePassed)
	{
		return true;
	}

	/**
	 *
	 * \param pPage 
	 * \param vPos 
	 * \param timePassed 
	 * \return 
	 */
	bool			EditorTerrain::optSplat(EditorTerrainPage* pPage, Vector3& vPos, 
		float timePassed)
	{
		if (pPage == NULL)
			return 0;
		
		Terrain* pTerrain = pPage->getTerrain();
		if (pTerrain)
		{
			int nBlendMapSize = pTerrain->getLayerBlendMapSize();
			vPos.x	*= nBlendMapSize;
			vPos.y	= (1.0f - vPos.y) * (float)(nBlendMapSize);

			Rect	brushRect;
			Rect	mapRect;

			if (!optRect(vPos, brushRect, mapRect, nBlendMapSize))
				return 0;
			
			int nLayerID = pPage->getLayerID(m_BlendTexture);
			if (nLayerID < 0)
			{
				nLayerID = pPage->addLayer(m_BlendTexture, m_BlendNormal, 30);
			}

			int	nLayerCount	= pTerrain->getLayerCount();

			if (nLayerCount > 1)
			{
				TerrainLayerBlendMap*	pBlendMaps[128];
				float*					pBlendData[128];

				TerrainLayerBlendMap*	pLayerMaps = pTerrain->getLayerBlendMap(nLayerID);
				if (pLayerMaps)
				{
					// 当前混合数据
					float*	pLayerData	= pLayerMaps->getBlendPointer();
					
					for (int i=nLayerID; i<nLayerCount; i++)
					{
						pBlendMaps[i] = pTerrain->getLayerBlendMap(i);
						pBlendData[i] = pBlendMaps[i]->getBlendPointer();
					}

					float	fFactor	= 70 * timePassed * 0.2f;
					float	fRatio	= (float)(BRUSH_DATA_SIZE) / m_fBrushSize;
					int		nRight	= brushRect.right;

					brushRect.right	= BRUSH_DATA_SIZE - brushRect.left;
					brushRect.left	= BRUSH_DATA_SIZE - nRight;

					float	fBrushPos;
					int		nMapPos;
					int		u;
					float	fSum;
					
					for (int j=mapRect.top; j<mapRect.bottom; j++)
					{
						fBrushPos	= (brushRect.top + (int)((j - mapRect.top) * fRatio)) * BRUSH_DATA_SIZE;
						fBrushPos	+= brushRect.right;

						nMapPos		= j * nBlendMapSize + mapRect.left;

						for (int i=mapRect.left; i<mapRect.right; i++)
						{
							fBrushPos	-= fRatio;
							fSum		= 0.0f;

							for (u=nLayerID + 1; u<nLayerCount; u++)
							{
								fSum += pBlendData[u][nMapPos];
							}

							float fVal	= pLayerData[nMapPos] + (m_pBrushData[(int)fBrushPos] * fFactor);
							fSum		+= fVal;

							if (fSum > 1.0f)
							{
								float fNormalFactor = 1.0f / fSum;
								pLayerData[nMapPos]	= fVal * fNormalFactor;

								for (u=nLayerID +1; u<nLayerCount; u++)
								{
									pBlendData[u][nMapPos] *= fNormalFactor;
								}
							}
							else
							{
								pLayerData[nMapPos] = fVal;
							}

							++ nMapPos;
						}
					}

					for (u=nLayerID; u<nLayerCount; u++)
					{
						pBlendMaps[u]->dirtyRect(mapRect);
						pBlendMaps[u]->update();
					}
				}
			}
		}

		return true;
	}
	
	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool			EditorTerrain::frameStarted(const FrameEvent& evt)
	{
		return true;
	}

	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool			EditorTerrain::frameRenderingQueued(const FrameEvent& evt)
	{
		if (m_pBrushNode && m_nEtmValue != ETM_NONE)
		{
			// 当前画刷节点位置
			Vector3 vPos		= m_pBrushNode->getPosition();

			float fWorldSize	= m_pTerrainGroup->getTerrainWorldSize();
			float fMapSize		= m_pTerrainGroup->getTerrainSize();

			TerrainGroup::TerrainList vTerrain;
			float fBrushWorld	= (fWorldSize * m_fBrushSize) / fMapSize / 2;
			Sphere s(vPos, fBrushWorld);
			m_pTerrainGroup->sphereIntersects(s, &vTerrain);

			// 构建区域
			m_Region.merge(Rect(vPos.x - fBrushWorld, 
				vPos.z - fBrushWorld, 
				vPos.x + fBrushWorld, 
				vPos.z + fBrushWorld));
	
			Vector3 vRegin;
			for (int i=0; i<vTerrain.size(); i++)
			{
				vTerrain[i]->getTerrainPosition(vPos,
					&vRegin);

				// 选择页
				EditorTerrainPage* pSelectPage = NULL;

				HashMapEditorPluginIter hashPlugin = getPluginIter();
				while( hashPlugin.hasMoreElements() )
				{
					pSelectPage = static_cast<EditorTerrainPage*>(hashPlugin.getNext());
					if (pSelectPage->getTerrain() == vTerrain[i])
						break;
				}
		
				if (pSelectPage)
				{
					switch( m_nEtmValue )
					{
					case ETM_SPLAT:
						{
							optSplat(pSelectPage, vRegin, evt.timeSinceLastFrame);
						}
						break;
					}
				}
			}
		}

		return true;
	}

	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool			EditorTerrain::frameEnded(const FrameEvent& evt)
	{
		return true;
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
				TerrainGroup::RayResult rayResult = m_pTerrainGroup->rayIntersects(ray);
				if (rayResult.hit)
				{
					setBrushPosition(rayResult.position);
				}
			}
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorTerrain::OnLButtonDown(const Vector2& vPos)
	{
		m_nEtmValue = ETM_SPLAT;
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorTerrain::OnLButtonUp(const Vector2& vPos)
	{
		m_nEtmValue = ETM_NONE;
		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			EditorTerrain::OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		if (EditorPlugin::OnKeyDown(nChar, nRepCnt, nFlags))
			return true;

		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			EditorTerrain::OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		return true;
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