#ifndef DLG_GAME_RULE_HEAD_FILE
#define DLG_GAME_RULE_HEAD_FILE

#pragma once

#include "GameFrameHead.h"

//////////////////////////////////////////////////////////////////////////

//��Ϸ����
class GAME_FRAME_CLASS CDlgGameRule : public CSkinDialog
{
	//�ؼ�����
public:
	CWebBrowser *					m_pHtmlBrowser;						//����ؼ�

	//��������
public:
	//���캯��
	CDlgGameRule();
	//��������
	virtual ~CDlgGameRule();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ����Ϣ
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();

	//��Ϣӳ��
public:
	//������Ϣ
	VOID OnNcDestroy();
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif