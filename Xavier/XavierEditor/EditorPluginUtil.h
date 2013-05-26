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

#ifndef SAFE_DELETE
#define SAFE_DELETE( p ) { if (NULL != p) {delete p; p=NULL;}}
#endif

	//////////////////////////////////////////////////////////////////////////
	static const String		EDITOR_SCENEPLUGIN_NAME = "SceneManager";
	static const String		EDITOR_VIEWPORT_CAMER	= "Camera";
	static const String		EDITOR_VIEWPORT			= "Viewport";
	static const String		EDITOR_TERRAIN			= "TerrainGroup";

	// »­Ë¢Íø¸ñÃû³Æ
	static const String		BRUSH_MESH_NAME			= "XavierEditorBrushMesh";

	static const float		BRUSH_MAX_VALUE			= 999999;

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

	static const String FogModePropertyName[] = {
		/// No fog. Duh.
		"FOG_NONE",
		/// Fog density increases  exponentially from the camera (fog = 1/e^(distance * density))
		"FOG_EXP",
		/// Fog density increases at the square of FOG_EXP, i.e. even quicker (fog = 1/e^(distance * density)^2)
		"FOG_EXP2",
		/// Fog density increases linearly between the start and end distances
		"FOG_LINEAR"
	};

	static int	convertFogModePropertyType(const String& name)
	{
		for (int i=0; i<=FOG_LINEAR; i++)
		{
			if (FogModePropertyName[i] == name)
				return i;
		}

		return 0;
	}
	//////////////////////////////////////////////////////////////////////////

	
	static int	QueryAutoID()
	{
		static int nAutoID;
		return nAutoID ++;
	}
}