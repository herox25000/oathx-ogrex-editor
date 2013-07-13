#ifndef _____Og2dSize_H
#define _____Og2dSize_H

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
	template<class T> class Og2d_Export_API TSize
	{
#ifdef __cplusplus
	public:
		//! 构造函数
		/**
		*
		* \param void 
		* \return 
		*/
		TSize(void)
			: w(0), h(0)
		{
		}
		
		//! 构造函数
		/**
		*
		* \param nw 宽度
		* \param nh 高度
		* \return 
		*/
		TSize(T nw, T nh)
			: w(nw), h(nh)
		{

		}

		//! 析构函数
		/**
		*
		* \param void 
		* \return 
		*/
		~TSize(void)
		{
		}

		//! 赋值构造函数
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize(const TSize<T>& rhs)
		{
			w = rhs.w;
			h = rhs.h;
		}

		//! 拷贝构造函数
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T>& operator = (const TSize<T>& rhs)
		{
			w = rhs.w;
			h = rhs.h;

			return *this;
		}

		//! 重载 + 
		/**
		*
		* \return 
		*/
		TSize<T> operator + () const
		{
			return TSize<T>(w, h);
		}

		//! 重载 -
		/**
		*
		* \return 
		*/
		TSize<T> operator - () const
		{
			return TSize<T>(-x, -y);
		}

		//! 重载 +
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator + (const TSize<T>& rhs) const
		{
			return TSize<T>(w + rhs.w, h + rhs.h);
		}

		//! 重载 -
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator - (const TSize<T>& rhs) const
		{
			return TSize<T>(w - rhs.w, h - rhs.h);
		}

		//! 重载 *
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator * (const TSize<T>& rhs) const
		{
			return TSize<T>(w * rhs.w, h * rhs.h);
		}

		//! 重载 /
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator / (const TSize<T>& rhs) const
		{
			return TSize<T>(w / rhs.w, h / rhs.h);
		}

		//! 重载 *
		/**
		*
		* \param size 
		* \return 
		*/
		TSize<T> operator * (const T size) const
		{
			return TSize<T>(w * size, h * size);
		}

		//! 重载 /
		/**
		*
		* \param size 
		* \return 
		*/
		TSize<T> operator / (const T size) const
		{
			return TSize<T>(w / size, h / size);
		}

		//! 重载 +=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T>& operator += (const TSize<T>& rhs)
		{
			w += rhs.w;
			h += rhs.h;

			return *this;
		}


		//! 重载 -=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T>& operator -= (const TSize<T>& rhs)
		{
			w -= rhs.w;
			h -= rhs.h;

			return *this;
		}


		//! 重载 *=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T>& operator *= (const TSize<T>& rhs)
		{
			w *= rhs.w;
			h *= rhs.h;

			return *this;
		}


		//! 重载 /=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T>& operator /= (const TSize<T>& rhs)
		{
			w /= rhs.w;
			h /= rhs.h;

			return *this;
		}

		//! 重载 ==
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator == (const TSize<T>& rhs) const
		{
			return (w == rhs.w && h == rhs.h)
		}

		//! 重载  !=
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator != (const TSize<T>& rhs) const
		{
			return (w != rhs.w || h != rhs.h);
		}
	
		//!
		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		bool operator > (const TSize<T>& rhs) const
		{
			return (w > rhs.w && h > rhs.h);
		}

		//!
		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		bool operator < (const TSize<T>& rhs) const
		{
			return (w < rhs.w && h < rhs.h);
		}

		//!
		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		bool operator >= (const TSize<T>& rhs) const
		{
			return (w >= rhs.w && h >= rhs.h);
		}

		//!
		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		bool operator <= (const TSize<T>& rhs) const
		{
			return (w <= rhs.w && h <=rhs.h);
		}

		//! 设置尺寸
		/**
		*
		* \param nw 宽
		* \param nh 高
		*/
		_____inline
			void setDimension(T nw, T nh)
		{
			w = nw;
			h = nh;
		}

		//! 设置尺寸
		/**
		*
		* \param rhs 
		*/
		_____inline
			void setDimension(const TSize<T>& rhs)
		{
			w = rhs.w;
			h = rhs.h;
		}

		//! 获取面积
		/**
		*
		* \return 返回面积
		*/
		_____inline
			T getArea()const
		{
			return w*h;
		}

		_____inline
			/**
			 *
			 * \param val 
			 */
			void setDimension(T val)
		{
			w = h = val;
		}

	public:
		T w;
		T h;
#endif
	};
}

#endif