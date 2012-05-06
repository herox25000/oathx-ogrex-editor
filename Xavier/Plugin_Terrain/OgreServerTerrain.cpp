#include "OgreSystemPrerequisites.h"
#include "OgreServerTerrain.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	TerrainServer::TerrainServer(const String& typeName) : Server(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	TerrainServer::~TerrainServer()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	const String	TerrainServerFactory::FactoryTypeName = "System/TerrainServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	TerrainServerFactory::TerrainServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String	TerrainServerFactory::getTypeName() const
	{
		return TerrainServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*	TerrainServerFactory::createServer(const SSAdp& ssadp)
	{
		const STerrainServerAdp& adp = static_cast<const STerrainServerAdp&>(ssadp);

		return new TerrainServer(adp.typeName);
	}
}