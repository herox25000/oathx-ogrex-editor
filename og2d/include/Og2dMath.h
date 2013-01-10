#ifndef _____Og2dMath_H
#define _____Og2dMath_H

#include "Og2dTypes.h"

namespace Og2d
{
#ifdef __cplusplus
	extern "C" { 
#endif

		//!
		/**
		*
		* \param x 
		* \return 
		*/
		_____inline
			Og2d_Export_API  float  ___invSqrt( const float x)
		{
			union
			{
				int		intPart;
				float	floatPart;
			}convertor;

			convertor.floatPart = x;
			convertor.intPart	= 0x5f3759df - (convertor.intPart >> 1);
			return convertor.floatPart*(1.5f - 0.4999f*x*convertor.floatPart*convertor.floatPart);
		}
	

		//! 设置DWORD
		/**
		*
		* \param pdword 
		* \param x 
		* \param y 
		*/
		_____inline
			Og2d_Export_API void setDWORD(ulong* pdword, int x, int y)
		{
			ushort* pwr = (ushort*)pdword;
			pwr[0] = x;
			pwr[1] = y;
		}
	

		//! 获取DWORD
		/**
		*
		* \param pdword 
		* \param x 
		* \param y 
		*/
		_____inline
			Og2d_Export_API void getDWORD(ulong* pdword, int* x, int* y)
		{
			ushort* pwr = (ushort*)pdword;
			*x = (int)pwr[0];
			*y = (int)pwr[1];
		}

		static unsigned int gnSeed = 0;

		//!
		/**
		*
		* \param Min 
		* \param Max 
		* \return 
		*/
		_____inline
			Og2d_Export_API float rdft(float Min, float Max)
		{
			if (gnSeed == 0)
			{
				gnSeed = ::GetTickCount();
			}

			gnSeed = 214013 * gnSeed + 2531011;

			return Min+(gnSeed >> 16) * (1.0f / 65535.0f) * (Max-Min);
		}
	
#ifdef __cplusplus
	}
#endif

	const float  PI32	= 3.1415926f;
	const float  PI32_2 = 1.57079632679489661923f;
	const double PI64	= 3.1415926535897932384626433832795028841971693993751;

	//! 浮点精度
	const float FLOATPRECISION = 0.000001f;

	//! 定义浮点数比较函数
	_____inline
		Og2d_Export_API bool equals(const float a, const float b)
	{
		return (a + FLOATPRECISION >= b) && ( a - FLOATPRECISION <= b);
	}

	/**
	 *
	 * \param x 
	 * \return 
	 */
	__forceinline float reciprocal_squareroot(const float x)
	{
#ifndef OG2D_FAST_MATH
#if 1
		unsigned int temp = (unsigned int(0x3f800000 << 1) + 0x3f800000 - *(unsigned int*)&x) >> 1;
		float y = *(float*)&temp;
		return y * (1.47f - 0.47f * x * y * y);
#elif defined(_MSC_VER)
		__asm
		{
			movss xmm0, x
			rsqrtss xmm0, xmm0
			movss x,xmm0
		}
#endif
#else
		return 1.0f / sqrtf(x);
#endif
	}
}

#include "Og2dTVector2D.h"
#include "Og2dTSize.h"
#include "Og2dTRect.h"
#include "Og2dTVector3D.h"
#include "Og2dColour.h"
#include "Og2dHash.h"

namespace Og2d
{
	typedef TVector2D<float>	Vector2D;
	typedef TVector3D<float>	Vector3D;
	typedef TRect<float>		Rect;
	typedef TSize<float>		Size;
}
#endif