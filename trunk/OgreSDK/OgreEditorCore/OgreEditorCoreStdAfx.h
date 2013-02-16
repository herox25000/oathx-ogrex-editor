#pragma once

#include <Windows.h>

#pragma warning(disable : 4251)
#pragma warning(disable : 4193)
#pragma warning(disable : 4275)
#pragma warning(disable : 4661)

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_EditorCore_Export_API
#   else
#      ifdef OGREEDITORCORE_EXPORTS
#         define Ogre_EditorCore_Export_API __declspec (dllexport)
#      else
#         define Ogre_EditorCore_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_EventSet_Export_API
#endif

#include <Ogre.h>

#include "OgreEditorEventDef.h"
#include "OgreEditorTypes.h"
#include "OgreEditorUtility.h"
#include "OgreEventSetStdAfx.h"
#include "OgreEditorSystem.h"

using namespace Ogre;