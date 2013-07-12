#ifndef DATA_BASE_PACKET_HEAD_FILE
#define DATA_BASE_PACKET_HEAD_FILE

//////////////////////////////////////////////////////////////////////////////////
//�������ݰ�

//�û��¼�
#define	DBR_GR_LOGON_USERID			100									//I D ��¼
#define	DBR_GR_LOGON_MOBILE			101									//�ֻ���¼
#define	DBR_GR_LOGON_ACCOUNTS		102									//�ʺŵ�¼

//ϵͳ�¼�
#define DBR_GR_WRITE_GAME_SCORE		200									//��Ϸ����
#define DBR_GR_LEAVE_GAME_SERVER	201									//�뿪����
#define DBR_GR_GAME_SCORE_RECORD	202									//���ּ�¼
#define DBR_GR_MANAGE_USER_RIGHT	203									//Ȩ�޹���
#define DBR_GR_LOAD_SYSTEM_MESSAGE	204									//ϵͳ��Ϣ

//�����¼�
#define DBR_GR_LOAD_PARAMETER		300									//���ز���
#define DBR_GR_LOAD_GAME_COLUMN		301									//�����б�
#define DBR_GR_LOAD_ANDROID_USER	302									//���ػ���
#define DBR_GR_LOAD_GAME_PROPERTY	303									//���ص���

//�����¼�
#define DBR_GR_USER_SAVE_SCORE		400									//������Ϸ��
#define DBR_GR_USER_TAKE_SCORE		401									//��ȡ��Ϸ��
#define DBR_GR_USER_TRANSFER_SCORE	402									//ת����Ϸ��
#define DBR_GR_QUERY_INSURE_INFO	403									//��ѯ����
#define DBR_GR_QUERY_TRANSFER_USER_INFO	    404							//��ѯ�û�

//��Ϸ�¼�
#define DBR_GR_PROPERTY_REQUEST		500									//��������
#define DBR_GR_GAME_FRAME_REQUEST	502									//��Ϸ����

//�����¼�
#define DBR_GR_MATCH_FEE			600									//��������
#define DBR_GR_MATCH_START			601									//������ʼ
#define DBR_GR_MATCH_OVER			602									//��������
#define DBR_GR_MATCH_REWARD			603									//��������
#define DBR_GR_MATCH_QUIT			604									//�˳�����

//////////////////////////////////////////////////////////////////////////////////
//�����Ϣ

//�߼��¼�
#define DBO_GR_LOGON_SUCCESS		100									//��¼�ɹ�
#define DBO_GR_LOGON_FAILURE		101									//��¼ʧ��

//�����¼�
#define DBO_GR_GAME_PARAMETER		200									//������Ϣ
#define DBO_GR_GAME_COLUMN_INFO		201									//�б���Ϣ
#define DBR_GR_GAME_ANDROID_INFO	202									//������Ϣ
#define DBO_GR_GAME_PROPERTY_INFO	203									//������Ϣ

//��������
#define DBO_GR_USER_INSURE_INFO		300									//��������
#define DBO_GR_USER_INSURE_SUCCESS	301									//���гɹ�
#define DBO_GR_USER_INSURE_FAILURE	302									//����ʧ��
#define DBO_GR_USER_INSURE_USER_INFO   303								//�û�����

//��Ϸ�¼�
#define DBO_GR_PROPERTY_SUCCESS		400									//���߳ɹ�
#define DBO_GR_PROPERTY_FAILURE		401									//����ʧ��
#define DBO_GR_GAME_FRAME_RESULT	402									//��Ϸ���

//�����¼�
#define DBO_GR_MATCH_EVENT_START	500									//�¼���Χ
#define DBO_GR_MATCH_EVENT_END		599									//�¼���Χ
#define DBO_GR_MATCH_FEE_RESULT		500									//��������
#define DBO_GR_MATCH_RANK			501									//��������
#define DBO_GR_MATCH_QUIT_RESULT	502									//�������

//ϵͳ�¼�
#define DBO_GR_SYSTEM_MESSAGE_RESULT	600									//��Ϣ���

//////////////////////////////////////////////////////////////////////////////////

//ID ��¼
struct DBR_GR_LogonUserID
{		
	//��¼��Ϣ
	DWORD							dwUserID;							//�û� I D
	TCHAR							szPassword[LEN_MD5];				//��¼����

	//������Ϣ
	DWORD							dwClientAddr;						//���ӵ�ַ
	TCHAR							szMachineID[LEN_MACHINE_ID];		//������ʶ
};

//ID ��¼
struct DBR_GR_LogonMobile
{		
	//��¼��Ϣ
	DWORD							dwUserID;							//�û� I D
	TCHAR							szPassword[LEN_MD5];				//��¼����
	BYTE                            cbDeviceType;                       //�豸����
	WORD                            wBehaviorFlags;                     //��Ϊ��ʶ
	WORD                            wPageTableCount;                    //��ҳ����

	//������Ϣ
	DWORD							dwClientAddr;						//���ӵ�ַ
	TCHAR							szMachineID[LEN_MACHINE_ID];		//������ʶ
};

//�ʺŵ�¼
struct DBR_GR_LogonAccounts
{
	//��¼��Ϣ
	TCHAR							szPassword[LEN_MD5];				//��¼����
	TCHAR							szAccounts[LEN_ACCOUNTS];			//��¼�ʺ�

	//������Ϣ
	DWORD							dwClientAddr;						//���ӵ�ַ
	TCHAR							szMachineID[LEN_MACHINE_ID];		//������ʶ
};

//��Ϸ����
struct DBR_GR_WriteGameScore
{
	//�û���Ϣ
	DWORD							dwUserID;							//�û���ʶ
	DWORD							dwClientAddr;						//���ӵ�ַ

	//�û���Ϣ
	DWORD							dwDBQuestID;						//�����ʶ
	DWORD							dwInoutIndex;						//��������

	//�ɼ�����
	tagVariationInfo				VariationInfo;						//��ȡ��Ϣ
};

//�뿪����
struct DBR_GR_LeaveGameServer
{
	//�û���Ϣ
	DWORD							dwUserID;							//�û���ʶ
	DWORD							dwInoutIndex;						//��¼����
	DWORD							dwLeaveReason;						//�뿪ԭ��
	DWORD							dwOnLineTimeCount;					//����ʱ��

	//�ɼ�����
	tagVariationInfo				RecordInfo;							//��¼��Ϣ
	tagVariationInfo				VariationInfo;						//��ȡ��Ϣ

	//ϵͳ��Ϣ
	DWORD							dwClientAddr;						//���ӵ�ַ
	TCHAR							szMachineID[LEN_MACHINE_ID];		//������ʶ
};

//��Ϸ��¼
struct DBR_GR_GameScoreRecord
{
	//������Ϣ
	WORD							wTableID;							//���Ӻ���
	WORD							wUserCount;							//�û���Ŀ
	WORD							wAndroidCount;						//������Ŀ

	//���˰��
	SCORE							lWasteCount;						//�����Ŀ
	SCORE							lRevenueCount;						//˰����Ŀ

	//ͳ����Ϣ
	DWORD							dwUserMemal;						//������Ŀ
	DWORD							dwPlayTimeCount;					//��Ϸʱ��

	//ʱ����Ϣ
	SYSTEMTIME						SystemTimeStart;					//��ʼʱ��
	SYSTEMTIME						SystemTimeConclude;					//����ʱ��

	//���ּ�¼
	WORD							wRecordCount;						//��¼��Ŀ
	tagGameScoreRecord				GameScoreRecord[MAX_CHAIR];			//��Ϸ��¼
};

//������Ϸ��
struct DBR_GR_UserSaveScore
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	DWORD							dwUserID;							//�û� I D
	SCORE							lSaveScore;							//������Ϸ��
	DWORD							dwClientAddr;						//���ӵ�ַ
	TCHAR							szMachineID[LEN_MACHINE_ID];		//��������
};

//ȡ����Ϸ��
struct DBR_GR_UserTakeScore
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	DWORD							dwUserID;							//�û� I D
	SCORE							lTakeScore;							//��ȡ��Ϸ��
	DWORD							dwClientAddr;						//���ӵ�ַ
	TCHAR							szPassword[LEN_PASSWORD];			//��������
	TCHAR							szMachineID[LEN_MACHINE_ID];		//��������
};

//ת����Ϸ��
struct DBR_GR_UserTransferScore
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	DWORD							dwUserID;							//�û� I D
	DWORD							dwClientAddr;						//���ӵ�ַ
	BYTE                            cbByNickName;                       //�ǳ�����
	SCORE							lTransferScore;						//ת����Ϸ��
	TCHAR							szNickName[LEN_NICKNAME];			//Ŀ���û�
	TCHAR							szPassword[LEN_PASSWORD];			//��������
	TCHAR							szMachineID[LEN_MACHINE_ID];		//��������
};

//��ѯ����
struct DBR_GR_QueryInsureInfo
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	DWORD							dwUserID;							//�û� I D
	DWORD							dwClientAddr;						//���ӵ�ַ
};

//��ѯ�û�
struct DBR_GR_QueryTransferUserInfo
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	BYTE                            cbByNickName;                       //�ǳ�����
	TCHAR							szNickName[LEN_NICKNAME];			//Ŀ���û�
};

//��������
struct DBR_GR_PropertyRequest
{
	//������Ϣ
	WORD							wItemCount;							//������Ŀ
	WORD							wPropertyIndex;						//��������
	DWORD							dwSourceUserID;						//�������
	DWORD							dwTargetUserID;						//ʹ�ö���

	//����ģʽ
	BYTE                            cbRequestArea;			            //ʹ�÷�Χ 
	BYTE							cbConsumeScore;						//��������
	SCORE							lFrozenedScore;						//�������

	//�û�Ȩ��
	DWORD                           dwUserRight;						//��ԱȨ��

	//ϵͳ��Ϣ
	WORD							wTableID;							//���Ӻ���
	DWORD							dwInoutIndex;						//�����ʶ
	DWORD							dwClientAddr;						//���ӵ�ַ
	TCHAR							szMachineID[LEN_MACHINE_ID];		//��������
};

//////////////////////////////////////////////////////////////////////////////////

//��¼�ɹ�
struct DBO_GR_LogonSuccess
{
	//��������
	WORD							wFaceID;							//ͷ���ʶ
	DWORD							dwUserID;							//�û� I D
	DWORD							dwGameID;							//��Ϸ I D
	DWORD							dwGroupID;							//���� I D
	DWORD							dwCustomID;							//�Զ�ͷ��
	TCHAR							szNickName[LEN_NICKNAME];			//�ʺ��ǳ�
	TCHAR							szGroupName[LEN_GROUP_NAME];		//��������

	//�û�����
	BYTE							cbGender;							//�û��Ա�
	BYTE							cbMemberOrder;						//��Ա�ȼ�
	BYTE							cbMasterOrder;						//����ȼ�
	TCHAR							szUnderWrite[LEN_UNDER_WRITE];		//����ǩ��

	//������Ϣ
	SCORE							lScore;								//�û�����
	SCORE							lGrade;								//�û��ɼ�
	SCORE							lInsure;							//�û�����

	//��Ϸ��Ϣ
	DWORD							dwWinCount;							//ʤ������
	DWORD							dwLostCount;						//ʧ������
	DWORD							dwDrawCount;						//�;�����
	DWORD							dwFleeCount;						//��������
	DWORD							dwUserMedal;						//�û�����
	DWORD							dwExperience;						//�û�����
	LONG							lLoveLiness;						//�û�����

	//�û�Ȩ��
	DWORD							dwUserRight;						//�û�Ȩ��
	DWORD							dwMasterRight;						//����Ȩ��

	//��������
	DWORD							dwInoutIndex;						//��¼����
	TCHAR							szMachineID[LEN_MACHINE_ID];		//������ʶ

	//�ֻ�����
	BYTE                            cbDeviceType;                       //�豸����
	WORD                            wBehaviorFlags;                     //��Ϊ��ʶ
	WORD                            wPageTableCount;                    //��ҳ����

	//������Ϣ
	TCHAR							szPassword[LEN_MD5];				//��¼����
	TCHAR							szDescribeString[128];				//������Ϣ
};

//��¼ʧ��
struct DBO_GR_LogonFailure
{
	LONG							lResultCode;						//�������
	TCHAR							szDescribeString[128];				//������Ϣ
};

//������Ϣ
struct DBO_GR_GameParameter
{
	//������Ϣ
	WORD							wMedalRate;							//���ƻ���
	WORD							wRevenueRate;						//����˰��

	//�汾��Ϣ
	DWORD							dwClientVersion;					//�ͻ��汾
	DWORD							dwServerVersion;					//����汾
};

//�б���Ϣ
struct DBO_GR_GameColumnInfo
{
	LONG							lResultCode;						//�������
	BYTE							cbColumnCount;						//�б���Ŀ
	tagColumnItem					ColumnItemInfo[MAX_COLUMN];			//�б���Ϣ
};

//������Ϣ
struct DBO_GR_GameAndroidInfo
{
	LONG							lResultCode;						//�������
	WORD							wAndroidCount;						//�û���Ŀ
	tagAndroidParameter				AndroidParameter[MAX_ANDROID];		//������Ϣ
};

//������Ϣ
struct DBO_GR_GamePropertyInfo
{
	LONG							lResultCode;						//�������
	BYTE							cbPropertyCount;					//������Ŀ
	tagPropertyInfo					PropertyInfo[MAX_PROPERTY];			//������Ϣ
};

//��������
struct DBO_GR_UserInsureInfo
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	WORD							wRevenueTake;						//˰�ձ���
	WORD							wRevenueTransfer;					//˰�ձ���
	WORD							wServerID;							//�����ʶ
	SCORE							lUserScore;							//�û���Ϸ��
	SCORE							lUserInsure;						//������Ϸ��
	SCORE							lTransferPrerequisite;				//ת������
};

//���гɹ�
struct DBO_GR_UserInsureSuccess
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	DWORD							dwUserID;							//�û� I D
	SCORE							lSourceScore;						//ԭ����Ϸ��
	SCORE							lSourceInsure;						//ԭ����Ϸ��
	SCORE							lInsureRevenue;						//����˰��
	SCORE							lFrozenedScore;						//�������
	SCORE							lVariationScore;					//��Ϸ�ұ仯
	SCORE							lVariationInsure;					//���б仯
	TCHAR							szDescribeString[128];				//������Ϣ
};

//����ʧ��
struct DBO_GR_UserInsureFailure
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	LONG							lResultCode;						//��������
	SCORE							lFrozenedScore;						//�������
	TCHAR							szDescribeString[128];				//������Ϣ
};

//�û�����
struct DBO_GR_UserTransferUserInfo
{
	BYTE                            cbActivityGame;                     //��Ϸ����
	DWORD							dwGameID;							//�û� I D
	TCHAR							szNickName[LEN_NICKNAME];			//�ʺ��ǳ�
};

//���߳ɹ�
struct DBO_GR_S_PropertySuccess
{
	//������Ϣ
	WORD							wItemCount;							//������Ŀ
	WORD							wPropertyIndex;						//��������
	DWORD							dwSourceUserID;						//�������
	DWORD							dwTargetUserID;						//ʹ�ö���

	//����ģʽ
	BYTE                            cbRequestArea;						//����Χ
	BYTE							cbConsumeScore;						//��������
	SCORE							lFrozenedScore;						//�������

	//��ԱȨ��
	DWORD                           dwUserRight;						//��ԱȨ��

	//�����Ϣ
	SCORE							lConsumeGold;						//������Ϸ��
	LONG							lSendLoveLiness;					//��������
	LONG							lRecvLoveLiness;					//��������

	//��Ա��Ϣ
	BYTE							cbMemberOrder;						//��Ա�ȼ�
};

//����ʧ��
struct DBO_GR_PropertyFailure
{
	BYTE                            cbRequestArea;						//����Χ
	LONG							lResultCode;						//��������
	SCORE							lFrozenedScore;						//�������
	TCHAR							szDescribeString[128];				//������Ϣ
};

//��������
struct DBO_GR_MatchRank
{
	BYTE							cbRank;								//��������
	TCHAR							szNickName[LEN_NICKNAME];			//�û��ǳ�
	LONG							lMatchScore;						//�û��÷�
};

//Ȩ�޹���
struct DBR_GR_ManageUserRight
{
	DWORD							dwUserID;							//Ŀ���û�
	DWORD							dwAddRight;							//���Ȩ��
	DWORD							dwRemoveRight;						//ɾ��Ȩ��
	bool							bGameRight;							//��ϷȨ��
};

//��������
struct DBR_GR_MatchFee
{
	//��������
	DWORD							dwUserID;							//�û�ID
	DWORD							dwMatchFee;							//��������

	//ϵͳ��Ϣ
	DWORD							dwInoutIndex;						//�����ʶ
	DWORD							dwClientAddr;						//���ӵ�ַ
	DWORD							dwMatchID;							//����ID
	DWORD							dwMatchNO;							//��������
	TCHAR							szMachineID[LEN_MACHINE_ID];		//��������
};

//������ʼ
struct DBR_GR_MatchStart
{
	DWORD							dwMatchID;						//������ʶ
	DWORD							dwMatchNo;						//��������
	WORD							wMatchCount;					//�ܳ���
	LONG							lInitScore;						//��ʼ����
};

//��������
struct DBR_GR_MatchOver
{
	DWORD							dwMatchID;						//������ʶ
	DWORD							dwMatchNo;						//��������
	WORD							wMatchCount;					//�ܳ���
};

//��������
struct DBR_GR_MatchReward
{
	DWORD								dwUserID;							//�û� I D
	DWORD								dwMatchID;							//���� I D 
	DWORD								dwMatchNO;							//��������
	WORD								wRank;								//��������
	SCORE								lMatchScore;						//�����÷�
	DWORD								dwExperience;						//�û�����
	DWORD								dwGold;								//��Ϸ��
	DWORD								dwMedal;							//�û�����
	DWORD								dwClientAddr;						//���ӵ�ַ
};

//ϵͳ��Ϣ
struct DBR_GR_SystemMessage
{
	BYTE                            cbMessageID;                        //��ϢID
	BYTE							cbMessageType;						//��Ϣ����
	BYTE                            cbAllRoom;                          //ȫ�巿��
	DWORD							dwTimeRate;						    //ʱ��Ƶ��
	TCHAR							szSystemMessage[LEN_USER_CHAT];		//ϵͳ��Ϣ
};
//////////////////////////////////////////////////////////////////////////////////

#endif