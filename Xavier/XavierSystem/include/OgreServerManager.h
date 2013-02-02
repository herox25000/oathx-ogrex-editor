#ifndef _____OgreServerManager_H
#define _____OgreServerManager_H

namespace Ogre
{
	struct SKernelServer
	{
		String					SERVER_SCENEMANAGER;
		String					SERVER_CAMERA;
		String					SERVER_VIEWPORT;
	};

	static	SKernelServer		Kernel;

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
	* \Desc    : 服务管理器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API ServerManager : public Singleton<ServerManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	ServerManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	ServerManager*	getSingletonPtr();

	public:
		/**
		 *
		 * \return 
		 */
		ServerManager(const String& rootName);

		/**
		 *
		 * \return 
		 */
		virtual ~ServerManager();
		
		/**
		 *
		 * \return 
		 */
		virtual	Server*					getRootServer() const;

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	Server*					getServer(const String& name);
	protected:
		Server*							m_pRootServer;
	};
}

#endif