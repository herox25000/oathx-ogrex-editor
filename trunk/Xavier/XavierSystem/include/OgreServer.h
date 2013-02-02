#ifndef _____OgreServer_H
#define _____OgreServer_H

#include "OgrePropertySet.h"

namespace Ogre
{
	// server create adapter param
	struct SServerAdp
	{
		String		name;
	};

	// server hash table
	typedef HashMap<String, Server*>	HashMapServer;
	// server hash table
	typedef MapIterator<HashMapServer>	HashMapServerIter;

	/**
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-30
	*
	* \Author  : lp
	*
	* \Desc    : base server object
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API Server : public PropertySet
	{
	public:
		/**	构造函数
		 *
		 * \param name		服务对象名称
		 * \return 
		 */
		Server(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual	~Server();

		/** 设置名称
		 *
		 * \param name 
		 */
		virtual	void				setName(const String& name);

		/** 获取名称
		 *
		 * \return 
		 */
		virtual	const String&		getName() const;

		/** grab
		 *
		 * \return 
		 */
		virtual	void				grab();

		/** get current ref count
		 *
		 * \return 
		 */
		virtual	int					getRefCount() const;

		/** drop the object
		 *
		 * \return 
		 */
		virtual	void				drop();

		/** register a server
		 *
		 * \param pServer 
		 * \return 
		 */
		virtual	bool				attachServer(Server* pServer);
		
		/** get child server object
		 *
		 * \param name 
		 * \return 
		 */
		virtual	Server*				getServer(const String& name);
		
		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	Server*				findServer(const String& name);

		/** ungister server object
		/**
		 *
		 * \param pServer 
		 * \param bDestroy	if the param is true, then will destroy
		 */
		virtual	void				detachServer(Server* pServer, bool bDestroy=true);
		
		/**
		 *
		 * \param pParent 
		 */
		virtual	void				setParent(Server* pParent);

		/**
		 *
		 * \return 
		 */
		virtual	Server*				getParent() const;

		/**
		 *
		 */
		virtual	void				destroyAllServer();
	protected:
		int							m_nRefCount;
		String						m_Name;
		HashMapServer				m_HashMapServer;
		Server*						m_pParent;
	};
}

#endif