#ifndef _____OgreEventSetStdAfx_H
#define _____OgreEventSetStdAfx_H

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_EventSet_Export_API
#   else
#      ifdef OGREEVENTSET_EXPORTS
#         define Ogre_EventSet_Export_API __declspec (dllexport)
#      else
#         define Ogre_EventSet_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_EventSet_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif

#pragma warning(disable : 4251)
#pragma warning(disable : 4193)
#pragma warning(disable : 4275)
#pragma warning(disable : 4661)

#include <OgreSingleton.h>
#include <OgreAny.h>
#include <OgreIteratorWrapper.h>
#include <OgreLogManager.h>

#endif