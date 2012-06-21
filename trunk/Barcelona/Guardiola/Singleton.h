#ifndef _____Singleton_H
#define _____Singleton_H

#include <assert.h>

namespace Barcelona
{
    /**
    * \ingroup : Guardiola
    *
    * \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
    *
    * \VERSION : 1.0
    *
    * \date    : 2012-06-22
    *
    * \Author  : lp
    *
    * \Desc    : 单实例对象接口
    *
    * \bug     : 
    *
    */
    template <typename T> class Singleton
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

        static T* msSingleton;

    public:
        /**
         *
         * \param void 
         * \return 
         */
        Singleton( void )
        {
            assert( !msSingleton );
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
            int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
            msSingleton = (T*)((int)this + offset);
#else
			msSingleton = static_cast< T* >( this );
#endif
        }
        /**
         *
         * \param void 
         * \return 
         */
        ~Singleton( void )
        {  
			assert( msSingleton );  msSingleton = 0; 
		}

        /**
         *
         * \param void 
         * \return 
         */
        static T& getSingleton( void )
		{	
			assert( msSingleton );  return ( *msSingleton ); 
		}

        /**
         *
         * \param void 
         * \return 
         */
        static T* getSingletonPtr( void )
		{ 
			return msSingleton; 
		}
    };	
}

#endif