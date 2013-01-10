#ifndef _____Og2dShape_H
#define _____Og2dShape_H

#include "Og2dVertex.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-28
	*
	* \Author  : lp
	*
	* \Desc    : ��״����װ����ƽ̨�¶��㴴����
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Shape
	{
	public:
		/** ���캯��
		 *
		 * \param nLength ������״����Ҫ�Ķ�����
		 * \return 
		 */
		Shape(int nLength);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~Shape();
		
		/** ��ȡ���㳤��
		 *
		 * \return 
		 */
		virtual	int			getLength() const;

		/** �����������
		 *
		 * \return 
		 */
		virtual	SVertex2D*	lock() = 0;

		/** �����豸����
		 *
		 * \param nStage 
		 * \param pTexture 
		 */
		virtual	void		setTexture(int nStage, Texture* pTexture) = 0;

		/** ����
		 *
		 */
		virtual	void		draw() = 0;

		/** �������
		 *
		 */
		virtual	void		unlock() = 0;
	protected:
		int					m_nLength;
	};
}

#endif