#include "OgreETMTerrainPluginPrerequisites.h"
#include "OgreETMServerTerrain.h"
#include "OgreServerCamera.h"
#include "OgreSystem.h"

namespace Ogre
{
	static const String		SPLATTING_BASE_NAME			=	"ETSplatting";
	static const String		SPLATTING_GROUP_NAME		=	"ET";
	static const String		SPLATTING_LIGHT_TEXTURE		=	"ETLightmap";
	static const String		SPLATTING_MATERIAL			=	"ETTerrainMaterial";

	static const int		SPLATTING_DEFAULT_WIDTH		=	128;
	static const int		SPLATTING_DEFAULT_HEIGHT	=	128;

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	ETMTerrainServer::ETMTerrainServer(const String& typeName, const String& depServerName,  CameraServer* pCameraServer,
		int w, int h, const Vector3& vMin, const Vector3& vMax, int nNumTexture)
		: TerrainServer(typeName), m_pTerrainManager(0), m_pSplatManager(0)
	{
		WorldSpaceServer* pWorldServer = static_cast<WorldSpaceServer*>(
			System::getSingletonPtr()->getServer(depServerName)
			);
		if (pWorldServer)
		{
			/*
			* ����ETM���ι�����
			*/
			m_pTerrainManager = new ET::TerrainManager(pWorldServer->getSceneManager());
			
			// ��ȡ�����
			Camera* pCamera	= pCameraServer->getCamera();
			if (pCamera)
			{
				m_pTerrainManager->setLODErrorMargin(2,
					pCamera->getViewport()->getActualHeight()
					);
				
				// ����LOAD
				m_pTerrainManager->setUseLODMorphing(true);

				/*
				* �������ù�����
				*/
				m_pSplatManager = new ET::SplattingManager(SPLATTING_BASE_NAME, SPLATTING_GROUP_NAME,
					SPLATTING_DEFAULT_WIDTH, SPLATTING_DEFAULT_HEIGHT);

				// ������Ҫ�������������
				m_pSplatManager->setNumTextures(nNumTexture);
				
				// ���岢���ص���
				defineTerrain(AxisAlignedBox(vMin, vMax), w, h);
				// �������ù���
				defintSplatting(SPLATTING_DEFAULT_WIDTH, SPLATTING_DEFAULT_WIDTH);
			}
		}
	}

	/**
	 *
	 * \return 
	 */
	ETMTerrainServer::~ETMTerrainServer()
	{
		if (m_pSplatManager != NULL)
		{
			delete m_pSplatManager;
			m_pSplatManager = 0;
		}

		if (m_pTerrainManager != NULL)
		{
			delete m_pTerrainManager;
			m_pTerrainManager = 0;
		}
	}

	/**
	 *
	 * \param w 
	 * \param h 
	 * \param heightmap 
	 * \param axis 
	 */
	void		ETMTerrainServer::defineTerrain(const AxisAlignedBox& box, int w, int h)
	{
		// ���������Ϣ
		ET::TerrainInfo tr(w, h, std::vector<float>(w*h,0));
		tr.setExtents(box);
		
		// ��������
		m_pTerrainManager->createTerrain(tr);
	}

	/**
	 *
	 * \param nNumTexture 
	 * \param w 
	 * \param h 
	 */
	void				ETMTerrainServer::defintSplatting(int w, int h)
	{
		// ������������
		TexturePtr texture = TextureManager::getSingleton().createManual(SPLATTING_LIGHT_TEXTURE,
			SPLATTING_GROUP_NAME, TEX_TYPE_2D, w, h, 1, PF_BYTE_RGB);

		Image image;
		ET::createTerrainLightmap(m_pTerrainManager->getTerrainInfo(), image, w, h,
			Vector3(1, -1, 1), ColourValue::White, ColourValue(0.3, 0.3, 0.3));

		texture->getBuffer(0, 0)->blitFromMemory(image.getPixelBox(0, 0));

		m_pTerrainManager->setMaterial(
			MaterialManager::getSingleton().getByName(SPLATTING_MATERIAL)
			);		
	}

	/**
	 *
	 * \return 
	 */
	ET::TerrainManager*	ETMTerrainServer::getTerrainManager() const
	{
		return m_pTerrainManager;
	}

	//////////////////////////////////////////////////////////////////////////
	const String ETMTerrainServerFactory::FactoryTypeName	=	"Plugin/ETMTerrainServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	ETMTerrainServerFactory::ETMTerrainServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	ETMTerrainServerFactory::~ETMTerrainServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String		ETMTerrainServerFactory::getTypeName() const
	{
		return ETMTerrainServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*		ETMTerrainServerFactory::createServer(const SSAdp& ssadp)
	{
		const SETMTerrainServerAdp& adp = static_cast<const SETMTerrainServerAdp&>(ssadp);

		CameraServer* pCameraServer = static_cast<CameraServer*>(
			System::getSingleton().getServer(adp.depCameraServerName)
			);
		if (pCameraServer != NULL)
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("create server " + adp.typeName);
#endif
			
			return new ETMTerrainServer(adp.typeName, adp.depServerName,
				pCameraServer, adp.w, adp.h, adp.vMin, adp.vMax, adp.nNumTexture);
		}

		return NULL;
	}
}
