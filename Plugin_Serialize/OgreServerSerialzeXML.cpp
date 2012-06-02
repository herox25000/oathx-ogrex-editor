#include "OgreSerialzePluginPrerequisites.h"
#include "OgreServerSerialzeXML.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \param name 
	 * \param path 
	 * \param version 
	 * \return 
	 */
	SerialzeXMLServer::SerialzeXMLServer(const String& typeName, const String& name, const String& path, 
		const String& version) : Server(typeName), m_pDocument(0), m_name(name), m_path(path), m_version(version)
	{
		m_pDocument = new TiXmlDocument();
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	SerialzeXMLServer::~SerialzeXMLServer(void)
	{
		if (m_pDocument)
		{
			m_pDocument->SaveFile(getFullPathName().c_str());
			delete m_pDocument;
		}
	}
	
	/**
	 *
	 * \return 
	 */
	String	SerialzeXMLServer::getSerialzeName() const
	{
		return m_name;
	}

	/**
	 *
	 * \return 
	 */
	String	SerialzeXMLServer::getSerialzePath() const
	{
		return m_path;
	}

	/**
	 *
	 * \return 
	 */
	String	SerialzeXMLServer::getFullPathName() const
	{
		String path = getSerialzePath();

		path.append("/");
		path.append(getSerialzeName());

		return path;
	}

	/**
	 *
	 * \return 
	 */
	String	SerialzeXMLServer::getVersion() const
	{
		return m_version;
	}

	//////////////////////////////////////////////////////////////////////////
	const String	SerialzeXMLServerFactory::FactoryTypeName = "Serialze/SerialzeXMLServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	SerialzeXMLServerFactory::SerialzeXMLServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String	SerialzeXMLServerFactory::getTypeName() const
	{
		return SerialzeXMLServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*	SerialzeXMLServerFactory::createServer(const SSAdp& ssadp)
	{
		const SSerialzdXMLAdp& adp = static_cast<const SSerialzdXMLAdp&>(ssadp);

		/*
		* create serialze form xml file
		*/
		return new SerialzeXMLServer(adp.typeName, 
									adp.name, 
									adp.path,
									adp.version
									);
	}
}
