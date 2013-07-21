#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "Platform.h"

//���ư�ť
#define IDC_MIN						100									//��С��ť
#define IDC_CLOSE					101									//�رհ�ť

//Բ�Ǵ�С
#define ROUND_CX					7									//Բ�ǿ��
#define ROUND_CY					7									//Բ�Ǹ߶�

//��Ӱ����
#define SHADOW_CX					0									//��Ӱ���
#define SHADOW_CY					0									//��Ӱ�߶�

IMPLEMENT_DYNCREATE(CPlatformFrame, CFrameWnd)

CPlatformFrame::CPlatformFrame()
{
}

CPlatformFrame::~CPlatformFrame()
{
}


BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


int CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);

// 	m_pGamePlazaDlg = new CGamePlazaDlg();
// 	m_pGamePlazaDlg->Create(IDD_GAMEPLAZA_DIALOG, this);
// 	m_pGamePlazaDlg->ShowWindow(SW_SHOW);

	//������ť
	m_btMin.CreateButton(this, "BT_FRAME_MIN", _T("PNG"), 0, 3, IDC_MIN, 5);
	m_btClose.CreateButton(this, "BT_FRAME_CLOSE", _T("PNG"), LESS_SCREEN_CX-38, 3, IDC_CLOSE, 5);

	SetFrameSize(LESS_SCREEN_CX, LESS_SCREEN_CY);
	
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(), rcClient.Height());

	//��ʾ����
	ShowWindow(SW_SHOW);
	SetForegroundWindow();

	m_pTest.Create(1, 300, 300, this, NULL, TEXT("GAMEITEM_BACK"), TEXT("GAMEITEM_BILL"));
	m_pRoom.Create(2, 605, 300, this, NULL, TEXT("GAMEITEM_BACK"), TEXT("GAMEROOM_BILL"));

	return 0;
}

void CPlatformFrame::SetFrameSize(int nWidth, int nHeight)
{
	SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER);
	CenterWindow();
}

BOOL CPlatformFrame::RectifyResource(int nWidth, int nHeight)
{
	//�����ж�
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//���λ��
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX, SHADOW_CY, nWidth-SHADOW_CX,nHeight-SHADOW_CY);

		//��������
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//��������
		SetWindowRgn(RegionWindow,TRUE);
	}

	return TRUE;
}

BOOL CPlatformFrame::OnEraseBkgnd(CDC* pDC)
{
	CPngImage imageHead;
	imageHead.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_HEAD"));

	CPngImage imageBack;
	imageBack.LoadImage(AfxGetInstanceHandle(),TEXT("BACKGROUND_PLAZA"));

	CMemDC pDevC(pDC);
	imageHead.DrawImage(pDevC, 0, 0);
	imageBack.DrawImage(pDevC,0,147);

	return TRUE;
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

BOOL CPlatformFrame::OnCommand( WPARAM wParam, LPARAM lParam )
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
	case IDC_CLOSE:				//�رհ�ť
		{
			PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	}

	return FALSE;

}

VOID CPlatformFrame::OnClose()
{
	__super::OnClose();
}
