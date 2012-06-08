#include "StdAfx.h"
#include "XavierDecalCursor.h"
#include "OgreTSSDK.h"

namespace Ogre
{
	template<>	XavierDecalCursor*	Singleton<XavierDecalCursor>::msSingleton = NULL;
	XavierDecalCursor&	XavierDecalCursor::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	XavierDecalCursor*	XavierDecalCursor::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	static const String		XAVIER_DECAL_CURSOR_NAME		= "XavierDecalCursorDecal";
	static const int		CURSOR_RES						= 6;
	static const String		XAVIER_DECAL_CURSOR_MATERIAL	= "Editor/TerrainMeshDecal";

	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XavierDecalCursor::XavierDecalCursor(Ogre::WorldSpaceServer* pWorldServer, Ogre::TerrainGroupServer* pTerrainServer)
	: m_pWorldServer(pWorldServer), m_pTerrainServer(pTerrainServer), m_pDecalMesh(0),m_fRadius(3.0f)
	{
		createDecalCursor(0); 
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XavierDecalCursor::~XavierDecalCursor(void)
	{
		delete m_pDecalMesh;
	}

	/**
	 *
	 * \param vSize 
	 * \param name 
	 */
	void	XavierDecalCursor::createDecalCursor(float fRaidus)
	{
		m_pDecalMesh = new Ogre::ManualObject(XAVIER_DECAL_CURSOR_NAME);
		m_pWorldServer->getSceneManager()->getRootSceneNode()->attachObject(m_pDecalMesh);

		int x_size = 6;
		int z_size = 6;

		m_pDecalMesh->begin(XAVIER_DECAL_CURSOR_MATERIAL, Ogre::RenderOperation::OT_TRIANGLE_LIST);
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
	 * \param vSize 
	 */
	void	XavierDecalCursor::setDecalCursor(float x, float z, float fRaidus)
	{
		Ogre::Real x1 = x - fRaidus;
		Ogre::Real z1 = z - fRaidus;

		int x_size = 6;
		int z_size = 6;

		Ogre::Real x_step = fRaidus * 2 / x_size;
		Ogre::Real z_step = fRaidus * 2 / z_size;

		m_pDecalMesh->beginUpdate(0);
		
		for (int i=0; i<=x_size; i++)
		{
			for (int j=0; j<=z_size; j++)
			{
				m_pDecalMesh->position(Ogre::Vector3(x1, getTerrainHeight(x1, z1) + 0.1, z1));
				m_pDecalMesh->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
				z1 += z_step;
			}
			x1 += x_step;
			z1 = z - fRaidus;
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
	 * \return 
	 */
	float	XavierDecalCursor::getTerrainHeight(float x, float z)
	{
		Ogre::Ray ray;
		ray.setOrigin(Ogre::Vector3(x, 5000, z));
		ray.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

		Vector3 vPos;
		if (m_pTerrainServer->rayIntersectsTerrain(ray, vPos))
		{
			return vPos.y;
		}

		return 0;
	}


	/**
	 *
	 * \param pCamera 
	 * \param nScreenX 
	 * \param nScreenY 
	 */
	void	XavierDecalCursor::invalid(Ogre::Camera* pCamera, float fScreenX, float fScreenY)
	{
		if (pCamera != NULL)
		{
			if (m_pTerrainServer->rayIntersectsTerrain(
				pCamera->getCameraToViewportRay(fScreenX, fScreenY), m_vPos))
			{
				setDecalCursor(m_vPos.x, m_vPos.z, m_fRadius);						
			}
		}
	}

	/**
	 *
	 * \return 
	 */
	Ogre::Vector3&	XavierDecalCursor::getPosition()
	{
		return m_vPos;
	}

	/**
	 *
	 * \param fRadius 
	 */
	void	XavierDecalCursor::setRadius(float fRadius)
	{
		m_fRadius = fRadius;
	}

	/**
	 *
	 * \return 
	 */
	float	XavierDecalCursor::getRadius() const
	{
		return m_fRadius;
	}

}

