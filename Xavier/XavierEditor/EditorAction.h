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
	* \Desc    : 编辑动作，用于redo和undo
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorAction
	{
	public:
		/** 行为名称
		 *
		 * \return 
		 */
		EditorAction(const String& name);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~EditorAction();

		/** 执行该动作
		 *
		 */
		virtual	void			execute();

		/** 获取动作名
		 *
		 * \return 
		 */
		virtual const String&	getName() const;
	protected:
		String					m_Name;
	};
}

#endif