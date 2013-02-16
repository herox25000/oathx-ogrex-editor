#pragma once

#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "WizardDialog.h"

class CMainFrame : public CFrameWndEx
{
protected:
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	virtual BOOL		PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL		LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL,
		CCreateContext* pContext = NULL);
	virtual	void		ResetFileTree();

	/**
	 *
	 * \return 
	 */
	CPropertiesWnd*		GetPropertyWnd();
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CMFCMenuBar			m_wndMenuBar;
	CMFCToolBar			m_wndToolBar;
	CMFCStatusBar		m_wndStatusBar;
	CMFCToolBarImages	m_UserImages;
	CFileView			m_wndFileView;
	CClassView			m_wndClassView;
	COutputWnd			m_wndOutput;
	CPropertiesWnd		m_wndProperties;
	CWizardDialog		m_dWizardDialog;
protected:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnViewCustomize();
	afx_msg LRESULT		OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void		OnApplicationLook(UINT id);
	afx_msg void		OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL				CreateDockingWindows();
	void				SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void		OnFileNew();
};


