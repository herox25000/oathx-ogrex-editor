#ifndef MATCH_SERVICE_HEAD_H
#define MATCH_SERVICE_HEAD_H
#include "resource.h"
#pragma once

#include "Stdafx.h"
#include "DistributeManager.h"
#include "TableFrame.h"
#include "afxwin.h"

//////////////////////////////////////////////////////////////////////////
//����˵��
typedef CWHArray<CTableFrame *>		CTableFrameArray;					//��������
typedef CMap<CTableFrame*,CTableFrame*,DWORD,DWORD> CTableFrameMap;		//��������
typedef CMap<DWORD,DWORD,IServerUserItem*,IServerUserItem*> CIServerUserItemMap;
typedef CWHArray <CMD_GR_Match_Info*> CMatchInfoArray;

//////////////////////////////////////////////////////////////////////////
//��������
#define MAX_MATCH_COUNT				(512/(sizeof(ULARGE_INTEGER)*2))	//��������

//����״̬
#define MATCH_STATUS_NOT_STARTED			0							//û�п�ʼ
#define MATCH_STATUS_MATCHING				1							//������
#define MATCH_STATUS_WAIT_FINISH			2							//�ȴ�����
#define MATCH_STATUS_WAIT_START				3							//�ȴ���ʼ
#define MATCH_STATUS_FINISH					4							//��������

#ifdef _UNICODE
#define VER_IMatchService INTERFACE_VERSION(1,1)
static const GUID IID_IMatchService={0x6e733049,0x0f23,0x40c2,0x00ad,0xec,0xcb,0x87,0x76,0xb6,0x3e,0xf5};
#else
#define VER_IMatchService INTERFACE_VERSION(1,1)
static const GUID IID_IMatchService={0x24725b64,0x0e46,0x4ca3,0x0091,0xc7,0x4a,0x8a,0x78,0x69,0x06,0x83};
#endif

//�����ӿ�
interface IMatchService:public IUnknownEx
{
	//�����¼�
	virtual bool OnAttemperEngineStart(IUnknownEx * pIUnknownEx)=NULL;
	//ֹͣ�¼�
	virtual bool OnAttemperEngineConclude(IUnknownEx * pIUnknownEx)=NULL;
	//���ò���
	virtual bool ModifyMatchParameter()=NULL;
	//���ýӿ�
	virtual bool InitMatchService(IMainServiceFrame *pIMainServiceFrame, IDataBaseEngine *pIKernelDataBaseEngine,ITimerEngine *pITimerEngine,
		tagGameServiceAttrib *pGameServiceAttrib,tagGameServiceOption *pGameServiceOption,CTableFrameArray &TableFrameArray)=NULL;
	//�û�����
	virtual bool OnUserJoinMatch(IServerUserItem * pIServerUserItem)=NULL;
	//�û�����
	virtual bool OnUserQuitMatch(IServerUserItem * pIServerUserItem)=NULL;
	//������Ϣ
	virtual bool OnEventSocketMatch(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem, DWORD dwSocketID)=NULL;
	//ʱ���¼�
	virtual bool OnEventTimer(DWORD dwTimerID, WPARAM dwBindParameter)=NULL;
	//��������
	virtual DWORD GetSignUpUserCount()=NULL;
	//���ù���
	virtual VOID  SetDistributeRule(BYTE cbDistributeRule)=NULL;
	//�������
	virtual bool InsertDistribute(IServerUserItem * pIServerUserItem)=NULL;
	//������Ϣ
	virtual bool SendMatchInfo(IServerUserItem * pIServerUserItem)=NULL;
	//���ݿ��¼�
	virtual bool OnEventDataBase(WORD wRequestID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////
#ifdef _UNICODE
#define VER_IMatchTableFrameNotify INTERFACE_VERSION(1,1)
static const GUID IID_IMatchTableFrameNotify={0x726112e4,0x7820,0x4e49,0x00af,0x69,0xe5,0x39,0x6e,0x71,0xb2,0xfb};
#else
#define VER_IMatchTableFrameNotify INTERFACE_VERSION(1,1)
static const GUID IID_IMatchTableFrameNotify={0xdfc52f50,0x0692,0x430a,0x00aa,0x44,0x4d,0xda,0x2d,0xd3,0x08,0xd8};
#endif


interface IMatchTableFrameNotify: public IUnknownEx
{
	//�û�׼��
	virtual bool OnUserReay(IServerUserItem * pIServerUserItem,WORD wTableID,WORD wChairID)=NULL;
	//��Ϸ��ʼ
	virtual bool OnEventGameStart(WORD wTableID)=NULL;
	//��Ϸ����
	virtual bool OnEventGameEnd(WORD wTableID)=NULL;
};

//////////////////////////////////////////////////////////////////////////////////
class CMatchParameterDlg:public CDialog
{
	enum {IDD=IDD_DLG_MATCH_PARAMETER};

public:
	WORD							m_wMatchID;							//����ID
	BYTE							&m_cbMatchTime;						//��������
	ULARGE_INTEGER					*m_puiMatchDate;					//����ʱ��
	CMatchInfoArray					&m_MatchInfo;						//������Ϣ
	TCHAR							*m_pszMatchRoom;					//��������
	DWORD							&m_dwMatchFee;						//��������
	LONG							&m_lInitScore;						//��ʼ����
	WORD							&m_wMatchGameCount;					
	
	//�ؼ�����
protected:
	CListCtrl						m_ListMatch;						//�����б�
	CListCtrl						m_ListMatchInfo;					//������Ϣ

public:
	CMatchParameterDlg(CMatchInfoArray &MatchInfo,ULARGE_INTEGER *puiMatchDate,BYTE &cbMatchTime, TCHAR *pszMatchRoom,DWORD &dwMatchFee,
						LONG &lInitScore, WORD &wMatchGameCount,WORD wMatchID);
    virtual ~CMatchParameterDlg();

	//���غ���
public:
	//��ʼ������
	virtual BOOL OnInitDialog();
	//���ݽ���
	virtual void DoDataExchange(CDataExchange* pDX);

	//��Ϣӳ��
public:
	//���ʱ��
	VOID OnBnClickedAdd();
	//�޸�ʱ��
	VOID OnBnClickedModify();
	//ɾ��ʱ��
	VOID OnBnClickedDelete();
	//�����Ϣ
	VOID OnBnClickedAddInfo();
	//�޸���Ϣ
	VOID OnBnClickedModifyInfo();
	//ɾ����Ϣ
	VOID OnBnClickedDeleteInfo();


	//��������
private:
	//���¿ؼ�
	VOID UpdateMatchList();
	//���¿ؼ�
	VOID UpdateMatchInfoList();
	//��ȡʱ���ַ���
	LPCTSTR GetTimeString( SYSTEMTIME &st );
	DECLARE_MESSAGE_MAP()
protected:
	virtual void OnOK();
};

//////////////////////////////////////////////////////////////////////////
class CTimeRankingsMatch:public IMatchService, public IMatchTableFrameNotify
{
	//��������
public:	
	DWORD							m_dwMatchFee;						//��������
	IMainServiceFrame *				m_pIMainServiceFrame;				//����ӿ�
	IDataBaseEngine *				m_pIKernelDataBaseEngine;			//��������
	tagGameServiceAttrib *			m_pGameServiceAttrib;				//��������
	tagGameServiceOption *			m_pGameServiceOption;				//��������
	CDistributeManager              m_DistributeManage;                 //�������
	ITimerEngine *					m_pITimerEngine;					//ʱ������
	CTableFrameArray				m_TableFrameArray;					//��������

	//��������
public:
	CMatchInfoArray					m_MatchInfo;						//������Ϣ
	CIServerUserItemMap				m_ServerUserItemMap;				//������Ա
	BYTE							m_cbMatchTime;						//��������
	ULARGE_INTEGER					m_uiMatchDate[MAX_MATCH_COUNT*2];	//����ʱ��
	CMatchParameterDlg				*m_pParameterDlg;					//���ò���
	TCHAR							m_szMatchName[32];					//��������
	WORD							m_wMatchID;							//����ID
	LONG							m_lInitScore;						//��ʼ����
	WORD							m_wMatchGameCount;					//��������
	CMD_GR_MatchRank *				m_pMatchRank;						//��������
	WORD 							m_wRankCount;						//������

	//״̬����
protected:
	BYTE							m_cbMatchStatus;					//����״̬
	CTime							m_TimeMatchStart;					//������ʼ
	CTime							m_TimeMatchOver;					//��������
	BYTE							m_cbCurMatch;						//��ǰ����

	//��������
public:
	//���캯��
	CTimeRankingsMatch(WORD wMatchID);
	//��������
	virtual ~CTimeRankingsMatch(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release(){delete this;}
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//�����ӿ�
public:
	//�����¼�
	virtual bool OnAttemperEngineStart(IUnknownEx * pIUnknownEx);
	//ֹͣ�¼�
	virtual bool OnAttemperEngineConclude(IUnknownEx * pIUnknownEx);
	//���ò���
	virtual bool ModifyMatchParameter();
	//���ýӿ�
	virtual bool InitMatchService(IMainServiceFrame *pIMainServiceFrame, IDataBaseEngine *pIKernelDataBaseEngine,ITimerEngine *pITimerEngine,
		tagGameServiceAttrib *pGameServiceAttrib,tagGameServiceOption *pGameServiceOption,CTableFrameArray &TableFrameArray);
	//�û�����
	virtual bool OnUserJoinMatch(IServerUserItem * pIServerUserItem);
	//�û�����
	virtual bool OnUserQuitMatch(IServerUserItem * pIServerUserItem);
	//������Ϣ
	virtual bool OnEventSocketMatch(WORD wSubCmdID, VOID * pData, WORD wDataSize, IServerUserItem * pIServerUserItem, DWORD dwSocketID);
	//ʱ���¼�
	virtual bool OnEventTimer(DWORD dwTimerID, WPARAM dwBindParameter);
	//��������
	virtual DWORD GetSignUpUserCount(){return (DWORD)m_ServerUserItemMap.GetCount();}
	//���ù���
	virtual VOID  SetDistributeRule(BYTE cbDistributeRule){m_DistributeManage.SetDistributeRule(cbDistributeRule);}
	//�������
	virtual bool InsertDistribute(IServerUserItem * pIServerUserItem);
	//������Ϣ
	virtual bool SendMatchInfo(IServerUserItem * pIServerUserItem);
	//���ݿ��¼�
	virtual bool OnEventDataBase(WORD wRequestID, IServerUserItem * pIServerUserItem, VOID * pData, WORD wDataSize);

	//����֪ͨ
public:
	//�û�׼��
	virtual bool OnUserReay(IServerUserItem * pIServerUserItem,WORD wTableID,WORD wChairID);
	//��Ϸ��ʼ
	virtual bool OnEventGameStart(WORD wTableID){return true;}
	//��Ϸ����
	virtual bool OnEventGameEnd(WORD wTableID);

	//���к���
protected:
	//��ʼ��һ������
	VOID StartNextMatch();
	//�����û�
	bool PerformDistribute();
	//��ȡʱ���ַ���
	LPCTSTR GetTimeString( SYSTEMTIME &st );
};
//////////////////////////////////////////////////////////////////////////

//��ӱ���������
class  CDlgAddMatchDate : public CDialog
{
	//�������
public:
	CTime					m_TimeBegin;				//��ʼʱ��
	CTime					m_TimeEnd;					//����ʱ��

	//�ؼ�����
protected:
	CDateTimeCtrl			m_CtrlDateBegin;			//��ʼ����
	CDateTimeCtrl			m_CtrlTimeBegin;			//��ʼʱ��
	CDateTimeCtrl			m_CtrlDateEnd;				//��������
	CDateTimeCtrl			m_CtrlTimeEnd;				//����ʱ��

	//��������
public:
	//���캯��
	CDlgAddMatchDate();   
	//��������
	virtual ~CDlgAddMatchDate();

	//���غ���
protected:
	//���ݽ���
	virtual void DoDataExchange(CDataExchange* pDX); 
	//��ʼ��
	virtual BOOL OnInitDialog();
	//ȷ������
	VOID OnOK();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////
//��ӱ�����Ϣ��
class  CDlgAddMatchInfo : public CDialog
{
	enum {IDD=IDD_MATCH_INFO};
	//�ؼ�����
public:
	CString					m_strInfoTitle;				//��Ϣ����
	CString					m_strInfoDesc;				//��Ϣ����
	int						m_nInfoTitleLen;			//���ⳤ��
	int						m_nInfoDescLen;				//��������

	//��������
public:
	//���캯��
	CDlgAddMatchInfo();   
	//��������
	virtual ~CDlgAddMatchInfo();

	//���غ���
protected:
	//���ݽ���
	virtual void DoDataExchange(CDataExchange* pDX); 
	//��ʼ��
	virtual BOOL OnInitDialog();
	//ȷ������
	VOID OnOK();

	DECLARE_MESSAGE_MAP()


};

class CMatchGroup
{
	//��������
protected:
	DWORD							m_dwMatchID;						//����ID
	CTableFrameArray				m_TableFrameArray;					//��������
	CIServerUserItemMap				m_ServerUserItemMap;				//������Ա
	BYTE							m_cbCurRound;						//��ǰ����
};
//////////////////////////////////////////////////////////////////////////////////
#endif
