#ifndef _____OgreEditToolPrerequisites_H
#define _____OgreEditToolPrerequisites_H

#include "OgrePrerequisites.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#	if defined( OGRE_STATIC_LIB )
#   	define OgreEditTool_Export_API
#   else
#   	if defined( OGRE_EDITTOOL_EXPORTS )
#       	define OgreEditTool_Export_API __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define OgreEditTool_Export_API
#           else
#       	    define OgreEditTool_Export_API __declspec( dllimport )
#           endif
#   	endif
#	endif
#elif defined ( OGRE_GCC_VISIBILITY )
#   define OgreEditTool_Export_API __attribute__ ((visibility("default")))
#else
#	define OgreEditTool_Export_API
#endif

namespace Ogre
{
	typedef unsigned int		uint32; 
}

#include <Ogre.h>
#include <map>
#include <vector>
#include <list>

#endif