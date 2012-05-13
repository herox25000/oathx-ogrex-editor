#include "OgreTerrainPluginPrerequisites.h"
#include "OgreServerTerrainPage.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	TerrainPageServer::TerrainPageServer(const String& typeName) : Server(typeName)
	{

	}

	/**
	 *
	 * \return 
	 */
	TerrainPageServer::~TerrainPageServer()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	const String	TerrainPageServerFactory::FactoryTypeName = "System/TerrainServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	TerrainPageServerFactory::TerrainPageServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String	TerrainPageServerFactory::getTypeName() const
	{
		return TerrainPageServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*	TerrainPageServerFactory::createServer(const SSAdp& ssadp)
	{
		const STerrainPageServerAdp& adp = static_cast<const STerrainPageServerAdp&>(ssadp);

		return new TerrainPageServer(adp.typeName);
	}
}