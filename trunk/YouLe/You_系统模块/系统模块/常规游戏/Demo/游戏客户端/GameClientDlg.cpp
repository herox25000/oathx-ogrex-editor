#include "Stdafx.h"
#include "GameOption.h"
#include "GameClient.h"
#include "GameClientDlg.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientDlg, CGameFrameDlg)
	ON_WM_TIMER()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameClientDlg::CGameClientDlg() : CGameFrameDlg(&m_GameClientView)
{
	
}

//析构函数
CGameClientDlg::~CGameClientDlg()
{
}

//定时器消息
void CGameClientDlg::OnTimer(UINT nIDEvent)
{
	__super::OnTimer(nIDEvent);
}