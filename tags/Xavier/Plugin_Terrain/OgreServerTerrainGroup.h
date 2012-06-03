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
			int nTerrainSize, float fWorldSize, const Vector3& vOrigin, float fMaxPixelError, float fCompositeMapDistance, 
			const Vector3& vLightMapDirection, const ColourValue& clrCompositeMapDiffuse);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainGroupServer();

		/**
		 *
		 * \return 
		 */
		virtual TerrainGroup*	getTerrainGroup() const;
		
		/**
		 *
		 * \param vPos 
		 */
		virtual	bool			rayIntersectsTerrain(const Ray& ray, Vector3& vPos);
	protected:
		TerrainGlobalOptions*	m_pOption;
		TerrainGroup*			m_pTerrainGroup;
	};
	
	//////////////////////////////////////////////////////////////////////////
	struct STerrainGroupServerAdp : public SSAdp
	{
		int						nTerrainSize;
		float					fWorldSize;
		Vector3					vOrigin;
		float					fMaxPixelError;
		float					fCompositeMapDistance;
		Vector3					vLightMapDirection;
		ColourValue				clrCompositeMapDiffuse;
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