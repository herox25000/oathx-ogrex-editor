#pragma once

#include "FileView.h"
#include "ResourceView.h"
#include "OutputWnd.h"
#include "PropertySetWnd.h"

class CMainFrame : public CFrameWndEx
{
	
protected: 
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	BOOL				CreateDockingWindows();
	void				SetDockingWindowIcons(BOOL bHiColorIcons);

protected:
	CMFCMenuBar			m_wMenuBar;
	CMFCToolBar			m_wToolBar;
	CMFCStatusBar		m_wStatusBar;
	CMFCToolBarImages	m_UserImages;
	CFileView			m_wFileView;
	CResourceView		m_wTreeView;
	COutputWnd			m_wOutput;
	CPropertySetWnd		m_wPropertySet;
protected:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnViewCustomize();
	afx_msg LRESULT		OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void		OnApplicationLook(UINT id);
	afx_msg void		OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};


