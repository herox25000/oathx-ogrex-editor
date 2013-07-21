#pragma once

#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "GameItemWnd.h"
#include "GameRoomWnd.h"

class CPlatformFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

protected:
	CGamePlazaDlg*					m_pGamePlazaDlg;

	//控件按钮
protected:
	CGdipButton						m_btMin;
	CGdipButton						m_btClose;
	
	CGameItemWnd					m_pTest;
	CGameRoomWnd					m_pRoom;
public:
	virtual BOOL					RectifyResource(int nWidth, int nHeight);
	virtual void					SetFrameSize(int nWidth, int nHeight);
protected:
	//命令函数
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:	
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//关闭消息
	VOID OnClose();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


