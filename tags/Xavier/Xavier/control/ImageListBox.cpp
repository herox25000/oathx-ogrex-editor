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
		
		// ����ͼƬ��С
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
						// ���λͼ
						m_ImageList.Add(pBitmap, RGB(0, 0, 0));
						
						// ������Ŀ
						InsertItem(nItem, s.GetBuffer(), nItem);

						// ��������
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