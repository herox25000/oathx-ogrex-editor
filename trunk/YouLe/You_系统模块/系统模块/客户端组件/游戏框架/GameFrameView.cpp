#include "StdAfx.h"
#include "Resource.h"
#include "GlobalOption.h"
#include "GameFrameView.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
const int			CGameFrameView::m_nXFace=32;						//ͷ��߶�
const int			CGameFrameView::m_nYFace=32;						//ͷ����
const int			CGameFrameView::m_nXTimer=48;						//��ʱ����
const int			CGameFrameView::m_nYTimer=48;						//��ʱ����
const int			CGameFrameView::m_nXBorder=0;						//��ʱ����
const int			CGameFrameView::m_nYBorder=0;						//��ʱ����

//ʱ�䶨��
#define IDI_FLOWER_START			3000								//�ʻ���ʱ��
#define IDI_IRRLICHT_TIMER			3001								//3d engine render timer

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameView, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameView::CGameFrameView() : m_pReserve(NULL), m_nAnimeStep(30), m_pIUserFaceRes(NULL), m_pIrrlichtDevice(NULL), m_pVideoDriver(NULL)
{
	memset(&m_wTimer, 0, sizeof(m_wTimer));
	memset(&m_ptName, 0, sizeof(m_ptName));
	memset(&m_ptFace, 0, sizeof(m_ptFace));
	memset(&m_ptTimer, 0, sizeof(m_ptTimer));
	memset(&m_ptReady, 0, sizeof(m_ptReady));
	memset(&m_pUserItem, 0, sizeof(m_pUserItem));
}

//��������
CGameFrameView::~CGameFrameView()
{
	if (m_pIrrlichtDevice != NULL)
		m_pIrrlichtDevice->drop();
}

//�ӿڲ�ѯ
void * __cdecl CGameFrameView::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IGameFrameView,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IGameFrameView,Guid,dwQueryVer);
	return NULL;
}

//��ȡʱ��
WORD CGameFrameView::GetUserTimer(WORD wChairID)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR)
		return 0;

	return m_wTimer[wChairID];
}

//��ȡ���
const tagUserData * CGameFrameView::GetUserInfo(WORD wChairID)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR)
		return NULL;

	return m_pUserItem[wChairID];
}

//���ý���
void CGameFrameView::ResetData()
{

}

//���ýӿ�
bool CGameFrameView::SetUserFaceRes(IUnknownEx * pIUnknownEx)
{
	ASSERT(pIUnknownEx!=NULL);
	m_pIUserFaceRes=(IUserFaceRes *)pIUnknownEx->QueryInterface(IID_IUserFaceRes,VER_IUserFaceRes);
	return (m_pIUserFaceRes!=NULL);
}

//����ʱ��
bool CGameFrameView::SetUserTimer(WORD wChairID, WORD wTimer)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR)
		return 0;
	
	m_wTimer[wChairID]=wTimer;
	
	return true;
}

//�����û�
bool CGameFrameView::SetUserInfo(WORD wChairID, tagUserData * pUserItem)
{
	ASSERT(wChairID<MAX_CHAIR);
	if (wChairID>=MAX_CHAIR)
		return 0;

	m_pUserItem[wChairID]=pUserItem;

	return true;
}

//������Ϣ
int CGameFrameView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//��ʼ��
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	irr::SIrrlichtCreationParameters irrParam;
	irrParam.WindowId	= reinterpret_cast<void*>(m_hWnd);
	irrParam.DriverType	= irr::video::EDT_DIRECT3D9;
	m_pIrrlichtDevice	= irr::createDeviceEx(irrParam);
	if (m_pIrrlichtDevice)
	{
		m_pVideoDriver = m_pIrrlichtDevice->getVideoDriver();
		ASSERT(m_pVideoDriver != NULL);
		if (m_pVideoDriver)
		{
			SetTimer(IDI_IRRLICHT_TIMER, 15, NULL);
		}
	}

	return 0;
}

//�滭����
void CGameFrameView::OnPaint()
{
	CPaintDC dc(this);
}

//λ�ñ仯
void CGameFrameView::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
		
	if (cx > 0 && cy > 0 && GetSystemMetrics(SM_CXSCREEN)>cx)
	{
		CRect rc;
		GetClientRect(&rc);

		if (m_pVideoDriver)
			m_pVideoDriver->OnResize(irr::core::dimension2d<irr::u32>(cx, cy));
	}
}

//�����Ϣ
void CGameFrameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	__super::OnLButtonDown(nFlags, point);
}

//������Ϣ
void CGameFrameView::OnDestroy()
{
	KillTimer(IDI_IRRLICHT_TIMER);
	__super::OnDestroy();
}

//ʱ����Ϣ
void CGameFrameView::OnTimer(UINT nIDEvent)
{
	if (IDI_IRRLICHT_TIMER == nIDEvent)
	{
		if (m_pVideoDriver)
		{
			m_pVideoDriver->beginScene();
			DrawAll();
			m_pVideoDriver->endScene();
		}
	}
	__super::OnTimer(nIDEvent);
}

//��Ϸ�滭
bool CGameFrameView::DrawAll()
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
