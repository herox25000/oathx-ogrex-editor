#include "stdafx.h"
#include "EditorAction.h"

namespace Ogre
{
	/**
	 *
	 * \return 
	 */
	EditorAction::EditorAction(const String& name)
		: m_Name(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorAction::~EditorAction()
	{
		
	}

	/**
	 *
	 */
	void			EditorAction::execute()
	{
		
	}

	/**
	 *
	 * \return 
	 */
	const String&	EditorAction::getName() const
	{
		return m_Name;
	}
}