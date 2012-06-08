#pragma once

#include "FileView.h"
#include "MeshView.h"
#include "OutputWnd.h"
#include "PropertySetWnd.h"
#include "WizardDialog.h"
#include "TerrainToolView.h"

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-03-08
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CMainFrame : public CFrameWndEx
{
protected:
	/**
	 *
	 * \return 
	 */
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	/**
	 *
	 * \param cs 
	 * \return 
	 */
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	/**
	 *
	 * \param nIDResource 
	 * \param dwDefaultStyle 
	 * \param pParentWnd 
	 * \param pContext 
	 * \return 
	 */
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
		CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

	/** Êä³öLOG
	 *
	 * \param message 
	 * \param clr 
	 * \return 
	 */
	virtual void OutputLogMessage(const LPCTSTR& lpszMessage, COLORREF clr);

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CMainFrame();

	/**
	 *
	 * \return 
	 */
	CString				GetPath() const {return m_dWizard.GetPath();}

	/**
	 *
	 * \return 
	 */
	CString				GetName() const {return m_dWizard.GetName();}
	/**
	 *
	 * \return 
	 */
	CFileView*			GetFileView() {return &m_wFileView;}

	/**
	 *
	 * \return 
	 */
	CPropertySetWnd*	GetPropertyWnd() {return &m_wProperties;}
#ifdef _DEBUG
	/**
	 *
	 */
	virtual void AssertValid() const;

	/**
	 *
	 * \param dc 
	 */
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CMFCMenuBar				m_wMenuBar;
	CMFCToolBar				m_wToolBar;
	CMFCStatusBar			m_wStatusBar;
	CMFCToolBarImages		m_UserImages;
	CFileView				m_wFileView;
	CMeshView				m_wMeshView;
	COutputWnd				m_wOutput;
	CPropertySetWnd			m_wProperties;
	CWizardDialog			m_dWizard;
	CTerrainToolView		m_wTerrainView;

protected:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 */
	afx_msg void			OnFileNew();

	/**
	 *
	 */
	afx_msg void			OnViewCustomize();

	/**
	 *
	 * \param wp 
	 * \param lp 
	 * \return 
	 */
	afx_msg LRESULT			OnToolbarCreateNew(WPARAM wp, LPARAM lp);

	/**
	 *
	 * \param id 
	 */
	afx_msg void			OnApplicationLook(UINT id);

	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void			OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	/**
	 *
	 * \return 
	 */
	BOOL	CreateDockingWindows();

	/**
	 *
	 * \param bHiColorIcons 
	 */
	void	SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	
};


