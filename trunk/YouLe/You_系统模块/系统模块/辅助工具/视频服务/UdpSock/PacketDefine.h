#pragma once

//���
#define PACKET_LOGIN		0x0003 //��½
#define PACKET_LOGIN_OK		0x0103 //��½ok
#define PACKET_LOGIN_ERR	0x0403 //���ش���
#define PACKET_QUIT			0x0503 //�˳�
#define PACKET_ADDCLIENT	0x0203 //��ӿͻ���
#define PACKET_USER_CONNECT	0x0303 //�û������½
#define PACKET_USER_CONNECT_OK	0x0603 //ȷ������
#define PACKET_USER_VEDIO	0x0104 //��Ƶ��
#define PACKET_USER_VEDIO_OK	0x0204 //��Ƶ�����
#define PACKET_USER_VEDIO_NEW	0x0304 //����Ƶ
#define PACKET_USER_GET_NEW_VEDIO	0x0404 //����Ƶ�����
#define PACKET_USER_GET_VEDIO 0x0504 //������Ƶ
#define PACKET_USER_VEDIO_ERR 0x0604 //��Ƶ����
#define PACKET_USER_SOUND	0x0105 //������
#define PACKET_USER_SOUND_OK	0x0205 //�������
#define PACKET_USER_SOUND_NEXT	0x0305 //����ȷ��
#define PACKET_USER_GET_SOUND 0x0405 //ȡȱ�ٵ�������
#define PACKET_USER_SOUND_ERR 0x0505 //������

//����IP
#define PACKET_SWAP_CONNECT	0x0102 //�û������½