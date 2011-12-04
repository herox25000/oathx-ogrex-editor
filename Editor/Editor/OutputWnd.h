#pragma once

class COutputList : public CListBox
{
public:
	COutputList();
	virtual ~COutputList();

	void				AddLogMessage(LPCTSTR message);
protected:
	afx_msg void		OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void		OnEditCopy();
	afx_msg void		OnEditClear();
	afx_msg void		OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{

public:
	COutputWnd();
	virtual ~COutputWnd();

protected:
	CFont				m_Font;
	CMFCTabCtrl			m_wndTabs;

	COutputList			m_wndOutputBuild;
	COutputList			m_wndOutputDebug;
	COutputList			m_wndOutputFind;

public:
	COutputList*		GetBuildLogListWindow() {return &m_wndOutputBuild;}

protected:
	void				AdjustHorzScroll(CListBox& wndListBox);

protected:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

