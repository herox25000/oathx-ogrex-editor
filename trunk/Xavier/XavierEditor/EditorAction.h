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
	* \Desc    : �༭����������redo��undo
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorAction
	{
	public:
		/** ��Ϊ����
		 *
		 * \return 
		 */
		EditorAction(const String& name);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~EditorAction();

		/** ִ�иö���
		 *
		 */
		virtual	void			execute();

		/** ��ȡ������
		 *
		 * \return 
		 */
		virtual const String&	getName() const;
	protected:
		String					m_Name;
	};
}

#endif