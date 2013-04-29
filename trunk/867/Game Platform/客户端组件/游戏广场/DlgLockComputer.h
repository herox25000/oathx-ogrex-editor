#ifndef CUSTOM_LOCKCOMPUTER_FILE
#define CUSTOM_LOCKCOMPUTER_FILE

#pragma once
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

//��������
class CDlgLockComputer : public CSkinPngDialog 
{
	//��������
protected:
	enOperateStatus				m_enOperateStatus;					//״̬����
	CBrush						m_brBkground;						//����ˢ��

	//�ؼ�����
protected:
	CSkinButton					m_btOk;								//ȷ������
	ITCPSocket					* m_pIClientSocket;					//�������
	TCHAR						m_szLogonPws[PASS_LEN];				//��Ϸ����

	//��������
public:
	//���캯��
	CDlgLockComputer(CWnd* pParent = NULL);
	//�鹹����
	virtual ~CDlgLockComputer();

	//��������
public:
	//��������
	bool SendData();

	//��������
protected:
	//��������
	virtual void DoDataExchange(CDataExchange* pDX);
	//��ʼ����
	virtual BOOL OnInitDialog();

	//��������
public:
	//��ʾ��Ϣ
	void ShowMessage(TCHAR *pMessage);
	//��������
	bool ConnectServer();
	//���¿ؼ�
	void UpdateControls();
	//����״̬
	void SetStatus(enOperateStatus enOperateStatus){m_enOperateStatus = enOperateStatus;}

	//��Ϣ����
protected:
	//ȷ��
	afx_msg void OnBnClickedOK();
	//�滭����
	afx_msg void OnPaint();
	afx_msg void OnCancel();
	//������Ϣ
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////////////////////////////////////

#endif