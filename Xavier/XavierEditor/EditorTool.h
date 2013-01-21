#pragma once

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-21
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorTool
	{
	public:
		/**
		 *
		 * \return 
		 */
		EditorTool(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorTool();

		/**
		 *
		 */
		virtual	void				setName(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual	String				getName() const;

	protected:
		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnLButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnLButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnRButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnRButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnMouseMove(const Vector2& vPos);

		/**
		 *
		 * \param zDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnMouseWheel(float zDelta, const Vector2& vPos);
	protected:
		String						m_name;
	};

	struct SEditorAdp
	{
		
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-21
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorToolFactory
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorToolFactory(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolFactory();

		/**
		 *
		 * \param seadp 
		 */
		virtual void				createEditorTool(const SEditorAdp& seadp) = 0;

		/**
		 *
		 * \return 
		 */
		virtual	String				getName() const;

		/**
		 *
		 * \param name 
		 */
		virtual	void				setName(const String& name);

	protected:
		String						m_name;
	};
}