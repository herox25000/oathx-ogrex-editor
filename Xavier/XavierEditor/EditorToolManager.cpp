#include "stdafx.h"
#include "EditorTool.h"
#include "EditorToolManager.h"

namespace Ogre
{
	template<>	EditorToolManager*	Singleton<EditorToolManager>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditorToolManager&		EditorToolManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditorToolManager*		EditorToolManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \return 
	 */
	EditorToolManager::EditorToolManager(const String& rootName)
		: m_pSelect(NULL)
	{
		m_pRoot = new EditorTool(rootName);
	}

	/**
	 *
	 * \return 
	 */
	EditorToolManager::~EditorToolManager()
	{
		delete m_pRoot;
	}

	/**
	 *
	 * \return 
	 */
	EditorTool*	EditorToolManager::getRoot() const
	{
		return m_pRoot;
	}

	/**
	 *
	 * \param pEditorTool 
	 * \param pParent 
	 * \return 
	 */
	bool		EditorToolManager::addEditorTool(EditorTool* pEditorTool, EditorTool* pParent)
	{
		if (pParent != NULL)
		{
			// Ìí¼Ó±à¼­Æ÷
			if (pParent->addEditorTool(pEditorTool))
			{
				pEditorTool->setParent(pParent);
			}
		}
		else
		{
			if (m_pRoot->addEditorTool(pEditorTool))
			{
				pEditorTool->setParent(m_pRoot);
			}
		}

		return true;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorTool*	EditorToolManager::getEditorTool(const String& name)
	{
		if (m_pRoot->getName() == name)
			return m_pRoot;

		return m_pRoot->findEditorTool(name);
	}

	/**
	 *
	 * \param pEditorTool 
	 */
	void		EditorToolManager::setSelectEditorTool(EditorTool* pEditorTool)
	{
		m_pSelect = pEditorTool;
	}

	/**
	 *
	 * \return 
	 */
	EditorTool*	EditorToolManager::getSelectEditorTool() const
	{
		return m_pSelect;
	}
}