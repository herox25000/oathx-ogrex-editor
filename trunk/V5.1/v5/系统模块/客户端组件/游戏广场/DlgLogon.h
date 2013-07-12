#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "PlatformPublicize.h"

//////////////////////////////////////////////////////////////////////////////////

//ѡ�����
class CWndLogonButton : public CWnd
{
	//���Ϣ
protected:
	bool							m_bHovering;						//������־
	WORD							m_wItemDown;						//��������
	WORD							m_wItemHover;						//��������
	WORD							m_wItemActive;						//��������

	//������Ϣ
protected:
	CSize							m_SizeButton;						//��ť��С

	//��������
public:
	//���캯��
	CWndLogonButton();
	//��������
	virtual ~CWndLogonButton();

	//�ڲ�����
private:
	//�����л�
	WORD SwitchToButtonIndex(CPoint MousePoint);

	//��Ϣ����
protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//����ƶ�
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//��ѡ�ؼ�
class  CControlCheckButton
{
	//״̬����
protected:
	BYTE                           m_cbChecked;                        //��ס����
	CWnd *                         m_pParentSink;                      //����ָ��

	//λ�ñ���
protected:
	CPoint                         m_ptControlBenchmark;               //��׼λ��

	//��Դ����
protected:
	CBitImage                      m_ImageBtnBack;                     //������Դ

	//��������
public:
	//���캯��
	CControlCheckButton();
	//��������
	virtual ~CControlCheckButton();

	//��������
public:
	//�ؼ�����
	CRect GetControlRect();

	//��������
public:
	//��׼λ��
	inline VOID  SetControlBenchmark(INT nXPos,INT nYPos) { m_ptControlBenchmark.SetPoint(nXPos,nYPos); };
	//��ȡ״̬
	inline BYTE  GetButtonChecked() { return m_cbChecked; };
	//����״̬
	inline VOID  SetButtonChecked(BYTE cbChecked);
	//���ø���
	inline VOID  SetParentWndSink(CWnd * pParentSink) { m_pParentSink=pParentSink; };

	//�¼�����
public:
	//���ƿؼ�
	VOID  OnDrawControl(CDC * pDC);
	//����¼�
	VOID  OnClickControl(CPoint Point);

};

//////////////////////////////////////////////////////////////////////////////////

//��¼����
class CDlgLogon : public CDialog
{
	//���ñ���
public:
	BYTE							m_cbRemPassword;					//��ס����

	//��¼��Ϣ
public:
	TCHAR							m_szAccounts[LEN_ACCOUNTS];			//��Ϸ�ʺ�
	TCHAR							m_szPassword[LEN_PASSWORD];			//�û�����
	TCHAR							m_szLogonServer[LEN_SERVER];		//��¼��ַ

	//�ؼ�����
protected:
	CSkinButton						m_btQuit;							//�˳���ť
	CSkinButton						m_btEnter;							//��¼��ť

	//����ؼ�
protected:
	CSkinEditEx						m_edAccounts;						//��¼�ʺ�
	CSkinComboBox					m_ServerControl;					//��¼��ַ
	CPasswordControl				m_PasswordControl;					//�û�����
	CControlCheckButton             m_RemPwdControl;                    //��ס����

	//����ؼ�
protected:
	CBrush							m_brBrush;							//������ˢ
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��
	CWndLogonButton					m_WndLogonButton;					//��ť�ؼ�
	CPlatformPublicize				m_PlatformPublicize;				//����ؼ�

	//��������
public:
	//���캯��
	CDlgLogon();
	//��������
	virtual ~CDlgLogon();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();

	//���ܺ���
public:
	//��������
	WORD ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize);

	//��������
private:
	//��ȡ��Ϣ
	bool GetInformation();
	//�����˺�
	VOID LoadAccountsInfo();
	//��ַ��Ϣ
	VOID LoadLogonServerInfo();

	//��ť��Ϣ
protected:
	//ע���ʺ�
	VOID OnBnClickedRegister();
	//�༭�ı�
	VOID OnCbnEditchangeAccounts();

	//ϵͳ��Ϣ
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	//��Ϣӳ��
public:
	afx_msg void OnEnChangeAccounts();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

//////////////////////////////////////////////////////////////////////////////////

#endif