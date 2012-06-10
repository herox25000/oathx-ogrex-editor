#pragma once

#include "OgreSingleton.h"
#include "XavierEditor.h"

namespace Ogre
{
	typedef std::vector<XavierEditor*>				VXavierEditor;
	typedef HashMap<String, XavierEditorFactory*>	HashXavierEditorFactory;
	typedef VectorIterator<VXavierEditor>			VEditorIter;

	/**
	* \ingroup : Xavier
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-06-09
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class XavierEditorManager : public Singleton<XavierEditorManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	XavierEditorManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	XavierEditorManager*	getSingletonPtr();
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		XavierEditorManager(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~XavierEditorManager(void);

		/**
		 *
		 * \param pFactory 
		 */
		/**
		 *
		 * \param pFactory 
		 */
		virtual void					registerEditorFactory(XavierEditorFactory* pFactory);

		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual	XavierEditorFactory*	getEditorFactory(const String& typeName);

		/**
		 *
		 * \param pFactory 
		 */
		virtual	void					unregisterEditorFactory(XavierEditorFactory* pFactory);

		/**
		 *
		 */
		virtual	void					clearEditorFactory();

		/**
		 *
		 * \param pTool 
		 */
		virtual	void					addTool(XavierEditor* pTool);

		/**
		 *
		 * \param name 
		 */
		virtual	XavierEditor*			getTool(const String& name);

		/**
		 *
		 * \param pTool 
		 */
		virtual	void					delTool(XavierEditor* pTool);

		/**
		 *
		 */
		virtual	void					clearTool();

		/**
		 *
		 * \return 
		 */
		virtual VEditorIter				getEditorIter();

		/** ¼ÓÔØ±à¼­Æ÷
		 *
		 * \param name 
		 * \return 
		 */
		virtual	bool					load(const String& name);

		/**
		 *
		 */
		virtual	void					update();

		/** Ð¶ÔØ±à¼­Æ÷
		 *
		 */
		virtual	void					unload();
		
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual	void					setCurrentTool(XavierEditor* pTool);

		/**
		 *
		 * \return 
		 */
		virtual	XavierEditor*			getCurrentTool() const;
	protected:
		HashXavierEditorFactory			m_HashEditorFactory;
		VXavierEditor					m_vEditor;
		XavierEditor*					m_pCurrentTool;
	};
}
