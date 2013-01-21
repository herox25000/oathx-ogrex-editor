#include "stdafx.h"
#include "EditorTool.h"

namespace Ogre
{
	/**
	 *
	 * \return 
	 */
	EditorTool::EditorTool(const String& name)
		: m_name(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorTool::~EditorTool()
	{

	}
	
	/**
	 *
	 * \param name 
	 */
	void	EditorTool::setName(const String& name)
	{
		m_name = name;
	}

	/**
	 *
	 * \return 
	 */
	String	EditorTool::getName() const
	{
		return m_name;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorTool::OnLButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorTool::OnLButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorTool::OnRButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorTool::OnRButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorTool::OnMouseMove(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param zDelta 
	 * \param vPos 
	 * \return 
	 */
	bool	EditorTool::OnMouseWheel(float zDelta, const Vector2& vPos)
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