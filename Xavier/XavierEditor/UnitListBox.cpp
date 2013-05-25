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
