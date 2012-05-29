#ifndef _____OgreEventSetPrerequisites_H
#define _____OgreEventSetPrerequisites_H

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

namespace Ogre
{
	class FreeFunctionSlot;
	class SubscriberSlot;
	class Event;
	class GlobalEventSet;
	class Property;
	class PropertySet;
}

#endif