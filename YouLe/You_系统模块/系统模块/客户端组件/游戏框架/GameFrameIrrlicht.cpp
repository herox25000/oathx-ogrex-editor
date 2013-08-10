#include "stdafx.h"
#include "Resource.h"
#include "GlobalOption.h"
#include "GameFrame.h"
#include "GameFrameIrrlicht.h"

IMPLEMENT_DYNAMIC(CGameFrameIrrlicht, CWnd)
CGameFrameIrrlicht::CGameFrameIrrlicht()
{
}

CGameFrameIrrlicht::~CGameFrameIrrlicht()
{
}


BEGIN_MESSAGE_MAP(CGameFrameIrrlicht, CWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CGameFrameIrrlicht::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
