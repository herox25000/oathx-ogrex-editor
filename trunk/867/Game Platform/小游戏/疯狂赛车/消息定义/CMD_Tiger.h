#ifndef CMD_TIGER_HEAD_FILE
#define CMD_TIGER_HEAD_FILE

//////////////////////////////////////////////////////////////////////////
//�����궨��

static void SuperRand()
{
	srand(::GetTickCount());

	LONG count=rand()%30;

	for ( int i=0; i<count; i++ )
	{
		rand();
	}
}

#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

#define SAFE_DELETE(p) { if(p) { delete (p); (p)=NULL; } }

#define SOCKET_PACKAGE				2048				//�����ֽڳ���
#define KIND_ID						103					//��Ϸ I D
#define GAME_PLAYER					100					//��Ϸ����
#define GAME_NAME					TEXT("�������")	//��Ϸ����
#define GAME_GENRE					(GAME_GENRE_GOLD)	//��Ϸ����

#define BANK_CONDITION_MONEY		10000000
#define ANIMAL_ROLL_SPEED			50					//����������ת�ٶ�(����)

//�������
#define ID_BIG_TIGER				1					//������
#define ID_SML_TIGER				2					//С������
#define ID_BIG_DOG					3					//������
#define ID_SML_DOG					4					//С������
#define ID_BIG_HORSE				5					//��������
#define ID_SML_HORSE				6					//С������
#define ID_BIG_SNAKE				7					//��������
#define ID_SML_SNAKE				8					//С������

#define ID_FIRST_ANIMAL				1					//��һ����������

#define MAX_ANIMAL_COUNT			8					//������Ŀ

static const BYTE s_Multiple[MAX_ANIMAL_COUNT]={39, 4, 29, 4, 19, 4, 9, 4};

static const BYTE s_arJettonArea[MAX_ANIMAL_COUNT]={ID_BIG_TIGER, ID_SML_TIGER, ID_BIG_DOG, ID_SML_DOG, ID_BIG_HORSE, ID_SML_HORSE, ID_BIG_SNAKE, ID_SML_SNAKE};

#define LIMIT_VALUE(x, min, max) {if ((x)<(min)) (x)=(min); if ((x)>(max)) (x)=(max);}

//��¼��Ϣ
struct tagServerGameRecord
{
	BYTE							cbWinner;							//ʤ�����
	__int64							lBigTigerScore;						//�����ע
	__int64							lSmlTigerScore;						//��С����ע
	__int64							lBigBogScore;						//�����ע
	__int64							lSmlBogScore;						//�����ע
	__int64							lBigHorseScore;						//�������ע
	__int64							lSmlHorseScore;						//��С����ע
	__int64							lBigSnakeScore;						//�������ע
	__int64							lSmlSnakeScore;						//��С����ע
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
	__int64							lBankerWinScore;					//ׯ�ҷ���
	__int64							lBankerTreasure;					//ׯ�ҽ��
};

//��Ϸ״̬
struct CMD_S_StatusFree
{
	//ȫ����Ϣ
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	__int64							lCellScore;							//���Ԫ��ע
	//��ע��Ϣ
	__int64							lBigTigerScore;						//�����ע
	__int64							lSmlTigerScore;						//��С����ע
	__int64							lBigBogScore;						//�����ע
	__int64							lSmlBogScore;						//�����ע
	__int64							lBigHorseScore;						//�������ע
	__int64							lSmlHorseScore;						//��С����ע
	__int64							lBigSnakeScore;						//�������ע
	__int64							lSmlSnakeScore;						//��С����ע

	//�ҵ���ע
	__int64							lMeMaxScore;						//�����ע
	
	__int64							lMeBigTigerScore;					//�������ע
	__int64							lMeSmlTigerScore;					//����С����ע
	__int64							lMeBigBogScore;						//�������ע
	__int64							lMeSmlBogScore;						//�������ע
	__int64							lMeBigHorseScore;					//���������ע
	__int64							lMeSmlHorseScore;					//����С����ע
	__int64							lMeBigSnakeScore;					//���������ע
	__int64							lMeSmlSnakeScore;					//����С����ע

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
	__int64							lBigTigerScore;						//����ϻ���ע
	__int64							lSmlTigerScore;						//��С�ϻ���ע
	__int64							lBigBogScore;						//�����ע
	__int64							lSmlBogScore;						//�����ע
	__int64							lBigHorseScore;						//�������ע
	__int64							lSmlHorseScore;						//��С����ע
	__int64							lBigSnakeScore;						//�������ע
	__int64							lSmlSnakeScore;						//��С����ע

	//�ҵ���ע
	__int64							lMeMaxScore;						//�����ע
	
	__int64							lMeBigTigerScore;					//������ϻ���ע
	__int64							lMeSmlTigerScore;					//����С�ϻ���ע
	__int64							lMeBigBogScore;						//�������ע
	__int64							lMeSmlBogScore;						//�������ע
	__int64							lMeBigHorseScore;					//���������ע
	__int64							lMeSmlHorseScore;					//����С����ע
	__int64							lMeBigSnakeScore;					//���������ע
	__int64							lMeSmlSnakeScore;					//����С����ע

	//�˿���Ϣ
 	BYTE							cbAnimalBox;				//�����˿�

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
	BYTE							cbAnimalBox;
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	__int64							lApplyBankerCondition;				//��������

	//ׯ����Ϣ
	WORD							wBankerChairID;						//ׯ�Һ���
	__int64							lBankerWinScore;					//ׯ�һ���
	BYTE							cbBankerTime;						//��ׯ����
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
	BYTE							cbTimeLeave;						//ʣ��ʱ��
	__int64							lMeMaxScore;						//�����ע
	__int64							lCellScore;							//�����ע

	//�ɼ���¼
	BYTE							cbWinner;							//ʤ�����
	__int64							lBankerTreasure;					//ׯ�ҽ��

	__int64							lBankerTotalScore;					//ׯ�ҳɼ�
	__int64							lBankerWinScore;					//ׯ�ҳɼ�
	INT								nBankerTime;						//��ׯ����
};

//��Ϸ�÷�
struct CMD_S_GameScore
{
	//�ɼ���¼
	BYTE							cbWinner;							//ʤ�����
	__int64							lMeGameScore;						//�ҵĳɼ�
	__int64							lMeReturnScore;						//����ע��
	__int64							lBankerWinScore;						//ׯ�ҳɼ�

	//��ע��Ϣ
	__int64							lDrawBigTigerScore;					//����ϻ���ע
	__int64							lDrawSmlTigerScore;					//��С�ϻ���ע
	__int64							lDrawBigBogScore;					//�����ע
	__int64							lDrawSmlBogScore;					//�����ע
	__int64							lDrawBigHorseScore;					//�������ע
	__int64							lDrawSmlHorseScore;					//��С����ע
	__int64							lDrawBigSnakeScore;					//�������ע
	__int64							lDrawSmlSnakeScore;					//��С����ע

	//�ҵ���ע
	__int64							lMeBigTigerScore;					//������ϻ���ע
	__int64							lMeSmlTigerScore;					//����С�ϻ���ע
	__int64							lMeBigBogScore;						//�������ע
	__int64							lMeSmlBogScore;						//�������ע
	__int64							lMeBigHorseScore;					//���������ע
	__int64							lMeSmlHorseScore;					//����С����ע
	__int64							lMeBigSnakeScore;					//���������ע
	__int64							lMeSmlSnakeScore;					//����С����ע
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

#endif //CMD_TIGER_HEAD_FILE