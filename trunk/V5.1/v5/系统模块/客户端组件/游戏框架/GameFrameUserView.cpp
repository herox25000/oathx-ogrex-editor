#include "StdAfx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "GameFrameUserView.h"

//////////////////////////////////////////////////////////////////////////////////

//���ƫ��
#define	BILL_T						5									//����ϸ�
#define	BILL_L						7									//������
#define	BILL_R						6									//����ҿ�
#define	BILL_B						118  								//����¸�

//���ƫ��
#define PANEL_T						5									//����ϸ�
#define PANEL_L						7									//������
#define PANEL_R						5									//����ҿ�
#define PANEL_B						2									//����¸�

//�ؼ���ʾ
#define IDC_WEB_PUBLICIZE			100									//����ؼ�
#define IDC_BT_USER_MEDAL			101									//�һ�����
#define IDC_BT_LOVE_LINESS			102									//�һ�����
#define IDC_CUSTOM_PANEL            104                                 //�Զ������

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameUserView, CWnd)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()

	//��ť��Ϣ
	ON_BN_CLICKED(IDC_BT_USER_MEDAL, OnBnClickedUserMedal)
	ON_BN_CLICKED(IDC_BT_LOVE_LINESS, OnBnClickedLoveLiness)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameUserView::CGameFrameUserView()
{
	//���ñ���
	m_pIClientKernel=NULL;
	m_pICurrentUserItem=NULL;
	m_pCustomPanel=NULL;

	return;
}

//��������
CGameFrameUserView::~CGameFrameUserView()
{
}

//���ù��
VOID CGameFrameUserView::SetGameBillInfo(WORD wKindID, WORD wServerID)
{
	//�����ַ
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s/Ads/GameFrame.aspx?KindID=%ld&ServerID=%ld"),szPlatformLink,wKindID,wServerID);

	//�򿪵�ַ
	m_GameFramePublicize.Navigate(szBillUrl);

	return;
}

//�����û�
VOID CGameFrameUserView::SetUserViewInfo(IClientUserItem * pIClientUserItem)
{
	//�����û�
	if (m_pICurrentUserItem!=pIClientUserItem)
	{
		//���ñ���
		m_pICurrentUserItem=pIClientUserItem;

		//���½���
		if (m_hWnd!=NULL)
		{
			RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
		}
	}

	return;
}

//�Զ����
VOID CGameFrameUserView::SetCustomPanel(CWnd * pCustomPanel)
{
	//����У��
	ASSERT(pCustomPanel!=NULL);
	if(pCustomPanel==NULL) return;

	//���ñ���
	m_pCustomPanel = pCustomPanel;

	//���ٴ���
	if(m_pCustomPanel->GetSafeHwnd()!=NULL) m_pCustomPanel->DestroyWindow();

	//��������
	try
	{
		CRect rcCreate(0,0,0,0);
		m_pCustomPanel->Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,rcCreate,this,IDC_CUSTOM_PANEL);
	}
	catch(LPCTSTR pszMessage)
	{
		//���ñ���
		if(m_pCustomPanel->GetSafeHwnd()) m_pCustomPanel->DestroyWindow();
		m_pCustomPanel = NULL;

		//�׳��쳣
		throw(pszMessage);
	}

	//�����ؼ�
	CRect rcWindow(0,0,0,0);
	GetWindowRect(&rcWindow);
	RectifyControl(rcWindow.Width(),rcWindow.Height());

	return;
}

//�����ؼ�
VOID CGameFrameUserView::RectifyControl(INT nWidth, INT nHeight)
{
	//��ȡ��С
	///*CRect rcButton;
	//m_btUserMedal.GetWindowRect(&rcButton);*/

	//����λ��
	/*INT nXBorad=12L;
	INT nXButtonPos=(nWidth-rcButton.Width()*2L-nXBorad*2L)/3L;*/

	////������ť
	//m_btUserMedal.SetWindowPos(NULL,nXBorad+nXButtonPos,nHeight-rcButton.Height()-6,0,0,SWP_NOZORDER|SWP_NOSIZE);
	//m_btLoveLiness.SetWindowPos(NULL,nXBorad+nXButtonPos*2+rcButton.Width(),nHeight-rcButton.Height()-6,0,0,SWP_NOZORDER|SWP_NOSIZE);	

	HDWP hDwp=BeginDeferWindowPos(32);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	//�Զ����
	if(m_pCustomPanel!=NULL && m_pCustomPanel->GetSafeHwnd()!=NULL)
	{
		DeferWindowPos(hDwp,*m_pCustomPanel,NULL,PANEL_L,PANEL_T,nWidth-PANEL_L-PANEL_R,nHeight-PANEL_T-PANEL_B,uFlags);
	}//�������
	else if (m_GameFramePublicize.m_hWnd!=NULL) 
	{
		DeferWindowPos(hDwp,m_GameFramePublicize,NULL,BILL_L,BILL_T,nWidth-BILL_L-BILL_R,nHeight-BILL_T-BILL_B,uFlags);
	}

	//�����ƶ�
	EndDeferWindowPos(hDwp);

	return;
}

//���ƶһ�
VOID CGameFrameUserView::OnBnClickedUserMedal()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/UserMedal.aspx"),szPlatformLink);

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//�����һ�
VOID CGameFrameUserView::OnBnClickedLoveLiness()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("LoveLiness.aspx"));

	//��ҳ��
	CDlgBrowser DlgBrowser;
	DlgBrowser.CreateBrowserControl(TEXT("�����һ�"),szLogonLink,CSize(730,450));

	return;
}

//�滭����
BOOL CGameFrameUserView::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SetTextAlign(TA_LEFT|TA_TOP);
	pBufferDC->SetTextColor(RGB(250,250,250));
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//������Դ
	CImage ImageUserInfoL;
	CImage ImageUserInfoM;
	CImage ImageUserInfoR;
	ImageUserInfoL.LoadFromResource(GetModuleHandle(GAME_FRAME_DLL_NAME),IDB_USER_INFO_L);
	ImageUserInfoM.LoadFromResource(GetModuleHandle(GAME_FRAME_DLL_NAME),IDB_USER_INFO_M);
	ImageUserInfoR.LoadFromResource(GetModuleHandle(GAME_FRAME_DLL_NAME),IDB_USER_INFO_R);

	//��������
	INT nXStartPos=ImageUserInfoL.GetWidth();
	INT nXConcludePos=rcClient.Width()-ImageUserInfoR.GetWidth();

	//�滭���
	ImageUserInfoL.BitBlt(BufferDC,0,0);
	ImageUserInfoR.BitBlt(BufferDC,rcClient.Width()-ImageUserInfoR.GetWidth(),0);

	//�滭�м�
	for (INT nXPos=nXStartPos;nXPos<nXConcludePos;nXPos+=ImageUserInfoM.GetWidth())
	{
		INT nCXDraw=__min(ImageUserInfoM.GetWidth(),nXConcludePos-nXPos);
		ImageUserInfoM.BitBlt(BufferDC,nXPos,0,nCXDraw,ImageUserInfoM.GetHeight(),0,0);
	}

	//�滭�û�
	if (m_pICurrentUserItem!=NULL)
	{
		//��������
		INT nYExcursion=90L;
		TCHAR szString[128]=TEXT("");

		//��������
		tagUserInfo * pUserInfo=m_pICurrentUserItem->GetUserInfo();
		tagGameAttribute * pGameAttribute=m_pIClientKernel->GetGameAttribute();
		tagCustomFaceInfo * pCustomFaceInfo=m_pICurrentUserItem->GetCustomFaceInfo();

		//��������
		CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
		CFaceItemControl * pFaceItemControl=CFaceItemControl::GetInstance();
		CUserItemElement * pUserItemElement=CUserItemElement::GetInstance();

		//�ӿڱ���
		IUserOrderParser * pIUserOrderParser=pGlobalUnits->m_UserOrderParserModule.GetInterface();
		IGameLevelParser * pIGameLevelParser=pGlobalUnits->m_GameLevelParserModule.GetInterface();

		//�滭ͷ��
		if ((pCustomFaceInfo->dwDataSize!=0L)&&(m_pICurrentUserItem->GetCustomID()!=0L))
		{
			pFaceItemControl->DrawFaceNormal(pBufferDC,21,nYExcursion-2,pCustomFaceInfo->dwCustomFace);
		}
		else
		{
			pFaceItemControl->DrawFaceNormal(pBufferDC,21,nYExcursion-2,m_pICurrentUserItem->GetFaceID());
		}

		//λ�ö���
		CRect rcNickName(80,nYExcursion-1,rcClient.Width()-12,nYExcursion+11);
		CRect rcExperience(80,nYExcursion+16,rcClient.Width()-12,nYExcursion+28);
		CRect rcUserGameID(80,nYExcursion+35,rcClient.Width()-12,nYExcursion+47);

		//λ�ö���
		CRect rcGameLevel(24,nYExcursion+55,rcClient.Width()-12,nYExcursion+67);
		CRect rcGameDrawInfo(24,nYExcursion+74,rcClient.Width()-12,nYExcursion+86);

		//������Ϣ
		DWORD dwExperience=m_pICurrentUserItem->GetUserExperience();
		WORD wExperienceLevel=pUserItemElement->GetExperienceLevel(dwExperience);

		//�û���Ϣ
		LPCTSTR pszMember=pIUserOrderParser->GetMemberDescribe(m_pICurrentUserItem->GetMemberOrder());
		LPCTSTR pszMaster=pIUserOrderParser->GetMasterDescribe(m_pICurrentUserItem->GetMasterOrder());

		//�û���Ϣ
		LPCTSTR pszUserOrder=(pszMaster[0]!=0)?pszMaster:((pszMember[0]!=0)?pszMember:TEXT("��ͨ���"));
		_sntprintf(szString,CountArray(szString),TEXT("�ǳƣ�%s [ %s ]"),m_pICurrentUserItem->GetNickName(),pszUserOrder);
		pBufferDC->DrawText(szString,lstrlen(szString),&rcNickName,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//�û�����
		_sntprintf(szString,CountArray(szString),TEXT("���飺%d ��"),wExperienceLevel);
		pBufferDC->DrawText(szString,lstrlen(szString),&rcExperience,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//�����־
		CSize SizeExperience=pDC->GetTextExtent(szString,lstrlen(szString));
		pUserItemElement->DrawExperience(pBufferDC,rcExperience.left+SizeExperience.cx+6,rcExperience.top-4L,dwExperience);

		//��Ϸ��ʶ
		_sntprintf(szString,CountArray(szString),TEXT(" I D��%ld"),pUserInfo->dwGameID);
		pBufferDC->DrawText(szString,lstrlen(szString),&rcUserGameID,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//���ֵȼ�
		LPCTSTR pszGameLevel=pIGameLevelParser->GetLevelDescribe(m_pICurrentUserItem);
		if(m_pIClientKernel!=NULL && (m_pIClientKernel->GetServerAttribute()->wServerType&GAME_GENRE_GOLD)!=0)
		{
			_sntprintf(szString,CountArray(szString),TEXT("��ң�") SCORE_STRING TEXT(" �ȼ���%s [ %s ]"),pUserInfo->lScore	,pszGameLevel,pGameAttribute->szGameName);
		}
		else
		{
			_sntprintf(szString,CountArray(szString),TEXT("�ɼ���") SCORE_STRING TEXT(" �ȼ���%s [ %s ]"),pUserInfo->lScore	,pszGameLevel,pGameAttribute->szGameName);
		}
		pBufferDC->DrawText(szString,lstrlen(szString),&rcGameLevel,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

		//��Ϸ��Ϣ
		LONG lPlayCount=m_pICurrentUserItem->GetUserPlayCount();
		float fUserWinRate=m_pICurrentUserItem->GetUserWinRate();
		float fUserFleeRate=m_pICurrentUserItem->GetUserFleeRate();
		_sntprintf(szString,CountArray(szString),TEXT("������%ld ʤ�ʣ�%.2f%% ���ʣ�%.2f%%"),lPlayCount,fUserWinRate,fUserFleeRate);
		pBufferDC->DrawText(szString,lstrlen(szString),&rcGameDrawInfo,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//λ����Ϣ
VOID CGameFrameUserView::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	return;
}

//������Ϣ
INT CGameFrameUserView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//��ѯ�ӿ�
	ASSERT(CGlobalUnits::GetInstance()->m_ClientKernelModule.GetInterface()!=NULL);
	m_pIClientKernel=CGlobalUnits::GetInstance()->m_ClientKernelModule.GetInterface();

	//�����ؼ�
	CRect rcCreate(0,0,0,0);
	/*m_btUserMedal.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BT_USER_MEDAL);
	m_btLoveLiness.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BT_LOVE_LINESS);*/

	//���ð�ť
	/*HINSTANCE hInstance=GetModuleHandle(GAME_FRAME_DLL_NAME);
	m_btUserMedal.SetButtonImage(IDB_BT_USER_INFO,TEXT("BT_USER_DEMAL"),hInstance,false,false);
	m_btLoveLiness.SetButtonImage(IDB_BT_USER_INFO,TEXT("BT_LOVE_LINESS"),hInstance,false,false);*/

	//�������
	m_GameFramePublicize.SetBoradColor(RGB(0,0,0));
	m_GameFramePublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
