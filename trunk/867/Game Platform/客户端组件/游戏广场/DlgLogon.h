#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////

//���������ƺ͵�½��ַ
struct SERVER_ITEM
{
	char szName[256];
	char szIPAddress[256];
};


//��¼ģʽ
enum enLogonMode
{
	LogonMode_Accounts,			//�ʺŵ�¼
	LogonMode_UserID,			//I D ��¼
};

//////////////////////////////////////////////////////////////////////////

//�û�ע��
class CDlgRegister : public CDialog
{
	friend class CDlgLogon;

	//��¼��Ϣ
public:
	WORD								m_wFaceID;						//ͷ���ʶ
	BYTE								m_cbGender;						//�û��Ա�
	TCHAR								m_szSpreader[NAME_LEN];			//��������
	TCHAR								m_szAccounts[NAME_LEN];			//��Ϸ�ʺ�
	TCHAR								m_szPassword[PASS_LEN];			//��Ϸ����
	TCHAR								m_szBankPassword[PASS_LEN];		//��������
	TCHAR								m_szSFZ[PASS_LEN];				//���֤����
	TCHAR								m_szPhone[PASS_LEN];			//�绰����

protected:
	CBrush							m_brBrush;							//������ˢ
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��

	BYTE							m_cbLogonPassLevel;					//����ǿ��
	BYTE							m_cbInsurePassLevel;				//����ǿ��
	//�ؼ�����
public:
	CImageList							m_ImageList;
	CComboBoxEx							m_FaceSelect;

	CSkinButtonEx							m_btLogon;						//��¼��ť
	CSkinButtonEx							m_btCancel;						//ȡ����ť
	CSkinButtonEx							m_btClose;						//�رհ�ť

	//��������
public:
	//���캯��
	CDlgRegister();
	//��������
	virtual ~CDlgRegister();
	//����ȼ�
	BYTE GetPasswordLevel(LPCTSTR pszPassword);
	//��½��������
	VOID OnEnChangeLogonPass();
	//������������
	VOID OnEnChangeInsurePass();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//ȷ������
	virtual void OnOK();
	//ȡ����Ϣ
	virtual void OnCancel();
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);


	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//��¼�Ի���
class CDlgLogon : public CDialog
{
	friend class CRoomViewItem;
	friend class CPlazaViewItem;

	//��¼��Ϣ
protected:
	WORD								m_wFaceID;						//ͷ���ʶ
	BYTE								m_cbGender;						//�û��Ա�
	DWORD								m_dwUserID;						//�û� I D
	TCHAR								m_szSpreader[NAME_LEN];			//�ƹ�����
	TCHAR								m_szAccounts[NAME_LEN];			//��Ϸ�ʺ�
	TCHAR								m_szPassword[PASS_LEN];			//��Ϸ����
	TCHAR								m_szBankPassword[PASS_LEN];		//��������
	TCHAR								m_szSFZ[PASS_LEN];		//���֤
	TCHAR								m_szPhone[PASS_LEN];		//�绰

	//λ�ñ���
protected:
	INT									m_nFullWidth;					//ȫ�����
	INT									m_nFullHeight;					//ȫ���߶�
	bool								m_bNetOption;					//��������
	//CRect								m_rcNormalFrame;				//���λ��

	//��¼ģʽ
protected:
	enLogonMode							m_LogonMode;					//��¼ģʽ

	//������Ϣ
protected:
	bool								m_bRegister;					//ע���־
	bool								m_bChangePassWord;				//�ı��־

	//������Ϣ
protected:
	CString								m_strLogonServer;				//��������ַ

	//��ť����
public:
	CSkinButtonEx							m_btLogon;						//��¼��ť
	CSkinButtonEx							m_btCancel;						//ȡ����ť
	CSkinButtonEx							m_btDelete;						//ɾ����ť
	CSkinButtonEx							m_btRegister;					//ע�ᰴť
	CSkinButtonEx							m_btNetOption;					//���簴ť
	CSkinButtonEx							m_btQuit;

	//�ؼ�����
public:
	CSkinLayered						m_SkinLayered;						//�ֲ㴰��
	CWebBrowser							m_BrowerAD;							//�������
	CSkinTabCtrl						m_TabLogonMode;						//��¼ѡ��
	CBrush								m_brBrush;							//������ˢ

	//��������
public:
	//���캯��
	CDlgLogon();
	//��������
	virtual ~CDlgLogon();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();
	//ȡ����Ϣ
	virtual void OnCancel();

	//���ܺ���
public:
	//��ȡ������
	LPCTSTR GetLogonServer() { return m_strLogonServer; }
	//���͵�¼��
	bool SendLogonPacket(ITCPSocket * pIClientSocke);
	//��¼�ɹ�����
	bool OnLogonSuccess();

	//�ڲ�����
private:
	//���ط�����
	void LoadLogonServer();
	//��ȡ�ʺ�
	void LoadAccountsInfo();
	//Ч������
	bool CheckLogonInput(bool bShowError);
	//����ģʽ
	void SetLogonMode(enLogonMode LogonMode);

	//��������
private:
	//��������
	void UpdateUserPassWord(DWORD dwUserDBID);
	//����ģʽ
	void SwitchNetOption(bool bNetOption);
	//����ѡ��
	void UpdateUserComboBox(UINT uComboBoxID);
	//�����ַ�
	int ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString);

	//��Ϣ����
public:
	//ע���ʺ�
	afx_msg void OnRegisterAccounts();
	//ɾ���û�
	afx_msg void OnDeleteAccounts();
	//��������
	afx_msg void OnBnClickedNetOption();
	//����ı�
	afx_msg void OnEnChangePassword();
	//ѡ��ı�
	afx_msg void OnSelchangeAccounts();
	//ѡ��ı�
	afx_msg void OnSelchangeUserID();
	//���͸ı�
	afx_msg void OnTcnSelchangeLogonType(NMHDR * pNMHDR, LRESULT * pResult);
	//��ҳ
	afx_msg void OnMainPage();
	//����
	afx_msg void OnNewUser();
	//����������
	afx_msg void OnServer();
	//�һ�����
	afx_msg void OnFindPassWord();
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//�ػ���Ϣ
	afx_msg void OnPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif
