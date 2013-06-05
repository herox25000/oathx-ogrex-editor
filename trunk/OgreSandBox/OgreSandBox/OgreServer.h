#ifndef _____OgreServer_H
#define _____OgreServer_H

#include "OgrePropertySet.h"

namespace Ogre
{
	struct SSAdp{
		String			szPropertyFilePath;
	};

	// child server table
	typedef map<uint32, Server*>::type	ServerRegister;

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
		 * \param ssadp 
		 * \return 
		 */
		virtual bool			configure(const SSAdp& ssadp);
		
		/**
		 *
		 * \param szPropertyFilePath 
		 */
		virtual	bool			loadProperty(const String& szPropertyFilePath);
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
}

#endif