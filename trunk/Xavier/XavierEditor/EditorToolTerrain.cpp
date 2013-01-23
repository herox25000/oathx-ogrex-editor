#include "stdafx.h"
#include "EditorTool.h"
#include "EditorToolTerrain.h"

namespace Ogre
{
	static const String		TERRAIN_DECALMESH_NAME		= "TerrainDecalMesh";
	static const String		TERRAIN_DECALMESH_MATERIAL	= "System/DecalMesh";

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
	EditorToolTerrain::EditorToolTerrain(const String& name, float fMaxPixelError, 
		float fCompositeMapDistance, const ColourValue& clrCompositeMapDiffuse, int nTerrainSize, float fWorldSize, int nMinBatchSize, int nMaxBatchSize,
		float fInputScale, const String& texture, const Vector3& vOrigin)
		: EditorTool(name), m_pTerrainSystem(NULL), m_pDecalMesh(NULL)
	{		
		SceneManager* pSceneManager = World::getSingletonPtr()->getSceneManager();
		if (pSceneManager)
		{
			// create terrain system
			m_pTerrainSystem = new TerrainSystem(fMaxPixelError, fCompositeMapDistance, clrCompositeMapDiffuse,
				nTerrainSize, fWorldSize, nMinBatchSize, nMaxBatchSize, fInputScale, texture, vOrigin);
			if (m_pTerrainSystem)
			{
				m_pTerrainSystem->defineTerrain(0, 0, true);
			}

			// create terrain decal
			m_pDecalMesh = new DecalMesh(pSceneManager, m_pTerrainSystem,
				TERRAIN_DECALMESH_NAME, 1, TERRAIN_DECALMESH_MATERIAL);
			m_pDecalMesh->setPosition(Vector3(0, 0, 0));
		}

		Root::getSingleton().addFrameListener(this);
	}

	/**
	 *
	 * \return 
	 */
	EditorToolTerrain::~EditorToolTerrain()
	{
		if (m_pDecalMesh)
		{
			delete m_pDecalMesh;
			m_pDecalMesh = NULL;
		}

		delete m_pTerrainSystem;
		m_pTerrainSystem = NULL;
	}

	/**
	 *
	 * \param terrain 
	 * \param vCntre 
	 * \param timeElapsed 
	 */
	void	EditorToolTerrain::upheave(Terrain* pTerrain, const Vector3& vCntre, bool bUpheave, Real timeElapsed)
	{
		if (pTerrain)
		{
			Vector3 vPos;
			pTerrain->getTerrainPosition(vCntre, &vPos);

			if (m_pDecalMesh)
			{
				// get bursh  radius
				float fBurshRaidus = m_pDecalMesh->getRaidus();
				
				// calc
				Real fTerrainSize = (pTerrain->getSize() - 1);
				long startx	= max((vPos.x - fBurshRaidus) * fTerrainSize, 0L);
				long starty	= max((vPos.y - fBurshRaidus) * fTerrainSize, 0L);
				long endx	= min((vPos.x + fBurshRaidus) * fTerrainSize,
					(long)fTerrainSize);
				long endy	= min((vPos.y + fBurshRaidus) * fTerrainSize, 
					(long)fTerrainSize);

				for (long y = starty; y <= endy; ++y)
				{
					for (long x = startx; x <= endx; ++x)
					{
						Real fXdist = (x / fTerrainSize) - vPos.x;
						Real fYdist = (y / fTerrainSize) - vPos.y;

						Real fWeight = min((Real)1.0, 
							Math::Sqrt(fYdist * fYdist + fXdist * fXdist) / Real(0.5 * nBurshRaidus));
						fWeight = 1.0 - (fWeight * fWeight);

						float fAddHeight = fWeight * 250.0 * timeElapsed;
						float fNewheight;
						if (bUpheave)
							fNewheight = pTerrain->getHeightAtPoint(x, y) + fAddHeight;
						else
							fNewheight = pTerrain->getHeightAtPoint(x, y) - fAddHeight;
		
						pTerrain->setHeightAtPoint(x, y, fNewheight);
					}
				}
			}
		}
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorToolTerrain::OnMouseMove(const Vector2& vPos)
	{
		if (m_pDecalMesh)
		{
			Camera* pCamera = World::getSingletonPtr()->getCamera();
			if (!pCamera)
				return 0;

			Viewport* pViewprot = pCamera->getViewport();
			if (pViewprot)
			{
				Ray ray = pCamera->getCameraToViewportRay(vPos.x / pViewprot->getActualWidth(), 
					vPos.y / pViewprot->getActualHeight());
				
				Vector3 vHit;
				if (m_pTerrainSystem->rayIntersects(ray, vHit))
				{
					m_pDecalMesh->setPosition(vHit);
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
	bool	EditorToolTerrain::frameStarted(const FrameEvent& evt)
	{
		return true;
	}

	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool	EditorToolTerrain::frameRenderingQueued(const FrameEvent& evt)
	{
		return true;
	}

	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool	EditorToolTerrain::frameEnded(const FrameEvent& evt)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolTerrainFactory::EditorToolTerrainFactory(const String& name)
		: EditorToolFactory(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorToolTerrainFactory::~EditorToolTerrainFactory()
	{
		
	}

	/**
	 *
	 * \param seadp 
	 * \return 
	 */
	EditorTool*	EditorToolTerrainFactory::createEditorTool(const SEditorAdp& seadp)
	{
		const SEditorTerrainAdp& adp = static_cast<const SEditorTerrainAdp&>(seadp);

		return new EditorToolTerrain(adp.name, adp.fMaxPixelError, adp.fCompositeMapDistance, adp.clrCompositeMapDiffuse,
			adp.nTerrainSize, adp.fWorldSize, adp.nMinBatchSize, adp.nMaxBatchSize, adp.fInputScale, adp.texture, adp.vOrigin);
	}
}