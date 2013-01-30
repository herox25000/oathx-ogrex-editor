#ifndef _____OgreSystemAPIExport_H
#define _____OgreSystemAPIExport_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4193)
#pragma warning(disable : 4275)
#pragma warning(disable : 4661)

#include <Ogre.h>

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_System_Export_API
#   else
#      ifdef XAVIERSYSTEM_EXPORTS
#         define Ogre_System_Export_API __declspec (dllexport)
#      else
#         define Ogre_System_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_System_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif


namespace Ogre
{
	class Server;
}

#endif