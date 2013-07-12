#include "Stdafx.h"
#include "Resource.h"
#include "VideoServiceControl.h"

//////////////////////////////////////////////////////////////////////////

//���ڱ�ʶ
#define IDC_VIDEO_SNED				100									//���ʹ���
#define IDC_VIDEO_RCEC				100									//���մ���
#define IDC_VIDEO_SR				100									//��Ƶ����

//��ť��ʶ
#define IDC_FLOWER					103									//�ͻ���ť
#define IDC_VIDEO					104									//��Ƶ��ť
#define IDC_AUDIO					105									//��Ƶ��ť
#define IDC_CLONE					106									//��¡��ť
#define IDC_MORE					107									//���ఴť


//λ�ñ�ʶ
#define X_SMALL_POS					5									//��ʼ����
#define Y_SMALL_POS					4									//��ʼ����
#define X_LARGE_POS					5									//��ʼ����
#define Y_LARGE_POS					5									//��ʼ����

//��ȱ�ʶ
#define W_SMALL_POS					90									//�������
#define H_SMALL_POS					60									//�߶�����
#define W_LARGE_POS					161									//�������
#define H_LARGE_POS					120									//�߶�����

//////////////////////////////////////////////////////////////////////////

//�˵�����
#define	IDM_UM_COPY_NAME			WM_USER+100							//��������
#define	IDM_UM_SET_CHAT				WM_USER+101							//��������
#define	IDM_UM_CANECL_CHAT			WM_USER+102							//ȡ������
#define	IDM_UM_ALLOW_LOOKON			WM_USER+103							//�Թۿ���
#define	IDM_UM_ENJOIN_LOOKON		WM_USER+104							//�Թۿ���


//�ʻ��˵�
#define	IDM_UM_FLOWER				WM_USER+306							//��������


//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CVideoServiceControl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_FLOWER,OnBnClickedFlower)
	ON_BN_CLICKED(IDC_VIDEO,OnBnClickedVideo)
	ON_BN_CLICKED(IDC_AUDIO,OnBnClickedAudio)
	ON_BN_CLICKED(IDC_CLONE,OnBnClickedClone)
	ON_BN_CLICKED(IDC_MORE,OnBnClickedMore)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CVideoServiceManager, CWnd)
	ON_MESSAGE(WM_GV_CONNECT,OnGVClientConnect)
	ON_MESSAGE(WM_GV_LOGINSYSTEM,OnGVClientLogin)
	ON_MESSAGE(WM_GV_ENTERROOM,OnGVClientEnterRoom)
	ON_MESSAGE(WM_GV_ONLINEUSER,OnGVClientOnlineUser)
	ON_MESSAGE(WM_GV_USERATROOM,OnGVClientUserAtRoom)
	ON_MESSAGE(WM_GV_LINKCLOSE,OnGVClientLinkClose)
	ON_MESSAGE(WM_GV_CAMERASTATE,OnGVClientCameraState)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//��̬����
CVideoServiceManager * CVideoServiceManager::m_pVideoServiceManager=NULL;//�������
HINSTANCE CVideoServiceManager::m_hResInstance=NULL;
//tagVideoFrameImage CVideoServiceManager::m_VideoFrameImage;
//tagPropertyMenuImage CVideoServiceManager::m_PropertyMenuImage;


//ȫ�ֱ���
bool							g_bClientClosed=true;

//////////////////////////////////////////////////////////////////////////
//�ص�����

//��Ƶ���ݻص�����
void CALLBACK VideoDataCallBack(DWORD dwUserID, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
	//�ر��ж�
	if (g_bClientClosed) return;

	CVideoServiceManager* pVideoServiceManager=(CVideoServiceManager*)lpUserValue;

	if(pVideoServiceManager&&pVideoServiceManager->m_hWnd!=NULL) 
	{
		//��ȡ���
		IClientKernel *pIClientKernel=pVideoServiceManager->GetClientKernel();
		if (pIClientKernel==NULL) return;
		if (pIClientKernel->IsServiceStatus()==false) return;
 		IClientUserItem *pClientUserItem=pVideoServiceManager->GetClientKernel()->SearchUserByUserID(dwUserID);
		if (pClientUserItem==NULL) return;

		//�滭��Ƶ
		WORD wVideoIndex=pVideoServiceManager->GetVideoIndex(pClientUserItem->GetUserInfo());
		if (wVideoIndex==MAX_CHAIR) return;
		CVideoServiceControl *pVideoServiceControl=pVideoServiceManager->GetVideoServiceControl(wVideoIndex);
		pVideoServiceControl->DrawUserVideo(dwUserID,lpBuf,dwLen,bmiHeader);
	}
}

//��Ƶ�ص�
void CALLBACK AudioDataCallBack(DWORD dwUserID, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
	//�ر��ж�
	if (g_bClientClosed) return;

	CVideoServiceManager* pVideoServiceManager=(CVideoServiceManager*)lpUserValue;
	if(pVideoServiceManager) 
	{
		//��ȡ���
		IClientUserItem *pUserData=pVideoServiceManager->GetClientKernel()->SearchUserByGameID(dwUserID);
		if (pUserData==NULL) return;

		//��ȡ����		
		WORD wVideoIndex=pVideoServiceManager->GetVideoIndex(pUserData->GetUserInfo());
		if (wVideoIndex==MAX_CHAIR) return;
		CVideoServiceControl *pVideoServiceControl=pVideoServiceManager->GetVideoServiceControl(wVideoIndex);
		ASSERT(pVideoServiceControl!=NULL);
		if (pVideoServiceControl==NULL) return;
		ASSERT(pVideoServiceControl->GetSafeHwnd()!=NULL);
		if (pVideoServiceControl->GetSafeHwnd()==NULL) return;

		// ��������
		USHORT* pData = (USHORT*)lpBuf;
		DWORD	datalen = dwLen/2;
		LONGLONG totalvolume = 0;
		for(int i=0; i<(int)datalen; i++)
		{
			totalvolume += *(pData + i);
		}
		DWORD dwCurrentVolume=(DWORD)((totalvolume% (0xFFFF-1))*100)/(0xFFFF-1);

		//�滭����
		pVideoServiceControl->SetVolume(dwCurrentVolume);
	}
}

//���캯��
CVideoServiceControl::CVideoServiceControl()
{
	//�ں˱���
	m_bInitVideo=false;
	m_bShowVideo=false;

	//���Ʊ���
	m_bSmallMode=false;
	m_bLocalMode=false;
	m_bEnableVideo=true;
	m_bEnableAudio=true;

	//״̬����
	m_fVolumePercent=0.0f;

	//�ͻ�����
	m_dwTargerUserID = 0;

	//�û���Ϣ
	m_dwUserID=0L;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));

	//�ͻ�����
	m_pUserData=NULL;

	//������Դ
	HINSTANCE hResInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	m_ImageSmallPhoto.LoadFromResource(hResInstance,IDB_SMALL_PHOTO);
	m_ImageLargePhoto.LoadFromResource(hResInstance,IDB_LARGE_PHOTO);
	m_ImageSmallFrame.LoadFromResource(hResInstance,IDB_SMALL_FRAME);
	m_ImageLargeFrame.LoadFromResource(hResInstance,IDB_LARGE_FRAME);

	m_ImageLargeVolume.LoadFromResource	 (hResInstance,IDB_LARGE_VOLUME);
	m_ImageLargeVolumeEx.LoadFromResource(hResInstance,IDB_LARGE_VOLUME_EX);
	m_ImageSmallVolumeEx.LoadFromResource(hResInstance,IDB_SMALL_VOLUME_EX);
	m_ImageSmallVolume.LoadFromResource  (hResInstance,IDB_SMALL_VOLUME);	

	return;
}

//��������
CVideoServiceControl::~CVideoServiceControl()
{
	g_bClientClosed=true;
}

//��Ϣ����
BOOL CVideoServiceControl::PreTranslateMessage(MSG * pMsg)
{
	//��ʾ��Ϣ
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//��������
void CVideoServiceControl::SetVolume(DWORD dwCurrentVolume)
{
	//�������
	m_fVolumePercent = dwCurrentVolume/(100.f);
	if (m_fVolumePercent>1.0) m_fVolumePercent=1.0f;

	//���½���
	InvalidateRect(&m_rcPaintVolume);
}

//��Сģʽ
bool CVideoServiceControl::SetSmallMode(bool bSmallMode)
{
	//���ñ���
	if (m_bSmallMode!=bSmallMode)
	{
		//���ñ���
		m_bSmallMode=bSmallMode;

		//��������
		RectifyControl();
	}

	return true;
}

//��ȡ��С
void CVideoServiceControl::GetVideoSize(CRect &rcVideo)
{
	if (m_bSmallMode==true) rcVideo.SetRect(X_SMALL_POS,Y_SMALL_POS,X_SMALL_POS+W_SMALL_POS,Y_SMALL_POS+H_SMALL_POS);
	else rcVideo.SetRect(X_LARGE_POS,Y_LARGE_POS,X_LARGE_POS+W_LARGE_POS,Y_LARGE_POS+H_LARGE_POS);
}

//�����û�
bool CVideoServiceControl::SetVideoUserInfo(DWORD dwUserID, LPCTSTR pszAccounts)
{
	//���ñ���
	m_dwUserID=dwUserID;
	lstrcpyn(m_szAccounts,pszAccounts,CountArray(m_szAccounts));

	//ˢ�´���
	if (m_hWnd!=NULL) Invalidate(FALSE);

	return true;
}

//������Ƶ
bool CVideoServiceControl::InitVideoService(bool bLocalMode, bool bSmallMode)
{
	//Ч��״̬
	ASSERT((m_hWnd!=NULL)&&(m_bInitVideo==false));
	if ((m_hWnd==NULL)||(m_bInitVideo==true)) return false;

	//��ȡ����
	ASSERT(CVideoServiceManager::GetInstance()!=NULL);
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();

	//���ñ���
	m_bInitVideo=true;
	m_bSmallMode=bSmallMode;
	m_bLocalMode=bLocalMode;

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	m_btMore.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_MORE:IDB_BT_BIG_MORE,hResInstance,false,false);
	m_btVideo.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_SEE:IDB_BT_BIG_SEE,hResInstance,false,false);
	m_btAudio.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_TALK:IDB_BT_BIG_TALK,hResInstance,false,false);
	m_btClone.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_RESORE:IDB_BT_BIG_RESORE,hResInstance,false,false);
	m_btFlower.SetButtonImage(m_bSmallMode?IDB_BT_SMALL_FLOWER:IDB_BT_BIG_FLOWER,hResInstance,false,false);


	//��������
	RectifyControl();

	//��������	
	if (m_bSmallMode==true)
	{
		//����ͼƬ
// 		CImageHandle HandleFrame(&m_ImageSmallFrame);
// 		CImageHandle ImageVolume(&m_ImageSmallVolume);

		m_rcPaintVolume.left = (m_ImageSmallFrame.GetWidth()-m_ImageSmallVolume.GetWidth())/2;
		m_rcPaintVolume.top = H_SMALL_POS+8;
		m_rcPaintVolume.right = m_rcPaintVolume.left + m_ImageSmallVolume.GetWidth();
		m_rcPaintVolume.bottom = m_rcPaintVolume.top + m_ImageSmallVolume.GetHeight();
	}
	else
	{
		//����ͼƬ
// 		CImageHandle HandleFrame(&m_ImageLargeFrame);
// 		CImageHandle ImageVolume(&m_ImageLargeVolume);

		m_rcPaintVolume.left = (m_ImageLargeFrame.GetWidth()-m_ImageLargeVolume.GetWidth())/2;;
		m_rcPaintVolume.top = H_LARGE_POS+10;
		m_rcPaintVolume.right = m_rcPaintVolume.left + m_ImageLargeVolume.GetWidth();
		m_rcPaintVolume.bottom = m_rcPaintVolume.top + m_ImageLargeVolume.GetHeight();
	}
	return true;
}

//��������
VOID CVideoServiceControl::RectifyControl()
{
	//�����ж�
	if (m_hWnd==NULL) return;

	//��������
	if (m_bInitVideo==true)
	{
		//������Դ
		CBitImage *pImageFrame;
		if (m_bSmallMode==true) pImageFrame=&m_ImageSmallFrame;
		if (m_bSmallMode==false) pImageFrame=&m_ImageLargeFrame;

		//��������
		INT nFrameWidth=pImageFrame->GetWidth();
		INT nFrameHeight=pImageFrame->GetHeight();
		SetWindowPos(NULL,0,0,nFrameWidth,nFrameHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);

		//��������
		INT nSpace=m_bSmallMode?1:10;
		INT nXCenterPos=pImageFrame->GetWidth()/2;
		INT nYPos=m_bSmallMode?H_SMALL_POS+13:H_LARGE_POS+18;
		const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOSIZE;

		//��ťλ��
		CRect rcButton;
		m_btFlower.GetWindowRect(&rcButton);

		//�ƶ���ť
		HDWP hDwp=BeginDeferWindowPos(32);
		DeferWindowPos(hDwp,m_btFlower,NULL,nXCenterPos-rcButton.Width()*5/2-nSpace*2,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btVideo,NULL,nXCenterPos-rcButton.Width()*3/2-nSpace,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btAudio,NULL,nXCenterPos-rcButton.Width()/2,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btClone,NULL,nXCenterPos+rcButton.Width()/2+nSpace,nYPos,0,0,uFlags);
		DeferWindowPos(hDwp,m_btMore,NULL,nXCenterPos+rcButton.Width()*3/2+nSpace*2,nYPos,0,0,uFlags);
		EndDeferWindowPos(hDwp);
	}
	else
	{
		//��С����
		SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOCOPYBITS);
	}

	//�ػ�����
	Invalidate(TRUE);

	return;
}

//��¡��ť
VOID CVideoServiceControl::OnBnClickedClone()
{
	if (m_bShowVideo==true)
	{
		if (m_DlgVideoClone.m_hWnd==NULL) m_DlgVideoClone.Create(IDD_VIDEO_CLONE,this);
		m_DlgVideoClone.ShowWindow(SW_SHOW);
		m_DlgVideoClone.CenterWindow();
		m_DlgVideoClone.BringWindowToTop();
	}
}

//�ػ�����
VOID CVideoServiceControl::OnPaint()
{
	CPaintDC dcPaint(this);

	//�����ж�
	ASSERT(m_bInitVideo==true);
	if (m_bInitVideo==false) return;

	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);

	//�ڴ�DC
	CDC dcBuffer;
	dcBuffer.CreateCompatibleDC(&dcPaint);
	CBitmap BufferBmp;
	BufferBmp.CreateCompatibleBitmap(&dcPaint, rcClient.Width(), rcClient.Height());
	dcBuffer.SelectObject(&BufferBmp);

	//�����ж�
	CRect rcClipBox;
	dcPaint.GetClipBox(rcClipBox);
	if ( rcClipBox != m_rcPaintVolume )
	{
		//�滭����
		if (m_bSmallMode==true)
		{
//			CImageHandle HandleFrame(&m_ImageSmallFrame);
			m_ImageSmallFrame.BitBlt(dcBuffer,0,0);

			//����ͼƬ
//			CImageHandle ImageVolume(&m_ImageSmallVolume);

			INT nXPos=(m_ImageSmallFrame.GetWidth()-m_ImageSmallVolume.GetWidth())/2;
			INT nYPos=H_SMALL_POS+8;
			m_ImageSmallVolume.BitBlt(dcBuffer,nXPos, nYPos);
		}
		else
		{
			//CImageHandle HandleFrame(&m_ImageLargeFrame);
			m_ImageLargeFrame.BitBlt(dcBuffer,0,0);

			//����ͼƬ
			//CImageHandle ImageVolume(&m_ImageLargeVolume);

			INT nXPos=(m_ImageLargeFrame.GetWidth()-m_ImageLargeVolume.GetWidth())/2;
			INT nYPos=H_LARGE_POS+10;
			m_ImageLargeVolume.BitBlt(dcBuffer,nXPos, nYPos);
		}

		//��Ƶ��ʶ
		if (m_bShowVideo==false)
		{
			if (m_bSmallMode==true)
			{
				m_ImageSmallPhoto.BitBlt(dcBuffer,X_SMALL_POS+(W_SMALL_POS-m_ImageSmallPhoto.GetWidth())/2,Y_SMALL_POS+(H_SMALL_POS-m_ImageSmallPhoto.GetHeight())/2);
			}
			else
			{
				m_ImageLargePhoto.BitBlt(dcBuffer,X_LARGE_POS+(W_LARGE_POS-m_ImageLargePhoto.GetWidth())/2,Y_LARGE_POS+(H_LARGE_POS-m_ImageLargePhoto.GetHeight())/2);
			}
		}

		dcPaint.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcBuffer, 0, 0, SRCCOPY);
	}
	else
	{
		if (m_bSmallMode==true)
		{
			//����ͼƬ
			m_ImageSmallVolume.BitBlt(dcBuffer,m_rcPaintVolume.left, m_rcPaintVolume.top);
			m_ImageSmallVolumeEx.BitBlt(dcBuffer,m_rcPaintVolume.left, m_rcPaintVolume.top,int(m_rcPaintVolume.Width()*m_fVolumePercent),m_rcPaintVolume.Height(),0,0);
		}
		else
		{
			//����ͼƬ
			m_ImageLargeVolume.BitBlt(dcBuffer,m_rcPaintVolume.left, m_rcPaintVolume.top);
			m_ImageLargeVolumeEx.BitBlt(dcBuffer,m_rcPaintVolume.left, m_rcPaintVolume.top,int(m_rcPaintVolume.Width()*m_fVolumePercent),m_rcPaintVolume.Height(),0,0);
		}

		dcPaint.BitBlt(rcClipBox.left, rcClipBox.top, rcClipBox.Width(), rcClipBox.Height(), &dcBuffer, rcClipBox.left, rcClipBox.top, SRCCOPY);
	}

	//������Դ
	dcBuffer.DeleteDC();
	BufferBmp.DeleteObject();	

	return;
}

//��������
INT CVideoServiceControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//�޸Ĵ�������
	ModifyStyle(0,WS_CLIPCHILDREN);

	//������ť
	CRect rcCreate(0,0,0,0);
	m_btMore.Create(TEXT(""),WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MORE);
	m_btVideo.Create(TEXT(""),WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_VIDEO);
	m_btAudio.Create(TEXT(""),WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_AUDIO);
	m_btClone.Create(TEXT(""),WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CLONE);
	m_btFlower.Create(TEXT(""),WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_FLOWER);

	//������ʾ
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(&m_btMore, TEXT("�鿴��Ϣ"));
	m_ToolTipCtrl.AddTool(&m_btVideo, TEXT("��ֹ��Ƶ"));
	m_ToolTipCtrl.AddTool(&m_btAudio, TEXT("��ֹ����"));
	m_ToolTipCtrl.AddTool(&m_btClone, TEXT("������Ƶ"));
	m_ToolTipCtrl.AddTool(&m_btFlower, TEXT("�����ʻ�"));

	//��������
	RectifyControl();

	return 0;
}

//�ͻ���ť
VOID CVideoServiceControl::OnBnClickedFlower()
{
// 		//��ȡĿ��
// 	m_dwTargerUserID = GetVideoUserID();
// 	if ( m_dwTargerUserID == 0 ) return;
// 
// 	//�˵�����
// 	UINT uCommands[FLOWER_COUNT] ;
// 	for ( WORD wCmdIdx = 0; wCmdIdx < FLOWER_COUNT; ++wCmdIdx )
// 		uCommands[wCmdIdx] = IDM_UM_FLOWER + wCmdIdx;
// 
// 	//�˵�λͼ
// 	CBitmap MenuBmps[FLOWER_COUNT];
// 	AfxSetResourceHandle(CVideoServiceManager::m_hResInstance);
// 	tagPropertyMenuImage & PropertyMenuImage=CVideoServiceManager::m_PropertyMenuImage;
// 
// 	//����λͼ
// 	for(WORD i=0;i<FLOWER_COUNT;i++)
// 	{
// 		MenuBmps[i].LoadBitmap( PropertyMenuImage.uMenuGift[i] );
// 	}
// 
// 	AfxSetResourceHandle(GetModuleHandle(NULL));
//     
//     //�����˵�
// 	CMenu GiftMenu;
// 	GiftMenu.CreatePopupMenu();
// 
// 	//���ò˵�
// 	for ( UINT uMenuItem = 0; uMenuItem < FLOWER_COUNT; ++uMenuItem )
// 	{
// 		//�˵���Ϣ
// 		CString strMenuItem = g_FlowerDescribe[uMenuItem].szName;
// 		CString strGiftPay;
// 		strGiftPay.Format("%ld", CPropertyBar::m_FlowerInfo[uMenuItem].lPrice);
// 		strMenuItem += strGiftPay;
// 
// 		//���Ӳ˵�
// 		GiftMenu.AppendMenu( 0, uCommands[uMenuItem], strMenuItem);
// 		GiftMenu.SetMenuItemBitmaps(uCommands[uMenuItem], MF_BYCOMMAND,&MenuBmps[uMenuItem], &MenuBmps[uMenuItem] );
// 	}	
// 
// 	//��ȡλ��
// 	CPoint MousePoint;
// 	GetCursorPos(&MousePoint);
// 
// 	GiftMenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,MousePoint.x,MousePoint.y,this);
// 
// 	//�ͷ���Դ
// 	for ( INT nBmpIdx = 0; nBmpIdx < FLOWER_COUNT; ++nBmpIdx ) MenuBmps[nBmpIdx].DeleteObject();
// 	GiftMenu.DestroyMenu();

	return;
}

//�˵�����
BOOL CVideoServiceControl::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//��ȡ����
	UINT uCmd = LOWORD(wParam);

// 	if ( IDM_UM_FLOWER <= uCmd && uCmd <= IDM_UM_FLOWER + FLOWER_COUNT )
// 	{
// 		//����ת��
// 		UINT uBaseCmd = IDM_UM_FLOWER;
// 		UINT uFlowerIdx = uCmd - uBaseCmd;
// 
// 		//������Ϣ
// 		CString strMsg;
// 		LONG lValue = CPropertyBar::m_FlowerInfo[uFlowerIdx].lPrice;
// 		strMsg.Format(TEXT("��ѡ�������ͣ�%s�ݣ�����۳�[%ld]�𶹡�\n�����ǡ�����\n������ȡ����β���"),g_FlowerDescribe[uFlowerIdx].szName, lValue, lValue );
// 		if(IDYES!=MessageBox(strMsg,TEXT("��ܰ��ʾ"),MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2))
// 			return TRUE;
// 
// 		//�����ж�
// 		DWORD dwRcvUserID = GetVideoUserID();
// 		if ( dwRcvUserID == 0 || m_dwTargerUserID != dwRcvUserID )
// 		{
// 			MessageBox(strMsg,TEXT("��ܰ��ʾ"), MB_ICONINFORMATION );
// 			return TRUE;
// 		}
// 
// 		//��ȡ����
// 		ASSERT(CVideoServiceManager::GetInstance()!=NULL);
// 		CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();
// 		IClientKernel *pIClientKernel = pVideoServiceManager->m_pIClientKernel;
// 		ASSERT( pIClientKernel != NULL );
// 
// 		//��������
// 		CMD_GF_Gift Gift;
// 		ZeroMemory( &Gift, sizeof( Gift ) );
// 
// 		Gift.cbSendLocation = LOCATION_GAME_ROOM;
// 		Gift.wFlowerCount=1;
// 		Gift.dwRcvUserID = GetVideoUserID();
// 		Gift.dwSendUserID = pVideoServiceManager->m_dwLocalUserID;
// 		Gift.wGiftID = uFlowerIdx;
// 
// 		//������Ϣ
// 		pIClientKernel->SendSocketData( MDM_GF_PRESENT,SUB_GF_FLOWER,&Gift, sizeof(Gift));
// 
// 		return TRUE;
// 	}

	//��ȡ����
	ASSERT(CVideoServiceManager::GetInstance()!=NULL);
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();
	ASSERT(pVideoServiceManager!=NULL) ;

	//��������
	IClientKernel * pIClientKernel=pVideoServiceManager->m_pIClientKernel;
	ASSERT(pIClientKernel!=NULL) ;

	switch (LOWORD(wParam))
	{
	case IDM_UM_COPY_NAME:		//��������
		{
			if ( m_pUserData == NULL ) return TRUE;

			//Ѱ�����
			if ((m_pUserData==NULL)||(m_pUserData->dwUserID==0)) return TRUE;

			//�򿪼��а�
			if (OpenClipboard()==FALSE) return TRUE;
			if (EmptyClipboard()==FALSE) 
			{
				CloseClipboard();
				return TRUE;
			}

			//��������
			HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,LEN_NICKNAME);
			if (hData==NULL) 
			{
				CloseClipboard();
				return TRUE;
			}
			LPTSTR szMemName=(LPTSTR)GlobalLock(hData);
			lstrcpy(szMemName,m_pUserData->szNickName);
			SetClipboardData(CF_TEXT,hData);
			GlobalUnlock(hData);
			CloseClipboard();

			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//��Ƶ��ť
VOID CVideoServiceControl::OnBnClickedVideo()
{
	//�Ϸ��ж�
	if (m_dwUserID==0) return ;

	//��ȡ�豸
	CHAR szDeviceName[128];
	DWORD dwReturnValue=BRAC_GetCurVideoCapture(szDeviceName,CountArray(szDeviceName));
	if (dwReturnValue!=GV_ERR_SUCCESS || szDeviceName[0]==0) return;

	//���ñ���
	m_bEnableVideo=!m_bEnableVideo;

	//���ð�ť
	HINSTANCE hInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	if (m_bSmallMode==false) m_btVideo.SetButtonImage((m_bEnableVideo==true)?IDB_BT_BIG_SEE:IDB_BT_BIG_NOSEE,hInstance,false,false);
	if (m_bSmallMode==true) m_btVideo.SetButtonImage((m_bEnableVideo==true)?IDB_BT_SMALL_SEE:IDB_BT_SMALL_NOSEE,hInstance,false,false);

	if ( m_bEnableVideo ) m_ToolTipCtrl.AddTool(&m_btVideo, TEXT("��ֹ��Ƶ"));
	else m_ToolTipCtrl.AddTool(&m_btVideo, TEXT("������Ƶ"));

	BRAC_UserCameraControl(m_dwUserID,m_bEnableVideo);
	m_bShowVideo=m_bEnableVideo;

	//�ػ��ؼ�
	Invalidate(FALSE);

	return;
}

//��Ƶ��ť
VOID CVideoServiceControl::OnBnClickedAudio()
{
	//�Ϸ��ж�
	if (m_dwUserID==0) return ;

	//���ñ���
	m_bEnableAudio=!m_bEnableAudio;

	//���ð�ť
	HINSTANCE hInstance=GetModuleHandle(VIDEO_SERVICE_DLL_NAME);
	if (m_bSmallMode==false) m_btAudio.SetButtonImage((m_bEnableAudio==true)?IDB_BT_BIG_TALK:IDB_BT_BIG_NOTALK,hInstance,false,false);
	if (m_bSmallMode==true) m_btAudio.SetButtonImage((m_bEnableAudio==true)?IDB_BT_SMALL_TALK:IDB_BT_SMALL_NOTALK,hInstance,false,false);

	if ( m_bEnableAudio ) m_ToolTipCtrl.AddTool(&m_btAudio, TEXT("��ֹ����"));
	else m_ToolTipCtrl.AddTool(&m_btAudio, TEXT("��������"));

	//��Ƶ����
	BRAC_UserSpeakControl(m_dwUserID,m_bEnableAudio);

	//���ñ���
	m_fVolumePercent=0.f;

	//���½���
	InvalidateRect(m_rcPaintVolume);
	
	return;
}

//���ఴť
VOID CVideoServiceControl::OnBnClickedMore()
{
	//��ȡλ��
	CPoint MousePoint;
	GetCursorPos(&MousePoint);

	//��ȡ����
	ASSERT(CVideoServiceManager::GetInstance()!=NULL);
	CVideoServiceManager * pVideoServiceManager=CVideoServiceManager::GetInstance();
	ASSERT( pVideoServiceManager != NULL ) ;

	//��ȡ�ӿ�
	IClientKernel * pIClientKernel=pVideoServiceManager->m_pIClientKernel;
	ASSERT( pIClientKernel != NULL ) ;

	//��ȡ�û�
	TCHAR szBuffer[512]=TEXT("");
	IClientUserItem *pUserItem=pIClientKernel->SearchUserByUserID(m_dwUserID);
	if(pUserItem==NULL) return;
	m_pUserData=pUserItem->GetUserInfo();
	if(m_pUserData==NULL) return;

	//Ԥ�ȼ���
	double dFleeRate=0.0;
	DWORD dwPlayCount=m_pUserData->dwWinCount+m_pUserData->dwLostCount+m_pUserData->dwDrawCount+m_pUserData->dwFleeCount;
	if (m_pUserData->dwFleeCount>0)
	{
		dFleeRate=(double)(m_pUserData->dwFleeCount*100)/(double)dwPlayCount;
		if (dFleeRate<0.01) dFleeRate=0.0;
	}

	//����˵�
	CSkinMenu UserInfoMenu;
	UserInfoMenu.CreateMenu();

	//���ܲ˵�
	UserInfoMenu.AppendMenu(IDM_UM_COPY_NAME,TEXT("�����û���"));
	UserInfoMenu.AppendSeparator();

	//�û���ν
	_sntprintf(szBuffer,CountArray(szBuffer),TEXT("�û�����%s"),m_pUserData->szNickName);
	UserInfoMenu.AppendMenu(0,szBuffer);

	//�û� ID
	_sntprintf(szBuffer,CountArray(szBuffer),TEXT("��Ϸ ID��%ld"),m_pUserData->dwUserID);
	UserInfoMenu.AppendMenu(0,szBuffer);

	//�û�����
	_sntprintf(szBuffer,CountArray(szBuffer),TEXT("����ֵ��%ld"),m_pUserData->dwExperience);
	UserInfoMenu.AppendMenu(0,szBuffer);

	//�û�����
	_sntprintf(szBuffer,CountArray(szBuffer),TEXT("���֣�%ld  �ܾ�����%ld  �����ʣ�%.2f%%"),m_pUserData->lScore,dwPlayCount,dFleeRate);
	UserInfoMenu.AppendMenu(0,szBuffer);

	//��ȡ�û�
	const tagUserInfo* pMeUserData=pIClientKernel->GetMeUserItem()->GetUserInfo();

	//��ʾ�˵�
	UserInfoMenu.TrackPopupMenu(/*TPM_LEFTALIGN|TPM_LEFTBUTTON,MousePoint.x,MousePoint.y,*/this);

	return;
}

//������Ƶ
void CVideoServiceControl::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
	if (m_hWnd==NULL) return;

	//��¡�ж�
	if (m_DlgVideoClone.m_hWnd!=NULL) m_DlgVideoClone.DrawUserVideo(dwUserid, lpBuf, dwLen, bmiHeader);

	//����λͼ
	BITMAPINFOHEADER  *lpbmi = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER)+dwLen);  
	ZeroMemory(lpbmi,sizeof(BITMAPINFOHEADER)+dwLen);
    memcpy((LPBYTE)lpbmi,&bmiHeader,sizeof(bmiHeader));
	memcpy(((LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER)),lpBuf,dwLen);  

	HDC hdc=::GetDC(m_hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,lpbmi,CBM_INIT,(LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)lpbmi,DIB_RGB_COLORS);  

	//����λ��
	CRect rcVideo;
	if (m_bSmallMode==true) rcVideo.SetRect(X_SMALL_POS,Y_SMALL_POS,X_SMALL_POS+W_SMALL_POS,Y_SMALL_POS+H_SMALL_POS);
	else rcVideo.SetRect(X_LARGE_POS,Y_LARGE_POS,X_LARGE_POS+W_LARGE_POS,Y_LARGE_POS+H_LARGE_POS);

	//��ͼλͼ 
	HBITMAP holdbm = (HBITMAP)SelectObject(dcMem,hBitmap);  
	::SetStretchBltMode(hdc,COLORONCOLOR);
	::StretchBlt(hdc,rcVideo.left,rcVideo.top,rcVideo.Width(),rcVideo.Height(),dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);

	//�ͷ���Դ
	SelectObject(dcMem,holdbm);  
	DeleteObject(dcMem);
	DeleteObject(hBitmap);
	DeleteObject(hdc);
	free(lpbmi);
	lpbmi = NULL;

	//���ñ�ʶ
	m_bShowVideo=true;
}

//�����¼�
bool CVideoServiceControl::OnEventUserEnter()
{
	return true;
}

//�뿪�¼�
bool CVideoServiceControl::OnEventUserLeave()
{
	CString strLog;
	strLog.Format(TEXT("%s �뿪"),m_szAccounts);
	CVideoServiceManager::GetInstance()->AppendLogString(strLog);

	//���ñ�ʶ
	m_bShowVideo=false;

	//�û���Ϣ
	m_dwUserID=0;	
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));

	//���½���
	InvalidateRect(NULL);
    
	return true;
}

//�����¼�
bool CVideoServiceControl::OnEventReset()
{
	//�ں˱���
	m_bShowVideo=false;

	//���Ʊ���
	m_bEnableVideo=true;
	m_bEnableAudio=true;

	//״̬����
	m_fVolumePercent=0.0f;

	//�û���Ϣ
	m_dwUserID=0L;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));

	//�ͻ�����
	m_pUserData=NULL;

	return true;
}

//����ͷ�¼�
void CVideoServiceControl::OnEventCameraState(BYTE cbState)
{
	//���ñ�ʶ
	if (cbState==GV_CAMERA_STATE_OPEN) m_bShowVideo=true;
	else m_bShowVideo=false;

	//���½���
	InvalidateRect(NULL);
}
//////////////////////////////////////////////////////////////////////////

//���캯��
CVideoServiceManager::CVideoServiceManager()
{
	//��Ƶ��Ϣ
	m_wVideoPort=0;
	m_dwVideoServer=0L;
	m_dwLocalUserID=0L;
	ZeroMemory(m_dwUserID,sizeof(m_dwUserID));
	m_dwVideoRoomID=0;

	//�������
	m_pIClientKernel=NULL;
	m_pIMessageProxy=NULL;
	ZeroMemory(m_VideoServiceControl,sizeof(m_VideoServiceControl));

	//���ö���
	ASSERT(m_pVideoServiceManager==NULL);
	if (m_pVideoServiceManager==NULL) m_pVideoServiceManager=this;

	//���ܰ�ť
// 	m_VideoFrameImage.uBtBigFlower  = DEF_IDB_BT_VIDEO_BIG_FLOWER  ; 
// 	m_VideoFrameImage.uBtBigMore    = DEF_IDB_BT_VIDEO_BIG_MORE    ;  
// 	m_VideoFrameImage.uBtBigNosee   = DEF_IDB_BT_VIDEO_BIG_NOSEE   ;  
// 	m_VideoFrameImage.uBtBigNotalk  = DEF_IDB_BT_VIDEO_BIG_NOTALK  ; 
// 	m_VideoFrameImage.uBtBigResore  = DEF_IDB_BT_VIDEO_BIG_RESORE  ; 
// 	m_VideoFrameImage.uBtBigSee     = DEF_IDB_BT_VIDEO_BIG_SEE     ;  
// 	m_VideoFrameImage.uBtBigTalk    = DEF_IDB_BT_VIDEO_BIG_TALK    ;  
// 	m_VideoFrameImage.uBtSmallFlower= DEF_IDB_BT_VIDEO_SMALL_FLOWER; 
// 	m_VideoFrameImage.uBtSmallMore  = DEF_IDB_BT_VIDEO_SMALL_MORE  ; 
// 	m_VideoFrameImage.uBtSmallNosee = DEF_IDB_BT_VIDEO_SMALL_NOSEE ; 
// 	m_VideoFrameImage.uBtSmallNotalk= DEF_IDB_BT_VIDEO_SMALL_NOTALK; 
// 	m_VideoFrameImage.uBtSmallResore= DEF_IDB_BT_VIDEO_SMALL_RESORE; 
// 	m_VideoFrameImage.uBtSmallSee   = DEF_IDB_BT_VIDEO_SMALL_SEE   ;  
// 	m_VideoFrameImage.uBtSmallTalk  = DEF_IDB_BT_VIDEO_SMALL_TALK  ; 
// 
// 	//�����Դ
// 	m_VideoFrameImage.uBigFemale		=	DEF_IDB_VIDEO_LARGE_FEMALE	  ; 
// 	m_VideoFrameImage.uBigFrame		 =	DEF_IDB_VIDEO_LARGE_FRAME	  ; 
// 	m_VideoFrameImage.uBigMale		 =	DEF_IDB_VIDEO_LARGE_MALE	  ; 
// 	m_VideoFrameImage.uBigPhoto		=	DEF_IDB_VIDEO_LARGE_PHOTO	  ; 
// 	m_VideoFrameImage.uBigVolume		=	DEF_IDB_VIDEO_LARGE_VOLUME	  ; 
// 	m_VideoFrameImage.uBigVolumeEx	 =	DEF_IDB_VIDEO_LARGE_VOLUME_EX ;
// 	m_VideoFrameImage.uSmallFemale	 =	DEF_IDB_VIDEO_SMALL_FEMALE	  ; 
// 	m_VideoFrameImage.uSmallFrame		=	DEF_IDB_VIDEO_SMALL_FRAME	 ; 
// 	m_VideoFrameImage.uSmallMale		=	DEF_IDB_VIDEO_SMALL_MALE	  ; 
// 	m_VideoFrameImage.uSmallPhoto		=	DEF_IDB_VIDEO_SMALL_PHOTO	  ; 
// 	m_VideoFrameImage.uSmallVolume	=	DEF_IDB_VIDEO_SMALL_VOLUME	 ; 
// 	m_VideoFrameImage.uSmallVolumeEx =	DEF_IDB_VIDEO_SMALL_VOLUME_EX; 


	return;
}

//��������
CVideoServiceManager::~CVideoServiceManager()
{
	g_bClientClosed=true;
}

//���ýӿ�
bool CVideoServiceManager::SetClientKernel(IUnknownEx * pIUnknownEx)
{
	//���ýӿ�
	if (pIUnknownEx!=NULL)
	{
		//��ѯ�ӿ�
		ASSERT(QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IClientKernel)!=NULL);
		m_pIClientKernel=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IClientKernel);

		//�ɹ��ж�
		if (m_pIClientKernel==NULL) return false;
	}
	else m_pIClientKernel=NULL;

	//��������
	if (m_hWnd==NULL)
	{
		Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),GetDesktopWindow(),300);	
		g_bClientClosed=false;
	}

	return true;
}

//������Ϣ
bool CVideoServiceManager::SetVideoServiceInfo(DWORD dwLoaclUserID, DWORD dwVideoServer, WORD wVideoPort)
{
	//���ñ���
	m_wVideoPort=wVideoPort;
	m_dwVideoServer=dwVideoServer;
	m_dwLocalUserID=dwLoaclUserID;

	return true;
}

//���ö���
bool CVideoServiceManager::SetVideoServiceControl(WORD wVideoIndex, CVideoServiceControl * pVideoServiceControl)
{
	//��ȡ����
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return false;

	//���ö���
	m_VideoServiceControl[wVideoIndex]=pVideoServiceControl;

	return true;
}

//��ȡ����
CVideoServiceControl *CVideoServiceManager::GetVideoServiceControl(WORD wVideoIndex)
{
	//���ض���
	ASSERT(wVideoIndex<MAX_CHAIR);
	if (wVideoIndex>=MAX_CHAIR) return NULL;
	return m_VideoServiceControl[wVideoIndex];
}

//���ýӿ�
bool CVideoServiceManager::SetMessageProxy(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIMessageProxy=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IStringMessage);
	ASSERT(m_pIMessageProxy!=NULL);
	return (m_pIMessageProxy!=NULL);
}

//��½��Ƶ
void CVideoServiceManager::LoginVideoSystem()
{
	//�����ж�
	if (m_dwVideoRoomID!=0) 
	{
		OnEventGameReset();
		return;
	}

	//�Թ��ж�
	ASSERT(m_pIClientKernel!=NULL);
	if(m_pIClientKernel==NULL) return;
	IClientUserItem *pUserItem=m_pIClientKernel->GetMeUserItem();
	if(pUserItem==NULL) return;
	const tagUserInfo *pUserData=pUserItem->GetUserInfo();
	if (pUserData==NULL || pUserData->cbUserStatus==US_LOOKON) return;

	//������Ƶ
	DWORD dwFuncMode = BRAC_FUNC_VIDEO_CBDATA | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_AUDIO_CBDATA;
	ASSERT(m_hWnd!=NULL);
	BRAC_InitSDK(m_hWnd,dwFuncMode);
	BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,VideoDataCallBack,this);
	BRAC_SetAudioDataCallBack(AudioDataCallBack,this);
	WORD wVideoIndex=GetVideoIndex(pUserData);
	if (wVideoIndex==MAX_CHAIR) return;
	CVideoServiceControl *pVideoServiceControl=GetVideoServiceControl(wVideoIndex);

	//��ַת��
	BYTE *pByte=(BYTE*)&m_dwVideoServer;
	char szServerIPAddr[30] = {0};
	_snprintf(szServerIPAddr,CountArray(szServerIPAddr),"%d.%d.%d.%d",pByte[0],pByte[1],pByte[2],pByte[3]);

	//���ӷ�����
	DWORD dwReturnValue=0;
	dwReturnValue=BRAC_Connect((LPCTSTR)szServerIPAddr,m_wVideoPort);

	CString strLog;
	strLog.Format(TEXT("IP:%s,Port:%d"),CA2CT(szServerIPAddr),m_wVideoPort);
	//�����־
	AppendLogString(strLog);

	if (dwReturnValue==0) strLog=TEXT("������Ƶ������...");
	else strLog.Format(TEXT("���ӷ�����ʧ�ܣ��������δ��%ld"), dwReturnValue);

	//�����־
	AppendLogString(strLog);

}

//������Ƶ
bool CVideoServiceManager::OnEventGameReset()
{
	//�뿪����
	if (m_dwVideoRoomID!=0)
	{
		BRAC_LeaveRoom(m_dwVideoRoomID);
		m_dwVideoRoomID=0;
	}

	//�Թ��ж�
	ASSERT(m_pIClientKernel!=NULL);
	if(m_pIClientKernel==NULL) return true;
	IClientUserItem *pUserItem=m_pIClientKernel->GetMeUserItem();
	if(pUserItem==NULL) return true;
	const tagUserInfo *pUserData=pUserItem->GetUserInfo();
	if (pUserData==NULL || pUserData->cbUserStatus==US_LOOKON) return true;

	//������
	const tagServerAttribute *pServerAttribute=m_pIClientKernel->GetServerAttribute();
	m_dwVideoRoomID=pServerAttribute->wServerID*1000+pUserData->wTableID;

	//���뷿��
	CString strLog;
	DWORD dwReturnValue=BRAC_EnterRoom(m_dwVideoRoomID,NULL,0);

	if (dwReturnValue==0) strLog=TEXT("��½��Ƶ����...");
	else strLog.Format(TEXT("��½��Ƶ����ʧ�ܣ��������δ��%ld"), dwReturnValue);

	//�����־
	AppendLogString(strLog);

	return true;
}


//��ʾ��־
void CVideoServiceManager::AppendLogString(CString strLog)
{
#ifdef _DEBUG
	if (m_pIMessageProxy!=NULL) m_pIMessageProxy->InsertSystemString(strLog);
#endif
}

//��ȡ����
WORD CVideoServiceManager::GetVideoIndex(tagUserInfo const*pagUserData)
{
	ASSERT(pagUserData!=NULL);
	if (pagUserData==NULL) return MAX_CHAIR;
	WORD wChairID=pagUserData->wChairID;
	WORD wVideoIndex=m_pIClientKernel->SwitchViewChairID(wChairID);

	return wVideoIndex;
}

//��ȡ����
WORD CVideoServiceManager::GetVideoIndex(DWORD dwUserID)
{
	ASSERT(dwUserID!=0);
	for (WORD i=0; i<MAX_CHAIR; ++i) 
		if (m_dwUserID[i]==dwUserID)
			return i;

	ASSERT(FALSE);
	return MAX_CHAIR;
}

//�����¼�
LRESULT CVideoServiceManager::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
	AppendLogString(wParam ? TEXT("������Ƶ�������ɹ�..."):TEXT("������Ƶ������ʧ��..."));

	if(wParam)
	{
		//��½ϵͳ
		DWORD dwReturnValue=0;
		CString strLog;
		//�Թ��ж�
		ASSERT(m_pIClientKernel!=NULL);
		if(m_pIClientKernel==NULL) return TRUE;
		IClientUserItem *pUserItem=m_pIClientKernel->GetMeUserItem();
		if(pUserItem==NULL) return TRUE;
		const tagUserInfo *pUserData=pUserItem->GetUserInfo();
		if (pUserData==NULL || pUserData->cbUserStatus==US_LOOKON) return TRUE;

		char szUserID[32], szVideoPassword[33];
		_snprintf(szUserID,CountArray(szUserID),"%ld",pUserData->dwUserID);
		//CWHEncrypt::MD5Encrypt(szUserID,szVideoPassword);
		szVideoPassword[32]=0;//ID��md5ǰ17λ
		dwReturnValue=BRAC_Login((LPCTSTR)szUserID,(LPCTSTR)szVideoPassword,0);

		if (dwReturnValue==0) strLog=TEXT("��½��Ƶ������...");
		else strLog.Format(TEXT("��½��Ƶ������ʧ�ܣ��������δ��%ld"), dwReturnValue); 

		//�����־
		AppendLogString(strLog);
	}

	return TRUE;
}

//��½�¼�
LRESULT CVideoServiceManager::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
	CString strLog;
	if (lParam==0)
	{	
		//�Ϸ��ж�
		ASSERT(m_dwLocalUserID==wParam);
		if (m_dwLocalUserID==wParam) strLog=TEXT("��½��Ƶ�������ɹ�");
		else strLog.Format(TEXT("��Ƶ�����������û���ʶ�ͱ��ر�ʶ��һ�£�����:%ld������:%ld"),wParam,m_dwLocalUserID);	

		//������
		DWORD dwReturnValue=0;
		const tagServerAttribute *pServerAttribute=m_pIClientKernel->GetServerAttribute();
		if(m_pIClientKernel==NULL) return 1;
		IClientUserItem *pUserItem=m_pIClientKernel->GetMeUserItem();
		if(pUserItem==NULL) return 1;
		const tagUserInfo *pUserData=pUserItem->GetUserInfo();
		if (pUserData==NULL || pUserData->cbUserStatus==US_LOOKON) return 1;
//#ifndef _DEBUG
		m_dwVideoRoomID=pServerAttribute->wServerID*1000+pUserData->wTableID;
// #else
// 		m_dwVideoRoomID=pUserData->wTableID;
// #endif

		//���뷿��
		dwReturnValue=BRAC_EnterRoom(m_dwVideoRoomID,NULL,0); 

		if (dwReturnValue==0) strLog=TEXT("��½��Ƶ����...");
		else strLog.Format(TEXT("��½��Ƶ����ʧ�ܣ��������δ��%ld"), dwReturnValue);

		//�����־
		AppendLogString(strLog);
	}
	else
	{
		strLog.Format(TEXT("��¼��Ƶ������ʧ�ܣ��������Ϊ��%d "),lParam);
		m_dwLocalUserID=0;
	}

	//�����־
	AppendLogString(strLog);

	return TRUE;
}

//�����¼�
LRESULT CVideoServiceManager::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
	CString strLog;
	if (lParam==0)
	{
		strLog.Format(TEXT("�ɹ�������Ϊ��%d ����Ƶ����"),wParam);

		//������Ƶ
		CRect rcVideo;
		if(m_pIClientKernel==NULL) return TRUE;
		IClientUserItem *pUserItem=m_pIClientKernel->GetMeUserItem();
		if(pUserItem==NULL) return TRUE;
		const tagUserInfo *pUserData=pUserItem->GetUserInfo();
		if (pUserData==NULL || pUserData->cbUserStatus==US_LOOKON) return TRUE;

		WORD wVideoIndex=GetVideoIndex(pUserData);
		if (wVideoIndex==MAX_CHAIR) return TRUE;
		CVideoServiceControl *pVideoServiceControl=m_VideoServiceControl[wVideoIndex];
		pVideoServiceControl->GetVideoSize(rcVideo);
		BRAC_SetVideoPos(m_dwLocalUserID,pVideoServiceControl->GetSafeHwnd(),rcVideo.left,rcVideo.top,rcVideo.right,rcVideo.bottom);
		BRAC_UserCameraControl(m_dwLocalUserID,TRUE);
		BRAC_UserSpeakControl(m_dwLocalUserID,TRUE);

		//�¼�֪ͨ
		pVideoServiceControl->SetVideoUserInfo(m_dwLocalUserID,pUserData->szNickName);
		pVideoServiceControl->OnEventUserEnter();

		//�����ʶ
		m_dwUserID[wVideoIndex]=m_dwLocalUserID;
	}
	else
	{
		strLog.Format(TEXT("������뷿��ʧ�ܣ��������Ϊ�� %d "),lParam);
	}

	//�����־
	AppendLogString(strLog);

	return TRUE;
}

//�б��¼�
LRESULT CVideoServiceManager::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
{
	//��ȡ����
	DWORD dwUserNum = 0;
	BRAC_GetOnlineUser(NULL,dwUserNum);
	if(!dwUserNum) return TRUE;

	//��ȡ�б�
	DWORD dwUserList[MAX_CHAIR];
	BRAC_GetOnlineUser(dwUserList,dwUserNum);

	for(INT i=0; i< (INT)dwUserNum; i++)
	{
		//��ȡ���
		DWORD dwUserID=dwUserList[i];
		IClientUserItem *pUserItem=m_pIClientKernel->SearchUserByUserID(dwUserID);
		if (pUserItem==NULL)
		{
			//�����־
			CString strLog;
			strLog.Format(TEXT("IDΪ��%ld ������ڽ�����Ϸƽ̨ǰ������Ƶϵͳ����Ƶ��ʾʧ�ܣ�"),dwUserID);
			AppendLogString(strLog);
			continue;
		}
		tagUserInfo *pUserData=pUserItem->GetUserInfo();
		if(pUserData==NULL) continue;

		//������Ƶ
		CRect rcVideo;
		WORD wVideoIndex=GetVideoIndex(pUserData);
		if (wVideoIndex==MAX_CHAIR) return TRUE;
		CVideoServiceControl *pVideoServiceControl=m_VideoServiceControl[wVideoIndex];
		pVideoServiceControl->GetVideoSize(rcVideo);
		BRAC_SetVideoPos(dwUserID,pVideoServiceControl->GetSafeHwnd(),rcVideo.left,rcVideo.top,rcVideo.right,rcVideo.bottom);
		BRAC_UserCameraControl(dwUserID,TRUE);
		BRAC_UserSpeakControl(dwUserID,TRUE);

		//�����ʶ
		m_dwUserID[wVideoIndex]=dwUserID;

		//�¼�֪ͨ
		pVideoServiceControl->SetVideoUserInfo(pUserData->dwUserID,pUserData->szNickName);
		pVideoServiceControl->OnEventUserEnter();
	}

	return TRUE;
}

//�����¼�
LRESULT CVideoServiceManager::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{	
	DWORD dwUserID=(DWORD)wParam;
	BOOL bEnter=(BOOL)lParam;

#ifdef _DEBUG
	CString strLog;
	strLog.Format(TEXT("���Ϊ��%ld ���û� %s ����"),dwUserID, bEnter ? TEXT("����") : TEXT("�뿪"));
	AppendLogString(strLog);
#endif	


	if (bEnter)
	{
		//��ȡ���
		IClientUserItem *pUserItem=m_pIClientKernel->SearchUserByUserID(dwUserID);
		ASSERT(pUserItem!=NULL);
		if (pUserItem==NULL)
		{
			//�����־
			CString strLog;
			strLog.Format(TEXT("IDΪ��%ld ������ڽ�����Ϸƽ̨ǰ������Ƶϵͳ����Ƶ��ʾʧ�ܣ�"),dwUserID);
			AppendLogString(strLog);
			return TRUE;
		}
		tagUserInfo *pUserData=pUserItem->GetUserInfo();
		if(pUserData==NULL) return TRUE;

		//��ȡ�ؼ�
		CRect rcVideo;
		WORD wVideoIndex=GetVideoIndex(pUserData);
		if (wVideoIndex==MAX_CHAIR) return TRUE;
		CVideoServiceControl *pVideoServiceControl=m_VideoServiceControl[wVideoIndex];

		//������Ƶ
		pVideoServiceControl->GetVideoSize(rcVideo);
		BRAC_SetVideoPos(dwUserID,pVideoServiceControl->GetSafeHwnd(),rcVideo.left,rcVideo.top,rcVideo.right,rcVideo.bottom);
		BRAC_UserCameraControl(dwUserID,TRUE);
		BRAC_UserSpeakControl(dwUserID,TRUE);

		//�¼�֪ͨ
		pVideoServiceControl->SetVideoUserInfo(pUserData->dwUserID,pUserData->szNickName);
		pVideoServiceControl->OnEventUserEnter();

		//�����ʶ
		m_dwUserID[wVideoIndex]=dwUserID;
	}
	else
	{
		//��ȡ����
		WORD wVideoIndex=GetVideoIndex(dwUserID);
		if (wVideoIndex==MAX_CHAIR) return TRUE;
		CVideoServiceControl *pVideoServiceControl=m_VideoServiceControl[wVideoIndex];
		ASSERT(pVideoServiceControl!=NULL);
		if (pVideoServiceControl==NULL) return TRUE;

		//�¼�֪ͨ
		m_dwUserID[wVideoIndex]=0;
		pVideoServiceControl->OnEventUserLeave();
		pVideoServiceControl->OnEventReset();
	}

	return TRUE;
}

//�����¼�
LRESULT CVideoServiceManager::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
	//�����־
	AppendLogString(TEXT("������Ƶ�������Ͽ����ӣ���ʱ������Ƶ"));

	//��ȡ���
	if(m_pIClientKernel==NULL) return TRUE;
	IClientUserItem *pUserItem=m_pIClientKernel->GetMeUserItem();
	if(pUserItem==NULL) return TRUE;
	const tagUserInfo *pUserData=pUserItem->GetUserInfo();
	if (pUserData==NULL || pUserData->cbUserStatus==US_LOOKON) return TRUE;

	WORD wVideoIndex=GetVideoIndex(pUserData);
	if (wVideoIndex==MAX_CHAIR) return TRUE;
	CVideoServiceControl *pVideoServiceControl=m_VideoServiceControl[wVideoIndex];

	//�¼�֪ͨ
	pVideoServiceControl->OnEventUserLeave();

	return TRUE;
}

//����ͷ�¼�
LRESULT CVideoServiceManager::OnGVClientCameraState(WPARAM wParam, LPARAM lParam)
{
	//��ұ�ʶ
	DWORD dwUserID=(DWORD)wParam;

	//��ȡ����
	WORD wVideoIndex=GetVideoIndex(dwUserID);
	if (wVideoIndex==MAX_CHAIR) return TRUE;
	CVideoServiceControl *pVideoServiceControl=GetVideoServiceControl(wVideoIndex);
	ASSERT(pVideoServiceControl!=NULL);
	if (pVideoServiceControl==NULL) return TRUE;

	//�¼�֪ͨ
	pVideoServiceControl->OnEventCameraState(BYTE(lParam));

	return TRUE;
}

//������Դ
void CVideoServiceManager::SetSkinResource(HINSTANCE hResInstance/*,tagVideoFrameImage *pVideoFrameImage,tagPropertyMenuImage *pPropertyMenuImage*/)
{
	//��Դ����
	m_hResInstance=hResInstance;
//	CopyMemory(&m_VideoFrameImage,pVideoFrameImage,sizeof(m_VideoFrameImage));
//	CopyMemory(&m_PropertyMenuImage,pPropertyMenuImage,sizeof(m_PropertyMenuImage));

	return ;
}

//�ǳ�ϵͳ
void CVideoServiceManager::LogoutVideoSystem()
{
	//�뿪����
	if (m_dwVideoRoomID!=0)
	{
		BRAC_LeaveRoom(m_dwVideoRoomID);
		m_dwVideoRoomID=0;
	}

	//ע��ϵͳ
	BRAC_Logout();

	g_bClientClosed=true;
}
//////////////////////////////////////////////////////////////////////////
