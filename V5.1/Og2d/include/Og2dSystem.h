#ifndef _____Og2dSystem_H
#define _____Og2dSystem_H

#include "Og2dWorld.h"

namespace Og2d
{	
	typedef vector<DynLib*>::type	VectorDynlib;
	typedef map<String, RenderSystem*>::type MapRenderSystem;
	typedef vector<Plugin*>::type	VectorPlugin;
	typedef map<String, SceneFactory*>::type MapSceneFactory;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : Og2d系统类
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API System : public Singleton<System>
	{
	public:
		/** 实现获取单件引用
		 *
		 * \return 
		 */
		static	System&				getSingleton();

		/** 使用获取单件指针
		 *
		 * \return 
		 */
		static	System*				getSingletonPtr();

	public:
		/** 构造函数
		 *
		 * \return 
		 */
		System();

		/** 析构函数
		 *
		 * \return 
		 */
		~System();
		
	public:
		/** 系统启动
		 *
		 * \param szPlginFile		配置文件名
		 * \param szLogFile			LOG文件名
		 * \param Value 
		 * \return 
		 */
		virtual	bool				startup(const String& szPlginFile, const String& szLogFile,
			const StringValue& Value);
		
		/** 系统运行
		 *
		 */
		virtual	bool				run(float fElapsed);

		/** 关闭系统
		 *
		 */
		virtual	void				shutdown();

	public:
		/** 添加渲染系统
		 *
		 * \param pRenderSystem
		 */
		virtual	void				addRenderSystem(RenderSystem* pRenderSystem);

		/** 移除渲染系统
		 *
		 * \param pRenderSystem 
		 */
		virtual	void				removeRenderSystem(
			RenderSystem* pRenderSystem
			);

		/** 获取渲染系统
		 *
		 * \param name 
		 * \return 
		 */
		virtual	RenderSystem*		getRenderSystem(const String& name);

		/** 设置渲染系统
		 *
		 * \param pRenderSystem 
		 */
		virtual	void				setRenderSystem(
			RenderSystem* pRenderSystem
			);

		/** 获取当前渲染系统
		 *
		 * \return 
		 */
		virtual	RenderSystem*		getRenderSystem() const;
	
	public:
		/** 添加场景工厂
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual	void				addSceneFactory(SceneFactory* pFactory);

		/** 获取场景工厂
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	SceneFactory*		getSceneFactory(const String& szName);

		/** 移除场景工厂
		 *
		 * \param pFactory 
		 */
		virtual void				removeFactory(SceneFactory* pFactory);
		
		/** 清空所有场景工厂
		 *
		 */
		virtual	void				clearSceneFactory();

		/** 创建世界
		 *
		 * \param szName 
		 * \param vOrigin 世界原点
		 * \return 
		 */
		virtual	World*				createWorld(const String& szName, const Vector2D& vPos, WorldMask mask);
		
		/**
		 *
		 */
		virtual	void				destroyWorld();
	public:
		/** 加载插件
		 *
		 * \param name 
		 */
		virtual	void				loadPlugin(const String& name);

		/** 卸载插件
		 *
		 * \param name 
		 */
		virtual	void				unloadPlugin(const String& name);

		/** 安装插件
		 *
		 * \param pPlugin 
		 */
		virtual void				installPlugin(Plugin* pPlugin);

		/** 卸载插件
		 *
		 * \param pPlugin 
		 */
		virtual void				uninstallPlugin(Plugin* pPlugin);

		/** 清空插件
		 *
		 */
		virtual	void				clearPlugin();
	protected:
		MapRenderSystem				m_vRenderSystem;
		RenderSystem*				m_pRenderSystem;
		VectorDynlib				m_vDynlib;
		VectorPlugin				m_vPlugin;
		MapSceneFactory				m_vSceneFactory;
		World*						m_pWorld;
	};
}

#endif