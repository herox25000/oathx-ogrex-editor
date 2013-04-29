#pragma once

//////////////////////////////////////////////////////////////////////////

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif

#ifndef WINVER
#define WINVER 0x0400
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif						

#ifndef _WIN32_WINDOWS	
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS

#define _AFX_ALL_WARNINGS

#include <afxwin.h> 
#include <afxext.h> 
#include <afxdisp.h>

#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif

//////////////////////////////////////////////////////////////////////////

//系统头文件
#include "Nb30.h"
#include "Afxmt.h"
#include "AfxHtml.h"
#include "AfxInet.h"

//全局头文件
#include "..\..\开发库\Include\Constant.h"
#include "..\..\开发库\Include\GlobalDef.h"
#include "..\..\开发库\Include\GlobalField.h"
#include "..\..\开发库\Include\GlobalFrame.h"
#include "..\..\开发库\Include\GlobalRight.h"

//命令头文件
#include "..\..\开发库\Include\CMD_Game.h"
#include "..\..\开发库\Include\CMD_Plaza.h"
#include "..\..\开发库\Include\CMD_Video.h"

//开发库\Include
#include "..\..\开发库\Include\Template.h"

//组件头文件
#include "..\头像组件\UserFace.h"
#include "..\下载组件\DownLoad.h"
#include "..\游戏等级\GameRank.h"
#include "..\关系管理\Companion.h"
#include "..\信道模块\ChannelModule.h"
#include "..\客户端共享\ClientShare.h"
#include "..\网络服务\NetworkServiceHead.h"
#include "..\鲜花道具\PropertyModule.h"
#include "..\..\共享组件\公共服务\ComService.h"
#include "..\..\共享组件\界面控件\SkinControls.h"
#include "..\..\共享组件\界面控件\PngImage.h"
#include "..\..\共享组件\界面资源\SkinResourceModule.h"




//////////////////////////////////////////////////////////////////////////
