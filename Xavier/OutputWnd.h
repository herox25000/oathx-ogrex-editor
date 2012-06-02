#pragma once

#include "ColorListBox.h"

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
class COutputList : public CColorListBox
{
public:
	/**
	 *
	 * \return 
	 */
	COutputList();

public:
	/**
	 *
	 * \return 
	 */
	virtual ~COutputList();

protected:
	/**
	 *
	 * \param pWnd 
	 * \param point 
	 */
	afx_msg void			OnContextMenu(CWnd* pWnd, CPoint point);

	/**
	 *
	 */
	afx_msg void			OnEditCopy();

	/**
	 *
	 */
	afx_msg void			OnEditClear();

	/**
	 *
	 */
	afx_msg void			OnViewOutput();

	DECLARE_MESSAGE_MAP()
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
class COutputWnd : public CDockablePane
{
public:
	/**
	 *
	 * \return 
	 */
	COutputWnd();

protected:
	CFont					m_Font;
	CMFCTabCtrl				m_wTabs;
	COutputList				m_wBuild;
	COutputList				m_wDebug;
	COutputList				m_wFind;

protected:
	/**
	 *
	 * \param wndListBox 
	 */
	void AdjustHorzScroll(CListBox& wndListBox);
	
public:
	/**
	 *
	 * \return 
	 */
	virtual ~COutputWnd();
	
	/** Êä³öLOGÏûÏ¢
	 *
	 * \param message 
	 * \param clr 
	 * \return 
	 */
	virtual void			OutputDebugMessage(const LPCTSTR& lpszMessage, COLORREF clr);
protected:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 * \param nType 
	 * \param cx 
	 * \param cy 
	 */
	afx_msg void			OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

