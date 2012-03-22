#pragma once

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
class CPropertiesToolBar : public CMFCToolBar
{
public:
	/**
	 *
	 * \param pTarget 
	 * \param bDisableIfNoHndler 
	 */
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	/**
	 *
	 * \return 
	 */
	virtual BOOL AllowShowOnList() const 
	{
		return FALSE; 
	}
};

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
class CPropertiesWnd : public CDockablePane
{
public:
	/**
	 *
	 * \return 
	 */
	CPropertiesWnd();

	/**
	 *
	 */
	void AdjustLayout();

public:
	/**
	 *
	 * \param bSet 
	 */
	void	SetVSDotNetLook(BOOL bSet)
	{
		m_wPropList.SetVSDotNetLook(bSet);
		m_wPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont						m_fntPropList;
	CComboBox					m_wObjectCombo;
	CPropertiesToolBar			m_wToolBar;
	CMFCPropertyGridCtrl		m_wPropList;

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CPropertiesWnd();

protected:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int					OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void				OnSize(UINT nType, int cx, int cy);

	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT				OnSelectEditor(WPARAM wParam, LPARAM lParam);

	/**
	 *
	 */
	afx_msg void				OnExpandAllProperties();

	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void				OnUpdateExpandAllProperties(CCmdUI* pCmdUI);

	/**
	 *
	 */
	afx_msg void				OnSortProperties();

	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void				OnUpdateSortProperties(CCmdUI* pCmdUI);

	/**
	 *
	 */
	afx_msg void				OnProperties1();

	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void				OnUpdateProperties1(CCmdUI* pCmdUI);

	/**
	 *
	 */
	afx_msg void				OnProperties2();

	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void				OnUpdateProperties2(CCmdUI* pCmdUI);

	/**
	 *
	 * \param pOldWnd 
	 */
	afx_msg void				OnSetFocus(CWnd* pOldWnd);

	/**
	 *
	 * \param uFlags 
	 * \param lpszSection 
	 */
	afx_msg void				OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	/**
	 *
	 */
	void InitPropList();

	/**
	 *
	 */
	void SetPropListFont();
};

