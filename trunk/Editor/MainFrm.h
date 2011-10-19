#pragma once

#include "FileView.h"
#include "UnitView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "NullPTDialog.h"

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
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

	CFileView*				GetFileView() {return &m_wFileView;}
	CUnitView*				GetUnitView() {return &m_wUnitView;}
	COutputWnd*				GetOutputView()	{return &m_wOutput;}

protected:			
	CMFCMenuBar				m_wMenuBar;
	CMFCToolBar				m_wToolBar;
	CMFCStatusBar			m_wndStatusBar;
	CMFCToolBarImages		m_UserImages;
	CFileView				m_wFileView;
	CUnitView				m_wUnitView;
	COutputWnd				m_wOutput;
	CPropertiesWnd			m_wPropertie;
	CNullPTDialog			m_dNullPT;

protected:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void			OnViewCustomize();
	afx_msg LRESULT			OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void			OnApplicationLook(UINT id);
	afx_msg void			OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL					CreateDockingWindows();
	void					SetDockingWindowIcons(BOOL bHiColorIcons);

public:
	afx_msg void			OnNullSolution();
};

//////////////////////////////////////////////////////////////////////////
#define BDLogMessage( s )								 \
{														 \
	CMainFrame* pFrame = (CMainFrame*)(AfxGetMainWnd()); \
	ASSERT(pFrame != NULL);								 \
	pFrame->GetOutputView()->AddBDString(s);			 \
}
//////////////////////////////////////////////////////////////////////////

