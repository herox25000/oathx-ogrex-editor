#pragma once

/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-22
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
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
	class EditorTool;
}

/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-01-22
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CPropertiesWnd : public CDockablePane
{
// ππ‘Ï
public:
	CPropertiesWnd();

	/**
	 *
	 */
	void						AdjustLayout();

public:
	/**
	 *
	 * \param bSet 
	 */
	void						SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}
	
	/**
	 *
	 */
	void						ClearProperty();

	/**
	 *
	 * \param lpszValue 
	 * \param lpszName 
	 * \param lpszHelp 
	 * \param bEnable 
	 * \param pParent 
	 * \return 
	 */
	template<typename T>
		CMFCPropertyGridProperty*	CreateProperty(LPCTSTR lpszName, T tValue, LPCTSTR lpszHelp, BOOL bEnable,
		CMFCPropertyGridProperty* pParent)
	{
		CMFCPropertyGridProperty* pProperty = new CMFCPropertyGridProperty(lpszName, (_variant_t)tValue, lpszHelp, NULL);
		pProperty->Enable(bEnable);
		if (pParent)
			pParent->AddSubItem(pProperty);
	
		return pProperty;
	}

	/**
	 *
	 * \param dwColour 
	 * \param fAlpha 
	 * \param lpszGroupName 
	 * \param lpszName 
	 * \param lpszHelp 
	 * \return 
	 */
	CMFCPropertyGridProperty*		CreateColourValueProperty(DWORD dwColour, float fAlpha, 
		LPCTSTR lpszGroupName, LPCTSTR lpszName, LPCTSTR lpszHelp);

	/**
	 *
	 * \param vPos 
	 * \param lpszGroupName 
	 * \param lpszHelp 
	 * \return 
	 */
	CMFCPropertyGridProperty*		CreateVector3ValueProperty(Ogre::Vector3 vPos, LPCTSTR lpszGroupName,
		LPCTSTR lpszHelp);

	/**
	 *
	 * \param pTool 
	 */
	void							CreateToolProperty(Ogre::EditorTool* pTool);
protected:
	CFont							m_fntPropList;
	CComboBox						m_wndObjectCombo;
	CPropertiesToolBar				m_wndToolBar;
	CMFCPropertyGridCtrl			m_wndPropList;

public:
	virtual ~CPropertiesWnd();

protected:
	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT			OnSelectEditor(WPARAM wParam, LPARAM lParam);

	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	afx_msg LRESULT			OnPropertyChanged(WPARAM wParam, LPARAM lParam);
protected:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void			OnSize(UINT nType, int cx, int cy);
	afx_msg void			OnExpandAllProperties();
	afx_msg void			OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void			OnSortProperties();
	afx_msg void			OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void			OnProperties1();
	afx_msg void			OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void			OnProperties2();
	afx_msg void			OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void			OnSetFocus(CWnd* pOldWnd);
	afx_msg void			OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();
};

