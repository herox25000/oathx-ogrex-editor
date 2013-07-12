#ifndef VIDEO_SERVICE_HEAD_FILE
#define VIDEO_SERVICE_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////
//�����ļ�

//ƽ̨�ļ�
#include "macro.h"
//#include "GlobalDef.h"

//���ͷ�ļ�
#include "module.h"
#include "GameFrameHead.h"
#include "SkinControlHead.h"
#include "GamePropertyHead.h"
//#include "PropertyBar.h"

//////////////////////////////////////////////////////////////////////////
//�����궨��

//��������
#ifndef VIDEO_SERVICE_CLASS
	#ifdef  VIDEO_SERVICE_DLL
		#define VIDEO_SERVICE_CLASS _declspec(dllexport)
	#else
		#define VIDEO_SERVICE_CLASS _declspec(dllimport)
	#endif
#endif

//ģ�鶨��
#ifndef _DEBUG
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoService.dll")			//��� DLL ����
#else
	#define VIDEO_SERVICE_DLL_NAME	TEXT("VideoServiceD.dll")			//��� DLL ����
#endif

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//������Ϣ
struct tagVideoNetwordInfo
{
	WORD							wNatPort;							//����˿�
	WORD							wLocalPort;							//����˿�
	DWORD							dwNatAddr;							//�����ַ
	DWORD							dwLocalAddr;						//���ص�ַ
};

//������ͷ�ļ�
#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

#endif
