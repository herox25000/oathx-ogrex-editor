#pragma once

#include <map>

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
	typedef std::map<CString, CBitmap*>	BitmapRegister;
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
protected:
	CImageList		m_ImageList;
	CSize			m_ImageSize;
	CString			m_cItemText;

protected:
	DECLARE_MESSAGE_MAP()
};


