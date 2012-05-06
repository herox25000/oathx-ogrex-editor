#ifndef _____OgreSystem_H
#define _____OgreSystem_H

#include "OgreServer.h"

namespace Ogre
{
	typedef std::vector<Server*>	VServer;
	typedef HashMap<String, ServerFactory*>	HashServerFactory;
	typedef std::vector<Plugin*>	VPlugin;
	typedef std::vector<DynLib*>	VDynlib;

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-06
	*
	* \Author  : lp
	*
	* \Desc    : 系统核心
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API System 
		: public Singleton<System>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	System&			getSingleton();

		/**
		 *
		 * \return 
		 */
		static	System*			getSingletonPtr();

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
		virtual ~System();

		/** 创建系统
		 *
		 * \param pluginFileName	系统插件配置文件
		 * \param resourceFileName	系统资源配置文件
		 * \return 
		 */
		virtual bool				create(const String& pluginFileName, const String& resourceFileName, bool bAutoCreateWindow);
		
		/**
		 *
		 */
		virtual void				update();

		/** 销毁系统
		 *
		 */
		virtual void				destroy();
	
	public:
		/**
		 *
		 * \param pFactory 
		 */
		virtual void				registerServerFactory(ServerFactory* pFactory);

		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual ServerFactory*		getServerFactory(const String& typeName);

		/**
		 *
		 * \param pFactory 
		 */
		virtual void				unregisterServerFactory(ServerFactory* pFactory);

		/**
		 *
		 */
		virtual void				clearServerFactory();

	public:
		/** 添加子服务
		 *
		 * \param pServer 服务对象,将自动设置父服务
		 * \return 
		 */
		virtual bool				addServer(Server* pServer);

		/** 获取子服务
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual Server*				getServer(const String& typeName);

		/** 删除服务
		 *
		 * \param pServer 
		 */
		virtual void				delServer(Server* pServer);

		/** 清空所有服务，反向删除
		 *
		 */
		virtual void				clearServer();

		/**
		 *
		 * \return 
		 */
		virtual int					getServerCount() const;

	public:
		/** 创建渲染窗口
		 *
		 * \param hWnd 
		 * \param w 
		 * \param h 
		 * \param bFullScree 
		 */
		virtual void				createApplicationWindow(const String& name, HWND hWnd, int w, int h, bool bFullScreen);
		
		/** 获取渲染窗口
		 *
		 * \return 
		 */
		virtual RenderWindow*		getApplicationWindow() const;

		/** 加载插件
		 *
		 * \param name 
		 */
		virtual	void				loadPlugin(const String& name);

		/** 卸载插件
		 *
		 * \param name 
		 */
		virtual void				unloadPlugin(const String& name);

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
		virtual void				clearPlugin();
	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pRenderWindow;
		HashServerFactory			m_hashFactory;
		VServer						m_vServer;
		VPlugin						m_vPlugin;
		VDynlib						m_vDynlib;
	};
}

#endif