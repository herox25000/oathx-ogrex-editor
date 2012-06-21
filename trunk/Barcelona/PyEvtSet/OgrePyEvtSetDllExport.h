#ifndef _____OgrePyEvtSetDllExport_H
#define _____OgrePyEvtSetDllExport_H

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_EventSet_Export_API
#   else
#      ifdef OGRE_EVENTSET_EXPORT
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

#include "OgreSingleton.h"
#include "OgreAny.h"
#include "OgreIteratorWrapper.h"
#include "OgreLogManager.h"

// LOG ºê
#ifndef TKLogEvent
#	define TKLogEvent	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->logMessage
#endif

// Êä³öLOGÎÄ¼ş
#ifndef _DEBUG_LOG
#	define _DEBUG_LOG
#endif

#endif