#ifndef _____OgreEditor_H
#define _____OgreEditor_H

namespace Ogre
{
	// create editor adapter param
	struct SEditorAdp
	{
	};
	
	/**
	* \ingroup : OgreSandBoxEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-02
	*
	* \Author  : lp
	*
	* \Desc    : Sand box editor base class
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBoxEdit_Export_API Editor : public PropertySet
	{
	public:
		// editor regsiter table
		typedef map<String, Editor*>::type			EditorRegister;
		// editor register iter
		typedef MapIterator<EditorRegister>			EditorRegisterIter;

		/**
		 *
		 * \param szName 
		 * \return 
		 */
		Editor(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual ~Editor();

	public:
		/**
		 *
		 * \param ssadp 
		 * \return 
		 */
		virtual	bool				create(const SEditorAdp& ssadp);

		/**
		 *
		 */
		virtual	void				destroy();

		/** set editor name
		 *
		 * \param szName 
		 */
		virtual	void				setName(const String& szName);

		/**
		 *
		 * \param szName 
		 * \return 
		 */
		virtual String				makeAutoName(const String& szName);

		/** get editor name
		 *
		 * \return 
		 */
		virtual const String&		getName() const;

		/** set editor parent
		 *
		 * \param pParent 
		 */
		virtual	void				setParent(Editor* pParent);

		/** get editor parent
		 *
		 * \return 
		 */
		virtual	Editor*				getParent() const;

	public:
		/**
		 *
		 * \param pEditor 
		 */
		virtual	void				registerEditor(Editor* pEditor);

		/**
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	Editor*				findEditor(const String& szName);

		/**
		 *
		 * \param pEditor 
		 */
		virtual	void				unregisterEditor(Editor* pEditor, 
			bool bDestroy=0);

	public:
		/**
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool				OnSize(int cx, int cy);

		/**
		 *
		 * \param fzDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnMouseWheel(float fzDelta, const Vector2& vPos);

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
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool				OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool				OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \return 
		 */
		virtual	bool				OnSetFocus();

		/**
		 *
		 * \return 
		 */
		virtual	bool				OnLoseFocus();
	protected:
		EditorRegister				m_EditorRegister;
		Editor*						m_pParent;
		String						m_szName;
		uint32						m_nAutoEditorID;
	};

	/**
	* \ingroup : OgreSandBoxEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-02
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBoxEdit_Export_API EditorFactory
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		EditorFactory(const String& typeName)
			: m_typeName(typeName)
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual ~EditorFactory()
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual	const String&		getTypeName() const
		{
			return m_typeName;
		}

		/**
		 *
		 * \param szName 
		 * \param seadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	Editor*				create(const String& szName, const SEditorAdp& seadp, Editor* pParent) = 0;
	protected:
		String						m_typeName;
	};
}

#endif