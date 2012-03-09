#ifndef _____IKernelTypes_h
#define _____IKernelTypes_h

#include <string>

//////////////////////////////////////////////////////////////////////////
//! 关闭常见警告
#pragma warning (disable : 4786)

#pragma warning (disable : 4503)

#pragma warning (disable : 4244)

#pragma warning (disable : 4305)

#pragma warning (disable : 4251)

#pragma warning (disable : 4275)

#pragma warning (disable : 4290)

#pragma warning (disable:  4661)

#pragma warning (disable:  4996)

#pragma warning (disable : 201)

//////////////////////////////////////////////////////////////////////////
//！定义DLL导出
#ifdef __cplusplus
extern "C" { 
#endif

#define LGQKernel_Export
#	ifdef  LGQKernel_Export
#		define Kernel_Export_API _declspec(dllexport)
#	else
#		define Kernel_Export_API _declspec(dllimport)
#endif

#ifdef __cplusplus
}
#endif


namespace kernel
{

#ifndef String
	typedef std::string String;
#endif
	
	//! 8 bit unsigned variable.
		/** This is a typedef for unsigned char, it ensures portability of the engine. */
#ifdef _MSC_VER
		typedef unsigned __int8		u8;
#else
		typedef unsigned char		u8;
#endif

	//! 8 bit signed variable.
	/** This is a typedef for signed char, it ensures portability of the engine. */
#ifdef _MSC_VER
	typedef __int8					s8;
#else
	typedef signed char				s8;
#endif

	//! 8 bit character variable.
	/** This is a typedef for char, it ensures portability of the engine. */
	typedef char					c8;



	//! 16 bit unsigned variable.
	/** This is a typedef for unsigned short, it ensures portability of the engine. */
#ifdef _MSC_VER
	typedef unsigned __int16		u16;
#else
	typedef unsigned short			u16;
#endif

	//! 16 bit signed variable.
	/** This is a typedef for signed short, it ensures portability of the engine. */
#ifdef _MSC_VER
	typedef __int16					s16;
#else
	typedef signed short			s16;
#endif


	//! 32 bit unsigned variable.
	/** This is a typedef for unsigned int, it ensures portability of the engine. */
#ifdef _MSC_VER
	typedef unsigned __int32		u32;
#else
	typedef unsigned int			u32;
#endif

	//! 32 bit signed variable.
	/** This is a typedef for signed int, it ensures portability of the engine. */
#ifdef _MSC_VER
	typedef __int32					s32;
#else
	typedef signed int				s32;
#endif

	// 64 bit signed variable.
	// This is a typedef for __int64, it ensures portability of the engine.
	// This type is currently not used by the engine and not supported by compilers
	// other than Microsoft Compilers, so it is outcommented.
	//typedef __int64				s64;


	//! 32 bit floating point variable.
	/** This is a typedef for float, it ensures portability of the engine. */
	typedef float					f32;

	//! 64 bit floating point variable.
	/** This is a typedef for double, it ensures portability of the engine. */
	typedef double					d64;
}

//! creates four CC codes used in Irrlicht for simple ids
/** some compilers can create those by directly writing the
code like 'code', but some generate warnings so we use this macro here */
#define MAKE_IRR_ID(c0, c1, c2, c3) ((u32)(u8)(c0) | ((u32)(u8)(c1) << 8) | ((u32)(u8)(c2) << 16) | ((u32)(u8)(c3) << 24 ))

#endif