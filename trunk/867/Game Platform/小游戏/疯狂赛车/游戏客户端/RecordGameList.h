#ifndef RECORD_GAME_LIST_HEAD_FILE
#define RECORD_GAME_LIST_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//��Ϸ��¼
struct tagGameRecord
{
	//��Ϸ��Ϣ
	WORD							wDrawCount;							//��Ϸ����	
	BYTE							cbWinerSide;						//ʤ�����
	BYTE							cbPlayerPoint;						//�м��Ƶ�
	BYTE							cbBankerPoint;						//ׯ���Ƶ�	

	//�ҵ���Ϣ
	__int64							lGameScore;							//��Ϸ�ɼ�	
	__int64							lMyAddGold;							//��Ϸ��ע	

	//��ע����
	__int64							lDrawBigTigerScore;					//����ϻ���ע
	__int64							lDrawSmlTigerScore;					//��С�ϻ���ע
	__int64							lDrawBigBogScore;					//�����ע
	__int64							lDrawSmlBogScore;					//�����ע
	__int64							lDrawBigHorseScore;					//�������ע
	__int64							lDrawSmlHorseScore;					//��С����ע
	__int64							lDrawBigSnakeScore;					//�������ע
	__int64							lDrawSmlSnakeScore;					//��С����ע
};

//////////////////////////////////////////////////////////////////////////

//��Ϸ��¼
class CGameRecord : public CSkinDialogEx
{
	//�ؼ�����
public:
	CSkinListCtrl					m_RecordGameList;					//��Ϸ�б�

	//��������
public:
	//���캯��
	CGameRecord();
	//��������
	virtual ~CGameRecord();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ����Ϣ
	virtual void OnOK() { return; }
	//ȡ����Ϣ
	virtual void OnCancel() { return; }

	//���ܺ���
public:
	//�����б�
	void FillGameRecourd(tagGameRecord & GameRecord);

	//��Ϣӳ��
protected:
	//λ�ñ仯
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif