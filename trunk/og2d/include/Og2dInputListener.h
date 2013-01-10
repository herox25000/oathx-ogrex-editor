#ifndef _____Og2dInputListener_H
#define _____Og2dInputListener_H

#include "Og2dKeyCode.h"
#include "Og2dTypes.h"

namespace Og2d
{
	//! 枚举输入类型
	typedef enum EIPUPTT_TYPE
	{
		EIPT_INVALD,

		//! 键盘输入
		EIPT_KEY,

		//! 鼠标输入
		EIPT_MOUSE,

		//! 用户输入
		EIPT_USER,
	}IptType;

	//! 枚举鼠标输入事件
	typedef enum EMOUSE_EVENT
	{
		//! 鼠标左键按下
		MS_LBTNDOWN,

		//! 鼠标坐键弹起
		MS_LBTNUP,

		//! 鼠标中键按下
		MS_MBTNDOWN,

		//! 鼠标中键弹起
		MS_MBTNUP,

		//! 鼠标右键按下
		MS_RBTNDOWN,

		//! 鼠标右键弹起
		MS_RBTNUP,

		//! 鼠标移动
		MS_MOVE,

		//! 鼠标滚轮移动
		MS_WHEEL,
	}MseEvt;

	//! 键盘输入事件
	typedef enum EKEY_EVENT
	{
		KEYEVT_DOWN,
		KEYEVT_UP,
	}KeyEvt;

	//! 输入事件定义
	typedef struct SInputEvent
	{
		//! 鼠标输入
		struct Mouse
		{
			EMOUSE_EVENT	evt;

			float			x;
			float			y;
			float			z;
		};

		//! 键盘输入
		struct Keyboard
		{
			KeyCode			code;		//! 输入代码
			wchar_t			wchar;		//! 输入字符
			bool			shift;		//! 是否按下shift
			bool			control;	//! 是否按下control

			EKEY_EVENT		evt;		//! 键盘输入事件
		};

		//! 输入数据联合体
		union{
			Keyboard		keyboard;
			Mouse			mouse;
		};

		//! 输入类型
		EIPUPTT_TYPE		iType;
	}SEVENTARGS,*PSEVENTARGS;

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
	* \Desc    : 输入监听器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API InputListener
	{
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		InputListener();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~InputListener();

		/** 事件处理
		 *
		 * \param args 
		 * \return 
		 */
		virtual	bool			OnEvent(const SInputEvent& iEvt) = 0;
	};
}

#endif