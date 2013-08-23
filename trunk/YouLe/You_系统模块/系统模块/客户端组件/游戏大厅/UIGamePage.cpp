#include "Stdafx.h"
#include "UIGamePage.h"

namespace YouLe
{
#define IDP_GAME_VIEW						55530
#define IDP_ROOM_VIEW						55531
#define IDP_TABLE_VIEW						55532

	// ���캯��
	UIGamePage::UIGamePage()
		: m_pGameView(NULL)
	{

	}

	// ��������
	UIGamePage::~UIGamePage()
	{
		
	}

	// ���ڿؼ�
	BOOL	UIGamePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		m_pGameView = new UIGameView();
		m_pGameView->Create(IDP_GAME_VIEW, CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top), pAttach, pProcess, this);
		// ��������ҳ
		m_pRoomView = new UIRoomPage();
		m_pRoomView->Create(IDP_ROOM_VIEW, CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top), pAttach, pProcess, this);
		// ��������ҳ
		m_pTableView = new UITablePage();
		m_pTableView->Create(IDP_TABLE_VIEW, CRect(0, 0, rect.right - rect.left, rect.bottom - rect.top), pAttach, pProcess, this);

		VisibleWidget(FALSE);

		return TRUE;
	}

	void UIGamePage::ShowRoomView( CListKind* pKind )
	{
		if(!m_pRoomView->ShowRoomList(pKind))
		{
			ShowMessageBox("�Բ�����Ϸ������û������",MB_ICONQUESTION);
			return;
		}
		m_pGameView->VisibleWidget(FALSE);
		m_pRoomView->VisibleWidget(TRUE);	
	}

	void UIGamePage::VisibleTrigger()
	{
		if(!m_pRoomView->m_bEnterRoom)
		{
			m_pGameView->VisibleWidget(TRUE);
			m_pRoomView->VisibleWidget(FALSE);
			m_pTableView->VisibleWidget(FALSE);
		}
		else
		{	
			m_pTableView->VisibleWidget(TRUE);
			m_pGameView->VisibleWidget(FALSE);
			m_pRoomView->VisibleWidget(FALSE);
			m_pRoomView->SetEnterRoom(false);
		}

	}

}