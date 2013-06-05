#include "stdafx.h"
#include "OgreEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param szName 
	 * \return 
	 */
	Editor::Editor(const String& szName)
		: m_szName(szName), m_nAutoEditorID(0), m_pParent(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	Editor::~Editor()
	{
		destroy();
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	bool			Editor::create(const SEditorAdp& ssadp)
	{
		return 0;
	}

	/**
	 *
	 */
	void			Editor::destroy()
	{
		EditorRegister::iterator it = m_EditorRegister.begin();
		while( it != m_EditorRegister.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				m_szName + "->Unregister editor : " + it->second->getName());

			SAFE_DELETE(it->second); it = m_EditorRegister.erase(it);
		}
	}

	/**
	 *
	 * \param szName 
	 */
	void			Editor::setName(const String& szName)
	{
		m_szName = szName;
	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	String			Editor::makeAutoName(const String& szName)
	{
		char szAutoName[MAX_PATH];
		sprintf(szAutoName, "%s%d", szName.c_str(), m_nAutoEditorID);
		return szAutoName;
	}

	/**
	 *
	 * \return 
	 */
	const String&	Editor::getName() const
	{
		return m_szName;
	}

	/**
	 *
	 * \param pParent 
	 */
	void			Editor::setParent(Editor* pParent)
	{
		m_pParent = pParent;
	}

	/**
	 *
	 * \return 
	 */
	Editor*			Editor::getParent() const
	{
		return m_pParent;
	}

	/**
	 *
	 * \param pEditor 
	 */
	void			Editor::registerEditor(Editor* pEditor)
	{
		EditorRegister::iterator it = m_EditorRegister.find(pEditor->getName());
		if ( it != m_EditorRegister.end() )
		{
			// Renaming Editor
			String szName = makeAutoName(pEditor->getName());
			pEditor->setName(szName);
		}
		
		// reset parent editor
		Editor* pParent = pEditor->getParent();
		if (pParent)
			pParent->unregisterEditor(pEditor, 0);

		LogManager::getSingleton().logMessage(LML_NORMAL, 
			m_szName + "->Register editor : " + pEditor->getName());

		pEditor->setParent(this);

		// register editor object
		m_EditorRegister.insert(
			EditorRegister::value_type(pEditor->getName(), pEditor)
			);
	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	Editor*			Editor::findEditor(const String& szName)
	{
		if (m_szName == szName)
			return this;

		EditorRegister::iterator it = m_EditorRegister.begin();
		while (it != m_EditorRegister.end())
		{
			Editor* pEditor = it->second->findEditor(szName);
			if (pEditor)
				return pEditor;

			it ++;
		}

		return NULL;
	}

	/**
	 *
	 * \param pEditor 
	 */
	void			Editor::unregisterEditor(Editor* pEditor, bool bDestroy)
	{
		EditorRegister::iterator it = m_EditorRegister.find(pEditor->getName());
		if ( it != m_EditorRegister.end() )
		{
			LogManager::getSingleton().logMessage(LML_NORMAL, 
				m_szName + "->Unregister editor : " + pEditor->getName());

			if (bDestroy)
			{
				SAFE_DELETE(it->second);
			}
			
			m_EditorRegister.erase(it);
		}
	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool			Editor::OnSize(int cx, int cy)
	{
		return 0;
	}

	/**
	 *
	 * \param fzDelta 
	 * \param vPos 
	 * \return 
	 */
	bool			Editor::OnMouseWheel(float fzDelta, const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			Editor::OnLButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			Editor::OnLButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			Editor::OnRButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			Editor::OnRButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			Editor::OnMouseMove(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			Editor::OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			Editor::OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		return 0;
	}

	/**
	 *
	 * \return 
	 */
	bool			Editor::OnSetFocus()
	{
		return 0;
	}

	/**
	 *
	 * \return 
	 */
	bool			Editor::OnLoseFocus()
	{
		return 0;
	}

}