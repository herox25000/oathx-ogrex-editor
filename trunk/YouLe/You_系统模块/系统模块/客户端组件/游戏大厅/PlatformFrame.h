#pragma once

#include "GamePlazaDlg.h"
#include "GdipButton.h"


class CPlatformFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

protected:
	CGamePlazaDlg*					m_pGamePlazaDlg;

	//�ؼ���ť
protected:
	CGdipButton						m_btMin;
	CGdipButton						m_btClose;

public:
	virtual BOOL					RectifyResource(int nWidth, int nHeight);
	virtual void					SetFrameSize(int nWidth, int nHeight);
protected:
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:	
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�ر���Ϣ
	VOID OnClose();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


