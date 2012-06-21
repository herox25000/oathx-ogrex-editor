#include "GuardiolaDllExport.h"
#include "PyEvtSet.h"
#include "tinyxml.h"
#include "Server.h"

namespace Barcelona
{
	// 导入OGRE
	using namespace			Ogre;

	/**
	 *
	 * \return 
	 */
	Server::Server(const Ogre::String& typeName, const SSAdp& ssadp)
		:m_typeName(typeName)
	{
		// 加载属性定义文件
		loadProperty(ssadp.defPopertyFile);
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	Server::~Server(void)
	{
	}

	/**
	 *
	 * \return 
	 */
	String		Server::getTypeName() const
	{
		return m_typeName;
	}

	/**
	 *
	 * \param typeName 
	 */
	void		Server::setTypeName(const Ogre::String& typeName)
	{
		m_typeName = typeName;
	}

	/**
	 *
	 * \param path 
	 */
	void		Server::loadProperty(const Ogre::String& path)
	{
		if (!path.empty())
		{
			// 构造属性定义文件
			TiXmlDocument* pDocument = new TiXmlDocument();
			
			try
			{
				// 加载属性定义文件
				if (pDocument->LoadFile(path.c_str()))
					OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "can not found file " + path, "Server::loadProperty");
	
				TiXmlElement* root = pDocument->RootElement();
				assert(root);

				TiXmlElement* node = root->FirstChildElement(
					XML_ATT_PROPERTY
					);
				while( node != NULL )
				{
					String describe	= node->Attribute(XML_ATT_DESCRIBE);
					String name		= node->Attribute(XML_ATT_NAME);
					String val		= node->Attribute(XML_ATT_VALUE);
					String only		= node->Attribute(XML_ATT_WRITE);

					int typeValue	= PVT_UNKNOWN;
					node->Attribute(XML_ATT_TYPE, &typeValue);
					switch(typeValue)
					{
					case PVT_SHORT:
						addProperty(name, Any(StringConverter::parseInt(val)),
							PVT_SHORT,StringConverter::parseBool(only) , describe);
						break;

					case PVT_COLOUR:
						addProperty(name, Any(StringConverter::parseColourValue(val)),
							PVT_COLOUR,StringConverter::parseBool(only) , describe);
						break;
					}

					node = root->NextSiblingElement(XML_ATT_PROPERTY);
				}

			}catch( const Ogre::Exception& e) {
#ifdef _DEBUG_LOG
				TKLogEvent("waring: Ogre exception " + e.getFullDescription(), Ogre::LML_TRIVIAL);
#endif
				delete pDocument; 
				pDocument = NULL;
			}

			// 销毁属性文档
			if( pDocument != NULL)
			{
				delete pDocument;
				pDocument = NULL;
			}
		}
	}

	/**
	 *
	 */
	void		Server::unloadProperty()
	{
		clearProperty();
	}

	//////////////////////////////////////////////////////////////////////////
	const Ogre::String		ServerFactory::FactoryTypeName	= "ServerFactory/NullServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	ServerFactory::ServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	ServerFactory::~ServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	Ogre::String	ServerFactory::getTypeName() const
	{
		return ServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*			ServerFactory::createServer(const SSAdp& ssadp)
	{
#ifdef _DEBUG_LOG
		TKLogEvent("create server [" + ssadp.typeName + "] dependencie server : " + (ssadp.depServerName.empty() ? "NULL" : ssadp.depServerName));
#endif
		return new Server(ssadp.typeName, ssadp);
	}
}
