#ifndef _____Og2dInputManager_H
#define _____Og2dInputManager_H

#include "Og2dSingleton.h"
#include "Og2dInputListener.h"

namespace Og2d
{
	// 输入监听表
	typedef vector<InputListener*>::type VectorInputListener;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-11
	*
	* \Author  : lp
	*
	* \Desc    : 输入管理器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API InputManager : public Singleton<InputManager>
	{
	public:
		/** 获取单件指针
		 *
		 * \return 
		 */
		static	InputManager*	getSingletonPtr();

		/** 获取单件信息
		 *
		 * \return 
		 */
		static	InputManager&	getSingleton();

	public:
		/** 构造函数
		 *
		 * \return 
		 */
		InputManager();

		/** 析构函数
		 *
		 * \return 
		 */
		~InputManager();

		/** 添加监听器
		 *
		 * \param pListener 
		 */
		virtual	void			addInputListener(InputListener* pListener);

		/** 移除监听器
		 *
		 * \param pListener 
		 */
		virtual	void			removeInputListener(
			InputListener* pListener);

		/** 注入输入事件
		 *
		 * \param evt 
		 * \return 
		 */
		virtual	bool			injectEvent(const SInputEvent& evt);
	protected:
		VectorInputListener		m_vInput;
	};
}

#endif