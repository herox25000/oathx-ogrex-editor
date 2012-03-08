#pragma once

// CColorListBox
class CColorListBox : public CListBox
{
	DECLARE_DYNAMIC(CColorListBox)
public:
	CColorListBox();
	virtual ~CColorListBox();

public:
	// Adds a string to the list box
	int				AddString(LPCTSTR lpszItem);

	// Adds a colored string to the list box
	int				AddString(LPCTSTR lpszItem, COLORREF rgb);

	// Inserts a string to the list box
	int				InsertString(int nIndex, LPCTSTR lpszItem);

	// Inserts a colored string to the list box
	int				InsertString(int nIndex, LPCTSTR lpszItem, COLORREF rgb);
	
	// Sets the color of an item in the list box
	void			SetItemColor(int nIndex, COLORREF rgb);

public:
	// Sets the color of an item in the list box
	virtual void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// Sets the color of an item in the list box
	virtual void	MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
protected:
	DECLARE_MESSAGE_MAP()
};


