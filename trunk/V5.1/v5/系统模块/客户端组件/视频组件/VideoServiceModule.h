#ifndef VIDEO_SERVICE_HEAD_FILE
#define VIDEO_SERVICE_HEAD_FILE

#pragma once

//////////////////////////////////////////////////////////////////////////
//�����ļ�

//ƽ̨�ļ�
#include "..\..\ȫ�ֶ���\macro.h"
//#include "..\..\�����ļ�\GlobalDef.h"

//���ͷ�ļ�
#include "..\..\ȫ�ֶ���\module.h"
#include "..\..\�ͻ������\��Ϸ���\GameFrameHead.h"
#include "..\..\�ͻ������\����ؼ�\SkinControlHead.h"
#include "..\..\�ͻ������\��Ϸ����\GamePropertyHead.h"
//#include "..\..\�ͻ������\�ʻ�����\PropertyBar.h"

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
