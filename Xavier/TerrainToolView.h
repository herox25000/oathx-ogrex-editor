#pragma once


/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-06-09
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CTerrainToolView : public CDockablePane
{
	DECLARE_DYNAMIC(CTerrainToolView)

public:
	/**
	 *
	 * \return 
	 */
	CTerrainToolView();

	/**
	 *
	 * \return 
	 */
	virtual ~CTerrainToolView();

	/**
	 *
	 */
	void						AdjustLayout();

protected:
	CTabCtrl					m_TabCtrl;

protected:
	DECLARE_MESSAGE_MAP()

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
	 */
	afx_msg void				OnPaint();

	/**
	 *
	 * \param pOldWnd 
	 */
	afx_msg void				OnSetFocus(CWnd* pOldWnd);
};


