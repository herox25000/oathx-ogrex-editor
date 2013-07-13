#ifndef _____Og2dPlatform_H
#define _____Og2dPlatform_H

//! 定义各种平台
#define OG2D_PLATFORM_WIN32			1
#define OG2D_PLATFORM_LINUX			2
#define OG2D_PLATFORM_APPLE			3
#define OG2D_PLATFORM_SYMBIAN		4
#define OG2D_PLATFORM_IOS			5
#define OG2D_PLATFORM_ANDROID		6
#define OG2D_PLATFORM_NACL			7

//! 定义编译器
#define OG2D_COMPILER_MSVC			1
#define OG2D_COMPILER_GNUC			2
#define OG2D_COMPILER_BORL			3
#define OG2D_COMPILER_WINSCW		4
#define OG2D_COMPILER_GCCE			5
#define OG2D_COMPILER_CLANG			6

#define OG2D_ENDIAN_LITTLE			1
#define OG2D_ENDIAN_BIG				2

#define OG2D_ARCHITECTURE_32		1
#define OG2D_ARCHITECTURE_64		2

/*
* 查找编译器和版本
*/

#if defined( _MSC_VER )
#   define OG2D_COMPILER			OG2D_COMPILER_MSVC
#   define OG2D_COMP_VER			_MSC_VER
#endif


#if OG2D_COMPILER == OG2D_COMPILER_MSVC
#   if OG2D_COMP_VER >= 1200
#       define _____inline __forceinline
#   endif
#else
#   define _____inline __inline
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define OG2D_ARCH_TYPE OG2D_ARCHITECTURE_64
#else
#   define OG2D_ARCH_TYPE OG2D_ARCHITECTURE_32
#endif

/*
* 查找当前平台
*/
#if defined( __WIN32__ ) || defined( _WIN32 )
#   define OG2D_PLATFORM			OG2D_PLATFORM_WIN32
#endif

//----------------------------------------------------------------------------
// Windows Settings
#if OG2D_PLATFORM == OG2D_PLATFORM_WIN32
#include <Windows.h>

//！定义DLL导出
#ifdef __cplusplus
extern "C" { 
#endif

#define Og2d_Export
#ifdef  Og2d_Export
#	define Og2d_Export_API _declspec(dllexport)
#else
#	define Og2d_Export_API _declspec(dllimport)
#endif

#ifdef __cplusplus
}
#endif

#endif // OG2D_PLATFORM == OG2D_PLATFORM_WIN32

//! 定义引擎版本
#ifndef OG2D_SDK_VERSION
#	define OG2D_SDK_VERSION "Og2d-1.0.0"
#endif

#endif
