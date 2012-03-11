#ifndef _____OgreEditSystemPrerequisites_H
#define _____OgreEditSystemPrerequisites_H

#include "OgrePrerequisites.h"

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_EditSystem_Export_API
#   else
#      ifdef OGREEDITSYSTEM_EXPORT
#         define Ogre_EditSystem_Export_API __declspec (dllexport)
#      else
#         define Ogre_EditSystem_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_EditSystem_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif


namespace Ogre
{
	class BaseEditor;
	class BaseEditorFactory;
	class RenderWindowEditor;
	class RenderWindowEditorFactory;
	class SceneManagerEditor;
	class RenderWindowEditorFactory;
}

#include <Ogre.h>
#include <map>
#include <vector>
#include <list>

#ifndef KER_HANDLE_WINDOW
#define	KER_HANDLE_WINDOW		"externalWindowHandle" 
#endif

// Ö÷äÖÈ¾´°¿ÚÃû
#ifndef XAVIER_WINDOW_NAME
#define XAVIER_WINDOW_NAME		"XavierWindow"
#endif

#define EDIT_RENDERWINDOW		"RenderWindowEditor"
#define FACTORY_RENDERWINDOW	"RenderWindowEditorFactory"

#define EDIT_SCENEMANAGER		"SceneManagerEditor"
#define FACTORY_SCENEMANAGER	"SceneManagerEditorFactory"

#endif