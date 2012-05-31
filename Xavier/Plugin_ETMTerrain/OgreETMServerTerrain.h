#ifndef _____OgreETMServerTerrain_H
#define _____OgreETMServerTerrain_H

#include "OgreServerTerrain.h"
#include "ETTerrainManager.h"
#include "ETTerrainInfo.h"
#include "ETBrush.h"
#include "ETSplattingManager.h"

namespace Ogre
{
	// 摄像机服务
	class CameraServer;
	
	/**
	* \ingroup : Plugin_ETMTerrain
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-29
	*
	* \Author  : lp
	*
	* \Desc    : 地形服务
	*
	* \bug     : 
	*
	*/
	class Ogre_ETMTerrain_Export_API ETMTerrainServer : public TerrainServer
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param depServerName 
		 * \param pCameraServer 
		 * \param w 
		 * \param h 
		 * \param vMin 
		 * \param vMax 
		 * \return 
		 */
		ETMTerrainServer(const String& typeName, const String& depServerName, CameraServer* pCameraServer,
			int w, int h, const Vector3& vMin, const Vector3& vMax, int nNumTexture);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~ETMTerrainServer(void);

		/**
		 *
		 * \param box 
		 * \param w 
		 * \param h 
		 * \param heightmap 
		 */
		virtual	void					defineTerrain(const AxisAlignedBox& box, int w, int h);

		/**
		 *
		 * \param w 
		 * \param h 
		 */
		virtual	void					defintSplatting(int w, int h);

		/**
		 *
		 * \return 
		 */
		virtual	ET::TerrainManager*		getTerrainManager() const;
	protected:
		ET::TerrainManager*				m_pTerrainManager;
		ET::SplattingManager*			m_pSplatManager;
	};

	// 地形服务适配
	struct SETMTerrainServerAdp : public SSAdp
	{
		String							depCameraServerName;
		int								w;
		int								h;
		Vector3							vMin;
		Vector3							vMax;
		int								nNumTexture;
	};

	/**
	* \ingroup : Plugin_ETMTerrain
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-29
	*
	* \Author  : lp
	*
	* \Desc    : 地形服务工厂
	*
	* \bug     : 
	*
	*/
	class Ogre_ETMTerrain_Export_API ETMTerrainServerFactory : public ServerFactory
	{
	public:
		static const String		FactoryTypeName;

		/** 构造函数
		 *
		 * \return 
		 */
		ETMTerrainServerFactory();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~ETMTerrainServerFactory();

	public:
		/** 获取工厂名
		 *
		 * \return 
		 */
		virtual String			getTypeName() const;
	
		/** 创建服务
		 *
		 * \param pAdp	服务适配参数
		 * \return 
		 */
		virtual Server*			createServer(const SSAdp& ssadp);
	};
}

#endif
