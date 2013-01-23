#include "OgreSystemStdAfx.h"
#include "OgreTerrainSystem.h"
#include "OgreDecalMesh.h"

namespace Ogre
{
	static const float		MAX_DECAL_RAY_ORIGIN_Y	= 5000;
	/**
	 *
	 * \param pSceneManager 
	 * \param fRaidus 
	 * \return 
	 */
	DecalMesh::DecalMesh(SceneManager* pSceneManager, TerrainSystem* pTerrainSystem, const String& name, float fRaidus, const String& materialName)
		: m_pSceneManager(pSceneManager), m_pTerrainSystem(pTerrainSystem), m_pDecalMesh(NULL), m_fRaidus(fRaidus)
	{
		createDecalMesh(name, fRaidus, materialName);
	}

	/**
	 *
	 * \return 
	 */
	DecalMesh::~DecalMesh()
	{
		m_pSceneManager->getRootSceneNode()->detachObject(m_pDecalMesh);
		delete m_pDecalMesh;
	}

	/**
	 *
	 * \param fRaidus 
	 */
	void	DecalMesh::createDecalMesh(const String& name, float fRaidus, const String& materialName)
	{
		m_pDecalMesh = new Ogre::ManualObject(name);
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
	void	DecalMesh::setPosition(const Vector3& vPos)
	{
		Ogre::Real x1 = vPos.x - m_fRaidus;
		Ogre::Real z1 = vPos.z - m_fRaidus;

		int x_size = 12;
		int z_size = 12;

		Ogre::Real x_step = m_fRaidus * 2 / x_size;
		Ogre::Real z_step = m_fRaidus * 2 / z_size;

		m_pDecalMesh->beginUpdate(0);

		for (int i=0; i<=x_size; i++)
		{
			for (int j=0; j<=z_size; j++)
			{
				m_pDecalMesh->position(Ogre::Vector3(x1, getTerrainHeight(vPos) + 0.1, z1));
				m_pDecalMesh->textureCoord((float)i / (float)x_size, (float)j / (float)z_size);
				z1 += z_step;
			}
			x1 += x_step;
			z1 = vPos.z - m_fRaidus;
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
	 * \return 
	 */
	Vector3	DecalMesh::getPosition()
	{
		return m_vPos;
	}

	/**
	 *
	 * \param fRaidus 
	 */
	void	DecalMesh::setRaidus(float fRaidus)
	{
		m_fRaidus = fRaidus;
	}

	/**
	 *
	 * \return 
	 */
	float	DecalMesh::getRaidus() const
	{
		return m_fRaidus;
	}

	/**
	 *
	 * \param x 
	 * \param z 
	 * \return 
	 */
	float	DecalMesh::getTerrainHeight(const Vector3& vPos)
	{
		if (m_pTerrainSystem != NULL)
		{
			Ray ray;
			ray.setOrigin(
				Vector3(vPos.x, MAX_DECAL_RAY_ORIGIN_Y, vPos.y)
				);
			ray.setDirection(Vector3::NEGATIVE_UNIT_Y);

			if (m_pTerrainSystem->rayIntersects(ray, m_vPos))
			{
				return m_vPos.y;
			}
		}

		return 0;
	}
}