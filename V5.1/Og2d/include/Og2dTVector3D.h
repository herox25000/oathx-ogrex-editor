#ifndef _____Og2dTVector3D_H
#define _____Og2dTVector3D_H

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
	* \Desc    : 3Œ¨œÚ¡ø
	*
	* \bug     : 
	*
	*/
	template<class T> class Og2d_Export_API TVector3D
	{
#ifdef __cplusplus
	public:
		//!
		/**
		*
		* \param void 
		* \return 
		*/
		TVector3D(void) : x(0), y(0)
		{

		}

		//!
		/**
		*
		* \param nx 
		* \param ny 
		* \param nz 
		* \return 
		*/
		TVector3D(T nx, T ny, T nz)
		{
			x = nx;
			y = ny;
			z = nz;
		}

	public:
		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D(const TVector3D<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T>& operator = (const TVector3D<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;

			return *this;
		}

		//!
		/**
		*
		* \return 
		*/
		TVector3D<T> operator + () const
		{
			return TVector3D<T>(x, y, z);
		}

		//!
		/**
		*
		* \return 
		*/
		TVector3D<T> operator - () const
		{
			return TVector3D<T>(-x, -y, -z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T> operator + (const TVector3D<T>& rhs) const
		{
			return TVector3D<T>(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T> operator - (const TVector3D<T>& rhs) const
		{
			return TVector3D<T>(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T> operator * (const TVector3D<T>& rhs) const
		{
			return TVector3D<T>(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T> operator / (const TVector3D<T>& rhs) const
		{
			return TVector3D<T>(x / rhs.x, y / rhs.y, z / rhs.z);
		}
	
		//!
		/**
		*
		* \param vec 
		* \return 
		*/
		TVector3D<T> operator * (const T vec) const
		{
			return TVector3D<T>(x * vec, y * vec, z * vec);
		}

		//!
		/**
		*
		* \param vec 
		* \return 
		*/
		TVector3D<T> operator / (const T vec) const
		{
			return TVector3D<T>(x / vec, y / vec, z / vec);
		}
	
		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T>& operator += (const TVector3D<T>& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;

			return *this;
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T>& operator -= (const TVector3D<T>& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;

			return *this;
		}


		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T>& operator *= (const TVector3D<T>& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;

			return *this;
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		TVector3D<T>& operator /= (const TVector3D<T>& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;

			return *this;
		}

	
		//!
		/**
		*
		* \param vec 
		* \return 
		*/
		TVector3D<T>& operator *= (const T vec)
		{
			x *= vec;
			y *= vec;
			z *= vec;

			return *this;
		}

		//!
		/**
		*
		* \param vec 
		* \return 
		*/
		TVector3D<T>& operator /= (const T vec)
		{
			x /= vec;
			y /= vec;
			z /= vec;

			return *this;
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator <= (const TVector3D<T>& rhs) const
		{
			return (x <= rhs.x && y <= rhs.y && z <= rhs.z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator >= (const TVector3D<T>& rhs) const
		{
			return (x >= rhs.x && y >= rhs.y && z >= rhs.z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator < (const TVector3D<T>& rhs)  const
		{
			return (x < rhs.x && y < rhs.y && z < rhs.z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator > (const TVector3D<T>& rhs)  const
		{
			return (x > rhs.x && y > rhs.y && z > rhs.z);
		}
	
		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator == (const TVector3D<T>& rhs) const
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z);
		}

		//!
		/**
		*
		* \param rhs 
		* \return 
		*/
		bool operator != (const TVector3D<T>& rhs) const
		{
			return (x != rhs.x || y != rhs.y || z != rhs.z);
		}
	

	public:
		_____inline 
			//!
			/**
			*
			* \param nx 
			* \param ny 
			* \param nz 
			*/
			void setVector3D(const T nx, const T ny, const T nz)
		{
			x = nx;
			y = ny;
			z = nz;
		}

		_____inline
			//!
			/**
			*
			* \param rhs 
			*/
			void setVector3D(const TVector3D<T>& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}

		_____inline
			//!
			/**
			*
			* \return 
			*/
			T getVector3DLength() const
		{
			return ((T)sqrt((double)(x*x + y*y + z*z)));
		}
#endif
	};

}

#endif