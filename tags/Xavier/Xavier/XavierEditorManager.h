#pragma once

#include "OgreSingleton.h"
#include "XavierEditor.h"

namespace Ogre
{
	typedef HashMap<String, XavierEditor*>	HashXavierEditor;

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

		/** ���ر༭��
		 *
		 * \param name 
		 * \return 
		 */
		virtual	bool					load(const String& name);

		/** ж�ر༭��
		 *
		 */
		virtual	void					unload();

	protected:
		HashXavierEditor				m_HashEditor;
	};
}
