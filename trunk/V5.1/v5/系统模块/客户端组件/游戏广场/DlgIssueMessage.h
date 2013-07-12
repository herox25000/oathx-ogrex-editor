#ifndef DLG_ISSUE_MESSAGE_HEAD_FILE
#define DLG_ISSUE_MESSAGE_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//�������
class CDlgIssueMessage : public CSkinDialog
{
	//��������
public:
	CString							m_strMessage;						//��Ϣ��ʾ
	BOOL							m_bSendALLRoom;						//������Ϣ
	BOOL							m_bSendRoom;						//������Ϣ
	BOOL							m_bSendGame;						//��Ϸ��Ϣ

	//���Ʊ���
protected:
	CSkinButton						m_btOK;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť

	//��������
public:
	//���캯��
	CDlgIssueMessage();
	//��������
	virtual ~CDlgIssueMessage();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////


#endif