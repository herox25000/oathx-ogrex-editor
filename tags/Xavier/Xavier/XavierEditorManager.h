#pragma once

#include "OgreSingleton.h"

namespace Ogre
{
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

		/** ¼ÓÔØ±à¼­Æ÷
		 *
		 * \param name 
		 * \return 
		 */
		virtual	bool					load(const String& name);

		/** Ð¶ÔØ±à¼­Æ÷
		 *
		 */
		virtual	void					unload();
	};
}
