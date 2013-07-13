#ifndef _____Og2dInputListener_H
#define _____Og2dInputListener_H

#include "Og2dKeyCode.h"
#include "Og2dTypes.h"

namespace Og2d
{
	//! ö����������
	typedef enum EIPUPTT_TYPE
	{
		EIPT_INVALD,

		//! ��������
		EIPT_KEY,

		//! �������
		EIPT_MOUSE,

		//! �û�����
		EIPT_USER,
	}IptType;

	//! ö����������¼�
	typedef enum EMOUSE_EVENT
	{
		//! ����������
		MS_LBTNDOWN,

		//! �����������
		MS_LBTNUP,

		//! ����м�����
		MS_MBTNDOWN,

		//! ����м�����
		MS_MBTNUP,

		//! ����Ҽ�����
		MS_RBTNDOWN,

		//! ����Ҽ�����
		MS_RBTNUP,

		//! ����ƶ�
		MS_MOVE,

		//! �������ƶ�
		MS_WHEEL,
	}MseEvt;

	//! ���������¼�
	typedef enum EKEY_EVENT
	{
		KEYEVT_DOWN,
		KEYEVT_UP,
	}KeyEvt;

	//! �����¼�����
	typedef struct SInputEvent
	{
		//! �������
		struct Mouse
		{
			EMOUSE_EVENT	evt;

			float			x;
			float			y;
			float			z;
		};

		//! ��������
		struct Keyboard
		{
			KeyCode			code;		//! �������
			wchar_t			wchar;		//! �����ַ�
			bool			shift;		//! �Ƿ���shift
			bool			control;	//! �Ƿ���control

			EKEY_EVENT		evt;		//! ���������¼�
		};

		//! ��������������
		union{
			Keyboard		keyboard;
			Mouse			mouse;
		};

		//! ��������
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
	* \Desc    : ���������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API InputListener
	{
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		InputListener();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~InputListener();

		/** �¼�����
		 *
		 * \param args 
		 * \return 
		 */
		virtual	bool			OnEvent(const SInputEvent& iEvt) = 0;
	};
}

#endif