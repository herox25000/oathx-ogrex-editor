#include "StdAfx.h"
#include "Resource.h"
#include "PlazaViewItem.h"
#include "GlobalUnits.h"
#include "WndGameTypeCtrl.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
#define MIN_TYPE_ID					1									//��С����
#define MAX_TYPE_ID					6									//�������

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWndGameTypeCtrl, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CWndGameTypeCtrl::CWndGameTypeCtrl()
{
	//���Ϣ
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//��ȡ��С
	CPngImage ImageGameTypeItem;
	ImageGameTypeItem.LoadImage(AfxGetInstanceHandle(),TEXT("GAME_TYPE_ITEM"));
	m_SizeButton.SetSize(ImageGameTypeItem.GetWidth()/5,ImageGameTypeItem.GetHeight()/7);

	return;
}

//��������
CWndGameTypeCtrl::~CWndGameTypeCtrl()
{
}

//��ȡ��С
VOID CWndGameTypeCtrl::GetControlSize(CSize & ResultSize)
{
	//���ñ���
	ResultSize.cy=m_SizeButton.cy;
	ResultSize.cx=740;

	return;
}

//��������
VOID CWndGameTypeCtrl::InsertGameType(CGameTypeItem * pGameTypeItem)
{
	//Ч�����
	ASSERT(pGameTypeItem!=NULL);
	ASSERT(pGameTypeItem->m_GameType.wTypeID>=MIN_TYPE_ID);
	ASSERT(pGameTypeItem->m_GameType.wTypeID<=MAX_TYPE_ID);

	//Ч�����
	if (pGameTypeItem==NULL) return;
	if (pGameTypeItem->m_GameType.wTypeID<MIN_TYPE_ID) return;
	if (pGameTypeItem->m_GameType.wTypeID>MAX_TYPE_ID) return;

	//��������
	for (INT i=0;i<m_GameTypeItemArray.GetCount();i++)
	{
		//��ȡ����
		ASSERT(m_GameTypeItemArray[i]!=NULL);
		CGameTypeItem * pGameTypeTemp=m_GameTypeItemArray[i];

		//�����ж�
		if (pGameTypeItem->m_GameType.wSortID<=pGameTypeTemp->m_GameType.wSortID)
		{
			m_GameTypeItemArray.InsertAt(i,pGameTypeItem);
			break;
		}
	}

	//Ĭ�ϲ���
	if (i==m_GameTypeItemArray.GetCount())
	{
		m_GameTypeItemArray.Add(pGameTypeItem);
	}

	//��������
	if (m_wItemActive==INVALID_WORD)
	{
		m_wItemActive=0;
	}

	//�����ؼ�
	if (m_hWnd!=NULL)
	{
		CSize SizeControl;
		GetControlSize(SizeControl);
		SetWindowPos(NULL,0,0,SizeControl.cx,SizeControl.cy,SWP_NOZORDER|SWP_NOMOVE);
	}

	return;
}

//��������
WORD CWndGameTypeCtrl::GetTypeItemIndex(WORD wTypeID)
{
	//��������
	for (INT_PTR i=0;i<m_GameTypeItemArray.GetCount();i++)
	{
		//��ȡ����
		ASSERT(m_GameTypeItemArray[i]!=NULL);
		CGameTypeItem * pGameTypeItem=m_GameTypeItemArray[i];

		//��ʶ�ж�
		if (pGameTypeItem->m_GameType.wTypeID==wTypeID)
		{
			return (WORD)i;
		}
	}

	return INVALID_WORD;
}

//��������
WORD CWndGameTypeCtrl::GetTypeItemIndex(CPoint MousePoint)
{
	//��������
	CRect rcClient(0,0,0,0);
	GetClientRect(rcClient);

	//��������
	WORD wItemIndex = INVALID_WORD;
	WORD wItemCount = m_GameTypeItemArray.GetCount();
	INT nXPitch = (m_GameTypeItemArray.GetCount()>1)?((rcClient.Width()-(wItemCount+1)*m_SizeButton.cx)/wItemCount):0;

	//��������
	if((MousePoint.x%(m_SizeButton.cx+nXPitch)<=m_SizeButton.cx))
	{
		wItemIndex=(WORD)(MousePoint.x/(m_SizeButton.cx+nXPitch));
		if (wItemIndex>=wItemCount+1) wItemIndex=INVALID_WORD;
	}

	return wItemIndex;
}

//�滭����
BOOL CWndGameTypeCtrl::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//�����豸
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//������Դ
	CBitImage ImageItemBack;
	CPngImage ImageGameTypeItem;
	ImageItemBack.LoadFromResource(AfxGetInstanceHandle(),IDB_ITEM_BACK);
	ImageGameTypeItem.LoadImage(AfxGetInstanceHandle(),TEXT("GAME_TYPE_ITEM"));

	if(m_GameTypeItemArray.GetCount()>0)
	{
		INT nItemCount = (INT)m_GameTypeItemArray.GetCount();
		INT nXPitch = (nItemCount>1)?((rcClient.Width()-(nItemCount+1)*m_SizeButton.cx)/(nItemCount)):0;

		//�滭����
		for (INT i=0;i<nItemCount+1;i++)
		{
			//��������
			ASSERT((i==0)||(m_GameTypeItemArray[i-1]!=NULL));
			WORD wTypeID=(i==0)?0:m_GameTypeItemArray[i-1]->m_GameType.wTypeID;

			//λ�ñ���
			INT nXImagePos=0;
			INT nYImagePos=(wTypeID+1-MIN_TYPE_ID)*m_SizeButton.cy;

			//����λ��
			if (m_wItemActive==i)
			{
				if (m_wItemHover!=i) nXImagePos=m_SizeButton.cx*3L;
				if (m_wItemHover==i) nXImagePos=m_SizeButton.cx*4L;
			}
			else
			{
				if ((m_wItemHover==i)&&(m_wItemDown!=i)) nXImagePos=m_SizeButton.cx;
				if ((m_wItemHover==i)&&(m_wItemDown==i)) nXImagePos=m_SizeButton.cx*2L;
			}

			//�滭����
			ImageItemBack.StretchBlt(BufferDC,i*(m_SizeButton.cx+nXPitch),0,m_SizeButton.cx+nXPitch,m_SizeButton.cy,0,0,m_SizeButton.cx,m_SizeButton.cy,SRCCOPY);
			ImageGameTypeItem.DrawImage(pBufferDC,i*(m_SizeButton.cx+nXPitch),0,m_SizeButton.cx,m_SizeButton.cy,nXImagePos,nYImagePos);
		}
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//�����Ϣ
VOID CWndGameTypeCtrl::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//����λ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//λ�ü���
	WORD wItemHover=GetTypeItemIndex(Point);

	//��������
	if (wItemHover!=m_wItemHover)
	{
		//���ñ���
		m_wItemHover=wItemHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//�����ж�
	if (m_bHovering==false)
	{
		//���ñ���
		m_bHovering=true;

		//��������
		TRACKMOUSEEVENT TrackMouseEvent;
		ZeroMemory(&TrackMouseEvent,sizeof(TrackMouseEvent));

		//ע����Ϣ
		TrackMouseEvent.hwndTrack=m_hWnd;
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);

		//ע���¼�
		_TrackMouseEvent(&TrackMouseEvent);
	}

	return;
}

//�����Ϣ
VOID CWndGameTypeCtrl::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//��������
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover==m_wItemDown))
	{
		//���ñ���
		m_wItemActive=m_wItemDown;

		//��ȡ����
		ASSERT(CPlazaViewItem::GetInstance()!=NULL);
		CPlazaViewItem * pPlazaViewItem=CPlazaViewItem::GetInstance();

		//��������
		CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
		if(pGlobalUnits!=NULL)
		{
			pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
		}

		//������ͼ
		if (m_wItemActive>0)
		{
			CGameTypeItem * pGameTypeItem=m_GameTypeItemArray[m_wItemActive-1];
			pPlazaViewItem->ShowKindItemView(pGameTypeItem->m_GameType.wTypeID);			
		}
		else
		{
			pPlazaViewItem->ShowKindItemView(0);
		}
	}

	//������
	if (m_wItemDown!=INVALID_WORD)
	{
		//�ͷ����
		ReleaseCapture();

		//���ñ���
		m_wItemDown=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
VOID CWndGameTypeCtrl::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//���ý���
	SetFocus();

	//���´���
	if (m_wItemHover!=INVALID_WORD)
	{
		//����˻�
		SetCapture();

		//���ñ���
		m_wItemDown=m_wItemHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�����Ϣ
LRESULT CWndGameTypeCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//����״̬
	m_bHovering=false;

	//���½���
	if (m_wItemHover!=INVALID_WORD)
	{
		//���ñ���
		m_wItemHover=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
