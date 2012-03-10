#ifndef _____OgreKernelPrerequisites_H
#define _____OgreKernelPrerequisites_H

#include "OgrePrerequisites.h"

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//	//////////////////////////////////////////////////////////////////////////
//	//！定义DLL导出
//	#ifdef __cplusplus
//	extern "C" { 
//	#endif
//
//	#define OgreKernel_Export
//	#	ifdef  OgreKernel_Export
//	#		define Ogre_Export_API _declspec(dllexport)
//	#	else
//	#		define Ogre_Export_API _declspec(dllimport)
//	#endif
//
//	#ifdef __cplusplus
//	}
//	#endif
//#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#	if defined( OGRE_STATIC_LIB )
#   	define Ogre_Export_API
#   else
#   	if defined( OGRE_KENRNEL_EXPORTS )
#       	define Ogre_Export_API __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define Ogre_Export_API
#           else
#       	    define Ogre_Export_API __declspec( dllimport )
#           endif
#   	endif
#	endif
#elif defined ( OGRE_GCC_VISIBILITY )
#   define Ogre_Export_API __attribute__ ((visibility("default")))
#else
#	define Ogre_Export_API
#endif

namespace Ogre
{
	typedef unsigned int		uint32; 
}


#endif