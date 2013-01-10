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
	* \Desc    : 形状（封装各种平台下顶点创建）
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Shape
	{
	public:
		/** 构造函数
		 *
		 * \param nLength 构成形状的需要的顶点数
		 * \return 
		 */
		Shape(ulong nLength);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~Shape();
		
		/** 获取顶点长度
		 *
		 * \return 
		 */
		virtual	ulong		getLength() const;

		/** 锁定顶点类存
		 *
		 * \return 
		 */
		virtual	SVertex2D*	lock() = 0;

		/** 设置设备文理
		 *
		 * \param nStage 
		 * \param pTexture 
		 */
		virtual	void		setTexture(int nStage, Texture* pTexture) = 0;

		/** 绘制
		 *
		 */
		virtual	void		draw() = 0;

		/** 解除锁定
		 *
		 */
		virtual	void		unlock() = 0;
	protected:
		ulong				m_nLength;
	};
}

#endif