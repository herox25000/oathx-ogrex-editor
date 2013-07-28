#include "Stdafx.h"
#include "UIFrameSheet.h"
#include "UIGamePage.h"
#include "UIFramePage.h"

namespace YouLe
{
	// 构造函数
	UIFrameSheet::UIFrameSheet()
	{

	}
	
	// 析构函数
	UIFrameSheet::~UIFrameSheet()
	{

	}

	// 创建窗口
	UIFrameSheet::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;
		
		UIFramePage* pFramePage = new UIFramePage();
		pFramePage->Create(1, rect, pAttach, pProcess, this);

		UIGamePage* pGamePage	= new UIGamePage();
		pGamePage->Create(0, CRect(245, 206, 245+176*3, 260+140*3), pAttach, pProcess, this);

		return TRUE;
	}
}