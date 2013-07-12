#if !defined(BR_ANYCHAT_CORE_SDK_H__INCLUDED_)
#define BR_ANYCHAT_CORE_SDK_H__INCLUDED_

#include <mmsystem.h>
#include <wingdi.h>


/**
 *	AnyChat Core SDK Include File
 */


#pragma once

#include "GVSDK.h"

#define BRAC_API extern "C" __declspec(dllexport)

// ��Ƶͼ���ʽ����
enum BRAC_PixelFormat{
	BRAC_PIX_FMT_RGB24 = 0,						///< Packed RGB 8:8:8, 24bpp, RGBRGB...��MEDIASUBTYPE_RGB24��
	BRAC_PIX_FMT_RGB32,							///< ��Ӧ�ڣ�MEDIASUBTYPE_RGB32��Packed RGB 8:8:8, 32bpp, (msb)8A 8R 8G 8B(lsb), in cpu endianness
	BRAC_PIX_FMT_YV12,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YV12��Planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
	BRAC_PIX_FMT_YUY2,							///< ��Ӧ�ڣ�MEDIASUBTYPE_YUY2��Packed YUV 4:2:2, 16bpp, Y0 Cb Y1 Cr
};

// ��Ƶ�豸����
enum BRAC_AudioDevice{
	BRAC_AD_WAVEIN = 0,							///< �����豸��Mic
	BRAC_AD_WAVEOUT,							///< ����豸��Wave
};

// ����ģʽ����
#define BRAC_FUNC_VIDEO_CBDATA		0x00000001L	///< ͨ���ص����������Ƶ����
#define BRAC_FUNC_VIDEO_AUTODISP	0x00000002L	///< ��SDK��������Ƶ������Ƶ��ʾ��ָ���Ĵ�����
#define BRAC_FUNC_AUDIO_CBDATA		0x00000004L	///< ͨ��˳�����������Ƶ����
#define BRAC_FUNC_AUDIO_AUTOPLAY	0x00000008L	///< ��SDK��������Ƶ��ֱ�Ӳ���


// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_VideoData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue);
// ��Ƶ���ݻص���������
typedef void (CALLBACK * BRAC_AudioData_CallBack)(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue);
// ������Ϣ�ص���������
typedef void (CALLBACK * BRAC_TextMessage_CallBack)(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen, LPVOID lpUserValue);
// ͸��ͨ�����ݻص���������
typedef void (CALLBACK * BRAC_TransBuffer_CallBack)(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue);
// �����仯�ص���������
typedef void (CALLBACK * BRAC_VolumeChange_CallBack)(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue);

/**
 *	API��������
 */

// ��ȡSDK�汾��Ϣ
BRAC_API DWORD BRAC_GetSDKVersion(DWORD& dwMainVer, DWORD& dwSubVer, LPSTR lpCompileTime, DWORD dwBufLen);

// ��ʼ��ϵͳ
BRAC_API DWORD BRAC_InitSDK(HWND hWnd, DWORD dwFuncMode);

// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetVideoDataCallBack(BRAC_PixelFormat pixFmt, BRAC_VideoData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ������Ƶ���ݻص�����
BRAC_API DWORD BRAC_SetAudioDataCallBack(BRAC_AudioData_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����������Ϣ�ص�����
BRAC_API DWORD BRAC_SetTextMessageCallBack(BRAC_TextMessage_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ����͸��ͨ�����ݻص�����
BRAC_API DWORD BRAC_SetTransBufferCallBack(BRAC_TransBuffer_CallBack lpFunction, LPVOID lpUserValue=NULL);
// ���������仯�ص�����
BRAC_API DWORD BRAC_SetVolumeChangeCallBack(BRAC_VolumeChange_CallBack lpFunction, LPVOID lpUserValue=NULL);

// ���ӷ�����
BRAC_API DWORD BRAC_Connect(LPCTSTR lpServerAddr, DWORD dwPort);
// ��¼ϵͳ
BRAC_API DWORD BRAC_Login(LPCTSTR lpUserName, LPCTSTR lpPassword, DWORD dwPassEncType); 
// ���뷿��
BRAC_API DWORD BRAC_EnterRoom(DWORD dwRoomid, LPCTSTR lpRoomPass, DWORD dwPassEncType);
// �뿪����
BRAC_API DWORD BRAC_LeaveRoom(DWORD dwRoomid);
// ע��ϵͳ
BRAC_API DWORD BRAC_Logout(VOID);

// �ͷ�������Դ
BRAC_API DWORD BRAC_Release(VOID);

// ��ȡ��ǰ���������û��б�
BRAC_API DWORD BRAC_GetOnlineUser(LPDWORD lpUserIDArray, DWORD& dwUserNum);
// ��ѯ�û�����ͷ��״̬
BRAC_API DWORD BRAC_GetCameraState(DWORD dwUserid, DWORD& dwState);
// ��ѯ�û�����״̬
BRAC_API DWORD BRAC_GetSpeakState(DWORD dwUserid, DWORD& dwState);
// ��ʾ������Ƶ������ڶԻ���
BRAC_API DWORD BRAC_ShowLVProperty(HWND hParent, LPCTSTR szCaption=NULL, DWORD dwX=0, DWORD dwY=0);


// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumVideoCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectVideoCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurVideoCapture(CHAR* lpDeviceName, DWORD dwLen);
// ö�ٱ�����Ƶ�ɼ��豸
BRAC_API DWORD BRAC_EnumAudioCapture(CHAR** lpDeviceName, DWORD& dwDeviceNum);
// ѡ��ָ������Ƶ�ɼ��豸
BRAC_API DWORD BRAC_SelectAudioCapture(LPCTSTR szCaptureName);
// ��ȡ��ǰʹ�õ���Ƶ�ɼ��豸
BRAC_API DWORD BRAC_GetCurAudioCapture(CHAR* lpDeviceName, DWORD dwLen);


// �����û���Ƶ
BRAC_API DWORD BRAC_UserCameraControl(DWORD dwUserid, BOOL bOpen);
// �����û�����
BRAC_API DWORD BRAC_UserSpeakControl(DWORD dwUserid, BOOL bOpen);
// ������Ƶ��ʾλ��
BRAC_API DWORD BRAC_SetVideoPos(DWORD dwUserid, HWND hWnd, DWORD dwLeft, DWORD dwTop, DWORD dwRight, DWORD dwBottom);

// ��ȡָ����Ƶ�豸�ĵ�ǰ����
BRAC_API DWORD BRAC_AudioGetVolume(BRAC_AudioDevice device, DWORD& dwVolume);
// ����ָ����Ƶ�豸������
BRAC_API DWORD BRAC_AudioSetVolume(BRAC_AudioDevice device, DWORD dwVolume);

// ͸��ͨ�����ͻ�����
BRAC_API DWORD BRAC_TransBuffer(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen);
// �����ı���Ϣ
BRAC_API DWORD BRAC_SendTextMessage(DWORD dwUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen);

// ���ĵ�ǰ������ģʽ
BRAC_API DWORD BRAC_ChangeChatMode(DWORD dwChatMode);
// ��ȡָ���û���ǰ������ģʽ
BRAC_API DWORD BRAC_GetUserChatMode(DWORD dwUserid, DWORD& dwChatMode);
// ������Է�˽�ģ���Է�����˽������
BRAC_API DWORD BRAC_PrivateChatRequest(DWORD dwUserid);
// �ظ��Է���˽������
BRAC_API DWORD BRAC_PrivateChatEcho(DWORD dwUserid, DWORD dwRequestid,BOOL bAccept);
// �ظ��Է���˽��������չ�����Ը���������룩
BRAC_API DWORD BRAC_PrivateChatEchoEx(DWORD dwUserid, DWORD dwRequestid,DWORD dwErrorCode);
// �˳���ĳ�û���˽�ģ����߽�ĳ�û����Լ���˽���б������
BRAC_API DWORD BRAC_PrivateChatExit(DWORD dwUserid);



#endif //BR_ANYCHAT_CORE_SDK_H__INCLUDED_
