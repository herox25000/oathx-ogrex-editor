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
		//! ���캯��
		/**
		*
		* \param void 
		* \return 
		*/
		TSize(void)
			: w(0), h(0)
		{
		}
		
		//! ���캯��
		/**
		*
		* \param nw ���
		* \param nh �߶�
		* \return 
		*/
		TSize(T nw, T nh)
			: w(nw), h(nh)
		{

		}

		//! ��������
		/**
		*
		* \param void 
		* \return 
		*/
		~TSize(void)
		{
		}

		//! ��ֵ���캯��
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

		//! �������캯��
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

		//! ���� + 
		/**
		*
		* \return 
		*/
		TSize<T> operator + () const
		{
			return TSize<T>(w, h);
		}

		//! ���� -
		/**
		*
		* \return 
		*/
		TSize<T> operator - () const
		{
			return TSize<T>(-x, -y);
		}

		//! ���� +
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator + (const TSize<T>& rhs) const
		{
			return TSize<T>(w + rhs.w, h + rhs.h);
		}

		//! ���� -
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator - (const TSize<T>& rhs) const
		{
			return TSize<T>(w - rhs.w, h - rhs.h);
		}

		//! ���� *
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator * (const TSize<T>& rhs) const
		{
			return TSize<T>(w * rhs.w, h * rhs.h);
		}

		//! ���� /
		/**
		*
		* \param rhs 
		* \return 
		*/
		TSize<T> operator / (const TSize<T>& rhs) const
		{
			return TSize<T>(w / rhs.w, h / rhs.h);
		}

		//! ���� *
		/**
		*
		* \param size 
		* \return 
		*/
		TSize<T> operator * (const T size) const
		{
			return TSize<T>(w * size, h * size);
		}

		//! ���� /
		/**
		*
		* \param size 
		* \return 
		*/
		TSize<T> operator / (const T size) const
		{
			return TSize<T>(w / size, h / size);
		}

		//! ���� +=
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


		//! ���� -=
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


		//! ���� *=
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


		//! ���� /=
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

		//! ���� ==
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator == (const TSize<T>& rhs) const
		{
			return (w == rhs.w && h == rhs.h)
		}

		//! ����  !=
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

		//! ���óߴ�
		/**
		*
		* \param nw ��
		* \param nh ��
		*/
		_____inline
			void setDimension(T nw, T nh)
		{
			w = nw;
			h = nh;
		}

		//! ���óߴ�
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

		//! ��ȡ���
		/**
		*
		* \return �������
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