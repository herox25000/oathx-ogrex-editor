#include "StdAfx.h"
#include "Resource.h"
#include "GameClientView.h"


BEGIN_MESSAGE_MAP(CGameClientView, CGameFrameView)
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameClientView::CGameClientView(void)
{
	
}

//��������
CGameClientView::~CGameClientView(void)
{
}

//������Ϣ
int CGameClientView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1)
		return -1;

	m_pImage = m_pVideoDriver->getTexture("2ddemo.png");
	m_pVideoDriver->makeColorKeyTexture(m_pImage, core::position2d<s32>(0,0));
	return 0;
}

//ʱ����Ϣ
void CGameClientView::OnTimer(UINT nIDEvent)
{
	__super::OnTimer(nIDEvent);
}

//��Ϸ�滭
bool CGameClientView::DrawAll()
{
	if (m_pVideoDriver == NULL)
		return 0;

	m_pVideoDriver->draw2DImage(m_pImage, core::position2d<s32>(0,0));
	m_pVideoDriver->draw2DRectangle(video::SColor(100,255,255,255),
		core::rect<s32>(0, 0, 300, 300));
	return true;
}

