/**
 *	AnyChat Platform SDK Include file
 */

#if !defined(GV_SDK_DEFINE__)
#define GV_SDK_DEFINE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GVMessageDefine.h"
#include "GVErrorCodeDefine.h"


#pragma pack(push, 1)


/**
 *	�ͻ���״̬�����
 */
typedef enum GV_STATE_TYPE_DEFINE
{
	GV_STATE_TYPE_ACTIVE = 0,					///< �ͻ��˻����״̬
	GV_STATE_TYPE_CAMERA,						///< �ͻ��������״̬
	GV_STATE_TYPE_AUDIO,						///< �ͻ�����Ƶ�豸״̬
	GV_STATE_TYPE_CHATMODE						///< �ͻ�������ģʽ
}GV_STATE_TYPE;


//����ģʽ����
#define GV_MEETING_MODE_FREE	0				///< ����ģʽ������û�����ƣ����ɷ��ԣ���Mic
#define GV_MEETING_MODE_CHAIR	1				///< ����ģʽ�����������ƣ�ֻ�������˸�Mic���ܷ���
#define GV_MEETING_MODE_ORDER	2				///< ��Ѳģʽ�����������ƣ�ֻ���ֵ��Լ����ܷ���


//�״̬����
#define GV_ACTIVE_STATE_NORMAL	0				///< ����
#define GV_ACTIVE_STATE_BUSY	1				///< ��æ
#define GV_ACTIVE_STATE_AWAY	2				///< �뿪

//����ͷ״̬����
#define GV_CAMERA_STATE_NULL	0				///< û������ͷ
#define GV_CAMERA_STATE_NORMAL	1				///< ������ͷ��û�д�
#define GV_CAMERA_STATE_OPEN	2				///< ����ͷ�Ѵ�

// Mic�״̬����
#define GV_AUDIO_STATE_NULL		0				///< û�а�װ����
#define GV_AUDIO_STATE_NORMAL	1				///< ����������û�д�Mic
#define GV_AUDIO_STATE_OPEN		2				///< Mic�Ѵ�

// �ͻ�������ģʽ����
#define GV_CHATMODE_PUBLIC		0				///< ����ģʽ
#define GV_CHATMODE_PRIVATE		1				///< ˽��ģʽ�����ղ��������û�����������Ƶ���ݣ����ܽ��յ��Լ�˽�Ķ������������Ƶ���ݣ�������Ϣ����ģʽӰ��

#pragma pack(pop)

#endif // !defined(GV_SDK_DEFINE__)
