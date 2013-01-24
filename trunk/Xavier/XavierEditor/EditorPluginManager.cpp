#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorPluginManager.h"

namespace Ogre
{
	template<>	EditorPluginManager*	Singleton<EditorPluginManager>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	EditorPluginManager&	EditorPluginManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	EditorPluginManager*	EditorPluginManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \param rootName 
	 * \return 
	 */
	EditorPluginManager::EditorPluginManager(const String& rootName)
		: m_pRootPlugin(NULL), m_pSelectPlugin(NULL)
	{
		m_pRootPlugin = new EditorPlugin(rootName);
		if (m_pRootPlugin)
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Init root plugin : " + rootName);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorPluginManager::~EditorPluginManager()
	{
		delete m_pRootPlugin;
	}

	/**
	 *
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::getRootPlugin() const
	{
		return m_pRootPlugin;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::findPlugin(const String& name)
	{
		if (name == m_pRootPlugin->getName())
			return m_pRootPlugin;

		return m_pRootPlugin->findPlugin(name);
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void			EditorPluginManager::setSelectPlugin(EditorPlugin* pPlugin)
	{
		if (m_pSelectPlugin != pPlugin)
			m_pSelectPlugin = pPlugin;
	}

	/**
	 *
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::getSelectPlugin() const
	{
		return m_pSelectPlugin;
	}

	/**
	 *
	 * \param factoryName 
	 * \param seadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::createEditorPlugin(const int factoryType, const SEditorPluginAdp& seadp,
		EditorPlugin* pParent)
	{
		return NULL;
	}
}