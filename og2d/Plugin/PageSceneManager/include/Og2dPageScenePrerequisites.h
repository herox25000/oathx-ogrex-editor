#ifndef ____Og2dPageScenePrerequisites_H
#define ____Og2dPageScenePrerequisites_H

#include "Og2dTypes.h"
#include "Og2dMath.h"
#include "Og2dLogManager.h"
#include "Og2dException.h"

#if (OG2D_PLATFORM == OG2D_PLATFORM_WIN32) && !defined(OG2D_STATIC_LIB)
#define sprintf_s snprintf
#	ifdef OG2D_PSM_EXPORT
#		define Og2d_PSM_Export_API __declspec(dllexport)
#	else
#       if defined( __MINGW32__ )
#           define Og2d_PSM_Export_API
#       else
#    		define Og2d_PSM_Export_API __declspec(dllimport)
#       endif
#	endif
#else
#	define Og2d_PSM_Export_API

#ifdef _DEBUG
#include "Og2dDebug.h"
#endif
#endif

#endif