#ifndef _____OgreEditSystemPrerequisites_H
#define _____OgreEditSystemPrerequisites_H

#include "OgrePrerequisites.h"
#include "OgreSystemPrerequisites.h"

#if _WIN32
#   if defined( __MINGW32__ )
#      define OgreAppEdit_Export_API
#   else
#      ifdef OGREAPPEDIT_EXPORT
#         define OgreAppEdit_Export_API __declspec (dllexport)
#      else
#         define OgreAppEdit_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define OgreAppEdit_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif

#include <Ogre.h>

#ifdef _DEBUG
#   define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#   define DEBUG_CLIENTBLOCK
#endif  // _DEBUG

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

#define EDIT_XMLSERIALIZE		"XMLSerializeEditor"
#define FACTORY_XMLSERIALIZE	"XMLSerializeEditorFactory"

#define EDIT_GRIDEDIROR			"GridEditor"
#define FACTORY_GRID			"GridEditorFactory"

#define EDIT_TERRAIN			"TerrainEditor"
#define FACTORY_TERRAIN			"TerrainEditorFactory"

#endif