#include "Stdafx.h"
#include "UIFramePage.h"
#include "Platform.h"
#include "UIFrameClose.h"



namespace YouLe
{
	// ���캯��
	UIFramePage::UIFramePage()
	{

	}

	// ��������
	UIFramePage::~UIFramePage()
	{

	}

	// ���ڿؼ�
	BOOL	UIFramePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);


		return TRUE;
	}

	// ��������Ϣ
	BOOL	UIFramePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		//switch(pWidget->GetID())
		//{
		//case IDC_BT_FRAME_MIN:
		//	{
		//		m_pAttach->ShowWindow(SW_MINIMIZE);
		//		return TRUE;
		//	}
		//case IDC_BT_LOBBYSET:
		//	{
		//		SendMessage(WM_COMMAND, WM_SHOW_LOBBYSET, NULL);
		//		return TRUE;
		//	}
		//case IDC_BT_FRAME_CLOSE:
		//	{
		//		//UIWidget* pCloseWnd = Search(IDP_FRAME_CLOSE);
		//		//pCloseWnd->MoveToFront();
		//		//pCloseWnd->VisibleWidget(TRUE);
		//		return TRUE;
		//	}
		//}

		return FALSE;
	}
}