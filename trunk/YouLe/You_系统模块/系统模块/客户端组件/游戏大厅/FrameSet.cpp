// FrameSet.cpp : 实现文件
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



// CFrameSet 对话框

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


// CFrameSet 消息处理程序

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
	//调整判断
	if ((rcClient.Width()!=0)&&(rcClient.Height()!=0))
	{
		//框架位置
		CRect rcFrame;
		rcFrame.SetRect(0, 0, rcClient.Width(), rcClient.Height());

		//窗口区域
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//设置区域
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

//鼠标消息
VOID CFrameSet::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟按标题
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

BOOL CFrameSet::OnCommand( WPARAM wParam, LPARAM lParam )
{
	//变量定义
	UINT nCommandID=LOWORD(wParam);
	switch (nCommandID)
	{
	case IDC_BT_CLOSE:					//关闭按钮
		{
			OnCancel();
			return TRUE;
		}
	}
	return FALSE;

}
