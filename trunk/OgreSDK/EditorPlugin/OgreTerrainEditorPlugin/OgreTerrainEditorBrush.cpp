#include "OgreTerrainEditorPluginStdAfx.h"
#include "OgreTerrainEditorBrush.h"

namespace Ogre
{
//////////////////////////////////////////////////////////////////////////
		/**
	 *
	 * \param pSceneManager 
	 * \param materialName 
	 * \param fRaidus 
	 * \return 
	 */
	Brush::Brush(SceneManager* pSceneManager, const String& materialName, float fRaidus, float fIntensity, const String& texture)
		: m_pSceneManager(pSceneManager), m_pBrushMesh(NULL), m_pBrushNode(NULL), m_fRaidus(fRaidus), m_fIntensity(fIntensity), m_pBrushData(NULL)
	{
		m_pBrushData	= new float[BRUSH_DATA_SIZE * BRUSH_DATA_SIZE];
		m_pBrushTexture = TextureManager::getSingletonPtr()->createManual("TerrainEditorBrush", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
			TEX_TYPE_2D, 256, 256, 1, 1, PF_A8R8G8B8, TU_DYNAMIC_WRITE_ONLY);
		
		setBrushTexture(texture);

		m_pBrushMesh = new ManualObject("TerrainEditorBrush");
		m_pSceneManager->getRootSceneNode()->attachObject(m_pBrushMesh);

		int x_size = 8;
		int z_size = 8;

		m_pBrushMesh->begin(materialName, RenderOperation::OT_TRIANGLE_LIST);
		for (int i = 0; i <= x_size; i++)
		{
			for (int j = 0; j <= z_size; j++)
			{
				m_pBrushMesh->position(Ogre::Vector3((float)i, 0, (float)j));
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
	Brush::~Brush()
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
	void			Brush::setBrushTexture(const String& texture)
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
	void		Brush::setPosition(Terrain* pTerrain, const Vector3& vPos)
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
	Vector3			Brush::getPosition() const
	{
		return m_vBrushPos;
	}

	/**
	 *
	 * \param fRadius 
	 */
	void			Brush::setRadius(float fRadius)
	{
		m_fRaidus = fRadius;
	}

	/**
	 *
	 * \return 
	 */
	float			Brush::getRadius() const
	{
		return m_fRaidus;
	}

	/**
	 *
	 * \param fBrushIntensity 
	 */
	void			Brush::setIntensity(float fIntensity)
	{
		m_fIntensity = fIntensity;
	}

	/**
	 *
	 * \return 
	 */
	float			Brush::getIntensity() const
	{
		return m_fIntensity;
	}

	/**
	 *
	 * \return 
	 */
	float*			Brush::getBrushData() const
	{
		return m_pBrushData;
	}
}