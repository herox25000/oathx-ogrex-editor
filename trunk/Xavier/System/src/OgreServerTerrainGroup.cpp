#include "OgreSystemPrerequisites.h"
#include "OgreServerTerrainGroup.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	TerrainGroupServer::TerrainGroupServer(const String& typeName, WorldSpaceServer* pWorldSpace) 
		: Server(typeName), m_pGlobalOption(NULL), m_pTerrainGroup(NULL)
	{
	
	}

	/**
	 *
	 * \return 
	 */
	TerrainGroupServer::~TerrainGroupServer()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	const String	TerrainGroupServerFactory::FactoryTypeName = "System/TerrainGroupServerFactory";
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
		return NULL;
	}
}