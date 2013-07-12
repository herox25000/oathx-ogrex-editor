#pragma once


// CCollocateRoom dialog

class CCollocateRoom : public CSkinDialog
{
	DECLARE_DYNAMIC(CCollocateRoom)

public:
	CCollocateRoom();
	virtual ~CCollocateRoom();

	//���ñ���
protected:
	CParameterGame *				m_pParameterGame;					//��Ϸ����
	CParameterServer *				m_pParameterServer;					//��������

	//�ؼ�����
protected:
	CSkinButton						m_btOk;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť

	//ʤ������
public:
	WORD							m_wMinWinRate;						//���ʤ��
	bool							m_bLimitWinRate;					//����ʤ��

	//��������
public:
	WORD							m_wMaxFleeRate;						//�������
	bool							m_bLimitFleeRate;					//���ƶ���

	//��������
public:
	LONG							m_lMaxGameScore;					//��߷��� 
	LONG							m_lMinGameScore;					//��ͷ���
	bool							m_bLimitGameScore;					//���Ʒ���

	//��������
public:
	bool							m_bLimitDetest;						//�������
	bool							m_bLimitSameIP;						//Ч���ַ

	//Я������
public:
	bool							m_bTakePassword;					//Я������
	TCHAR							m_szPassword[LEN_PASSWORD];			//��������

	//�༭�ؼ�
protected:
	CSkinEdit						m_edWinRate;						//�û�ʤ��
	CSkinEdit						m_edFleeRate;						//�û�����
	CSkinEdit						m_edScoreMin;						//��ͻ���
	CSkinEdit						m_edScoreMax;						//��߻���
	CSkinEdit						m_edPassword;						//��������

	//���ܺ���
public:
	//���ò���
	bool InitCollocate(CParameterGame * pParameterGame, CParameterServer * pParameterServer);

	//���غ���
public:
	//�������
	virtual bool SaveParameter();
	//Ĭ�ϲ���
	virtual bool DefaultParameter();
	//���¿���
	virtual bool UpdateControlStatus();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
