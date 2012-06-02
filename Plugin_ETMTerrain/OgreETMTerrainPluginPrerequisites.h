#ifndef _____OgreETMTerrainPrerequisites_H
#define _____OgreETMTerrainPrerequisites_H


#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_ETMTerrain_Export_API
#   else
#      ifdef OGRE_ETMTERRAIN_EXPORT
#         define Ogre_ETMTerrain_Export_API __declspec (dllexport)
#      else
#         define Ogre_ETMTerrain_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_ETMTerrain_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif

#include "OgreSdk.h"
#include "OgreEventSetPrerequisites.h"

#endif