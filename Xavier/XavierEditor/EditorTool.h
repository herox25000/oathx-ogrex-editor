#pragma once

#include "EditorPropertyKeyWordDef.h"
#include "OgreIteratorWrapper.h"

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
	class EditorTool : public PropertySet
	{
	public:
		typedef HashMap<String, EditorTool*>	HashMapEditorTool;
		typedef MapIterator<HashMapEditorTool>	HashMapEditorIter;

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

		/**
		 *
		 * \param pParent 
		 */
		virtual	void				setParent(EditorTool* pParent);

		/**
		 *
		 * \return 
		 */
		virtual	EditorTool*			getParent() const;

		/**
		 *
		 * \param nType 
		 * \param adp 
		 * \return 
		 */
		virtual	bool				addEditorTool(EditorTool* pEditorTool);
		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorTool*			getEditorTool(const String& name);

		/**
		 *
		 * \param pEditorTool 
		 */
		virtual	void				removeEditorTool(EditorTool* pEditorTool);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorTool*			findEditorTool(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual	EditorTool::HashMapEditorIter	getHashMapEditorIter();
	public:
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

		/**
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool				OnSize(int cx, int cy);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 */
		virtual bool				OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 */
		virtual bool				OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param name 
		 * \param angValue 
		 * \param nValueType 
		 * \return 
		 */
		virtual bool				OnPropertyChanged(const String& parentName, const String& name, 
			Any anyValue, int nValueType);
	protected:
		String						m_name;
		HashMapEditorTool			m_HashMapEditorTool;
		EditorTool*					m_pParent;
	};

	struct SEditorAdp
	{
		String		name;
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
		virtual EditorTool*			createEditorTool(const SEditorAdp& seadp) = 0;

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