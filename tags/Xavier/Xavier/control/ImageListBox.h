#pragma once


/**
* \ingroup : asss
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-06-06
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CImageListBox : public CListCtrl
{
	DECLARE_DYNAMIC(CImageListBox)

public:
	/**
	 *
	 * \return 
	 */
	CImageListBox();

	/**
	 *
	 * \return 
	 */
	virtual ~CImageListBox();
	
	/**
	 *
	 * \param dwStyle 
	 * \param rect 
	 * \param pParentWnd 
	 * \param nID 
	 * \return 
	 */
	BOOL			Create(const SIZE& szImage, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	
	/**
	 *
	 * \param lpszFilePath 
	 * \return 
	 */
	BOOL			Load(LPCTSTR lpszPath, LPCTSTR lpszFilter);

	/**
	 *
	 * \return 
	 */
	CString			GetHotItemText();

	/**
	 *
	 * \param szImage 
	 * \param pBitmap 
	 * \return 
	 */
	CBitmap*		AdjustBitmap(LPCTSTR lpszImagePathName);

protected:
	CImageList		m_ImageList;
	CSize			m_ImageSize;
	CString			m_cHotText;

protected:
	DECLARE_MESSAGE_MAP()

public:
	/**
	 *
	 * \param *pNMHDR 
	 * \param *pResult 
	 */
	afx_msg void	OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


