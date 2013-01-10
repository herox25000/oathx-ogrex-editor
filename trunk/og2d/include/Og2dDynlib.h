#ifndef _____Og2dDynlib_H
#define _____Og2dDynlib_H

#include "Og2dTypes.h"

#if OG2D_PLATFORM == OG2D_PLATFORM_WIN32
#    define DYNLIB_HANDLE			hInstance
#    define DYNLIB_LOAD( a )		LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNLIB_GETSYM( a, b )	GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a )		!FreeLibrary( a )

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;
typedef void* Symbol;

#elif OG2D_PLATFORM == OG2D_PLATFORM_LINUX || OG2D_PLATFORM == OG2D_PLATFORM_ANDROID
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a )		dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#    define DYNLIB_GETSYM( a, b )	dlsym( a, b )
#    define DYNLIB_UNLOAD( a )		dlclose( a )
typedef void* Symbol;

#elif OG2D_PLATFORM == OG2D_PLATFORM_APPLE || OG2D_PLATFORM == OG2D_PLATFORM_APPLE_IOS
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a )		mac_loadDylib( a )
#    define DYNLIB_GETSYM( a, b )	dlsym( a, b )
#    define DYNLIB_UNLOAD( a )		dlclose( a )
typedef void* Symbol;

#elif OG2D_PLATFORM == OG2D_PLATFORM_SYMBIAN || OG2D_PLATFORM == OG2D_PLATFORM_NACL
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a ) 0
#    define DYNLIB_GETSYM( a, b ) 0
#    define DYNLIB_UNLOAD( a ) 0
typedef void* Symbol;

#endif

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
	* \Desc    : 动态链接库
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API DynLib
    {
    public:
        /** 构造函数
         *
         * \param name 
         * \return 
         */
        DynLib( const String& name );

        /** 析构函数
         *
         * \return 
         */
        virtual ~DynLib();

		/** 获取名称
		 *
		 * \param void 
		 * \return 
		 */
		const String&			getName(void) const 
		{
			return m_Name; 
		}

        /** 获取函数指针
         *
         * \param strName 
         */
        virtual Symbol			getSymbol( const String& strName ) const throw();

		/** 加载动态链接库
         *
         */
        virtual void			load();

        /** 卸载动态链接库
         *
         */
         virtual void			unload();

	protected:
		
        /** 获取加载错误
         *
         * \param void 
         * \return 
         */
        String					dynlibError(void);
    protected:
        DYNLIB_HANDLE			m_hInst;
		String					m_Name;
    };
}

#endif