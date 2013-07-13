#ifndef _____Og2dSingleton_H
#define _____Og2dSingleton_H

#include "Og2dTypes.h"

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
	* \Desc    : 单件模板
	*
	* \bug     : 
	*
	*/
	template <typename T> class Og2d_Export_API Singleton
	{
	private:
		/**
		 *
		 * \param & 
		 * \return 
		 */
		Singleton(const Singleton<T> &);

		/**
		 *
		 * \param & 
		 * \return 
		 */
		Singleton& operator=(const Singleton<T> &);

	protected:
		// 单件实列
		static T* mpSingleton;

	public:
		/** 构造函数
		 *
		 * \param void 
		 * \return 
		 */
		Singleton( void )
		{
			assert( !mpSingleton );
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
			int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
			mpSingleton = (T*)((int)this + offset);
#else
			mpSingleton = static_cast< T* >( this );
#endif
		}
		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		~Singleton( void )
		{  
			assert( mpSingleton );  mpSingleton = 0; 
		}

		/** 获取单件引用
		 *
		 * \param void 
		 * \return 
		 */
		static T& getSingleton( void )
		{	
			assert( mpSingleton );  return ( *mpSingleton ); 
		}

		/** 获取单件实例
		 *
		 * \param void 
		 * \return 
		 */
		static T* getSingletonPtr( void )
		{ 
			return mpSingleton; 
		}
	};
}

#endif