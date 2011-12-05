#pragma once


// CColorListBox

class CColorListBox : public CListBox
{
	DECLARE_DYNAMIC(CColorListBox)



public:
	CColorListBox();
	virtual ~CColorListBox();

public:
	int AddString(LPCTSTR lpszItem);											// Adds a string to the list box
	int AddString(LPCTSTR lpszItem, COLORREF rgb);						// Adds a colored string to the list box
	int InsertString(int nIndex, LPCTSTR lpszItem);						// Inserts a string to the list box
	int InsertString(int nIndex, LPCTSTR lpszItem, COLORREF rgb);	// Inserts a colored string to the list box
	void SetItemColor(int nIndex, COLORREF rgb);							// Sets the color of an item in the list box
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL



protected:
	DECLARE_MESSAGE_MAP()
};


