#include "Stdafx.h"
#include "DlgLogon.h"
#include "GamePlaza.h"
#include "MissionLogon.h"
#include ".\dlglogon.h"

//////////////////////////////////////////////////////////////////////////////////

//Բ�Ǵ�С
#define ROUND_CX					7									//Բ�ǿ��
#define ROUND_CY					7									//Բ�Ǹ߶�

//��Ļλ��
#define LAYERED_SIZE				5									//�ֲ��С
#define CAPTION_SIZE				35									//�����С

//��ť��Ŀ
#define BUTTON_COUNT_CX				5									//������Ŀ
#define BUTTON_COUNT_CY				4									//������Ŀ
#define BUTTON_ITEM_UNDER			0									//��ť�ײ�
#define BUTTON_ITEM_START			12									//��ť��ʼ
#define BUTTON_ITEM_SPACE			16									//��ť���

//�ؼ���ʶ
#define IDC_WEB_PUBLICIZE			300									//����ؼ�
#define IDC_WND_LOGON_BUTTON		301									//��ť�ؼ�

//��ť��ʶ
#define INDEX_REGISTER				0									//ע�ᰴť
#define INDEX_USER_HELP				1									//���ְ���
#define INDEX_BUY_SCORE				2									//������ֵ
#define INDEX_HOME_PAGE				3									//�ٷ���ҳ

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)

	//ϵͳ��Ϣ
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//��ť��Ϣ
	ON_BN_CLICKED(IDC_REGISTER, OnBnClickedRegister)
	ON_CBN_EDITCHANGE(IDC_ACCOUNTS, OnCbnEditchangeAccounts)

	ON_EN_CHANGE(IDC_ACCOUNTS, OnEnChangeAccounts)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWndLogonButton, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CWndLogonButton::CWndLogonButton()
{
	//���Ϣ
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//������Ϣ
	m_SizeButton.SetSize(0,0);

	//������Դ
	CPngImage ImageButton;
	ImageButton.LoadImage(AfxGetInstanceHandle(),TEXT("WND_LOGON_BUTTON"));
	m_SizeButton.SetSize(ImageButton.GetWidth()/BUTTON_COUNT_CX,ImageButton.GetHeight()/BUTTON_COUNT_CY);

	return;
}

//��������
CWndLogonButton::~CWndLogonButton()
{
}

//�����л�
WORD CWndLogonButton::SwitchToButtonIndex(CPoint MousePoint)
{
	//����λ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//�߽��ж�
	if (MousePoint.x<BUTTON_ITEM_START) return INVALID_WORD;
	if (MousePoint.y>(rcClient.Height()-BUTTON_ITEM_UNDER)) return INVALID_WORD;
	if (MousePoint.y<(rcClient.Height()-m_SizeButton.cy-BUTTON_ITEM_UNDER)) return INVALID_WORD;
	if (MousePoint.x>BUTTON_ITEM_START+(m_SizeButton.cx+BUTTON_ITEM_SPACE)*BUTTON_COUNT_CY) return INVALID_WORD;

	//��������
	for (WORD i=0;i<BUTTON_COUNT_CY;i++)
	{
		//λ�ü���
		CRect rcButton;
		rcButton.bottom=rcClient.Height()-BUTTON_ITEM_UNDER;
		rcButton.top=rcClient.Height()-m_SizeButton.cy-BUTTON_ITEM_UNDER;
		rcButton.left=BUTTON_ITEM_START+(m_SizeButton.cx+BUTTON_ITEM_SPACE)*i;
		rcButton.right=BUTTON_ITEM_START+(m_SizeButton.cx+BUTTON_ITEM_SPACE)*i+m_SizeButton.cx;

		//�����ж�
		if (rcButton.PtInRect(MousePoint)) return i;
	}

	return INVALID_WORD;
}

//�ػ���Ϣ
VOID CWndLogonButton::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//�����豸
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//������Դ
	//CPngImage ImageLine;
	CPngImage ImageButton;
	CBitImage ImageWndBack;
	//ImageLine.LoadImage(AfxGetInstanceHandle(),TEXT("WND_LOGON_LINE"));
	ImageButton.LoadImage(AfxGetInstanceHandle(),TEXT("WND_LOGON_BUTTON"));
	ImageWndBack.LoadFromResource(AfxGetInstanceHandle(),IDB_WND_LOGON_BACK);

	//�滭����
	pBufferDC->FillSolidRect(&rcClient,RGB(255,255,255));
	ImageWndBack.BitBlt(BufferDC,(rcClient.Width()-ImageWndBack.GetWidth())/2,(rcClient.Height()-ImageWndBack.GetHeight())/2);

	//�滭����
	//ImageLine.DrawImage(pBufferDC,(rcClient.Width()-ImageLine.GetWidth())/2,rcClient.Height()-ImageLine.GetHeight());

	//�滭��ť
	for (INT i=0;i<BUTTON_COUNT_CY;i++)
	{
		//��������
		INT nXButtomPos=0;
		INT nYButtomPos=i*m_SizeButton.cy;

		//���м���
		if ((m_wItemHover==i)&&(m_wItemDown!=i)) nXButtomPos=m_SizeButton.cx*2;
		if ((m_wItemActive==i)||(m_wItemDown==i)) nXButtomPos=m_SizeButton.cx;

		//�滭��ť
		INT nYDrawPos=(rcClient.Height()-m_SizeButton.cy)/2;
		INT nXDrawPos=(m_SizeButton.cx+BUTTON_ITEM_SPACE)*i+BUTTON_ITEM_START;
		ImageButton.DrawImage(pBufferDC,nXDrawPos,nYDrawPos,m_SizeButton.cx,m_SizeButton.cy,nXButtomPos,nYButtomPos);
	}

	//�滭����
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return;
}

//������Ϣ
INT CWndLogonButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//���ñ���
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//������С
	CBitImage ImageWndBack;
	ImageWndBack.LoadFromResource(AfxGetInstanceHandle(),IDB_WND_LOGON_BACK);
	SetWindowPos(NULL,0,0,ImageWndBack.GetWidth(),ImageWndBack.GetHeight(),SWP_NOZORDER|SWP_NOMOVE);

	return 0;
}

//�����Ϣ
VOID CWndLogonButton::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//����λ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//λ�ü���
	WORD wCollocateHover=SwitchToButtonIndex(Point);

	//��������
	if (wCollocateHover!=m_wItemHover)
	{
		//���ñ���
		m_wItemHover=wCollocateHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//�����ж�
	if (m_bHovering==false)
	{
		//���ñ���
		m_bHovering=true;

		//��������
		TRACKMOUSEEVENT TrackMouseEvent;
		ZeroMemory(&TrackMouseEvent,sizeof(TrackMouseEvent));

		//ע����Ϣ
		TrackMouseEvent.hwndTrack=m_hWnd;
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);

		//ע���¼�
		_TrackMouseEvent(&TrackMouseEvent);
	}

	return;
}

//�����Ϣ
VOID CWndLogonButton::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//��������
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover==m_wItemDown))
	{
		switch (m_wItemHover)
		{
		case INDEX_REGISTER:	//ע�ᰴť
			{
				//��ȡ����
				CWnd * pParentWnd=GetParent();
				pParentWnd->PostMessage(WM_COMMAND,IDC_REGISTER,0);

				break;
			}
		case INDEX_USER_HELP:	//��������
			{
				//�����ַ
				TCHAR szBrowseUrl[256]=TEXT("");
				_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/LogonLink1.aspx"),szPlatformLink);

				//��ҳ��
				ShellExecute(NULL,TEXT("OPEN"),szBrowseUrl,NULL,NULL,SW_NORMAL);

				break;
			}
		case INDEX_BUY_SCORE:	//������ֵ
			{
				//�����ַ
				TCHAR szBrowseUrl[256]=TEXT("");
				_sntprintf(szBrowseUrl,CountArray(szBrowseUrl),TEXT("%s/LogonLink2.aspx"),szPlatformLink);

				//��ҳ��
				ShellExecute(NULL,TEXT("OPEN"),szBrowseUrl,NULL,NULL,SW_NORMAL);

				break;
			}
		case INDEX_HOME_PAGE:	//�������
			{
				//��ҳ��
				ShellExecute(NULL,TEXT("OPEN"),szPlatformLink,NULL,NULL,SW_NORMAL);

				break;
			}
		}
	}

	//������
	if (m_wItemDown!=INVALID_WORD)
	{
		//�ͷ����
		ReleaseCapture();

		//���ñ���
		m_wItemDown=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
VOID CWndLogonButton::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//���ý���
	SetFocus();

	//���´���
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover!=m_wItemActive))
	{
		//����˻�
		SetCapture();

		//���ñ���
		m_wItemDown=m_wItemHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
LRESULT CWndLogonButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	if (m_bHovering==true)
	{
		//���ñ���
		m_bHovering=false;
		m_wItemHover=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return 0;
}

//�����Ϣ
BOOL CWndLogonButton::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//���ù��
	if (m_wItemHover!=INVALID_WORD)
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CControlCheckButton::CControlCheckButton()
{
	//���ñ���
	m_cbChecked=FALSE;
	m_pParentSink=NULL;

	//������Դ
	m_ImageBtnBack.LoadFromResource(AfxGetResourceHandle(),IDB_CHECK_BUTTON_BACK);
}

//��������
CControlCheckButton::~CControlCheckButton()
{
}

//�ؼ�����
CRect CControlCheckButton::GetControlRect()
{
	CRect rcClient(m_ptControlBenchmark.x,m_ptControlBenchmark.y,m_ptControlBenchmark.x+m_ImageBtnBack.GetWidth()/2,m_ptControlBenchmark.y+m_ImageBtnBack.GetHeight());

	return rcClient;
}

//����״̬
VOID  CControlCheckButton::SetButtonChecked(BYTE cbChecked) 
{ 
	//���ñ���
	m_cbChecked=cbChecked;

	//�������
	CRect rcClient = GetControlRect();

	//�ػ����
	if(m_pParentSink!=NULL) m_pParentSink->InvalidateRect(&rcClient);
};

//���ƿؼ�
VOID  CControlCheckButton::OnDrawControl(CDC * pDC)
{
	//����У��
	if(pDC==NULL) return;

	//�������
	INT nImageWidth = m_ImageBtnBack.GetWidth()/2;
	INT nImageHeight = m_ImageBtnBack.GetHeight();
    
    //���Ʊ���
	m_ImageBtnBack.BitBlt(*pDC,m_ptControlBenchmark.x,m_ptControlBenchmark.y,nImageWidth,nImageHeight,m_cbChecked==TRUE?nImageWidth:0,0);
}

//����¼�
VOID  CControlCheckButton::OnClickControl(CPoint Point)
{
	//�������
	CRect rcClient = GetControlRect();

	//ѡ���ж�
	if(rcClient.PtInRect(Point))
	{
		//���ñ���
		m_cbChecked=m_cbChecked==FALSE?TRUE:FALSE;

		//�ػ����
		if(m_pParentSink!=NULL)	m_pParentSink->InvalidateRect(&rcClient);
	}
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgLogon::CDlgLogon() : CDialog(IDD_DLG_LOGON)
{
	//��¼��Ϣ
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLogonServer[0]=0;

	//������ˢ
	m_brBrush.CreateSolidBrush(RGB(215,223,228));

	return;
}

//��������
CDlgLogon::~CDlgLogon()
{
	//������Դ
	if (m_brBrush.GetSafeHandle()!=NULL)
	{
		m_brBrush.DeleteObject();
	}

	return;
}

//�ؼ���
VOID CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�󶨿ؼ�
	DDX_Control(pDX, IDOK, m_btEnter);
	DDX_Control(pDX, IDCANCEL, m_btQuit);

	//�󶨿ؼ�
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
	DDX_Control(pDX, IDC_LOGON_SERVER, m_ServerControl);
}

//��������
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("�û���¼ -- Version 6603"));
	
	//������Դ
	CPngImage ImageBack;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));

	//���ô�С
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	//�߿�����
	m_ServerControl.SetDrawBorad(false);
	m_PasswordControl.SetDrawBorad(false);
	m_PasswordControl.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edAccounts.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btQuit.SetButtonImage(IDB_BT_LOGON_QUIT,hInstance,false,false);
	m_btEnter.SetButtonImage(IDB_BT_LOGON,TEXT("BT_LOGON_ENTER"),hInstance,false,false);

	//�����ؼ�
	CRect rcCreate(0,0,0,0);
	m_PlatformPublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE);

	//�����ؼ�
	CRect rcWndButton(20,273,411,305);
	m_WndLogonButton.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcWndButton,this,IDC_WND_LOGON_BUTTON);

	//��������
	CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
	ASSERT(pGlobalUnits!=NULL);

	//��ס����
	m_RemPwdControl.SetControlBenchmark(107,246);
	m_RemPwdControl.SetParentWndSink(this);

	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//�����ַ
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s\\Web\\LobbyTopNotice.htm"),szDirectory);

	//���ù��
	if(pGlobalUnits!=NULL && pGlobalUnits->LocalFileExist(szBillUrl))
	{
		m_PlatformPublicize.Navigate(szBillUrl);
		m_PlatformPublicize.SetWindowPos(NULL,36,9,SizeWindow.cx-71,18,SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);
	}
	else
		m_PlatformPublicize.SetWindowPos(NULL,36,9,SizeWindow.cx-71,18,SWP_HIDEWINDOW|SWP_NOZORDER|SWP_NOCOPYBITS|SWP_NOACTIVATE);


	//������Ϣ
	LoadAccountsInfo();
	LoadLogonServerInfo();

	//���д���
	CenterWindow(this);

	//��ȡ����
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//����λ��
	CRect rcUnLayered;
	rcUnLayered.top=LAYERED_SIZE;
	rcUnLayered.left=LAYERED_SIZE;
	rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;

	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);

	//��������
	SetWindowRgn(RgnWindow,FALSE);

	//�ֲ㴰��
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(ROUND_CX,ROUND_CY),false);

	return FALSE;
}

//��Ϣ����
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//ȷ������
VOID CDlgLogon::OnOK()
{
	//��ȡ��Ϣ
	if (GetInformation()==false) return;

	//��������
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//���ش���
	ShowWindow(SW_HIDE);

	//ִ�е�¼
	CMissionLogon * pMissionLogon=CMissionLogon::GetInstance();
	if (pMissionLogon!=NULL) pMissionLogon->PerformLogonMission(m_RemPwdControl.GetButtonChecked()==TRUE);

	return;
}

//ȡ����Ϣ
VOID CDlgLogon::OnCancel()
{
	//�رմ���
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);

	return;
}

//��������
WORD CDlgLogon::ConstructLogonPacket(BYTE cbBuffer[], WORD wBufferSize)
{
	//��������
	CMD_GP_LogonAccounts * pLogonAccounts=(CMD_GP_LogonAccounts *)cbBuffer;

	//������Ϣ
	CWHService::GetMachineIDEx(pLogonAccounts->szMachineID);
	CWHEncrypt::MD5Encrypt(m_szPassword,pLogonAccounts->szPassword);

	//��¼��Ϣ
	pLogonAccounts->dwPlazaVersion=VERSION_PLAZA;
	lstrcpyn(pLogonAccounts->szAccounts,m_szAccounts,CountArray(pLogonAccounts->szAccounts));

	//��������
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	lstrcpyn(pGlobalUserData->szPassword,pLogonAccounts->szPassword,CountArray(pGlobalUserData->szPassword));

	return sizeof(CMD_GP_LogonAccounts);
}

//�����˺�
VOID CDlgLogon::LoadAccountsInfo()
{
	//��ȡ��Ϣ
	CWHRegKey RegUserInfo;
	if (RegUserInfo.OpenRegKey(REG_USER_INFO,false)==false) return;

	//��������
	DWORD dwLastUserID=RegUserInfo.GetValue(TEXT("LastUserID"),0L);

	//��ȡ��Ϣ
	if (dwLastUserID!=0L)
	{
		//��ȡ����
		TCHAR szKeyItemName[16]=TEXT("");
		_sntprintf(szKeyItemName,CountArray(szKeyItemName),TEXT("%s\\%ld"),REG_USER_INFO,dwLastUserID);

		//���Ӽ�
		CWHRegKey RegUserItem;
		if (RegUserItem.OpenRegKey(szKeyItemName,false)==true)
		{
			//�ʻ���Ϣ
			TCHAR szAccounts[LEN_ACCOUNTS]=TEXT("");
			RegUserItem.GetString(TEXT("UserAccount"),szAccounts,CountArray(szAccounts));

			//��ȡ����
			TCHAR szPasswordDes[LEN_PASSWORD]=TEXT("");
			TCHAR szPasswordSrc[MAX_ENCRYPT_LEN]=TEXT("");
			RegUserItem.GetString(TEXT("UserPassword"),szPasswordSrc,CountArray(szPasswordSrc));

			//�⿪����
			if (szPasswordSrc[0]!=0)
			{
				CWHEncrypt::XorCrevasse(szPasswordSrc,szPasswordDes,CountArray(szPasswordDes));
			}

			//���ÿؼ�
			m_edAccounts.SetWindowText(szAccounts);
			m_PasswordControl.SetUserPassword(szPasswordDes);

			//��ס����
			if (szPasswordDes[0]!=0)
			{
				m_RemPwdControl.SetButtonChecked(TRUE);
			}
		}
	}

	return;
}

//��ַ��Ϣ
VOID CDlgLogon::LoadLogonServerInfo()
{
	//��ȡ��Ŀ
	CGlobalServer GlobalServer;
	WORD wItemCount=GlobalServer.GetItemCount();
	INT nIndex=0;

	//�ϴε�¼
	TCHAR szLastServer[LEN_SERVER]=TEXT("");
	GlobalServer.GetLastServerName(szLastServer);

	//��ȡ��Ϣ
	for (WORD i=0;i<wItemCount;i++)
	{
		//��ȡ��Ϣ
		TCHAR szServerItem[LEN_SERVER]=TEXT("");
		GlobalServer.GetServerItemName(i,szServerItem);

		//������Ϣ
		if (szServerItem[0]!=0)
		{
			//������Ϣ
			INT nItem=m_ServerControl.AddString(szServerItem);

			//�����¼
			if ((szLastServer[0]!=0)&&(lstrcmp(szLastServer,szServerItem)==0))
			{
				szLastServer[0]=0;
				m_ServerControl.SetCurSel(nItem);
			}
		}
	}

	//�����¼
	if (szLastServer[0]!=0)
	{
		m_ServerControl.SetCurSel(m_ServerControl.AddString(szLastServer));
	}

	//����ѡ��
	if (m_ServerControl.GetCurSel()==LB_ERR)
	{
		if (m_ServerControl.GetCount()==0L)
		{
			m_ServerControl.SetCurSel(m_ServerControl.AddString(szLogonServer));
		}
		else
		{
			m_ServerControl.SetCurSel(0);
		}
	}

	return;
}

//��ȡ��Ϣ
bool CDlgLogon::GetInformation()
{
	//��ȡ����
	m_PasswordControl.GetUserPassword(m_szPassword);

	//��ȡ��Ϣ
	GetDlgItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	GetDlgItemText(IDC_LOGON_SERVER,m_szLogonServer,CountArray(m_szLogonServer));

	//��ַ�ж�
	if (m_szLogonServer[0]==0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("��ѡ�񡰵�¼�����������ٵ�¼��������������������ָ�ϡ���ȡ������"),MB_ICONERROR,0);

		//��ʾ����
		ShowWindow(SW_SHOW);

		//���ý���
		m_ServerControl.SetFocus();

		return false;
	}

	//�ʺ��ж�
	if (m_szAccounts[0]==0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���������ʺź��ٵ�¼��������������������ָ�ϡ���ȡ������"),MB_ICONERROR,0);

		//��ʾ����
		ShowWindow(SW_SHOW);

		//���ý���
		m_edAccounts.SetFocus();

		return false;
	}

	//�����ж�
	if (m_szPassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("��������������ٵ�¼��������������������ָ�ϡ���ȡ������"),MB_ICONERROR,0);

		//��ʾ����
		ShowWindow(SW_SHOW);

		//���ý���
		m_PasswordControl.SetFocus();

		return false;
	}

	return true;
}

//ע���ʺ�
VOID CDlgLogon::OnBnClickedRegister()
{
	//���ش���
	ShowWindow(SW_HIDE);

	//��ȡ��ַ
	CString strLogonServer;
	GetDlgItemText(IDC_LOGON_SERVER,strLogonServer);

	//�����ַ
	strLogonServer.TrimLeft();
	strLogonServer.TrimRight();
	lstrcpyn(m_szLogonServer,(strLogonServer.IsEmpty()==true)?szLogonServer:strLogonServer,CountArray(m_szLogonServer));

	//��ʾע��
	ASSERT(CMissionLogon::GetInstance()!=NULL);
	if (CMissionLogon::GetInstance()!=NULL) CMissionLogon::GetInstance()->ShowRegister();

	return;
}

//�༭�ı�
VOID CDlgLogon::OnCbnEditchangeAccounts()
{
	//��ȫ����
	((CButton *)GetDlgItem(IDC_REM_PASSWORD))->SetCheck(BST_UNCHECKED);

	//��������
	if (m_PasswordControl.IsFalsityPassword()==true) m_PasswordControl.SetUserPassword(NULL);

	return;
}

//�滭����
BOOL CDlgLogon::OnEraseBkgnd(CDC * pDC)
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
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//������Դ
	CPngImage ImageBack;
	CBitImage ImageNotice;
	ImageBack.LoadImage(AfxGetInstanceHandle(),TEXT("DLG_LOGON_BACK"));
	ImageNotice.LoadFromResource(AfxGetInstanceHandle(),IDB_LOGON_NOTICE);

	//�滭����
	ImageBack.DrawImage(pBufferDC,0,0);
	ImageNotice.BitBlt(*pBufferDC,10,35,410,100,0,0,SRCCOPY);

	//���ƿؼ�
	m_RemPwdControl.OnDrawControl(pBufferDC);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//��ʾ��Ϣ
VOID CDlgLogon::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//��ʾ�ֲ�
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//�����Ϣ
VOID CDlgLogon::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�����
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//λ�øı�
VOID CDlgLogon::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//�ƶ��ֲ�
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//�ؼ���ɫ
HBRUSH CDlgLogon::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(10,10,10));
			return m_brBrush;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//�ؼ��ı�
void CDlgLogon::OnEnChangeAccounts()
{
	//�������
	if(m_PasswordControl.m_hWnd!=NULL && m_PasswordControl.IsFalsityPassword()==true)
	{
		//��������
		m_PasswordControl.SetUserPassword(TEXT(""));

        //��ȫ����
		m_RemPwdControl.SetButtonChecked(FALSE);
	}
}

//��굯��
void CDlgLogon::OnLButtonUp(UINT nFlags, CPoint point)
{
	//ѡ���¼�
	m_RemPwdControl.OnClickControl(point);

	CDialog::OnLButtonUp(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////////////



