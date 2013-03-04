#ifndef CMD_BACCARAT_HEAD_FILE
#define CMD_BACCARAT_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//�����궨��

#define KIND_ID						PAIJIU_KIND_ID						//��Ϸ I D
#define GAME_PLAYER					100									//��Ϸ����
#define GAME_NAME					TEXT("�ƾ�")						//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_GOLD|GAME_GENRE_MATCH)	//��Ϸ����

#define BANK_CONDITION_MONEY		1000

//�������

#define ID_SHUN_MEN					0x01	
#define ID_TIAN_MEN					0x02
#define ID_DAO_MEN					0x04
#define ID_ZUO_JIAO					0x08
#define ID_YOU_JIAO					0x10
#define ID_QIAO						0x20
#define ID_QUAN_SHU					0x40									//ȫ��

//��¼��Ϣ
struct tagServerGameRecord
{
	WORD							wWinner;							//ʤ�����
	__int64							lTieScore;							//��ƽ��ע
	__int64							lBankerScore;						//��ׯ��ע
	__int64							lPlayerScore;						//������ע
	BYTE							cbPlayerCount;						//�мҵ���
	BYTE							cbBankerCount;						//ׯ�ҵ���
};

//////////////////////////////////////////////////////////////////////////
//����������ṹ

#define SUB_S_GAME_START			100									//��Ϸ��ʼ
#define SUB_S_PLACE_JETTON			101									//�û���ע
#define SUB_S_GAME_END				102									//��Ϸ����
#define SUB_S_APPLY_BANKER			103									//����ׯ��
#define SUB_S_CHANGE_BANKER			104									//�л�ׯ��
#define SUB_S_CHANGE_USER_SCORE		105									//���»���
#define SUB_S_SEND_RECORD			106									//��Ϸ��¼
#define SUB_S_PLACE_JETTON_FAIL		107									//��עʧ��
#define SUB_S_GAME_SCORE			108									//���ͻ���

//ʧ�ܽṹ
struct CMD_S_PlaceJettonFail
{
	__int64							lJettonArea;						//��ע����
	__int64							lPlaceScore;						//��ǰ��ע
	__int64							lMaxLimitScore;						//���ƴ�С
	__int64							lFinishPlaceScore;					//����ע��
};

//���»���
struct CMD_S_ChangeUserScore
{
	WORD							wChairID;							//���Ӻ���
	__int64							lScore;								//��һ���

	//ׯ����Ϣ
	WORD							wCurrentBankerChairID;				//��ǰׯ��
	BYTE							cbBankerTime;						//ׯ�Ҿ���
	__int64							lCurrentBankerScore;				//ׯ�ҷ���
};

//����ׯ��
struct CMD_S_ApplyBanker
{
	CHAR							szAccount[ 32 ];					//�������
	__int64							lScore;								//��ҽ��
	bool							bApplyBanker;						//�����ʶ
};

//�л�ׯ��
struct CMD_S_ChangeBanker
{
	WORD							wChairID;							//���Ӻ���
	BYTE							cbBankerTime;						//ׯ�Ҿ���
	__int64							lBankerScore;						//ׯ�ҷ���
	__int64							lBankerTreasure;					//ׯ�ҽ��
};

//��Ϸ״̬
struct CMD_S_StatusFree
{
	//ȫ����Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	__int64							lCellScore;							//���Ԫ��ע

	//��ע��Ϣ
	__int64							lTieScore;							//��ƽ��ע
	__int64							lBankerScore;						//��ׯ��ע
	__int64							lPlayerScore;						//������ע
	__int64							lTieSamePointScore;					//ͬ��ƽע
	__int64							lPlayerKingScore;					//������ע
	__int64							lBankerKingScore;					//ׯ����ע

	//�ҵ���ע
	__int64							lMeMaxScore;						//�����ע
	__int64							lMeTieScore;						//��ƽ��ע
	__int64							lMeBankerScore;						//��ׯ��ע
	__int64							lMePlayerScore;						//������ע
	__int64							lMeTieKingScore;					//ͬ��ƽע
	__int64							lMePlayerKingScore;					//������ע
	__int64							lMeBankerKingScore;					//ׯ����ע

	//ׯ����Ϣ
	WORD							wCurrentBankerChairID;				//��ǰׯ��
	BYTE							cbBankerTime;						//ׯ�Ҿ���
	__int64							lCurrentBankerScore;				//ׯ�ҷ���
	__int64							lApplyBankerCondition;				//��������
	__int64							lBankerTreasure;					//ׯ�ҽ��
};

//��Ϸ״̬
struct CMD_S_StatusPlay
{
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	__int64							lCellScore;							//���Ԫ��ע
	//��ע��Ϣ
	__int64							lTieScore;							//��ƽ��ע
	__int64							lBankerScore;						//��ׯ��ע
	__int64							lPlayerScore;						//������ע
	__int64							lTieSamePointScore;					//ͬ��ƽע
	__int64							lPlayerKingScore;					//������ע
	__int64							lBankerKingScore;					//ׯ����ע

	//�ҵ���ע
	__int64							lMeMaxScore;						//�����ע
	__int64							lMeTieScore;						//��ƽ��ע
	__int64							lMeBankerScore;						//��ׯ��ע
	__int64							lMePlayerScore;						//������ע
	__int64							lMeTieKingScore;					//ͬ��ƽע
	__int64							lMePlayerKingScore;					//������ע
	__int64							lMeBankerKingScore;					//ׯ����ע

	//�˿���Ϣ
 	BYTE							cbCardCount[2];						//�˿���Ŀ
	BYTE							cbTableCardArray[5][2];				//�����˿�

	//ׯ����Ϣ
	WORD							wCurrentBankerChairID;				//��ǰׯ��
	BYTE							cbBankerTime;						//ׯ�Ҿ���
	__int64							lCurrentBankerScore;				//ׯ�ҷ���
	__int64							lApplyBankerCondition;				//��������
	__int64							lBankerTreasure;					//ׯ�ҽ��
};

//��Ϸ��ʼ
struct CMD_S_GameStart
{
	BYTE							cbCardCount[2];						//�˿���Ŀ
	BYTE							cbTableCardArray[5][2];				//�����˿�
	__int64							lApplyBankerCondition;				//��������

	//ׯ����Ϣ
	WORD							wBankerChairID;						//ׯ�Һ���
	__int64							lBankerScore;						//ׯ�һ���
	BYTE							cbBankerTime;						//��ׯ����
	BYTE							cbTimeLeave;						//ʣ��ʱ��
};

//�û���ע
struct CMD_S_PlaceJetton
{
	WORD							wChairID;							//�û�λ��
	BYTE							cbJettonArea;						//��������
	__int64							lJettonScore;						//��ע��Ŀ
};

//��Ϸ����
struct CMD_S_GameEnd
{
	//�¾���Ϣ
	__int64							lMeMaxScore;						//�����ע
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	__int64							lCellScore;							//�����ע

	//�ɼ���¼
	BYTE							cbWinner;							//ʤ�����
	BYTE							cbKingWinner;						//����ʤ��
	__int64							lBankerTreasure;					//ׯ�ҽ��

	__int64							lBankerTotalScore;					//ׯ�ҳɼ�
	__int64							lBankerScore;						//ׯ�ҳɼ�
	INT								nBankerTime;						//��ׯ����
};

//��Ϸ�÷�
struct CMD_S_GameScore
{
	//�ɼ���¼
	BYTE							cbWinner;							//ʤ�����
	BYTE							cbKingWinner;						//����ʤ��
	__int64							lMeGameScore;						//�ҵĳɼ�
	__int64							lMeReturnScore;						//����ע��
	__int64							lBankerScore;						//ׯ�ҳɼ�

	//��ע��Ϣ
	__int64							lDrawTieScore;						//��ƽ��ע
	__int64							lDrawBankerScore;					//��ׯ��ע
	__int64							lDrawPlayerScore;					//������ע
	__int64							lDrawTieSamPointScore;				//ͬ��ƽע
	__int64							lDrawPlayerKingScore;				//������ע
	__int64							lDrawBankerKingScore;				//ׯ����ע

	//�ҵ���ע
	__int64							lMeTieScore;						//��ƽ��ע
	__int64							lMeBankerScore;						//��ׯ��ע
	__int64							lMePlayerScore;						//������ע
	__int64							lMeTieKingScore;					//ͬ��ƽע
	__int64							lMePlayerKingScore;					//������ע
	__int64							lMeBankerKingScore;					//ׯ����ע
};

//////////////////////////////////////////////////////////////////////////
//�ͻ�������ṹ

#define SUB_C_PLACE_JETTON			1									//�û���ע
#define SUB_C_APPLY_BANKER			2									//����ׯ��

//�û���ע
struct CMD_C_PlaceJetton
{
	BYTE							cbJettonArea;						//��������
	__int64							lJettonScore;						//��ע��Ŀ
};

//����ׯ��
struct CMD_C_ApplyBanker
{
	bool							bApplyBanker;						//�����ʶ
};

//////////////////////////////////////////////////////////////////////////

#endif