#if !defined(ANYCHAT_ERROR_CODE_DEFINE_)
#define ANYCHAT_ERROR_CODE_DEFINE_

#pragma once

#define GV_ERR_SUCCESS			0		///< �ɹ�

#define GV_ERR_DB_ERROR			1		///< ���ݿ����
#define GV_ERR_NOTINIT			2		///< ϵͳû�г�ʼ��
#define	GV_ERR_NOTINROOM		3		///< ��δ���뷿��

#define GV_ERR_FUNCNOTALLOW		20		///< �������ܲ�����

//���Ӳ���
#define GV_ERR_CONNECT_TIMEOUT	100		///< ���ӷ�������ʱ
#define GV_ERR_CONNECT_ABORT	101		///< ��������������ж�
#define GV_ERR_CONNECT_AUTHFAIL	102		///< δ��ͨ������������֤�����ڷǷ�����

//��¼����
#define GV_ERR_CERTIFY_FAIL		200		///< ��֤ʧ�ܣ��û�������������
#define GV_ERR_ALREADY_LOGIN	201		///< ���û��ѵ�¼
#define GV_ERR_ACCOUNT_LOCK		202		///< �ʻ��ѱ���ʱ����
#define GV_ERR_IPADDR_LOCK		203		///< IP��ַ�ѱ���ʱ����
#define GV_ERR_VISITOR_DENY		204		///< �ο͵�¼����ֹ����¼ʱû���������룩


//���뷿��
#define GV_ERR_ROOM_LOCK		300		///< �����ѱ���ס����ֹ����
#define GV_ERR_ROOM_PASSERR		301		///< ����������󣬽�ֹ����
#define GV_ERR_ROOM_FULLUSER	302		///< ��������Ա�����ܽ���
#define GV_ERR_ROOM_INVALID		303		///< ���䲻����
#define GV_ERR_ROOM_EXPIRE		304		///< �������ʱ���ѵ���
#define GV_ERR_ROOM_REJECT		305		///< �����ܾ�����
#define GV_ERR_ROOM_OWNERBEOUT	306		///< �������ڣ����ܽ��뷿��
#define GV_ERR_ROOM_ENTERFAIL	307		///< ���ܽ��뷿��
#define GV_ERR_ROOM_ALREADIN	308		///< �Ѿ��ڷ��������ˣ����ν��뷿���������


//˽��
#define GV_ERR_ROOM_PRINULL		401		///< �û��Ѿ��뿪����
#define GV_ERR_ROOM_REJECTPRI	402		///< �û��ܾ���˽������
#define GV_ERR_ROOM_PRIDENY		403		///< ����������û�˽�ģ������û���ֹ˽��

#define GV_ERR_ROOM_PRIREQIDERR	420		///< ˽������ID�Ŵ��󣬻����󲻴���
#define GV_ERR_ROOM_PRIALRCHAT	421		///< �Ѿ���˽���б���

#define GV_ERR_ROOM_PRITIMEOUT	431		///< ˽������ʱ
#define GV_ERR_ROOM_PRICHATBUSY	432		///< �Է�����˽���У���æ״̬

//Mic����Ȩ
#define	GV_ERR_MICLOSE_TIMEOUT	500		///< ˵��ʱ��̫��������Ϣһ��
#define GV_ERR_MICLOSE_HIGHUSER	501		///< �и߼����û���Ҫ���ԣ�����Ϣһ��


//�޸��ǳ�
#define GV_ERR_NAMECHG_ONUSE	600		///< ���ǳ��ѱ�ʹ�ã��뻻���������ǳ�


#endif