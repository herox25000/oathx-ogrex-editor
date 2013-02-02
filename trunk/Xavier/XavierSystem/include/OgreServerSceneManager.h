#ifndef _____OgreServerSceneManager_H
#define _____OgreServerSceneManager_H

namespace Ogre
{
	/**
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-31
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API ServerSceneManager : public Server
	{
	public:
		/**
		 *
		 * \param name 
		 * \param typeMask 
		 * \param clrAmbientLight 
		 * \param fogMode 
		 * \param clrFog 
		 * \param fExpDensity 
		 * \param fLinearStart 
		 * \param fLinearEnd 
		 * \return 
		 */
		ServerSceneManager(const String& name, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
			FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd);

		/**
		 *
		 * \return 
		 */
		virtual ~ServerSceneManager();

		/**
		 *
		 * \return 
		 */
		virtual	SceneManager*		getSceneManager() const;

	protected:
		/**
		 *
		 * \param pluginName 
		 * \param typeMask 
		 * \param fogMode 
		 * \param clrFog 
		 * \param expDensity 
		 * \param linearStart 
		 * \param linearEnd 
		 */
		virtual	bool				configure(const String& pluginName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
			FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd);
	protected:
		SceneManager*				m_pSceneManager;
	};

	// 场景服务适配参数
	struct SServerSceneManagerAdp : public SServerAdp
	{
		SceneTypeMask				typeMask;
		ColourValue					clrAmbientLight;
		FogMode						fogMode; 
		ColourValue					clrFog; 
		float						expDensity; 
		float						linearStart; 
		float						linearEnd;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : 场景插件工厂
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class ServerSceneManagerFactory : public ServerFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		ServerSceneManagerFactory(const String& typeName);

		/**
		 *
		 * \return 
		 */
		virtual ~ServerSceneManagerFactory();

		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	Server*			createServer(const SServerAdp& ssadp, Server* pParent);
	};
}

#endif