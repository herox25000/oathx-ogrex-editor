#ifndef _____OgreEditorInput_H
#define _____OgreEditorInput_H

#include "OgrePropertySet.h"

namespace Ogre
{
	/**
	* \ingroup : OgreEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-14
	*
	* \Author  : lp
	*
	* \Desc    : �༭������ӿ�
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorInput : public PropertySet
	{
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		EditorInput();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~EditorInput();

	public:
		/** ���༭�������ڴ�С�����ı�ʱ����
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool					OnSize(int cx, int cy);

		/** �����ָı�ʱ����
		 *
		 * \param fzDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseWheel(float fzDelta, const Vector2& vPos);

		/** ����������
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonDown(const Vector2& vPos);

		/** ����������
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonUp(const Vector2& vPos);

		/** ����Ҽ�����
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonDown(const Vector2& vPos);

		/** ����������
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonUp(const Vector2& vPos);

		/** ����ƶ�
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseMove(const Vector2& vPos);

		/** ���̰�������
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** ���̰�������
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** �༭���Ըı�
		 *
		 * \param parentName 
		 * \param name 
		 * \param anyValue 
		 * \param nType 
		 * \return 
		 */
		virtual	bool					OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);
	};
}

#endif