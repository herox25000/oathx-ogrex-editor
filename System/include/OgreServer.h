#ifndef _____OgreServer_H
#define _____OgreServer_H

#include "OgrePropertySet.h"

namespace Ogre
{
;

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
	* \Desc    : 基本服务接口
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API Server : public PropertySet
	{
	public:
		/** 构造函数
		 *
		 * \param typeName	指定该服务名
		 * \return 
		 */
		Server(const String& typeName);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~Server();

	public:
		/** 获取服务名
		 *
		 * \return 
		 */
		virtual	String				getTypeName() const;

		/** 设置服务名
		 *
		 * \param name 
		 */
		virtual void				setTypeName(const String& typeName);

		/**
		 *
		 */
		virtual bool				load();

		/**
		 *
		 */
		virtual void				unload();

	protected:
		String						m_typeName;
	};

	// 服务创建参数适配结构
	struct SSAdp
	{
		String						typeName;		// the server type name
		String						depServerName;	// dependencie server name
	};

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
	* \Desc    : 服务创建工厂
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API ServerFactory
	{
	public:
		static const String		FactoryTypeName;

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

	public:
		/** 获取工厂名
		 *
		 * \return 
		 */
		virtual String			getTypeName() const = 0;
	
		/** 创建服务
		 *
		 * \param pAdp	服务适配参数
		 * \return 
		 */
		virtual Server*			createServer(const SSAdp& ssadp) = 0;
	};
}

#endif