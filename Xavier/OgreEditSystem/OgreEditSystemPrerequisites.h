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
	class CameraEditor;
	class CameraEditorFactory;
	class ViewPortEditor;
	class ViewPortEditorFactory;
}

#include <Ogre.h>

#define _OUTPUT_LOG

#ifndef TKLogEvent
#define TKLogEvent	Ogre::LogManager::getSingletonPtr()->getDefaultLog()->logMessage
#endif

#ifndef KER_HANDLE_WINDOW
#define	KER_HANDLE_WINDOW		"externalWindowHandle" 
#endif

// Ö÷äÖÈ¾´°¿ÚÃû
#ifndef XAVIER_WINDOW_NAME
#define XAVIER_WINDOW_NAME		"XavierWindow"
#endif

#define NAME_CAMERA				"XavierCamera"
#define NAME_SCENEMANAGER		"XavierSceneManager"

#define EDIT_RENDERWINDOW		"RenderWindowEditor"
#define FACTORY_RENDERWINDOW	"RenderWindowEditorFactory"

#define EDIT_SCENEMANAGER		"SceneManagerEditor"
#define FACTORY_SCENEMANAGER	"SceneManagerEditorFactory"

#define EDIT_CAMERA				"CameraEditor"
#define FACTORY_CAMERA			"CameraEditorFactory"

#define EDIT_VIEWPORT			"ViewPortEditor"
#define FACTORY_VIEWPORT		"ViewPortEditorFactory"

#endif