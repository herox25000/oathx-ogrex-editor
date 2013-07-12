#include "StdAfx.h"
#include "Resource.h"
#include "DlgServerManager.h"

//////////////////////////////////////////////////////////////////////////////////

//�궨��
#define COLOR_FRAME					RGB(239,249,255)					//�����ɫ
#define COLOR_BORAD					RGB(170,170,170)					//�߿���ɫ

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgServerManager, CSkinDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_REVENUE_RADIO, OnBnClickedRevenueRadio)
	ON_BN_CLICKED(IDC_SERVICE_RADIO, OnBnClickedServiceRadio)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgServerManager::CDlgServerManager() : CSkinDialog(IDD_DLG_SERVER_MANAGER)
{
	//���ñ���
	m_pITCPSocket=NULL;
	m_pIMySelfUserItem=NULL;
	m_wServerType=GAME_GENRE_SCORE;

	//������Դ
	m_FrameBrush.CreateSolidBrush(COLOR_FRAME);
	m_BoradPen.CreatePen(PS_SOLID,1,COLOR_BORAD);

	return;
}

//��������
CDlgServerManager::~CDlgServerManager()
{
}

//�ؼ���
VOID CDlgServerManager::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�󶨿ؼ�
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);

	//�б�����
	DDX_Control(pDX, IDC_KIND_ID, m_edKindID);
	DDX_Control(pDX, IDC_NODE_ID, m_edNodeID);
	DDX_Control(pDX, IDC_SORT_ID, m_edSortID);

	//��������
	DDX_Control(pDX, IDC_SERVER_NAME, m_edServerName);
	DDX_Control(pDX, IDC_SERVICE_REVENUE, m_edRevenueRatio);
	DDX_Control(pDX, IDC_RESTRICT_SCORE, m_edRestrictScore);

	//��������
	DDX_Control(pDX, IDC_MIN_ENTER_SCORE, m_edMinEnterScore);
	DDX_Control(pDX, IDC_MAX_ENTER_SCORE, m_edMaxEnterScore);
	DDX_Control(pDX, IDC_MIN_TABLE_SCORE, m_edMinTableScore);
	DDX_Control(pDX, IDC_MIN_ENTER_MEMBER, m_comMinEnterMember);
	DDX_Control(pDX, IDC_MAX_ENTER_MEMBER, m_comMaxEnterMember);
}

//���ú���
BOOL CDlgServerManager::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("���������� -- ������ֵ��"));

	//�б�����
	((CEdit *)GetDlgItem(IDC_KIND_ID))->LimitText(5);
	((CEdit *)GetDlgItem(IDC_NODE_ID))->LimitText(5);
	((CEdit *)GetDlgItem(IDC_SORT_ID))->LimitText(5);

	//��������
	((CEdit *)GetDlgItem(IDC_SERVER_NAME))->LimitText(31);
	((CEdit *)GetDlgItem(IDC_SERVICE_REVENUE))->LimitText(3);
	((CEdit *)GetDlgItem(IDC_RESTRICT_SCORE))->LimitText(9);

	//��������
	((CEdit *)GetDlgItem(IDC_MIN_ENTER_SCORE))->LimitText(8);
	((CEdit *)GetDlgItem(IDC_MAX_ENTER_SCORE))->LimitText(8);
	((CEdit *)GetDlgItem(IDC_MIN_TABLE_SCORE))->LimitText(8);

	//��Ա����
	LPCTSTR pszMember[]={TEXT("û������"),TEXT("�����Ա"),TEXT("�����Ա"),TEXT("�����Ա"),TEXT("�����Ա"),TEXT("VIP��Ա")};

	//��Ա��Ϣ
	for (INT i=0;i<CountArray(pszMember);i++)
	{
		m_comMinEnterMember.SetItemData(m_comMinEnterMember.AddString(pszMember[i]),i);
		m_comMaxEnterMember.SetItemData(m_comMaxEnterMember.AddString(pszMember[i]),i);
	}

	//���Ͳ�ѯ
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket!=NULL) m_pITCPSocket->SendData(MDM_GR_MANAGE,SUB_GR_QUERY_OPTION);

	return FALSE;
}

//ȷ������
VOID CDlgServerManager::OnOK()
{
	//��������
	CMD_GR_ServerOption ServerOption;
	ZeroMemory(&ServerOption,sizeof(ServerOption));

	//�ҽ�����
	ServerOption.ServerOptionInfo.wKindID=GetDlgItemInt(IDC_KIND_ID);
	ServerOption.ServerOptionInfo.wNodeID=GetDlgItemInt(IDC_NODE_ID);
	ServerOption.ServerOptionInfo.wSortID=GetDlgItemInt(IDC_SORT_ID);

	//��������
	ServerOption.ServerOptionInfo.cbMinEnterMember=0;
	ServerOption.ServerOptionInfo.cbMaxEnterMember=0;
	ServerOption.ServerOptionInfo.lMinEnterScore=GetDlgItemInt(IDC_MIN_ENTER_SCORE);
	ServerOption.ServerOptionInfo.lMaxEnterScore=GetDlgItemInt(IDC_MAX_ENTER_SCORE);
	ServerOption.ServerOptionInfo.lMinTableScore=GetDlgItemInt(IDC_MIN_TABLE_SCORE);

	//��������
	ServerOption.ServerOptionInfo.lRestrictScore=GetDlgItemInt(IDC_RESTRICT_SCORE);
	GetDlgItemText(IDC_SERVER_NAME,ServerOption.ServerOptionInfo.szServerName,CountArray(ServerOption.ServerOptionInfo.szServerName));
	if(((CButton*)GetDlgItem(IDC_REVENUE_RADIO))->GetCheck()==BST_CHECKED)
	{
		ServerOption.ServerOptionInfo.wRevenueRatio=GetDlgItemInt(IDC_SERVICE_REVENUE);
		ServerOption.ServerOptionInfo.lServiceScore=0L;
	}
	else
	{
		ServerOption.ServerOptionInfo.lServiceScore=GetDlgItemInt(IDC_SERVICE_REVENUE);
		ServerOption.ServerOptionInfo.wRevenueRatio=0L;
	}

	//��Ա����
	if (m_comMinEnterMember.GetCurSel()!=LB_ERR)
	{
		INT nCurSelect=m_comMinEnterMember.GetCurSel();
		ServerOption.ServerOptionInfo.cbMinEnterMember=(BYTE)m_comMinEnterMember.GetItemData(nCurSelect);
	}

	//��߻�Ա
	if (m_comMaxEnterMember.GetCurSel()!=LB_ERR)
	{
		INT nCurSelect=m_comMaxEnterMember.GetCurSel();
		ServerOption.ServerOptionInfo.cbMaxEnterMember=(BYTE)m_comMaxEnterMember.GetItemData(nCurSelect);
	}

	//��ֹ����
	CButton * pForfendGameChat=(CButton *)GetDlgItem(IDC_FORFEND_GAME_CHAT);
	CServerRule::SetForfendGameChat(ServerOption.ServerOptionInfo.dwServerRule,(pForfendGameChat->GetCheck()==BST_CHECKED));

	//��ֹ����
	CButton * pForfendRoomChat=(CButton *)GetDlgItem(IDC_FORFEND_ROOM_CHAT);
	CServerRule::SetForfendRoomChat(ServerOption.ServerOptionInfo.dwServerRule,(pForfendRoomChat->GetCheck()==BST_CHECKED));

	//��ֹ˽��
	CButton * pForfendWisperChat=(CButton *)GetDlgItem(IDC_FORFEND_WISPER_CHAT);
	CServerRule::SetForfendWisperChat(ServerOption.ServerOptionInfo.dwServerRule,(pForfendWisperChat->GetCheck()==BST_CHECKED));

	//��ֹ˽��
	CButton * pForfendWisperOnGame=(CButton *)GetDlgItem(IDC_FORFEND_WISPER_ON_GAME);
	CServerRule::SetForfendWisperOnGame(ServerOption.ServerOptionInfo.dwServerRule,(pForfendWisperOnGame->GetCheck()==BST_CHECKED));

	//��ֹ����
	CButton * pForfendRoomEnter=(CButton *)GetDlgItem(IDC_FORFEND_ROOM_ENTER);
	CServerRule::SetForfendRoomEnter(ServerOption.ServerOptionInfo.dwServerRule,(pForfendRoomEnter->GetCheck()==BST_CHECKED));

	//��ֹ����
	CButton * pForfendGameEnter=(CButton *)GetDlgItem(IDC_FORFEND_GAME_ENTER);
	CServerRule::SetForfendGameEnter(ServerOption.ServerOptionInfo.dwServerRule,(pForfendGameEnter->GetCheck()==BST_CHECKED));

	//��ֹ�Թ�
	CButton * pForfendGameLookon=(CButton *)GetDlgItem(IDC_FORFEND_GAME_LOOKON);
	CServerRule::SetForfendGameLookon(ServerOption.ServerOptionInfo.dwServerRule,(pForfendGameLookon->GetCheck()==BST_CHECKED));

	//��ֹ����
	CButton * pForfendGameRule=(CButton *)GetDlgItem(IDC_FORFEND_GAME_RULE);
	CServerRule::SetForfendGameRule(ServerOption.ServerOptionInfo.dwServerRule,(pForfendGameRule->GetCheck()==BST_CHECKED));

	//��ֹ����
	CButton * pForfendLockTable=(CButton *)GetDlgItem(IDC_FORFEND_LOCK_TABLE);
	CServerRule::SetForfendLockTable(ServerOption.ServerOptionInfo.dwServerRule,(pForfendLockTable->GetCheck()==BST_CHECKED));

	//��¼����
	CButton * pRecordGameScore=(CButton *)GetDlgItem(IDC_RECORD_GAME_SCORE);
	CServerRule::SetRecordGameScore(ServerOption.ServerOptionInfo.dwServerRule,(pRecordGameScore->GetCheck()==BST_CHECKED));

	//��¼����
	CButton * pRecordGameTrack=(CButton *)GetDlgItem(IDC_RECORD_GAME_TRACK);
	CServerRule::SetRecordGameTrack(ServerOption.ServerOptionInfo.dwServerRule,(pRecordGameTrack->GetCheck()==BST_CHECKED));

	//��ʱд��
	CButton * pImmediateWriteScore=(CButton *)GetDlgItem(IDC_IMMEDIATE_WRITE_SCORE);
	CServerRule::SetImmediateWriteScore(ServerOption.ServerOptionInfo.dwServerRule,(pImmediateWriteScore->GetCheck()==BST_CHECKED));

	//��̬�׷�
	CButton * pDynamicCellScore=(CButton *)GetDlgItem(IDC_DYNAMIC_CELL_SCORE);
	CServerRule::SetDynamicCellScore(ServerOption.ServerOptionInfo.dwServerRule,(pDynamicCellScore->GetCheck()==BST_CHECKED));

	//������Ϣ
	CButton * pAllowAvertCheatMode=(CButton *)GetDlgItem(IDC_ALLOW_AVERT_CHEAT_MODE);
	CServerRule::SetAllowAvertCheatMode(ServerOption.ServerOptionInfo.dwServerRule,(pAllowAvertCheatMode->GetCheck()==BST_CHECKED));

	//��ֹ��Ǯ
	CButton * pForfendSaveInRoom=(CButton *)GetDlgItem(IDC_FORFEND_SAVE_IN_ROOM);
	CServerRule::SetForfendSaveInRoom(ServerOption.ServerOptionInfo.dwServerRule,(pForfendSaveInRoom->GetCheck()==BST_CHECKED));

	//��ֹ��Ǯ
	CButton * pForfendSaveInGame=(CButton *)GetDlgItem(IDC_FORFEND_SAVE_IN_GAME);
	CServerRule::SetForfendSaveInGame(ServerOption.ServerOptionInfo.dwServerRule,(pForfendSaveInGame->GetCheck()==BST_CHECKED));

	//��̬����
	CButton * pAllowDynamicJoin=(CButton *)GetDlgItem(IDC_ALLOW_DYNAMIC_JOIN);
	CServerRule::SetAllowDynamicJoin(ServerOption.ServerOptionInfo.dwServerRule,(pAllowDynamicJoin->GetCheck()==BST_CHECKED));

	//���ߴ���
	CButton * pAllowOffLineTrustee=(CButton *)GetDlgItem(IDC_ALLOW_OFFLINE_TRUSTEE);
	CServerRule::SetAllowOffLineTrustee(ServerOption.ServerOptionInfo.dwServerRule,(pAllowOffLineTrustee->GetCheck()==BST_CHECKED));

	//�������
	CButton * pAllowAndroidAttend=(CButton *)GetDlgItem(IDC_ALLOW_ANDROID_ATTEND);
	CServerRule::SetAllowAndroidAttend(ServerOption.ServerOptionInfo.dwServerRule,(pAllowAndroidAttend->GetCheck()==BST_CHECKED));

	//��������
	if (ServerOption.ServerOptionInfo.szServerName[0]==0)
	{
		CInformation Information;
		Information.ShowMessageBox(TEXT("��Ϸ�������ֲ���Ϊ�գ���������Ϸ��������"),MB_ICONERROR);
		return;
	}

	//����Ч��
	if ((ServerOption.ServerOptionInfo.lMaxEnterScore!=0L)&&(ServerOption.ServerOptionInfo.lMaxEnterScore<ServerOption.ServerOptionInfo.lMinEnterScore))
	{
		CInformation Information;
		Information.ShowMessageBox(TEXT("���뷿����ͳɼ�����߳ɼ����ߣ���������κ���Ҷ����ܽ���"),MB_ICONERROR);
		return;
	}

	//����Ч��
	if ((ServerOption.ServerOptionInfo.cbMaxEnterMember!=0L)&&(ServerOption.ServerOptionInfo.cbMaxEnterMember<ServerOption.ServerOptionInfo.cbMinEnterMember))
	{
		CInformation Information;
		Information.ShowMessageBox(TEXT("���뷿����ͻ�Ա�������߻�Ա���𻹸ߣ���������κ���Ҷ����ܽ���"),MB_ICONERROR);
		return;
	}

	//��������
	ASSERT(m_pITCPSocket!=NULL);
	m_pITCPSocket->SendData(MDM_GR_MANAGE,SUB_GR_OPTION_SERVER,&ServerOption,sizeof(ServerOption));

	__super::OnOK();
}

//�滭��Ϣ
VOID CDlgServerManager::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//ѡ�����
	pDC->SelectObject(m_BoradPen);
	pDC->SelectObject(m_FrameBrush);

	//�滭�׿�
	pDC->RoundRect(20,47,510,162,5,5);
	pDC->RoundRect(20,172,510,320,5,5);
	pDC->RoundRect(20,330,510,475,5,5);

	return;
}

//���ù���
VOID CDlgServerManager::Initialization(ITCPSocket * pITCPSocket, IClientUserItem * pIMySelfUserItem)
{
	//���ñ���
	m_pITCPSocket=pITCPSocket;
	m_pIMySelfUserItem=pIMySelfUserItem;

	return;
}

//��������
VOID CDlgServerManager::SetServerOptionInfo(tagServerOptionInfo & ServerOptionInfo, DWORD dwRuleMask)
{
	//�ҽ�����
	if (ServerOptionInfo.wNodeID!=0) SetDlgItemInt(IDC_NODE_ID,ServerOptionInfo.wNodeID);
	if (ServerOptionInfo.wSortID!=0) SetDlgItemInt(IDC_SORT_ID,ServerOptionInfo.wSortID);
	if (ServerOptionInfo.wKindID!=0) SetDlgItemInt(IDC_KIND_ID,ServerOptionInfo.wKindID);

	//��������
	if (ServerOptionInfo.szServerName[0]!=0) SetDlgItemText(IDC_SERVER_NAME,ServerOptionInfo.szServerName);
	if (ServerOptionInfo.lRestrictScore!=0) SetDlgItemInt(IDC_RESTRICT_SCORE,(LONG)ServerOptionInfo.lRestrictScore);
	if (ServerOptionInfo.wRevenueRatio!=0)
	{
		((CButton*)GetDlgItem(IDC_REVENUE_RADIO))->SetCheck(BST_CHECKED);
		OnBnClickedRevenueRadio();
		SetDlgItemInt(IDC_SERVICE_REVENUE,(LONG)ServerOptionInfo.wRevenueRatio);
	}
	else if(ServerOptionInfo.lServiceScore != 0)
	{
		((CButton*)GetDlgItem(IDC_SERVICE_RADIO))->SetCheck(BST_CHECKED);
		OnBnClickedServiceRadio();
		SetDlgItemInt(IDC_SERVICE_REVENUE,(LONG)ServerOptionInfo.lServiceScore);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_REVENUE_RADIO))->SetCheck(BST_CHECKED);
		OnBnClickedRevenueRadio();
	}

	//��������
	SetDlgItemInt(IDC_MIN_ENTER_SCORE,(LONG)ServerOptionInfo.lMinEnterScore);
	SetDlgItemInt(IDC_MAX_ENTER_SCORE,(LONG)ServerOptionInfo.lMaxEnterScore);
	if (ServerOptionInfo.lMinTableScore!=0) SetDlgItemInt(IDC_MIN_TABLE_SCORE,(LONG)ServerOptionInfo.lMinTableScore);

	//��Ա����
	if (ServerOptionInfo.cbMaxEnterMember!=0)
	{
		//��ͻ�Ա
		for (INT i=0;i<m_comMinEnterMember.GetCount();i++)
		{
			if (m_comMinEnterMember.GetItemData(i)==ServerOptionInfo.cbMinEnterMember)
			{
				m_comMinEnterMember.SetCurSel(i);
				break;
			}
		}

		//��߻�Ա
		for (INT i=0;i<m_comMaxEnterMember.GetCount();i++)
		{
			if (m_comMaxEnterMember.GetItemData(i)==ServerOptionInfo.cbMaxEnterMember)
			{
				m_comMaxEnterMember.SetCurSel(i);
				break;
			}
		}
	}

	//��ֹ����
	bool bForfendGameChat=CServerRule::IsForfendGameChat(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_CHAT))->EnableWindow(CServerRule::IsForfendGameChat(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_CHAT))->SetCheck((bForfendGameChat)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ����
	bool bForfendRoomChat=CServerRule::IsForfendRoomChat(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_ROOM_CHAT))->EnableWindow(CServerRule::IsForfendRoomChat(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_ROOM_CHAT))->SetCheck((bForfendRoomChat)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ˽��
	bool bForfendWisperChat=CServerRule::IsForfendWisperChat(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_WISPER_CHAT))->EnableWindow(CServerRule::IsForfendWisperChat(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_WISPER_CHAT))->SetCheck((bForfendWisperChat)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ˽��
	bool bForfendWisperOnGame=CServerRule::IsForfendWisperOnGame(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_WISPER_ON_GAME))->EnableWindow(CServerRule::IsForfendWisperOnGame(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_WISPER_ON_GAME))->SetCheck((bForfendWisperOnGame)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ����
	bool bForfendRoomEnter=CServerRule::IsForfendRoomEnter(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_ROOM_ENTER))->EnableWindow(CServerRule::IsForfendRoomEnter(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_ROOM_ENTER))->SetCheck((bForfendRoomEnter)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ����
	bool bForfendGameEnter=CServerRule::IsForfendGameEnter(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_ENTER))->EnableWindow(CServerRule::IsForfendGameEnter(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_ENTER))->SetCheck((bForfendGameEnter)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ�Թ�
	bool bForfendGameLookon=CServerRule::IsForfendGameLookon(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_LOOKON))->EnableWindow(CServerRule::IsForfendGameLookon(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_LOOKON))->SetCheck((bForfendGameLookon)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ����
	bool bForfendGameRule=CServerRule::IsForfendGameRule(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_RULE))->EnableWindow(CServerRule::IsForfendGameRule(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_GAME_RULE))->SetCheck((bForfendGameRule)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ����
	bool bForfendLockTable=CServerRule::IsForfendLockTable(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_LOCK_TABLE))->EnableWindow(CServerRule::IsForfendLockTable(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_LOCK_TABLE))->SetCheck((bForfendLockTable)?BST_CHECKED:BST_UNCHECKED);

	//��¼����
	bool bRecordGameScore=CServerRule::IsRecordGameScore(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_RECORD_GAME_SCORE))->EnableWindow(CServerRule::IsRecordGameScore(dwRuleMask));
	((CButton *)GetDlgItem(IDC_RECORD_GAME_SCORE))->SetCheck((bRecordGameScore)?BST_CHECKED:BST_UNCHECKED);

	//��¼����
	//bool bRecordGameTrack=CServerRule::IsRecordGameTrack(ServerOptionInfo.dwServerRule);
	//((CButton *)GetDlgItem(IDC_RECORD_GAME_TRACK))->EnableWindow(CServerRule::IsRecordGameTrack(dwRuleMask));
	//((CButton *)GetDlgItem(IDC_RECORD_GAME_TRACK))->SetCheck((bRecordGameTrack)?BST_CHECKED:BST_UNCHECKED);
	((CButton *)GetDlgItem(IDC_RECORD_GAME_TRACK))->SetCheck(BST_UNCHECKED);
	((CButton *)GetDlgItem(IDC_RECORD_GAME_TRACK))->EnableWindow(FALSE);

	//��ʱд��
	bool bImmediateWriteScore=(m_wServerType==GAME_GENRE_GOLD)?true:CServerRule::IsImmediateWriteScore(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_IMMEDIATE_WRITE_SCORE))->EnableWindow((m_wServerType==GAME_GENRE_GOLD)?FALSE:CServerRule::IsImmediateWriteScore(dwRuleMask));
	((CButton *)GetDlgItem(IDC_IMMEDIATE_WRITE_SCORE))->SetCheck((bImmediateWriteScore)?BST_CHECKED:BST_UNCHECKED);

	//��̬�׷�
	bool bDynamicCellScore=CServerRule::IsDynamicCellScore(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_DYNAMIC_CELL_SCORE))->EnableWindow(FALSE);//CServerRule::IsDynamicCellScore(dwRuleMask));
	((CButton *)GetDlgItem(IDC_DYNAMIC_CELL_SCORE))->SetCheck((bDynamicCellScore)?BST_CHECKED:BST_UNCHECKED);

	//������Ϣ
	bool bAllowAvertCheatMode=CServerRule::IsAllowAvertCheatMode(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_ALLOW_AVERT_CHEAT_MODE))->EnableWindow(CServerRule::IsAllowAvertCheatMode(dwRuleMask));
	((CButton *)GetDlgItem(IDC_ALLOW_AVERT_CHEAT_MODE))->SetCheck((bAllowAvertCheatMode)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ��Ǯ
	bool bForfendSaveInRoom=CServerRule::IsForfendSaveInRoom(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_SAVE_IN_ROOM))->EnableWindow(CServerRule::IsForfendSaveInRoom(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_SAVE_IN_ROOM))->SetCheck((bForfendSaveInRoom)?BST_CHECKED:BST_UNCHECKED);

	//��ֹ��Ǯ
	bool bForfendSaveInGame=CServerRule::IsForfendSaveInGame(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_FORFEND_SAVE_IN_GAME))->EnableWindow(CServerRule::IsForfendSaveInGame(dwRuleMask));
	((CButton *)GetDlgItem(IDC_FORFEND_SAVE_IN_GAME))->SetCheck((bForfendSaveInGame)?BST_CHECKED:BST_UNCHECKED);

	//��̬����
	bool bAllowDynamicJoin=CServerRule::IsAllowDynamicJoin(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_ALLOW_DYNAMIC_JOIN))->EnableWindow(CServerRule::IsAllowDynamicJoin(dwRuleMask));
	((CButton *)GetDlgItem(IDC_ALLOW_DYNAMIC_JOIN))->SetCheck((bAllowDynamicJoin)?BST_CHECKED:BST_UNCHECKED);

	//�������
	bool bAllowAndroidAttend=CServerRule::IsAllowAndroidAttend(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_ALLOW_ANDROID_ATTEND))->EnableWindow(CServerRule::IsAllowAndroidAttend(dwRuleMask));
	((CButton *)GetDlgItem(IDC_ALLOW_ANDROID_ATTEND))->SetCheck((bAllowAndroidAttend)?BST_CHECKED:BST_UNCHECKED);

	//�������ռλ
	bool bAllowAndroidSimulate=CServerRule::IsAllowAndroidSimulate(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_ALLOW_ANDROID_SIMULATE))->EnableWindow(CServerRule::IsAllowAndroidSimulate(dwRuleMask));
	((CButton *)GetDlgItem(IDC_ALLOW_ANDROID_SIMULATE))->SetCheck((bAllowAndroidSimulate)?BST_CHECKED:BST_UNCHECKED);

	//���ߴ���
	bool bAllowOffLineTrustee=CServerRule::IsAllowOffLineTrustee(ServerOptionInfo.dwServerRule);
	((CButton *)GetDlgItem(IDC_ALLOW_OFFLINE_TRUSTEE))->EnableWindow(CServerRule::IsAllowOffLineTrustee(dwRuleMask));
	((CButton *)GetDlgItem(IDC_ALLOW_OFFLINE_TRUSTEE))->SetCheck((bAllowOffLineTrustee)?BST_CHECKED:BST_UNCHECKED);

	//���ÿؼ�
	m_btOk.EnableWindow(TRUE);

	return;
}

//��ɫ��Ϣ
HBRUSH CDlgServerManager::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(COLOR_FRAME);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return m_FrameBrush;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

void CDlgServerManager::OnBnClickedRevenueRadio()
{
	//
	GetDlgItem(IDC_STATIC_REVENUE_SERVICE)->SetWindowText(TEXT("˰�ձ�����"));
	((CEdit *)GetDlgItem(IDC_SERVICE_REVENUE))->SetWindowText(TEXT(""));
	((CEdit *)GetDlgItem(IDC_SERVICE_REVENUE))->LimitText(3);
}

void CDlgServerManager::OnBnClickedServiceRadio()
{
	//
	GetDlgItem(IDC_STATIC_REVENUE_SERVICE)->SetWindowText(TEXT("���������"));
	((CEdit *)GetDlgItem(IDC_SERVICE_REVENUE))->SetWindowText(TEXT(""));
	((CEdit *)GetDlgItem(IDC_SERVICE_REVENUE))->LimitText(9);
}
//////////////////////////////////////////////////////////////////////////////////
