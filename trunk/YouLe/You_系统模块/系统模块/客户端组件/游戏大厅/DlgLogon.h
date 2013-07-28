#ifndef DLG_LOGON_HEAD_FILE
#define DLG_LOGON_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "PasswordControl.h"
#include "GdipButton.h"
#include "MemDC.h"
#include "LogonFramSheet.h"


//////////////////////////////////////////////////////////////////////////

//��¼ģʽ
enum enLogonMode
{
	LogonMode_Accounts,			//�ʺŵ�¼
	LogonMode_UserID,			//I D ��¼
};

//ע�������
#define REG_OPTION_LOGON		TEXT("OptionLogon")
#define REG_USER_INFO			TEXT("Software\\WHQPGame\\GamePlaza\\UserInfo")
#define REG_LOGON_SERVER		TEXT("Software\\WHQPGame\\GamePlaza\\LogonServer")

//////////////////////////////////////////////////////////////////////////
//��ѡ�ؼ�
class  CControlCheckButton
{
	//״̬����
protected:
	bool                           m_cbChecked;                        //��ס����
	CWnd *                         m_pParentSink;                      //����ָ��

	//λ�ñ���
protected:
	CPoint                         m_ptControlBenchmark;               //��׼λ��

	//��Դ����
protected:
	CPngImage		m_ImageBack;
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
	//��ȡ״̬
	inline bool  GetButtonChecked() { return m_cbChecked; };
	//����״̬
	inline VOID  SetButtonChecked(bool cbChecked);
	//����(ֻ�����PNG��Դ)
	void CreatCheckButton(CWnd* pParentWnd,HINSTANCE hInstance, LPCTSTR pszResourceName,INT nXPos,INT nYPos);

	//�¼�����
public:
	//���ƿؼ�
	VOID  OnDrawControl(CDC * pDC);
	//����¼�
	bool  OnClickControl(CPoint Point);

};
//////////////////////////////////////////////////////////////////////////

//�û�ע��
class CDlgRegister : public CDialog
{
	friend class CDlgLogon;
	enum passLevel
	{		
		PASSWORD_LEVEL_0=0,	
		PASSWORD_LEVEL_1,			
		PASSWORD_LEVEL_2,		
		PASSWORD_LEVEL_3		
	};
	//��¼��Ϣ
public:
	WORD								m_wFaceID;						//ͷ���ʶ
	BYTE								m_cbGender;						//�û��Ա�
	TCHAR								m_szAccounts[NAME_LEN];			//��Ϸ�ʺ�
	TCHAR								m_szPassword[PASS_LEN];			//��Ϸ����
	TCHAR								m_szLikeName[NAME_LEN];			//�ǳ�
	TCHAR								m_szAddress[32];				//��ַ
	TCHAR								m_szName[NAME_LEN];				//
	TCHAR								m_szSFZ[PASS_LEN];				//���֤����

	BYTE								m_cbLogonPassLevel;					//����ǿ��
	CPngImage							m_ImageBack;
	CPngImage							m_ImagePasswordLevel;

	TCHAR*		m_StrSheng[36];
	TCHAR*		m_StrDiqu[36][21];
	//�ؼ�����
public:
	CGdipButton							m_btEixt;
	CGdipButton							m_btRegisterOk;
	CControlCheckButton					m_btMan;
	CControlCheckButton					m_btWoman;

	CSkinEditEx				m_NameEdit;
	CSkinEditEx				m_SfzEdit;
	CSkinComboBox			m_BoxChengshi;
	CSkinComboBox			m_BoxDiqu;

	//��������
public:
	//���캯��
	CDlgRegister();
	//��������
	virtual ~CDlgRegister();
	//��ť����
	void SetButtonBackGrounds(CDC *pDC);
	//����ȼ�
	BYTE GetPasswordLevel(LPCTSTR pszPassword);
	//��½��������
	VOID OnEnChangeLogonPass();

	void InitChengShiDiQu();
	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();
	//ȡ����Ϣ
	virtual void OnCancel();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//��굯��
	void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeComboChengshi();
	afx_msg void OnCbnSelchangeComboDiqu();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

//��¼�Ի���
class CDlgLogon : public CDialog
{
public:
	CWnd*		m_pPlatformFrame;
	//��¼��Ϣ
protected:
	WORD								m_wFaceID;						//ͷ���ʶ
	BYTE								m_cbGender;						//�û��Ա�
	DWORD								m_dwUserID;						//�û� I D
	TCHAR								m_szAccounts[NAME_LEN];			//��Ϸ�ʺ�
	TCHAR								m_szPassword[PASS_LEN];			//��Ϸ����
	TCHAR								m_szLikeName[NAME_LEN];			//�ǳ�
	TCHAR								m_szAddress[32];				//��ַ
	TCHAR								m_szName[NAME_LEN];				//
	TCHAR								m_szSFZ[PASS_LEN];				//���֤����
	//λ�ñ���
protected:
	INT									m_nFullWidth;					//ȫ�����
	INT									m_nFullHeight;					//ȫ���߶�
	bool								m_bNetOption;					//��������
	CRect								m_rcNormalFrame;				//���λ��

	//��¼ģʽ
protected:
	enLogonMode							m_LogonMode;					//��¼ģʽ

	//������Ϣ
protected:
	bool								m_bRegister;					//ע���־
	
	//������Ϣ
protected:
	CString								m_strLogonServer;				//��������ַ
	CPngImage							m_ImageBack;
	//��ť����
public:
	CGdipButton							m_btCancel;						//ȡ����ť
	CGdipButton							m_btLogon;
	CGdipButton							m_btWebhome;
	CGdipButton							m_btRegister;
	CGdipButton							m_btChongzhi;
	CGdipButton							m_btBanben;

	CSkinEditEx							m_edAccounts;						//��¼�ʺ�
	CSkinEditEx							m_edPassWord;
	CControlCheckButton					m_RemPwdControl;

	//�������
	CGdipButton							m_btNumber[10];		//���ְ�ť
	CGdipButton							m_btAlphabet[26];	//��ĸ��ť
	CGdipButton							m_btOther[2];		//ɾ���ʹ�д
	//
public:
	TCHAR								m_szKeyboradNumber[2][11];			//�����ַ�
	TCHAR								m_szKeyboradChar[2][27];			//�����ַ�
	bool								m_bCaps;	//�Ƿ��д
	//�ؼ�����
public:
	CWebBrowser							m_BrowerAD;						//�������
	CSkinHyperLink						m_LineMainPage;					//��Ϸ��ҳ
	CSkinHyperLink						m_LinePassWord;					//���뱣��
	CSkinHyperLink						m_LineGetPassWord;				//ȡ������

	//�༭�ؼ�
protected:
	CSkinEdit							m_edProxyPort;					//����˿�
	CSkinEdit							m_edProxyServer;				//�����ַ
	CSkinEdit							m_edProxyUserName;				//�����û�
	CSkinEdit							m_edProxyPassword;				//��������
	CComboBox							m_cmProxyServerType;			//��������

public:
	YouLe::UILogonFramSheet				m_LogonFramSheet;
	bool								m_bCreateUI;
	//��������
public:
	//���캯��
	CDlgLogon();
	//��������
	virtual ~CDlgLogon();
	//���ô���ָ��
	void SetPlatFormPointer(CWnd* pPointer)	{m_pPlatformFrame = pPointer;}
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

	//��������
private:
	//��������
	//void UpdateUserPassWord(DWORD dwUserDBID);
	//����ģʽ
	//void SwitchNetOption(bool bNetOption);
	//����ѡ��
	//void UpdateUserComboBox(UINT uComboBoxID);
	//�����ַ�
	//int ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString);
	//��ȡ����
	//void GetProxyInfo(enProxyServerType &ProxyServerType, tagProxyServerInfo &ProxyServerInfo);
	//�����ж�
	bool EnableProxy() { return m_bNetOption;}

	//��Ϣ����
public:
	//ע���ʺ�
	afx_msg void OnRegisterAccounts();
	afx_msg void OnWebhome();
	afx_msg void OnChongzhi();
	afx_msg void OnBanben();
	//��Ӧ�����
	afx_msg void OnKeyBoard(UINT uID);
	//����ı�
	//afx_msg void OnEnChangePassword();
	//ѡ��ı�
	//afx_msg void OnSelchangeAccounts();
	//ѡ��ı�
	//afx_msg void OnSelchangeUserID();
	//�ؼ��ı�
//	void OnEnChangeAccounts();
	//�ػ���Ϣ
	afx_msg void OnPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//��굯��
	void OnLButtonUp(UINT nFlags, CPoint point);
	//
	void OnMouseMove(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif