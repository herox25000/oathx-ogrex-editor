#pragma once

class GAME_FRAME_CLASS CGameFrameIrrlicht : public CWnd, public IGameFrameView
{
	DECLARE_DYNAMIC(CGameFrameIrrlicht)

public:
	CGameFrameIrrlicht();
	virtual ~CGameFrameIrrlicht();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


