#include "stdafx.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorTerrain.h"
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
		: EditorPlugin(pluginName), m_pGlobalOptions(NULL), m_pTerrainGroup(NULL), m_pBrush(NULL), m_bShift(false), m_bActive(false)
	{
		// get viewport plugin
		m_pViewporPlugin = static_cast<EditorViewport*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_VIEWPORT)
			);
		if (m_pViewporPlugin == NULL)
		{
			TKLogEvent("Can't find editor plugin : " + EDITOR_VIEWPORT,
				LML_CRITICAL);
		}

		m_nActionValue	= ETM_NONE;
		m_nCurAction	= ETM_NONE;

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
		SAFE_DELETE(m_pBrush);
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
				
				m_pBrush = new MeshBrush(pSceneManager, "System/BrushMesh", 6, 25, "sharp_circular.png");
		
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
	 * \return 
	 */
	MeshBrush*		EditorTerrain::getMeshBrush() const
	{
		return m_pBrush;
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
	 * \param nActionValue 
	 */
	void			EditorTerrain::setActionValue(int nActionValue)
	{
		m_nActionValue	= nActionValue;
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
		Rect& mapRect, int nSize, float fRaidus)
	{
		if (m_pBrush == NULL)
			return 0;

		float fBrushSize	= fRaidus;
		int mMapBrushSize	= (float)fBrushSize; 
		float halfSize		= (float)fBrushSize / 2.0f;

		float tx = vPos.x - halfSize;
		float ty = vPos.y - halfSize;

		int mapX = tx;
		mapX += (int)(tx * 2.0f) - (mapX * 2);

		int mapY = ty;
		mapY += (int)(ty * 2.0f) - (mapY * 2);

		mapRect		= Rect(mapX, mapY, mMapBrushSize + mapX, mMapBrushSize + mapY);
		brushRect	= Rect(0, 0, fBrushSize, fBrushSize);

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

		brushRect.left		*= (float)BRUSH_DATA_SIZE / (float)fBrushSize;
		brushRect.right		*= (float)BRUSH_DATA_SIZE / (float)fBrushSize;
		brushRect.top		*= (float)BRUSH_DATA_SIZE / (float)fBrushSize;
		brushRect.bottom	*= (float)BRUSH_DATA_SIZE / (float)fBrushSize;

		return true;
	}

	/**
	 *
	 * \param pPahe 
	 * \param Vector3&vPos 
	 * \param fAvg 
	 * \param nSampleCount 
	 */
	void			EditorTerrain::calcSmoothingFactor(EditorTerrainPage* pPage, Vector3&vPos, float& fAvg, int& nSampleCount)
	{
		Terrain* pTerrain = pPage->getTerrain();
		
		Rect brushRect;
		Rect mapRect;

		int nMapSize = pTerrain->getSize();
		vPos.x *= (float)(nMapSize - 1);
		vPos.y *= (float)(nMapSize - 1);

		fAvg			= 0.0f;
		nSampleCount	= 0;

		if(!optRect(vPos, brushRect, mapRect, nMapSize, m_pBrush->getRadius()))
			return;

		float* pHeightData = pTerrain->getHeightData();
		int nMapPos;

		for(int j=mapRect.top; j<mapRect.bottom; j++)
		{
			nMapPos = (j * nMapSize) + mapRect.left;

			for(int i= mapRect.left; i<mapRect.right; i++)
			{
				fAvg += pHeightData[nMapPos];
				++nMapPos;
			}
		}

		nSampleCount = (mapRect.right - mapRect.left) * (mapRect.bottom - mapRect.top);
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
		if (pPage == NULL || m_pBrush == NULL)
			return 0;
		
		Terrain* pTerrain = pPage->getTerrain();
		if (pTerrain)
		{
			int nBlendMapSize = pTerrain->getLayerBlendMapSize();
			vPos.x	*= nBlendMapSize;
			vPos.y	= (1.0f - vPos.y) * (float)(nBlendMapSize);

			float	fIntensity	= m_pBrush->getIntensity();
			float	fBrushSize	= m_pBrush->getRadius();
			fBrushSize *= (5 + (fBrushSize / BRUSH_DATA_SIZE));
			Rect	brushRect;
			Rect	mapRect;
			if (!optRect(vPos, brushRect, mapRect, nBlendMapSize, fBrushSize))
				return 0;
			
			int nLayerID = pPage->getLayerID(m_BlendTexture);
			if (nLayerID == INVALID_LAYER)
			{
				nLayerID = pPage->addLayer(m_BlendTexture, m_BlendNormal, 30);
			}

			if (nLayerID == INVALID_LAYER)
			{
				TKLogEvent("Waring: Supports up to 5 layers texture blend",
					LML_CRITICAL);

				return 0;
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
					float*	pBrushData	= m_pBrush->getBrushData();
					
					for (int i=nLayerID; i<nLayerCount; i++)
					{
						pBlendMaps[i] = pTerrain->getLayerBlendMap(i);
						pBlendData[i] = pBlendMaps[i]->getBlendPointer();
					}

					float	fFactor	= fIntensity * timePassed * 0.2f;
					float	fRatio	= (float)(BRUSH_DATA_SIZE) / fBrushSize;
					int		nRight	= brushRect.right;

					brushRect.right	= BRUSH_DATA_SIZE - brushRect.left;
					brushRect.left	= BRUSH_DATA_SIZE - nRight;

					float	fBrushPos;
					int		nMapPos;

					if (!m_bShift)
					{
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

								float fVal	= pLayerData[nMapPos] + (pBrushData[(int)fBrushPos] * fFactor);
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
					else
					{
						for (int j=mapRect.top; j<mapRect.bottom; j++)
						{
							fBrushPos	= (brushRect.top + (int)((j - mapRect.top) * fRatio)) * BRUSH_DATA_SIZE;
							fBrushPos	+= brushRect.right;

							nMapPos		= j * nBlendMapSize + mapRect.left;

							for (int i=mapRect.left; i<mapRect.right; i++)
							{
								fBrushPos -= fRatio;

								float fVal = pLayerData[nMapPos] - (pBrushData[(int)fBrushPos] * fFactor);

								if(fVal < 0.0f)
									fVal = 0.0f;

								pLayerData[nMapPos] = fVal;

								++nMapPos;
							}
						}

						pLayerMaps->dirtyRect(mapRect);
						pLayerMaps->update();
					}
				}
			}
		}

		return true;
	}

	/**
	 *
	 * \param pPage 
	 * \param vPos 
	 * \param timePassed 
	 * \return 
	 */
	bool			EditorTerrain::optDeform(EditorTerrainPage* pPage, Vector3& vPos, float timePassed)
	{
		if (pPage == NULL || m_pBrush == NULL)
			return 0;
	
		Terrain* pTerrain = pPage->getTerrain();
		if (pTerrain == NULL)
			return 0;

		uint16 nTerrainSize = pTerrain->getSize();
		vPos.x *= (float)(nTerrainSize - 1);
		vPos.y *= (float)(nTerrainSize - 1);

		Rect	brushRect;
		Rect	mapRect;
		if (!optRect(vPos, brushRect, mapRect,  nTerrainSize, m_pBrush->getRadius()))
			return 0;

		pPage->alterStart(0, mapRect);

		float	fIntensity	= m_pBrush->getIntensity() * ((m_bShift) ? -1 : 1);
		float	fBrushSize	= m_pBrush->getRadius();
		float*	pBrushData	= m_pBrush->getBrushData();
		float*	pHeightData	= pTerrain->getHeightData();
		if (pHeightData)
		{
			float	fRatio	= (float)(BRUSH_DATA_SIZE) / fBrushSize;
			float	fBrushPos;
			int		nMapPos;

			for (int j=mapRect.top; j<mapRect.bottom; j++)
			{
				fBrushPos	= (brushRect.top + (int)((j - mapRect.top) * fRatio)) * BRUSH_DATA_SIZE;
				fBrushPos	+= brushRect.left;
				nMapPos		= (j * nTerrainSize) + mapRect.left;

				for(int i=mapRect.left; i<mapRect.right; i++)
				{
					float fVal = pHeightData[nMapPos] + (pBrushData[(int)fBrushPos] * fIntensity * timePassed);
					pHeightData[nMapPos] = fVal;
					
					++ nMapPos;

					fBrushPos += fRatio;
				}
			}

			pTerrain->dirtyRect(mapRect);

			if (m_pTerrainGroup)
				m_pTerrainGroup->update();
		}
	
		return true;
	}

	/**
	 *
	 * \param pPage 
	 * \param vPos 
	 * \param timePassed 
	 * \return 
	 */
	bool			EditorTerrain::optSmooth(EditorTerrainPage* pPage, Vector3& vPos, float fAvg, float timePassed)
	{
		Terrain* pTerrain = pPage->getTerrain();
		if (pTerrain == NULL)
			return 0;


		float*	pHeightData	= pTerrain->getHeightData();
		float*	pBrushData	= m_pBrush->getBrushData();
		float	fIntensity	= m_pBrush->getIntensity();
		float	fRadius		= m_pBrush->getRadius();

		int nMapSize	= pTerrain->getSize();
		vPos.x *= (float)(nMapSize - 1);
		vPos.y *= (float)(nMapSize - 1);

		Rect	brushRect;
		Rect	mapRect;
		if(!optRect(vPos, brushRect, mapRect, nMapSize, fRadius))
			return 0;

		float	fRatio		= (float)BRUSH_DATA_SIZE / fRadius;
		float	fFactor		= fIntensity * timePassed * 0.03f;

		float	brushPos;
		int		nMapPos;

		if(!m_bShift)
		{
			for(int j=mapRect.top; j<mapRect.bottom; j++)
			{
				brushPos = (brushRect.top + (int)((j - mapRect.top) * fRatio)) * BRUSH_DATA_SIZE;
				brushPos += brushRect.left;
				nMapPos = (j * nMapSize) + mapRect.left;

				for(int i = mapRect.left;i < mapRect.right;i++)
				{
					float fVal = fAvg - pHeightData[nMapPos];
					fVal = fVal * min(pBrushData[(int)brushPos] * fFactor, 1.0f);
					pHeightData[nMapPos] -= fVal;

					++ nMapPos;
					
					brushPos += fRatio;
				}
			}
		}
		else
		{
			for(int j=mapRect.top; j<mapRect.bottom; j++)
			{
				brushPos = (brushRect.top + (int)((j - mapRect.top) * fRatio)) * BRUSH_DATA_SIZE;
				brushPos += brushRect.left;
				nMapPos = (j * nMapSize) + mapRect.left;

				for(int i=mapRect.left; i<mapRect.right; i++)
				{
					float fVal = fAvg - pHeightData[nMapPos];
					fVal = fVal * min(pBrushData[(int)brushPos] * fFactor, 1.0f);
					pHeightData[nMapPos] += fVal;
					
					++ nMapPos;

					brushPos += fRatio;
				}
			}
		}

		pTerrain->dirtyRect(mapRect);

		if (m_pTerrainGroup)
			m_pTerrainGroup->update();

		return true;
	}

	/**
	 *
	 */
	void			EditorTerrain::optStart()
	{
		m_bActive = true;
	}

	/**
	 *
	 */
	void			EditorTerrain::optEnd()
	{
		if (m_bActive)
		{
			m_bActive = false;

			HashMapEditorPluginIter hashPlugin = getPluginIter();
			while( hashPlugin.hasMoreElements() )
			{
				EditorTerrainPage* pPage = static_cast<EditorTerrainPage*>(hashPlugin.getNext());
				if (pPage)
				{
					pPage->alterEnd(0);
				}
			}
		}
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
		if (m_pBrush != NULL && m_nCurAction != ETM_NONE)
		{
			// 当前画刷节点位置
			Vector3 vPos		= m_pBrush->getPosition();
			float fBrushSize	= m_pBrush->getRadius();

			float fWorldSize	= m_pTerrainGroup->getTerrainWorldSize();
			float fMapSize		= m_pTerrainGroup->getTerrainSize();

			TerrainGroup::TerrainList vTerrain;
			float fBrushWorld	= (fWorldSize * fBrushSize) / fMapSize / 2;
			Sphere s(vPos, fBrushWorld);
			m_pTerrainGroup->sphereIntersects(s, &vTerrain);

			// 构建区域
			m_Region.merge(Rect(vPos.x - fBrushWorld, 
				vPos.z - fBrushWorld, 
				vPos.x + fBrushWorld, 
				vPos.z + fBrushWorld));
	
			Vector3 vRegin;
			float	fAvgTotal			= 0.0f;
			float	fSampleCountTotal	= 0;

			if(m_nCurAction == ETM_SMOOTH)
			{
				for (int i=0; i<vTerrain.size(); i++)
				{
					vTerrain[i]->getTerrainPosition(vPos, &vRegin);

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
						float	 fAvg			= 0.0f;
						int		nSampleCount	= 0;
						calcSmoothingFactor(pSelectPage, vRegin, fAvg, nSampleCount);

						fAvgTotal += fAvg;
						fSampleCountTotal += nSampleCount;
					}
				}
			}
			
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
					switch( m_nCurAction )
					{
					case ETM_SPLAT:
						{
							optSplat(pSelectPage, vRegin, evt.timeSinceLastFrame);
						}
						break;
					case ETM_DEFORM:
						{
							optDeform(pSelectPage, vRegin, evt.timeSinceLastFrame);
						}
						break;
					case ETM_SMOOTH:
						{
							optSmooth(pSelectPage, vRegin, fAvgTotal / (float)fSampleCountTotal, 
								evt.timeSinceLastFrame);
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
					if (m_pBrush)
						m_pBrush->setPosition(rayResult.terrain, rayResult.position);
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
		if (m_nActionValue != ETM_NONE)
		{
			m_nCurAction = m_nActionValue;
			optStart();
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorTerrain::OnLButtonUp(const Vector2& vPos)
	{
		if (m_nActionValue != ETM_NONE)
		{
			optEnd();
			m_nCurAction = ETM_NONE;
		}

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

		switch( nChar )
		{
		case VK_SHIFT:
			{
				m_bShift = true;
			}
			break;
		}

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
		switch( nChar )
		{
		case VK_SHIFT:
			{
				m_bShift = 0;
			}
			break;
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	bool			EditorTerrain::OnSetFocus()
	{
		return 0;
	}

	/**
	 *
	 * \return 
	 */
	bool			EditorTerrain::OnLoseFocus()
	{
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

			TKLogEvent("Create editor plugin : " + adp.pluginName,
				LML_NORMAL);

			if (pParent)
				pParent->registerPlugin(pEditorTerrain);

			return pEditorTerrain;
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////
		/**
	 *
	 * \param pSceneManager 
	 * \param materialName 
	 * \param fRaidus 
	 * \return 
	 */
	MeshBrush::MeshBrush(SceneManager* pSceneManager, const String& materialName, float fRaidus, float fIntensity, const String& texture)
		: m_pSceneManager(pSceneManager), m_pBrushMesh(NULL), m_pBrushNode(NULL), m_fRaidus(fRaidus), m_fIntensity(fIntensity), m_pBrushData(NULL)
	{
		m_pBrushData	= new float[BRUSH_DATA_SIZE * BRUSH_DATA_SIZE];
		m_pBrushTexture = TextureManager::getSingletonPtr()->createManual(BRUSH_MESH_NAME, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			TEX_TYPE_2D, 256, 256, 1, 1, PF_A8R8G8B8, TU_DYNAMIC_WRITE_ONLY);
		
		setBrushTexture(texture);

		m_pBrushMesh = new ManualObject(BRUSH_MESH_NAME);
		m_pSceneManager->getRootSceneNode()->attachObject(m_pBrushMesh);

		int x_size = 8;
		int z_size = 8;

		m_pBrushMesh->begin(materialName, RenderOperation::OT_TRIANGLE_LIST);
		for (int i = 0; i <= x_size; i++)
		{
			for (int j = 0; j <= z_size; j++)
			{
				m_pBrushMesh->position(Ogre::Vector3(i, 0, j));
				m_pBrushMesh->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
			}
		}

		for (int i = 0; i < x_size; i++)
		{
			for (int j = 0; j < z_size; j++)
			{
				m_pBrushMesh->quad( 
					i * (x_size + 1) + j,
					i * (x_size + 1) + j + 1,
					(i + 1) * (x_size + 1) + j + 1,
					(i + 1) * (x_size + 1) + j);
			}
		}
		m_pBrushMesh->end();
	}

	/**
	 *
	 * \return 
	 */
	MeshBrush::~MeshBrush()
	{
		if (m_pBrushData != NULL)
		{
			delete []m_pBrushData;
			m_pBrushData = NULL;
		}

		m_pSceneManager->getRootSceneNode()->detachObject(m_pBrushMesh);
		SAFE_DELETE(m_pBrushMesh);
	}

	/**
	 *
	 * \param texture 
	 */
	void			MeshBrush::setBrushTexture(const String& texture)
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
	 * \param pTerrain 
	 * \param vPos 
	 */
	void		MeshBrush::setPosition(Terrain* pTerrain, const Vector3& vPos)
	{
		if (pTerrain)
		{
			Real x1 = vPos.x - m_fRaidus;
			Real z1 = vPos.z - m_fRaidus;

			int x_size = 8;
			int z_size = 8;

			Real x_step = (m_fRaidus * 2) / x_size;
			Real z_step = (m_fRaidus * 2) / z_size;

			m_pBrushMesh->beginUpdate(0);
			for (int i=0; i<=x_size; i++)
			{
				for (int j= 0; j<=z_size; j++)
				{
					float f = pTerrain->getHeightAtWorldPosition(x1, vPos.y, z1);
					m_pBrushMesh->position(Vector3(x1,  f + 0.5, z1));
					m_pBrushMesh->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
					z1 += z_step;
				}
				x1 += x_step;
				z1 = vPos.z - m_fRaidus;
			}

			for (int i=0; i<x_size; i++)
			{
				for (int j=0; j<z_size; j++)
				{
					m_pBrushMesh->quad( 
						i * (x_size + 1) + j,
						i * (x_size + 1) + j + 1,
						(i + 1) * (x_size + 1) + j + 1,
						(i + 1) * (x_size + 1) + j);
				}
			}
			m_pBrushMesh->end();
		}

		m_vBrushPos = vPos;
	}

	/**
	 *
	 * \return 
	 */
	Vector3			MeshBrush::getPosition() const
	{
		return m_vBrushPos;
	}

	/**
	 *
	 * \param fRadius 
	 */
	void			MeshBrush::setRadius(float fRadius)
	{
		m_fRaidus = fRadius;
	}

	/**
	 *
	 * \return 
	 */
	float			MeshBrush::getRadius() const
	{
		return m_fRaidus;
	}

	/**
	 *
	 * \param fBrushIntensity 
	 */
	void			MeshBrush::setIntensity(float fIntensity)
	{
		m_fIntensity = fIntensity;
	}

	/**
	 *
	 * \return 
	 */
	float			MeshBrush::getIntensity() const
	{
		return m_fIntensity;
	}

	/**
	 *
	 * \return 
	 */
	float*			MeshBrush::getBrushData() const
	{
		return m_pBrushData;
	}
}