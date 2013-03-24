
#ifndef CMD_LLK_HEAD_FILE
#define CMD_LLK_HEAD_FILE

//�����궨��-----------------------------------------------------------------------
#define KIND_ID							1									//��Ϸ I D
#define GAME_PLAYER						100									//��Ϸ����
#define GAME_NAME						TEXT("������")						//��Ϸ����
#define GAME_GENRE						(GAME_GENRE_GOLD|GAME_GENRE_MATCH)  //��Ϸ����

//-----------------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////
//�����붨��

#define		SUB_C_MODIFY_LOGIN_PASSWORD		10
#define		SUB_C_MODIFY_BANK_PASSWORD		11
#define		SUB_C_MODIFY_NICKNAME			12
#define		SUB_C_BANK						13
#define		SUB_C_TRANSFER_MONEY			14
#define		SUB_C_QUERY_TRANSFER_LOG		15
#define		SUB_C_QUERY_USERNAME			16

//��ѯ�û���
struct CMS_QueryUserName
{
	long lGameID;
};

struct CMS_Return
{
	BYTE cbErrorCode;
};

//�޸�����
struct CMD_Modify_Login_Password
{
	TCHAR								szOLDPassword[PASS_LEN];			//������
	TCHAR								szNEWPassword[PASS_LEN];			//������
};

//�޸���������
struct CMD_Modify_Bank_Password
{
	TCHAR								szOLDPassword[PASS_LEN];			//����������
	TCHAR								szNEWPassword[PASS_LEN];			//����������
};

//�޸��ǳ�
struct CMD_Modify_Nickname
{
	TCHAR								szNickname[NAME_LEN];			//���ǳ�
};

//�޸��ǳ�
struct CMD_Transfer_Money
{
	__int64								sfMoneyNumber;
	DWORD								dwUserID;						//�Է���ID��
	TCHAR								szAccount[NAME_LEN];			//���ǳ�
};


#endif //CMD_LLK_HEAD_FILE