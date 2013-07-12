#pragma once

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

#include <afxwin.h>         
#include <afxext.h>         

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         
#include <afxodlgs.h>       
#include <afxdisp.h>        
#endif 

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			
#endif 

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			
#endif 

#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			
#endif 


//////////////////////////////////////////////////////////////////////////
//���Ӵ���
#pragma comment (lib,"Winmm.lib")

#ifndef _DEBUG
#ifndef _UNICODE
#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCore.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/SkinControl.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/WHImage.lib")
#else
#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCore.lib")
#pragma comment (lib,"../../���ӿ�/Unicode/SkinControl.lib")
#pragma comment (lib,"../../���ӿ�/Unicode/WHImage.lib")
#endif
#else
#ifndef _UNICODE
#pragma comment (lib,"../../���ӿ�/Ansi/ServiceCoreD.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/SkinControlD.lib")
#pragma comment (lib,"../../���ӿ�/Ansi/WHImageD.lib")
#else
#pragma comment (lib,"../../���ӿ�/Unicode/ServiceCoreD.lib")
#pragma comment (lib,"../../���ӿ�/Unicode/SkinControlD.lib")
#pragma comment (lib,"../../���ӿ�/Unicode/WHImageD.lib")
#endif
#endif


#include "VideoSDK/include/BRAnyChatCoreSDK.h"
#include "VideoSDK/include/GVMessageDefine.h"
#pragma comment(lib,"VideoSDK/lib/BRAnyChatCore.lib")