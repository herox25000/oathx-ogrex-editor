#ifndef _____Og2dQuad_H
#define _____Og2dQuad_H

#include "Og2dRenderTarget.h"
#include "Og2dTexture.h"

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
	* \Desc    : �ı���
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Quad : public RenderTarget
	{
	public:
		/** ���캯��
		 *
		 * \param rect 
		 * \return 
		 */
		Quad(const String& szName, const Rect& rect);

		/** ��������
		 *
		 * \return 
		 */
		virtual	~Quad();
		
		/**
		 *
		 * \param fScale 
		 */
		virtual	void	setScale(float fScale);

		/** ���ö�����ɫ
		 *
		 * \param vclr 
		 */
		virtual	void	setColour(const SVertexClr4& vclr);
		
		/** �����������
		 *
		 * \param pTexture 
		 */
		virtual	void	setTexture(Texture* pTexture);

		/**
		 *
		 * \param rect 
		 */
		virtual	bool	setTextureRect(const Rect& rect);

		/**
		 *
		 * \return 
		 */
		virtual	Rect	getTextureRect() const;

		/**
		 *
		 * \param fElapsed 
		 */
		virtual	bool	draw(float fElapsed);
		
	protected:
		Shape*			m_pShape;
		Texture*		m_pTexture;
		SVertexClr4		m_colour;
		Rect			m_tRect;
		Rect			m_tUV;
	};
}

#endif