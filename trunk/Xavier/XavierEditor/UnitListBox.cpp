#include "stdafx.h"
#include "UnitListBox.h"
#include "XavierEditorInclude.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CUnitListBox, CListCtrl)

/**
 *
 * \return 
 */
CUnitListBox::CUnitListBox()
{
	m_bDragging = false;
	m_pDragImage = NULL;
}

/**
 *
 * \return 
 */
CUnitListBox::~CUnitListBox()
{
}


BEGIN_MESSAGE_MAP(CUnitListBox, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CUnitListBox::OnNMClick)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &CUnitListBox::OnLvnBegindrag)
END_MESSAGE_MAP()

/**
 *
 * \param lpszPath 
 * \param lpszFilter 
 * \return 
 */
BOOL		CUnitListBox::Load(LPCTSTR lpszPath, LPCTSTR lpszFilter)
{
	char szPath[MAX_PATH];
	sprintf(szPath, "%s\\%s", lpszPath, lpszFilter);

	SetRedraw( FALSE );

	WIN32_FIND_DATA wDt;
	HANDLE hFile = ::FindFirstFile(szPath, &wDt);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		BOOL bFind = TRUE;

		while( bFind )
		{
			if (!(wDt.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				CString s(wDt.cFileName);
				if (!s.IsEmpty())
				{
					CImage image;
					sprintf(szPath, "%s\\%s", lpszPath, "ogrem2.bmp");

					image.Load(szPath);
					CBitmap* pBitmap = CBitmap::FromHandle((HBITMAP)image);
					if (pBitmap)
					{
						// 添加位图
						int image	= m_ImageList.Add(pBitmap, RGB(0, 0, 0));
						int nItem	= image ? image - 1 : 0;
						// 插入项目
						InsertItem(nItem, s.GetBuffer(), image);
					}
				}
			}

			bFind = ::FindNextFile(hFile, &wDt);
		}

		::FindClose(hFile);
	}

	SetRedraw(TRUE);
	Invalidate();

	return TRUE;
}

/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void		CUnitListBox::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{

	}

	*pResult = 0;
}

/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void	CUnitListBox::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV	= reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (pNMLV->iItem >= 0)
	{
		// 获取文件名
		m_szFileName		= GetItemText(pNMLV->iItem, pNMLV->iSubItem);

		POINT pt ={
			0, 0
		};

		int nOffset = 0;
		int nCount	= GetSelectedCount();
		if (nCount >= 1)
		{
			pt.x = nOffset;
			pt.y = nOffset;
		}

		m_pDragImage = CreateDragImage(pNMLV->iItem, &pt);
		if (m_pDragImage)
		{
			IMAGEINFO img;
			m_ImageList.GetImageInfo(pNMLV->iItem, &img);

			CBitmap* pBitmap = CBitmap::FromHandle(img.hbmImage);
			if (pBitmap)
			{
				m_pDragImage->Replace(0, pBitmap, NULL);
				m_pDragImage->BeginDrag(0, 
					CPoint(nOffset, nOffset));
				m_pDragImage->DragEnter(GetDesktopWindow(), pNMLV->ptAction);

				m_bDragging = TRUE;

				SetCapture ();
			}
		}
	}

	*pResult = 0;
}
/**
 *
 * \param nFlags 
 * \param point 
 */
void	CUnitListBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragging && m_pDragImage != NULL)
	{
		CPoint cPt(point);
		ClientToScreen(&cPt);

		m_pDragImage->DragMove(cPt);
		m_pDragImage->DragShowNolock(false);

		CWnd* pDropWnd = WindowFromPoint (cPt);
		if (pDropWnd)
		{
			pDropWnd->ScreenToClient(&cPt);

			if(pDropWnd->IsKindOf(RUNTIME_CLASS (CView)))
			{			
				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
			else
			{
				SetCursor(LoadCursor(NULL, IDC_NO));
			}

			m_pDragImage->DragShowNolock(true);
		}
	}
}
/**
 *
 * \param nFlags 
 * \param point 
 */
void	CUnitListBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDragging && m_pDragImage != NULL)
	{
		ReleaseCapture ();

		m_bDragging = FALSE;

		m_pDragImage->DragLeave (GetDesktopWindow ());
		m_pDragImage->EndDrag ();
		delete m_pDragImage;

		CPoint pt(point);
		ClientToScreen(&pt);
		
		CWnd* pDropWnd = WindowFromPoint (pt);
		if (pDropWnd)
		{
			if (pDropWnd->IsKindOf (RUNTIME_CLASS (CView)))
			{
				CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
				if (pMainFrame)
				{
					
					wmCreateUnit c;
					strcpy(c.Name, m_szFileName.GetBuffer());

					// 通知文件窗口
					::SendMessage(pMainFrame->GetActiveView()->m_hWnd,
						WM_CREATE_UNIT, (WPARAM)&c, NULL);
				}
			}
		}
	}
}

