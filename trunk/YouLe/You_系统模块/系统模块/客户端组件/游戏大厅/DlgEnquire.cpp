#include "Stdafx.h"
#include "DlgEnquire.h"
#include "GlobalUnits.h"


//////////////////////////////////////////////////////////////////////////////////

//Բ�Ǵ�С
#define ROUND_CX					5									//Բ�ǿ��
#define ROUND_CY					5									//Բ�Ǹ߶�

//��Ļλ��
#define LAYERED_SIZE				15									//�ֲ��С


//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgEnquire, CDialog)

	//ϵͳ��Ϣ
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//��ť��Ϣ
	ON_BN_CLICKED(WM_BT_CLOSE,OnCancel)
	ON_BN_CLICKED(WM_BT_QUITE,OnCancel)
	ON_BN_CLICKED(WM_BT_CLOSE_PLAZA, OnBnClickedClosePlaza)
	ON_BN_CLICKED(WM_BT_SWITCH_ACCOUNTS, OnBnClickedSwitchAccounts)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgEnquire::CDlgEnquire() : CDialog(IDD_DLG_ENQUIRE)
{
}

//��������
CDlgEnquire::~CDlgEnquire()
{
}

//�ؼ���
VOID CDlgEnquire::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}

//���ú���
BOOL CDlgEnquire::OnInitDialog()
{
	__super::OnInitDialog();
	//������Դ
	tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
	HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	m_ImageBack.LoadImage(hInstance, PlazaViewImage.pszEnquireBack);
	//���ô�С
	CSize SizeWindow(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	m_btCancel.CreateButton(this, PlazaViewImage.pszEnquireCancel, _T("PNG"),m_ImageBack.GetWidth()-50,15,WM_BT_CLOSE,4, hInstance);
	m_btClosePlaza.CreateButton(this, PlazaViewImage.pszEnquirePlaza, _T("PNG"),
		m_ImageBack.GetWidth()-160,m_ImageBack.GetHeight()-70,WM_BT_CLOSE_PLAZA, 4, hInstance);
	m_btSwitchAccounts.CreateButton(this, PlazaViewImage.pszEnquireSwitch, _T("PNG"),
		30,m_ImageBack.GetHeight()-70,WM_BT_SWITCH_ACCOUNTS,4, hInstance);
	//m_btQuite.CreateButton(this,TEXT("BT_ENQUIRE_QUITE"),_T("PNG"),
	//	m_ImageBack.GetWidth()-50,m_ImageBack.GetHeight()-100,WM_BT_QUITE,4);
	//���д���
	CenterWindow(this);
	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);
	SetWindowRgn(RgnWindow,FALSE);

	return FALSE;
}

//ȷ������
VOID CDlgEnquire::OnOK()
{
	return;
}

//�滭����
BOOL CDlgEnquire::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevDC(pDC,rcClient);
	//�滭����
	m_ImageBack.DrawImage(pDevDC,0,0);

	m_btCancel.SetBkGnd(pDevDC);
	m_btClosePlaza.SetBkGnd(pDevDC);
	m_btSwitchAccounts.SetBkGnd(pDevDC);
	//m_btQuite.SetBkGnd(pDevDC);
	return TRUE;
}

//��ʾ��Ϣ
VOID CDlgEnquire::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	return;
}

//�����Ϣ
VOID CDlgEnquire::OnLButtonDown(UINT nFlags, CPoint Point)
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
VOID CDlgEnquire::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	return;
}

//�رմ���
VOID CDlgEnquire::OnBnClickedClosePlaza()
{
	EndDialog(WM_BT_CLOSE_PLAZA);

	return;
}

//�رշ���
VOID CDlgEnquire::OnBnClickedCloseServer()
{
	//EndDialog(IDC_CLOSE_SERVER);

	return;
}

//�л��ʺ�
VOID CDlgEnquire::OnBnClickedSwitchAccounts()
{
	EndDialog(WM_BT_SWITCH_ACCOUNTS);

	return;
}

//////////////////////////////////////////////////////////////////////////////////
