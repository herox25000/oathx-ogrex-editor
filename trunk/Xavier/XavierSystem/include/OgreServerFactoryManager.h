#ifndef _____OgreServerFactoryManager_H
#define _____OgreServerFactoryManager_H

namespace Ogre
{
	// factory register
	typedef HashMap<String, ServerFactory*>	HashMapServerFactory;

	enum {
		SERVER_SCENEMANAGER,
		SERVER_CAMERA,
		SERVER_VIEWPORT,
		SERVER_TERRAINGROUP,
		SERVER_TERRAIN,
	};

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
	class Ogre_System_Export_API ServerFactoryManager : public Singleton<ServerFactoryManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	ServerFactoryManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	ServerFactoryManager*	getSingletonPtr();

	public:
		/**
		 *
		 * \return 
		 */
		ServerFactoryManager();

		/**
		 *
		 * \return 
		 */
		virtual ~ServerFactoryManager();

		/**
		 *
		 * \param typeName 
		 * \param pFactory 
		 * \return 
		 */
		virtual	bool			registerServerFactory(ServerFactory* pFactory);

		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual	ServerFactory*	getServerFactory(const String& typeName);

		/**
		 *
		 * \param nID 
		 * \return 
		 */
		virtual	ServerFactory*	getServerFactory(int nID);

		/**
		 *
		 * \param pFactory 
		 */
		virtual	void			unregisterServerFactory(ServerFactory* pFactory);

	protected:
		HashMapServerFactory	m_HashMapServerFactory;
	};
}

#endif