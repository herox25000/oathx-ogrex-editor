#ifndef _____OgreSerialzePluginPrerequisites_H
#define _____OgreSerialzePluginPrerequisites_H

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_Serialze_Export_API
#   else
#      ifdef OGRESERIALZE_EXPORT
#         define Ogre_Serialze_Export_API __declspec (dllexport)
#      else
#         define Ogre_Serialze_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_Serialze_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif

#include "OgreSdk.h"
#include "OgreSerialzePropertyNameDef.h"

#endif