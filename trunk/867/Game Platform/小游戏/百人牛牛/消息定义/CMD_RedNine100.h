#ifndef CMD_BACCARAT_HEAD_FILE
#define CMD_BACCARAT_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//�����궨��

#define KIND_ID						104									//��Ϸ I D
#define GAME_PLAYER					100									//��Ϸ����
#define GAME_NAME					TEXT("����ţţ")					//��Ϸ����

//״̬����
#define	GS_PLACE_JETTON				GS_PLAYING							//��ע״̬
#define	GS_GAME_END					GS_PLAYING+1						//����״̬
#define	GS_MOVECARD_END				GS_PLAYING+2						//����״̬

//��������
//#define ID_SHUN_MEN					1									//˳��
//#define ID_DUI_MEN					2									//����
//#define ID_DAO_MEN					3									//����
//#define ID_JIAO_L					4									//��߽�
//#define ID_QIAO						5									//��
//#define ID_JIAO_R					6									//�ұ߽�

#define ID_TIAN_MEN					1									//˳��
#define ID_DI_MEN					2									//��߽�
#define ID_XUAN_MEN					3									//��
#define ID_HUANG_MEN				4									//����

//�������
#define BANKER_INDEX				0									//ׯ������
#define SHUN_MEN_INDEX				1									//˳������
#define DUI_MEN_INDEX				2									//��������
#define DAO_MEN_INDEX				3									//��������
#define HUAN_MEN_INDEX				4									//��������

#define AREA_COUNT					4									//������Ŀ

//���ʶ���
#define RATE_TWO_PAIR				12									//��������

//��¼��Ϣ
struct tagServerGameRecord
{
	bool							bWinShunMen;						//˳��ʤ��
	bool							bWinDuiMen;							//����ʤ��
	bool							bWinDaoMen;							//����ʤ��
	bool							bWinHuang;							//����ʤ��
};

//////////////////////////////////////////////////////////////////////////
//����������ṹ

#define SUB_S_GAME_FREE				99									//��Ϸ����
#define SUB_S_GAME_START			100									//��Ϸ��ʼ
#define SUB_S_PLACE_JETTON			101									//�û���ע
#define SUB_S_GAME_END				102									//��Ϸ����
#define SUB_S_APPLY_BANKER			103									//����ׯ��
#define SUB_S_CHANGE_BANKER			104									//�л�ׯ��
#define SUB_S_CHANGE_USER_SCORE		105									//���»���
#define SUB_S_SEND_RECORD			106									//��Ϸ��¼
#define SUB_S_PLACE_JETTON_FAIL		107									//��עʧ��
#define SUB_S_CANCEL_BANKER			108									//ȡ������


//ʧ�ܽṹ
struct CMD_S_PlaceJettonFail
{
	WORD							wPlaceUser;							//��ע���
	BYTE							lJettonArea;						//��ע����
	LONG							lPlaceScore;						//��ǰ��ע
};

//���»���
struct CMD_S_ChangeUserScore
{
	WORD							wChairID;							//���Ӻ���
	DOUBLE							lScore;								//��һ���

	//ׯ����Ϣ
	WORD							wCurrentBankerChairID;				//��ǰׯ��
	BYTE							cbBankerTime;						//ׯ�Ҿ���
	DOUBLE							lCurrentBankerScore;				//ׯ�ҷ���
};

//����ׯ��
struct CMD_S_ApplyBanker
{
	WORD							wApplyUser;							//�������
};

//ȡ������
struct CMD_S_CancelBanker
{
	TCHAR							szCancelUser[32];					//ȡ�����
};

//�л�ׯ��
struct CMD_S_ChangeBanker
{
	WORD							wBankerUser;						//��ׯ���
	LONG							lBankerScore;						//ׯ�ҽ��
};

//��Ϸ״̬
struct CMD_S_StatusFree
{
	//ȫ����Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��

	//�����Ϣ
	LONG							lUserMaxScore;							//��ҽ��

	//ׯ����Ϣ
	WORD							wBankerUser;						//��ǰׯ��
	WORD							cbBankerTime;						//ׯ�Ҿ���
	LONG							lBankerWinScore;					//ׯ�ҳɼ�
	LONG							lBankerScore;						//ׯ�ҷ���
	bool							bEnableSysBanker;					//ϵͳ��ׯ

	//������Ϣ
	LONG							lApplyBankerCondition;				//��������
	LONG							lAreaLimitScore;					//��������
};

//��Ϸ״̬
struct CMD_S_StatusPlay
{
	//ȫ����ע
	LONG							lAllJettonScore[AREA_COUNT+1];		//ȫ����ע

	//�����ע
	LONG							lUserJettonScore[AREA_COUNT+1];		//������ע

	//��һ���
	LONG							lUserMaxScore;						//�����ע							

	//������Ϣ
	LONG							lApplyBankerCondition;				//��������
	LONG							lAreaLimitScore;					//��������

	//�˿���Ϣ
	BYTE							cbTableCardArray[5][5];				//�����˿�

	//ׯ����Ϣ
	WORD							wBankerUser;						//��ǰׯ��
	WORD							cbBankerTime;						//ׯ�Ҿ���
	LONG							lBankerWinScore;					//ׯ��Ӯ��
	LONG							lBankerScore;						//ׯ�ҷ���
	bool							bEnableSysBanker;					//ϵͳ��ׯ

	//������Ϣ
	LONG							lEndBankerScore;					//ׯ�ҳɼ�
	LONG							lEndUserScore;						//��ҳɼ�
	LONG							lEndUserReturnScore;				//���ػ���
	LONG							lEndRevenue;						//��Ϸ˰��

	//ȫ����Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	BYTE							cbGameStatus;						//��Ϸ״̬
};

//��Ϸ����
struct CMD_S_GameFree
{
	BYTE							cbTimeLeave;						//ʣ��ʱ��
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	WORD							wBankerUser;						//ׯ��λ��
	LONG							lBankerScore;						//ׯ�ҽ��
	LONG							lUserMaxScore;						//�ҵĽ��
	BYTE							cbTimeLeave;						//ʣ��ʱ��	
	bool							bContiueCard;						//��������
};

//�û���ע
struct CMD_S_PlaceJetton
{
	WORD							wChairID;							//�û�λ��
	BYTE							cbJettonArea;						//��������
	LONG							lJettonScore;						//��ע��Ŀ
};

//��Ϸ����
struct CMD_S_GameEnd
{
	//�¾���Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��

	//�˿���Ϣ
	BYTE							cbTableCardArray[5][5];				//�����˿�
	BYTE							cbLeftCardCount;					//�˿���Ŀ

	BYTE							bcFirstCard;
 
	//ׯ����Ϣ
	LONG							lBankerScore;						//ׯ�ҳɼ�
	LONG							lBankerTotallScore;					//ׯ�ҳɼ�
	INT								nBankerTime;						//��ׯ����

	//��ҳɼ�
	LONG							lUserScore;							//��ҳɼ�
	LONG							lUserReturnScore;					//���ػ���

	//ȫ����Ϣ
	LONG							lRevenue;							//��Ϸ˰��
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_PLACE_JETTON			1									//�û���ע
#define SUB_C_APPLY_BANKER			2									//����ׯ��
#define SUB_C_CANCEL_BANKER			3									//ȡ������
#define SUB_C_CONTINUE_CARD			4									//��������

//�û���ע
struct CMD_C_PlaceJetton
{
	BYTE							cbJettonArea;						//��������
	LONG							lJettonScore;						//��ע��Ŀ
};

//////////////////////////////////////////////////////////////////////////

#endif
