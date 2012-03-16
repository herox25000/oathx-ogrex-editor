#ifndef _____OgreSystemPrerequisites_H
#define _____OgreSystemPrerequisites_H

#include "OgrePrerequisites.h"

#if _WIN32
#   if defined( __MINGW32__ )
#      define OgreSystem_Export_API
#   else
#      ifdef OGRESYSTEM_EXPORT
#         define OgreSystem_Export_API __declspec (dllexport)
#      else
#         define OgreSystem_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define OgreSystem_Export_API
#endif

#ifndef _MSC_VER
	#define sprintf_s snprintf
#endif

#include <Ogre.h>

#endif