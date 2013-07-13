#ifndef _____Og2dTVector2D_H
#define _____Og2dTVector2D_H

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	template<class T> class Og2d_Export_API TVector2D
	{
#ifdef __cplusplus
	public:
		//! 默认构造函数
		/**
		*
		* \param void 
		* \return 
		*/
		TVector2D(void)
			: x(0), y(0)
		{

		}

		//! 构造函数
		/**
		*
		* \param x 指定X
		* \param y 指定Y
		* \return 
		*/
		TVector2D(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
	public:
		//! 构造函数
		/**
		* ！！使用常数构造
		* \param n 
		* \return 
		*/
		TVector2D(T n)
			:TVector2D<T>(n,n)
		{

		}
	public:
		//!拷贝构造函数
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D(const TVector2D<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}

		//! 赋值构造函数
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T>& operator = (const TVector2D<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;

			return *this;
		}

	public:
		//! 重载 + 
		/**
		*
		* \return 
		*/
		TVector2D<T> operator + () const
		{
			return TVector2D<T>(x, y);
		}

		//! 重载 -
		/**
		*
		* \return 
		*/
		TVector2D<T> operator - () const
		{
			return TVector2D<T>(-x, -y);
		}

	public:
		//! 重载 + 
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T> operator + (const TVector2D<T>& rhs) const
		{
			return TVector2D<T>(x + rhs.x, y + rhs.y);
		}

		//! 重载 -
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T> operator - (const TVector2D<T>& rhs) const
		{
			return TVector2D<T>(x - rhs.x, y - rhs.y);
		}

		//! 重载 *
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T> operator * (const TVector2D<T>& rhs) const
		{
			return TVector2D<T>(x * rhs.x, y * rhs.y);
		}

		//! 重载 /
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T> operator / (const TVector2D<T>& rhs) const
		{
			return TVector2D<T>(x / rhs.x, y / rhs.y);
		}

	public:
		//! 重载 + 
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T> operator + (const T val) const
		{
			return TVector2D<T>(x + val, y + val);
		}

		//! 重载 -
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T> operator - (const T val) const
		{
			return TVector2D<T>(x - val, y - val);
		}

		//! 重载 *
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T> operator * (const T val) const
		{
			return TVector2D<T>(x * val, y * val);
		}

		//! 重载 /
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T> operator / (const T val) const
		{
			return TVector2D<T>(x / val, y / val);
		}

	public:
		//! 重载 +=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T>& operator += (const TVector2D<T>& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		//! 重载 -=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T>& operator -= (const TVector2D<T>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		//! 重载 *=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T>& operator *= (const TVector2D<T>& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;

			return *this;
		}

		//! 重载 /=
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T>& operator /= (const TVector2D<T>& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;

			return *this;
		}

	public:
		//! 重载 +=
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T>& operator += (const T val)
		{
			x += val;
			y += val;

			return *this;
		}

		//! 重载 -=
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T>& operator -= (const T val)
		{
			x -= val;
			y -= val;

			return *this;
		}

		//! 重载 *=
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T>& operator *= (const T val)
		{
			x *= val;
			y *= val;

			return *this;
		}

		//! 重载 /=
		/**
		*
		* \param val 
		* \return 
		*/
		TVector2D<T>& operator /= (const T val)
		{
			return *this;
		}

	public:
		//! 重载 >
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator > (const TVector2D<T>& rhs) const
		{
			return x > rhs.x && y > rhs.y;
		}

		//! 重载 <
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator < (const TVector2D<T>& rhs) const
		{
			return x < rhs.x && y < rhs.y;
		}

	public:
		//! 重载 >=
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator >= (const TVector2D<T>& rhs) const
		{
			return x >= rhs.x && y >= rhs.y;
		}

		//! 重载 <=
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator <= (const TVector2D<T>& rhs) const
		{
			return x <= rhs.x && y <= rhs.y;
		}

	public:
		//! 重载 ==
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator == (const TVector2D<T>& rhs) const
		{
			return equals(rhs);
		}

		//! 重载 !=
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator != (const TVector2D<T>& rhs) const
		{
			return !equals(rhs);
		}

	public:
		//! 比较两向量
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool equals(const TVector2D<T>& rhs) const
		{
			return equals(x, rhs.x) && equals(y, rhs.y);
		}

	public:
		//! 设置向量
		/**
		*
		* \param nx 指定X
		* \param ny 指定Y
		* \return 
		*/
		TVector2D<T>& setVector2D(T nx, T ny)
		{
			x = nx;
			y = ny;

			return *this;
		}

		//! 设置向量
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector2D<T>& setVector2D(const TVector2D<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;

			return *this;
		}

	public:
		/**
		 *
		 * \return 
		 */
		T getVector2DLength() const
		{
			return (T)sqrt(float(x*x + y*y));
		}

		/**
		 *
		 * \return 
		 */
		T getVector2DLengthSquared() const
		{
			return x*x + y*y;
		}

		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		T getVector2DDot(const TVector2D<T>& rhs) const
		{
			return x*rhs.x + y*rhs.y;
		}

		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		T getDistanceForm(const TVector2D<T>& rhs) const
		{
			return TVector2D<T>(x - rhs.x, y - rhs.y).getVector2DLength();
		}

		/**
		 *
		 * \param rhs 
		 * \return 
		 */
		T getDistanceFormSquared(const TVector2D<T>& rhs) const
		{
			return TVector2D<T>(x - rhs.x, y - rhs.y).getVector2DLengthSquared();
		}

	public:
		/**
		 *
		 * \param degrees 
		 * \param center 
		 * \return 
		 */
		TVector2D<T>& rotate(float degrees, const TVector2D<T>& center=TVector2D<T>())
		{
			degrees *= PI32/180.0f;

			const float cs = cosf(degrees);
			const float sn = sinf(degrees);

			x -= center.x;
			y -= center.y;

			setVector2D((T)(x*cs - y*sn), (T)(x*sn + y*cs));

			x += center.x;
			y += center.y;

			return *this;
		}

		/**
		 *
		 * \return 
		 */
		TVector2D<T>& normalize()
		{
			float length = (float)(x*x + y*y);
			
			if (equals(length, 0.0f))
				return *this;

			length = core::reciprocal_squareroot(length);
			x = (T)(x*length);
			y = (T)(y*length);
			
			return *this;
		}

		/**
		 *
		 * \return 
		 */
		float getAngleTrig() const
		{
			if (x == 0)
			{
				return y < 0 ? 270 : 90;
			}
			else
			{
				if (y == 0)
					return x < 0 ? 180 : 0;
			}

			if ( y > 0)
			{
				if (x > 0)
					return atanf(y/x) * (180.0f/PI32);
				else
					return 180.0-atanf(y/-x) * (180.0f/PI32);
			}
			else
			{
				if (x > 0)
					return 360.0-atanf(-y/x) * (180.0f/PI32);
				else
					return 180.0-atanf(-y/-x) * (180.0f/PI32);
			}
		}


		_____inline
			/**
			 *
			 * \return 
			 */
			float getAngle() const
		{
			if (y == 0)
				return x < 0 ? 180.0f : 0.0f;
			else if (x == 0)
				return y < 0 ? 90.0f : 270.0f;

			float temp = y / getVector2DLength();
			temp = atanf(sqrt(1-temp*temp) / temp) * (180.0f/PI32);

			if (x > 0 && y > 0)
				return temp + 270.0f;
			else
			{
				if (x < 0 && y < 0)
					return 90 - temp;
				else
					if (x < 0 && y > 0)
						return 270.0f -temp;
			}

			return temp;
		}


		_____inline
			/**
			 *
			 * \param b 
			 * \return 
			 */
			float getAngleWith(const TVector2D<T>& b) const
		{
			float temp = x * b.x + y * b.y;

			if (temp == 0.0f)
				return 90.0f;

			temp = temp / sqrt((float)((x*x + y*y) * (b.x*b.x + b.y*b.y)));
			if (temp < 0.0f)
				temp = -temp;

			return atanf(sqrt(1-temp*temp) / temp) * (180.0f/PI32);
		}

		_____inline
			/**
			 *
			 * \param begin 
			 * \param end 
			 * \return 
			 */
			bool isBetPoint(const TVector2D<T>& begin, const TVector2D<T>& end) const
		{
			if (begin.x != end.y)
			{
				return ((begin.x <= x && x <= end.y) || (begin.x >= x && x >= end.x));
			}
			else
			{	
				return ((begin.y <= y && y <= end.y) || (begin.y >= y && y >= end.y));
			}
		}


		_____inline
			/**
			 *
			 * \param rhs 
			 * \param d 
			 * \return 
			 */
			TVector2D<T> getInterpolated(const TVector2D<T>& rhs, float d) const
		{
			float inv = 1.0f - d;
			return TVector2D<T>((T)(rhs.x*inv + x*d), (T)(rhs.y*inv + y*d));
		}

		_____inline
			/**
			 *
			 * \param a 
			 * \param b 
			 * \param d 
			 * \return 
			 */
			TVector2D<T>& interpolate(const TVector2D<T>& a, const TVector2D<T>& b, float d)
		{
			x = (T)((float)b.x + ((a.x - b.x) * d));
			y = (T)((float)b.y + ((a.y - b.y) * d));

			return *this;
		}

	public:
		T	x;
		T	y;
#endif
	};
}

#endif