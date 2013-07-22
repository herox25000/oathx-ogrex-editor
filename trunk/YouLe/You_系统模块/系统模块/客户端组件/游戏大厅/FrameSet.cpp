// FrameSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "FrameSet.h"
#include "Platform.h"


#define FRAMEDLG_X							359
#define FRAMEDLG_Y							240

#define IDC_BT_CLOSE						100
#define IDC_BT_CONFIRN						101
#define IDC_BT_CANCEL						102



// CFrameSet �Ի���

IMPLEMENT_DYNAMIC(CFrameSet, CDialog)
CFrameSet::CFrameSet(CWnd* pParent /*=NULL*/)
	: CDialog(CFrameSet::IDD, pParent)
{
}

CFrameSet::~CFrameSet()
{
}

void CFrameSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFrameSet, CDialog)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CFrameSet ��Ϣ�������

int CFrameSet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowPos(NULL, 0, 0, FRAMEDLG_X, FRAMEDLG_Y, SWP_NOZORDER);
	CenterWindow();

	m_ImageBack.LoadImage(AfxGetInstanceHandle(), TEXT("PNG_FRAME_SET"));

	m_btClose.CreateButton(this, "PNG_BT_FRAME_CLOSE", _T("PNG"), FRAMEDLG_X - 42, 3, IDC_BT_CLOSE, 4);

	CRect rcClient;
	GetClientRect(&rcClient);
	//�����ж�
	if ((rcClient.Width()!=0)&&(rcClient.Height()!=0))
	{
		//���λ��
		CRect rcFrame;
		rcFrame.SetRect(0, 0, rcClient.Width(), rcClient.Height());

		//��������
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//��������
		SetWindowRgn(RegionWindow,TRUE);
	}


	return 0;
}

BOOL CFrameSet::OnEraseBkgnd(CDC* pDC)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	m_ImageBack.DrawImage(pDevC, 0, 0);

	m_btClose.SetBkGnd(pDevC);

	return TRUE;
}

//�����Ϣ
VOID CFrameSet::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�ⰴ����
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

BOOL CFrameSet::OnCommand( WPARAM wParam, LPARAM lParam )
{
	//��������
	UINT nCommandID=LOWORD(wParam);
	switch (nCommandID)
	{
	case IDC_BT_CLOSE:					//�رհ�ť
		{
			OnCancel();
			return TRUE;
		}
	}
	return FALSE;

}
