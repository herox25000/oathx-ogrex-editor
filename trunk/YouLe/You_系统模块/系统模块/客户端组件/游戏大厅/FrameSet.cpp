// FrameSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "FrameSet.h"
#include "Platform.h"
#include ".\frameset.h"


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
	ON_WM_LBUTTONUP()
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CFrameSet ��Ϣ�������

int CFrameSet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowPos(NULL, 0, 0, FRAMEDLG_X, FRAMEDLG_Y, SWP_NOZORDER);
	CenterWindow();
if(m_ImageBack.IsNull())
	m_ImageBack.LoadImage(AfxGetInstanceHandle(), TEXT("PNG_FRAME_SET"));

	m_btClose.CreateButton(this, "PNG_BT_FRAME_CLOSE", _T("PNG"), FRAMEDLG_X - 42, 3, IDC_BT_CLOSE, 4);
	m_btConfirn.CreateButton(this, "PNG_BT_CONFIRN", _T("PNG"), FRAMEDLG_X / 2 - 100, 210, IDC_BT_CONFIRN, 4);
	m_btCancel.CreateButton(this, "PNG_BT_CANCEL", _T("PNG"), FRAMEDLG_X / 2 + 10, 210, IDC_BT_CANCEL, 4);

	m_btNotUse.CreatCheckButton(this, AfxGetInstanceHandle(),TEXT("PNG_BT_CHOSE"),28,68);
	m_btUserQuick.CreatCheckButton(this, AfxGetInstanceHandle(),TEXT("PNG_BT_CHOSE"),28,92);
	m_btNotUse.SetButtonChecked(true);


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
	pDevC->SetBkMode(TRANSPARENT);
	m_ImageBack.DrawImage(pDevC, 0, 0);

	m_btClose.SetBkGnd(pDevC);
	m_btConfirn.SetBkGnd(pDevC);
	m_btCancel.SetBkGnd(pDevC);

	m_btNotUse.OnDrawControl(pDevC);
	m_btUserQuick.OnDrawControl(pDevC);

	if (!m_strCtrl.empty() && !m_strKey.empty())
	{
		char temp[128];
		sprintf(temp, "%s + %s", m_strCtrl.c_str(), m_strKey.c_str());
		CRect rcAccounts;
		rcAccounts.SetRect(135, 92, 235,105);
		pDevC->DrawText(temp, lstrlen(temp),&rcAccounts,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}

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
	case IDC_BT_CANCEL:
		{
			OnCancel();
			return TRUE;
		}
	case IDC_BT_CONFIRN:
		{
			return TRUE;
		}
	}
	return FALSE;

}

//��굯��
void CFrameSet::OnLButtonUp(UINT nFlags, CPoint point)
{
	bool bClick = false;
	if(!bClick)
	{
		if(!m_btUserQuick.GetButtonChecked())
		{
			bClick = m_btUserQuick.OnClickControl(point);
			if(bClick)
				m_btNotUse.SetButtonChecked(false);
		}
	}
	if(!bClick)
	{
		if( !m_btNotUse.GetButtonChecked())
		{
			bClick = m_btNotUse.OnClickControl(point);
			if(bClick)
				m_btUserQuick.SetButtonChecked(false);
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CFrameSet::PreTranslateMessage(MSG* pMsg)
{
	if (m_btUserQuick.GetButtonChecked())
	{
		if (::GetAsyncKeyState(VK_CONTROL) & 0x8000f)
		{
			m_strCtrl = "CTRL";
		}
		else if (::GetAsyncKeyState(VK_MENU) & 0x8000f)
		{
			m_strCtrl = "ALT";
		}
		else if (::GetAsyncKeyState(VK_SHIFT) & 0x8000f)
		{
			m_strCtrl = "SHIFT";
		}
		
		for(int i = 0x30; i < 0x39; i++)
		{
			if (::GetAsyncKeyState(i) & 0x8000f)
			{
				m_strKey = MapVirtualKey(i,2);
			}
		}
		for(i = 0x41; i < 0x5A; i++)
		{
			if (::GetAsyncKeyState(i) & 0x8000f)
			{
				m_strKey = MapVirtualKey(i, 2);
			}
		}

	}
	return CDialog::PreTranslateMessage(pMsg);
}
