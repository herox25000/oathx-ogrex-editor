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
	TerrainGroupServer::TerrainGroupServer(const String& typeName, const String& depWorldServerName,
		int nTerrainSize, float fWorldSize, const Vector3& vOrigin)
		: Server(typeName), m_pTerrainGroup(NULL)
	{
		addProperty(PY_NAME_TERRAINSIZE,	Any(nTerrainSize),	PY_NAME_TERRAINSIZE_DESC,	PROPERTY_INT);
		addProperty(PY_NAME_WORLDSIZE,		Any(fWorldSize),	PY_NAME_WORLDSIZE_DESC,		PROPERTY_REAL);
		addProperty(PY_NAME_ORIGIN,			Any(vOrigin),		PY_NAME_OGIGIN_DESC,		PROPERTY_VECTOR3);

		// 构造地形组
		WorldSpaceServer* pWorldServer = static_cast<WorldSpaceServer*>(
			System::getSingletonPtr()->getServer(depWorldServerName)
			);
		m_pTerrainGroup = new TerrainGroup(
			pWorldServer->getSceneManager(), Terrain::ALIGN_X_Z, nTerrainSize, fWorldSize
			);
		if (m_pTerrainGroup)
		{
			m_pTerrainGroup->setFilenameConvention("test","terrain");
			m_pTerrainGroup->setOrigin(vOrigin);
		}
	}

	/**
	 *
	 * \return 
	 */
	TerrainGroupServer::~TerrainGroupServer()
	{
		if (m_pTerrainGroup)
			delete m_pTerrainGroup;

		m_pTerrainGroup = NULL;
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
	 */
	bool			TerrainGroupServer::load()
	{
		return 0;
	}

	/**
	 *
	 */
	void			TerrainGroupServer::unload()
	{

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
		
		// 创建地形组服务
		return new TerrainGroupServer(adp.typeName, adp.depServerName, 
			adp.nTerrainSize, adp.fWorldSize, adp.vOrigin);
	}
}