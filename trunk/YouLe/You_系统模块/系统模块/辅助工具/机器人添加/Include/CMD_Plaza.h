#ifndef CMD_PLAZA_HEAD_FILE
#define CMD_PLAZA_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//�㳡�汾
#define VER_PLAZA_LOW					1								//�㳡�汾
#define VER_PLAZA_HIGH					1								//�㳡�汾
#define VER_PLAZA_FRAME					MAKELONG(VER_PLAZA_LOW,VER_PLAZA_HIGH)

//////////////////////////////////////////////////////////////////////////
//��¼�����ʶ

#define ERC_GP_LOGON_SUCCESS			0								//��½�ɹ�
#define ERC_GP_ACCOUNTS_NOT_EXIST		1								//�ʺŲ�����
#define ERC_GP_LONG_NULLITY				2								//��ֹ��¼
#define ERC_GP_PASSWORD_ERCOR			3								//�������

//////////////////////////////////////////////////////////////////////////
//��¼������

#define MDM_GP_LOGON					1								//�㳡��¼

#define SUB_GP_LOGON_ACCOUNTS			1								//�ʺŵ�¼
#define SUB_GP_LOGON_USERID				2								//I D ��¼
#define SUB_GP_REGISTER_ACCOUNTS		3								//ע���ʺ�

#define SUB_GP_LOGON_SUCCESS			100								//��½�ɹ�
#define SUB_GP_LOGON_ERROR				101								//��½ʧ��
#define SUB_GP_LOGON_FINISH				102								//��½���

//�ʺŵ�¼
struct CMD_GP_LogonByAccounts
{
	DWORD								dwPlazaVersion;					//�㳡�汾
	TCHAR								szAccounts[NAME_LEN];			//��¼�ʺ�
	TCHAR								szPassWord[PASS_LEN];			//��¼����
	TCHAR								szRealityPass[PASS_LEN];		//��ʵ����
};

//I D ��¼
struct CMD_GP_LogonByUserID
{
	DWORD								dwPlazaVersion;					//�㳡�汾
	DWORD								dwUserID;						//�û� I D
	TCHAR								szPassWord[PASS_LEN];			//��¼����
};

//ע���ʺ�
struct CMD_GP_RegisterAccounts
{
	WORD								wFaceID;						//ͷ���ʶ
	DWORD								dwPlazaVersion;					//�㳡�汾
	TCHAR								szAccounts[NAME_LEN];			//��¼�ʺ�
	TCHAR								szPassWord[PASS_LEN];			//��¼����
};

//��½�ɹ�
struct CMD_GP_LogonSuccess
{
	BYTE								cbGender;						//�û��Ա�
	BYTE								cbMember;						//��Ա�ȼ�
	WORD								wFaceID;						//ͷ������
	DWORD								dwUserID;						//�û� I D
	DWORD								dwGroupID;						//��������
	DWORD								dwExperience;					//�û�����
	DWORD								dwUserRight;					//�û��ȼ�
	DWORD								dwMasterRight;					//����Ȩ��
};

//��½ʧ��
struct CMD_GP_LogonError
{
	LONG								lErrorCode;						//�������
	TCHAR								szErrorDescribe[128];			//������Ϣ
};

//////////////////////////////////////////////////////////////////////////
//��Ϸ�б�������

#define MDM_GP_SERVER_LIST				2								//�б���Ϣ

#define SUB_GP_LIST_TYPE				100								//�����б�
#define SUB_GP_LIST_KIND				101								//�����б�
#define SUB_GP_LIST_STATION				102								//վ���б�
#define SUB_GP_LIST_SERVER				103								//�����б�
#define SUB_GP_LIST_FINISH				104								//�������
#define SUB_GP_LIST_CONFIG				105								//�б�����

#define SUB_GP_LIST_PROCESS				106								//�����б�

//�б�����
struct CMD_GP_ListConfig
{
	BYTE								bShowOnLineCount;				//��ʾ����
};

//////////////////////////////////////////////////////////////////////////
//ϵͳ������

#define MDM_GP_SYSTEM					3								//ϵͳ����

#define SUB_GP_VERSION					100								//�汾֪ͨ
#define SUB_SP_SYSTEM_MSG				101								//ϵͳ��Ϣ

//�汾֪ͨ
struct CMD_GP_Version
{
	BYTE								bNewVersion;					//���°汾
	BYTE								bAllowConnect;					//��������
};

//////////////////////////////////////////////////////////////////////////

#endif