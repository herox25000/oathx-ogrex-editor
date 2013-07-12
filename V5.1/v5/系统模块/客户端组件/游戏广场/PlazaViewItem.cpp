#include "StdAfx.h"
#include "ExDispID.h"
#include "GamePlaza.h"
#include "PlazaViewItem.h"
#include "PlatformFrame.h"

//////////////////////////////////////////////////////////////////////////////////

//控件标识
#define IDC_PLAZA_BROWSER			100									//浏览控件

//图片位置
#define GAME_TITLE_CY				81									//标题高度
#define GAME_TITLE_CX				786									//标题宽度

//类型位置
#define GAME_KIND_ITEM_PX			2									//类型间隔
#define GAME_KIND_ITEM_PY			5									//类型间隔
#define GAME_KIND_ITEM_CX			187									//类型宽度
#define GAME_KIND_ITEM_CY			251									//类型高度

//类型位置
#define GAME_SERVER_ITEM_PX			2									//房间间隔
#define GAME_SERVER_ITEM_PY			5									//房间间隔
#define GAME_SERVER_ITEM_CX			187									//房间宽度
#define GAME_SERVER_ITEM_CY			210									//房间高度

//按钮标识
#define IDC_BT_LAST_KIND			100									//上页按钮
#define IDC_BT_NEXT_KIND			101									//下页按钮
#define IDC_BT_RETURN_HALL          102                                 //返回按钮  
#define IDC_BT_LAST_SERVER			103 								//上页按钮
#define IDC_BT_NEXT_SERVER			104									//下页按钮

//////////////////////////////////////////////////////////////////////////////////

//静态变量
CPlazaViewItem * CPlazaViewItem::m_pPlazaViewItem=NULL;					//广场指针

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPlazaViewItem, CDialog)

	//系统消息
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)

	//按钮消息
	ON_BN_CLICKED(IDC_BT_LAST_KIND, OnBnClickedLastKind)
	ON_BN_CLICKED(IDC_BT_NEXT_KIND, OnBnClickedNextKind)
	ON_BN_CLICKED(IDC_BT_RETURN_HALL,OnBnClickedReturnHall)
	ON_BN_CLICKED(IDC_BT_LAST_SERVER, OnBnClickedLastServer)
	ON_BN_CLICKED(IDC_BT_NEXT_SERVER, OnBnClickedNextServer)	

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CPlazaViewItem::CPlazaViewItem() : CDialog(IDD_GAME_PLAZA)
{
	//设置变量
	m_bHovering=false;
	m_bCreateFlag=false;
	m_cbShowItemMode=VIEW_MODE_NONE;

	//移动位置
	m_cbButtonDown=0;
	m_cbButtonHover=0;
	m_wViewItemDown=INVALID_WORD;
	m_wViewItemHover=INVALID_WORD;

	//位置变量
	m_wKindXCount=0;
	m_wKindYCount=0;
	m_wKindExcursion=0;
	m_wKindPageCount=0;
	m_wKindPageCurrent=0;
	m_wKindTypeCurrentID=0;

	//位置变量
	m_wServerXCount=0;
	m_wServerYCount=0;
	m_wServerExcursion=0;
	m_wServerPageCount=0;
	m_wServerPageCurrent=0;

	//设置对象
	ASSERT(m_pPlazaViewItem==NULL);
	if (m_pPlazaViewItem==NULL) m_pPlazaViewItem=this;

	return;
}

//析构函数
CPlazaViewItem::~CPlazaViewItem()
{
	//删除类型
	for (INT i=0;i<m_GameKindInfoActive.GetCount();i++)
	{
		SafeDelete(m_GameKindInfoActive[i]);
	}

	//删除类型
	for (INT i=0;i<m_GameKindInfoBuffer.GetCount();i++)
	{
		SafeDelete(m_GameKindInfoBuffer[i]);
	}

	//删除房间
	for (INT i=0;i<m_GameKindInfoActive.GetCount();i++)
	{
		SafeDelete(m_GameKindInfoActive[i]);
	}

	//删除房间
	for (INT i=0;i<m_GameServerInfoBuffer.GetCount();i++)
	{
		SafeDelete(m_GameServerInfoBuffer[i]);
	}

	return;
}

//接口查询
VOID * CPlazaViewItem::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE_IUNKNOWNEX(IUnknownEx,Guid,dwQueryVer);
	return NULL;
}

//创建函数
BOOL CPlazaViewItem::OnInitDialog()
{
	__super::OnInitDialog();

	//设置变量
	m_bCreateFlag=true;

	//创建按钮
	CRect rcCreate(0,0,0,0);
	m_btLastKind.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_LAST_KIND);
	m_btNextKind.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_NEXT_KIND);
	m_btReturnHall.Create(NULL,WS_CHILD,rcCreate,this,IDC_BT_RETURN_HALL);
	m_btLastServer.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_LAST_SERVER);
	m_btNextServer.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_NEXT_SERVER);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btLastKind.SetButtonImage(IDB_BT_KIND_ITEM_VIEW,TEXT("BT_LAST_KIND"),hInstance,true,false);
	m_btNextKind.SetButtonImage(IDB_BT_KIND_ITEM_VIEW,TEXT("BT_NEXT_KIND"),hInstance,true,false);
	m_btReturnHall.SetButtonImage(IDB_BT_KIND_ITEM_VIEW,TEXT("BT_RETURN_HALL"),hInstance,true,false);
	m_btLastServer.SetButtonImage(IDB_BT_SERVER_ITEM_VIEW,TEXT("BT_LAST_SERVER"),hInstance,true,false);
	m_btNextServer.SetButtonImage(IDB_BT_SERVER_ITEM_VIEW,TEXT("BT_NEXT_SERVER"),hInstance,true,false);

	return TRUE;
}

//显示类型
VOID CPlazaViewItem::ShowKindItemView(WORD wTypeID,BOOL bResetPageIndex)
{
	//获取对象
	ASSERT(CServerListData::GetInstance()!=NULL);
	CServerListData * pServerListData=CServerListData::GetInstance();

	//工作目录
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//变量定义
	POSITION Position=NULL;
	CGameKindItem * pGameKindItem=NULL;
	tagGameKindInfo * pGameKindInfo=NULL;

	//删除对象
	for (INT i=0;i<m_GameKindInfoActive.GetCount();i++)
	{
		//获取对象
		ASSERT(m_GameKindInfoActive[i]!=NULL);
		pGameKindInfo=m_GameKindInfoActive[i];

		//设置变量
		pGameKindInfo->wSortID=0;
		pGameKindInfo->pGameKindItem=NULL;

		//清理对象
		if (pGameKindInfo->ImageKindItem.IsNull()==false)
		{
			pGameKindInfo->ImageKindItem.DestroyImage();
		}
	}

	//删除对象
	m_GameKindInfoBuffer.Append(m_GameKindInfoActive);
	m_GameKindInfoActive.RemoveAll();

	//插入对象
	while (true)
	{
		//获取对象
		pGameKindItem=pServerListData->EmunGameKindItem(Position);

		//对象判断
		if (pGameKindItem==NULL) break;

		//类型判断
		if ((wTypeID!=0)&&(pGameKindItem->m_GameKind.wTypeID!=wTypeID))
		{
			if (Position==NULL) break;
			if (Position!=NULL) continue;
		}

		//获取对象
		if (m_GameKindInfoBuffer.GetCount()>0L)
		{
			//获取对象
			INT_PTR nCount=m_GameKindInfoBuffer.GetCount();
			pGameKindInfo=m_GameKindInfoBuffer[nCount-1L];

			//删除对象
			ASSERT(pGameKindInfo!=NULL);
			m_GameKindInfoBuffer.RemoveAt(nCount-1L);
		}
		else
		{
			try
			{
				pGameKindInfo=new tagGameKindInfo;
				if (pGameKindInfo==NULL) throw TEXT("创建对象失败");
			}
			catch (...)
			{
				ASSERT(FALSE);
				break;
			}
		}

		//设置对象
		pGameKindInfo->pGameKindItem=pGameKindItem;
		pGameKindInfo->wSortID=pGameKindItem->m_GameKind.wSortID;

		//获取目录
		TCHAR szGameDirectory[LEN_PROCESS]=TEXT("");
		GetGameDirectory(szGameDirectory,CountArray(szGameDirectory),pGameKindItem->m_GameKind);

		//构造路径
		TCHAR szImagePath[MAX_PATH]=TEXT("");
		_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\ADImage\\GameKind\\GameKind_%s.PNG"),szDirectory,szGameDirectory);

		//加载图片
		if (pGameKindInfo->ImageKindItem.LoadImage(szImagePath)==false)
		{
			HINSTANCE hInstance=AfxGetInstanceHandle();
			pGameKindInfo->ImageKindItem.LoadImage(hInstance,TEXT("UNKNOWN_KIND"));
		}

		//插入对象
		for (INT nItem=0;nItem<m_GameKindInfoActive.GetCount();nItem++)
		{
			//获取对象
			ASSERT(m_GameKindInfoActive[nItem]!=NULL);
			tagGameKindInfo * pGameKindTemp=m_GameKindInfoActive[nItem];

			//排序判断
			if (pGameKindInfo->wSortID<pGameKindTemp->wSortID)
			{
				m_GameKindInfoActive.InsertAt(nItem,pGameKindInfo);
				break;
			}
		}

		//默认插入
		if (nItem==m_GameKindInfoActive.GetCount())
		{
			m_GameKindInfoActive.Add(pGameKindInfo);
		}

		//结束判断
		if (Position==NULL)
		{
			break;
		}
	}

	//设置变量
	m_cbButtonDown=0;
	m_cbButtonHover=0;
	m_wKindTypeCurrentID=wTypeID;
	m_wViewItemDown=INVALID_WORD;
	m_wViewItemHover=INVALID_WORD;
	m_cbShowItemMode=VIEW_MODE_KIND;

	//设置索引
	if(bResetPageIndex==TRUE) m_wKindPageCurrent=0;

	//调整界面
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//显示房间
VOID CPlazaViewItem::ShowServerItemView(WORD wKindID,BOOL bResetPageIndex)
{
	//获取对象
	ASSERT(CServerListData::GetInstance()!=NULL);
	CServerListData * pServerListData=CServerListData::GetInstance();

	//查找类型
	ASSERT(pServerListData->SearchGameKind(wKindID)!=NULL);
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//工作目录
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//获取目录
	TCHAR szGameDirectory[LEN_PROCESS]=TEXT("");
	GetGameDirectory(szGameDirectory,CountArray(szGameDirectory),pGameKindItem->m_GameKind);

	//构造路径
	TCHAR szImageTitle[MAX_PATH]=TEXT("");
	TCHAR szImageServer[MAX_PATH]=TEXT("");
	_sntprintf(szImageTitle,CountArray(szImageTitle),TEXT("%s\\ADImage\\GameTitle\\GameTitle_%s.PNG"),szDirectory,szGameDirectory);
	_sntprintf(szImageServer,CountArray(szImageServer),TEXT("%s\\ADImage\\GameTitle\\GameServer_%s.PNG"),szDirectory,szGameDirectory);

	//销毁图片
	if (m_ImageTitle.IsNull()==false) m_ImageTitle.DestroyImage();
	if (m_ImageServer.IsNull()==false) m_ImageServer.DestroyImage();

	//加载图片
	if (m_ImageTitle.LoadImage(szImageTitle)==false)
	{
		HINSTANCE hInstance=AfxGetInstanceHandle();
		m_ImageTitle.LoadImage(hInstance,TEXT("UNKNOWN_TITLE"));
	}

	//加载图片
	if (m_ImageServer.LoadImage(szImageServer)==false)
	{
		HINSTANCE hInstance=AfxGetInstanceHandle();
		m_ImageServer.LoadImage(hInstance,TEXT("UNKNOWN_SERVER"));
	}

	//变量定义
	POSITION Position=NULL;
	CGameServerItem * pGameServerItem=NULL;
	tagGameServerInfo * pGameServerInfo=NULL;

	//删除对象
	for (INT i=0;i<m_GameServerInfoActive.GetCount();i++)
	{
		//获取对象
		ASSERT(m_GameServerInfoActive[i]!=NULL);
		pGameServerInfo=m_GameServerInfoActive[i];

		//设置变量
		pGameServerInfo->wSortID=0;
		pGameServerInfo->wServerID=0;
		pGameServerInfo->pGameServerItem=NULL;
	}

	//删除对象
	m_GameServerInfoBuffer.Append(m_GameServerInfoActive);
	m_GameServerInfoActive.RemoveAll();

	//插入对象
	while (true)
	{
		//获取对象
		pGameServerItem=pServerListData->EmunGameServerItem(Position);

		//对象判断
		if (pGameServerItem==NULL) break;

		//类型判断
		if (pGameServerItem->m_GameServer.wKindID!=wKindID)
		{
			if (Position==NULL) break;
			if (Position!=NULL) continue;
		}

		//获取对象
		if (m_GameServerInfoBuffer.GetCount()>0L)
		{
			//获取对象
			INT_PTR nCount=m_GameServerInfoBuffer.GetCount();
			pGameServerInfo=m_GameServerInfoBuffer[nCount-1L];

			//删除对象
			ASSERT(pGameServerInfo!=NULL);
			m_GameServerInfoBuffer.RemoveAt(nCount-1L);
		}
		else
		{
			try
			{
				pGameServerInfo=new tagGameServerInfo;
				if (pGameServerInfo==NULL) throw TEXT("创建对象失败");
			}
			catch (...)
			{
				ASSERT(FALSE);
				break;
			}
		}

		//设置对象
		pGameServerInfo->pGameServerItem=pGameServerItem;
		pGameServerInfo->wSortID=pGameServerItem->m_GameServer.wSortID;
		pGameServerInfo->wServerID=pGameServerItem->m_GameServer.wServerID;

		//插入对象
		for (INT nItem=0;nItem<m_GameServerInfoActive.GetCount();nItem++)
		{
			//获取对象
			ASSERT(m_GameServerInfoActive[nItem]!=NULL);
			tagGameServerInfo * pGameServerTemp=m_GameServerInfoActive[nItem];

			//排序判断
			if (pGameServerInfo->wSortID<pGameServerTemp->wSortID)
			{
				m_GameServerInfoActive.InsertAt(nItem,pGameServerInfo);
				break;
			}
		}

		//默认插入
		if (nItem==m_GameServerInfoActive.GetCount())
		{
			m_GameServerInfoActive.Add(pGameServerInfo);
		}

		//结束判断
		if (Position==NULL)
		{
			break;
		}
	}

	//无效判断
	if (m_GameServerInfoActive.GetCount()==0)
	{
		//提示信息
		CInformation Information;
		Information.ShowMessageBox(TEXT("此游戏暂时没有可以进入的游戏房间，请选择其他游戏！"),MB_ICONINFORMATION,30L);

		return;
	}

	//设置变量
	m_cbButtonDown=0;
	m_cbButtonHover=0;
	m_wViewItemDown=INVALID_WORD;
	m_wViewItemHover=INVALID_WORD;
	m_cbShowItemMode=VIEW_MODE_SERVER;

	//设置索引
	if(bResetPageIndex==TRUE) m_wServerPageCurrent=0;

	//调整界面
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//位置消息
VOID CPlazaViewItem::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//对象索引
WORD CPlazaViewItem::GetHoverIndex(CPoint MousePoint)
{
	switch (m_cbShowItemMode)
	{
	case VIEW_MODE_KIND:	//类型视图
		{
			//无效判断
			if (MousePoint.x<m_wKindExcursion) return INVALID_WORD;
			if (MousePoint.y<GAME_KIND_ITEM_PY) return INVALID_WORD;

			//位置计算
			INT nXItem=(MousePoint.x-m_wKindExcursion)/(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX);
			INT nYItem=(MousePoint.y-GAME_KIND_ITEM_PY)/(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY);

			//溢出判断
			if ((MousePoint.x-m_wKindExcursion-(nXItem*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX)))>GAME_KIND_ITEM_CX) return INVALID_WORD;
			if ((MousePoint.y-GAME_KIND_ITEM_PY-(nYItem*(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY)))>GAME_KIND_ITEM_CY) return INVALID_WORD;

			//结果判断
			if ((nYItem>=0)&&(nXItem>=0)&&(nYItem<m_wKindYCount)&&(nXItem<m_wKindXCount))
			{
				WORD wViewCount=m_wKindXCount*m_wKindYCount;
				WORD wResultItem=nYItem*m_wKindXCount+nXItem;
				if ((m_wKindPageCurrent*wViewCount+wResultItem)<m_GameKindInfoActive.GetCount()) return wResultItem;
			}

			return INVALID_WORD;
		}
	case VIEW_MODE_SERVER:	//房间视图
		{
			//无效判断
			if (MousePoint.x<m_wServerExcursion) return INVALID_WORD;
			if (MousePoint.y<GAME_SERVER_ITEM_PY) return INVALID_WORD;

			//位置计算
			INT nXItem=(MousePoint.x-m_wServerExcursion)/(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX);
			INT nYItem=(MousePoint.y-GAME_SERVER_ITEM_PY-GAME_TITLE_CY)/(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY);

			//溢出判断
			if ((MousePoint.x-m_wServerExcursion-(nXItem*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX)))>GAME_SERVER_ITEM_CX) return INVALID_WORD;
			if ((MousePoint.y-GAME_SERVER_ITEM_PY-GAME_TITLE_CY-(nYItem*(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY)))>GAME_SERVER_ITEM_CY) return INVALID_WORD;

			//结果判断
			if ((nYItem>=0)&&(nXItem>=0)&&(nYItem<m_wServerYCount)&&(nXItem<m_wServerXCount))
			{
				WORD wViewCount=m_wServerXCount*m_wServerYCount;
				WORD wResultItem=nYItem*m_wServerXCount+nXItem;
				if ((m_wServerPageCurrent*wViewCount+wResultItem)<m_GameServerInfoActive.GetCount()) return wResultItem;
			}

			return INVALID_WORD;
		}
	}

	return INVALID_WORD;
}

//按钮测试
BYTE CPlazaViewItem::GetHoverButton(WORD wViewIndex, CPoint MousePoint)
{
	//无效判断
	if (wViewIndex==INVALID_WORD) return 0;

	//按钮检测
	switch (m_cbShowItemMode)
	{
	case VIEW_MODE_KIND:	//类型视图
		{
			//设置位置
			MousePoint.x-=(m_wKindExcursion+(wViewIndex%m_wKindXCount)*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX));
			MousePoint.y-=(GAME_SERVER_ITEM_PY+(wViewIndex/m_wKindXCount)*(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY));

			//规则位置
			CRect rcViewRule(9,203,92,242);
			if (rcViewRule.PtInRect(MousePoint)==TRUE) return BT_VIEW_RULE;

			//进入房间
			CRect rcEnterKind(94,203,176,242);
			if (rcEnterKind.PtInRect(MousePoint)==TRUE) return BT_ENTER_KIND;

			break;
		}
	case VIEW_MODE_SERVER:	//房间视图
		{
			//设置位置
			MousePoint.x-=(m_wServerExcursion+(wViewIndex%m_wServerXCount)*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX));
			MousePoint.y-=(GAME_SERVER_ITEM_PY+GAME_TITLE_CY+(wViewIndex/m_wServerXCount)*(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY));

			//进入房间
			CRect rcEnterServer(9,164,178,204);
			if (rcEnterServer.PtInRect(MousePoint)==TRUE) return BT_ENTER_SERVER;

			break;
		}
	}

	return 0;
}

//查看规则
VOID CPlazaViewItem::OnButtonViewRule(WORD wKindID)
{
	//构造地址
	TCHAR szRuleLink[MAX_PATH]=TEXT("");
	_sntprintf(szRuleLink,CountArray(szRuleLink),TEXT("%sGameDetails.aspx?KID=%ld"),szPlatformLink,wKindID);

	//打开页面
	ShellExecute(NULL,TEXT("OPEN"),szRuleLink,NULL,NULL,SW_NORMAL);

	return;
}

//进入类型
VOID CPlazaViewItem::OnButtonEnterKind(WORD wKindID)
{
	//查找对象
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//事件处理
	if (pGameKindItem!=NULL)
	{
		if (pGameKindItem->m_dwProcessVersion==0L)
		{
			//安装游戏
			CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
			pGlobalUnits->DownLoadClient(pGameKindItem->m_GameKind.szKindName,wKindID,0);
		}
		else
		{
			//显示房间
			ShowServerItemView(wKindID);
		}
	}

	return;
}

//进入房间
VOID CPlazaViewItem::OnButtonEnterServer(WORD wServerID)
{
	//获取对象
	CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
	CServerListData * pServerListData=CServerListData::GetInstance();

	//进入房间
	CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(wServerID);
	if (pGameServerItem!=NULL) pPlatformFrame->EntranceServerItem(pGameServerItem);

	return;
}

//上页按钮
VOID CPlazaViewItem::OnBnClickedLastKind()
{
	//效验状态
	ASSERT(m_wKindPageCurrent>0);
	if (m_wKindPageCurrent==0) return;

	//播放声音
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//设置变量
	m_wKindPageCurrent--;

	//控制按钮
	m_btLastKind.EnableWindow((m_wKindPageCurrent>0)?TRUE:FALSE);
	m_btNextKind.EnableWindow(((m_wKindPageCurrent+1)<m_wKindPageCount)?TRUE:FALSE);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//下页按钮
VOID CPlazaViewItem::OnBnClickedNextKind()
{
	//效验状态
	ASSERT((m_wKindPageCurrent+1)<m_wKindPageCount);
	if ((m_wKindPageCurrent+1)>=m_wKindPageCount) return;

	//播放声音
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//设置变量
	m_wKindPageCurrent++;

	//控制按钮
	m_btLastKind.EnableWindow((m_wKindPageCurrent>0)?TRUE:FALSE);
	m_btNextKind.EnableWindow(((m_wKindPageCurrent+1)<m_wKindPageCount)?TRUE:FALSE);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//返回按钮
VOID CPlazaViewItem::OnBnClickedReturnHall()
{
	//播放声音
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//返回大厅
	ShowKindItemView(m_wKindTypeCurrentID,FALSE);

	return;
}

//上页按钮
VOID CPlazaViewItem::OnBnClickedLastServer()
{
	//效验状态
	ASSERT(m_wServerPageCurrent>0);
	if (m_wServerPageCurrent==0) return;

	//播放声音
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//设置变量
	m_wServerPageCurrent--;

	//控制按钮
	m_btLastServer.EnableWindow((m_wServerPageCurrent>0)?TRUE:FALSE);
	m_btNextServer.EnableWindow(((m_wServerPageCurrent+1)<m_wServerPageCount)?TRUE:FALSE);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//下页按钮
VOID CPlazaViewItem::OnBnClickedNextServer()
{
	//效验状态
	ASSERT((m_wServerPageCurrent+1)<m_wServerPageCount);
	if ((m_wServerPageCurrent+1)>=m_wServerPageCount) return;

	//播放声音
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//设置变量
	m_wServerPageCurrent++;

	//控制按钮
	m_btLastServer.EnableWindow((m_wServerPageCurrent>0)?TRUE:FALSE);
	m_btNextServer.EnableWindow(((m_wServerPageCurrent+1)<m_wServerPageCount)?TRUE:FALSE);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//绘画背景
BOOL CPlazaViewItem::OnEraseBkgnd(CDC * pDC)
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

	//绘画背景
	CBitImage ImageGround;
	ImageGround.LoadFromResource(AfxGetInstanceHandle(),IDB_PLAZA_GROUND);
	ImageGround.DrawImageTile(pBufferDC,0,0,rcClient.Width(),rcClient.Height());

	//绘画界面
	switch (m_cbShowItemMode)
	{
	case VIEW_MODE_KIND:	//类型视图
		{
			//变量定义
			WORD wViewCount=m_wKindXCount*m_wKindYCount;
			WORD wStartIndex=wViewCount*m_wKindPageCurrent;

			//绘画类型
			for (WORD i=0;i<wViewCount;i++)
			{
				//完成判断
				if ((wStartIndex+i)>=m_GameKindInfoActive.GetCount())
				{
					break;
				}

				//计算位置
				INT nXDrawPos=m_wKindExcursion+(i%m_wKindXCount)*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX);
				INT nYDrawPos=GAME_KIND_ITEM_PY+(i/m_wKindXCount)*(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY);

				//绘画对象
				tagGameKindInfo * pGameKindInfo=m_GameKindInfoActive[wStartIndex+i];
				if (pGameKindInfo!=NULL) DrawKindItem(pBufferDC,i,nXDrawPos,nYDrawPos,pGameKindInfo);
			}

			break;
		}
	case VIEW_MODE_SERVER:	//房间视图
		{
			//变量定义
			WORD wViewCount=m_wServerXCount*m_wServerYCount;
			WORD wStartIndex=wViewCount*m_wServerPageCurrent;

			//绘画标题
			m_ImageTitle.DrawImage(pBufferDC,(rcClient.Width()-GAME_TITLE_CX)/2,0,GAME_TITLE_CX,GAME_TITLE_CY,0,0);

			//绘画类型
			for (WORD i=0;i<wViewCount;i++)
			{
				//完成判断
				if ((wStartIndex+i)>=m_GameServerInfoActive.GetCount())
				{
					break;
				}

				//计算位置
				INT nXDrawPos=m_wServerExcursion+(i%m_wServerXCount)*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX);
				INT nYDrawPos=GAME_TITLE_CY+GAME_SERVER_ITEM_PY+(i/m_wServerXCount)*(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY);

				//绘画对象
				tagGameServerInfo * pGameServerInfo=m_GameServerInfoActive[wStartIndex+i];
				if (pGameServerInfo!=NULL) DrawServerItem(pBufferDC,i,nXDrawPos,nYDrawPos,pGameServerInfo);
			}

			break;
		}
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//界面更新
VOID CPlazaViewItem::InValidateWndView(BYTE cbViewType)
{
	//模式判断
	if(m_cbShowItemMode==cbViewType) InvalidateRect(NULL);

	return;
}

//绘画类型
VOID CPlazaViewItem::DrawKindItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameKindInfo * pGameKindInfo)
{
	//效验参数
	ASSERT(pGameKindInfo!=NULL);
	if (pGameKindInfo==NULL) return;

	//安装判断
	bool bInstall=false;
	if (pGameKindInfo->pGameKindItem->m_dwProcessVersion!=0L) bInstall=true;

	//加载资源
	CPngImage ImageViewRule;
	CPngImage ImageEnterKind;
	ImageViewRule.LoadImage(AfxGetInstanceHandle(),TEXT("BT_VIEW_RULE"));
	ImageEnterKind.LoadImage(AfxGetInstanceHandle(),(bInstall==true)?TEXT("BT_ENTER_KIND"):TEXT("BT_INSTALL_GAME"));

	//获取大小
	CSize SizeViewRule;
	CSize SizeEnterKind;
	SizeViewRule.SetSize(ImageViewRule.GetWidth()/5L,ImageViewRule.GetHeight());
	SizeEnterKind.SetSize(ImageEnterKind.GetWidth()/5L,ImageEnterKind.GetHeight());

	//绘画类型
	if (pGameKindInfo->ImageKindItem.IsNull()==false)
	{
		CSize SizeImage;
		SizeImage.SetSize(pGameKindInfo->ImageKindItem.GetWidth(),pGameKindInfo->ImageKindItem.GetHeight());
		pGameKindInfo->ImageKindItem.DrawImage(pDC,nXPos,nYPos,GAME_KIND_ITEM_CX,GAME_KIND_ITEM_CY,0,0,SizeImage.cx,SizeImage.cy);
	}

	//查看规则
	INT nXRuleIndex=0;
	bool bRuleButtonDown=((m_wViewItemDown==wViewIndex)&&(m_cbButtonDown==BT_VIEW_RULE));
	bool bRuleButtonHover=((m_wViewItemHover==wViewIndex)&&(m_cbButtonHover==BT_VIEW_RULE));

	//查看规则
	if ((bRuleButtonHover==true)&&(bRuleButtonDown==true)) nXRuleIndex=1;
	if ((bRuleButtonHover==true)&&(bRuleButtonDown==false)) nXRuleIndex=2;
	ImageViewRule.DrawImage(pDC,nXPos+9,nYPos+203,SizeViewRule.cx,SizeViewRule.cy,nXRuleIndex*SizeViewRule.cx,0);

	//进入游戏
	INT nXEnterIndex=0;
	bool bEnterButtonDown=((m_wViewItemDown==wViewIndex)&&(m_cbButtonDown==BT_ENTER_KIND));
	bool bEnterButtonHover=((m_wViewItemHover==wViewIndex)&&(m_cbButtonHover==BT_ENTER_KIND));

	//进入游戏
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==true)) nXEnterIndex=1;
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==false)) nXEnterIndex=2;
	ImageEnterKind.DrawImage(pDC,nXPos+94,nYPos+203,SizeEnterKind.cx,SizeEnterKind.cy,nXEnterIndex*SizeEnterKind.cx,0);

	return;
}

//绘画房间
VOID CPlazaViewItem::DrawServerItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameServerInfo * pGameServerInfo)
{
	//效验参数
	ASSERT(pGameServerInfo!=NULL);
	if (pGameServerInfo==NULL) return;

	//加载资源
	CPngImage ImageEnterServer;
	ImageEnterServer.LoadImage(AfxGetInstanceHandle(),TEXT("BT_ENTER_SERVER"));

	//获取大小
	CSize SizeEnterServer;
	SizeEnterServer.SetSize(ImageEnterServer.GetWidth()/5L,ImageEnterServer.GetHeight());

	//绘画类型
	if (m_ImageServer.IsNull()==false)
	{
		CSize SizeImage;
		SizeImage.SetSize(m_ImageServer.GetWidth(),m_ImageServer.GetHeight());
		m_ImageServer.DrawImage(pDC,nXPos,nYPos,GAME_SERVER_ITEM_CX,GAME_SERVER_ITEM_CY,0,0,SizeImage.cx,SizeImage.cy);
	}

	//进入游戏
	INT nXEnterIndex=0;
	bool bEnterButtonDown=((m_wViewItemDown==wViewIndex)&&(m_cbButtonDown==BT_ENTER_SERVER));
	bool bEnterButtonHover=((m_wViewItemHover==wViewIndex)&&(m_cbButtonHover==BT_ENTER_SERVER));

	//进入游戏
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==true)) nXEnterIndex=1;
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==false)) nXEnterIndex=2;
	ImageEnterServer.DrawImage(pDC,nXPos+9,nYPos+164,SizeEnterServer.cx,SizeEnterServer.cy,nXEnterIndex*SizeEnterServer.cx,0);

	//变量定义
	LPCTSTR szOnLineStatus[] = { TEXT("空闲"),TEXT("繁忙"),TEXT("拥挤"),TEXT("爆满") };
	INT nOnLineLevel[] = {20,100,200,0xfff};
	INT nOnLinetCount = pGameServerInfo->pGameServerItem->m_GameServer.dwOnLineCount;

	//在线状态
	TCHAR szServerOnLine[16]=TEXT("");
	for(BYTE cbIndex=0;cbIndex<CountArray(szOnLineStatus);++cbIndex)
	{
		if(nOnLinetCount<nOnLineLevel[cbIndex])
		{
			_sntprintf(szServerOnLine,CountArray(szServerOnLine),szOnLineStatus[cbIndex]);
			break;
		}
	}

	//单元积分
	TCHAR szServerScore[32]=TEXT("");
	_sntprintf(szServerScore,CountArray(szServerScore),SCORE_STRING,pGameServerInfo->pGameServerItem->m_GameServer.lServerScore);

	//需要金币
	TCHAR szMinServerScore[32]=TEXT("");
	_sntprintf(szMinServerScore,CountArray(szMinServerScore),SCORE_STRING,pGameServerInfo->pGameServerItem->m_GameServer.lMinServerScore);

	//房间名字
	TCHAR szServerName[LEN_SERVER]=TEXT("");
	_sntprintf(szServerName,CountArray(szServerName),TEXT("%s"),pGameServerInfo->pGameServerItem->m_GameServer.szServerName);

	//设置环境
	pDC->SetBkColor(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//绘画信息
	CRect rcOnlineCount(nXPos+78,nYPos+64,nXPos+168,nYPos+80);
	CRect rcServerName(nXPos+22,nYPos+133,nXPos+168,nYPos+149);
	CRect rcServerScore(nXPos+78,nYPos+87,nXPos+168,nYPos+103);
	CRect rcMinServerScore(nXPos+78,nYPos+110,nXPos+168,nYPos+126);
	pDC->DrawText(szServerName,lstrlen(szServerName),rcServerName,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);
	pDC->DrawText(szServerOnLine,lstrlen(szServerOnLine),rcOnlineCount,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);
	pDC->DrawText(szServerScore,lstrlen(szServerScore),rcServerScore,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);
	pDC->DrawText(szMinServerScore,lstrlen(szMinServerScore),rcMinServerScore,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);

	return;
}

//调整控件
VOID CPlazaViewItem::RectifyControl(INT nWidth, INT nHeight)
{
	//状态判断
	if (m_bCreateFlag==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//按钮大小
	CRect rcButton;
	m_btLastKind.GetWindowRect(&rcButton);

	//类型位置
	m_wKindXCount=(nWidth+GAME_KIND_ITEM_PX)/(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX);
	m_wKindYCount=(nHeight+GAME_KIND_ITEM_PY)/(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY);
	m_wKindExcursion=(nWidth+GAME_KIND_ITEM_PX-m_wKindXCount*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX))/2;

	//类型页面
	WORD wViewCountKind=m_wKindXCount*m_wKindYCount;
	m_wKindPageCount=(WORD)(m_GameKindInfoActive.GetCount()+wViewCountKind-1)/wViewCountKind;
	m_wKindPageCurrent=(WORD)__min(m_GameKindInfoActive.GetCount()/wViewCountKind,m_wKindPageCurrent);

	//房间位置
	m_wServerXCount=(nWidth+GAME_SERVER_ITEM_PX)/(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX);
	m_wServerYCount=(nHeight+GAME_SERVER_ITEM_PY)/(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY);
	m_wServerExcursion=(nWidth+GAME_SERVER_ITEM_PX-m_wServerXCount*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX))/2;

	//房间页面
	WORD wViewCountServer=m_wServerXCount*m_wServerYCount;
	m_wServerPageCount=(WORD)(m_GameServerInfoActive.GetCount()+wViewCountServer-1)/(m_wServerXCount*m_wServerYCount);
	m_wServerPageCurrent=(WORD)__min(m_GameServerInfoActive.GetCount()/(m_wServerXCount*m_wServerYCount),m_wServerPageCurrent);

	//按钮控制
	m_btLastKind.EnableWindow((m_wKindPageCurrent>0)?TRUE:FALSE);
	m_btNextKind.EnableWindow(((m_wKindPageCurrent+1)<m_wKindPageCount)?TRUE:FALSE);

	//按钮控制
	m_btLastServer.EnableWindow((m_wServerPageCurrent>0)?TRUE:FALSE);
	m_btNextServer.EnableWindow(((m_wServerPageCurrent+1)<m_wServerPageCount)?TRUE:FALSE);

	//变量定义
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE;

	//类型按钮
	UINT uKindFlags=(m_cbShowItemMode==VIEW_MODE_KIND)?SWP_SHOWWINDOW:SWP_HIDEWINDOW;
	DeferWindowPos(hDwp,m_btLastKind,NULL,m_wKindExcursion+2,nHeight-rcButton.Height()-2,0,0,uFlags|uKindFlags);
	DeferWindowPos(hDwp,m_btNextKind,NULL,nWidth-rcButton.Width()-m_wKindExcursion-2,nHeight-rcButton.Height()-2,0,0,uFlags|uKindFlags);

	//房间按钮
	CRect rcButtonServer;
	m_btLastServer.GetWindowRect(&rcButtonServer);
	UINT uServerFlags=(m_cbShowItemMode==VIEW_MODE_SERVER)?SWP_SHOWWINDOW:SWP_HIDEWINDOW;
	DeferWindowPos(hDwp,m_btReturnHall,NULL,m_wServerExcursion+2,nHeight-rcButton.Height()-2,0,0,uFlags|uServerFlags);
	DeferWindowPos(hDwp,m_btLastServer,NULL,nWidth/2+2,nHeight-rcButtonServer.Height()-2,0,0,uFlags|uServerFlags);
	DeferWindowPos(hDwp,m_btNextServer,NULL,nWidth/2+rcButtonServer.Width()+6,nHeight-rcButtonServer.Height()-2,0,0,uFlags|uServerFlags);

	//结束调整
	EndDeferWindowPos(hDwp);

	return;
}

//资源目录
VOID CPlazaViewItem::GetGameDirectory(TCHAR szDirectory[], WORD wBufferCount, tagGameKind & GameKind)
{
	//变量定义
	WORD wStringIndex=0;

	//构造目录
	ZeroMemory(szDirectory,wBufferCount*sizeof(TCHAR));
	lstrcpyn(szDirectory,GameKind.szProcessName,wBufferCount);

	//构造目录
	while ((szDirectory[wStringIndex]!=0)&&(szDirectory[wStringIndex]!=TEXT('.')))
	{
		wStringIndex++;
	}

	//字符终止
	szDirectory[wStringIndex]=0;

	return;
}

//鼠标消息
VOID CPlazaViewItem::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//窗口位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//位置计算
	WORD wViewItemHover=GetHoverIndex(Point);
	BYTE cbButtonHover=GetHoverButton(wViewItemHover,Point);

	//数据调整
	if ((m_wViewItemDown!=INVALID_WORD)&&(m_cbButtonDown!=0))
	{
		if (cbButtonHover!=m_cbButtonDown) cbButtonHover=0;
		if (wViewItemHover!=m_wViewItemDown) wViewItemHover=INVALID_WORD;
	}

	//盘旋变量
	if ((wViewItemHover!=m_wViewItemHover)||(m_cbButtonHover!=cbButtonHover))
	{
		//设置变量
		m_cbButtonHover=cbButtonHover;
		m_wViewItemHover=wViewItemHover;

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
VOID CPlazaViewItem::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//结果动作
	BYTE cbButtonDown=0;
	WORD wViewItemDown=INVALID_WORD;

	//设置变量
	if ((m_wViewItemDown!=INVALID_WORD)&&(m_wViewItemDown==m_wViewItemHover)&&(m_cbButtonDown==m_cbButtonHover))
	{
		cbButtonDown=m_cbButtonDown;
		wViewItemDown=m_wViewItemDown;
	}

	//按起处理
	if ((m_wViewItemDown!=INVALID_WORD)&&(m_cbButtonDown!=0))
	{
		//释放鼠标
		ReleaseCapture();

		//设置变量
		m_cbButtonDown=0;
		m_wViewItemDown=INVALID_WORD;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);
	}

	//执行动作
	if ((wViewItemDown!=INVALID_WORD)&&(cbButtonDown!=0))
	{
		//播放声音
		CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
		if(pGlobalUnits!=NULL)
		{
			pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
		}

		switch (cbButtonDown)
		{
		case BT_VIEW_RULE:		//查看规则
			{
				//查看规则
				WORD wViewCount=m_wKindXCount*m_wKindYCount*m_wKindPageCurrent;
				tagGameKindInfo * pGameKindInfo=m_GameKindInfoActive[wViewCount+wViewItemDown];
				if (pGameKindInfo!=NULL) OnButtonViewRule(pGameKindInfo->pGameKindItem->m_GameKind.wKindID);

				break;
			}
		case BT_ENTER_KIND:		//进入类型
			{
				//进入类型
				WORD wViewCount=m_wKindXCount*m_wKindYCount*m_wKindPageCurrent;
				tagGameKindInfo * pGameKindInfo=m_GameKindInfoActive[wViewCount+wViewItemDown];
				if (pGameKindInfo!=NULL) OnButtonEnterKind(pGameKindInfo->pGameKindItem->m_GameKind.wKindID);

				break;
			}
		case BT_ENTER_SERVER:	//进入房间
			{
				//进入房间
				WORD wViewCount=m_wServerXCount*m_wServerYCount*m_wServerPageCurrent;
				tagGameServerInfo * pGameServerInfo=m_GameServerInfoActive[wViewCount+wViewItemDown];
				if (pGameServerInfo!=NULL) OnButtonEnterServer(pGameServerInfo->pGameServerItem->m_GameServer.wServerID);

				break;
			}
		}
	}

	return;
}

//鼠标消息
VOID CPlazaViewItem::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//设置焦点
	SetFocus();

	//按下处理
	if ((m_wViewItemHover!=INVALID_WORD)&&(m_cbButtonHover!=0))
	{
		//鼠标扑获
		SetCapture();

		//设置变量
		m_cbButtonDown=m_cbButtonHover;
		m_wViewItemDown=m_wViewItemHover;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);
	}

	return;
}

//鼠标消息
LRESULT CPlazaViewItem::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//设置状态
	m_bHovering=false;

	//更新界面
	if (m_wViewItemHover!=INVALID_WORD)
	{
		//设置变量
		m_cbButtonDown=0;
		m_cbButtonHover=0;
		m_wViewItemDown=INVALID_WORD;
		m_wViewItemHover=INVALID_WORD;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
