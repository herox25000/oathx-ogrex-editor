#ifndef _____OgreWorldEditor_H
#define _____OgreWorldEditor_H

#include "OgreEditor.h"

namespace Ogre
{
	struct SWorldAdp : public SEditorAdp
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
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBoxEdit_Export_API WorldEditor : public Editor
	{
	public:
		/**
		 *
		 * \param szName 
		 * \return 
		 */
		WorldEditor(const String& szName);
		/**
		 *
		 * \return 
		 */
		virtual ~WorldEditor();
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
	class Ogre_SandBoxEdit_Export_API WorldEditorFactory : public EditorFactory
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		WorldEditorFactory(const String& typeName);

		/**
		 *
		 * \return 
		 */
		virtual ~WorldEditorFactory();

		/**
		 *
		 * \param ssadp 
		 * \return 
		 */
		virtual	Editor*			create(const String& szName, const SEditorAdp& seadp, Editor* pParent);
	};
}

#endif