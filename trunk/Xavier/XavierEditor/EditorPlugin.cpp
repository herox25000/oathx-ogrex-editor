#include "stdafx.h"
#include "EditorPlugin.h"

namespace Ogre
{
	/**
	 *
	 * \param pluginName 
	 * \return 
	 */
	EditorPlugin::EditorPlugin(const String& pluginName)
		: m_Name(pluginName), m_pParent(NULL)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	EditorPlugin::~EditorPlugin()
	{
		HashMapEditorPlugin::iterator it = m_HashMapEditorPlugin.begin();
		while( it != m_HashMapEditorPlugin.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Deleted this plugin tool :  " + it->second->getName());

			delete it->second; it = m_HashMapEditorPlugin.erase(it);
		}
	}

	/**
	 *
	 * \param pluginName 
	 */
	void				EditorPlugin::setName(const String& pluginName)
	{
		m_Name = pluginName;
	}

	/**
	 *
	 * \return 
	 */
	String				EditorPlugin::getName() const
	{
		return m_Name;
	}

	/**
	 *
	 * \param pPlugin 
	 * \return 
	 */
	bool				EditorPlugin::registerPlugin(EditorPlugin* pPlugin)
	{
		if (m_Name == pPlugin->getName())
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Can not add your own : " + pPlugin->getName());

			return 0;
		}

		HashMapEditorPlugin::iterator it = m_HashMapEditorPlugin.find(pPlugin->getName());
		if ( it == m_HashMapEditorPlugin.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				m_Name + "->Register editor plugin : " + pPlugin->getName());
			
			EditorPlugin* pParent = pPlugin->getParent();
			if (pParent)
				pParent->unregisterPlugin(pPlugin, 0);
			
			pPlugin->setParent(this);

			m_HashMapEditorPlugin.insert(
				HashMapEditorPlugin::value_type(pPlugin->getName(), pPlugin)
				);

			return true;
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"This plugin tool has been exist : " + pPlugin->getName());	
		}

		return 0;
	}

	/**
	 *
	 * \param pluginName 
	 * \return 
	 */
	EditorPlugin*			EditorPlugin::getPlugin(const String& pluginName)
	{
		HashMapEditorPlugin::iterator it = m_HashMapEditorPlugin.find(pluginName);
		if ( it != m_HashMapEditorPlugin.end() )
		{
			return it->second;
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"This plugin tool can not be found :  " + pluginName);
		}

		return NULL;
	}

	/**
	 *
	 * \param pluginName 
	 * \return 
	 */
	EditorPlugin*			EditorPlugin::findPlugin(const String& pluginName)
	{	
		if (m_Name == pluginName)
			return this;

		EditorPlugin* pPlugin = getPlugin(pluginName);
		if (!pPlugin)
		{
			HashMapEditorPlugin::iterator it = m_HashMapEditorPlugin.begin();
			while( it != m_HashMapEditorPlugin.end() )
			{
				pPlugin = it->second->findPlugin(pluginName);
				if (pPlugin)
					break;

				it ++;
			}
		}

		return pPlugin;		
	}

	/**
	 *
	 * \param pPlugin 
	 */
	void					EditorPlugin::unregisterPlugin(EditorPlugin* pPlugin, bool bDestroy)
	{
		HashMapEditorPlugin::iterator it = m_HashMapEditorPlugin.find(pPlugin->getName());
		if ( it != m_HashMapEditorPlugin.end() )
		{
			pPlugin->setParent(NULL);

			if (bDestroy)
			{
				LogManager::getSingleton().logMessage(LML_NORMAL, 
					"Deleted this plugin tool :  " + pPlugin->getName());
				
				delete it->second; 
			}

			m_HashMapEditorPlugin.erase(it);
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, 
				"This plugin tool can not be found :  " + pPlugin->getName());
		}
	}

	/**
	 *
	 * \param pParent 
	 */
	void					EditorPlugin::setParent(EditorPlugin* pParent)
	{
		m_pParent = pParent;
	}

	/**
	 *
	 * \return 
	 */
	EditorPlugin*			EditorPlugin::getParent() const
	{
		return m_pParent;
	}

	/**
	 *
	 * \return 
	 */
	HashMapEditorPluginIter	EditorPlugin::getPluginIter()
	{
		return HashMapEditorPluginIter(m_HashMapEditorPlugin.begin(), m_HashMapEditorPlugin.end());
	}
}