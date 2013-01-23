#ifndef _____OgreTerrainSystem_H
#define _____OgreTerrainSystem_H

#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"

namespace Ogre
{
	/**
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-23
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API TerrainSystem : public Singleton<TerrainSystem>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	TerrainSystem&				getSingleton();

		/**
		 *
		 * \return 
		 */
		static	TerrainSystem*				getSingletonPtr();
	public:
		/**
		 *
		 * \param name 
		 * \param fMaxPixelError 
		 * \param fCompositeMapDistance 
		 * \param clrCompositeMapDiffuse 
		 * \param nTerrainSize 
		 * \param fWorldSize 
		 * \param nMinBatchSize 
		 * \param nMaxBatchSize 
		 * \param fInputScale 
		 * \param texture 
		 * \param vOrigin 
		 * \return 
		 */
		TerrainSystem(float fMaxPixelError, 
			float fCompositeMapDistance, const ColourValue& clrCompositeMapDiffuse, int nTerrainSize, float fWorldSize, int nMinBatchSize, int nMaxBatchSize, 
			float fInputScale, const String& texture, const Vector3& vOrigin);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainSystem();

		/**
		 *
		 * \param nPageX 
		 * \param nPageY 
		 * \param bLoad 
		 */
		virtual	void						defineTerrain(int nPageX, int nPageY, bool bLoad);
		
		/**
		 *
		 * \param nPageX 
		 * \param nPageY 
		 * \return 
		 */
		virtual Terrain*					getTerrain(int nPageX, int nPageY);
		
		/**
		 *
		 * \param ray 
		 * \param vPos 
		 * \return 
		 */
		virtual Terrain*					rayIntersects(const Ray& ray, Vector3& vPos);

		/**
		 *
		 * \return 
		 */
		virtual	TerrainGroup*				getTerrainGroup() const;
	protected:
		/**
		 *
		 * \param fWorldSize 
		 * \param nTerrainSize 
		 * \param fInputScale 
		 * \param nMinBatchSize 
		 * \param nMaxBatchSize 
		 * \param defaultTexture 
		 */
		virtual	void						configureTerrainDefault(float fWorldSize, int nTerrainSize, float fInputScale, 
			int nMinBatchSize, int nMaxBatchSize, const String& defaultTexture);
	protected:
		TerrainGlobalOptions*				m_pGlobalOptions;
		TerrainGroup*						m_pTerrainGroup;
	};
}

#endif