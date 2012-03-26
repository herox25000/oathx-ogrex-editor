#ifndef _____OgreSystemPrerequisites_H
#define _____OgreSystemPrerequisites_H

#include "OgrePrerequisites.h"

#if _WIN32
#   if defined( __MINGW32__ )
#      define OgreSystem_Export_API
#   else
#      ifdef OGRESYSTEM_EXPORT
#         define OgreSystem_Export_API __declspec (dllexport)
#      else
#         define OgreSystem_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define OgreSystem_Export_API
#endif

#ifndef _MSC_VER
	#define sprintf_s snprintf
#endif

#include <Ogre.h>

#ifndef SetAlpha
#define SetAlpha(col,a)			(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#endif

#ifndef	GetAlpha
#define GetAlpha(argb)			((BYTE)(((DWORD)(argb))>>24))
#endif

#define ARGBNORMAL(a, r, g, b)	(((DWORD)(a*255.0f)<<24)|((DWORD)(r*255.0f)<<16)|((DWORD)(g*255.0f)<<8)|((BYTE)(b*255.0f)))

#define GetB(argb)				((BYTE)(argb))
#define GetG(argb)				((BYTE)(((WORD)(argb))>>8))
#define GetR(argb)				((BYTE)((((DWORD)(argb))>>16) & 0xff))


#define SetB(col,r)				(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SetG(col,g)				(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SetR(col,b)				(((col) & 0xFFFFFF00) + DWORD(b))


#define NormalValue(a)	(a/255.0f)

#endif