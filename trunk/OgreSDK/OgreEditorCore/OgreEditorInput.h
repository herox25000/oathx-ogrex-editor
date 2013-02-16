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
	* \Desc    : 编辑器输入接口
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorInput : public PropertySet
	{
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		EditorInput();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~EditorInput();

	public:
		/** 当编辑器主窗口大小发生改变时调用
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool					OnSize(int cx, int cy);

		/** 鼠标滚轮改变时调用
		 *
		 * \param fzDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseWheel(float fzDelta, const Vector2& vPos);

		/** 鼠标左键按下
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonDown(const Vector2& vPos);

		/** 鼠标左键弹起
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonUp(const Vector2& vPos);

		/** 鼠标右键按下
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonDown(const Vector2& vPos);

		/** 鼠标左键弹起
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonUp(const Vector2& vPos);

		/** 鼠标移动
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseMove(const Vector2& vPos);

		/** 键盘按键按下
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** 键盘按键弹起
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** 编辑属性改变
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