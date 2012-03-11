#ifndef _____OgreEditSystemPrerequisites_H
#define _____OgreEditSystemPrerequisites_H

#include "OgrePrerequisites.h"

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_EditSystem_Export_API
#   else
#      ifdef OGREEDITSYSTEM_EXPORT
#         define Ogre_EditSystem_Export_API __declspec (dllexport)
#      else
#         define Ogre_EditSystem_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_EditSystem_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
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