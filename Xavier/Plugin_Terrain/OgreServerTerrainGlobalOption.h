#ifndef _____OgreServerTerrainGlobalOption_H
#define _____OgreServerTerrainGlobalOption_H

#include "OgreServer.h"

namespace Ogre
{
	/**
	* \ingroup : Plugin_Terrain
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-13
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainGlobalOptionServer : public Server
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param fMaxPixelError 
		 * \param CompositeMapDistance 
		 * \param vLightMapDirection 
		 * \param clrAmbientLight 
		 * \param clrCompositeMapDiffuse 
		 * \return 
		 */
		TerrainGlobalOptionServer(const String& typeName, float fMaxPixelError, float CompositeMapDistance, 
			const Vector3& vLightMapDirection, const ColourValue& clrCompositeMapDiffuse);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainGlobalOptionServer();

		/**
		 *
		 */
		virtual	bool					load();

		/**
		 *
		 */
		virtual	void					unload();

	protected:
		/**
		 *
		 */
		virtual void					configureTerrainDefault();

	protected:
		TerrainGlobalOptions*			m_pGlobalOption;
	};

	// 地形全局配置参数
	struct STerrainGlobalOptionServerAdp : public SSAdp
	{
		float							fMaxPixelError;
		float							fCompositeMapDistance;
		Vector3							vLightMapDirection;
		ColourValue						clrCompositeMapDiffuse;
	};

	/**
	* \ingroup : Plugin_Terrain
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-13
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainGlobalOptionServerFactory : public ServerFactory
	{
	public:
		static const String		FactoryTypeName;

	public:
		/**
		 *
		 * \return 
		 */
		TerrainGlobalOptionServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainGlobalOptionServerFactory();

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