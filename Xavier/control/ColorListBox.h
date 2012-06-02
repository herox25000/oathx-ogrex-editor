#pragma once

// CColorListBox
/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-03-08
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CColorListBox : public CListBox
{
	DECLARE_DYNAMIC(CColorListBox)
public:
	/**
	 *
	 * \return 
	 */
	CColorListBox();

	/**
	 *
	 * \return 
	 */
	virtual ~CColorListBox();

public:
	// Adds a string to the list box
	/**
	 *
	 * \param lpszItem 
	 * \return 
	 */
	int				AddString(LPCTSTR lpszItem);

	// Adds a colored string to the list box
	/**
	 *
	 * \param lpszItem 
	 * \param rgb 
	 * \return 
	 */
	int				AddString(LPCTSTR lpszItem, COLORREF rgb);

	// Inserts a string to the list box
	/**
	 *
	 * \param nIndex 
	 * \param lpszItem 
	 * \return 
	 */
	int				InsertString(int nIndex, LPCTSTR lpszItem);

	// Inserts a colored string to the list box
	/**
	 *
	 * \param nIndex 
	 * \param lpszItem 
	 * \param rgb 
	 * \return 
	 */
	int				InsertString(int nIndex, LPCTSTR lpszItem, COLORREF rgb);
	
	// Sets the color of an item in the list box
	/**
	 *
	 * \param nIndex 
	 * \param rgb 
	 */
	void			SetItemColor(int nIndex, COLORREF rgb);

public:
	// Sets the color of an item in the list box
	/**
	 *
	 * \param lpDrawItemStruct 
	 */
	virtual void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// Sets the color of an item in the list box
	/**
	 *
	 * \param lpMeasureItemStruct 
	 */
	virtual void	MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
protected:
	DECLARE_MESSAGE_MAP()
};


