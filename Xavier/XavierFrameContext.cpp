#include "StdAfx.h"
#include "XavierFrameContext.h"
#include "XavierDecalCursor.h"
#include "OgreTSSDK.h"
#include "OgreSSSDK.h"

using namespace Ogre;

/**
 *
 * \param void 
 * \return 
 */
XavierFrameContext::XavierFrameContext(void) : m_nState(EDIT_STATE_INVALID)
{
}

/**
 *
 * \param void 
 * \return 
 */
XavierFrameContext::~XavierFrameContext(void)
{
}

/**
 *
 * \param evt 
 * \return 
 */
bool	XavierFrameContext::frameStarted(const FrameEvent& evt)
{
	return true;
}

/**
 *
 * \param evt 
 * \return 
 */
bool	XavierFrameContext::frameRenderingQueued(const FrameEvent& evt)
{
	if (m_nState == EDIT_STATE_PAINT)
	{
		// 获取当前鼠标位置
		Vector3 vPos = XavierDecalCursor::getSingleton().getPosition();
		
		TerrainGroupServer* pTerrainServer = static_cast<TerrainGroupServer*>(
			System::getSingleton().getServer(SERVER_TERRAIN_GROUP)
			);
		if (pTerrainServer)
		{
			TerrainGroup* pGroup = pTerrainServer->getTerrainGroup();
			if (pGroup)
			{
				TerrainGroup::TerrainList tl;

				Sphere sphere(vPos, pGroup->getTerrainWorldSize() * 0.02);
				pGroup->sphereIntersects(sphere,
					&tl);

				TerrainGroup::TerrainList::iterator it = tl.begin();
				while( it != tl.end() )
				{
					execturTerrain(*it, vPos, evt.timeSinceLastFrame);
					it ++;
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
bool	XavierFrameContext::frameEnded(const FrameEvent& evt)
{
	return true;
}

/**
 *
 * \param nState 
 */
void	XavierFrameContext::changeState(int nState)
{
	m_nState = nState;
}

/**
 *
 * \param terrain 
 */
void	XavierFrameContext::execturTerrain(Ogre::Terrain* terrain, const Ogre::Vector3& vCenter, float fElapsed)
{
	Vector3 vPos;
	terrain->getTerrainPosition(vCenter, &vPos);

	TerrainLayerBlendMap* layer = terrain->getLayerBlendMap(2);
	// we need image coords
	Real imgSize = terrain->getLayerBlendMapSize();
	long startx = (vPos.x - 0.02) * imgSize;
	long starty = (vPos.y - 0.02) * imgSize;
	long endx = (vPos.x + 0.02) * imgSize;
	long endy= (vPos.y + 0.02) * imgSize;
	startx = std::max(startx, 0L);
	starty = std::max(starty, 0L);
	endx = std::min(endx, (long)imgSize);
	endy = std::min(endy, (long)imgSize);
	for (long y = starty; y <= endy; ++y)
	{
		for (long x = startx; x <= endx; ++x)
		{
			Real tsXdist = (x / imgSize) - vPos.x;
			Real tsYdist = (y / imgSize)  - vPos.y;

			Real weight = std::min((Real)1.0, 
				Math::Sqrt(tsYdist * tsYdist + tsXdist * tsXdist) / Real(0.5 * 0.02));
			weight = 1.0 - (weight * weight);

			float paint = weight * fElapsed*5;
			size_t imgY = imgSize - y;
			float val;
			val = layer->getBlendValue(x, imgY) + paint;
			val = Math::Clamp(val, 0.0f, 1.0f);
			layer->setBlendValue(x, imgY, val);

		}
	}

	layer->update();
}
