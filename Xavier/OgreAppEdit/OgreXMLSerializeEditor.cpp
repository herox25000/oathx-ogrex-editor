#include "OgreAppEditPrerequisites.h"
#include "OgreXMLSerializeEditor.h"
#include "OgreXMLSerialize.h"

namespace Ogre
{
	/**
	 *
	 * \param pThis 
	 * \return 
	 */
	XMLSerializeCreateEventArgs::XMLSerializeCreateEventArgs(XMLSerialize* pThis)
		:pSerialize(pThis)
	{

	}

	/**
	 *
	 * \return 
	 */
	XMLSerializeCreateEventArgs::~XMLSerializeCreateEventArgs()
	{

	}

	// define events
	const String XMLSerializeEditor::EventNamespace				= "XMLSerializeEditor";
	const String XMLSerializeEditor::EventXMLSerializeCreated	= "XMLSerializeCreated";

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XMLSerializeEditor::XMLSerializeEditor()
	{
		setTypeName(EDIT_XMLSERIALIZE);
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XMLSerializeEditor::~XMLSerializeEditor(void)
	{
		clearAllXMLSerialize();
	}
	
	/**
	 *
	 * \param sPath 
	 * \param sName 
	 * \return 
	 */
	XMLSerialize*	XMLSerializeEditor::createXMLSerialize(const String& sPath, const String& sName)
	{
		StringXMLSerialize::iterator it = m_vXMLSerialize.find(sName);
		if ( it == m_vXMLSerialize.end() )
		{
			XMLSerialize* pXMLSerialize = new XMLSerialize();
			assert(pXMLSerialize != NULL);

			if (pXMLSerialize->createSerialize(sPath, sName))
			{
				// insert to map manager
				m_vXMLSerialize.insert(StringXMLSerialize::value_type(sName, pXMLSerialize));

#ifdef _OUTPUT_LOG
				TKLogEvent("已创建文档 " + pXMLSerialize->getPathName(), LML_NORMAL);
#endif				
				// send create event
				fireEvent(EventXMLSerializeCreated,
					XMLSerializeCreateEventArgs(pXMLSerialize), EventNamespace);

				return pXMLSerialize;
			}
		}

		return NULL;
	}

	/**
	 *
	 * \param sName 
	 */
	void			XMLSerializeEditor::destroyXMLSerialize(const String& sName)
	{
		StringXMLSerialize::iterator it = m_vXMLSerialize.find(sName);
		if ( it != m_vXMLSerialize.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("已清理文档 " + it->second->getPathName(), LML_NORMAL);
#endif
			delete it->second; it = m_vXMLSerialize.erase(it);
		}
	}
	/**
	 *
	 * \return 
	 */
	void			XMLSerializeEditor::clearAllXMLSerialize()
	{
		StringXMLSerialize::iterator it = m_vXMLSerialize.begin();
		while ( it != m_vXMLSerialize.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("已清理文档 " + it->second->getPathName(), LML_NORMAL);
#endif
			delete it->second; it = m_vXMLSerialize.erase(it);
		}
	}

	/**
	 *
	 * \return 
	 */
	XMLSerializeEditorFactory::XMLSerializeEditorFactory()
	{
		setTypeName(FACTORY_XMLSERIALIZE);
	}

	/**
	 *
	 * \return 
	 */
	XMLSerializeEditorFactory::~XMLSerializeEditorFactory()
	{

	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*	XMLSerializeEditorFactory::create(const SBaseCreateParam* pm)
	{
		if (pm != NULL)
		{
			SXMLSerializeCreateParam* cm = (SXMLSerializeCreateParam*)(pm);

			/*
			* 创建文档编辑
			*/
			BaseEditor* editor = new XMLSerializeEditor();
			return editor;
		}

		return NULL;
	}
}
