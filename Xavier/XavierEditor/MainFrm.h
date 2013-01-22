#pragma once

#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"
#include "WizardDialog.h"

/**
* \ingroup : OgreEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-15
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CMainFrame : public CFrameWndEx
{
protected:
	/**
	 *
	 * \return 
	 */
	CMainFrame();

	/**
	 *
	 * \return 
	 */
	virtual ~CMainFrame();

	DECLARE_DYNCREATE(CMainFrame)
public:
	/**
	 *
	 * \param cs 
	 * \return 
	 */
	virtual BOOL		PreCreateWindow(CREATESTRUCT& cs);

	/**
	 *
	 * \param nIDResource 
	 * \param dwDefaultStyle 
	 * \param pParentWnd 
	 * \param pContext 
	 * \return 
	 */
	virtual BOOL		LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, 
		CCreateContext* pContext = NULL);
	
	/**
	 *
	 * \param lpszMessage 
	 * \param clr 
	 * \return 
	 */
	virtual BOOL		AddLogMessage(LPCTSTR lpszMessage, COLORREF clr);

	/**
	 *
	 */
	virtual	void		UpdateFileView();
public:
	/**
	 *
	 * \return 
	 */
	CPropertiesWnd*		GetPropertyWnd();
protected:
	/**
	 *
	 * \return 
	 */
	BOOL				CreateDockingWindows();

	/**
	 *
	 * \param bHiColorIcons 
	 */
	void				SetDockingWindowIcons(BOOL bHiColorIcons);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CMFCMenuBar			m_wMenuBar;
	CMFCToolBar			m_wToolBar;
	CMFCStatusBar		m_wStatusBar;
	CMFCToolBarImages	m_UserImages;
	CFileView			m_wFileView;
	CClassView			m_wClassView;
	COutputWnd			m_wOutput;
	CPropertiesWnd		m_wProperties;
	CWizardDialog		m_dWizardDialog;

protected:
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void		OnViewCustomize();
	afx_msg LRESULT		OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void		OnApplicationLook(UINT id);
	afx_msg void		OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void		OnFileNew();
};


