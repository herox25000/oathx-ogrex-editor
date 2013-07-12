#include "Stdafx.h"
#include "GamePlaza.h"
#include "DlgEnquire.h"
#include "PlatformFrame.h"

//////////////////////////////////////////////////////////////////////////////////

//圆角大小
#define ROUND_CX					5									//圆角宽度
#define ROUND_CY					5									//圆角高度

//阴影定义
#define SHADOW_CX					5									//阴影宽度
#define SHADOW_CY					5									//阴影高度

//屏幕位置
#define BORAD_SIZE					5									//边框大小
#define CAPTION_SIZE				79									//标题大小

//控制位置
#define SPLITTER_CX					0									//拆分宽度
#define LESS_LIST_CX				235									//列表宽度
#define FRAME_AFFICHE_CX			225									//框架公告

//屏幕限制
#define LESS_SCREEN_CY				740									//最小高度
#define LESS_SCREEN_CX				1024								//最小宽度
#define MAX_SCREEN_CX               1024                                //最大分辨率
#define MAX_SCREEN_CY               768                                 //最小分辨率           

//////////////////////////////////////////////////////////////////////////////////

//控制按钮
#define IDC_MIN						100									//最小按钮
#define IDC_MAX						101									//最大按钮
#define IDC_CLOSE					102									//关闭按钮

//控件标识
#define IDC_WEB_PUBLICIZE			300									//浏览控件
#define IDC_WEB_PUBLICIZE1          301                                 //浏览控件 
#define IDC_SKIN_SPLITTER			302									//拆分控件
#define IDC_SYSTEM_TRAY_ICON		303									//任务图标

//控件标识
#define IDC_GAME_TYPE_CTRL			311									//类型框架
#define IDC_USER_INFO_CTRL			312									//用户信息

//范围按钮
#define IDC_NAVIGATION				400									//导航按钮

//时间标识
#define IDI_FLASH_TRAY_ICON			10									//闪动图标

//////////////////////////////////////////////////////////////////////////////////
//静态变量

CPlatformFrame * CPlatformFrame::m_pPlatformFrame=NULL;					//框架指针

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPlatformFrame, CFrameWnd)

	//系统消息
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()

	//自定消息
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)
	ON_MESSAGE(WM_INSUREPLAZA_UPDATA, OnMessageInsureUpdate)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CPlatformFrame::CPlatformFrame()
{
	//状态变量
	m_bMaxShow=false;
	m_bRectify=false;
	m_bWhisperIcon=false;
	m_bShowLeftPanel=true;
	m_rcPlazaView.SetRect(0,0,0,0);
	m_rcServerView.SetRect(0,0,0,0);
	m_rcGameType.SetRect(0,0,0,0);
	m_rcToolBar.SetRect(0,0,0,0);
	m_rcNormalSize.SetRect(0,0,0,0);

	//任务组件
	m_MissionManager.InsertMissionItem(&m_MissionList);
	m_MissionManager.InsertMissionItem(&m_MissionLogon);

	//平台变量
	ASSERT(m_pPlatformFrame==NULL);
	if (m_pPlatformFrame==NULL) m_pPlatformFrame=this;

	//框架环绕
	tagEncircleResource	EncircleFrame;
	EncircleFrame.pszImageTL=TEXT("FRAME_TL");
	EncircleFrame.pszImageTM=TEXT("FRAME_TM");
	EncircleFrame.pszImageTR=TEXT("FRAME_TR");
	EncircleFrame.pszImageML=TEXT("FRAME_ML");
	EncircleFrame.pszImageMR=TEXT("FRAME_MR");
	EncircleFrame.pszImageBL=TEXT("FRAME_BL");
	EncircleFrame.pszImageBM=TEXT("FRAME_BM");
	EncircleFrame.pszImageBR=TEXT("FRAME_BR");
	m_FrameEncircle.InitEncircleResource(EncircleFrame,AfxGetInstanceHandle());

	//公告资源
	tagEncircleResource	EncircleAffiche;
	EncircleAffiche.pszImageTL=MAKEINTRESOURCE(IDB_AFFICHE_TL);
	EncircleAffiche.pszImageTM=MAKEINTRESOURCE(IDB_AFFICHE_TM);
	EncircleAffiche.pszImageTR=MAKEINTRESOURCE(IDB_AFFICHE_TR);
	EncircleAffiche.pszImageML=MAKEINTRESOURCE(IDB_AFFICHE_ML);
	EncircleAffiche.pszImageMR=MAKEINTRESOURCE(IDB_AFFICHE_MR);
	EncircleAffiche.pszImageBL=MAKEINTRESOURCE(IDB_AFFICHE_BL);
	EncircleAffiche.pszImageBM=MAKEINTRESOURCE(IDB_AFFICHE_BM);
	EncircleAffiche.pszImageBR=MAKEINTRESOURCE(IDB_AFFICHE_BR);
	m_AfficheEncircle.InitEncircleResource(EncircleAffiche,AfxGetInstanceHandle());

	//子项资源
	tagEncircleResource	EncircleItemFrame;
	EncircleItemFrame.pszImageTL=MAKEINTRESOURCE(IDB_ITEM_FRAME_TL);
	EncircleItemFrame.pszImageTM=MAKEINTRESOURCE(IDB_ITEM_FRAME_TM);
	EncircleItemFrame.pszImageTR=MAKEINTRESOURCE(IDB_ITEM_FRAME_TR);
	EncircleItemFrame.pszImageML=MAKEINTRESOURCE(IDB_ITEM_FRAME_ML);
	EncircleItemFrame.pszImageMR=MAKEINTRESOURCE(IDB_ITEM_FRAME_MR);
	EncircleItemFrame.pszImageBL=MAKEINTRESOURCE(IDB_ITEM_FRAME_BL);
	EncircleItemFrame.pszImageBM=MAKEINTRESOURCE(IDB_ITEM_FRAME_BM);
	EncircleItemFrame.pszImageBR=MAKEINTRESOURCE(IDB_ITEM_FRAME_BR);
	m_ItemFrameEncircle.InitEncircleResource(EncircleItemFrame,AfxGetInstanceHandle());

	//指针变量
	m_pServerViewItem = NULL;

	return;
}

//析构函数
CPlatformFrame::~CPlatformFrame()
{
	//平台变量
	ASSERT(m_pPlatformFrame==this);
	if (m_pPlatformFrame==this) m_pPlatformFrame=NULL;

	//修改分辨率
	ChangeScreenSetting(m_ScreenMetrics.cx,m_ScreenMetrics.cy,false);

	return;
}

//接口查询
VOID * CPlatformFrame::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ICustomFaceEvent,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ICustomFaceEvent,Guid,dwQueryVer);
	return NULL;
}

//下载失败
VOID CPlatformFrame::OnEventSystemFace(DWORD dwUserID, WORD wFaceID)
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//自我数据
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//设置变量
		pGlobalUserData->wFaceID=wFaceID;

		//清理数据
		pGlobalUserData->dwCustomID=0L;
		ZeroMemory(&pGlobalUserData->CustomFaceInfo,sizeof(pGlobalUserData->CustomFaceInfo));

		//发送事件
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	return;
}

//头像数据
VOID CPlatformFrame::OnEventCustomFace(DWORD dwUserID, DWORD dwCustomID, tagCustomFaceInfo & CustomFaceInfo)
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//自我数据
	if (pGlobalUserData->dwUserID==dwUserID)
	{
		//设置变量
		pGlobalUserData->dwCustomID=dwCustomID;
		CopyMemory(&pGlobalUserData->CustomFaceInfo,&CustomFaceInfo,sizeof(CustomFaceInfo));

		//发送事件
		CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
		if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);
	}

	//当前房间
	if ( m_pServerViewItem != NULL)
	{
		m_pServerViewItem->UpdateUserCustomFace(dwUserID,dwCustomID,CustomFaceInfo);
	}

	return;
}

//获取通知
VOID CPlatformFrame::OnGameItemFinish()
{
	//显示列表
	m_PlazaViewItem.ShowKindItemView(0);

	return;
}

//获取通知
VOID CPlatformFrame::OnGameKindFinish(WORD wKindID)
{
	return;
}

//更新通知
VOID CPlatformFrame::OnGameItemUpdateFinish()
{
	return;
}

//插入通知
VOID CPlatformFrame::OnGameItemInsert(CGameListItem * pGameListItem)
{
	//效验参数
	ASSERT(pGameListItem!=NULL);
	if (pGameListItem==NULL) return;

	//插入处理
	switch (pGameListItem->GetItemGenre())
	{
	case ItemGenre_Type:	//游戏种类
		{
			//插入种类
			m_WndGameTypeCtrl.InsertGameType((CGameTypeItem *)pGameListItem);

			break;
		}
	case ItemGenre_Kind:	//游戏类型
		{
			break;
		}
	case ItemGenre_Server:	//游戏房间
		{
			break;
		}
	}

	return;
}

//更新通知
VOID CPlatformFrame::OnGameItemUpdate(CGameListItem * pGameListItem)
{
	return;
}

//删除通知
VOID CPlatformFrame::OnGameItemDelete(CGameListItem * pGameListItem)
{
	return;
}

//消息过虑
BOOL CPlatformFrame::PreTranslateMessage(MSG * pMsg)
{
	//提示消息
	if (m_ToolTipCtrl.m_hWnd!=NULL)
	{
		m_ToolTipCtrl.RelayEvent(pMsg);
	}

	return __super::PreTranslateMessage(pMsg);
}

//命令函数
BOOL CPlatformFrame::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//变量定义
	UINT nCommandID=LOWORD(wParam);

	//功能按钮
	switch (nCommandID)
	{
	case IDC_MIN:				//最小按钮
		{
			ShowWindow(SW_MINIMIZE);
			return TRUE;
		}
	case IDC_MAX:
		{
			if(m_bMaxShow==false)
			{
				MaxSizeWindow();				
			}
			else
			{
				RestoreWindow();
			}			

			return TRUE;
		}
	case IDC_CLOSE:				//关闭按钮
		{
			PostMessage(WM_CLOSE,0,0);
			return TRUE;
		}
	case IDC_NAVIGATION+2:		//上传头像
		{
			//显示窗口
			CDlgCustomFace DlgCustomFace;
			DlgCustomFace.SetCustomFaceEvent(QUERY_OBJECT_PTR_INTERFACE(CPlatformFrame::GetInstance(),IUnknownEx));

			//显示窗口
			DlgCustomFace.DoModal();
						
			return TRUE;
		}
	case IDC_NAVIGATION+3:		//锁定本机
		{
			//显示窗口
			CDlgLockMachine DlgLockMachine;
			DlgLockMachine.DoModal();

			return TRUE;
		}
	case IDC_NAVIGATION+0:
	case IDC_NAVIGATION+1:
	case IDC_NAVIGATION+4:
	case IDC_NAVIGATION+5:
	case IDC_NAVIGATION+6:		//导航按钮
		{
			//获取指针
			CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
			ASSERT(pGlobalUnits!=NULL);

			//构造地址
			TCHAR szNavigation[256]=TEXT("");
			_sntprintf(szNavigation,CountArray(szNavigation),TEXT("%s%sNavigation%ld.aspx"),szPlatformLink,pGlobalUnits->GetValidateParamAsString(),(nCommandID-IDC_NAVIGATION)+1);

			//连接地址
			ShellExecute(NULL,TEXT("OPEN"),szNavigation,NULL,NULL,SW_NORMAL);

			return TRUE;
		}
	}

	//菜单命令
	switch (nCommandID)
	{
	case IDM_USER_LOGON:		//用户登录
		{
			m_MissionLogon.ShowLogon();

			return TRUE;
		}
	case IDM_SWITCH_ACCOUNTS:	//切换帐号
		{
			//切换询问
			if ( m_pServerViewItem != NULL )
			{
				CInformation Information(this);
				if (Information.ShowMessageBox(TEXT("游戏房间即将关闭，确实要“切换帐号”吗？ "),MB_YESNO)!=IDYES) return TRUE;
			}

			//全局设置
			CGlobalUnits::GetInstance()->DeleteUserCookie();
			CGlobalUserInfo::GetInstance()->ResetUserInfoData();

			//发送事件
			CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
			if (pPlatformEvent!=NULL) pPlatformEvent->SendPlatformEvent(EVENT_USER_LOGOUT,0L);

			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//调整控件
VOID CPlatformFrame::RectifyControl(INT nWidth, INT nHeight)
{
	//状态判断
	if ((nWidth==0)||(nHeight==0)) return;

	//拆分位置
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//环绕信息
	tagEncircleInfo EncircleInfoFrame;
	tagEncircleInfo EncircleInfoAffiche;
	tagEncircleInfo EncircleInfoItemFrame;
	m_FrameEncircle.GetEncircleInfo(EncircleInfoFrame);
	m_AfficheEncircle.GetEncircleInfo(EncircleInfoAffiche);
	m_ItemFrameEncircle.GetEncircleInfo(EncircleInfoItemFrame);

	//获取位置
	ScreenToClient(&rcSplitter);

	//拆分范围
	INT nLessPos=nWidth*28/100,nMaxPos=nWidth/2;
	if (nLessPos>=LESS_LIST_CX) nLessPos=LESS_LIST_CX;

	//拆分控件
	if (m_bShowLeftPanel==true)
	{
		rcSplitter.left=nLessPos;
		rcSplitter.right=rcSplitter.left+SPLITTER_CX;
	}
	else 
	{
		//拆分位置
		rcSplitter.left=EncircleInfoFrame.nLBorder;
		rcSplitter.right=rcSplitter.left+SPLITTER_CX;
	}

	//拆分范围
	m_SkinSplitter.SetSplitterRange(nLessPos,nMaxPos);

	//调整位置
	if ((nWidth!=0)&&(nHeight!=0))
	{
		if (rcSplitter.left<EncircleInfoFrame.nLBorder)
		{
			rcSplitter.left=EncircleInfoFrame.nLBorder;
			rcSplitter.right=rcSplitter.left+SPLITTER_CX;
		}
		if (rcSplitter.right>nMaxPos)
		{
			rcSplitter.right=nMaxPos;
			rcSplitter.left=rcSplitter.right-SPLITTER_CX;
		}
	}

	//位置调整
	rcSplitter.top=EncircleInfoFrame.nTBorder;
	rcSplitter.bottom=nHeight-EncircleInfoFrame.nBBorder;

	//控件位置
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);

	//中间框架
	CRect rcMiddleFrame(EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder,nWidth-EncircleInfoFrame.nRBorder,EncircleInfoFrame.nTBorder+33);

	//设置区域
	m_MiddleFrameControl.SetControlRect(rcMiddleFrame);	

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//控制按钮
	DeferWindowPos(hDwp,m_btMin,NULL,nWidth-86,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btMax,NULL,nWidth-60,3,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btClose,NULL,nWidth-34,3,0,0,uFlags|SWP_NOSIZE);

	//导航按钮
	CRect rcNavigation;
	m_btNavigation[0].GetWindowRect(&rcNavigation);

	//导航按钮
	INT nNavigationArea=rcNavigation.Width()*CountArray(m_btNavigation);
	INT nSpace=__min(__max((nWidth-nNavigationArea-328)/(CountArray(m_btNavigation)-1),0),33);

	//导航按钮
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		INT nIndex=CountArray(m_btNavigation)-i;
		INT nXExcursion=nWidth-(rcNavigation.Width()+nSpace)*nIndex-6;
		DeferWindowPos(hDwp,m_btNavigation[i],NULL,nXExcursion,39,0,0,uFlags|SWP_NOSIZE);
	}

	//视图位置
	m_rcPlazaView.left= rcSplitter.right+EncircleInfoItemFrame.nLBorder;
	m_rcPlazaView.top=EncircleInfoFrame.nTBorder+EncircleInfoItemFrame.nTBorder+rcMiddleFrame.Height();
	m_rcPlazaView.right=nWidth-EncircleInfoFrame.nRBorder-EncircleInfoItemFrame.nRBorder;
	m_rcPlazaView.bottom=nHeight-EncircleInfoFrame.nBBorder-EncircleInfoItemFrame.nBBorder;

	//游戏广场
	DeferWindowPos(hDwp,m_PlazaViewItem,NULL,m_rcPlazaView.left,m_rcPlazaView.top,m_rcPlazaView.Width(),m_rcPlazaView.Height(),uFlags);

	//视图位置
	m_rcServerView.left=rcSplitter.right;
	m_rcServerView.top=EncircleInfoFrame.nTBorder+rcMiddleFrame.Height()-1;
	m_rcServerView.right=nWidth-EncircleInfoFrame.nRBorder;
	m_rcServerView.bottom=nHeight-EncircleInfoFrame.nBBorder;

	//房间视图
	if( m_pServerViewItem!=NULL )
	{
		DeferWindowPos(hDwp,m_pServerViewItem->m_hWnd,NULL,m_rcServerView.left,m_rcServerView.top,m_rcServerView.Width(),m_rcServerView.Height(),uFlags);
	}

	//类型框架
	CSize SizeGameTypeCtrl;
	m_WndGameTypeCtrl.GetControlSize(SizeGameTypeCtrl);

	//游戏类型
	m_rcGameType.left = rcSplitter.right+10;
	m_rcGameType.top = EncircleInfoFrame.nTBorder+EncircleInfoItemFrame.nTBorder-SizeGameTypeCtrl.cy+22;
	m_rcGameType.right = m_rcGameType.left+SizeGameTypeCtrl.cx;
	m_rcGameType.bottom = m_rcGameType.top+SizeGameTypeCtrl.cy;

	//游戏类型
	DeferWindowPos(hDwp,m_WndGameTypeCtrl,NULL,m_rcGameType.left,m_rcGameType.top,m_rcGameType.Width(),m_rcGameType.Height(),uFlags);

	//变量定义
	CRect rcServerToolBar;
	m_ServerToolBar.GetWindowRect(rcServerToolBar);

	//工具栏
	m_rcToolBar.left = rcSplitter.right+344;
	m_rcToolBar.top = EncircleInfoFrame.nTBorder+EncircleInfoItemFrame.nTBorder+rcMiddleFrame.Height()-SizeGameTypeCtrl.cy-13;
	m_rcToolBar.right = m_rcToolBar.left+rcServerToolBar.Width();
	m_rcToolBar.bottom = m_rcToolBar.top+rcServerToolBar.Height();

	//房间工具栏
	DeferWindowPos(hDwp,m_ServerToolBar,NULL,m_rcToolBar.left,m_rcToolBar.top,m_rcToolBar.Width(),m_rcToolBar.Height(),uFlags);

	//其他控件
	DeferWindowPos(hDwp,m_SkinSplitter,NULL,rcSplitter.left,rcSplitter.top,rcSplitter.Width(),rcSplitter.Height(),uFlags);
	DeferWindowPos(hDwp,m_WndUserInfoCtrl,NULL,EncircleInfoFrame.nLBorder,EncircleInfoFrame.nTBorder+rcMiddleFrame.Height(),rcSplitter.left-EncircleInfoFrame.nLBorder,rcUserInfoCtrl.Height(),uFlags);

	DeferWindowPos(hDwp,m_PlatFormNoticePublicize,NULL,247,9,530,18,uFlags);
	

	//结束调整
	LockWindowUpdate();
	EndDeferWindowPos(hDwp);
	UnlockWindowUpdate();
	

	//更新界面
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	return;
}

//调整资源
VOID CPlatformFrame::RectifyResource(INT nWidth, INT nHeight)
{
	//调整判断
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//框架位置
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX,SHADOW_CY,nWidth-SHADOW_CX,nHeight-SHADOW_CY);

		//窗口区域
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//设置区域
		SetWindowRgn(RegionWindow,TRUE);

		//分层窗口
		if (m_SkinLayered.m_hWnd!=NULL)
		{
			//建立缓冲
			CImage ImageBuffer;
			ImageBuffer.Create(nWidth,nHeight,32);

			//创建 DC
			CImageDC ImageDC(ImageBuffer);
			CDC * pBufferDC=CDC::FromHandle(ImageDC);

			//绘画界面
			DrawControlView(pBufferDC,nWidth,nHeight);

			//更新分层
			m_SkinLayered.InitLayeredArea(pBufferDC,255,rcFrame,CPoint(ROUND_CX,ROUND_CX),false);
		}
	}

	return;
}

//绘画界面
VOID CPlatformFrame::DrawControlView(CDC * pDC, INT nWidth, INT nHeight)
{
	//框架位置
	tagEncircleInfo FrameEncircleInfo;
	tagEncircleInfo ItemFrameEncircleInfo;
	m_FrameEncircle.GetEncircleInfo(FrameEncircleInfo);
	m_ItemFrameEncircle.GetEncircleInfo(ItemFrameEncircleInfo);

	//拆分位置
	CRect rcSplitter;
	m_SkinSplitter.GetWindowRect(&rcSplitter);

	//位置转换
	ScreenToClient(&rcSplitter);

	//控件位置
	CRect rcUserInfoCtrl;
	m_WndUserInfoCtrl.GetWindowRect(&rcUserInfoCtrl);

	//控件位置
	CRect rcMiddleFrame;
	m_MiddleFrameControl.GetControlRect(rcMiddleFrame);

	//框架区域
	CRect rcFrame;
	rcFrame.SetRect(0,0,nWidth,nHeight);

	//公告位置
	CRect rcAffiche;
	rcAffiche.right=rcSplitter.left;
	rcAffiche.left=FrameEncircleInfo.nLBorder;
	rcAffiche.top=FrameEncircleInfo.nTBorder+rcMiddleFrame.Height()+rcUserInfoCtrl.Height();
	rcAffiche.bottom=nHeight-FrameEncircleInfo.nBBorder;

	//子项区域
	CRect rcItemFrame;
	rcItemFrame.left=rcSplitter.right;
	rcItemFrame.top=FrameEncircleInfo.nTBorder+rcMiddleFrame.Height();
	rcItemFrame.right=nWidth-FrameEncircleInfo.nRBorder;
	rcItemFrame.bottom=nHeight-FrameEncircleInfo.nBBorder;

	//绘画框架
	m_FrameEncircle.DrawEncircleFrame(pDC,rcFrame);
	m_ItemFrameEncircle.DrawEncircleFrame(pDC,rcItemFrame);
	m_MiddleFrameControl.OnDrawFrameControl(pDC);

	//加载资源
	CPngImage StationLogo;
	StationLogo.LoadImage(AfxGetInstanceHandle(),TEXT("PLATFORM_LOGO"));

	//绘画标志
	StationLogo.DrawImage(pDC,SHADOW_CX+8,SHADOW_CY+34);

	//绘画广告
	if (m_bShowLeftPanel==true && m_ImageFrame.IsNull()==false)
	{
		//绘制框架
		m_AfficheEncircle.DrawEncircleFrame(pDC,rcAffiche);

		//获取大小
		CSize SizeImageFrame;
		SizeImageFrame.SetSize(m_ImageFrame.GetWidth(),m_ImageFrame.GetHeight());

		//绘画广告
		INT nXPos=rcAffiche.left+8;
		INT nYPos=rcAffiche.top+9;

		//绘画广告
		pDC->SetStretchBltMode(HALFTONE);
		m_ImageFrame.StretchBlt(pDC->m_hDC,nXPos,nYPos,rcAffiche.Width()-14,rcAffiche.Height()-17,0,0,SizeImageFrame.cx,SizeImageFrame.cy);
	}

	return;
}

//激活房间
bool CPlatformFrame::ActiveServerViewItem()
{
	//激活判断
	ASSERT(m_pServerViewItem!=NULL);
	if (m_pServerViewItem==NULL) return false;

	//隐藏面板
	ShowPlazaLeftPanel(false);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//游戏广场
	DeferWindowPos(hDwp,m_PlazaViewItem,NULL,m_rcPlazaView.left,m_rcPlazaView.top,m_rcPlazaView.Width(),m_rcPlazaView.Height(),uFlags|SWP_HIDEWINDOW);
	DeferWindowPos(hDwp,m_pServerViewItem->m_hWnd,NULL,m_rcServerView.left,m_rcServerView.top,m_rcServerView.Width(),m_rcServerView.Height(),uFlags|SWP_SHOWWINDOW);
	DeferWindowPos(hDwp,m_ServerToolBar,NULL,m_rcToolBar.left,m_rcToolBar.top,m_rcToolBar.Width(),m_rcToolBar.Height(),uFlags|SWP_SHOWWINDOW);
	DeferWindowPos(hDwp,m_WndGameTypeCtrl,NULL,m_rcGameType.left,m_rcGameType.top,m_rcGameType.Width(),m_rcGameType.Height(),uFlags|SWP_HIDEWINDOW);

	//结束调整
	EndDeferWindowPos(hDwp);

	//设置标识
	m_MiddleFrameControl.SetAfficheTitleFlag(false);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	return true;
}

//删除房间
bool CPlatformFrame::DeleteServerViewItem()
{
	//激活判断
	ASSERT(m_pServerViewItem!=NULL);
	if (m_pServerViewItem==NULL) return false;

	//显示面板
	ShowPlazaLeftPanel(true);

	//移动准备
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;

	//游戏广场
	DeferWindowPos(hDwp,m_PlazaViewItem,NULL,m_rcPlazaView.left,m_rcPlazaView.top,m_rcPlazaView.Width(),m_rcPlazaView.Height(),uFlags|SWP_SHOWWINDOW);
	DeferWindowPos(hDwp,m_pServerViewItem->m_hWnd,NULL,m_rcServerView.left,m_rcServerView.top,m_rcServerView.Width(),m_rcServerView.Height(),uFlags|SWP_HIDEWINDOW);
	DeferWindowPos(hDwp,m_ServerToolBar,NULL,m_rcToolBar.left,m_rcToolBar.top,m_rcToolBar.Width(),m_rcToolBar.Height(),uFlags|SWP_HIDEWINDOW);
	DeferWindowPos(hDwp,m_WndGameTypeCtrl,NULL,m_rcGameType.left,m_rcGameType.top,m_rcGameType.Width(),m_rcGameType.Height(),uFlags|SWP_SHOWWINDOW);

	//结束调整
	EndDeferWindowPos(hDwp);

	//设置标识
	m_MiddleFrameControl.SetAfficheTitleFlag(true);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_ERASE|RDW_INVALIDATE);

	//销毁窗口
	m_pServerViewItem->DestroyWindow();
	m_pServerViewItem = NULL;

	return true;
}

//进入房间
bool CPlatformFrame::EntranceServerItem(CGameServerItem * pGameServerItem)
{
	//效验参数
	ASSERT(pGameServerItem!=NULL);
	if (pGameServerItem==NULL) return NULL;

	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//登录判断
	if (pGlobalUserData->dwUserID==0L) return NULL;

	//变量定义
	tagGameServer * pGameServer=&pGameServerItem->m_GameServer;
	tagGameKind * pGameKind=&pGameServerItem->m_pGameKindItem->m_GameKind;

	//当前判断
	if ( m_pServerViewItem!=NULL)
	{
		//提示消息
		TCHAR szBuffer[256]=TEXT("");
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("正在进入 [ %s ] 游戏房间中，请稍后等待片刻..."),m_pServerViewItem->GetServerName());

		//提示消息
		CInformation Information(this);
		Information.ShowMessageBox(szBuffer,MB_OK|MB_ICONWARNING,30);

		return false;
	}

	//安装判断
	if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
	{
		//获取版本
		CGameKindItem * pGameKindItem=pGameServerItem->m_pGameKindItem;
		CWHService::GetModuleVersion(pGameKind->szProcessName,pGameKindItem->m_dwProcessVersion);

		//下载游戏
		if (pGameServerItem->m_pGameKindItem->m_dwProcessVersion==0L)
		{
			CGlobalUnits * pCGlobalUnits=CGlobalUnits::GetInstance();
			pCGlobalUnits->DownLoadClient(pGameKind->szKindName,pGameKind->wKindID,pGameServer->wServerID);

			return NULL;
		}

		//更新列表
		OnGameItemUpdate(pGameKindItem);
	}

	//创建房间
	try
	{
		//创建窗口
		m_pServerViewItem = new CServerViewItem;
		m_pServerViewItem->Create(IDD_GAME_SERVER,this);
		m_pServerViewItem->InitServerViewItem(pGameServerItem);
	}
	catch (LPCTSTR pszString)
	{
		//销毁房间
		if( m_pServerViewItem!=NULL )
		{
			if(m_pServerViewItem->m_hWnd!=NULL) m_pServerViewItem->DestroyWindow();
			SafeDelete(m_pServerViewItem);
		}

		//提示信息
		CInformation Information(this);
		Information.ShowMessageBox(pGameServer->szServerName,pszString,MB_ICONERROR);

		return false;
	}

	return true;
}

//关闭消息
VOID CPlatformFrame::OnClose()
{
	//变量定义
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//关闭提示
	if ((pGlobalUserData->dwUserID!=0L)&&(m_MissionLogon.GetActiveStatus()==false))
	{
		//显示窗口
		CDlgEnquire DlgEnquire;
		INT_PTR nResult=DlgEnquire.DoModal();

		//命令处理
		switch (nResult)
		{
		case IDCANCEL:				//取消动作
			{
				return;
			}
		case IDC_CLOSE_SERVER:		//退出房间
			{
				//关闭房间
				if (m_pServerViewItem!=NULL)
				{
					DeleteServerViewItem();
				}

				return;
			}
		case IDC_SWITCH_ACCOUNTS:	//切换帐号
			{
				//投递消息
				PostMessage(WM_COMMAND,IDM_SWITCH_ACCOUNTS,0);

				return;
			}
		}
	}

	__super::OnClose();
}

//绘画背景
BOOL CPlatformFrame::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建 DC
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//绘画界面
	DrawControlView(pBufferDC,rcClient.Width(),rcClient.Height());

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//位置消息
VOID CPlatformFrame::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	//调整资源
	RectifyResource(cx,cy);

	return;
}

//建立消息
INT CPlatformFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//设置窗口
	ModifyStyle(WS_CAPTION,0,0);
	ModifyStyleEx(WS_BORDER|WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE,0,0);

	//创建广场
	CRect rcCreate(0,0,0,0);
	m_PlazaViewItem.Create(IDD_GAME_PLAZA,this);
	m_ServerToolBar.Create(IDD_DLG_SERVER_TOOL_BAR,this);

	//创建控件
	m_SkinSplitter.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SKIN_SPLITTER);
	m_WndUserInfoCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_USER_INFO_CTRL);
	m_WndGameTypeCtrl.Create(NULL,NULL,WS_VISIBLE|WS_CHILD|WS_CLIPCHILDREN,rcCreate,this,IDC_GAME_TYPE_CTRL);
	m_PlatFormNoticePublicize.Create(NULL,NULL,WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,rcCreate,this,IDC_WEB_PUBLICIZE1);

	//创建按钮
	m_btMin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MIN);
	m_btMax.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MAX);
	m_btClose.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CLOSE);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btMin.SetButtonImage(IDB_BT_MIN,hInstance,true,false);
	m_btMax.SetButtonImage(IDB_BT_MAX,hInstance,true,false);
	m_btClose.SetButtonImage(IDB_BT_CLOSE,hInstance,true,false);

	//导航按钮
	for (INT i=0;i<CountArray(m_btNavigation);i++)
	{
		m_btNavigation[i].Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_NAVIGATION+i);
	}

	//导航按钮
	m_btNavigation[0].SetButtonImage(IDB_BK_NAVIGATION1,TEXT("BT_NAVIGATION_1"),hInstance,true,false);
	m_btNavigation[1].SetButtonImage(IDB_BK_NAVIGATION2,TEXT("BT_NAVIGATION_2"),hInstance,true,false);
	m_btNavigation[2].SetButtonImage(IDB_BK_NAVIGATION3,TEXT("BT_NAVIGATION_3"),hInstance,true,false);
	m_btNavigation[3].SetButtonImage(IDB_BK_NAVIGATION4,TEXT("BT_NAVIGATION_4"),hInstance,true,false);
	m_btNavigation[4].SetButtonImage(IDB_BK_NAVIGATION5,TEXT("BT_NAVIGATION_5"),hInstance,true,false);
	m_btNavigation[5].SetButtonImage(IDB_BK_NAVIGATION6,TEXT("BT_NAVIGATION_6"),hInstance,true,false);
	m_btNavigation[6].SetButtonImage(IDB_BK_NAVIGATION7,TEXT("BT_NAVIGATION_7"),hInstance,true,false);

	//游戏列表
	m_ServerListData.SetServerListDataSink(this);

	//提示控件
	m_ToolTipCtrl.Create(this);
	m_ToolTipCtrl.Activate(TRUE);
	m_ToolTipCtrl.AddTool(&m_btNavigation[0],TEXT("官方网站"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[1],TEXT("在线充值"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[2],TEXT("上传头像"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[3],TEXT("锁定本机"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[4],TEXT("兑换商城"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[5],TEXT("玩家推广"));
	m_ToolTipCtrl.AddTool(&m_btNavigation[6],TEXT("客服中心"));
	//m_ToolTipCtrl.AddTool(&m_btMin,TEXT("最小化"));
	//m_ToolTipCtrl.AddTool(&m_btClose,TEXT("关闭大厅"));

	//注册事件
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//设置分辨率
	m_ScreenMetrics.cx = ::GetSystemMetrics(SM_CXSCREEN); 
	m_ScreenMetrics.cy = ::GetSystemMetrics(SM_CYSCREEN);

	//设置位置
	CSize SizeRestrict;
	SizeRestrict.SetSize(LESS_SCREEN_CX,LESS_SCREEN_CY);

	//窗口位置
	CRect rcArce;
	SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

	//位置调整
	SizeRestrict.cx=__max(LESS_SCREEN_CX,SizeRestrict.cx);
	SizeRestrict.cy=__max(LESS_SCREEN_CY,SizeRestrict.cy);
	SizeRestrict.cx=__min(rcArce.Width(),SizeRestrict.cx);
	SizeRestrict.cy=__min(rcArce.Height(),SizeRestrict.cy);

	//移动窗口
	m_rcNormalSize.top=(rcArce.Height()-SizeRestrict.cy)/2;
	m_rcNormalSize.left=(rcArce.Width()-SizeRestrict.cx)/2;
	m_rcNormalSize.right=(rcArce.Width()+SizeRestrict.cx)/2;
	m_rcNormalSize.bottom=(rcArce.Height()+SizeRestrict.cy)/2;
	SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);

	//工作目录
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//构造地址
	TCHAR szBillUrl[256]=TEXT("");
	_sntprintf(szBillUrl,CountArray(szBillUrl),TEXT("%s\\Web\\LobbyTopNotice.htm"),szDirectory);

	//变量定义
	CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
	ASSERT(pGlobalUnits!=NULL);

	//连接广告
	if(pGlobalUnits!=NULL && pGlobalUnits->LocalFileExist(szBillUrl))
		m_PlatFormNoticePublicize.Navigate(szBillUrl);
	m_PlatFormNoticePublicize.SetBackColor(RGB(19,69,103));

	//登录系统
	PostMessage(WM_COMMAND,IDM_USER_LOGON,0);

	//创建分层
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	m_SkinLayered.CreateLayered(this,rcWindow);

	//调整资源
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(),rcClient.Height());

	//构造路径
	TCHAR szImagePath[MAX_PATH]=TEXT("");
	_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\ADImage\\Frame.BMP"),szDirectory);

	//加载资源
	m_ImageFrame.Load(szImagePath);

	return 0;
}


//时间消息
VOID CPlatformFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case IDI_FLASH_TRAY_ICON:	//任务图标
		{
			//设置变量
			m_bWhisperIcon=!m_bWhisperIcon;

			//设置图标
			UINT uIconID=(m_bWhisperIcon==true)?IDI_WHISPER:IDI_NULL;
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(uIconID)));

			return;
		}
	}

	__super::OnTimer(nIDEvent);
}

//显示消息
VOID CPlatformFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//显示分层
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//位置改变
VOID CPlatformFrame::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanging(lpWndPos);

	//移动分层
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//鼠标消息
VOID CPlatformFrame::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//模拟按标题
	if ((IsZoomed()==FALSE)&&(Point.y<=CAPTION_SIZE))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}

//事件消息
LRESULT CPlatformFrame::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	//事件处理
	switch (wParam)
	{
	case EVENT_USER_LOGON:			//登录完成
		{
			//显示窗口
			ShowWindow(SW_SHOW);
			SetForegroundWindow();

			//更新人数
			m_MissionList.UpdateMissionStatus(true);

			//获取指针
			CGlobalUnits * pGlobalUnits = (CGlobalUnits *)CGlobalUnits::GetInstance();
			if(pGlobalUnits==NULL) return 0L;

			//用户甜饼			
			pGlobalUnits->WriteUserCookie();

			//用户信息
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			ASSERT(pGlobalUserData!=NULL);

			//设置参数
			pGlobalUnits->SetValidateParam(pGlobalUserData->dwUserID,pGlobalUserData->szPassword);

			return 0L;
		}
	case EVENT_USER_LOGOUT:			//注销成功
		{
			//隐藏窗口
			ShowWindow(SW_HIDE);

			//关闭房间
			DeleteServerViewItem();

			//显示登录
			m_MissionLogon.ShowLogon();

			return 0L;
		}
	case EVENT_DOWN_LOAD_FINISH:	//下载完成
		{
			//获取参数
			WORD wKindID=LOWORD(lParam);
			WORD wServerID=HIWORD(lParam);

			//更新列表
			CServerListData * pServerListData=CServerListData::GetInstance();
			if (pServerListData!=NULL) pServerListData->OnEventDownLoadFinish(wKindID);

			//进入房间
			if ((wKindID!=0)&&(wServerID!=0))
			{
				CGameServerItem * pGameServerItem=m_ServerListData.SearchGameServer(wServerID);
				if (pGameServerItem!=NULL) EntranceServerItem(pGameServerItem);
			}

			return 0L;
		}
	case EVENT_UPDATE_ONLINE: //人数更新
		{
			//更新界面
			m_PlazaViewItem.InValidateWndView(VIEW_MODE_SERVER);

			return 0L;
		}
	}

	return 0L;
}


//提取私聊
bool CPlatformFrame::ShowWhisperItem()
{
	//提取消息
	if (m_DlgWhisperItemArray.GetCount()>0L)
	{
		//获取子项
		CDlgWhisper * pDlgWhisper=m_DlgWhisperItemArray[0];

		//显示窗口
		pDlgWhisper->ShowWindow(SW_RESTORE);

		//置顶窗口
		pDlgWhisper->SetActiveWindow();
		pDlgWhisper->BringWindowToTop();
		pDlgWhisper->SetForegroundWindow();

		//删除子项
		m_DlgWhisperItemArray.RemoveAt(0L);

		//删除图标
		if (m_DlgWhisperItemArray.GetCount()==0L)
		{
			//设置变量
			m_bWhisperIcon=false;

			//删除时间
			KillTimer(IDI_FLASH_TRAY_ICON);

			//设置图标
			m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
		}

		return true;
	}

	return false;
}


//插入私聊
bool CPlatformFrame::InsertWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//参数效验
	ASSERT((pDlgWhisper!=NULL)&&(pDlgWhisper->m_hWnd!=NULL));
	if ((pDlgWhisper==NULL)||(pDlgWhisper->m_hWnd==NULL)) return false;

	//状态判断
	if (pDlgWhisper->IsWindowVisible()) return false;

	//存在搜索
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper) return false;
	}

	//插入私聊
	m_DlgWhisperItemArray.Add(pDlgWhisper);

	//设置图标
	if (m_DlgWhisperItemArray.GetCount()==1L)
	{
		//设置变量
		m_bWhisperIcon=true;

		//设置时间
		SetTimer(IDI_FLASH_TRAY_ICON,500,NULL);

		//设置图标
		m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_WHISPER)));
	}

	return true;
}

//删除私聊
bool CPlatformFrame::RemoveWhisperItem(CDlgWhisper * pDlgWhisper)
{
	//存在搜索
	for (INT_PTR i=0;i<m_DlgWhisperItemArray.GetCount();i++)
	{
		if (m_DlgWhisperItemArray[i]==pDlgWhisper)
		{
			//删除子项
			m_DlgWhisperItemArray.RemoveAt(i);

			//删除图标
			if (m_DlgWhisperItemArray.GetCount()==0L)
			{
				//设置变量
				m_bWhisperIcon=false;

				//删除时间
				KillTimer(IDI_FLASH_TRAY_ICON);

				//设置图标
				m_SystemTrayIcon.ShowTrayIcon(LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)));
			}

			return true;
		}
	}

	return false;
}

//显示面板
VOID CPlatformFrame::ShowPlazaLeftPanel(bool bShowPanel)
{
	//设置变量
	m_bShowLeftPanel = bShowPanel;

	//变量定义
	CRect rcClient;
	GetClientRect(rcClient);

	//调整控件
	RectifyControl(rcClient.Width(),rcClient.Height());

	return;
}

//修改分辨率
VOID CPlatformFrame::ChangeScreenSetting(INT nScreencx,INT nScreency,bool bRecordResol)
{
	//获取分辨率
	CSize SizeScreenMetrics;
	SizeScreenMetrics.cx = ::GetSystemMetrics(SM_CXSCREEN); 
	SizeScreenMetrics.cy = ::GetSystemMetrics(SM_CYSCREEN);

	//比较分辨率
	if(nScreencx != SizeScreenMetrics.cx && nScreency!=SizeScreenMetrics.cy)
	{
		//设置变量
		if(bRecordResol==true) m_ScreenMetrics = SizeScreenMetrics;

		//构造结构
		DEVMODE lpDevMode;
		lpDevMode.dmBitsPerPel=32;
		lpDevMode.dmPelsWidth=nScreencx;
		lpDevMode.dmPelsHeight=nScreency;
		lpDevMode.dmSize=sizeof(lpDevMode);
		lpDevMode.dmFields =DM_PELSWIDTH|DM_PELSHEIGHT|DM_BITSPERPEL;

		//修改分辨率
		LONG lResult=ChangeDisplaySettings(&lpDevMode,0);
		if (lResult==DISP_CHANGE_SUCCESSFUL)
		{
			ChangeDisplaySettings(&lpDevMode,CDS_UPDATEREGISTRY);
		}
		else
		{
			ChangeDisplaySettings(NULL,0);
		}
	}

	return;
}

//最大窗口
bool CPlatformFrame::MaxSizeWindow()
{
	if(m_bMaxShow==false)
	{
		//设置变量
		m_bMaxShow = true;

		//记录区域
		GetWindowRect(m_rcNormalSize);

		//更新资源
		m_btMax.SetButtonImage(IDB_BT_RESTORE,AfxGetInstanceHandle(),true,false);	
		
		//修改分辨率
		ChangeScreenSetting(MAX_SCREEN_CX,MAX_SCREEN_CY,true);

		//获取位置
		CRect rcArce;
		SystemParametersInfo(SPI_GETWORKAREA,0,&rcArce,SPIF_SENDCHANGE);

		//移动窗口
		LockWindowUpdate();
		SetWindowPos(NULL,rcArce.left-2,rcArce.top-2,rcArce.Width()+4,rcArce.Height()+4,SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//还原窗口
bool CPlatformFrame::RestoreWindow()
{
	if(m_bMaxShow==true)
	{
		//设置变量
		m_bMaxShow = false;

		//更新资源
		m_btMax.SetButtonImage(IDB_BT_RESTORE,AfxGetInstanceHandle(),true,false);

		//修改分辨率
		ChangeScreenSetting(m_ScreenMetrics.cx,m_ScreenMetrics.cy,false);

		//移动窗口
		LockWindowUpdate();
		SetWindowPos(NULL,m_rcNormalSize.left,m_rcNormalSize.top,m_rcNormalSize.Width(),m_rcNormalSize.Height(),SWP_NOZORDER);
		UnlockWindowUpdate();
	}

	return true;
}

//银行更新
LRESULT CPlatformFrame::OnMessageInsureUpdate(WPARAM wParam, LPARAM lParam)
{
	//提取数据
	tagInsurePlazaUpdata * pInsurePlazaUpdate = (tagInsurePlazaUpdata *)wParam;
	ASSERT(pInsurePlazaUpdate!=NULL);
	if(pInsurePlazaUpdate==NULL) return 0L;

	//用户信息
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
	if(pGlobalUserData==NULL) return 0;
    
	//更新银行
	pGlobalUserData->lUserScore=pInsurePlazaUpdate->lUserScore;
	pGlobalUserData->lUserInsure=pInsurePlazaUpdate->lUserInsure;

	//平台事件
	CPlatformEvent * pPlatformEvent = CPlatformEvent::GetInstance();
	ASSERT(pPlatformEvent!=NULL);
	pPlatformEvent->SendPlatformEvent(EVENT_USER_INFO_UPDATE,0L);

	return 0L;
}

//////////////////////////////////////////////////////////////////////////////////
