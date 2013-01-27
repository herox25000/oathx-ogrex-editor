#pragma once

#include "DecalImageListBox.h"
#include "BrushImageListBox.h"
#include "TerrainOptDialog.H"

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
	enum {
		ID_TERRAINTOOLVIEW	= 14, 
		ID_TERRAIN_DECAL	= 15, 
		ID_TERRAIN_BRUSH	= 16
	};
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
	CDecalImageListBox			m_ImageDecal;
	CBrushImageListBox			m_ImageBrush;
	CTerrainOptDialog			m_TOptDialog;
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

	/**
	 *
	 * \param pNMHDR 
	 * \param pResult 
	 */
	afx_msg void				OnTabPageSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
};


