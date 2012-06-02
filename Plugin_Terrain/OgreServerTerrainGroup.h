#ifndef _____OgreServerTerrainGroup_H
#define _____OgreServerTerrainGroup_H

#include "OgreServer.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"

namespace Ogre
{
	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-05
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainGroupServer : public Server
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param depWorldServerName 
		 * \param nTerrainSize 
		 * \param fWorldSize 
		 * \param vOrigin 
		 * \return 
		 */
		TerrainGroupServer(const String& typeName, const String& depWorldServerName,
			int nTerrainSize, float fWorldSize, const Vector3& vOrigin);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainGroupServer();

	protected:
		TerrainGroup*			m_pTerrainGroup;
		TerrainGlobalOptions*	m_pOptions;
	};
	
	//////////////////////////////////////////////////////////////////////////
	struct STerrainGroupServerAdp : public SSAdp
	{
		int						nTerrainSize;
		float					fWorldSize;
		Vector3					vOrigin;
	};

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-05
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainGroupServerFactory : public ServerFactory
	{
	public:
		static const String		FactoryTypeName;

	public:
		/**
		 *
		 * \return 
		 */
		TerrainGroupServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual String			getTypeName() const;

		/**
		 *
		 * \param ssadp 
		 * \return 
		 */
		virtual Server*			createServer(const SSAdp& ssadp);

	};
}

#endif