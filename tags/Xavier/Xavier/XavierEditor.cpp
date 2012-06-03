#include "stdafx.h"
#include "XavierEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierEditor::XavierEditor(const String& typeName)
		:m_typeName(typeName)
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
}