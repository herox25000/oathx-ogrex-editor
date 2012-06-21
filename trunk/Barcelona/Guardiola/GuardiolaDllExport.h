#ifndef _____GuardiolaDllExport_H
#define _____GuardiolaDllExport_H

#if _WIN32
#   if defined( __MINGW32__ )
#      define GuardiolaDLL_Export_API
#   else
#      ifdef GUARDIOLA_DLL_EXPORT
#         define GuardiolaDLL_Export_API __declspec (dllexport)
#      else
#         define GuardiolaDLL_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define GuardiolaDLL_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif

#include "Ogre.h"

#endif