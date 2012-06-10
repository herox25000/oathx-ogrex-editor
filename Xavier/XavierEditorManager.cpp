#include "StdAfx.h"
#include "XavierAppEditor.h"
#include "XavierEditorManager.h"

namespace Ogre
{
	template<>	XavierEditorManager*	Singleton<XavierEditorManager>::msSingleton = NULL;
	XavierEditorManager&	XavierEditorManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	XavierEditorManager*	XavierEditorManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}
	
	/**
	 *
	 * \param void 
	 * \return 
	 */
	XavierEditorManager::XavierEditorManager(void) : m_pCurrentTool(NULL)
	{
	
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XavierEditorManager::~XavierEditorManager(void)
	{
		// 清空所有工具
		clearTool();
		
		// 青口编辑工具工厂
		clearEditorFactory();
	}
	
	/**
	 *
	 * \param pFactory 
	 */
	void					XavierEditorManager::registerEditorFactory(XavierEditorFactory* pFactory)
	{
		HashXavierEditorFactory::iterator it = m_HashEditorFactory.find(pFactory->getTypeName());
		if ( it == m_HashEditorFactory.end() )
		{
			m_HashEditorFactory.insert(HashXavierEditorFactory::value_type(pFactory->getTypeName(),
				pFactory));
		}
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierEditorFactory*	XavierEditorManager::getEditorFactory(const String& typeName)
	{
		HashXavierEditorFactory::iterator it = m_HashEditorFactory.find(typeName);
		if ( it != m_HashEditorFactory.end() )
		{
			return it->second;
		}		

		return NULL;
	}

	/**
	 *
	 * \param pFactory 
	 */
	void					XavierEditorManager::unregisterEditorFactory(XavierEditorFactory* pFactory)
	{
		HashXavierEditorFactory::iterator it = m_HashEditorFactory.find(pFactory->getTypeName());
		if ( it != m_HashEditorFactory.end() )
		{
			delete it->second; m_HashEditorFactory.erase(it);
		}
	}

	/**
	 *
	 */
	void					XavierEditorManager::clearEditorFactory()
	{
		HashXavierEditorFactory::iterator it = m_HashEditorFactory.begin();
		while( it != m_HashEditorFactory.end() )
		{
			delete it->second; it = m_HashEditorFactory.erase(it);
		}
	}

	/**
	 *
	 * \param pTool 
	 */
	void					XavierEditorManager::addTool(XavierEditor* pTool)
	{
		if (pTool != NULL)
		{
			VXavierEditor::iterator it = std::find(m_vEditor.begin(), m_vEditor.end(), pTool);
			if ( it == m_vEditor.end() )
			{
				m_vEditor.push_back(pTool);
			}
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	XavierEditor*			XavierEditorManager::getTool(const String& name)
	{
		for (VXavierEditor::iterator it=m_vEditor.begin(); it!=m_vEditor.end(); it++)
		{
			if ((*it)->getTypeName() == name)
				return (*it);
		}

		return NULL;
	}

	/**
	 *
	 * \param pTool 
	 */
	void					XavierEditorManager::delTool(XavierEditor* pTool)
	{
		VXavierEditor::iterator it = std::find(m_vEditor.begin(), m_vEditor.end(), pTool);
		if ( it != m_vEditor.end() )
		{
			delete (*it); m_vEditor.erase(it);
		}
	}

	/**
	 *
	 */
	void					XavierEditorManager::clearTool()
	{
		while( m_vEditor.size() )
		{
			XavierEditor* pTool = m_vEditor.back(); delete pTool; m_vEditor.pop_back();
		}
	}

	/**
	 *
	 * \return 
	 */
	VEditorIter			XavierEditorManager::getEditorIter()
	{
		return VEditorIter(m_vEditor.begin(), m_vEditor.end());
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	bool					XavierEditorManager::load(const String& name)
	{
		registerEditorFactory(new XavierWorldSpaceEditorFactory());
		registerEditorFactory(new XavierCameraEditorFactory());
		registerEditorFactory(new XavierViewportEditorFactory());
		registerEditorFactory(new XavierBaseGridEditorFactory());
		registerEditorFactory(new XavierTerrainEditorFactory());
		registerEditorFactory(new XavierTerrainPageEditorFactory());

		TiXmlDocument* pDocument = new TiXmlDocument();

		try{	
			if (!pDocument->LoadFile(name.c_str()))
				OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND, "can not found file " + name, "XavierEditorManager::load");

			// 获取根元素
			TiXmlElement* root = pDocument->RootElement();
			ASSERT(root != NULL);
			
			// 第一个节点
			TiXmlElement* node = root->FirstChildElement(
				XML_ATT_PROPERTYSET
				);
			while( node != NULL)
			{
				// 取得类型
				String typeName = node->Attribute(XML_TYPE_NAME);
				if (!typeName.empty())
				{
					XavierEditorFactory* pFactory = getEditorFactory(typeName);
					if (pFactory)
					{
						String propertySetFile = node->Attribute(XML_ATT_FILE);
						pFactory->setPropertySetFile(propertySetFile);
					}
				}

				node = node->NextSiblingElement();
			}

		}catch(Ogre::Exception& e)
		{
			TKLogEvent(e.getFullDescription(), LML_TRIVIAL);

			// 销毁
			SAFE_DELETE(pDocument);
		}
		
		// 销毁文档
		if (pDocument != NULL)
			delete pDocument;
				
		return 0;
	}

	/**
	 *
	 */
	void				XavierEditorManager::update()
	{
		System::getSingletonPtr()->update();
	}

	/**
	 *
	 */
	void				XavierEditorManager::unload()
	{

	}

	/**
	 *
	 * \param pTool 
	 * \return 
	 */
	void				XavierEditorManager::setCurrentTool(XavierEditor* pTool)
	{
		if (m_pCurrentTool != pTool)
		{
			m_pCurrentTool = pTool;
		}
	}

	/**
	 *
	 * \return 
	 */
	XavierEditor*		XavierEditorManager::getCurrentTool() const
	{
		return m_pCurrentTool;
	}
}
