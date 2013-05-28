#ifndef _____OgreSandBoxTypes_H
#define _____OgreSandBoxTypes_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4193)
#pragma warning(disable : 4275)
#pragma warning(disable : 4661)

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_SandBox_Export_API
#   else
#      ifdef OGRESANDBOXCORE_EXPORTS
#         define Ogre_SandBox_Export_API __declspec (dllexport)
#      else
#         define Ogre_SandBox_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_SandBox_Export_API
#endif

#include <iosfwd>
#include <Ogre.h>
#include <OgrePlugin.h>
#include <OgreDynLib.h>
#include <OgreDynLibManager.h>

namespace Ogre
{

}

#endif