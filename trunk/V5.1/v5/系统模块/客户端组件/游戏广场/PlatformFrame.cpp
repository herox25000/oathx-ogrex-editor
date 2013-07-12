#include "Stdafx.h"
#include "GamePlaza.h"
#include "DlgEnquire.h"
#include "PlatformFrame.h"

//////////////////////////////////////////////////////////////////////////////////

//Բ�Ǵ�С
#define ROUND_CX					5									//Բ�ǿ��
#define ROUND_CY					5									//Բ�Ǹ߶�

//��Ӱ����
#define SHADOW_CX					5									//��Ӱ���
#define SHADOW_CY					5									//��Ӱ�߶�

//��Ļλ��
#define BORAD_SIZE					5									//�߿��С
#define CAPTION_SIZE				79									//�����С

//����λ��
#define SPLITTER_CX					0									//��ֿ��
#define LESS_LIST_CX				235									//�б���
#define FRAME_AFFICHE_CX			225									//��ܹ���

//��Ļ����
#define LESS_SCREEN_CY				740									//��С�߶�
#define LESS_SCREEN_CX				1024								//��С���
#define MAX_SCREEN_CX               1024                                //���ֱ���
#define MAX_SCREEN_CY               768                                 //��С�ֱ���           

//////////////////////////////////////////////////////////////////////////////////

//���ư�ť
#define IDC_MIN						100									//��С��ť
#define IDC_MAX						101									//���ť
#define IDC_CLOSE					102									//�رհ�ť

//�ؼ���ʶ
#define IDC_WEB_PUBLICIZE			300									//����ؼ�
#define IDC_WEB_PUBLICIZE1          301                                 //����ؼ� 
#define IDC_SKIN_SPLITTER			302									//��ֿؼ�
#define IDC_SYSTEM_TRAY_ICON		303									//����ͼ��

//�ؼ���ʶ
#define IDC_GAME_TYPE_CTRL			311									//���Ϳ��
#define IDC_USER_INFO_CTRL			312									//�û���Ϣ

//��Χ��ť
#define IDC_NAVIGATION				400									//������ť

//ʱ���ʶ
#define IDI_FLASH_TRAY_ICON			10									//����ͼ��

//////////////////////////////////////////////////////////////////////////////////
//��̬����

CPlatformFrame * CPlatformFrame::m_pPlatformFrame=NULL;					//���ָ��

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//�Զ���Ϣ
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)
	ON_MESSAGE(WM_INSUREPLAZA_UPDATA, OnMessageInsureUpdate)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPlatformFrame::CPlatformFrame()
{
	//״̬����
	m_bMaxShow=false;
	m_bRectify=false;
	m_bWhisperIcon=false;
	m_bShowLeftPanel=true;
	m_rcPlazaView.SetRect(0,0,0,0);
	m_rcServerView.SetRect(0,0,0,0);
	m_rcGameType.SetRect(0,0,0,0);
	m_rcToolBar.SetRect(0,0,0,0);
	m_rcNormalSize.SetRect(0,0,0,0);

	//�������
	m_MissionManager.InsertMissionItem(&m_MissionList);
	m_MissionManager.InsertMissionItem(&m_MissionLogon);

	//ƽ̨����
	ASSERT(m_pPlatformFrame==NULL);
	if (m_pPlatformFrame==NULL) m_pPlatformFrame=this;

	//��ܻ���
	tagEncircleResource	EncircleFrame;
	EncircleFrame.pszImageTL=TEXT("FRAME_TL");
	EncircleFrame.pszImageTM=TEXT("FRAME_TM");
	EncircleFrame.pszImageTR=TEXT("FRAME_TR");
	EncircleFrame.pszImageML=TEXT("FRAME_ML");
	EncircleFrame.pszImageMR=TEXT("FRAME_MR");
	EncircleFrame.pszImageBL=TEXT("FRAME_BL");
	EncircleFrame.pszImageBM=TEXT("FRAME_BM");
	EncircleFrame.pszImageBR=TEXT("FRAME_BR");
	m_FrameEncircle.InitEncircleResource(EncircleFrame,AfxGetInstanceHandle());

	//������Դ
	tagEncircleResource	EncircleAffiche;
	EncircleAffiche.pszImageTL=MAKEINTRESOURCE(IDB_AFFICHE_TL);
	EncircleAffiche.pszImageTM=MAKEINTRESOURCE(IDB_AFFICHE_TM);
	EncircleAffiche.pszImageTR=MAKEINTRESOURCE(IDB_AFFICHE_TR);
	EncircleAffiche.pszImageML=MAKEINTRESOURCE(IDB_AFFICHE_ML);
	EncircleAffiche.pszImageMR=MAKEINTRESOURCE(IDB_AFFICHE_MR);
	EncircleAffiche.pszImageBL=MAKEINTRESOURCE(IDB_AFFICHE_BL);
	EncircleAffiche.pszImageBM=MAKEINTRESOURCE(IDB_AFFICHE_BM);
	EncircleAffiche.pszImageBR=MAKEINTRESOURCE(IDB_AFFICHE_BR);
	m_AfficheEncircle.InitEncircleResource(EncircleAffiche,AfxGetInstanceHandle());

	//������Դ
	tagEncircleResource	EncircleItemFrame;
	EncircleItemFrame.pszImageTL=MAKEINTRESOURCE(IDB_ITEM_FRAME_TL);
	EncircleItemFrame.pszImageTM=MAKEINTRESOURCE(IDB_ITEM_FRAME_TM);
	EncircleItemFrame.pszImageTR=MAKEINTRESOURCE(IDB_ITEM_FRAME_TR);
	EncircleItemFrame.pszImageML=MAKEINTRESOURCE(IDB_ITEM_FRAME_ML);
	EncircleItemFrame.pszImageMR=MAKEINTRESOURCE(IDB_ITEM_FRAME_MR);
	EncircleItemFrame.pszImageBL=MAKEINTRESOURCE(IDB_ITEM_FRAME_BL);
	EncircleItemFrame.pszImageBM=MAKEINTRESOURCE(IDB_ITEM_FRAME_BM);
	EncircleItemFrame.pszImageBR=MAKEINTRESOURCE(IDB_ITEM_FRAME_BR);
	m_ItemFrameEncircle.InitEncircleResource(EncircleItemFrame,AfxGetInstanceHandle());

	//ָ�����
	m_pServerViewItem = NULL;

	return;
}

//��������
CPlatformFrame::~CPlatformFrame()
{
	//ƽ̨����
	ASSERT(m_pPlatformFrame==this);
	if (m_pPlatformFrame==this) m_pPlatformFrame=NULL;

	//�޸ķֱ���
	ChangeScreenSetting(m_ScreenMetrics.cx,m_ScreenMetrics.cy,false);

	return;
}

//�ӿڲ�ѯ
VOID * CPlatformFrame::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ICustomFaceEvent,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ICustomFaceEvent,Guid,dwQueryVer);
	return NULL;
}

//����ʧ��
VOID CPlatformFrame::OnEventSystemFace(DWORD dwUserID, WORD wFaceID)
{
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//��������
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//���ñ���
		pGlobalUserData->wFaceID=wFaceID;

		//��������
		pGlobalUserData->dwCustomID=0L;
		ZeroMemory(&pGlobalUserData->CustomFaceInfo,sizeof(pGlobalUserData->CustomFaceInfo));

		//�����¼�
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	return;
}

//ͷ������
VOID CPlatformFrame::OnEventCustomFace(DWORD dwUserID, DWORD dwCustomID, tagCustomFaceInfo & CustomFaceInfo)
{
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//��������
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//���ñ���
		pGlobalUserData->dwCustomID=dwCustomID;
		CopyMemory(&pGlobalUserData->CustomFaceInfo,&CustomFaceInfo,sizeof(CustomFaceInfo));

		//�����¼�
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	//��ǰ����
	if ( m_pServerViewItem != NULL)
	{
		m_pServerViewItem->UpdateUserCustomFace(dwUserID,dwCustomID,CustomFaceInfo);
	}

	return;
}

//��ȡ֪ͨ
VOID CPlatformFrame::OnGameItemFinish()
{
	//��ʾ�б�
	m_PlazaViewItem.ShowKindItemView(0);

	return;
}

//��ȡ֪ͨ
VOID CPlatformFrame::OnGameKindFinish(WORD wKindID)
{
	return;
}

//����֪ͨ
VOID CPlatformFrame::OnGameItemUpdateFinish()
{
	return;
}

//����֪ͨ
VOID CPlatformFrame::OnGameItemInsert(CGameListItem * pGameListItem)
{
	//Ч�����
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//���봦��
	switch (pGameListItem->GetItemGenre())
	{
	case ItemGenre_Type:	//��Ϸ����
		{
			//��������
			m_WndGameTypeCtrl.InsertGameType((CGameTypeItem *)pGameListItem);

			break;
		}
	case ItemGenre_Kind:	//��Ϸ����
		{
			break;
		}
	case ItemGenre_Server:	//��Ϸ����
		{
			break;
		}
	}

	return;
}

//����֪ͨ
VOID CPlatformFrame::OnGameItemUpdate(CGameListItem * pGameListItem)
{
	return;
}

//ɾ��֪ͨ
VOID CPlatformFrame::OnGameItemDelete(CGameListItem * pGameListItem)
{
	return;
}

//��Ϣ����
BOOL CPlatformFrame::PreTranslateMessage(MSG * pMsg)
{
	//��ʾ��Ϣ
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//�����
BOOL CPlatformFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��������
	UINT nCommandID=LOWORD(wParam);

	//���ܰ�ť
	switch (nCommandID)
	{
	case IDC_MIN:				//��С��ť
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDC_MAX:
		{
			if(m_bMaxShow==false)
			{
				MaxSizeWindow();				
			}
			else
			{
				RestoreWindow();
			}			

			return TRUE;
		}
	case IDC_CLOSE:				//�رհ�ť
		{
			PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case IDC_NAVIGATION+2:		//�ϴ�ͷ��
		{
			//��ʾ����
			CDlgCustomFace DlgCustomFace;
			DlgCustomFace.SetCustomFaceEvent(QUERY_OBJECT_PTR_INTERFACE(CPlatformFrame::GetInstance(),IUnknownEx));

			//��ʾ����
			DlgCustomFace.DoModal();
						
			return TRUE;
		}
	case IDC_NAVIGATION+3:		//��������
		{
			//��ʾ����
			CDlgLockMachine DlgLockMachine;
			DlgLockMachine.DoModal();

			return TRUE;
		}
	case IDC_NAVIGATION+0:
	case IDC_NAVIGATION+1:
	case IDC_NAVIGATION+4:
	case IDC_NAVIGATION+5:
	case IDC_NAVIGATION+6:		//������ť
		{
			//��ȡָ��
			CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
			ASSERT(pGlobalUnits!=NULL);

			//�����ַ
			TCHAR szNavigation[256]=TEXT("");
			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s%sNavigation%ld.aspx"),szPlatformLink,pGlobalUnits->GetValidateParamAsString(),(nCommandID-IDC_NAVIGATION)+1);

			//���ӵ�ַ
			ShellExecute(NULL,TEXT("OPEN"),szNavigation,NULL,NULL,SW_NORMAL);

			return TRUE;
		}
	}

	//�˵�����
	switch (nCommandID)
	{
	case IDM_USER_LOGON:		//�û���¼
		{
			m_MissionLogon.ShowLogon();

			return TRUE;
		}
	case IDM_SWITCH_ACCOUNTS:	//�л��ʺ�
		{
			//�л�ѯ��
			if ( m_pServerViewItem != NULL )
			{
				CInformation Information(this);
				if (Information.ShowMessageBox(TEXT("��Ϸ���伴���رգ�ȷʵҪ���л��ʺš��� "),MB_YESNO)!=IDYES) return TRUE;
			}

			//ȫ������
			CGlobalUnits::GetInstance()->DeleteUserCookie();
			CGlobalUserInfo::GetInstance()->ResetUserInfoData();

			//�����¼�
			CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
			if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_LOGOUT,0L);

			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//�����ؼ�
VOID CPlatformFrame::RectifyControl(INT nWidth, INT nHeight)
{
	//״̬�ж�
	if ((nWidth==0)||(nHeight==0)) return;

	//���λ��
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//������Ϣ
	tagEncircleInfo EncircleInfoFrame;
	tagEncircleInfo EncircleInfoAffiche;
	tagEncircleInfo EncircleInfoItemFrame;
	m_FrameEncircle.GetEncircleInfo(EncircleInfoFrame);
	m_AfficheEncircle.GetEncircleInfo(EncircleInfoAffiche);
	m_ItemFrameEncircle.GetEncircleInfo(EncircleInfoItemFrame);

	//��ȡλ��
	ScreenToClient(&rcSplitter);

	//��ַ�Χ
	INT nLessPos=nWidth*28/100,nMaxPos=nWidth/2;
	if (nLessPos>=LESS_LIST_CX) nLessPos=LESS_LIST_CX;

	//��ֿؼ�
	if (m_bShowLeftPanel==true)
	{
		rcSplitter.left=nLessPos;
		rcSplitter.right=rcSplitter.left+SPLITTER_CX;
	}
	else 
	{
		//���λ��
		rcSplitter.left=EncircleInfoFrame.nLBorder;
		rcSplitter.right=rcSplitter.left+SPLITTER_CX;
	}

	//��ַ�Χ
	m_SkinSplitter.SetSplitterRange(nLessPos,nMaxPos);

	//����λ��
	if ((nWidth!=0)&&(nHeight!=0))
	{
		if (rcSplitter.left<EncircleInfoFrame.nLBorder)
		{
			rcSplitter.left=EncircleInfoFrame.nLBorder;
			rcSplitter.right=rcSplitter.left+SPLITTER_CX;
		}
		if (rcSplitter.right>nMaxPos)
		{
			rcSplitter.right=nMaxPos;
			rcSplitter.left=rcSplitter.right-SPLITTER_CX;
		}
	}

	//λ�õ���
	rcSplitter.top=EncircleInfoFrame.nTBorder;
	rcSplitter.bottom=nHeight-EncircleInfoFrame.nBBorder;

	//�ؼ�λ��
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);

	//�м���
	CRect rcMiddleFrame(EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder,nWidth-EncircleInfoFrame.nRBorder,EncircleInfoFrame.nTBorder+33);

	//��������
	m_MiddleFrameControl.SetControlRect(rcMiddleFrame);	

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//���ư�ť
	DeferWindowPos(hDwp,m_btMin,NULL,nWidth-86,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,nWidth-60,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,nWidth-34,3,0,0,uFlags|SWP_NOSIZE);

	//������ť
	CRect rcNavigation;
	m_btNavigation[0].GetWindowRect(&rcNavigation);

	//������ť
	INT nNavigationArea=rcNavigation.Width()*CountArray(m_btNavigation);
	INT nSpace=__min(__max((nWidth-nNavigationArea-328)/(CountArray(m_btNavigation)-1),0),33);

	//������ť
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		INT nIndex=CountArray(m_btNavigation)-i;
		INT nXExcursion=nWidth-(rcNavigation.Width()+nSpace)*nIndex-6;
		DeferWindowPos(hDwp,m_btNavigation[i],NULL,nXExcursion,39,0,0,uFlags|SWP_NOSIZE);
	}

	//��ͼλ��
	m_rcPlazaView.left= rcSplitter.right+EncircleInfoItemFrame.nLBorder;
	m_rcPlazaView.top=EncircleInfoFrame.nTBorder+EncircleInfoItemFrame.nTBorder+rcMiddleFrame.Height();
	m_rcPlazaView.right=nWidth-EncircleInfoFrame.nRBorder-EncircleInfoItemFrame.nRBorder;
	m_rcPlazaView.bottom=nHeight-EncircleInfoFrame.nBBorder-EncircleInfoItemFrame.nBBorder;

	//��Ϸ�㳡
	DeferWindowPos(hDwp,m_PlazaViewItem,NULL,m_rcPlazaView.left,m_rcPlazaView.top,m_rcPlazaView.Width(),m_rcPlazaView.Height(),uFlags);

	//��ͼλ��
	m_rcServerView.left=rcSplitter.right;
	m_rcServerView.top=EncircleInfoFrame.nTBorder+rcMiddleFrame.Height()-1;
	m_rcServerView.right=nWidth-EncircleInfoFrame.nRBorder;
	m_rcServerView.bottom=nHeight-EncircleInfoFrame.nBBorder;

	//������ͼ
	if( m_pServerViewItem!=NULL )
	{
		DeferWindowPos(hDwp,m_pServerViewItem->m_hWnd,NULL,m_rcServerView.left,m_rcServerView.top,m_rcServerView.Width(),m_rcServerView.Height(),uFlags);
	}

	//���Ϳ��
	CSize SizeGameTypeCtrl;
	m_WndGameTypeCtrl.GetControlSize(SizeGameTypeCtrl);

	//��Ϸ����
	m_rcGameType.left = rcSplitter.right+10;
	m_rcGameType.top = EncircleInfoFrame.nTBorder+EncircleInfoItemFrame.nTBorder-SizeGameTypeCtrl.cy+22;
	m_rcGameType.right = m_rcGameType.left+SizeGameTypeCtrl.cx;
	m_rcGameType.bottom = m_rcGameType.top+SizeGameTypeCtrl.cy;

	//��Ϸ����
	DeferWindowPos(hDwp,m_WndGameTypeCtrl,NULL,m_rcGameType.left,m_rcGameType.top,m_rcGameType.Width(),m_rcGameType.Height(),uFlags);

	//��������
	CRect rcServerToolBar;
	m_ServerToolBar.GetWindowRect(rcServerToolBar);

	//������
	m_rcToolBar.left = rcSplitter.right+344;
	m_rcToolBar.top = EncircleInfoFrame.nTBorder+EncircleInfoItemFrame.nTBorder+rcMiddleFrame.Height()-SizeGameTypeCtrl.cy-13;
	m_rcToolBar.right = m_rcToolBar.left+rcServerToolBar.Width();
	m_rcToolBar.bottom = m_rcToolBar.top+rcServerToolBar.Height();

	//���乤����
	DeferWindowPos(hDwp,m_ServerToolBar,NULL,m_rcToolBar.left,m_rcToolBar.top,m_rcToolBar.Width(),m_rcToolBar.Height(),uFlags);

	//�����ؼ�
	DeferWindowPos(hDwp,m_SkinSplitter,NULL,rcSplitter.left,rcSplitter.top,rcSplitter.Width(),rcSplitter.Height(),uFlags);
	DeferWindowPos(hDwp,m_WndUserInfoCtrl,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+rcMiddleFrame.Height(),rcSplitter.left-EncircleInfoFrame.nLBorder,rcUserInfoCtrl.Height(),uFlags);

	DeferWindowPos(hDwp,m_PlatFormNoticePublicize,NULL,247,9,530,18,uFlags);
	

	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();
	

	//���½���
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	return;
}

//������Դ
VOID CPlatformFrame::RectifyResource(INT nWidth, INT nHeight)
{
	//�����ж�
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//���λ��
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX,SHADOW_CY,nWidth-SHADOW_CX,nHeight-SHADOW_CY);

		//��������
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//��������
		SetWindowRgn(RegionWindow,TRUE);

		//�ֲ㴰��
		if (m_SkinLayered.m_hWnd!=NULL)
		{
			//��������
			CImage ImageBuffer;
			ImageBuffer.Create(nWidth,nHeight,32);

			//���� DC
			CImageDC ImageDC(ImageBuffer);
			CDC * pBufferDC=CDC::FromHandle(ImageDC);

			//�滭����
			DrawControlView(pBufferDC,nWidth,nHeight);

			//���·ֲ�
			m_SkinLayered.InitLayeredArea(pBufferDC,255,rcFrame,CPoint(ROUND_CX,ROUND_CX),false);
		}
	}

	return;
}

//�滭����
VOID CPlatformFrame::DrawControlView(CDC * pDC, INT nWidth, INT nHeight)
{
	//���λ��
	tagEncircleInfo FrameEncircleInfo;
	tagEncircleInfo ItemFrameEncircleInfo;
	m_FrameEncircle.GetEncircleInfo(FrameEncircleInfo);
	m_ItemFrameEncircle.GetEncircleInfo(ItemFrameEncircleInfo);

	//���λ��
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//λ��ת��
	ScreenToClient(&rcSplitter);

	//�ؼ�λ��
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);

	//�ؼ�λ��
	CRect rcMiddleFrame;
	m_MiddleFrameControl.GetControlRect(rcMiddleFrame);

	//�������
	CRect rcFrame;
	rcFrame.SetRect(0,0,nWidth,nHeight);

	//����λ��
	CRect rcAffiche;
	rcAffiche.right=rcSplitter.left;
	rcAffiche.left=FrameEncircleInfo.nLBorder;
	rcAffiche.top=FrameEncircleInfo.nTBorder+rcMiddleFrame.Height()+rcUserInfoCtrl.Height();
	rcAffiche.bottom=nHeight-FrameEncircleInfo.nBBorder;

	//��������
	CRect rcItemFrame;
	rcItemFrame.left=rcSplitter.right;
	rcItemFrame.top=FrameEncircleInfo.nTBorder+rcMiddleFrame.Height();
	rcItemFrame.right=nWidth-FrameEncircleInfo.nRBorder;
	rcItemFrame.bottom=nHeight-FrameEncircleInfo.nBBorder;

	//�滭���
	m_FrameEncircle.DrawEncircleFrame(pDC,rcFrame);
	m_ItemFrameEncircle.DrawEncircleFrame(pDC,rcItemFrame);
	m_MiddleFrameControl.OnDrawFrameControl(pDC);

	//������Դ
	CPngImage StationLogo;
	StationLogo.LoadImage(AfxGetInstanceHandle(),TEXT("PLATFORM_LOGO"));

	//�滭��־
	StationLogo.DrawImage(pDC,SHADOW_CX+8,SHADOW_CY+34);

	//�滭���
	if (m_bShowLeftPanel==true && m_ImageFrame.IsNull()==false)
	{
		//���ƿ��
		m_AfficheEncircle.DrawEncircleFrame(pDC,rcAffiche);

		//��ȡ��С
		CSize SizeImageFrame;
		SizeImageFrame.SetSize(m_ImageFrame.GetWidth(),m_ImageFrame.GetHeight());

		//�滭���
		INT nXPos=rcAffiche.left+8;
		INT nYPos=rcAffiche.top+9;

		//�滭���
		pDC->SetStretchBltMode(HALFTONE);
		m_ImageFrame.StretchBlt(pDC->m_hDC,nXPos,nYPos,rcAffiche.Width()-14,rcAffiche.Height()-17,0,0,SizeImageFrame.cx,SizeImageFrame.cy);
	}

	return;
}

//�����
bool CPlatformFrame::ActiveServerViewItem()
{
	//�����ж�
	ASSERT(m_pServerViewItem!=NULL);
	if (m_pServerViewItem==NULL) return false;

	//�������
	ShowPlazaLeftPanel(false);

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//��Ϸ�㳡
	DeferWindowPos(hDwp,m_PlazaViewItem,NULL,m_rcPlazaView.left,m_rcPlazaView.top,m_rcPlazaView.Width(),m_rcPlazaView.Height(),uFlags|SWP_HIDEWINDOW);
	DeferWindowPos(hDwp,m_pServerViewItem->m_hWnd,NULL,m_rcServerView.left,m_rcServerView.top,m_rcServerView.Width(),m_rcServerView.Height(),uFlags|SWP_SHOWWINDOW);
	DeferWindowPos(hDwp,m_ServerToolBar,NULL,m_rcToolBar.left,m_rcToolBar.top,m_rcToolBar.Width(),m_rcToolBar.Height(),uFlags|SWP_SHOWWINDOW);
	DeferWindowPos(hDwp,m_WndGameTypeCtrl,NULL,m_rcGameType.left,m_rcGameType.top,m_rcGameType.Width(),m_rcGameType.Height(),uFlags|SWP_HIDEWINDOW);

	//��������
	EndDeferWindowPos(hDwp);

	//���ñ�ʶ
	m_MiddleFrameControl.SetAfficheTitleFlag(false);

	//���½���
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	return true;
}

//ɾ������
bool CPlatformFrame::DeleteServerViewItem()
{
	//�����ж�
	ASSERT(m_pServerViewItem!=NULL);
	if (m_pServerViewItem==NULL) return false;

	//��ʾ���
	ShowPlazaLeftPanel(true);

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//��Ϸ�㳡
	DeferWindowPos(hDwp,m_PlazaViewItem,NULL,m_rcPlazaView.left,m_rcPlazaView.top,m_rcPlazaView.Width(),m_rcPlazaView.Height(),uFlags|SWP_SHOWWINDOW);
	DeferWindowPos(hDwp,m_pServerViewItem->m_hWnd,NULL,m_rcServerView.left,m_rcServerView.top,m_rcServerView.Width(),m_rcServerView.Height(),uFlags|SWP_HIDEWINDOW);
	DeferWindowPos(hDwp,m_ServerToolBar,NULL,m_rcToolBar.left,m_rcToolBar.top,m_rcToolBar.Width(),m_rcToolBar.Height(),uFlags|SWP_HIDEWINDOW);
	DeferWindowPos(hDwp,m_WndGameTypeCtrl,NULL,m_rcGameType.left,m_rcGameType.top,m_rcGameType.Width(),m_rcGameType.Height(),uFlags|SWP_SHOWWINDOW);

	//��������
	EndDeferWindowPos(hDwp);

	//���ñ�ʶ
	m_MiddleFrameControl.SetAfficheTitleFlag(true);

	//���½���
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	//���ٴ���
	m_pServerViewItem->DestroyWindow();
	m_pServerViewItem = NULL;

	return true;
}

//���뷿��
bool CPlatformFrame::EntranceServerItem(CGameServerItem * pGameServerItem)
{
	//Ч�����
	ASSERT(pGameServerItem!=NULL);
	if (pGameServerItem==NULL) return NULL;

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//��¼�ж�
	if (pGlobalUserData->dwUserID==0L) return NULL;

	//��������
	tagGameServer * pGameServer=&pGameServerItem->m_GameServer;
	tagGameKind * pGameKind=&pGameServerItem->m_pGameKindItem->m_GameKind;

	//��ǰ�ж�
	if ( m_pServerViewItem!=NULL)
	{
		//��ʾ��Ϣ
		TCHAR szBuffer[256]=TEXT("");
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("���ڽ��� [ %s ] ��Ϸ�����У����Ժ�ȴ�Ƭ��..."),m_pServerViewItem->GetServerName());

		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(szBuffer,MB_OK|MB_ICONWARNING,30);

		return false;
	}

	//��װ�ж�
	if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
	{
		//��ȡ�汾
		CGameKindItem * pGameKindItem=pGameServerItem->m_pGameKindItem;
		CWHService::GetModuleVersion(pGameKind->szProcessName,pGameKindItem->m_dwProcessVersion);

		//������Ϸ
		if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
		{
			CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
			pCGlobalUnits->DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,pGameServer->wServerID);

			return NULL;
		}

		//�����б�
		OnGameItemUpdate(pGameKindItem);
	}

	//��������
	try
	{
		//��������
		m_pServerViewItem = new CServerViewItem;
		m_pServerViewItem->Create(IDD_GAME_SERVER,this);
		m_pServerViewItem->InitServerViewItem(pGameServerItem);
	}
	catch (LPCTSTR pszString)
	{
		//���ٷ���
		if( m_pServerViewItem!=NULL )
		{
			if(m_pServerViewItem->m_hWnd!=NULL) m_pServerViewItem->DestroyWindow();
			SafeDelete(m_pServerViewItem);
		}

		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(pGameServer->szServerName,pszString,MB_ICONERROR);

		return false;
	}

	return true;
}

//�ر���Ϣ
VOID CPlatformFrame::OnClose()
{
	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//�ر���ʾ
	if ((pGlobalUserData->dwUserID!=0L)&&(m_MissionLogon.GetActiveStatus()==false))
	{
		//��ʾ����
		CDlgEnquire DlgEnquire;
		INT_PTR nResult=DlgEnquire.DoModal();

		//�����
		switch (nResult)
		{
		case IDCANCEL:				//ȡ������
			{
				return;
			}
		case IDC_CLOSE_SERVER:		//�˳�����
			{
				//�رշ���
				if (m_pServerViewItem!=NULL)
				{
					DeleteServerViewItem();
				}

				return;
			}
		case IDC_SWITCH_ACCOUNTS:	//�л��ʺ�
			{
				//Ͷ����Ϣ
				PostMessage(WM_COMMAND,IDM_SWITCH_ACCOUNTS,0);

				return;
			}
		}
	}

	__super::OnClose();
}

//�滭����
BOOL CPlatformFrame::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//�滭����
	DrawControlView(pBufferDC,rcClient.Width(),rcClient.Height());

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//λ����Ϣ
VOID CPlatformFrame::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	//������Դ
	RectifyResource(cx,cy);

	return;
}

//������Ϣ
INT CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ô���
	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);

	//�����㳡
	CRect rcCreate(0,0,0,0);
	m_PlazaViewItem.Create(IDD_GAME_PLAZA,this);
	m_ServerToolBar.Create(IDD_DLG_SERVER_TOOL_BAR,this);

	//�����ؼ�
	m_SkinSplitter.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SKIN_SPLITTER);
	m_WndUserInfoCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_USER_INFO_CTRL);
	m_WndGameTypeCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_GAME_TYPE_CTRL);
	m_PlatFormNoticePublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE1);

	//������ť
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MIN);
	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MAX);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CLOSE);

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btMin.SetButtonImage(IDB_BT_MIN,hInstance,true,false);
	m_btMax.SetButtonImage(IDB_BT_MAX,hInstance,true,false);
	m_btClose.SetButtonImage(IDB_BT_CLOSE,hInstance,true,false);

	//������ť
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		m_btNavigation[i].Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_NAVIGATION+i);
	}

	//������ť
	m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,TEXT("BT_NAVIGATION_1"),hInstance,true,false);
	m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,TEXT("BT_NAVIGATION_2"),hInstance,true,false);
	m_btNavigation[2].SetButtonImage(IDB_BK_NAVIGATION3,TEXT("BT_NAVIGATION_3"),hInstance,true,false);
	m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION4,TEXT("BT_NAVIGATION_4"),hInstance,true,false);
	m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,TEXT("BT_NAVIGATION_5"),hInstance,true,false);
	m_btNavigation[5].SetButtonImage(IDB_BK_NAVIGATION6,TEXT("BT_NAVIGATION_6"),hInstance,true,false);
	m_btNavigation[6].SetButtonImage(IDB_BK_NAVIGATION7,TEXT("BT_NAVIGATION_7"),hInstance,true,false);

	//��Ϸ�б�
	m_ServerListData.SetServerListDataSink(this);

	//��ʾ�ؼ�
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(&m_btNavigation[0],TEXT("�ٷ���վ"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[1],TEXT("���߳�ֵ"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[2],TEXT("�ϴ�ͷ��"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[3],TEXT("��������"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[4],TEXT("�һ��̳�"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[5],TEXT("����ƹ�"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[6],TEXT("�ͷ�����"));
	//m_ToolTipCtrl.AddTool(&m_btMin,TEXT("��С��"));
	//m_ToolTipCtrl.AddTool(&m_btClose,TEXT("�رմ���"));

	//ע���¼�
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//���÷ֱ���
	m_ScreenMetrics.cx = ::GetSystemMetrics(SM_CXSCREEN); 
	m_ScreenMetrics.cy = ::GetSystemMetrics(SM_CYSCREEN);

	//����λ��
	CSize SizeRestrict;
	SizeRestrict.SetSize(LESS_SCREEN_CX,LESS_SCREEN_CY);

	//����λ��
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//λ�õ���
	SizeRestrict.cx=__max(LESS_SCREEN_CX,SizeRestrict.cx);
	SizeRestrict.cy=__max(LESS_SCREEN_CY,SizeRestrict.cy);
	SizeRestrict.cx=__min(rcArce.Width(),SizeRestrict.cx);
	SizeRestrict.cy=__min(rcArce.Height(),SizeRestrict.cy);

	//�ƶ�����
	m_rcNormalSize.top=(rcArce.Height()-SizeRestrict.cy)/2;
	m_rcNormalSize.left=(rcArce.Width()-SizeRestrict.cx)/2;
	m_rcNormalSize.right=(rcArce.Width()+SizeRestrict.cx)/2;
	m_rcNormalSize.bottom=(rcArce.Height()+SizeRestrict.cy)/2;
	SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);

	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//�����ַ
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s\\Web\\LobbyTopNotice.htm"),szDirectory);

	//��������
	CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
	ASSERT(pGlobalUnits!=NULL);

	//���ӹ��
	if(pGlobalUnits!=NULL && pGlobalUnits->LocalFileExist(szBillUrl))
		m_PlatFormNoticePublicize.Navigate(szBillUrl);
	m_PlatFormNoticePublicize.SetBackColor(RGB(19,69,103));

	//��¼ϵͳ
	PostMessage(WM_COMMAND,IDM_USER_LOGON,0);

	//�����ֲ�
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	m_SkinLayered.CreateLayered(this,rcWindow);

	//������Դ
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(),rcClient.Height());

	//����·��
	TCHAR szImagePath[MAX_PATH]=TEXT("");
	_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\ADImage\\Frame.BMP"),szDirectory);

	//������Դ
	m_ImageFrame.Load(szImagePath);

	return 0;
}


//ʱ����Ϣ
VOID CPlatformFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDI_FLASH_TRAY_ICON:	//����ͼ��
		{
			//���ñ���
			m_bWhisperIcon=!m_bWhisperIcon;

			//����ͼ��
			UINT uIconID=(m_bWhisperIcon==true)?IDI_WHISPER:IDI_NULL;
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(uIconID)));

			return;
		}
	}

	__super::OnTimer(nIDEvent);
}

//��ʾ��Ϣ
VOID CPlatformFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//��ʾ�ֲ�
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//λ�øı�
VOID CPlatformFrame::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//�ƶ��ֲ�
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//�����Ϣ
VOID CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�ⰴ����
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//�¼���Ϣ
LRESULT CPlatformFrame::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	//�¼�����
	switch (wParam)
	{
	case EVENT_USER_LOGON:			//��¼���
		{
			//��ʾ����
			ShowWindow(SW_SHOW);
			SetForegroundWindow();

			//��������
			m_MissionList.UpdateMissionStatus(true);

			//��ȡָ��
			CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
			if(pGlobalUnits==NULL) return 0L;

			//�û����			
			pGlobalUnits->WriteUserCookie();

			//�û���Ϣ
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			ASSERT(pGlobalUserData!=NULL);

			//���ò���
			pGlobalUnits->SetValidateParam(pGlobalUserData->dwUserID,pGlobalUserData->szPassword);

			return 0L;
		}
	case EVENT_USER_LOGOUT:			//ע���ɹ�
		{
			//���ش���
			ShowWindow(SW_HIDE);

			//�رշ���
			DeleteServerViewItem();

			//��ʾ��¼
			m_MissionLogon.ShowLogon();

			return 0L;
		}
	case EVENT_DOWN_LOAD_FINISH:	//�������
		{
			//��ȡ����
			WORD wKindID=LOWORD(lParam);
			WORD wServerID=HIWORD(lParam);

			//�����б�
			CServerListData * pServerListData=CServerListData::GetInstance();
			if (pServerListData!=NULL) pServerListData->OnEventDownLoadFinish(wKindID);

			//���뷿��
			if ((wKindID!=0)&&(wServerID!=0))
			{
				CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);
				if (pGameServerItem!=NULL) EntranceServerItem(pGameServerItem);
			}

			return 0L;
		}
	case EVENT_UPDATE_ONLINE: //��������
		{
			//���½���
			m_PlazaViewItem.InValidateWndView(VIEW_MODE_SERVER);

			return 0L;
		}
	}

	return 0L;
}


//��ȡ˽��
bool CPlatformFrame::ShowWhisperItem()
{
	//��ȡ��Ϣ
	if (m_DlgWhisperItemArray.GetCount()>0L)
	{
		//��ȡ����
		CDlgWhisper * pDlgWhisper=m_DlgWhisperItemArray[0];

		//��ʾ����
		pDlgWhisper->ShowWindow(SW_RESTORE);

		//�ö�����
		pDlgWhisper->SetActiveWindow();
		pDlgWhisper->BringWindowToTop();
		pDlgWhisper->SetForegroundWindow();

		//ɾ������
		m_DlgWhisperItemArray.RemoveAt(0L);

		//ɾ��ͼ��
		if (m_DlgWhisperItemArray.GetCount()==0L)
		{
			//���ñ���
			m_bWhisperIcon=false;

			//ɾ��ʱ��
			KillTimer(IDI_FLASH_TRAY_ICON);

			//����ͼ��
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
		}

		return true;
	}

	return false;
}


//����˽��
bool CPlatformFrame::InsertWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//����Ч��
	ASSERT((pDlgWhisper!=NULL)&&(pDlgWhisper->m_hWnd!=NULL));
	if ((pDlgWhisper==NULL)||(pDlgWhisper->m_hWnd==NULL)) return false;

	//״̬�ж�
	if (pDlgWhisper->IsWindowVisible()) return false;

	//��������
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper) return false;
	}

	//����˽��
	m_DlgWhisperItemArray.Add(pDlgWhisper);

	//����ͼ��
	if (m_DlgWhisperItemArray.GetCount()==1L)
	{
		//���ñ���
		m_bWhisperIcon=true;

		//����ʱ��
		SetTimer(IDI_FLASH_TRAY_ICON,500,NULL);

		//����ͼ��
		m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_WHISPER)));
	}

	return true;
}

//ɾ��˽��
bool CPlatformFrame::RemoveWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//��������
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper)
		{
			//ɾ������
			m_DlgWhisperItemArray.RemoveAt(i);

			//ɾ��ͼ��
			if (m_DlgWhisperItemArray.GetCount()==0L)
			{
				//���ñ���
				m_bWhisperIcon=false;

				//ɾ��ʱ��
				KillTimer(IDI_FLASH_TRAY_ICON);

				//����ͼ��
				m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
			}

			return true;
		}
	}

	return false;
}

//��ʾ���
VOID CPlatformFrame::ShowPlazaLeftPanel(bool bShowPanel)
{
	//���ñ���
	m_bShowLeftPanel = bShowPanel;

	//��������
	CRect rcClient;
	GetClientRect(rcClient);

	//�����ؼ�
	RectifyControl(rcClient.Width(),rcClient.Height());

	return;
}

//�޸ķֱ���
VOID CPlatformFrame::ChangeScreenSetting(INT nScreencx,INT nScreency,bool bRecordResol)
{
	//��ȡ�ֱ���
	CSize SizeScreenMetrics;
	SizeScreenMetrics.cx = ::GetSystemMetrics(SM_CXSCREEN); 
	SizeScreenMetrics.cy = ::GetSystemMetrics(SM_CYSCREEN);

	//�ȽϷֱ���
	if(nScreencx != SizeScreenMetrics.cx && nScreency!=SizeScreenMetrics.cy)
	{
		//���ñ���
		if(bRecordResol==true) m_ScreenMetrics = SizeScreenMetrics;

		//����ṹ
		DEVMODE lpDevMode;
		lpDevMode.dmBitsPerPel=32;
		lpDevMode.dmPelsWidth=nScreencx;
		lpDevMode.dmPelsHeight=nScreency;
		lpDevMode.dmSize=sizeof(lpDevMode);
		lpDevMode.dmFields =DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;

		//�޸ķֱ���
		LONG lResult=ChangeDisplaySettings(&lpDevMode,0);
		if (lResult==DISP_CHANGE_SUCCESSFUL)
		{
			ChangeDisplaySettings(&lpDevMode,CDS_UPDATEREGISTRY);
		}
		else
		{
			ChangeDisplaySettings(NULL,0);
		}
	}

	return;
}

//��󴰿�
bool CPlatformFrame::MaxSizeWindow()
{
	if(m_bMaxShow==false)
	{
		//���ñ���
		m_bMaxShow = true;

		//��¼����
		GetWindowRect(m_rcNormalSize);

		//������Դ
		m_btMax.SetButtonImage(IDB_BT_RESTORE,AfxGetInstanceHandle(),true,false);	
		
		//�޸ķֱ���
		ChangeScreenSetting(MAX_SCREEN_CX,MAX_SCREEN_CY,true);

		//��ȡλ��
		CRect rcArce;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

		//�ƶ�����
		LockWindowUpdate();
		SetWindowPos(NULL,rcArce.left-2,rcArce.top-2,rcArce.Width()+4,rcArce.Height()+4,SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//��ԭ����
bool CPlatformFrame::RestoreWindow()
{
	if(m_bMaxShow==true)
	{
		//���ñ���
		m_bMaxShow = false;

		//������Դ
		m_btMax.SetButtonImage(IDB_BT_RESTORE,AfxGetInstanceHandle(),true,false);

		//�޸ķֱ���
		ChangeScreenSetting(m_ScreenMetrics.cx,m_ScreenMetrics.cy,false);

		//�ƶ�����
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//���и���
LRESULT CPlatformFrame::OnMessageInsureUpdate(WPARAM wParam, LPARAM lParam)
{
	//��ȡ����
	tagInsurePlazaUpdata * pInsurePlazaUpdate = (tagInsurePlazaUpdata *)wParam;
	ASSERT(pInsurePlazaUpdate!=NULL);
	if(pInsurePlazaUpdate==NULL) return 0L;

	//�û���Ϣ
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	if(pGlobalUserData==NULL) return 0;
    
	//��������
	pGlobalUserData->lUserScore=pInsurePlazaUpdate->lUserScore;
	pGlobalUserData->lUserInsure=pInsurePlazaUpdate->lUserInsure;

	//ƽ̨�¼�
	CPlatformEvent * pPlatformEvent = CPlatformEvent::GetInstance();
	ASSERT(pPlatformEvent!=NULL);
	pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);

	return 0L;
}

//////////////////////////////////////////////////////////////////////////////////
