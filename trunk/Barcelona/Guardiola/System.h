#ifndef _____System_H
#define _____System_H

namespace Barcelona
{
	typedef std::vector<Server*>					VServer;
	typedef HashMap<Ogre::String, ServerFactory*>	HashServerFactory;
	typedef Ogre::MapIterator<HashServerFactory>	ServerFactoryIter;

	/**
	* \ingroup : Guardiola
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-06-22
	*
	* \Author  : lp
	*
	* \Desc    : 系统对象，负责初始化配置以及管理运行的服务与插件
	*			 单实例类，必须在应用程序初始化时首先创建
	*
	* \bug     : 
	*
	*/
	class GuardiolaDLL_Export_API System : public Singleton<System>
	{
	public:
		/** 获取单实例对象引用
		 *
		 * \return 
		 */
		static	System&			getSingleton();

		/** 获取单实例对象指针
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

		/** 构造函数
		 *
		 * \param pluginFileName		系统插件配置文件
		 * \param resourceFileName		系统资源配置文件
		 * \param bAutoCreateWindow		是否自动创建窗口
		 * \return 
		 */
		System(const Ogre::String& pluginFileName, const Ogre::String& resourceFileName,
			bool bAutoCreateWindow);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~System(void);

		/** 创建系统
		 *
		 * \param pluginFileName		系统插件配置文件
		 * \param resourceFileName		系统资源配置文件 
		 * \param bAutoCreateWindow		是否自动创建窗口
		 * \return 
		 */
		virtual bool				create(const Ogre::String& pluginFileName, const Ogre::String& resourceFileName,
			bool bAutoCreateWindow);
		

		/** 创建应用程序
		 *
		 * \param name					应用程序名称
		 * \param hWnd					医用程序窗口句柄
		 * \param w						窗口像素宽度
		 * \param h						窗口像素高度
		 * \param bFullScreen			是否全屏
		 * \return 
		 */
		virtual void				createApplication(const Ogre::String& name, HWND hWnd, 
			int w, int h, bool bFullScreen);

		/** 更新系统
		 *
		 */
		virtual void				update();

		/** 销毁系统
		 *
		 */
		virtual void				destroy();

		/**	注册服务工厂
		 *
		 * \param pFactory	工厂对象
		 */
		virtual void				registerServerFactory(ServerFactory* pFactory);

		/** 获取服务工厂
		 *
		 * \param typeName	工厂名称
		 * \return 
		 */
		virtual ServerFactory*		getServerFactory(const Ogre::String& typeName);

		/** 注销服务工厂
		 *
		 * \param pFactory	工厂对象
		 */
		virtual void				unregisterServerFactory(ServerFactory* pFactory);

		/** 注销服务工厂
		 *
		 * \param typeName	工厂名称
		 */
		virtual void				unregisterServerFactory(const Ogre::String& typeName);

		/** 获取服务工厂迭代器
		 *
		 * \return 
		 */
		virtual ServerFactoryIter	getHashServerFactory();

		/** 清空服务工厂
		 *
		 */
		virtual void				clearServerFactory();

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
		virtual Server*				getServer(const Ogre::String& typeName);

		/**
		 *
		 * \param idx 
		 * \return 
		 */
		virtual Server*				getServer(int idx);

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
	protected:
		Ogre::Root*					m_pRoot;
		Ogre::RenderWindow*			m_pRenderWindow;
		HashServerFactory			m_hashFactory;
		VServer						m_vServer;
	};
}

#endif
