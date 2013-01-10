#ifndef _____Og2dInputManager_H
#define _____Og2dInputManager_H

#include "Og2dSingleton.h"
#include "Og2dInputListener.h"

namespace Og2d
{
	// ���������
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
	* \Desc    : ���������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API InputManager : public Singleton<InputManager>
	{
	public:
		/** ��ȡ����ָ��
		 *
		 * \return 
		 */
		static	InputManager*	getSingletonPtr();

		/** ��ȡ������Ϣ
		 *
		 * \return 
		 */
		static	InputManager&	getSingleton();

	public:
		/** ���캯��
		 *
		 * \return 
		 */
		InputManager();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~InputManager();

		/** ��Ӽ�����
		 *
		 * \param pListener 
		 */
		virtual	void			addInputListener(InputListener* pListener);

		/** �Ƴ�������
		 *
		 * \param pListener 
		 */
		virtual	void			removeInputListener(
			InputListener* pListener);

		/** ע�������¼�
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