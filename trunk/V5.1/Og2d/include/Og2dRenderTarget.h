#ifndef _____Og2dRenderTarget_H
#define _____Og2dRenderTarget_H

#include "Og2dShape.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-29
	*
	* \Author  : lp
	*
	* \Desc    : ��ȾĿ��������п���Ⱦ������ࣩ
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API RenderTarget
	{
	public:
		/**
		 *
		 * \return 
		 */
		RenderTarget(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual ~RenderTarget();
		
		/**
		 *
		 * \param szName 
		 */
		virtual	void		setName(const String& szName);
		
		/**
		 *
		 * \return 
		 */
		virtual	String		getName() const;

		/** ��������
		 *
		 * \param fScale 
		 */
		virtual	void		setScale(float fScale);

		/** ��ȡ��ǰ����
		 *
		 * \return 
		 */
		virtual	float		getScale() const;

		/** �����Ƿ�ɼ�
		 *
		 * \param bValue 
		 */
		virtual	void		setVisible(bool bVisible);

		/** �����Ƿ�ɼ�
		 *
		 * \return 
		 */
		virtual	bool		isVisible() const;

		/**
		 *
		 * \param vPos 
		 */
		virtual	void		setPosition(const Vector2D& vPos);

		/**
		 *
		 * \return 
		 */
		virtual	Vector2D	getPosition() const;
		
		/**
		 *
		 * \param  
		 */
		virtual	void		setSize(const Size& cSize);

		/**
		 *
		 * \return 
		 */
		virtual	Size		getSize() const;

		/**
		 *
		 * \param rcArea 
		 */
		virtual	void		setArea(const Rect& rcArea);

		/**
		 *
		 * \return 
		 */
		virtual	Rect		getArea() const;

		/**
		 *
		 * \param fElapsed 
		 */
		virtual	bool		draw(float fElapsed) = 0;
	protected:
		float				m_fScale;
		String				m_szName;
		bool				m_bVisible;
		Rect				m_rcArea;
	};
}

#endif