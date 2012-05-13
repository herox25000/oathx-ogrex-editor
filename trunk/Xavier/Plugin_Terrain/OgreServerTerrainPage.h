#ifndef _____OgreServerTerrainPage_H
#define _____OgreServerTerrainPage_H

#include "OgreServer.h"

namespace Ogre
{
	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-17
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainPageServer : public Server
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		TerrainPageServer(const String& typeName, const String& depGroupName,
			const Vector3& vPos, int nPageX, int nPageY, int nMinBatchSize, int nMaxBatchSize);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainPageServer();
		
		/**
		 *
		 * \param flipX 
		 * \param flipY 
		 * \param image 
		 */
		virtual void			getTerrainImage(const String& name, bool flipX, bool flipY, Image& image);
	
		/**
		 *
		 * \param name 
		 * \param x 
		 * \param y 
		 * \param flat 
		 */
		virtual void			defineTerrain(const String& name, long x, long y, bool flat);
	protected:
		Terrain*				m_pTerrain;
		String					m_depGroupName;
	};

	// 地形服务参数
	struct STerrainPageServerAdp : public SSAdp
	{
		Vector3					vPos;
		int						nPageX;
		int						nPageY;
		int						nMinBatchSize;
		int						nMaxBatchSzie;
	};

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-17
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainPageServerFactory : public ServerFactory
	{
	public:
		static const String		FactoryTypeName;

		/**
		 *
		 * \return 
		 */
		TerrainPageServerFactory();

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