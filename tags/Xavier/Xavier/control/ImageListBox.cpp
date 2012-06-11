#include "stdafx.h"
#include "ImageListBox.h"
#include <atlimage.h>


IMPLEMENT_DYNAMIC(CImageListBox, CListCtrl)

/**
 *
 * \return 
 */
CImageListBox::CImageListBox()
{

}

/**
 *
 * \return 
 */
CImageListBox::~CImageListBox()
{
}


BEGIN_MESSAGE_MAP(CImageListBox, CListCtrl)
	
	ON_NOTIFY_REFLECT(NM_CLICK, &CImageListBox::OnNMClick)
END_MESSAGE_MAP()


/**
 *
 * \param dwStyle 
 * \param rect 
 * \param pParentWnd 
 * \param nID 
 * \return 
 */
BOOL		CImageListBox::Create(const SIZE& szImage, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	DWORD dwImageListBox = dwStyle | LVS_SHOWSELALWAYS | LVS_ALIGNTOP | LVS_ICON | LVS_SINGLESEL | LVS_AUTOARRANGE;
	
	CListCtrl::Create(dwImageListBox, 
		rect, pParentWnd, nID);

	if (m_ImageList.Create(szImage.cx,
		szImage.cy, 
		ILC_COLOR32, 
		0, 
		1))
	{
		SetImageList(&m_ImageList, LVSIL_NORMAL);
		
		// 保存图片大小
		m_ImageSize = szImage;
	}
	
	return TRUE;
}


/**
 *
 * \param lpszFilePath 
 * \param lpszFilter 
 * \return 
 */
BOOL		CImageListBox::Load(LPCTSTR lpszFilePath, LPCTSTR lpszFilter)
{
	char szPath[MAX_PATH];
	sprintf(szPath, "%s\\%s", lpszFilePath, lpszFilter);

	SetRedraw( FALSE );

	WIN32_FIND_DATA wDt;
	HANDLE hFile = ::FindFirstFile(szPath, &wDt);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		UINT nItem = 0;
		BOOL bFind = TRUE;
		while( bFind )
		{
			if (!(wDt.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				CString s(wDt.cFileName);
				if (!s.IsEmpty())
				{
					CImage image;
					sprintf(szPath, "%s\\%s", lpszFilePath, wDt.cFileName);
					
					image.Load(szPath);
					CBitmap* pBitmap = CBitmap::FromHandle((HBITMAP)image);
					if (pBitmap)
					{
						// 添加位图
						m_ImageList.Add(pBitmap, RGB(0, 0, 0));
						
						// 插入项目
						InsertItem(nItem, s.GetBuffer(), nItem);

						// 递增索引
						nItem ++;
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
 * \param lpszImagePathName 
 * \return 
 */
CBitmap*	CImageListBox::AdjustBitmap(LPCTSTR lpszImagePathName)
{
	return NULL;
}

/**
 *
 * \return 
 */
CString		CImageListBox::GetSelectItemString()
{
	return m_cItemText;
}
/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void		CImageListBox::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		m_cItemText = GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
	}

	*pResult = 0;
}
