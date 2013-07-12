#ifndef DLG_INSURE_COUNTER_HEAD_FILE
#define DLG_INSURE_COUNTER_HEAD_FILE

#pragma once

#include "MissionManager.h"
#include "PasswordControl.h"
#include "ShareControlHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��˵��
class CDlgInsureItem;
class CDlgInsureMain;
class CDlgInsureSave;

//////////////////////////////////////////////////////////////////////////////////

//������ʽ
#define INSURE_SAVE					0									//��ȡ��ʽ
#define INSURE_TRANSFER				1									//ת�˷�ʽ

#define WM_INSUREPLAZA_UPDATA      (WM_USER+1680)						//���и�����Ϣ

//////////////////////////////////////////////////////////////////////////////////

struct tagInsurePlazaUpdata
{
	SCORE  lUserScore;
	SCORE  lUserInsure;
};

//������Ϣ
struct tagUserInsureInfo
{
	WORD							wRevenueTake;						//˰�ձ���
	WORD							wRevenueTransfer;					//˰�ձ���
	WORD							wServerID;							//�����ʶ
	SCORE							lUserScore;							//�û���Ϸ��
	SCORE							lUserInsure;						//������Ϸ��
	SCORE							lTransferPrerequisite;				//ת������
};

//////////////////////////////////////////////////////////////////////////////////

//���нӿ�
interface IInsureCounterAction
{
	//��ѯ�¼�
	virtual VOID PerformQueryInfo()=NULL;
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore)=NULL;
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)=NULL;
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////

//ҳ������
class CDlgInsureItem
{
	//��������
public:
	//���캯��
	CDlgInsureItem();
	//��������
	virtual ~CDlgInsureItem();

	//���ܺ���
public:
	//��ȡ��Ϸ��
	SCORE GetUserControlScore(CWnd * pWndScore);

	//���ܺ���
public:
	//�滭����
	VOID DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos);
	//ת���ַ�
	VOID SwitchScoreString(SCORE lScore, LPTSTR pszBuffer, WORD wBufferSize);
	//ת���ַ�
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);
};

//////////////////////////////////////////////////////////////////////////////////

//��ȡ��Ϸ��
class CDlgInsureSave : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ

	//�ؼ�����
public:
	CSkinEditEx						m_edScore;							//������Ϸ��
	CSkinButton						m_btTakeScore;						//ȡ�ť
	CSkinButton						m_btSaveScore;						//��ť

	//�����ؼ�
public:
	CSkinHyperLink					m_ForgetInsure;						//��������
	CDlgInsureItem					m_DlgInsureItem;					//��������
	CPasswordControl				m_PasswordControl;					//�û�����

	//��������
public:
	//���캯��
	CDlgInsureSave();
	//��������
	virtual ~CDlgInsureSave();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//��ť
	VOID OnBnClickedSaveScore();
	//ȡ�ť
	VOID OnBnClickedTakeScore();
	//��������
	VOID OnBnClickedForgetInsure();

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//ת����Ϸ��
class CDlgInsureTransfer : public CDialog
{
	//��Ԫ����
	friend class CDlgInsureMain;

	//��������
protected:
	bool							m_bSwitchIng;						//ת����־

	//����ָ��
protected:
	CDlgInsureMain *				m_pDlgInsureMain;					//����ָ��
	tagUserInsureInfo *				m_pUserInsureInfo;					//�û���Ϣ

	//�ؼ�����
public:
	CSkinEditEx						m_edScore;							//������Ϸ��
	CSkinEditEx						m_edNickName;						//�û��ǳ�
	CSkinButton						m_btTransferScore;					//ת�˰�ť

	//�����ؼ�
public:
	CSkinHyperLink					m_ForgetInsure;						//��������
	CDlgInsureItem					m_DlgInsureItem;					//��������
	CPasswordControl				m_PasswordControl;					//�û�����

	//��������
public:
	//���캯��
	CDlgInsureTransfer();
	//��������
	virtual ~CDlgInsureTransfer();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();
	//ȡ����ť
	virtual VOID OnCancel();

	//�ؼ�����
protected:
	//������Ϣ
	VOID OnEnChangeScore();
	//��������
	VOID OnBnClickedForgetInsure();
	//ת�˰�ť
	VOID OnBnClickedTransferScore();

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedById();
	afx_msg void OnBnClickedByName();
};

//////////////////////////////////////////////////////////////////////////////////

//���չ���
class SHARE_CONTROL_CLASS CDlgInsureMain : public CSkinDialog, public IInsureCounterAction
{
	//��������
protected:
	bool							m_bSaveMission;						//�������
	bool							m_bTakeMission;						//ȡ������
	bool							m_bQueryMission;					//��ѯ����
	bool							m_bTransferMission;					//ת������

	//��ѯ����
protected:
	bool							m_bInitInfo;						//������Ϣ
	BYTE							m_cbInsureMode;						//����ģʽ
	tagUserInsureInfo				m_UserInsureInfo;					//������Ϣ

	//�����ؼ�
protected:
	CSkinTabCtrl					m_TabControl;						//����ѡ��
	CSkinButton						m_btQueryInfo;						//��ѯ��ť

	//�����
protected:
	CDlgInsureItem					m_DlgInsureItem;					//��������
	CDlgInsureSave					m_DlgInsureSave;					//��ȡ����
	CDlgInsureTransfer				m_DlgInsureTransfer;				//ת������

	//��������
public:
	//���캯��
	CDlgInsureMain();
	//��������
	virtual ~CDlgInsureMain();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ����ť
	virtual VOID OnOK();

	//���ں���
protected:
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

	//�¼�����
public:
	//��ʼ����
	VOID OnMissionStart();
	//��ֹ����
	VOID OnMissionConclude();

	//���ܺ���
protected:
	//��ѯ����
	VOID QueryUserInsureInfo();
	//����ģʽ
	VOID SwitchInsureModeView(BYTE cbInsureMode);

	//��Ϣ����
protected:
	//��ѯ��ť
	VOID OnBnClickedQueryInfo();
	//���͸ı�
	VOID OnTcnSelchangeInsureMode(NMHDR * pNMHDR, LRESULT * pResult);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

//�㳡����
class SHARE_CONTROL_CLASS CDlgInsurePlaza : public CDlgInsureMain, public CMissionItem
{
	//��������
protected:
	BYTE                            m_cbByNickName;                       //�ǳ�����
	SCORE							m_lScore;							//��Ϸ����Ŀ
	TCHAR							m_szNickName[LEN_NICKNAME];			//�û��ǳ�
	TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������

	//�������
protected:
	CMissionManager					m_MissionManager;					//�������

	//��������
public:
	//���캯��
	CDlgInsurePlaza();
	//��������
	virtual ~CDlgInsurePlaza();

	//ִ�к���
protected:
	//��ѯ�¼�
	virtual VOID PerformQueryInfo();
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore);
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass);
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass);

	//�����¼�
private:
	//�����¼�
	virtual bool OnEventMissionLink(INT nErrorCode);
	//�ر��¼�
	virtual bool OnEventMissionShut(BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////////////

//��������
class SHARE_CONTROL_CLASS CDlgInsureServer : public CDlgInsureMain
{
	//��������
protected:
	BYTE                            m_cbByNickName;                       //�ǳ�����
	SCORE							m_lScore;							//��Ϸ����Ŀ
	TCHAR							m_szNickName[LEN_NICKNAME];			//�û��ǳ�
	TCHAR							m_szInsurePass[LEN_PASSWORD];		//��������

	//��������
protected:
	ITCPSocket *					m_pITCPSocket;						//����ӿ�
	IClientUserItem *				m_pIMySelfUserItem;					//�Լ�ָ��

	//��������
public:
	//���캯��
	CDlgInsureServer();
	//��������
	virtual ~CDlgInsureServer();

	//ִ�к���
protected:
	//��ѯ�¼�
	virtual VOID PerformQueryInfo();
	//�����¼�
	virtual VOID PerformSaveScore(SCORE lSaveScore);
	//ȡ���¼�
	virtual VOID PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass);
	//ת���¼�
	virtual VOID PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass);

	//���ܺ���
public:
	//��������
	VOID Initialization(ITCPSocket * pITCPSocket, IClientUserItem * pIMySelfUserItem);
	//������Ϣ
	bool OnServerInsureMessage(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize);
};

//////////////////////////////////////////////////////////////////////////////////

#endif