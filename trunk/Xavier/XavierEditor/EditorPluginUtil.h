#pragma once

namespace Ogre
{

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


#define NormalValue(a)			(a/255.0f)

	//////////////////////////////////////////////////////////////////////////
	static const String		EDITOR_SCENEPLUGIN_NAME = "SceneManager";
	static const String		EDITOR_VIEWPORT_CAMER	= "Camera";
	static const String		EDITOR_VIEWPORT			= "Viewport";

	//////////////////////////////////////////////////////////////////////////
	enum {
		NORMAL_ALHPA,
		NORMAL_RGB,
		NORMAL_X,
		NORMAL_Y,
		NORMAL_Z,
		NORMAL_COUNT,
	};

	static const String NormalPropertyName[] = {
		"Alpha",
		"RGB",
		"x",
		"y",
		"z",
	};

	static int convertNormalPropertyType(const String& name)
	{
		for (int i=0; i<NORMAL_COUNT; i++)
		{
			if (NormalPropertyName[i] == name)
				return i;
		}

		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
}