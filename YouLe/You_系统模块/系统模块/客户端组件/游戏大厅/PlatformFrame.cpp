#include "stdafx.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"

IMPLEMENT_DYNCREATE(CPlatformFrame, CFrameWnd)

CPlatformFrame::CPlatformFrame()
{
}

CPlatformFrame::~CPlatformFrame()
{
}


BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pGamePlazaDlg = new CGamePlazaDlg();
	m_pGamePlazaDlg->Create(IDD_GAMEPLAZA_DIALOG, this);
	m_pGamePlazaDlg->ShowWindow(SW_SHOW);

	return 0;
}
