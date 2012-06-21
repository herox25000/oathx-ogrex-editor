#ifndef _____Server_H
#define _____Server_H

namespace Barcelona
{
	// 服务适配参数
	typedef struct SSAdp{
		Ogre::String	defPopertyFile;		// 属性定义文件
		Ogre::String	typeName;			// 服务名称
		Ogre::String	depServerName;		// 依赖服务名称
	}*SSAdpPtr;

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
	* \Desc    : 基本服务，所有游戏单位的基础类
	*
	* \bug     : 
	*
	*/
	class GuardiolaDLL_Export_API Server : public Ogre::PropertySet
	{		
	public:
		/** 构造函数
		 *
		 * \param typeName	服务类型名称
		 * \return 
		 */
		Server(const Ogre::String& typeName, const SSAdp& ssadp);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~Server(void);

		/** 获取服务类型名
		 *
		 * \return 
		 */
		virtual Ogre::String		getTypeName() const;

		/** 设置服务类型名
		 *
		 * \param typeName 
		 */
		virtual	void				setTypeName(const Ogre::String& typeName);
		
		/** 加载服务属性定义文件
		 *
		 * \param path 
		 */
		virtual	void				loadProperty(const Ogre::String& path);

		/** 卸载所有属性
		 *
		 */
		virtual	void				unloadProperty();
	protected:
		Ogre::String				m_typeName;
	};

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
	* \Desc    : 服务工长
	*
	* \bug     : 
	*
	*/
	class GuardiolaDLL_Export_API ServerFactory
	{
	public:
		// 服务工厂类型名
		static const Ogre::String	FactoryTypeName;

		/** 构造函数
		 *
		 * \return 
		 */
		ServerFactory();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~ServerFactory();

		/** 获取服务类型名
		 *
		 * \return 
		 */
		virtual Ogre::String		getTypeName() const;

		/** 创建一个服务
		 *
		 * \param ssadp			服务适配参数
		 * \return 
		 */
		virtual Server*				createServer(const SSAdp& ssadp);
	};
}

#endif
