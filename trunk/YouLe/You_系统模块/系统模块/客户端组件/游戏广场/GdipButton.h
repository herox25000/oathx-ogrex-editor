//
// GdipButton.h : Version 1.0 - see article at CodeProject.com
//
// Author:  Darren Sessions
//          
//
// Description:
//     GdipButton is a CButton derived control that uses GDI+ 
//     to support alternate image formats
//
// History
//     Version 1.0 - 2008 June 10
//     - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you 
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

// GdipButton.h : header file
//

class CGdiPlusBitmapResource;
/////////////////////////////////////////////////////////////////////////////
// CGdipButton window

class CGdipButton : public CButton
{
public:

	CGdipButton();
	virtual ~CGdipButton();

	// image types
	enum	{
				STD_TYPE	= 0,
				ALT_TYPE,
				DIS_TYPE
			};

	// create button
	BOOL CreateButton(CWnd* pParentWnd,UINT ResourceID, LPCTSTR pImageName,int dx,int dy,UINT WondowsID,UINT lStatusNum = 1);

	// sets the image type
	void SetImage(int type);

	BOOL LoadAltImage(UINT id, LPCTSTR pType,UINT lStatusNum=1);
	BOOL LoadStdImage(UINT id, LPCTSTR pType,UINT lStatusNum=1);

	// if false, disables the press state and uses grayscale image if it exists
	void EnableButton(BOOL bEnable = TRUE) { m_bIsDisabled = !bEnable; }

	// in toggle mode each press toggles between std and alt images
	void EnableToggle(BOOL bEnable = TRUE);

	// return the enable/disable state
	BOOL IsDisabled(void) {return (m_bIsDisabled == TRUE); }

	void SetBkGnd(CDC* pDC);

	void SetToolTipText(CString spText, BOOL bActivate = TRUE);
	void SetToolTipText(UINT nId, BOOL bActivate = TRUE);
	void SetHorizontal(bool ImagesAreLaidOutHorizontally = FALSE);
	void DeleteToolTip();


protected:

	void PaintBk(CDC* pDC);
	void PaintBtn(CDC* pDC);

	BOOL	m_bHaveAltImage;
	BOOL	m_bHaveBitmaps;

	BOOL	m_bIsDisabled;
	BOOL	m_bIsToggle;
	BOOL	m_bIsHovering;	//����״̬
	BOOL	m_bIsTracking;


	int		m_nCurType;			//��ǰģʽ�����ã��ı䣬����
	int		m_nStatusNum;		//״̬����

	CGdiPlusBitmapResource* m_pAltImage;
	CGdiPlusBitmapResource* m_pStdImage;

	CString			m_tooltext;
	CToolTipCtrl*	m_pToolTip;
	
	void	InitToolTip();

	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	//{{AFX_MSG(CGdipButton)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam) ;
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:

	CDC		m_dcBk;			// ��ť����
	
	CDC		m_dcStd;		// ����״̬
	CDC		m_dcStdP;		// ����״̬
	CDC		m_dcStdH;		// ����״̬

	CDC		m_dcAlt;		// ����״̬
	CDC		m_dcAltP;		// ����״̬
	CDC		m_dcAltH;		// ����״̬

	CDC		m_dcGS;			// ������״̬

	CDC*	m_pCurBtn;		// ��ǰʹ��

};
