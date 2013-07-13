#ifndef _____Og2dTRect_H
#define _____Og2dTRect_H

#include "Og2dTVector2D.h"
#include "Og2dTSize.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-23
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	template<class T> class Og2d_Export_API TRect
	{
	public:
		union{
			struct{
				T left;
				T top;
				T right;
				T bottom;
			};

			T v[4];
		};
		
#ifdef __cplusplus
	public:
		//! 默认构造
		/**
		*
		* \param void 
		* \return 
		*/
		TRect(void)
			: left(0), top(0), right(0), bottom(0)
		{

		}

		//! 构造函数
		/**
		*
		* \param nLeft 
		* \param nTop 
		* \param nRight 
		* \param nBottom 
		* \return 
		*/
		TRect(T nLeft, T nTop, T nRight, T nBottom)
			: left(nLeft), top(nTop), right(nRight), bottom(nBottom)
		{

		}

		//! 构造函数
		/**
		*
		* \param leftTop 
		* \param rightBottom 
		* \return 
		*/
		TRect(TVector2D<T> up, TVector2D<T> rb)
			: left(up.x), top(up.y), right(rb.x), bottom(rb.y)
		{

		}

		//! 构造函数
		/**
		*
		* \param leftTop 
		* \param dim 
		* \return 
		*/
		TRect(TVector2D<T> up, TSize<T> dim)
			: left(up.x), top(up.y), right( up.x + dim.w ), bottom( up.y + dim.h )
		{

		}

	public:
		//! 拷贝构造函数
		/**
		*
		* \param rhs 
		* \return 
		*/
		TRect(const TRect<T>& rhs)
		{
			left    = rhs.left;
			top     = rhs.top;
			right   = rhs.right;
			bottom  = rhs.bottom;
		}

		//! 赋值构造函数
		/**
		*
		* \param rhs 
		* \return 
		*/
		TRect<T>& operator = (const TRect<T>& rhs)
		{
			left    = rhs.left;
			top     = rhs.top;
			right   = rhs.right;
			bottom  = rhs.bottom;

			return *this;
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TRect<T> operator + (const TVector2D<T>& rhs) const
		{
			return TRect<T>(left+rhs.x, top+rhs.y, right+rhs.x, bottom+rhs.y);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TRect<T> operator - (const TVector2D<T>& rhs) const
		{
			return TRect<T>(left-rhs.x, top-rhs.y, right-rhs.x, bottom-rhs.y);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TRect<T>& operator += (const TVector2D<T>& rhs)
		{
			left	+= rhs.x;
			top		+= rhs.y;
			right	+= rhs.x;
			bottom	+= rhs.y;

			return *this;
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TRect<T>& operator -= (const TVector2D<T>& rhs)
		{
			left   -= rhs.x;
			top    -= rhs.y;
			right  -= rhs.x;
			bottom -= rhs.y;

			return *this;
		}

		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		TRect<T>& operator += (const TSize<T>& rhs)
		{
			right	+= rhs.w;
			bottom	+= rhs.h;

			return *this;
		}


		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		TRect<T>& operator -= (const TSize<T>& rhs)
		{
			right	-= rhs.w;
			bottom	-= rhs.h;

			return *this;
		}

		//!
		/**
		*
		* \param vec2D 
		* \return 
		*/
		TRect<T> operator + (const TVector2D<T>& vec2D)
		{
			return TRect<T>(left+vec2D.x, top+vec2D.y, right+vec2D.x, bottom+vec2D.y);
		}

		//!
		/**
		*
		* \param vec2D 
		* \return 
		*/
		TRect<T> operator - (const TVector2D<T>& vec2D)
		{
			return TRect<T>(left-vec2D.x, top-vec2D.y, right-vec2D.x, bottom-vec2D.y);
		}

		//!
		/**
		*
		* \param vec2D 
		* \return 
		*/
		TRect<T> operator + (const TSize<T>& cSize)
		{
			return TRect<T>(left, top, right+cSize.w, bottom+cSize.h);
		}

		//!
		/**
		*
		* \param vec2D 
		* \return 
		*/
		TRect<T> operator - (const TSize<T>& cSize)
		{
			return TRect<T>(left, top, right-cSize.w, bottom-cSize.h);
		}

		//!
		/**
		*
		* \param scale 
		* \return 
		*/
		TRect<T> operator * (const T scale) const
		{
			return TRect<T>(left*scale, top*scale, right*scale, bottom*scale);
		}

		//!
		/**
		*
		* \param scale 
		* \return 
		*/
		TRect<T> operator / (const T scale) const
		{
			return TRect<T>(left/scale, top/scale, right/scale, bottom/scale);
		}

		//!
		/**
		*
		* \param scale 
		* \return 
		*/
		TRect<T>& operator *= (const T scale)
		{
			left   *= scale;
			top    *= scale;
			right  *= scale;
			bottom *= scale;

			return *this;
		}

		//!
		/**
		*
		* \param scale 
		* \return 
		*/
		TRect<T>& operator /= (const T scale)
		{
			left   /= scale;
			top    /= scale;
			right  /= scale;
			bottom /= scale;

			return *this;
		}

		//!
		/**
		*
		* \param rc 
		* \return 
		*/
		bool operator == (const TRect<T>& rc) const
		{
			return left==rc.left && top==rc.top && right==rc.right && bottom==bottom;
		}

		//!
		/**
		*
		* \param rc 
		* \return 
		*/
		bool operator != (const TRect<T>& rc) const
		{
			return left!=rc.left && top!=rc.top && right!=rc.right && bottom!=bottom;
		}
	public:
		/**
		 *
		 * \param idx 
		 * \return 
		 */
		T&	operator [] (int idx)
		{
			return v[idx];
		}

		/**
		 *
		 * \param idx 
		 * \return 
		 */
		const T& operator [] (int idx) const
		{
			return v[idx];
		}

	public:
		_____inline
			void setRect(T x, T y, T w, T h)
		{
			left = x; top = y; right = x+w; bottom = y+h;
		}

		_____inline
			void setOffset(T x, T y)
		{
			T w		= right - left; 
			T h		= bottom - top;

			left	= x;
			top		= y; 
			right	= x + w; 
			bottom	= y + h;
		}

		//!
		/**
		*
		* \return 
		*/
		_____inline
			T getWidth() const
		{
			return right - left;
		}

		//!
		/**
		*
		* \return 
		*/
		_____inline
			T getHeight() const
		{
			return bottom - top;
		}

		//!
		/**
		*
		* \return 
		*/
		_____inline
			T getRectArea() const
		{
			return getWidth()*getHeight();
		}
	public:
		//!
		/**
		*
		* \param pt 
		* \return 
		*/
		_____inline
			bool		ptInRect(const TVector2D<T>& pt) const
		{
			return (left <= pt.x && top <= pt.y && right >= pt.x && bottom >= pt.y);
		}

		//!
		/**
		*
		* \param rc 
		* \return 
		*/
		_____inline
			bool		isRectCollided(const TRect<T>& rc) const
		{
			return (bottom > rc.bottom && top < rc.bottom && right > rc.left && left < rc.right);
		}

		//!
		/**
		*
		* \param rc 
		* \return 
		*/
		_____inline
			void		clipAgainst(const TRect<T>& rc)
		{
			if (rc.right < right)
			{
				rc.right = rc.right;
			}

			if (rc.bottom < bottom)
			{
				rc.bottom = bottom;
			}

			if (rc.left > left)
			{
				left = rc.left;
			}

			if (rc.top > top)
			{
				top = rc.top;
			}

			if (top > bottom)
			{
				top = bottom;
			}

			if (left > right)
			{
				left = right;
			}
		}

		//!
		/**
		*
		* \param rc 
		* \return 
		*/
		_____inline
			bool			constrainTo(const TRect<T>& rc)
		{
			if (rc.getWidth() < getWidth() || rc.getHeight() < getHeight())
				return 0;

			T diff = rc.right - right;
			if (diff < 0)
			{
				right  += diff;
				left   += diff;
			}

			diff = left - rc.left;
			if (diff < 0)
			{
				left    -= diff;
				right   -= diff;
			}

			diff = top - rc.top;
			if (diff < 0)
			{
				top    -= diff;
				bottom -= diff;
			}

			return true;
		}

		//!
		/**
		*
		*/
		_____inline
			void			repair()
		{
			if (right < left)
			{
				T temp = right;
				right  = left;
				left   = temp;
			}

			if (bottom < top)
			{
				T temp = bottom;
				bottom = top;
				top    = temp;
			}
		}


		//!
		/**
		*
		* \return 
		*/
		_____inline
			bool			isValid() const
		{
			return (right >= left) && (bottom >= top);
		}

		//!
		/**
		*
		* \return 
		*/
		_____inline
			TVector2D<T>		getCenter() const
		{
			return TVector2D<T>((left + right)/2, (top + bottom)/2);
		}

		_____inline
			/**
			 *
			 * \return 
			 */
			TSize<T>			getSize() const
		{
			return TSize<T>(getWidth(), getHeight());
		}

		_____inline
			/**
			 *
			 * \param x 
			 * \param y 
			 */
			void			addInternalPoint(T x, T y)
		{
			if (x > right)
				right = x;

			if (y > bottom)
				bottom = y;

			if (x < left)
				left = x;

			if (y < top)
				top = y;
		}

		_____inline
			/**
			 *
			 * \param pt 
			 */
			void			addInternalPoint(const TVector2D<T>& pt)
		{
			addInternalPoint(pt.x, pt.y);
		}

		_____inline
			//!
			/**
			 *
			 * \return 
			 */
			bool			isEmpty() const
		{
			return (left == 0 && top == 0 && right == 0 && bottom == 0);
		}

		_____inline
			//!
			/**
			 *
			 * \return 
			 */
			TVector2D<T>		getUpper() const
		{
			return TVector2D<float>(left, top);
		}

		_____inline
			//!
			/**
			 *
			 * \return 
			 */
			TVector2D<T>		getLower() const
		{
			return TVector2D<T>(right, bottom);
		}

		_____inline
			//!
			/**
			 *
			 * \return 
			 */
			TSize<T>			getDimension() const
		{
			return TSize<T>(right-left, bottom-top);
		}
#endif
	};
}

#endif