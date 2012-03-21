#include "OgreSystemPrerequisites.h"
#include "OgreXMLSerialize.h"

namespace Ogre
{	
	/**
	 *
	 * \param void 
	 * \return 
	 */
	XMLSerialize::XMLSerialize(void) : m_pDocument(NULL)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XMLSerialize::~XMLSerialize(void)
	{
		if (m_pDocument != NULL)
			delete m_pDocument;
	}

	/**
	 *
	 * \param sPath 
	 * \param sName 
	 * \return 
	 */
	bool	XMLSerialize::createSerialize(const String& sPath, const String& sName)
	{
		m_pDocument = new TiXmlDocument();
		if (m_pDocument == NULL)
			return 0;
		
		// 添加跟节点
		m_pDocument->LinkEndChild(new TiXmlElement("Xavier"));

		m_sPath	= sPath;
		m_sName	= sName;
	
		// 保存
		return m_pDocument->SaveFile(getPathName().c_str());
	}

	/**
	 *
	 * \return 
	 */
	String	XMLSerialize::getName() const
	{
		return m_sName;
	}

	/**
	 *
	 * \return 
	 */
	String	XMLSerialize::getPath() const
	{
		return m_sPath;
	}

	/**
	 *
	 * \return 
	 */
	String	XMLSerialize::getPathName() const
	{
		return String(m_sPath + "/" + m_sName);
	}

	/**
	 *
	 * \param sPathName 
	 * \return 
	 */
	bool	XMLSerialize::load(const String& sPathName)
	{
		return 0;
	}

	/**
	 *
	 */
	void	XMLSerialize::unload()
	{

	}
}
