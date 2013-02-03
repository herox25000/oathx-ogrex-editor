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
	* \Desc    : �༭����������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorActionManager : public Singleton<EditorActionManager>
	{
		// ��������
		typedef deque<EditorAction*>::type	DequeAction;
	public:
		/** ��ȡ��������
		 *
		 * \return 
		 */
		static	EditorActionManager&	getSingleton();

		/** ��ȡ����ָ��
		 *
		 * \return 
		 */
		static	EditorActionManager*	getSingletonPtr();

	public:
		/** ���캯��
		 *
		 * \return 
		 */
		EditorActionManager();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~EditorActionManager();

		/** ���һ����������
		 *
		 * \param pRedo 
		 * \return 
		 */
		virtual	void					addRedo(EditorAction* pAction);
	
		/** ���һ�����ض���
		 *
		 * \param pAction 
		 * \return 
		 */
		virtual	void					addUndo(EditorAction* pAction);

		/** ����
		 *
		 * \return 
		 */
		virtual	bool					undo();

		/** ����
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