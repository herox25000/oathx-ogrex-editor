#ifndef _____OgreServerSerialzeXML_H
#define _____OgreServerSerialzeXML_H

#include "OgreServer.h"
#include "tinyxml.h"

namespace Ogre
{
	/**
	* \ingroup : Plugin_Serialize
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-20
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Serialze_Export_API SerialzeXMLServer : public Server
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param name 
		 * \param path 
		 * \param version 
		 * \return 
		 */
		SerialzeXMLServer(const String& typeName, const String& name, const String& path, const String& version);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~SerialzeXMLServer(void);
	
		/**
		 *
		 * \return 
		 */
		virtual String					getSerialzeName() const;

		/**
		 *
		 * \return 
		 */
		virtual String					getSerialzePath() const;

		/**
		 *
		 * \return 
		 */
		virtual	String					getFullPathName() const;
		
		virtual	String					getVersion() const;
	protected:
		TiXmlDocument*					m_pDocument;
		String							m_name;
		String							m_path;
		String							m_version;
	};

	// ÎÄµµ²ÎÊý
	struct SSerialzdXMLAdp : public SSAdp
	{
		String				name;
		String				path;
		String				version;
	};

	/**
	* \ingroup : Plugin_Serialize
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-20
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Serialze_Export_API SerialzeXMLServerFactory : public ServerFactory
	{
	public:
		static const String		FactoryTypeName;

	public:
		/**
		 *
		 * \return 
		 */
		SerialzeXMLServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual String			getTypeName() const;

		/**
		 *
		 * \param ssadp 
		 * \return 
		 */
		virtual Server*			createServer(const SSAdp& ssadp);
	};
}

#endif

