#ifndef _____OgreServer_H
#define _____OgreServer_H

#include "OgrePropertySet.h"

namespace Ogre
{
	struct SSAdp{
		String			szPropertyFilePath;
	};

	/**
	* \ingroup : OgreSandBox
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-07
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBox_Export_API RegServerEventArgs : public EventArgs
	{
	public:
		RegServerEventArgs(Server* pSend)
			: pServer(pSend)
		{

		}

	public:
		Server*			pServer;
	};

	/**
	* \ingroup : OgreSandBox
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-07
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBox_Export_API LoadPropertyEventArgs : public EventArgs
	{
	public:
		/**
		 *
		 * \param szPath 
		 * \return 
		 */
		LoadPropertyEventArgs(const String& szPath)
			: szPathName(szPath)
		{

		}

	public:
		String				szPathName;
	};

	// child server table
	typedef map<uint32, Server*>::type	ServerRegister;
	typedef MapIterator<ServerRegister>	ServerIterator;

	/**
	* \ingroup : OgreSandBox
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-06
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBox_Export_API Server : public PropertySet
	{
	public:
		static const String		EventNamespace;
		static const String		ServerTypeName;

		static const String		EventRegisterServer;
		static const String		EventUnregisterServer;
		static const String		EventLoadProperty;
	public:
		/**
		 *
		 * \param nID 
		 * \param szName 
		 * \return 
		 */
		Server(const uint32 nID, const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual ~Server();

	public:
		/**
		 *
		 * \return 
		 */
		virtual	uint32			getID() const;

		/**
		 *
		 * \param nID 
		 */
		virtual	void			setID(const uint32 nID);

		/**
		 *
		 * \param szName 
		 */
		virtual	void			setName(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual const String&	getName() const;

		/**
		 *
		 * \param pParent 
		 */
		virtual	void			setParent(Server* pParent);
		/**
		 *
		 * \return 
		 */
		virtual	Server*			getParent() const;

		/**
		 *
		 * \param pServer 
		 */
		virtual	void			registerServer(Server* pServer);

		/**
		 *
		 * \param nID 
		 * \return 
		 */
		virtual	Server*			getServer(const uint32 nID);

		/**
		 *
		 * \param pServer 
		 */
		virtual void			unregisterServer(Server* pServer, bool bDestory=true);

		/**
		 *
		 * \return 
		 */
		virtual	ServerIterator	getServerIterator();

		/**
		 *
		 */
		virtual	void			destroyAllServer();

		/**
		 *
		 * \param ssadp 
		 * \return 
		 */
		virtual bool			configure(const SSAdp& ssadp);
		
	protected:
		Server*					m_pParent;
		ServerRegister			m_ServerRegister;
		uint32					m_nID;
		String					m_szName;
	};

	/**
	* \ingroup : OgreSandBox
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-06
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBox_Export_API ServerFactory
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		ServerFactory(const String& typeName)
			: m_typeName(typeName)
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual ~ServerFactory()
		{

		}

		/**
		 *
		 * \param typeName 
		 */
		virtual	void			setTypeName(const String& typeName)
		{
			m_typeName = typeName;
		}

		/**
		 *
		 * \return 
		 */
		virtual	const String&	getTypeName() const
		{
			return m_typeName;
		}

		/**
		 *
		 * \param nID 
		 * \param ssadp 
		 * \return 
		 */
		virtual	Server*			createServer(const uint32 nID, const String& szName, const SSAdp& ssadp, Server* pParent) = 0;

	protected:
		String					m_typeName;
	};

	
	/**
	* \ingroup : OgreSandBox
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-07
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template<typename T> 
		class TemplateServerFactory : public ServerFactory
	{
	public:
		/**
		 *
		 * \return 
		 */
		TemplateServerFactory();
		
		/**
		 *
		 * \param nID 
		 * \param szName 
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	Server*			createServer(const uint32 nID, const String& szName, const SSAdp& ssadp, Server* pParent);
	};
	
	/**
	 *
	 * \return 
	 */
	template <typename T>
		TemplateServerFactory<T>::TemplateServerFactory() 
			: ServerFactory(T::ServerTypeName)
		{
		}

	/**
	 *
	 * \param nID 
	 * \param szName 
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	template <typename T>
		Server* TemplateServerFactory<T>::createServer(const uint32 nID, const String& szName, const SSAdp& ssadp, Server* pParent)
	{
		Server* pServer = new T(nID, szName);
		try{
			if (pServer->configure(ssadp))
			{
				if (pParent)
					pParent->registerServer(pServer);

				return pServer;
			}
			else
			{
				OGRE_EXCEPT(Exception::ERR_RT_ASSERTION_FAILED, "Crate server " + szName + " error",
					"createServer");
			}
		}
		catch(Exception& e)
		{
			TKLogEvent(e.getFullDescription().c_str(), 
				LML_CRITICAL);

			delete pServer;
		}

		return NULL;
	}
}

#endif