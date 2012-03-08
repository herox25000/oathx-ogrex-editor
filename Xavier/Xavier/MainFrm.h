#pragma once

#include "FileView.h"
#include "MeshView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"

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

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CMFCMenuBar				m_wndMenuBar;
	CMFCToolBar				m_wndToolBar;
	CMFCStatusBar			m_wndStatusBar;
	CMFCToolBarImages		m_UserImages;
	CFileView				m_wndFileView;
	CMeshView				m_wndClassView;
	COutputWnd				m_wndOutput;
	CPropertiesWnd			m_wndProperties;

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
};


