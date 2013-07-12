#include "StdAfx.h"
#include "Resource.h"
#include "GamePropertyCtrl.h"
#include "GamePropertyManager.h"
#include ".\gamepropertyctrl.h"

//////////////////////////////////////////////////////////////////////////////////

#define  IDC_BT_LEFT_MOVE                 100                    //���ư�ť
#define  IDC_BT_RIGHT_MOVE                101                    //���ư�ť  

#define  PROERTY_BORDER_SPACE             62                     //���߱߾�

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGamePropertyCtrl, CWnd)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()

	//�Զ���Ϣ
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_WM_CREATE()

	ON_BN_CLICKED(IDC_BT_LEFT_MOVE, OnBtnLeftMoveClicked)
	ON_BN_CLICKED(IDC_BT_RIGHT_MOVE, OnBtnRightMoveClicked)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyCtrl::CGamePropertyCtrl()
{
	//״̬����
	m_bHovering=false;
	m_wDownItem=INVALID_WORD;
	m_wHoverItem=INVALID_WORD;

	//���ñ���
	m_pIGamePropertySink=NULL;
	m_pCurrPropertyItem=NULL;

	//����λ��
	m_nItemExcursion = 0;
	m_SizeImageItem.SetSize(0,0);
	ZeroMemory(&m_PropertyResource,sizeof(m_PropertyResource));

	//���ñ���
	m_cbStartIndex = 0;
	m_cbPropertyCount=0;
	ZeroMemory(m_pGamePropertyItem,sizeof(m_pGamePropertyItem));

	return;
}

//��������
CGamePropertyCtrl::~CGamePropertyCtrl()
{
	//֪ͨ�˳�
	if(m_pCurrPropertyItem!=NULL)
		m_pCurrPropertyItem->OnEventPerformCommand(CMD_CLOSE_WND,NULL);
}

//���ýӿ�
bool CGamePropertyCtrl::SetGamePropertySink(IUnknownEx * pIUnknownEx)
{
	//���ýӿ�
	if (pIUnknownEx!=NULL)
	{
		//��ѯ�ӿ�
		ASSERT(QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IGamePropertySink)!=NULL);
		m_pIGamePropertySink=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,IGamePropertySink);

		//�ɹ��ж�
		if (m_pIGamePropertySink==NULL) return false;
	}
	else m_pIGamePropertySink=NULL;

	return true;
}

//������Դ
bool CGamePropertyCtrl::SetPropertyResource(tagPropertyResource & PropertyResource)
{
	//���ñ���
	m_PropertyResource=PropertyResource;

	//������Դ
	CImage ImageGamePropertyItem;
	ImageGamePropertyItem.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageItem);

	//���ñ���
	m_SizeImageItem.SetSize(ImageGamePropertyItem.GetWidth(),ImageGamePropertyItem.GetHeight());

	//����ƫ��
	CImage ImageGamePropertyL;
	CImage ImageGamePropertyR;
	ImageGamePropertyL.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageL);
	ImageGamePropertyR.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageR);

	//���ñ���
	m_nItemExcursion = ImageGamePropertyR.GetWidth()-ImageGamePropertyL.GetWidth();

	return true;
}

//���õ���
bool CGamePropertyCtrl::SetGamePropertyInfo(tagPropertyInfo PropertyInfo[], BYTE cbPropertyCount, WORD wIssueArea)
{
	//���ñ���
	m_cbPropertyCount=0;
	m_cbStartIndex = 0;
	ZeroMemory(m_pGamePropertyItem,sizeof(m_pGamePropertyItem));

	//���õ���
	for (BYTE i=0;i<cbPropertyCount;i++)
	{
		if ((PropertyInfo[i].wIssueArea&wIssueArea)!=0)
		{
			//����ж�
			ASSERT(m_cbPropertyCount<CountArray(m_pGamePropertyItem));
			if (m_cbPropertyCount>=CountArray(m_pGamePropertyItem)) break;

			//��������
			CGamePropertyManager * pGamePropertyManager=CGamePropertyManager::GetInstance();
			CGamePropertyItem * pGamePropertyItem=pGamePropertyManager->CreatePropertyItem(PropertyInfo[i]);

			//�������
			if (pGamePropertyItem!=NULL)
			{
				//��������
				m_pGamePropertyItem[m_cbPropertyCount++]=pGamePropertyItem;
			}
		}
	}

	//�����ؼ�
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

	return true;
}

//�ı��¼�
VOID  CGamePropertyCtrl::OnSelectedUserItemChange(IClientUserItem * pIClintUserItem)
{
	//����У��
	if(pIClintUserItem==NULL) return;

	//�����ж�
	if(m_pCurrPropertyItem==NULL) return;

	//�¼�����
	m_pCurrPropertyItem->OnEventPerformCommand(CMD_USER_CHANGE,(VOID *)pIClintUserItem);
}

//����ж�
WORD CGamePropertyCtrl::SwitchItemFromPoint(CPoint MousePoint)
{
	//��ȡ��С
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CSize SizeExcursion=m_PropertyResource.SizeExcursion;
	CPoint PointExcursion=m_PropertyResource.PointExcursion;

	//����λ��
	INT nItemCount=(rcClient.Width()-PROERTY_BORDER_SPACE)/m_SizeImageItem.cx;
	INT nItemStart=(rcClient.Width()-nItemCount*m_SizeImageItem.cx-m_nItemExcursion)/2L+PointExcursion.x;

	//��Χ�ж�
	if ((MousePoint.x<nItemStart)||(MousePoint.x>(nItemStart+nItemCount*SizeExcursion.cx))) return INVALID_WORD;
	if ((MousePoint.y<PointExcursion.y)||(MousePoint.y>(PointExcursion.y+2L*SizeExcursion.cy))) return INVALID_WORD;

	//����ж�
	if (((MousePoint.x-nItemStart)%SizeExcursion.cx)>PROPERTY_IMAGE_CX) return INVALID_WORD;
	if (((MousePoint.y-PointExcursion.y)%SizeExcursion.cy)>PROPERTY_IMAGE_CY) return INVALID_WORD;

	//��������
	INT nXIndex=(MousePoint.x-nItemStart)/SizeExcursion.cx;
	INT nYIndex=(MousePoint.y-PointExcursion.y)/SizeExcursion.cy;

	//��������
	WORD wSwitchIndex=/*nYIndex*nItemCount+*/nXIndex;
	if (wSwitchIndex>=m_cbPropertyCount) return INVALID_WORD;

	return wSwitchIndex;
}

//�����ؼ�
VOID CGamePropertyCtrl::RectifyControl(INT nWidth, INT nHeight)
{
	//��������
	if(m_SizeImageItem.cx==0) return;
	INT nItemCount=(nWidth-PROERTY_BORDER_SPACE)/m_SizeImageItem.cx;

	//������Դ
	CImage ImageGamePropertyL;
	CImage ImageGamePropertyR;
	ImageGamePropertyL.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageL);
	ImageGamePropertyR.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageR);

	//�ƶ�׼��
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;	

	//������ť
	CRect rcButton(0,0,0,0);
	m_btLeftMove.GetWindowRect(&rcButton);
	DeferWindowPos(hDwp,m_btLeftMove,NULL,ImageGamePropertyL.GetWidth(),(nHeight-rcButton.Height())/2+1,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btRightMove,NULL,nWidth-ImageGamePropertyR.GetWidth()-rcButton.Width(),(nHeight-rcButton.Height())/2+1,0,0,uFlags|SWP_NOSIZE);

	//��������
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();
	
	//���ư�ť
	if(m_cbStartIndex+nItemCount>=m_cbPropertyCount)
		m_btRightMove.EnableWindow(FALSE);
	else
		m_btRightMove.EnableWindow(TRUE);

	//���ư�ť
	if(m_cbStartIndex==0)
		m_btLeftMove.EnableWindow(FALSE);
	else
		m_btLeftMove.EnableWindow(TRUE);

	return;
}

//�滭����
BOOL CGamePropertyCtrl::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//���û���
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SetTextColor(RGB(250,250,250));
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//������Դ
	CImage ImageGamePropertyL;
	CImage ImageGamePropertyM;
	CImage ImageGamePropertyR;
	CImage ImageGamePropertyItem;
	ImageGamePropertyL.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageL);
	ImageGamePropertyM.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageM);
	ImageGamePropertyR.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageR);
	ImageGamePropertyItem.LoadFromResource(m_PropertyResource.hResInstance,m_PropertyResource.uImageItem);

	//��������
	ASSERT(CSkinRenderManager::GetInstance()!=NULL);
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	//��Ⱦ��Դ
	pSkinRenderManager->RenderImage(ImageGamePropertyL);
	pSkinRenderManager->RenderImage(ImageGamePropertyM);
	pSkinRenderManager->RenderImage(ImageGamePropertyR);
	pSkinRenderManager->RenderImage(ImageGamePropertyItem);

	//�滭���
	ImageGamePropertyL.BitBlt(BufferDC,0,0);
	ImageGamePropertyR.BitBlt(BufferDC,rcClient.Width()-ImageGamePropertyR.GetWidth(),0);

	//��������
	INT nXStartPos=ImageGamePropertyL.GetWidth();
	INT nXConcludePos=rcClient.Width()-ImageGamePropertyR.GetWidth();

	//����λ��
	INT nItemCount=(rcClient.Width()-PROERTY_BORDER_SPACE)/m_SizeImageItem.cx;
	INT nItemStart=(rcClient.Width()-nItemCount*m_SizeImageItem.cx-m_nItemExcursion)/2;

	//�滭�м�
	for (INT nXPos=nXStartPos;nXPos<nXConcludePos;nXPos+=ImageGamePropertyM.GetWidth())
	{
		INT nCXDraw=__min(ImageGamePropertyM.GetWidth(),nXConcludePos-nXPos);
		ImageGamePropertyM.BitBlt(BufferDC,nXPos,0,nCXDraw,ImageGamePropertyM.GetHeight(),0,0);
	}

	//�滭����
	for (INT i=0;i<nItemCount;i++)
	{
		ImageGamePropertyItem.BitBlt(BufferDC,nItemStart+i*ImageGamePropertyItem.GetWidth(),0);
	}

	//��������
	CSize SizeExcursion=m_PropertyResource.SizeExcursion;
	CPoint PointExcursion=m_PropertyResource.PointExcursion;
	INT nXHoverPos=-1;
	INT nYHoverPos=-1;

	//�滭����
	for (BYTE i=0;i<m_cbPropertyCount;i++)
	{
		//Ч�����
		ASSERT(m_pGamePropertyItem[i]!=NULL);
		if (m_pGamePropertyItem[i]==NULL) break;

		//��ȡ��Ϣ
		tagPropertyImage PropertyImage;
		m_pGamePropertyItem[i]->GetImageInfo(PropertyImage);

		//������Դ
		CPngImage ImageProperty;
		ImageProperty.LoadImage(PropertyImage.hResInstance,PropertyImage.pszImageID);

		//�����ж�
		if(i<m_cbStartIndex) continue;
		BYTE cbIndex=i-m_cbStartIndex;

		//��Ŀ�ж�
		if(cbIndex>=nItemCount) break;

		//�滭����
		if (ImageProperty.IsNull()==false)
		{
			//��ȡ��С
			CSize SizeProperty;
			SizeProperty.SetSize(ImageProperty.GetWidth()/3L,ImageProperty.GetHeight());

			//����λ��
			INT nImagePos=0;
			if (m_wDownItem==cbIndex) nImagePos=SizeProperty.cx;
			if ((m_wDownItem!=cbIndex)&&(m_wHoverItem==cbIndex)) nImagePos=SizeProperty.cx*2;

			//�滭ͼ��
			INT nXDrawPos=(cbIndex%nItemCount)*SizeExcursion.cx+PointExcursion.x;
			INT nYDrawPos=PointExcursion.y;
			ImageProperty.DrawImage(pBufferDC,nItemStart+nXDrawPos,nYDrawPos,PROPERTY_IMAGE_CX,PROPERTY_IMAGE_CY,nImagePos,0,SizeProperty.cx,SizeProperty.cy);

			//�滭���
			if (m_wHoverItem==cbIndex)
			{
				//������Դ
				CPngImage ImageHoverFrame;
				ImageHoverFrame.LoadImage(GetModuleHandle(GAME_PROPERTY_DLL_NAME),TEXT("HOVER_FRAME"));

				//��ȡ��С
				CSize SizeHoverFrame;
				SizeHoverFrame.SetSize(ImageHoverFrame.GetWidth(),ImageHoverFrame.GetHeight());

				//�滭���
				nXHoverPos=nXDrawPos+(PROPERTY_IMAGE_CX-SizeHoverFrame.cx)/2L;
				nYHoverPos=nYDrawPos+(PROPERTY_IMAGE_CY-SizeHoverFrame.cy)/2L;
				ImageHoverFrame.DrawImage(pBufferDC,nItemStart+nXHoverPos,nYHoverPos);
			}
		}
	}

	//��ʾ
	if(m_wHoverItem != INVALID_WORD && nXHoverPos != -1 && nYHoverPos != -1)
	{
		//��ȡ��Ϣ
		LPCTSTR pszPropertyName=NULL;
		pszPropertyName = m_pGamePropertyItem[m_wHoverItem+m_cbStartIndex]->GetPropertyAttrib()->szPropertyName;

		//λ������
		if(m_wHoverItem <= nItemCount/2) nXHoverPos += (PROPERTY_IMAGE_CX+12);
		else nXHoverPos -= (PROPERTY_IMAGE_CX+12);
		nYHoverPos += (PROPERTY_IMAGE_CY/2)+15;

		//������Ϣ
		CRect rcTip(nXHoverPos,nYHoverPos,nXHoverPos+80,nYHoverPos+20);
		pBufferDC->FillSolidRect(&rcTip, RGB(240,240,240));
		pBufferDC->Draw3dRect(&rcTip,RGB(153,149,103),RGB(153,149,103));
		if(pszPropertyName)
		{
			pBufferDC->SetTextColor(RGB(0,0,0));
			pBufferDC->DrawText(pszPropertyName, -1, &rcTip, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}


	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//λ����Ϣ
VOID CGamePropertyCtrl::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	return;
}

//�����Ϣ
VOID CGamePropertyCtrl::OnMouseMove(UINT nFlags, CPoint MousePoint)
{
	__super::OnMouseMove(nFlags, MousePoint);

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
VOID CGamePropertyCtrl::OnLButtonUp(UINT nFlags, CPoint MousePoint)
{
	//�ͷŲ���
	ReleaseCapture();

	//��������
	if (m_wDownItem!=INVALID_WORD)
	{
		//��������
		WORD wLastDown=m_wDownItem;

		//���ñ���
		m_wDownItem=INVALID_WORD;
		m_wHoverItem=SwitchItemFromPoint(MousePoint);

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

		//��������
		if (wLastDown==m_wHoverItem)
		{
			//��������
			ASSERT(m_pGamePropertyItem[m_cbStartIndex+wLastDown]!=NULL);
			if(m_cbStartIndex+wLastDown>=m_cbPropertyCount) return;
			m_pCurrPropertyItem = m_pGamePropertyItem[m_cbStartIndex+wLastDown];
			m_pCurrPropertyItem->ShowBuyPropertyWnd(m_pIGamePropertySink);				
		}
	}

	return;
}

//�����Ϣ
VOID CGamePropertyCtrl::OnLButtonDown(UINT nFlags, CPoint MousePoint)
{
	//����˻�
	SetCapture();

	//��������
	if (m_wDownItem==INVALID_WORD)
	{
		//���ñ���
		m_wDownItem=SwitchItemFromPoint(MousePoint);

		//���½���
		if (m_wDownItem!=INVALID_WORD)
		{
			//���½���
			RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
		}
	}

	return;
}

//�����Ϣ
LRESULT CGamePropertyCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//���ñ���
	m_bHovering=false;

	//���ý���
	if (m_wHoverItem!=INVALID_WORD) 
	{
		//���ñ���
		m_wHoverItem=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
	}

	return 0;
}

//�����Ϣ
BOOL CGamePropertyCtrl::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//����ж�
	WORD wLastItem=m_wHoverItem;
	WORD wHoverItem=SwitchItemFromPoint(MousePoint);

	//��ͬ�ж�
	if (wHoverItem!=m_wHoverItem)
	{
		//���ñ���
		m_wHoverItem=wHoverItem;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
	}

	//���ù��
	if (m_wHoverItem!=INVALID_WORD)
	{
		SetCursor(LoadCursor(GetModuleHandle(GAME_PROPERTY_DLL_NAME),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//���ư�ť
VOID CGamePropertyCtrl::OnBtnLeftMoveClicked()
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	INT nItemCount=(rcClient.Width()-PROERTY_BORDER_SPACE)/m_SizeImageItem.cx;

	//��������
	if(m_cbStartIndex>0) m_cbStartIndex--;

	//�����ؼ�
	RectifyControl(rcClient.Width(),rcClient.Height());

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}

//���ư�ť
VOID CGamePropertyCtrl::OnBtnRightMoveClicked()
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	INT nItemCount=(rcClient.Width()-PROERTY_BORDER_SPACE)/m_SizeImageItem.cx;

	//��������
	if(m_cbStartIndex+nItemCount<m_cbPropertyCount)
		m_cbStartIndex++;

	//�����ؼ�
	RectifyControl(rcClient.Width(),rcClient.Height());

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);
}

//��������
int CGamePropertyCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//��������
	CRect rcCreate(0,0,0,0);

	//������ť
	m_btLeftMove.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BT_LEFT_MOVE);
	m_btRightMove.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_BT_RIGHT_MOVE);

	//������Դ
	m_btLeftMove.SetButtonImage(IDB_BT_LEFT,GetModuleHandle(GAME_PROPERTY_DLL_NAME),true,false);
    m_btRightMove.SetButtonImage(IDB_BT_RIGHT,GetModuleHandle(GAME_PROPERTY_DLL_NAME),true,false);

	//�����ؼ�
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////