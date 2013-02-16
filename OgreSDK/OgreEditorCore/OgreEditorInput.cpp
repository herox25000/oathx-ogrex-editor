#include "OgreEditorCoreStdAfx.h"
#include "OgreEditorInput.h"

namespace Ogre
{
	/**
	 *
	 * \return 
	 */
	EditorInput::EditorInput()
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorInput::~EditorInput()
	{

	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool		EditorInput::OnSize(int cx, int cy)
	{
		return 0;
	}

	/**
	 *
	 * \param fzDelta 
	 * \param vPos 
	 * \return 
	 */
	bool		EditorInput::OnMouseWheel(float fzDelta, const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorInput::OnLButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorInput::OnLButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorInput::OnRButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorInput::OnRButtonUp(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool		EditorInput::OnMouseMove(const Vector2& vPos)
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
	bool		EditorInput::OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
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
	bool		EditorInput::OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
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
	bool		EditorInput::OnPropertyChanged(const String& parentName, const String& name, 
		const Any& anyValue, int nType)
	{
		return 0;
	}
}