#ifndef BANKER_STORAGE_HEAD_FILE
#define BANKER_STORAGE_HEAD_FILE

#include "PropertyModule.h"

#pragma once

//////////////////////////////////////////////////////////////////////////

//�һ���Ϸ�� 
class PROPERTY_MODULE_CLASS CBankStorage : public CSkinDialogEx
{
	//��������
public:
	tagUserData						*m_pMeUserData;					//�û���Ϣ
	__int64							m_lGameGold;					//������Ŀ
	__int64							m_lStorageGold;					//�洢��Ŀ
	DWORD							m_lInCount;						//������Ϸ��
	BOOL							m_bBanker;
	//�ؼ�����
protected:
	CSkinButton						m_btOK;							//ȷ����ť
	CSkinButton						m_btCancel;						//ȡ����ť

	//�ӿڱ���
protected:	
	IClientKernel					* m_pIClientKernel;				//�ں˽ӿ�
	ITCPSocket						* m_pClientSocket;				//����ӿ�

	//��������
public:
	//���캯��
	CBankStorage(CWnd* pParent = NULL); 
	//��������
	virtual ~CBankStorage();

	//��������
public:
	//���½���
	void UpdateView();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange* pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	afx_msg void OnBnClickedOk();
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//������Ϣ
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//ʱ����Ϣ
	afx_msg void OnTimer(UINT nIDEvent);
	//������Ϣ
	afx_msg void OnEnChangeInCount();

	//���ܺ���
public:
	//�Ƿ�ѡ��
	bool IsButtonSelected(UINT uButtonID);
	//ѡ�а�ť
	void SetButtonSelected(UINT uButtonID, bool bSelected);
	//����״̬
	void SetButtonAction(BOOL bBanker);
	//�������
	void SetSendInfo(IClientKernel *pClientKernel,ITCPSocket *pClientSocket,tagUserData *pMeUserDatas);
	//������Ϣ
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);

	DECLARE_MESSAGE_MAP()
};
//////////////////////////////////////////////////////////////////////////

//�һ�����
extern "C" PROPERTY_MODULE_CLASS VOID __cdecl ShowBankStorageDlg(IClientKernel *pIClientKernel,
																 ITCPSocket *pClientSocket,
																 tagUserData *pUserData,
																 BOOL bBanker=FALSE);

//////////////////////////////////////////////////////////////////////////
#endif