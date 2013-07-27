// FrameSet.cpp : 实现文件
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "FrameSet.h"
#include "Platform.h"
#include "GlobalUnits.h"

#define FRAMEDLG_X							359
#define FRAMEDLG_Y							240

#define IDC_BT_CLOSE						100
#define IDC_BT_CONFIRN						101
#define IDC_BT_CANCEL						102


KeyManage::KeyManage()
{
	memset(m_key,0,sizeof(BYTE)*256);
}

KeyManage::~KeyManage()
{

}

void KeyManage::PreTranslateKey()
{
	GetKeyboardState(m_key);
}

inline int KeyManage::GetKeyState(UINT vKey)
{
	ASSERT(vKey<256);
	return m_key[vKey]&0x80;
}

CString KeyManage::GetKeyName(UINT vk, BOOL fExtended)
{
	LONG lScan = MapVirtualKey(vk, 0) << 16;

	if (fExtended)
		lScan |= 0x01000000L;

	CString str;
	int nBufferLen = 64;
	int nLen;
	do
	{
		nBufferLen *= 2;
		LPTSTR psz = str.GetBufferSetLength(nBufferLen);
		nLen = ::GetKeyNameText(lScan, psz, nBufferLen + 1);
		str.ReleaseBuffer(nLen);
	}
	while (nLen == nBufferLen);
	return str;

}

BOOL KeyManage::GetKeyAllState(string &str)
{
	BOOL IsPress = FALSE;
	str = "";
	int nArrKey[2] = {-1, -1};
	for(int i = 0; i < 256; i++)
	{
		if(GetKeyState(i))
		{
			if (FALSE == IsPress)
				IsPress = TRUE;
			CString c = _T("");
			bool bExtend = FALSE;
			if (i == 18 || i == 164)			//alt
				nArrKey[0] = VK_MENU;
			else if (i == 17 || i == 162)		//ctrl
				nArrKey[0] = VK_CONTROL;
			else if (i == 16 || i == 160)		//ctrl
				nArrKey[0] = VK_SHIFT;
			else
				nArrKey[1] = i;
			str += c;
		}
	}
	if (nArrKey[0] >= 0)
		str += GetKeyName(nArrKey[0], FALSE);
	if (nArrKey[1] >= 0)
		str += GetKeyName(nArrKey[1], TRUE);
	return IsPress;
}

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
	ON_WM_LBUTTONUP()
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CFrameSet 消息处理程序

int CFrameSet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetWindowPos(NULL, 0, 0, FRAMEDLG_X, FRAMEDLG_Y, SWP_NOZORDER);
	CenterWindow();

	tagPlatformFrameImageNew & FrameViewImage = g_GlobalUnits.m_PlatformFrameImage;
	HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	m_ImageBack.LoadImage(hInstance, FrameViewImage.pszFrameSet);

	m_btClose.CreateButton(this, FrameViewImage.pszBtClose, _T("PNG"), FRAMEDLG_X - 42, 3, IDC_BT_CLOSE, 4, hInstance);
	m_btConfirn.CreateButton(this, FrameViewImage.pszBtConfirn, _T("PNG"), FRAMEDLG_X / 2 - 100, 210, IDC_BT_CONFIRN, 4, hInstance);
	m_btCancel.CreateButton(this, FrameViewImage.pszBtCancel, _T("PNG"), FRAMEDLG_X / 2 + 10, 210, IDC_BT_CANCEL, 4, hInstance);

	m_btNotUse.CreatCheckButton(this, hInstance, FrameViewImage.pszBtChose,28,68);
	m_btUserQuick.CreatCheckButton(this, hInstance, FrameViewImage.pszBtChose,28,92);
	m_btNotUse.SetButtonChecked(true);

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
	pDevC->SetBkMode(TRANSPARENT);
	m_ImageBack.DrawImage(pDevC, 0, 0);

	m_btClose.SetBkGnd(pDevC);
	m_btConfirn.SetBkGnd(pDevC);
	m_btCancel.SetBkGnd(pDevC);

	m_btNotUse.OnDrawControl(pDevC);
	m_btUserQuick.OnDrawControl(pDevC);

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
	case IDC_BT_CANCEL:
		{
			OnCancel();
			return TRUE;
		}
	case IDC_BT_CONFIRN:
		{
			//保存到配置文件中
			//AfxGetMainWnd()->SaveBossKey();
			OnOK();
			return TRUE;
		}
	}
	return FALSE;

}

//鼠标弹起
void CFrameSet::OnLButtonUp(UINT nFlags, CPoint point)
{
	bool bClick = false;
	if(!bClick)
	{
		if(!m_btUserQuick.GetButtonChecked())
		{
			bClick = m_btUserQuick.OnClickControl(point);
			if(bClick)
			{
				m_btNotUse.SetButtonChecked(false);
			}
		}
	}
	if(!bClick)
	{
		if( !m_btNotUse.GetButtonChecked())
		{
			bClick = m_btNotUse.OnClickControl(point);
			if(bClick)
			{
				m_btUserQuick.SetButtonChecked(false);
			}
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CFrameSet::PreTranslateMessage(MSG* pMsg)
{
	if (m_btUserQuick.GetButtonChecked())
	{
// 		m_keys.PreTranslateKey();
// 		string str;
// 		if(m_keys.GetKeyAllState(str))
// 		{
// 			CDC* pDC = GetDC();
// 			CRect rcClient;
// 			GetClientRect(&rcClient);
// 			CMemDC pDevC(pDC, rcClient);
// 			pDevC->SetBkMode(TRANSPARENT);
// 
// 			CRect rcAccounts;
// 			rcAccounts.SetRect(135, 92, 235,105);
// 			pDevC->DrawText(str.c_str(), str.length(),&rcAccounts,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
// 		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}