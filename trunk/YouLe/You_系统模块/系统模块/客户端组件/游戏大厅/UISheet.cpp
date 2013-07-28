#include "Stdafx.h"
#include "UISheet.h"

namespace YouLe
{	
	// ���캯��
	UISheet::UISheet()
		: m_pFocus(NULL), m_pInput(NULL), m_bPress(FALSE)
	{

	}

	// ��������
	UISheet::~UISheet()
	{

	}

	// ���ý���
	void		UISheet::SetFocus(UIWidget* pFocus)
	{
		if (m_pFocus != pFocus)
			m_pFocus = pFocus;
	}

	// �Ƿ��ǽ���
	BOOL		UISheet::IsFocus(UIWidget* pFocus)
	{
		if (m_pFocus != NULL && m_pFocus == pFocus)
			return TRUE;

		return FALSE;
	}

	// ��ȡ����
	UIWidget*	UISheet::GetFocus() const
	{
		return m_pFocus;
	}

	// ����ƶ�
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

	// ��갴��
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
	
	// ��굯��
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