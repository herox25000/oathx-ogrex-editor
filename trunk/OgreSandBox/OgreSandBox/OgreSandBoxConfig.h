#ifndef _____OgreSandBoxConfig_H
#define _____OgreSandBoxConfig_H

#pragma warning(disable : 4251)
#pragma warning(disable : 4193)
#pragma warning(disable : 4275)
#pragma warning(disable : 4661)

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_SandBox_Export_API
#   else
#      ifdef OGRESANDBOX_EXPORTS
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
#include <OgreAny.h>
#include <OgreIteratorWrapper.h>

#ifndef SAFE_DELETE
#	define SAFE_DELETE(p) if (p != NULL) {delete p; p=NULL;}
#endif


#endif