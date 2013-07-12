// GVMessageDefine.h: interface for the SDK Message.
//
//////////////////////////////////////////////////////////////////////

#if !defined(GV_MESSAGE_DEFINE__)
#define GV_MESSAGE_DEFINE__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	WM_GV	WM_USER + 200

#define WM_GV_CONNECT				WM_GV + 1		///< �ͻ������ӷ�������wParam��BOOL����ʾ�Ƿ����ӳɹ�
#define WM_GV_LOGINSYSTEM			WM_GV + 2		///< �ͻ��˵�¼ϵͳ��wParam��INT����ʾ�Լ����û�ID�ţ�lParam��INT����ʾ��¼�����0 �ɹ�������Ϊ������룬�ο�������붨��
#define WM_GV_ENTERROOM				WM_GV + 3		///< �ͻ��˽��뷿�䣬wParam��INT����ʾ�����뷿���ID�ţ�lParam��INT����ʾ�Ƿ���뷿�䣺0�ɹ����룬����Ϊ�������
#define WM_GV_MICSTATECHANGE		WM_GV + 4		///< �û���Mic״̬�仯��Ϣ��wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û��Ƿ����Mic
#define WM_GV_USERATROOM			WM_GV + 5		///< �û����루�뿪�����䣬wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û��ǽ��루TRUE�����뿪��FALSE������
#define WM_GV_LINKCLOSE				WM_GV + 6		///< ���������ѹرգ�����Ϣֻ���ڿͻ������ӷ������ɹ�֮�������쳣�ж�֮ʱ����
#define WM_GV_ONLINEUSER			WM_GV + 7		///< �յ���ǰ����������û���Ϣ�����뷿��󴥷�һ�Σ�wParam��INT����ʾ�����û����������Լ�����lParam��INT����ʾ����ID
#define WM_GV_FORTUNEMENU			WM_GV + 8		///< �û�ѡ����һ��Ƹ��˵��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�Ƹ��˵���ǣ�ָʾ��ѡ������һ��˵�
#define WM_GV_ROOMWAITQUEUE			WM_GV + 9		///< �û��յ���ǰ����ȴ�������Ϣ��wParam��INT����ʾ�û�ǰ��Ķ��г��ȣ�lParam��INT����ʾ��ǰ�����ܵĵȴ����г���
#define WM_GV_ENTERREQUEST			WM_GV + 10		///< �û�������뷿����Ϣ��wParam��INT����ʾ�û�ID�ţ�lParam��BOOL����ʾ���û���������루TRUE��������뿪��FALSE������ȴ�����

#define WM_GV_CAMERASTATE			WM_GV + 11		///< �û�����ͷ״̬�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ����ͷ�ĵ�ǰ״̬������Ϊ��GV_CAMERA_STATE_XXXX
#define WM_GV_CHATMODECHG			WM_GV + 12		///< �û�����ģʽ�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ����ģʽ
#define WM_GV_ACTIVESTATE			WM_GV + 13		///< �û��״̬�����仯��wParam��INT����ʾ�û�ID�ţ�lParam��INT����ʾ�û��ĵ�ǰ�״̬

#define WM_GV_PRIVATEREQUEST		WM_GV + 21		///< �û�����˽������wParam��INT����ʾ�����ߵ��û�ID�ţ�lParam��INT����ʾ˽�������ţ���ʶ������
#define WM_GV_PRIVATEECHO			WM_GV + 22		///< �û��ظ�˽������wParam��INT����ʾ�ظ��ߵ��û�ID�ţ�lParam��INT��Ϊ�������
#define WM_GV_PRIVATEEXIT			WM_GV + 23		///< �û��˳�˽�ģ�wParam��INT����ʾ�˳��ߵ��û�ID�ţ�lParam��INT��Ϊ�������

#define WM_GV_EXTENDBTNPRESS		WM_GV + 31		///< �û�������չ��ť��wParam��INT����ʾ��ť����Ӧ���û�ID�ţ�lParam��DWORD��ָʾ��ť�����½ǣ�������Ļλ��(x,y)���û��������øò�����ʾ�˵���

#endif // !defined(GV_MESSAGE_DEFINE__)
