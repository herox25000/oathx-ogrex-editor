#include "stdafx.h"
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
			TKLogEvent("Init root plugin : " + rootName, LML_NORMAL);
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
		// ��ʧ����
		if (m_pSelectPlugin != pPlugin)
		{
			if (m_pSelectPlugin != NULL)
				m_pSelectPlugin->OnLoseFocus();

			m_pSelectPlugin = pPlugin;

			// ��ȡ����
			if (m_pSelectPlugin)
				m_pSelectPlugin->OnSetFocus();
		}
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
	 * \param vPos 
	 * \return 
	 */
	EditorPlugin*	EditorPluginManager::getPlugin(const Vector2& vPos)
	{
		return NULL;
	}
}