#pragma once

namespace Ogre
{
	typedef HashMap<String, EditorToolFactory*>	HashMapEditorToolFactory;

	enum {
		EDITOR_WORLD,
	};
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
	class EditorToolFactoryManager : public Singleton<EditorToolFactoryManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorToolFactoryManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorToolFactoryManager*	getSingletonPtr();
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		EditorToolFactoryManager(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditorToolFactoryManager(void);

		/**
		 *
		 * \param pFactory 
		 */
		virtual	void						registerEditorToolFactory(EditorToolFactory* pFactory);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorToolFactory*			getEditorToolFactory(const String& name);

		/**
		 *
		 * \param nID 
		 * \return 
		 */
		virtual	EditorToolFactory*			getEditorToolFactory(const int nID);

		/**
		 *
		 * \param pFactory 
		 */
		virtual	void						unregisterEditorToolFactory(EditorToolFactory* pFactory);

	private:
		HashMapEditorToolFactory			m_HashMapEditorToolFactory;
	};

}
