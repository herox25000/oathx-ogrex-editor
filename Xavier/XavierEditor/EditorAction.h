#ifndef _____EditorAction_H
#define _____EditorAction_H

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-02
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorAction
	{
	public:
		/**
		 *
		 * \return 
		 */
		EditorAction();

		/**
		 *
		 * \return 
		 */
		virtual ~EditorAction();

		/**
		 *
		 */
		virtual	void		execute();
	};
}

#endif