#include "Stdafx.h"
#include "GamePlaza.h"
#include "DlgService.h"
#include "PlatformFrame.h"
#include "DlgLockMachine.h"
#include "WndUserInfoCtrl.h"

//////////////////////////////////////////////////////////////////////////////////

//���ư�ť
#define IDC_USER_INFO_1				100									//�û���ť
#define IDC_USER_INFO_2				101									//�û���ť
#define IDC_USER_INFO_3				102									//�û���ť

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWndUserInfoCtrl, CWnd)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()

	//�Զ���Ϣ
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)


END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CWndUserInfoCtrl::CWndUserInfoCtrl()
{
	//��������
	m_pDlgInsurePlaza = NULL;
}

//��������
CWndUserInfoCtrl::~CWndUserInfoCtrl()
{
}

//�����
BOOL CWndUserInfoCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��������
	UINT nCommandID=LOWORD(wParam);

	//���ܰ�ť
	switch (nCommandID)
	{
	case IDC_USER_INFO_1:		//��������
		{
			//��������
			CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
			if(pGlobalUnits!=NULL)
			{
				pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
			}

			//��������
			CDlgService DlgService;
			DlgService.DoModal();
						
			return TRUE;
		}
	case IDC_USER_INFO_2:		//������Ϣ
		{
			//��������
			CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
			if(pGlobalUnits!=NULL)
			{
				pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
			}

			//������Դ
			AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

			//��ȡָ��
			CPlatformFrame * pPlatformFrame =  (CPlatformFrame *)CPlatformFrame::GetInstance();
			if(pPlatformFrame->m_pServerViewItem != NULL )
			{
				pPlatformFrame->m_pServerViewItem->ShowInsureView();
			}
			else
			{
				//�㳡����
				CDlgInsurePlaza DlgInsurePlaza;

				//���ñ���
				m_pDlgInsurePlaza =&DlgInsurePlaza;
				INT_PTR nResult=DlgInsurePlaza.DoModal();

				m_pDlgInsurePlaza=NULL;
			}

			break;
		}
	case IDC_USER_INFO_3:		//��ʷ��¼
		{
			//��������
			CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
			if(pGlobalUnits!=NULL)
			{
				pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
			}

			//�û���Ϣ
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			DWORD dwUserID = pGlobalUserData?pGlobalUserData->dwUserID:0L;

			//��������
			TCHAR szOpenAddr[96] = TEXT("");
			_sntprintf(szOpenAddr,CountArray(szOpenAddr),TEXT("UserService/UService2.aspx?UID=%d&PWD=%s"),dwUserID,pGlobalUserData->szPassword);
			
			//��������
			CDlgServiceWebBrowse DlgServiceWebBrowse(TEXT("�����¼"),szOpenAddr);
			DlgServiceWebBrowse.DoModal();

			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//λ����Ϣ
VOID CWndUserInfoCtrl::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	return;
}

//������Ϣ
INT CWndUserInfoCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//ע���¼�
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//������Դ
	CBitImage ImageTitleM;
	ImageTitleM.LoadFromResource(AfxGetInstanceHandle(),IDB_USER_INFO_M);

	//������ť
	CRect rcCreate(0,0,0,0);
	m_btUserInfo1.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_USER_INFO_1);
	m_btUserInfo2.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_USER_INFO_2);
	m_btUserInfo3.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_USER_INFO_3);

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btUserInfo1.SetButtonImage(IDB_BK_USER_INFO,TEXT("BT_USER_INFO_1"),hInstance,true,false);
	m_btUserInfo2.SetButtonImage(IDB_BK_USER_INFO,TEXT("BT_USER_INFO_2"),hInstance,true,false);
	m_btUserInfo3.SetButtonImage(IDB_BK_USER_INFO,TEXT("BT_USER_INFO_3"),hInstance,true,false);

	//�ƶ�����
	CRect rcUserInfo;
	GetWindowRect(&rcUserInfo);
	SetWindowPos(NULL,0,0,rcUserInfo.Width(),ImageTitleM.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);

	return 0;
}

//�����ؼ�
VOID CWndUserInfoCtrl::RectifyControl(INT nWidth, INT nHeight)
{
	//��������
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE;

	//��ť��С
	CRect rcButton;
	m_btUserInfo1.GetWindowRect(&rcButton);

	//λ�ö���
	UINT nSpace=1;
	UINT nXStartPos=18;
	UINT nYStartPos=120;

	//������ť
	DeferWindowPos(hDwp,m_btUserInfo1,NULL,nXStartPos,nYStartPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btUserInfo2,NULL,nXStartPos,nYStartPos+rcButton.Height()+nSpace,0,0,uFlags);
	DeferWindowPos(hDwp,m_btUserInfo3,NULL,nXStartPos,nYStartPos+(rcButton.Height()+nSpace)*2,0,0,uFlags);

	//��������
	EndDeferWindowPos(hDwp);

	return;
}


//ת���ַ�
VOID CWndUserInfoCtrl::SwitchScoreFormat(SCORE lScore, UINT uSpace,UINT uDecimalCount,LPTSTR pszBuffer, WORD wBufferSize)
{
	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%d"),lScore);

	//��������
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore)-uDecimalCount-1;

	//ת���ַ�
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//�����ַ�
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//���붺��
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L) && (uSwitchLength-wSourceIndex)!=0)
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//�����ַ�
	pszBuffer[wTargetIndex++]=0;

	return;
}

//�滭����
BOOL CWndUserInfoCtrl::OnEraseBkgnd(CDC * pDC)
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

	//��������
	HINSTANCE hInstance=AfxGetInstanceHandle();
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	//������Դ
	CBitImage ImageTitleL;
	CBitImage ImageTitleM;
	CBitImage ImageTitleR;
	ImageTitleL.LoadFromResource(hInstance,IDB_USER_INFO_L);
	ImageTitleM.LoadFromResource(hInstance,IDB_USER_INFO_M);
	ImageTitleR.LoadFromResource(hInstance,IDB_USER_INFO_R);

	//��Ⱦ��Դ
	pSkinRenderManager->RenderImage(ImageTitleL);
	pSkinRenderManager->RenderImage(ImageTitleM);
	pSkinRenderManager->RenderImage(ImageTitleR);

	//�滭����
	ImageTitleL.BitBlt(BufferDC,0,0);

	//����м�
	for (INT nXPos=ImageTitleL.GetWidth();nXPos<rcClient.Width();nXPos+=ImageTitleM.GetWidth())
	{
		ImageTitleM.BitBlt(BufferDC,nXPos,0);
	}

	//�滭����
	ImageTitleR.BitBlt(BufferDC,rcClient.Width()-ImageTitleR.GetWidth(),0);

	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SetTextColor(RGB(255,255,255));
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�û���Ϣ
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//�滭�û�
	if (pGlobalUserData->dwUserID!=0L)
	{
		//������Ϣ
		TCHAR szScore[32]=TEXT("");
		TCHAR szInsure[32]=TEXT("");
		SwitchScoreFormat(pGlobalUserData->lUserScore,3,2,szScore,CountArray(szScore));
		SwitchScoreFormat(pGlobalUserData->lUserInsure,3,2,szInsure,CountArray(szInsure));

		//�������
		CRect rcScore;
		rcScore.SetRect(57,36,rcClient.Width()-18,68);
		pBufferDC->SetTextColor(RGB(255,211,91));
		pBufferDC->DrawText(szScore,lstrlen(szScore),&rcScore,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		//�������
		CRect rcInsure;
		rcInsure.SetRect(57,65,rcClient.Width()-18,97);
		pBufferDC->SetTextColor(RGB(255,180,0));
		pBufferDC->DrawText(szInsure,lstrlen(szInsure),&rcInsure,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		//����ʺ�
		CRect rcAccounts;
		rcAccounts.SetRect(57,8,rcClient.Width()-18,37);
		pBufferDC->SetTextColor(RGB(123,253,255));
		pBufferDC->DrawText(pGlobalUserData->szNickName,lstrlen(pGlobalUserData->szNickName),&rcAccounts,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//�¼���Ϣ
LRESULT CWndUserInfoCtrl::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case EVENT_USER_LOGON:			//��¼�ɹ�
		{
			//���´���
			Invalidate();

			//���ð�ť
			m_btUserInfo1.EnableWindow(TRUE);
			m_btUserInfo2.EnableWindow(TRUE);
			m_btUserInfo3.EnableWindow(TRUE);

			return 0L;
		}
	case EVENT_USER_LOGOUT:			//ע���ɹ�
		{
			//���´���
			Invalidate();

			//���ð�ť
			m_btUserInfo1.EnableWindow(FALSE);
			m_btUserInfo2.EnableWindow(FALSE);
			m_btUserInfo3.EnableWindow(FALSE);

			return 0L;
		}
	case EVENT_USER_INFO_UPDATE:	//���ϸ���
		{
			//��������
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			ASSERT(pGlobalUserData!=NULL);

			//��������
			/*if(m_pDlgInsurePlaza!=NULL) 
				m_pDlgInsurePlaza->OnEventUpdateInsurePlaza(pGlobalUserData->lUserScore,pGlobalUserData->lUserInsure);*/

			//���´���
			Invalidate();

			return 0L;
		}
	}

	return 0L;
}


//////////////////////////////////////////////////////////////////////////////////
