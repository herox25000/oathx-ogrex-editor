#ifndef ____Og2dD3D9Prerequisites_H
#define ____Og2dD3D9Prerequisites_H

#include "Og2dTypes.h"
#include "Og2dLogManager.h"
#include "Og2dException.h"

#if (OG2D_PLATFORM == OG2D_PLATFORM_WIN32) && !defined(OG2D_STATIC_LIB)
#define sprintf_s snprintf
#	ifdef OG2D_D3D9_EXPORT
#		define Og2d_D3D9_Export_API __declspec(dllexport)
#	else
#       if defined( __MINGW32__ )
#           define Og2d_D3D9_Export_API
#       else
#    		define Og2d_D3D9_Export_API __declspec(dllimport)
#       endif
#	endif
#else
#	define Og2d_D3D9_Export_API

#ifdef _DEBUG
#include "Og2dDebug.h"
#endif
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>

//! 灵活顶点格式
static const unsigned int SVERTEX2DFVF = (D3DFVF_XYZ|D3DFVF_TEX1|D3DFVF_DIFFUSE);

#endif