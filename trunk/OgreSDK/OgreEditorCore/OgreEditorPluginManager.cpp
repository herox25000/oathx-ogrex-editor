#include "OgreEditorCoreStdAfx.h"
#include "OgreEditorPluginManager.h"

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
			LogManager::getSingleton().logMessage("Init root plugin : " + rootName, LML_NORMAL);
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
	 * \param vPos 
	 * \return 
	 */
	bool			EditorPluginManager::injectMouseMove(const Vector2& vPos)
	{
		if (m_pSelectPlugin != NULL)
		{
			bool bResult = m_pSelectPlugin->OnMouseMove(vPos);
			if (!bResult)
			{
				
			}
		}

		return true;
	}
}