#include "OgreEditSystemPrerequisites.h"
#include "OgreBaseEditor.h"

namespace Ogre
{
	/** ���캯��
	 *
	 * \return 
	 */
	BaseEditor::BaseEditor()
	{
	}

	/** ��������
	 *
	 * \param void 
	 * \return 
	 */
	BaseEditor::~BaseEditor(void)
	{
	}

	/** ��ȡ������
	 *
	 * \return 
	 */
	String		BaseEditor::getTypeName() const
	{
		return m_typeName;
	}


	/** ��ȡ������
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
