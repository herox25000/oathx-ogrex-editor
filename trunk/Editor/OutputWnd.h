#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList ´°¿Ú
//
class COutputList : public CListBox
{
public:
	COutputList();

public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
class COutputWnd : public CDockablePane
{
public:
	COutputWnd();

	void				AddBDString(CString bdStreing) {m_wOutputBuild.AddString(bdStreing);}
protected:
	CFont				m_Font;
	CMFCTabCtrl			m_wTabs;

	COutputList			m_wOutputBuild;
	COutputList			m_wOutputDebug;
	COutputList			m_wOutputFind;

protected:
	void				AdjustHorzScroll(CListBox& wndListBox);

public:
	virtual ~COutputWnd();

protected:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

