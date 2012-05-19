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
		addProperty(PV_TERRAINSIZE, Any(nTerrainSize),PVT_INT);
		addProperty(PV_WORLDSIZE, Any(fWorldSize), PVT_REAL);
		addProperty(PV_ORIGIN, Any(vOrigin), PVT_VECTOR3);

		// ���������
		WorldSpaceServer* pWorldServer = static_cast<WorldSpaceServer*>(
			System::getSingletonPtr()->getServer(depWorldServerName)
			);
		m_pTerrainGroup = new TerrainGroup(
			pWorldServer->getSceneManager(), Terrain::ALIGN_X_Z, nTerrainSize, fWorldSize
			);
		if (m_pTerrainGroup)
		{
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
	 * \return 
	 */
	bool			TerrainGroupServer::isDerivedDataUpdateInProgress() const
	{
		return m_pTerrainGroup->isDerivedDataUpdateInProgress();
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
		// ��ȡ����
		const STerrainGroupServerAdp& adp = static_cast<const STerrainGroupServerAdp&>(ssadp);
		
		// �������������
		return new TerrainGroupServer(adp.typeName, adp.depServerName, 
			adp.nTerrainSize, adp.fWorldSize, adp.vOrigin);
	}
}