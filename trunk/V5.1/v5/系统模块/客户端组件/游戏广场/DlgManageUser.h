#ifndef DLG_MANAGE_USER_HEAD_FILE
#define DLG_MANAGE_USER_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//�������
class CDlgManageUser : public CSkinDialog
{
	//��������
protected:
	DWORD							m_dwMasterRight;					//����Ȩ��

	//�ӿڶ���
protected:
	ITCPSocket *					m_pITCPSocket;						//����ӿ�

	//�ؼ�����
protected:
	CSkinButton						m_btKickAllUser;					//���ư�ť
	CSkinButton						m_btDismissGame;					//���ư�ť
	CSkinButton						m_btSeeUserIP;					    //���ư�ť

	//��������
public:
	//���캯��
	CDlgManageUser();
	//��������
	virtual ~CDlgManageUser();

	//���غ��� 
protected:
	//�˵�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//���ܺ���
public:
	//���ýӿ�
	bool SetTCPSocket(IUnknownEx * pIUnknownEx);
	//����Ȩ��
	VOID SetMasterRight( DWORD dwMasterRight );

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////


#endif