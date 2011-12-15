#ifndef __SfxExplorerPluginPrerequisites_H__
#define __SfxExplorerPluginPrerequisites_H__

#include "OgrePrerequisites.h"

#if (OGRE_PLATFORM == OGRE_PLATFORM_WIN32) && !defined(OGRE_STATIC_LIB)
#   ifdef OGRE_EXPLORERPLUGIN_EXPORTS
#       define _OgreExplorerExport __declspec(dllexport)
#   else
#       if defined( __MINGW32__ )
#           define _OgreExplorerExport
#       else
#    		define _OgreExplorerExport __declspec(dllimport)
#       endif
#   endif
#elif defined ( OGRE_GCC_VISIBILITY )
#    define _OgreExplorerExport  __attribute__ ((visibility("default")))
#else
#   define _OgreExplorerExport
#endif


namespace Ogre {

}


#endif
