#ifndef _____EditorActionManager_H
#define _____EditorActionManager_H

#include "EditorAction.h"

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
	* \Desc    : 编辑动作管理器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorActionManager : public Singleton<EditorActionManager>
	{
		// 动作队列
		typedef deque<EditorAction*>::type	DequeAction;
	public:
		/** 获取单件对象
		 *
		 * \return 
		 */
		static	EditorActionManager&	getSingleton();

		/** 获取单件指针
		 *
		 * \return 
		 */
		static	EditorActionManager*	getSingletonPtr();

	public:
		/** 构造函数
		 *
		 * \return 
		 */
		EditorActionManager();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~EditorActionManager();

		/** 添加一个重做对象
		 *
		 * \param pRedo 
		 * \return 
		 */
		virtual	void					addRedo(EditorAction* pAction);
	
		/** 添加一个返回对象
		 *
		 * \param pAction 
		 * \return 
		 */
		virtual	void					addUndo(EditorAction* pAction);

		/** 重做
		 *
		 * \return 
		 */
		virtual	bool					undo();

		/** 重做
		 *
		 * \return 
		 */
		virtual	bool					redo();

		/**
		 *
		 * \return 
		 */
		virtual	int						getRedoCount() const;

		/**
		 *
		 * \return 
		 */
		virtual	int						getUndoCount() const;
	protected:
		DequeAction						m_DequeRedo;
		DequeAction						m_DequeUndo;
	};
}

#endif