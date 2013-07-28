#include "Stdafx.h"
#include "UISheet.h"

namespace YouLe
{	
	// 构造函数
	UISheet::UISheet()
		: m_pFocus(NULL), m_pInput(NULL), m_bPress(FALSE)
	{

	}

	// 析构函数
	UISheet::~UISheet()
	{

	}

	// 设置焦点
	void		UISheet::SetFocus(UIWidget* pFocus)
	{
		if (m_pFocus != pFocus)
			m_pFocus = pFocus;
	}

	// 是否是焦点
	BOOL		UISheet::IsFocus(UIWidget* pFocus)
	{
		if (m_pFocus != NULL && m_pFocus == pFocus)
			return TRUE;

		return FALSE;
	}

	// 获取焦点
	UIWidget*	UISheet::GetFocus() const
	{
		return m_pFocus;
	}

	// 鼠标移动
	BOOL		UISheet::InjectMouseMove(const CPoint& cPt)
	{
		// find current target widget
		UIWidget* pChildWnd = GetChildWidget(cPt);
		if (m_pInput == pChildWnd)
			 return FALSE;
		
		UIWidget* pDropWnd	= m_pInput;
		m_pInput = pChildWnd;
		
		if (pDropWnd)
			pDropWnd->OnMouseLeave(cPt);
	
		if (m_pInput)
			m_pInput->OnMouseEnter(cPt);

		return TRUE;
	}

	// 鼠标按下
	BOOL		UISheet::InjectLeftDown(const CPoint& cPt)
	{
		UIWidget* pTarget = GetChildWidget(cPt);
		if (pTarget != NULL)
		{
			if (m_pFocus != pTarget)
				m_pFocus = pTarget;

			m_pFocus->OnLeftDown(cPt);
		}
		else
		{
			m_pFocus = NULL;
		}

		return TRUE;
	}
	
	// 鼠标弹起
	BOOL		UISheet::InjectLeftUp(const CPoint& cPt)
	{
		// if current have focus widget then send left up messag to the focus
		if (m_pFocus)
		{
			// send left up message
			m_pFocus->OnLeftUp(cPt);

			// If the pop-up window when
			if (m_pFocus->PtInRect(cPt))
				m_pFocus->OnClicked(cPt);
			else
				m_pFocus = NULL;
		}
		
		return TRUE;
	}
}