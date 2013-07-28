// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// 从 Windows 标头中排除不常使用的资料
#endif

// 如果您必须使用下列所指定的平台之前的平台，则修改下面的定义。
// 有关不同平台的相应值的最新信息，请参考 MSDN。

#ifndef WINVER				// 允许使用 Windows 95 和 Windows NT 4 或更高版本的特定功能。
#define WINVER 0x0400		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_WINNT		// 允许使用 Windows NT 4 或更高版本的特定功能。
#define _WIN32_WINNT 0x0400		//为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
#endif						

#ifndef _WIN32_WINDOWS		// 允许使用 Windows 98 或更高版本的特定功能。
#define _WIN32_WINDOWS 0x0410 //为 Windows Me 及更新版本改变为适当的值。
#endif

#ifndef _WIN32_IE			// 允许使用 IE 4.0 或更高版本的特定功能。
#define _WIN32_IE 0x0400	//为 IE 5.0 及更新版本改变为适当的值。
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常被安全忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdisp.h>        // MFC 自动化类
#include <afxmt.h>
#include <AfxCmn.h>
#include <afxtempl.h>
#include <GdiPlus.h>
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <algorithm>

using namespace Gdiplus;
using namespace std;


//MFC 文件
#include <Nb30.h>
#include <AfxInet.h>



#include <afxdtctl.h>		// Internet Explorer 4 公共控件的 MFC 支持
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows 公共控件的 MFC 支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "..\..\公共文件\Constant.h"
#include "..\..\公共文件\GlobalDef.h"
#include "..\..\公共文件\GlobalField.h"
#include "..\..\公共文件\GlobalFrame.h"
#include "..\..\公共文件\GlobalRight.h"

//命令头文件
#include "..\..\消息定义\CMD_Game.h"
#include "..\..\消息定义\CMD_Plaza.h"
#include "..\..\消息定义\CMD_Video.h"

//模板库
#include "..\..\模板库\Template.h"

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
#include "..\..\共享组件\界面资源\SkinResourceModule.h"
#include "MemDC.h"
#include "GdipButton.h"
#include "resource.h"
#include "Platform.h"
#include "IGamePlaza.h"

#define CAPTION_SIZE						35							//标题大小
//字符串安全拼接
static void SafeStrCat(char* dest, const char* src, int iDestBufferLen)
{
	int iDestLen=lstrlen(dest);
	int iSrcLen=lstrlen(src);

	if ((iDestLen+iSrcLen)>=iDestBufferLen)
		return;

	lstrcat(dest, src);
}
//得到执行文件地址
static void GetModulePath(LPSTR szPath, int iLen)
{
	::GetModuleFileName(NULL, szPath, iLen);
	TCHAR* find=strrchr(szPath, '\\');
	*find=0;
}
