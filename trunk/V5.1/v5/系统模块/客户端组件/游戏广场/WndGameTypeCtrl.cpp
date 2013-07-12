#include "StdAfx.h"
#include "Resource.h"
#include "PlazaViewItem.h"
#include "GlobalUnits.h"
#include "WndGameTypeCtrl.h"

//////////////////////////////////////////////////////////////////////////////////

//常量定义
#define MIN_TYPE_ID					1									//最小类型
#define MAX_TYPE_ID					6									//最大类型

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWndGameTypeCtrl, CWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CWndGameTypeCtrl::CWndGameTypeCtrl()
{
	//活动信息
	m_bHovering=false;
	m_wItemDown=INVALID_WORD;
	m_wItemHover=INVALID_WORD;
	m_wItemActive=INVALID_WORD;

	//获取大小
	CPngImage ImageGameTypeItem;
	ImageGameTypeItem.LoadImage(AfxGetInstanceHandle(),TEXT("GAME_TYPE_ITEM"));
	m_SizeButton.SetSize(ImageGameTypeItem.GetWidth()/5,ImageGameTypeItem.GetHeight()/7);

	return;
}

//析构函数
CWndGameTypeCtrl::~CWndGameTypeCtrl()
{
}

//获取大小
VOID CWndGameTypeCtrl::GetControlSize(CSize & ResultSize)
{
	//设置变量
	ResultSize.cy=m_SizeButton.cy;
	ResultSize.cx=740;

	return;
}

//插入类型
VOID CWndGameTypeCtrl::InsertGameType(CGameTypeItem * pGameTypeItem)
{
	//效验参数
	ASSERT(pGameTypeItem!=NULL);
	ASSERT(pGameTypeItem->m_GameType.wTypeID>=MIN_TYPE_ID);
	ASSERT(pGameTypeItem->m_GameType.wTypeID<=MAX_TYPE_ID);

	//效验参数
	if (pGameTypeItem==NULL) return;
	if (pGameTypeItem->m_GameType.wTypeID<MIN_TYPE_ID) return;
	if (pGameTypeItem->m_GameType.wTypeID>MAX_TYPE_ID) return;

	//插入类型
	for (INT i=0;i<m_GameTypeItemArray.GetCount();i++)
	{
		//获取对象
		ASSERT(m_GameTypeItemArray[i]!=NULL);
		CGameTypeItem * pGameTypeTemp=m_GameTypeItemArray[i];

		//插入判断
		if (pGameTypeItem->m_GameType.wSortID<=pGameTypeTemp->m_GameType.wSortID)
		{
			m_GameTypeItemArray.InsertAt(i,pGameTypeItem);
			break;
		}
	}

	//默认插入
	if (i==m_GameTypeItemArray.GetCount())
	{
		m_GameTypeItemArray.Add(pGameTypeItem);
	}

	//激活子项
	if (m_wItemActive==INVALID_WORD)
	{
		m_wItemActive=0;
	}

	//调整控件
	if (m_hWnd!=NULL)
	{
		CSize SizeControl;
		GetControlSize(SizeControl);
		SetWindowPos(NULL,0,0,SizeControl.cx,SizeControl.cy,SWP_NOZORDER|SWP_NOMOVE);
	}

	return;
}

//对象索引
WORD CWndGameTypeCtrl::GetTypeItemIndex(WORD wTypeID)
{
	//搜索对象
	for (INT_PTR i=0;i<m_GameTypeItemArray.GetCount();i++)
	{
		//获取对象
		ASSERT(m_GameTypeItemArray[i]!=NULL);
		CGameTypeItem * pGameTypeItem=m_GameTypeItemArray[i];

		//标识判断
		if (pGameTypeItem->m_GameType.wTypeID==wTypeID)
		{
			return (WORD)i;
		}
	}

	return INVALID_WORD;
}

//对象索引
WORD CWndGameTypeCtrl::GetTypeItemIndex(CPoint MousePoint)
{
	//变量定义
	CRect rcClient(0,0,0,0);
	GetClientRect(rcClient);

	//变量定义
	WORD wItemIndex = INVALID_WORD;
	WORD wItemCount = m_GameTypeItemArray.GetCount();
	INT nXPitch = (m_GameTypeItemArray.GetCount()>1)?((rcClient.Width()-(wItemCount+1)*m_SizeButton.cx)/wItemCount):0;

	//对象索引
	if((MousePoint.x%(m_SizeButton.cx+nXPitch)<=m_SizeButton.cx))
	{
		wItemIndex=(WORD)(MousePoint.x/(m_SizeButton.cx+nXPitch));
		if (wItemIndex>=wItemCount+1) wItemIndex=INVALID_WORD;
	}

	return wItemIndex;
}

//绘画背景
BOOL CWndGameTypeCtrl::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建设备
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//加载资源
	CBitImage ImageItemBack;
	CPngImage ImageGameTypeItem;
	ImageItemBack.LoadFromResource(AfxGetInstanceHandle(),IDB_ITEM_BACK);
	ImageGameTypeItem.LoadImage(AfxGetInstanceHandle(),TEXT("GAME_TYPE_ITEM"));

	if(m_GameTypeItemArray.GetCount()>0)
	{
		INT nItemCount = (INT)m_GameTypeItemArray.GetCount();
		INT nXPitch = (nItemCount>1)?((rcClient.Width()-(nItemCount+1)*m_SizeButton.cx)/(nItemCount)):0;

		//绘画类型
		for (INT i=0;i<nItemCount+1;i++)
		{
			//变量定义
			ASSERT((i==0)||(m_GameTypeItemArray[i-1]!=NULL));
			WORD wTypeID=(i==0)?0:m_GameTypeItemArray[i-1]->m_GameType.wTypeID;

			//位置变量
			INT nXImagePos=0;
			INT nYImagePos=(wTypeID+1-MIN_TYPE_ID)*m_SizeButton.cy;

			//计算位置
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

			//绘画子项
			ImageItemBack.StretchBlt(BufferDC,i*(m_SizeButton.cx+nXPitch),0,m_SizeButton.cx+nXPitch,m_SizeButton.cy,0,0,m_SizeButton.cx,m_SizeButton.cy,SRCCOPY);
			ImageGameTypeItem.DrawImage(pBufferDC,i*(m_SizeButton.cx+nXPitch),0,m_SizeButton.cx,m_SizeButton.cy,nXImagePos,nYImagePos);
		}
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//鼠标消息
VOID CWndGameTypeCtrl::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//窗口位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//位置计算
	WORD wItemHover=GetTypeItemIndex(Point);

	//盘旋变量
	if (wItemHover!=m_wItemHover)
	{
		//设置变量
		m_wItemHover=wItemHover;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//进入判断
	if (m_bHovering==false)
	{
		//设置变量
		m_bHovering=true;

		//变量定义
		TRACKMOUSEEVENT TrackMouseEvent;
		ZeroMemory(&TrackMouseEvent,sizeof(TrackMouseEvent));

		//注册消息
		TrackMouseEvent.hwndTrack=m_hWnd;
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);

		//注册事件
		_TrackMouseEvent(&TrackMouseEvent);
	}

	return;
}

//鼠标消息
VOID CWndGameTypeCtrl::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//激活子项
	if ((m_wItemHover!=INVALID_WORD)&&(m_wItemHover==m_wItemDown))
	{
		//设置变量
		m_wItemActive=m_wItemDown;

		//获取对象
		ASSERT(CPlazaViewItem::GetInstance()!=NULL);
		CPlazaViewItem * pPlazaViewItem=CPlazaViewItem::GetInstance();

		//播放声音
		CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
		if(pGlobalUnits!=NULL)
		{
			pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
		}

		//设置视图
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

	//按起处理
	if (m_wItemDown!=INVALID_WORD)
	{
		//释放鼠标
		ReleaseCapture();

		//设置变量
		m_wItemDown=INVALID_WORD;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//鼠标消息
VOID CWndGameTypeCtrl::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//设置焦点
	SetFocus();

	//按下处理
	if (m_wItemHover!=INVALID_WORD)
	{
		//鼠标扑获
		SetCapture();

		//设置变量
		m_wItemDown=m_wItemHover;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//鼠标消息
LRESULT CWndGameTypeCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//设置状态
	m_bHovering=false;

	//更新界面
	if (m_wItemHover!=INVALID_WORD)
	{
		//设置变量
		m_wItemHover=INVALID_WORD;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
