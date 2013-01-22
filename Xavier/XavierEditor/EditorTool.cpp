#include "stdafx.h"
#include "EditorTool.h"

namespace Ogre
{
	/**
	 *
	 * \return 
	 */
	EditorTool::EditorTool(const String& name)
		: m_name(name), m_pParent(NULL)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorTool::~EditorTool()
	{
		HashMapEditorTool::iterator it = m_HashMapEditorTool.begin();
		while( it != m_HashMapEditorTool.end() )
		{
			delete it->second; it = m_HashMapEditorTool.erase(it);
		}
	}
	
	/**
	 *
	 * \param name 
	 */
	void		EditorTool::setName(const String& name)
	{
		m_name = name;
	}

	/**
	 *
	 * \return 
	 */
	String		EditorTool::getName() const
	{
		return m_name;
	}
	
	/**
	 *
	 * \param pParent 
	 */
	void		EditorTool::setParent(EditorTool* pParent)
	{
		m_pParent = pParent;
	}

	/**
	 *
	 * \return 
	 */
	EditorTool*	EditorTool::getParent() const
	{
		return m_pParent;
	}

	/**
	 *
	 * \param nType 
	 * \param adp 
	 * \return 
	 */
	bool		EditorTool::addEditorTool(EditorTool* pEditorTool)
	{
		HashMapEditorTool::iterator it = m_HashMapEditorTool.find(pEditorTool->getName());
		if ( it == m_HashMapEditorTool.end() )
		{
			m_HashMapEditorTool.insert(
				HashMapEditorTool::value_type(pEditorTool->getName(), pEditorTool)
				);

			return true;
		}
		
		return 0;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorTool*	EditorTool::getEditorTool(const String& name)
	{
		HashMapEditorTool::iterator it = m_HashMapEditorTool.find(name);
		if ( it != m_HashMapEditorTool.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param pEditorTool 
	 */
	void		EditorTool::removeEditorTool(EditorTool* pEditorTool)
	{
		HashMapEditorTool::iterator it = m_HashMapEditorTool.find(pEditorTool->getName());
		if ( it != m_HashMapEditorTool.end() )
		{
			delete it->second; m_HashMapEditorTool.erase(it);
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorTool*	EditorTool::findEditorTool(const String& name)
	{
		if (m_name == name)
			return this;

		EditorTool* pTool = getEditorTool(name);
		if (pTool == NULL)
		{
			HashMapEditorTool::iterator it = m_HashMapEditorTool.begin();
			while( it != m_HashMapEditorTool.end() )
			{
				pTool = it->second->findEditorTool(name);
				if (pTool != NULL)
					return pTool;

				it ++;
			}
		}

		return pTool;
	}

	/**
	 *
	 * \return 
	 */
	EditorTool::HashMapEditorIter EditorTool::getHashMapEditorIter()
	{
		return HashMapEditorIter(m_HashMapEditorTool.begin(), m_HashMapEditorTool.end());
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorTool::OnLButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorTool::OnLButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorTool::OnRButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorTool::OnRButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorTool::OnMouseMove(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param zDelta 
	 * \param vPos 
	 * \return 
	 */
	bool		EditorTool::OnMouseWheel(float zDelta, const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool		EditorTool::OnSize(int cx, int cy)
	{
		return 0;
	}

	/**
	 *
	 * \param name 
	 * \param angValue 
	 * \param nValueType 
	 * \return 
	 */
	bool		EditorTool::OnPropertyChanged(const String& parentName, const String& name, Any angValue,
		int nValueType)
	{
		return 0;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolFactory::EditorToolFactory(const String& name)
		: m_name(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorToolFactory::~EditorToolFactory()
	{

	}

	/**
	 *
	 * \param name 
	 */
	void	EditorToolFactory::setName(const String& name)
	{
		m_name = name;
	}

	/**
	 *
	 * \return 
	 */
	String	EditorToolFactory::getName() const
	{
		return m_name;
	}
}