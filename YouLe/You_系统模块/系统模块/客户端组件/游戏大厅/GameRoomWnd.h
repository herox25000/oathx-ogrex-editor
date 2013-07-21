#pragma once

typedef struct SRoomInfo
{
	INT			nLev;
	INT			nPlayerCount;
	INT			nMeasure;
	INT64		nScore;
	INT64		nMaxScore;
}*LPROOMINFO;

// 游戏房间控件
class CGameRoomWnd : public CWnd
{
	DECLARE_DYNAMIC(CGameRoomWnd)

public:
	CGameRoomWnd();
	virtual ~CGameRoomWnd();

	// create room wnd
	virtual BOOL	Create(UINT nID, INT nDestX, INT nDestY, 
		CWnd* pParent, HINSTANCE hResource, LPCTSTR lpszBackResourceName, LPCTSTR lpszBillResouceName);

	// set room info
	virtual void	SetRoomInfo(SRoomInfo* pInfo);
protected:
	CPngImage		m_PngBack;
	CPngImage		m_PngBill;
	
	// jion button
	CGdipButton		m_Join;
	SRoomInfo		m_Info;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnPaint();
};


