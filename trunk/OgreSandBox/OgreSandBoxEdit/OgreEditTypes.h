#ifndef _____OgreSandBoxEditTypes_H
#define _____OgreSandBoxEditTypes_H

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_SandBoxEdit_Export_API
#   else
#      ifdef OGRESANDBOXEDIT_EXPORTS
#         define Ogre_SandBoxEdit_Export_API __declspec (dllexport)
#      else
#         define Ogre_SandBoxEdit_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_SandBoxEdit_Export_API
#endif

#include "OgreSandBoxCore.h"

namespace Ogre
{
	class Editor;
	class EditorFactory;
}

#endif