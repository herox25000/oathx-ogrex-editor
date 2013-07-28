#include "Stdafx.h"
#include "UIFrameSheet.h"

namespace YouLe
{
	// ���캯��
	UIFrameSheet::UIFrameSheet()
	{

	}
	
	// ��������
	UIFrameSheet::~UIFrameSheet()
	{

	}

	// ��������
	UIFrameSheet::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;
		
		UIGamePage* pGamePage = new UIGamePage();
		pGamePage->Create(0, CRect(245, 206, 245+176*3, 260+140*3), pAttach, pProcess, this);

		UIFramePage* pFramePage = new UIFramePage();
		pFramePage->Create(1, rect, pAttach, pProcess, this);

		return TRUE;
	}

	// ע����갴��
	BOOL		UIFrameSheet::InjectLeftDown(const CPoint& cPt)
	{
		if (UIWidget::OnLeftDown(cPt))
			return TRUE;

		return FALSE;
	}

	// ע����굯��
	BOOL		UIFrameSheet::InjectLeftUp(const CPoint& cPt)
	{
		if (UIWidget::OnLeftUp(cPt))
			return TRUE;

		return FALSE;
	}

	// ע������ƶ�
	BOOL		UIFrameSheet::InjectMouseMove(const CPoint& cPt)
	{
		if (UIWidget::OnMouseMove(cPt))
			return TRUE;

		return FALSE;
	}
}