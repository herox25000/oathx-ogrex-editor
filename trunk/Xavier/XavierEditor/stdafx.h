
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include "OgreSystemAPIExport.h"
#include "OgreEventSetStdAfx.h"
#include "OgreAny.h"
#include "OgrePropertySet.h"
#include "OgreWorld.h"
#include "OgreTerrainSystem.h"
#include "OgreDecalMesh.h"
#include "XavierEditorMessageDef.h"
#include "EditorPropertyKeyWordDef.h"

using namespace Ogre;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

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

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


