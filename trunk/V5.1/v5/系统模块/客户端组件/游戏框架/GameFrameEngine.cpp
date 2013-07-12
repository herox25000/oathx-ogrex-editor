#include "StdAfx.h"
#include "GlobalUnits.h"
#include "GameFrameEngine.h"

//////////////////////////////////////////////////////////////////////////////////

//��ʶ����
#define IDC_GAME_FRAME_ENGINE		100									//���ڱ�ʶ

//////////////////////////////////////////////////////////////////////////////////
//��̬����

CGameFrameEngine *	CGameFrameEngine::m_pGameFrameEngine=NULL;			//����ӿ�

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameEngine, CWnd)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameEngine::CGameFrameEngine()
{
	//����ӿ�
	m_pIClientKernel=NULL;
	m_pIStringMessage=NULL;

	//���ýӿ�
	ASSERT(m_pGameFrameEngine==NULL);
	if (m_pGameFrameEngine==NULL) m_pGameFrameEngine=this;

	//ע�����
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
	pGlobalUnits->RegisterGlobalModule(MODULE_GAME_FRAME_ENGINE,QUERY_ME_INTERFACE(IUnknownEx));

	return;
}

//��������
CGameFrameEngine::~CGameFrameEngine()
{
	//���ýӿ�
	ASSERT(m_pGameFrameEngine==this);
	if (m_pGameFrameEngine==this) m_pGameFrameEngine=NULL;

	return;
}

//�ӿڲ�ѯ
VOID * CGameFrameEngine::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameFrameEngine,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameFrameEngine,Guid,dwQueryVer);
	return NULL;
}

//����ģʽ
bool CGameFrameEngine::IsSingleMode()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return true;

	//��ȡģʽ
	return m_pIClientKernel->IsSingleMode();
}

//�Թ��û�
bool CGameFrameEngine::IsLookonMode()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return true;

	//��ȡ����
	return m_pIClientKernel->IsLookonMode();
}

//�����Թ�
bool CGameFrameEngine::IsAllowLookon()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��ȡ����
	return m_pIClientKernel->IsAllowLookon();
}

//��ȡ״̬
BYTE CGameFrameEngine::GetGameStatus()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return GAME_STATUS_FREE;

	//��ȡ״̬
	return m_pIClientKernel->GetGameStatus();
}

//����״̬
VOID CGameFrameEngine::SetGameStatus(BYTE cbGameStatus)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return;

	//����״̬
	m_pIClientKernel->SetGameStatus(cbGameStatus);

	return;
}

//��ȡ�Լ�
WORD CGameFrameEngine::GetMeChairID()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return NULL;

	//��ȡ�Լ�
	return m_pIClientKernel->GetMeChairID();
}

//��ȡ�Լ�
IClientUserItem * CGameFrameEngine::GetMeUserItem()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return NULL;

	//��ȡ�Լ�
	return m_pIClientKernel->GetMeUserItem();
}

//��Ϸ�û�
IClientUserItem * CGameFrameEngine::GetTableUserItem(WORD wChariID)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return NULL;

	//��ȡ�Լ�
	return m_pIClientKernel->GetTableUserItem(wChariID);
}

//��Ϸ�û�
IClientUserItem * CGameFrameEngine::SearchTableUserItem(DWORD dwUserID)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return NULL;

	//�����û�
	return m_pIClientKernel->SearchUserByUserID(dwUserID);
}

//������Ϸ��
bool CGameFrameEngine::PerformSaveScore(SCORE lScore)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��������
	CMD_GR_C_SaveScoreRequest SaveScoreRequest;
	SaveScoreRequest.cbActivityGame=TRUE;
	SaveScoreRequest.lSaveScore=lScore;

	//��������
	return m_pIClientKernel->SendSocketData(MDM_GR_INSURE,SUB_GR_SAVE_SCORE_REQUEST,&SaveScoreRequest,sizeof(SaveScoreRequest));
}

//��ȡ��Ϸ��
bool CGameFrameEngine::PerformTakeScore(SCORE lScore, TCHAR *pszInsurePass)
{
	//Ч�����
	ASSERT(pszInsurePass!=NULL);
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��������
	CMD_GR_C_TakeScoreRequest TakeScoreRequest;
	ZeroMemory(&TakeScoreRequest,sizeof(TakeScoreRequest));
	TakeScoreRequest.cbActivityGame=TRUE;
	TakeScoreRequest.lTakeScore=lScore;
	CopyMemory(TakeScoreRequest.szInsurePass,pszInsurePass,sizeof(TakeScoreRequest.szInsurePass));

	//��������
	return m_pIClientKernel->SendSocketData(MDM_GR_INSURE,SUB_GR_TAKE_SCORE_REQUEST,&TakeScoreRequest,sizeof(TakeScoreRequest));
}

//���ͺ���
bool CGameFrameEngine::SendSocketData(WORD wSubCmdID)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��������
	return m_pIClientKernel->SendSocketData(MDM_GF_GAME,wSubCmdID);
}

//���ͺ���
bool CGameFrameEngine::SendSocketData(WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��������
	return m_pIClientKernel->SendSocketData(MDM_GF_GAME,wSubCmdID,pData,wDataSize);
}

//����׼��
bool CGameFrameEngine::SendUserReady(VOID * pData, WORD wDataSize)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��������
	return m_pIClientKernel->SendUserReady(pData,wDataSize);
}

//���ͱ���
bool CGameFrameEngine::SendUserExpression(DWORD dwTargetUserID, WORD wItemIndex)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��������
	return m_pIClientKernel->SendUserExpression(dwTargetUserID,wItemIndex);
}

//��������
bool CGameFrameEngine::SendUserChatMessage(DWORD dwTargetUserID, LPCTSTR pszChatMessage, COLORREF crFontColor)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//��������
	return m_pIClientKernel->SendUserChatMessage(dwTargetUserID,pszChatMessage,crFontColor);
}

//ʱ�ӱ�ʶ
UINT CGameFrameEngine::GetClockID()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//ɾ��ʱ��
	return m_pIClientKernel->GetClockID();
}

//ʱ��λ��
WORD CGameFrameEngine::GetClockChairID()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return false;

	//ɾ��ʱ��
	return m_pIClientKernel->GetClockChairID();
}

//ɾ��ʱ��
VOID CGameFrameEngine::KillGameClock(WORD wClockID)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return;

	//ɾ��ʱ��
	m_pIClientKernel->KillGameClock(wClockID);

	return;
}

//����ʱ��
VOID CGameFrameEngine::SetGameClock(WORD wChairID, WORD wClockID, UINT nElapse)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return;

	//����ʱ��
	m_pIClientKernel->SetGameClock(wChairID,wClockID,nElapse);

	return;
}

//������
VOID CGameFrameEngine::ActiveGameFrame()
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return;

	//������
	m_pIClientKernel->ActiveGameFrame();

	return;
}

//�л�����
WORD CGameFrameEngine::SwitchViewChairID(WORD wChairID)
{
	//Ч�����
	ASSERT(m_pIClientKernel!=NULL);
	if (m_pIClientKernel==NULL) return INVALID_CHAIR;

	//ת������
	return m_pIClientKernel->SwitchViewChairID(wChairID);
}

//��������
bool CGameFrameEngine::PlayGameSound(LPCTSTR pszSoundName)
{
	//��������
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
	if (pGlobalUnits!=NULL) pGlobalUnits->PlayGameSound(pszSoundName);

	return true;
}

//��������
bool CGameFrameEngine::PlayGameSound(HINSTANCE hInstance, LPCTSTR pszSoundName)
{
	//��������
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
	if (pGlobalUnits!=NULL) pGlobalUnits->PlayGameSound(hInstance,pszSoundName);

	return true;
}

//��������
bool CGameFrameEngine::PlayBackGroundSound(LPCTSTR pszSoundName)
{
	//��������
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
	if (pGlobalUnits!=NULL) pGlobalUnits->PlayBackGroundSound(pszSoundName);

	return true;
}

//��������
bool CGameFrameEngine::PlayBackGroundSound(HINSTANCE hInstance, LPCTSTR pszSoundName)
{
	//��������
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
	if (pGlobalUnits!=NULL) pGlobalUnits->PlayBackGroundSound(hInstance,pszSoundName);

	return true;
}

//ֹͣ����
bool CGameFrameEngine::StopSound()
{
	//ֹͣ����
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
	if (pGlobalUnits!=NULL) pGlobalUnits->StopSound();

	return true;
}

//��������
bool CGameFrameEngine::ResetGameFrameEngine()
{
	//����֪ͨ
	if (OnResetGameEngine()==false)
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//��������
bool CGameFrameEngine::CreateGameFrameEngine()
{
	//��������
	ASSERT(CGlobalUnits::GetInstance()!=NULL);
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();

	//��ѯ�ӿ�
	m_pIClientKernel=(IClientKernel *)pGlobalUnits->QueryGlobalModule(MODULE_CLIENT_KERNEL,IID_IClientKernel,VER_IClientKernel);

	//�û��ӿ�
	IUserEventSink * pIUserEventSink=QUERY_ME_INTERFACE(IUserEventSink);
	if (pIUserEventSink!=NULL) m_pIClientKernel->SetUserEventSink(pIUserEventSink);

	//��Ϣ�ӿ�
	m_pIStringMessage=m_pIClientKernel->GetIStringMessage();

	//��������
	if (Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),AfxGetMainWnd(),IDC_GAME_FRAME_ENGINE)==FALSE)
	{
		ASSERT(FALSE);
		return false;
	}

	//����֪ͨ
	if (OnInitGameEngine()==false)
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//������Ϣ
bool CGameFrameEngine::OnEventInsureMessage(WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	return true;
}

//��ʾ��Ϣ
INT CGameFrameEngine::ShowMessageBox(LPCTSTR pszString, UINT uType, UINT nElapse)
{
	CInformation Information(this);
	return Information.ShowMessageBox(pszString, uType, nElapse);
}

//��ʾ��Ϣ
INT CGameFrameEngine::ShowMessageBox(LPCTSTR pszCaption, LPCTSTR pszString, UINT uType, UINT nElapse)
{
	CInformation Information(this);
	return Information.ShowMessageBox(pszCaption, pszString, uType, nElapse);
}

//�����¼�
bool CGameFrameEngine::OnGameOptionChange()
{
	//�������
	CGlobalUnits *pGlobalUnits=CGlobalUnits::GetInstance();

	//�¼�����
	AllowBackGroundSound(pGlobalUnits->m_bAllowBackGroundSound);

	return true;
}
//////////////////////////////////////////////////////////////////////////////////
