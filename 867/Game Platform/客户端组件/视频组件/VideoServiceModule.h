#ifndef VIDEO_SERVICE_HEAD_FILE
#define VIDEO_SERVICE_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//平台头文件
#include "..\..\开发库\Include\Template.h"
#include "..\..\开发库\Include\GlobalDef.h"

//开发库\Include
#include "..\..\开发库\Include\CMD_Video.h"

//组件头文件
#include "..\..\开发库\Include\Module.h"
#include "..\..\共享组件\界面控件\SkinControls.h"
#include "..\..\客户端组件\游戏框架\GameFrame.h"
#include "..\..\客户端组件\鲜花道具\FlowerEffectcontrol.h"
//////////////////////////////////////////////////////////////////////////
//公共宏定义

//导出定义
#ifndef VIDEO_SERVICE_CLASS
	#ifdef  VIDEO_SERVICE_DLL
		#define VIDEO_SERVICE_CLASS _declspec(dllexport)
	#else
		#define VIDEO_SERVICE_CLASS _declspec(dllimport)
	#endif
#endif

//模块定义
#ifndef _DEBUG
	#define VIDEO_SERVICE_DLL_NAME	TEXT("plugin_video.dll")			//组件 DLL 名字
#else
	#define VIDEO_SERVICE_DLL_NAME	TEXT("plugin_video_d.dll")			//组件 DLL 名字
#endif

//////////////////////////////////////////////////////////////////////////
//结构定义

//连接信息
struct tagVideoNetwordInfo
{
	WORD							wNatPort;							//网络端口
	WORD							wLocalPort;							//网络端口
	DWORD							dwNatAddr;							//网络地址
	DWORD							dwLocalAddr;						//本地地址
};

//////////////////////////////////////////////////////////////////////////

//导出类头文件

#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

#endif
