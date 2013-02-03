#include "stdafx.h"
#include "EditorAction.h"
#include "EditorActionManager.h"

namespace Ogre
{
	template<>	EditorActionManager*	Singleton<EditorActionManager>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditorActionManager&	EditorActionManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditorActionManager*	EditorActionManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	EditorActionManager::EditorActionManager()
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorActionManager::~EditorActionManager()
	{
		DequeAction::iterator itR = m_DequeRedo.begin();
		while( itR != m_DequeRedo.end())
		{
			SAFE_DELETE(*itR); itR = m_DequeRedo.erase(itR);
		}

		DequeAction::iterator itU = m_DequeUndo.begin();
		while( itU != m_DequeUndo.end())
		{
			SAFE_DELETE(*itU); itU = m_DequeUndo.erase(itU);
		}
	}

	/**
	 *
	 * \param pRedo 
	 * \return 
	 */
	void	EditorActionManager::addRedo(EditorAction* pAction)
	{
		if (pAction)
		{
			m_DequeRedo.push_back(pAction);
		}
	}

	/**
	 *
	 * \return 
	 */
	bool	EditorActionManager::redo()
	{
		if (m_DequeRedo.size() > 0)
		{
			EditorAction* pAction = m_DequeRedo.back();
			if (pAction)
			{
				pAction->execute();
				m_DequeRedo.pop_back();
				addUndo(pAction);
			}
		}

		return true;
	}

	/**
	 *
	 * \param pAction 
	 * \return 
	 */
	void	EditorActionManager::addUndo(EditorAction* pAction)
	{
		if (pAction)
		{
			m_DequeUndo.push_back(pAction);
		}
	}

	/**
	 *
	 * \return 
	 */
	bool	EditorActionManager::undo()
	{
		if (m_DequeUndo.size() > 0)
		{
			EditorAction* pAction = m_DequeUndo.back();
			if (pAction)
			{
				pAction->execute();
				m_DequeUndo.pop_back();
				addRedo(pAction);
			}
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	int		EditorActionManager::getRedoCount() const
	{
		return m_DequeRedo.size();
	}

	/**
	 *
	 * \return 
	 */
	int		EditorActionManager::getUndoCount() const
	{
		return m_DequeUndo.size();
	}
}