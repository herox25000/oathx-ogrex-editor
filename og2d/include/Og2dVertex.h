#ifndef _____Og2dVertex_H
#define _____Og2dVertex_H

#include "Og2dTypes.h"
#include "Og2dMath.h"

namespace Og2d
{
	//@ 定义顶点结构
	typedef struct SVertex2D
	{
		float x,y,z;
		Colour color;
		float u,v;

		//! 默认构造
		/**
		*
		* \param void 
		* \return 
		*/
		SVertex2D(void)
			:x(0),y(0),z(1.0f),color(clrWHITE),u(0),v(0)
		{

		}

		//! 构造函数
		/**
		*
		* \param x 
		* \param y 
		* \param z 
		* \param color 
		* \param u 
		* \param v 
		* \return 
		*/
		SVertex2D(float x, float y, float z, const Colour color, float u, float v)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->color = color;
			this->u = u;
			this->v = v;
		}

		//! 拷贝
		/**
		*
		* \param ver2D 
		* \return 
		*/
		SVertex2D(const SVertex2D& ver2D)
		{
			x = ver2D.x;
			y = ver2D.y;
			z = ver2D.z;
			color = ver2D.color;
			u = ver2D.u;
			v = ver2D.v;
		}

		//! 赋值
		/**
		*
		* \param ver2D 
		* \return 
		*/
		SVertex2D& operator = (const SVertex2D& ver2D)
		{
			x = ver2D.x;
			y = ver2D.y;
			z = ver2D.z;
			color = ver2D.color;
			u = ver2D.u;
			v = ver2D.v;

			return *this;
		}

		//! 重载 ==
		/**
		*
		* \param ver2D 
		* \return 
		*/
		bool operator == (const SVertex2D& ver2D)
		{
			return (x==ver2D.x && y==ver2D.y && z==ver2D.z &&
				color==ver2D.color &&
				u==ver2D.u &&
				v==ver2D.v);
		}

		//! 重载 !=
		/**
		*
		* \param ver2D 
		* \return 
		*/
		bool operator != (const SVertex2D& ver2D)
		{
			return (x!=ver2D.x || y!=ver2D.y || z!=ver2D.z ||
				color!=ver2D.color ||
				u!=ver2D.u ||
				v!=ver2D.v);
		}
	}*LPSVERTEX2D;

	//! 计算顶点结构大小
#ifndef SVERTEX2DSIZE
#define SVERTEX2DSIZE sizeof(SVertex2D)
#endif
	
	//! 定义顶点颜色结构
	typedef struct SVertexClr4
	{
		Colour colour[4];

		/**
		 *
		 * \return 
		 */
		SVertexClr4()
		{
			colour[0] = clrWHITE;
			colour[1] = clrWHITE;
			colour[2] = clrWHITE;
			colour[3] = clrWHITE;
		}

		/**
		 *
		 * \param c0 
		 * \param c1 
		 * \param c2 
		 * \param c3 
		 * \return 
		 */
		SVertexClr4(const Colour c0, const Colour c1, const Colour c2, const Colour c3)
		{
			colour[0] = c0;
			colour[1] = c1;
			colour[2] = c2;
			colour[3] = c3;
		}

		/**
		 *
		 * \param c4 
		 * \return 
		 */
		SVertexClr4& operator = (const SVertexClr4& c4)
		{
			colour[0] = c4.colour[0];
			colour[1] = c4.colour[1];
			colour[2] = c4.colour[2];
			colour[3] = c4.colour[3];

			return *this;
		}

		/**
		 *
		 * \param idx 
		 * \return 
		 */
		Colour&	operator [] (int idx)
		{
			return colour[idx];
		}

		/**
		 *
		 * \param idx 
		 * \return 
		 */
		const Colour& operator [] (int idx) const
		{
			return colour[idx];
		}
	}*LPSVERTEXCLR;
#define SVERTEXCLRSIZE sizeof(SVertexClr4)

	//! 四顶点
	typedef struct SQuad
	{
		SVertex2D		vQuad[4];
		DWORD			blend;
		Texture*		pTexture;

		SQuad()
			:pTexture(NULL),blend(0)
		{
		}

		/** 设置所有顶点的颜色alpha值
		 *
		 * \param alpha 
		 */
		void			setAlpha(const short alpha);

		/** 设置顶点颜色
		 *
		 * \param nIdx 指定顶点索引，若为-1则设置全部4个顶点
		 * \param clr  指定颜色
		 */
		void			setVertexColor(int nIdx, const Colour clr);

		/** 设置纹理，原有纹理引用将被解除
		 *
		 * \param pNewTexture 
		 */
		void			setTexture(Texture* pNewTexture);

		/** 设置混合模式
		 *
		 * \param dwMode 
		 */
		void			setBlend(DWORD dwMode);

	}*PSQUAD;
#define SQUADSIZE sizeof(SQuad)
	
	//! 三顶点
	typedef struct STriangle
	{
		SVertex2D		vTran[3];
		DWORD			blend;
		Texture*		pTexture;

		STriangle()
			:pTexture(NULL),blend(0)
		{
		}
	}*PSTRIANGLE;
#define STRIANGLESIZE sizeof(STriangle)
}

#endif