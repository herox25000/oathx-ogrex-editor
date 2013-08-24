#include "Stdafx.h"
#include "UIEditBox.h"

namespace YouLe
{
	static const CString	CURSOR_TEXT	= TEXT("_");

	UIEditBox::UIEditBox() : m_bPressd(FALSE), m_nStart(0), m_nEnd(0), m_bCursor(TRUE)
	{
	
	}

	UIEditBox::~UIEditBox()
	{

	}

	// �����ؼ�
	BOOL	UIEditBox::Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight,
		CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;
	
		return TRUE;
	}

	// �ؼ�����
	BOOL	UIEditBox::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		// ����ѡ����
		if (m_bSelect)
		{
			CString text = GetSelectText(m_nStart, m_nEnd);
			if (!text.IsEmpty())
			{
				CSize cSize = pDC->GetTextExtent(text);
			}
		}

#ifdef _DEBUG
		pDC->FillRect(&m_rect, &CBrush(RGB(0, 255, 0)));
#endif
		if (m_bCursor)
		{
			// ��ȡ��ǰ���λ��
			CPoint ptCursor = GetCursorPoint(pDC, m_nStart, m_nEnd);

			// ��ȡ�ı����
			CSize cSize = pDC->GetTextExtent(CURSOR_TEXT);

			// ���ù�������
			CRect curRect;
			curRect.SetRect(ptCursor.x , ptCursor.y,
				ptCursor.x + cSize.cx, ptCursor.y + cSize.cy);

			// ���ƹ��
			pDC->DrawText(CURSOR_TEXT, &curRect, DT_LEFT|DT_VCENTER);		
		}

		return UIText::Draw(pDC);
	}
	
	// ��ȡ���
	CPoint	UIEditBox::GetCursorPoint(CDC* pDC, INT nStart, INT nEnd)
	{
		if (nStart == 0 && nEnd == 0)
		{
			return m_rect.TopLeft();
		}

		CString text = m_szText.Mid(nStart, nEnd - nStart);
		if (text.IsEmpty())
			return FALSE;

		// ��ȡ�ı����
		CSize cSize	= pDC->GetTextExtent(text);
		CPoint cPt;
		cPt.SetPoint(m_rect.left + cSize.cx,
			m_rect.top);

		return cPt;
	}

	// ��ȡ���
	INT		UIEditBox::GetCursor(const CPoint& cPt)
	{
		// ��ǰ�ؼ���ʼλ, ���ڹ����ַ���������
		CPoint ptStart = m_rect.TopLeft();

		for (int i=0; i<m_szText.GetLength(); i++)
		{
			CString c(
				m_szText.GetAt(i));

			CSize cSize = m_pAttach->GetDC()->GetTextExtent(c);

			CRect area;
			area.SetRect(ptStart.x, ptStart.y, 
				ptStart.x + cSize.cx, ptStart.y + cSize.cy);

			if (area.PtInRect(cPt))
				return i;

			ptStart.x += cSize.cx;
			//ptStart.y += cSize.cy;
		}

		return 0;
	}

	// ���ù��
	void	UIEditBox::SetCursor(const CPoint& cPt)
	{
		m_nEnd		= GetCursor(cPt);
		m_nStart	= 0;
	}

	// ѡ���ı�
	CString	UIEditBox::GetSelectText(INT nStart, INT nEnd)
	{
		INT nLength = nStart > nEnd ? nStart - nEnd : nEnd - nStart;
		return m_szText.Mid(nStart > nEnd ? nStart : nEnd, nLength);
	}

	// ���̰���
	BOOL	UIEditBox::OnKeyDwon(UINT nChar, 
		UINT nRepCnt, UINT nFlags)
	{
		// ���ͼ�����Ϣ
		UIText::OnKeyDwon(nChar, nRepCnt, nFlags);
		
		switch(nChar)
		{
		case VK_LEFT:
			{
				m_nEnd --;
			}
			break;

		case VK_RIGHT:
			{
				m_nEnd ++;
			}
			break;
		}
		return TRUE;
	}

	// ���̵���
	BOOL	UIEditBox::OnKeyUp(UINT nChar, 
		UINT nRepCnt, UINT nFlags)
	{
		return TRUE;
	}

	// �ַ�����
	BOOL	UIEditBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		UIWidget::OnChar(nChar, nRepCnt, nFlags);
		
		switch(nChar)
		{
		case VK_LBUTTON:
		case VK_RBUTTON:
		case VK_MBUTTON:
			break;

		case VK_BACK:
			{
				INT nLength = m_szText.GetLength();
				if (nLength > 0)
				{
					INT nStart = m_nEnd < nLength ? m_nEnd - 1 : nLength - 1;
					m_szText.Delete(nStart);

					m_nEnd -= 1;
				}
			}
			break;
		default:
			{
				m_szText.Append((char*)&nChar);

				if (m_nEnd >= 0 && m_nEnd < m_szText.GetLength())
				{
					m_nEnd += 1;
				}
				else
				{
					m_nEnd	= m_szText.GetLength();
				}
				
				m_nStart	= 0;
			}
		}

		return TRUE;
	}

	// ����ƶ�
	BOOL	UIEditBox::OnMouseMove(const CPoint& cPt)
	{
		// �������λ��
		m_ptMouse[MOUSE_MOVE]	= cPt;
		
		if (m_bPressd)
		{
			if (m_bCursor)
				SetCursor(cPt);

			m_bSelect = TRUE;
		}

		return UIText::OnMouseMove(cPt);;
	}

	// ��갴��
	BOOL	UIEditBox::OnLeftDown(const CPoint& cPt)
	{
		// �������λ��
		m_ptMouse[MOUSE_DOWN]	= cPt;
		
		if (m_bSelect)
			m_bSelect = FALSE;

		m_bPressd	= TRUE;
		
		return UIText::OnLeftDown(cPt);
	}

	// ��굯��
	BOOL	UIEditBox::OnLeftUp(const CPoint& cPt)
	{
		if (m_bCursor)
			SetCursor(cPt);

		m_bPressd	= FALSE;

		return UIText::OnLeftUp(cPt);;
	}


}