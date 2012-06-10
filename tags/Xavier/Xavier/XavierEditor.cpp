#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierEditor::XavierEditor(const String& typeName, const String& propertySetFile)
		:m_typeName(typeName), m_pServer(0), m_propertySetFile(propertySetFile)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	XavierEditor::~XavierEditor()
	{
		
	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierEditor::getTypeName() const
	{
		return m_typeName;
	}

	/**
	 *
	 * \param propertySetFile 
	 */
	void			XavierEditor::loadProperty()
	{
		TiXmlDocument* pDocument = new TiXmlDocument();

		try{	
			if (!pDocument->LoadFile(m_propertySetFile.c_str()))
				OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND, "can not found file " + m_propertySetFile, "XavierEditor::load");

			TiXmlElement* root = pDocument->RootElement();
			ASSERT(root);

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
					m_pServer->addProperty(name, Any(StringConverter::parseInt(val)),
						PVT_SHORT,StringConverter::parseBool(only) , describe);
					break;
				
				case PVT_COLOUR:
					m_pServer->addProperty(name, Any(StringConverter::parseColourValue(val)),
						PVT_COLOUR,StringConverter::parseBool(only) , describe);
					break;
				}

				node = root->NextSiblingElement(XML_ATT_PROPERTY);
			}
		}catch(Ogre::Exception& e)
		{
			SAFE_DELETE(pDocument);
		}

		if (pDocument)
		{
			delete pDocument;
			pDocument = NULL;
		}
	}

	/**
	 *
	 * \return 
	 */
	HashPropertyIter	XavierEditor::getHashPropertyIter()
	{
		return m_pServer->getHashPropertyIter();
	}
	
	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	XavierEditor::OnLButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	XavierEditor::OnLButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	XavierEditor::OnRButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	XavierEditor::OnRButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	XavierEditor::OnMouseMove(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param zDelta 
	 * \param vPos 
	 * \return 
	 */
	bool	XavierEditor::OnMouseWheel(float zDelta, const Vector2& vPos)
	{
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	XavierEditorFactory::XavierEditorFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	XavierEditorFactory::~XavierEditorFactory()
	{

	}

	/**
	 *
	 * \param name 
	 */
	void			XavierEditorFactory::setPropertySetFile(const String& name)
	{
		m_PropertySetFile = name;
	}
}