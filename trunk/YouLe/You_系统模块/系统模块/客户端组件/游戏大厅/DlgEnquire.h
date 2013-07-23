#ifndef DLG_ENQUIRE_HEAD_FILE
#define DLG_ENQUIRE_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////////////
#define  WM_BT_CLOSE				100
#define  WM_BT_CLOSE_PLAZA			101
#define  WM_BT_SWITCH_ACCOUNTS		102
#define  WM_BT_QUITE				103

//�رմ���
class CDlgEnquire : public CDialog
{
	//�ؼ�����
protected:
	CGdipButton						m_btCancel;							//ȡ������
	CGdipButton						m_btClosePlaza;						//�رմ���
	CGdipButton						m_btQuite;						//�رշ���
	CGdipButton						m_btSwitchAccounts;					//�л��ʺ�

public:
	CPngImage						m_ImageBack;
	//��������
public:
	//���캯��
	CDlgEnquire();
	//��������
	virtual ~CDlgEnquire();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//���ú���
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();

	//��ť��Ϣ
protected:
	//�رմ���
	VOID OnBnClickedClosePlaza();
	//�رշ���
	VOID OnBnClickedCloseServer();
	//�л��ʺ�
	VOID OnBnClickedSwitchAccounts();

	//��Ϣ����
public:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif