#ifndef _____OgreServerTerrainPage_H
#define _____OgreServerTerrainPage_H

#include "OgreServer.h"

namespace Ogre
{
	class TerrainGroupServer;

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
		 * \param pGroupServer 
		 * \param nPageX 
		 * \param nPageY 
		 * \param nMinBatchSize 
		 * \param nMaxBatchSize 
		 * \param diffuseTexture 
		 * \param normalheightTexture 
		 * \return 
		 */
		TerrainPageServer(const String& typeName, TerrainGroupServer* pGroupServer,
			int nPageX, int nPageY, int nMinBatchSize, int nMaxBatchSize, const String& diffuseTexture, const String& normalheightTexture, 
			float fLayerWorldSize);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainPageServer();

	protected:
		/**
		 *
		 * \param pGroup 
		 * \param nMinBatchSize 
		 * \param nMaxBatchSize 
		 * \param diffuseTexture 
		 * \param normalheightTexture 
		 * \param fLayerWorldSize 
		 * \return 
		 */
		Terrain::ImportData		configureTerrainPage(TerrainGroup* pGroup, int nMinBatchSize, int nMaxBatchSize, 
			const String& diffuseTexture, const String& normalheightTexture, float fLayerWorldSize);
	protected:
		TerrainGroupServer*		m_pGroupServer;
		Terrain*				m_pTerrain;
		int						m_nPageX;
		int						m_nPageY;
	};

	// 地形服务参数
	struct STerrainPageServerAdp : public SSAdp
	{
		int						nPageX;
		int						nPageY;
		int						nMinBatchSize;
		int						nMaxBatchSzie;
		String					normalheightTexture;
		String					diffuseTexture;
		float					fLayerWorldSize;
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