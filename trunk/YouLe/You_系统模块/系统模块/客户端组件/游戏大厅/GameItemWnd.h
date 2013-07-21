#pragma once

class CGameItemWnd : public CWnd
{
	DECLARE_DYNAMIC(CGameItemWnd)

public:
	CGameItemWnd();
	virtual ~CGameItemWnd();

	// create game item wnd
	virtual BOOL	Create(UINT nID, INT nDestX, INT nDestY, 
		CWnd* pParent, HINSTANCE hResource, LPCTSTR lpszBackResourceName, LPCTSTR lpszBillResouceName);

	virtual	BOOL	EnableWindow(BOOL bEnable /* = TRUE */);
protected:
	// back png image
	CPngImage		m_PngBack;
	// bill png image
	CPngImage		m_PngBill;

	CGdipButton		m_Regular;
	CGdipButton		m_JoinBtn;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
};

typedef CArray<CGameItemWnd*>	GameItemList;


