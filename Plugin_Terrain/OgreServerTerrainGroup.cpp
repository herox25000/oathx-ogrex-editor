#include "OgreTerrainPluginPrerequisites.h"
#include "OgreServerTerrainGroup.h"
#include "OgreServerWorldSpace.h"

namespace Ogre
{

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	TerrainGroupServer::TerrainGroupServer(const String& typeName, const String& depWorldServerName, int nTerrainSize, float fWorldSize, 
		const Vector3& vOrigin, float fMaxPixelError, float fCompositeMapDistance, const Vector3& vLightMapDirection, const ColourValue& clrCompositeMapDiffuse)
		: Server(typeName), m_pTerrainGroup(0),m_pOption(0)
	{
		// 构造地形组
		WorldSpaceServer* pWorldServer = static_cast<WorldSpaceServer*>(
			System::getSingletonPtr()->getServer(depWorldServerName)
			);
		if (pWorldServer)
		{
			// 取得场景管理器
			SceneManager* pSceneManager = pWorldServer->getSceneManager();
			
			// 创建地形配置
			m_pOption = new TerrainGlobalOptions();
			if (m_pOption)
			{
				m_pOption->setMaxPixelError(
					fMaxPixelError
					);
		
				ColourValue clrAmbient = pSceneManager->getAmbientLight();
				m_pOption->setCompositeMapAmbient(clrAmbient);
				
				// 设置灯光方向
				m_pOption->setLightMapDirection(
					vLightMapDirection
					);

				m_pOption->setCompositeMapDistance(fCompositeMapDistance);
				m_pOption->setCompositeMapDiffuse(clrCompositeMapDiffuse);
			}
			
			// 创建地形组
			m_pTerrainGroup = new TerrainGroup(
				pWorldServer->getSceneManager(), Terrain::ALIGN_X_Z, nTerrainSize, fWorldSize
				);
			if (m_pTerrainGroup)
			{
				m_pTerrainGroup->setOrigin(vOrigin);
			}
		}

	}

	/**
	 *
	 * \return 
	 */
	TerrainGroupServer::~TerrainGroupServer()
	{
		SAFE_DELETE(m_pTerrainGroup);
		SAFE_DELETE(m_pOption);
	}

	/**
	 *
	 * \return 
	 */
	TerrainGroup*	TerrainGroupServer::getTerrainGroup() const
	{
		return m_pTerrainGroup;
	}

	/**
	 *
	 * \param ray 
	 * \param vPos 
	 * \return 
	 */
	bool			TerrainGroupServer::rayIntersectsTerrain(const Ray& ray, Vector3& vPos)
	{
		TerrainGroup::RayResult result = m_pTerrainGroup->rayIntersects(ray);

		if (result.hit)
		{
			vPos = result.position;
			return true;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	const String	TerrainGroupServerFactory::FactoryTypeName = "Terrain/TerrainGroupServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	TerrainGroupServerFactory::TerrainGroupServerFactory()
	{
		
	}

	/**
	 *
	 * \return 
	 */
	String		TerrainGroupServerFactory::getTypeName() const
	{
		return TerrainGroupServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*		TerrainGroupServerFactory::createServer(const SSAdp& ssadp)
	{
		// 获取参数
		const STerrainGroupServerAdp& adp = static_cast<const STerrainGroupServerAdp&>(ssadp);
		
		if (!adp.depServerName.empty())
		{
			// 创建地形组服务
			return new TerrainGroupServer(adp.typeName, adp.depServerName, 
				adp.nTerrainSize, adp.fWorldSize, adp.vOrigin, adp.fMaxPixelError, adp.fCompositeMapDistance,
				adp.vLightMapDirection, adp.clrCompositeMapDiffuse);
		}
		
		return NULL;
	}
}