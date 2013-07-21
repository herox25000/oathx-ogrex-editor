// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// ��Ŀ�ض��İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�
#define WINVER 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINNT		// ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ�� Windows 98 ����߰汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0410 //Ϊ Windows Me �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ�� IE 4.0 ����߰汾���ض����ܡ�
#define _WIN32_IE 0x0400	//Ϊ IE 5.0 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ��������������ȫ���Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����
#include <afxmt.h>
#include <AfxCmn.h>
#include <GdiPlus.h>

using namespace Gdiplus;


//MFC �ļ�
#include <Nb30.h>
#include <AfxInet.h>



#include <afxdtctl.h>		// Internet Explorer 4 �����ؼ��� MFC ֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows �����ؼ��� MFC ֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "..\..\�����ļ�\Constant.h"
#include "..\..\�����ļ�\GlobalDef.h"
#include "..\..\�����ļ�\GlobalField.h"
#include "..\..\�����ļ�\GlobalFrame.h"
#include "..\..\�����ļ�\GlobalRight.h"

//����ͷ�ļ�
#include "..\..\��Ϣ����\CMD_Game.h"
#include "..\..\��Ϣ����\CMD_Plaza.h"
#include "..\..\��Ϣ����\CMD_Video.h"

//ģ���
#include "..\..\ģ���\Template.h"

//���ͷ�ļ�
#include "..\ͷ�����\UserFace.h"
#include "..\�������\DownLoad.h"
#include "..\��Ϸ�ȼ�\GameRank.h"
#include "..\��ϵ����\Companion.h"
#include "..\�ŵ�ģ��\ChannelModule.h"
#include "..\�ͻ��˹���\ClientShare.h"
#include "..\�������\NetworkServiceHead.h"
#include "..\�ʻ�����\PropertyModule.h"
#include "..\..\�������\��������\ComService.h"
#include "..\..\�������\����ؼ�\SkinControls.h"
#include "..\..\�������\������Դ\SkinResourceModule.h"
#include "MemDC.h"
#include "GdipButton.h"

//�ַ�����ȫƴ��
static void SafeStrCat(char* dest, const char* src, int iDestBufferLen)
{
	int iDestLen=lstrlen(dest);
	int iSrcLen=lstrlen(src);

	if ((iDestLen+iSrcLen)>=iDestBufferLen)
		return;

	lstrcat(dest, src);
}
//�õ�ִ���ļ���ַ
static void GetModulePath(LPSTR szPath, int iLen)
{
	::GetModuleFileName(NULL, szPath, iLen);
	TCHAR* find=strrchr(szPath, '\\');
	*find=0;
}
