#include "StdAfx.h"
#include "Resource.h"
#include "GameOptionItem.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameOptionItem, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameOptionItem::CGameOptionItem()
{
	//���ñ���
	m_ControlSize.SetSize(0,0);

	//������Դ
	HINSTANCE hInstance=GetModuleHandle(GAME_FRAME_DLL_NAME);
	m_ImageOptionLogo.LoadFromResource(hInstance,IDB_OPTION_LOGO);

	//��ȡ��С
	m_LogoSize.SetSize(m_ImageOptionLogo.GetWidth(),m_ImageOptionLogo.GetHeight());

	return;
}

//��������
CGameOptionItem::~CGameOptionItem()
{
}

//�ӿڲ�ѯ
VOID * CGameOptionItem::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameOptionItem,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameOptionItem,Guid,dwQueryVer);
	return NULL;
}

//�����ؼ�
VOID __cdecl CGameOptionItem::RectifyControl(INT nWidth, INT nHeight)
{
	//�����ؼ�
	if ((m_ControlSize.cx!=nWidth)||(m_ControlSize.cy!=nHeight))
	{
		//��������
		CWnd * pWndChild=NULL;

		//���Ҵ���
		do
		{
			//���Ҵ���
			pWndChild=FindWindowEx(m_hWnd,pWndChild->GetSafeHwnd(),NULL,NULL);

			//�ƶ�����
			if (pWndChild!=NULL)
			{
				//��ȡλ��
				CRect rcControl;
				pWndChild->GetWindowRect(&rcControl);

				//�ƶ�����
				ScreenToClient(&rcControl);
				pWndChild->SetWindowPos(NULL,rcControl.left+(nWidth-m_ControlSize.cx)/2,rcControl.top+(nHeight-m_ControlSize.cy)/2,0,0,SWP_NOSIZE|SWP_NOZORDER);
			}
		} while (pWndChild!=NULL);
	}

	return;
}

//�滭�ؼ�
VOID __cdecl CGameOptionItem::DrawControlFace(CDC * pDC, INT nWidth, INT nHeight)
{
	//�滭����
	pDC->FillSolidRect(0,0,nWidth,nHeight,CSkinDialog::m_SkinAttribute.m_crBackGround);
	m_ImageOptionLogo.BitBlt(pDC->m_hDC,nWidth-m_ImageOptionLogo.GetWidth(),nHeight-m_ImageOptionLogo.GetHeight());

	return;
}

//ȷ����Ϣ
VOID CGameOptionItem::OnOK()
{
	//������Ϣ
	CWnd * pParentWnd=GetParent();
	pParentWnd->SendMessage(WM_COMMAND,IDOK,(LPARAM)(pParentWnd->GetSafeHwnd()));

	return;
}

//ȡ����Ϣ
VOID CGameOptionItem::OnCancel()
{
	//������Ϣ
	CWnd * pParentWnd=GetParent();
	pParentWnd->SendMessage(WM_COMMAND,IDCANCEL,(LPARAM)(pParentWnd->GetSafeHwnd()));

	return;
}

//�滭��Ϣ
VOID CGameOptionItem::OnPaint()
{
	//��������
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//�滭����
	DrawControlFace(&dc,rcClient.Width(),rcClient.Height());

	return;
}

//�滭����
BOOL CGameOptionItem::OnEraseBkgnd(CDC * pDC)
{
	//���´���
	Invalidate(FALSE);
	UpdateWindow();

	return TRUE;
}

//λ����Ϣ
VOID CGameOptionItem::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType,cx,cy);

	//����λ��
	RectifyControl(cx,cy);

	return;
}

//������Ϣ
BOOL CGameOptionItem::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	__super::OnCreate(lpCreateStruct);

	//��ȡλ��
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//���ñ���
	m_ControlSize.SetSize(rcWindow.Width()+m_LogoSize.cx,rcWindow.Height());

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CGameOptionItem::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(CSkinDialog::m_SkinAttribute.m_crBackGround);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}
	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//////////////////////////////////////////////////////////////////////////
