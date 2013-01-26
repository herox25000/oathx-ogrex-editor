#include "stdafx.h"
#include "EditorPlugin.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param pluginName 
	 * \return 
	 */
	EditorPlugin::EditorPlugin(const String& pluginName)
		: m_Name(pluginName), m_pParent(NULL), m_bInheritPick(0), m_nPriority(PRIORITY_NORMAL)
	{
		
	}

	/**
	 *
	 * \return 
	 */
	EditorPlugin::~EditorPlugin()
	{
		destroyAllPlugin();
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
	 */
	void					EditorPlugin::destroyAllPlugin()
	{
		int nPriority	= PRIORITY_HEIGHT;
		do {
			HashMapEditorPlugin::iterator it = m_HashMapEditorPlugin.begin();
			while( it != m_HashMapEditorPlugin.end() )
			{
				if ( it->second->getPriority() == nPriority)
				{
					LogManager::getSingleton().logMessage(LML_NORMAL, 
						"Deleted this plugin tool :  " + it->second->getName());

					delete it->second; it = m_HashMapEditorPlugin.erase(it);
				}
				else
				{
					it ++;
				}
			}

			bool bFlags = 0;

			for (HashMapEditorPlugin::iterator c = m_HashMapEditorPlugin.begin();
				c!=m_HashMapEditorPlugin.end(); c++)
			{
				if (c->second->getPriority() == nPriority)
				{
					bFlags = true;
					break;
				}
			}

			if (!bFlags)
				nPriority --;

		} while (nPriority >= PRIORITY_LOWEST);
	}

	/**
	 *
	 * \return 
	 */
	HashMapEditorPluginIter	EditorPlugin::getPluginIter()
	{
		return HashMapEditorPluginIter(m_HashMapEditorPlugin.begin(), m_HashMapEditorPlugin.end());
	}

	/**
	 *
	 * \param bInheritPick 
	 */
	void					EditorPlugin::setInheritPick(bool bInheritPick)
	{
		m_bInheritPick = bInheritPick;
	}

	/**
	 *
	 * \return 
	 */
	bool					EditorPlugin::getInheritPick() const
	{
		return m_bInheritPick;
	}

	/**
	 *
	 * \param nPriority 
	 */
	void					EditorPlugin::setPriority(int nPriority)
	{
		m_nPriority = nPriority;
	}

	/**
	 *
	 * \return 
	 */
	int						EditorPlugin::getPriority() const
	{
		return m_nPriority;
	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool					EditorPlugin::OnSize(int cx, int cy)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnSize(cx, cy) && !pPlugin->getInheritPick())
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param fzDelta 
	 * \param vPos 
	 * \return 
	 */
	bool					EditorPlugin::OnMouseWheel(float fzDelta, const Vector2& vPos)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnMouseWheel(fzDelta, vPos) && !pPlugin->getInheritPick())
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool					EditorPlugin::OnLButtonDown(const Vector2& vPos)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnLButtonDown(vPos) && !pPlugin->getInheritPick())
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool					EditorPlugin::OnLButtonUp(const Vector2& vPos)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnLButtonUp(vPos) && !pPlugin->getInheritPick())
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool					EditorPlugin::OnRButtonDown(const Vector2& vPos)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnRButtonDown(vPos) && !pPlugin->getInheritPick())
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool					EditorPlugin::OnRButtonUp(const Vector2& vPos)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnRButtonUp(vPos) && !pPlugin->getInheritPick())
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool					EditorPlugin::OnMouseMove(const Vector2& vPos)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin)
			{
				if (pPlugin->OnMouseMove(vPos) && !pPlugin->getInheritPick())
					return true;
			}

		}

		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool					EditorPlugin::OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnKeyDown(nChar, nRepCnt, nFlags))
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool					EditorPlugin::OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnKeyUp(nChar, nRepCnt, nFlags) && !pPlugin->getInheritPick())
				return true;
		}

		return 0;
	}

	/**
	 *
	 * \param parentName 
	 * \param name 
	 * \param anyValue 
	 * \param nType 
	 * \return 
	 */
	bool					EditorPlugin::OnPropertyChanged(const String& parentName, const String& name, 
		const Any& anyValue, int nType)
	{
		HashMapEditorPluginIter hashPlugin = getPluginIter();
		while( hashPlugin.hasMoreElements() )
		{
			EditorPlugin* pPlugin = hashPlugin.getNext();
			if (pPlugin->OnPropertyChanged(parentName, name, anyValue, nType))
				return true;
		}

		return 0;
	}

}