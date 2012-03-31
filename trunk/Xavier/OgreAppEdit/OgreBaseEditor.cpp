#include "OgreAppEditPrerequisites.h"
#include "OgreBaseEditor.h"

namespace Ogre
{
	/** 构造函数
	 *
	 * \return 
	 */
	BaseEditor::BaseEditor() : m_pParent(NULL)
	{

	}

	/** 析构函数
	 *
	 * \param void 
	 * \return 
	 */
	BaseEditor::~BaseEditor(void)
	{
		clearEditor();
	}

	/** 获取类型名
	 *
	 * \return 
	 */
	String		BaseEditor::getTypeName() const
	{
		return m_typeName;
	}


	/** 获取类型名
	 *
	 * \param typeName 
	 */
	void		BaseEditor::setTypeName(const String& typeName)
	{
		m_typeName = typeName;
	}

	/**
	 *
	 * \param sPath 
	 * \return 
	 */
	bool		BaseEditor::load(const String& sPath)
	{
		return true;
	}

	/**
	 *
	 */
	void		BaseEditor::unload()
	{

	}

	/**
	 *
	 * \param pEditor 
	 */
	void		BaseEditor::setParent(BaseEditor* pEditor)
	{
		if (m_pParent != pEditor)
		{
			m_pParent = pEditor;
		}
	}

	/**
	 *
	 * \return 
	 */
	BaseEditor*	BaseEditor::getParent() const
	{
		return m_pParent;
	}

	/**
	 *
	 * \param pEditor 
	 */
	void		BaseEditor::addEditor(BaseEditor* pEditor)
	{
		if (pEditor != NULL)
		{
			VEditor::iterator it = std::find(m_vEditor.begin(), m_vEditor.end(), pEditor);
			if ( it == m_vEditor.end() )
			{
				pEditor->setParent(this);
#ifdef _OUTPUT_LOG
				TKLogEvent("已添加编辑器 " + pEditor->getTypeName(), LML_NORMAL);
#endif
				m_vEditor.push_back(pEditor);
			}
			else
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("重复添加编辑器 " + pEditor->getTypeName(), LML_TRIVIAL);
#endif
			}
		}
	}

	/**
	 *
	 * \param pEditor 
	 */
	void		BaseEditor::delEditor(BaseEditor* pEditor)
	{
		VEditor::iterator it = std::find(m_vEditor.begin(), m_vEditor.end(), pEditor);
		if ( it != m_vEditor.end() )
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("已卸载编辑器 " + (*it)->getTypeName(), LML_NORMAL);
#endif
			delete pEditor; m_vEditor.erase(it);
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	BaseEditor*	BaseEditor::getEditor(const String& name)
	{
		for (size_t i=0; i<m_vEditor.size(); i++)
		{
			if (m_vEditor[i]->getTypeName() == name)
				return m_vEditor[i];
		}

		return NULL;
	}

	/**
	 *
	 */
	void		BaseEditor::clearEditor()
	{
		while(m_vEditor.size())
		{
			BaseEditor* pEditor = m_vEditor.back();
			if (pEditor == NULL)
				break;
#ifdef _OUTPUT_LOG
			TKLogEvent("已卸载编辑器 " + pEditor->getTypeName(), LML_NORMAL);
#endif
			delete pEditor; m_vEditor.pop_back();		
		}
	}
	
	/**
	 *
	 * \param index 
	 * \return 
	 */
	BaseEditor*	BaseEditor::getEditor(int index)
	{
		return m_vEditor[index];
	}

	/**
	 *
	 * \return 
	 */
	size_t		BaseEditor::getEditorCount() const
	{
		return m_vEditor.size();
	}

	/**
	 *
	 * \param pFactory 
	 */
	void		BaseEditor::registerEditorFactory(BaseEditorFactory* pFactory)
	{
		if (pFactory != NULL)
		{
			VEditorFactory::iterator it = std::find(m_vFactory.begin(), m_vFactory.end(), pFactory);
			if ( it == m_vFactory.end() )
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("已注册编辑器 " + pFactory->getTypeName(), LML_NORMAL);
#endif
				m_vFactory.push_back(pFactory);
			}
			else
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("重复注册编辑器 " + pFactory->getTypeName(), LML_TRIVIAL);
#endif
			}
		}
	}

	/**
	 *
	 * \param pFactory 
	 */
	void		BaseEditor::unregisterEditorFactory(BaseEditorFactory* pFactory)
	{
		if (pFactory != NULL)
		{
			VEditorFactory::iterator it = std::find(m_vFactory.begin(), m_vFactory.end(), pFactory);
			if ( it != m_vFactory.end() )
			{
#ifdef _OUTPUT_LOG
				TKLogEvent("已注销编辑器 " + (*it)->getTypeName(), LML_NORMAL);
#endif		
				delete (*it); m_vFactory.erase(it);
			}
		}
	}

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	BaseEditorFactory*	BaseEditor::getEditorFactory(const String& typeName)
	{
		for (size_t i=0; i<m_vFactory.size(); i++)
		{
			if (m_vFactory[i]->getTypeName() == typeName)
				return m_vFactory[i];
		}

		return NULL;
	}

	/**
	 *
	 */
	void		BaseEditor::clearEditorFactory()
	{
		while(m_vFactory.size())
		{
			BaseEditorFactory* pFactory = m_vFactory.back();
			if (pFactory == NULL)
				break;
#ifdef _OUTPUT_LOG
			TKLogEvent("已注销编辑工厂 " + pFactory->getTypeName(), LML_NORMAL);
#endif
			delete pFactory; m_vFactory.pop_back();		
		}
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param void 
	 * \return 
	 */
	BaseEditorFactory::BaseEditorFactory(void)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	BaseEditorFactory::~BaseEditorFactory(void)
	{
	}

	/**
	 *
	 * \return 
	 */
	String		BaseEditorFactory::getTypeName() const
	{
		return m_typeName;
	}

	/**
	 *
	 * \param typeName 
	 */
	void		BaseEditorFactory::setTypeName(const String& typeName)
	{
		m_typeName = typeName;
	}
}
