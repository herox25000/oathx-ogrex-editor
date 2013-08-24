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

	// 创建控件
	BOOL	UIEditBox::Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight,
		CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;
	
		return TRUE;
	}

	// 控件绘制
	BOOL	UIEditBox::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		// 绘制选择区
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
			// 获取当前光标位置
			CPoint ptCursor = GetCursorPoint(pDC, m_nStart, m_nEnd);

			// 获取文本宽度
			CSize cSize = pDC->GetTextExtent(CURSOR_TEXT);

			// 设置光标绘制区
			CRect curRect;
			curRect.SetRect(ptCursor.x , ptCursor.y,
				ptCursor.x + cSize.cx, ptCursor.y + cSize.cy);

			// 绘制光标
			pDC->DrawText(CURSOR_TEXT, &curRect, DT_LEFT|DT_VCENTER);		
		}

		return UIText::Draw(pDC);
	}
	
	// 获取光标
	CPoint	UIEditBox::GetCursorPoint(CDC* pDC, INT nStart, INT nEnd)
	{
		if (nStart == 0 && nEnd == 0)
		{
			return m_rect.TopLeft();
		}

		CString text = m_szText.Mid(nStart, nEnd - nStart);
		if (text.IsEmpty())
			return FALSE;

		// 获取文本宽度
		CSize cSize	= pDC->GetTextExtent(text);
		CPoint cPt;
		cPt.SetPoint(m_rect.left + cSize.cx,
			m_rect.top);

		return cPt;
	}

	// 获取光标
	INT		UIEditBox::GetCursor(const CPoint& cPt)
	{
		// 当前控件起始位, 用于构建字符绘制区域
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

	// 设置光标
	void	UIEditBox::SetCursor(const CPoint& cPt)
	{
		m_nEnd		= GetCursor(cPt);
		m_nStart	= 0;
	}

	// 选择文本
	CString	UIEditBox::GetSelectText(INT nStart, INT nEnd)
	{
		INT nLength = nStart > nEnd ? nStart - nEnd : nEnd - nStart;
		return m_szText.Mid(nStart > nEnd ? nStart : nEnd, nLength);
	}

	// 键盘按下
	BOOL	UIEditBox::OnKeyDwon(UINT nChar, 
		UINT nRepCnt, UINT nFlags)
	{
		// 发送键盘消息
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

	// 键盘弹起
	BOOL	UIEditBox::OnKeyUp(UINT nChar, 
		UINT nRepCnt, UINT nFlags)
	{
		return TRUE;
	}

	// 字符输入
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

	// 鼠标移动
	BOOL	UIEditBox::OnMouseMove(const CPoint& cPt)
	{
		// 更新鼠标位置
		m_ptMouse[MOUSE_MOVE]	= cPt;
		
		if (m_bPressd)
		{
			if (m_bCursor)
				SetCursor(cPt);

			m_bSelect = TRUE;
		}

		return UIText::OnMouseMove(cPt);;
	}

	// 鼠标按下
	BOOL	UIEditBox::OnLeftDown(const CPoint& cPt)
	{
		// 更新鼠标位置
		m_ptMouse[MOUSE_DOWN]	= cPt;
		
		if (m_bSelect)
			m_bSelect = FALSE;

		m_bPressd	= TRUE;
		
		return UIText::OnLeftDown(cPt);
	}

	// 鼠标弹起
	BOOL	UIEditBox::OnLeftUp(const CPoint& cPt)
	{
		if (m_bCursor)
			SetCursor(cPt);

		m_bPressd	= FALSE;

		return UIText::OnLeftUp(cPt);;
	}


}