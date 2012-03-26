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

namespace Ogre
{
	class EventArgs;
	class BaseEditor;
}

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
class CPropertySetWnd : public CDockablePane
{
public:
	/**
	 *
	 * \return 
	 */
	CPropertySetWnd();

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

	/**
	 *
	 */
	void	InitPropList();

	/**
	 *
	 */
	void	SetPropListFont();

protected:
	CFont							m_fntPropList;
	CComboBox						m_wObjectCombo;
	CPropertiesToolBar				m_wToolBar;
	CMFCPropertyGridCtrl			m_wPropList;
	Ogre::BaseEditor*				m_pSelectEditor;

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CPropertySetWnd();

	/** ´´½¨ÑÕÉ«ÊìÏ¤
	 *
	 * \param dwColour 
	 * \param lpszName 
	 * \param lpszHelp 
	 * \return 
	 */
	CMFCPropertyGridProperty*		CreateColourValueProperty(UINT dwColour, UINT dwAlpha, 
		LPCTSTR lpszGroupName, LPCTSTR lpszName,  LPCTSTR lpszHelp);

	/**
	 *
	 * \param nMode 
	 * \param lpszName 
	 * \param lpszHelp 
	 * \return 
	 */
	CMFCPropertyGridProperty*		CreatePlygonModeProperty(int nMode, LPCTSTR lpszName, LPCTSTR lpszHelp);
	/**
	 *
	 * \param szWnd 
	 * \param lpszGroupName 
	 * \param lpszName 
	 * \param lpszHelp 
	 * \return 
	 */
	CMFCPropertyGridProperty*		CreateProperty(float fValue, LPCTSTR lpszName, LPCTSTR lpszHelp, BOOL bEnable, CMFCPropertyGridProperty* pParent);
protected:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int						OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void					OnSize(UINT nType, int cx, int cy);

	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT					OnSelectEditor(WPARAM wParam, LPARAM lParam);

	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT					OnPropertyChanged(WPARAM wParam, LPARAM lParam);

	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void					OnUpdateBaseProperty(CCmdUI* pCmdUI);
	
	/**
	 *
	 * \param pCmdUI 
	 */
	afx_msg void					OnUpdateEventDefine(CCmdUI* pCmdUI);

	/**
	 *
	 */
	afx_msg void					OnExpandAllProperties();

    /**
     *
     * \param pCmdUI 
     */
    afx_msg void					OnUpdateSortProperties(CCmdUI* pCmdUI);

	/**
	 *
	 */
	afx_msg void					OnSortProperties();

	/**
	 *
	 * \param pOldWnd 
	 */
	afx_msg void					OnSetFocus(CWnd* pOldWnd);

	/**
	 *
	 * \param uFlags 
	 * \param lpszSection 
	 */
	afx_msg void					OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()
};

