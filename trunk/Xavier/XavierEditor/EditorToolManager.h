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
	* \date    : 2013-01-22
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorToolManager : public Singleton<EditorToolManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorToolManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorToolManager*	getSingletonPtr();

	public:
		/**
		 *
		 * \return 
		 */
		EditorToolManager(const String& rootName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolManager();
		
		/**
		 *
		 * \return 
		 */
		virtual	EditorTool*		getRoot() const;

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	bool			addEditorTool(EditorTool* pEditorTool, EditorTool* pParent);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorTool*		getEditorTool(const String& name);

		/**
		 *
		 * \param pEditorTool 
		 */
		virtual	void			setCurrentEditorTool(EditorTool* pEditorTool);

		/**
		 *
		 * \return 
		 */
		virtual	EditorTool*		getCurrentEditorTool() const;
	protected:
		EditorTool*				m_pRoot;
		EditorTool*				m_pCurrent;
	};
}