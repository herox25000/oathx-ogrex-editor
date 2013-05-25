#include "stdafx.h"
#include "DefaultResourceListBox.h"
#include "MainFrm.h"
#include <atlimage.h>


IMPLEMENT_DYNAMIC(CDefaultResourceListBox, CListCtrl)

/**
 *
 * \return 
 */
CDefaultResourceListBox::CDefaultResourceListBox()
{
	m_pDragImage	= NULL;
	m_hDropItem		= NULL;
	m_bDragging		= FALSE;
}

/**
 *
 * \return 
 */
CDefaultResourceListBox::~CDefaultResourceListBox()
{
}


BEGIN_MESSAGE_MAP(CDefaultResourceListBox, CListCtrl)
	
	ON_NOTIFY_REFLECT(NM_CLICK, &CDefaultResourceListBox::OnNMClick)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &CDefaultResourceListBox::OnLvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void		CDefaultResourceListBox::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		m_cItemText = GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
		if (!m_cItemText.IsEmpty() && m_oldDecalName != m_cItemText)
		{
			CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
			if (pMainFrame)
			{
			}

			m_oldDecalName = m_cItemText;
		}
	}

	*pResult = 0;
}

/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void		CDefaultResourceListBox::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV	= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	m_nDragItem			= pNMLV->iItem;

	POINT pt;
	pt.x = 8;
	pt.y = 8;

	if(m_pDragImage)
		delete m_pDragImage;

	m_pDragImage = CreateDragImage(m_nDragItem, &pt);
	if (m_pDragImage)
	{
		VERIFY (m_pDragImage->BeginDrag (0, CPoint (8, 8)));
		VERIFY (m_pDragImage->DragEnter (GetDesktopWindow (), pNMLV->ptAction));

		m_bDragging = TRUE;
		m_hDropItem = NULL;

		// capture all mouse messages
		SetCapture ();
	}

	*pResult = 0;
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void		CDefaultResourceListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragging)
	{
		CPoint pt (point);
		ClientToScreen (&pt);

		VERIFY (m_pDragImage->DragMove (pt));
		//VERIFY (m_pDragImage->DragShowNolock (FALSE));
		//VERIFY (m_pDragImage->DragShowNolock (TRUE));
	}

	CImageListBox::OnMouseMove(nFlags, point);
}

/**
 *
 * \param nFlags 
 * \param point 
 */
void		CDefaultResourceListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDragging)
	{
		// release mouse capture
		VERIFY (::ReleaseCapture ());

		m_bDragging = FALSE;
		
		// end dragging
		VERIFY (m_pDragImage->DragLeave (GetDesktopWindow ()));
		m_pDragImage->EndDrag ();

		CPoint pt (point);
		ClientToScreen (&pt);

		// get the CWnd pointer of the window that is under the mouse cursor
		CWnd* pDropWnd = WindowFromPoint (pt);
		if (pDropWnd)
		{
			if (pDropWnd->IsKindOf (RUNTIME_CLASS (CView)))
			{
				int x = 0;
			}
			CWnd* pView = AfxGetMainWnd()->GetActiveWindow();
 			CRect rect;
			pView->GetClientRect(&rect);

			if (rect.PtInRect(pt))
			{
				int x = 0;
			}
		}
	}

	CImageListBox::OnLButtonUp(nFlags, point);
}
