#include "OgreEditSystemPrerequisites.h"
#include "OgreBaseEditor.h"

namespace Ogre
{
	/** 构造函数
	 *
	 * \return 
	 */
	BaseEditor::BaseEditor()
	{
	}

	/** 析构函数
	 *
	 * \param void 
	 * \return 
	 */
	BaseEditor::~BaseEditor(void)
	{
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
