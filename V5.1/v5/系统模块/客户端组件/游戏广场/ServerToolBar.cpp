#include "StdAfx.h"
#include "Resource.h"
#include "GamePlaza.h"
#include "PlatformFrame.h"
#include "ServerToolBar.h"
#include "CollocateRoom.h"
#include "DlgTablePassword.h"
#include "DlgSearchTable.h"

//////////////////////////////////////////////////////////////////////////////////
//宏定义
#define BUTTON_H_SPACE                   8                   //横向间距

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CServerToolBar, CDialog)

	//系统消息
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()

	//自定消息
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CServerToolBar::CServerToolBar() : CDialog(IDD_DLG_SERVER_TOOL_BAR)
{	
	//设置变量
	m_bCreateFlag = false;

	return;
}

//析构函数
CServerToolBar::~CServerToolBar()
{
	return;
}

//接口查询
VOID * CServerToolBar::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE_IUNKNOWNEX(IUnknownEx,Guid,dwQueryVer);
	return NULL;
}

//创建函数
BOOL CServerToolBar::OnInitDialog()
{
	__super::OnInitDialog();

	//设置变量
	m_bCreateFlag = true;
	
	//桌子按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btQuitServer.SetButtonImage(IDB_BT_QUIT_SERVER,TEXT("BT_QUIT_SERVER"),hInstance,true,false);
	m_btTableButton1.SetButtonImage(IDB_BT_TABLE_BUTTON_1,TEXT("BT_TABLE_BUTTON_1"),hInstance,true,false);
	m_btTableButton2.SetButtonImage(IDB_BT_TABLE_BUTTON_2,TEXT("BT_TABLE_BUTTON_2"),hInstance,true,false);
	m_btTableButton3.SetButtonImage(IDB_BT_TABLE_BUTTON_3,TEXT("BT_TABLE_BUTTON_3"),hInstance,true,false);
	m_btTableButton4.SetButtonImage(IDB_BT_TABLE_BUTTON_4,TEXT("BT_TABLE_BUTTON_4"),hInstance,true,false);
	m_btTableButton5.SetButtonImage(IDB_BT_TABLE_BUTTON_5,TEXT("BT_TABLE_BUTTON_5"),hInstance,true,false);

	//变量定义
	CRect rcButton;
	m_btTableButton1.GetWindowRect(rcButton);

	//设置窗口
	SetWindowPos(NULL,0,0,(rcButton.Width()+BUTTON_H_SPACE)*6,rcButton.Height(),SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);

	//注册事件
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	return TRUE;
}

//控件绑定
VOID CServerToolBar::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	//桌子按钮
	DDX_Control(pDX, IDC_BT_QUIT_SERVER, m_btQuitServer);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_1, m_btTableButton1);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_2, m_btTableButton2);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_3, m_btTableButton3);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_4, m_btTableButton4);
	DDX_Control(pDX, IDC_BT_TABLE_BUTTON_5, m_btTableButton5);

	return;
}

//位置消息
VOID CServerToolBar::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//命令函数
BOOL CServerToolBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//大厅框架
	CPlatformFrame * pPlatformFrame = CPlatformFrame::GetInstance();
	ASSERT(pPlatformFrame!=NULL);
	if(pPlatformFrame==NULL) return TRUE;

	//房间视图
	CServerViewItem * pServerViewItem = pPlatformFrame->m_pServerViewItem;
	ASSERT(pServerViewItem != NULL);
	if(pServerViewItem == NULL) return TRUE;

	//变量定义
	WORD wCommandID = LOWORD(wParam);
	switch(wCommandID)
	{
	case IDC_BT_QUIT_SERVER:		//退出房间
		{
			//发送命令
			pServerViewItem->PostMessage(WM_COMMAND,IDM_DELETE_SERVER_ITEM,0L);

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_1:		//加入按钮
		{
			//动作过虑
			if (pServerViewItem->m_ServiceStatus!=ServiceStatus_ServiceIng) return TRUE;
			if ((pServerViewItem->m_wReqTableID!=INVALID_TABLE)&&(pServerViewItem->m_wReqChairID!=INVALID_CHAIR)) return TRUE;

			//状态判断
			if (pServerViewItem->m_pIMySelfUserItem->GetUserStatus()>=US_PLAYING)
			{
				CInformation Information(this);
				Information.ShowMessageBox(TEXT("您正在游戏中，暂时不能离开，请先结束当前游戏！"),MB_ICONINFORMATION,30L);
				return TRUE;
			}

			//随机座位
			if (CServerRule::IsAllowAvertCheatMode(pServerViewItem->m_dwServerRule)==true)
			{
				pServerViewItem->PerformSitDownAction(INVALID_TABLE,INVALID_CHAIR,false);
				return TRUE;
			}

			//变量定义
			ASSERT(CParameterGlobal::GetInstance()!=NULL);
			CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();

			//执行动作
			switch (pParameterGlobal->m_cbActionHitAutoJoin)
			{
			case ACTION_SEARCH_TABLE:		//查找位置
				{
					//变量定义
					tagSearchTable SearchTable;
					ZeroMemory(&SearchTable,sizeof(SearchTable));

					//搜索条件
					SearchTable.bNotFull=true;
					SearchTable.bOneNull=true;
					SearchTable.bAllNull=false;
					SearchTable.bFilterPass=true;
					SearchTable.bTwoNull=(pServerViewItem->m_TableViewFrame.GetChairCount()!=2);

					//搜索结果
					SearchTable.wResultTableID=INVALID_TABLE;
					SearchTable.wResultChairID=INVALID_CHAIR;
					SearchTable.wStartTableID=pServerViewItem->m_wFindTableID+1;

					//搜索桌子
					pServerViewItem->SearchGameTable(SearchTable);
					pServerViewItem->m_wFindTableID=SearchTable.wResultTableID;

					//搜索桌子
					if (pServerViewItem->m_wFindTableID==INVALID_CHAIR)
					{
						//搜索条件
						SearchTable.bAllNull=true;
						SearchTable.bNotFull=true;
						SearchTable.bOneNull=true;
						SearchTable.bFilterPass=true;
						SearchTable.bTwoNull=(pServerViewItem->m_TableViewFrame.GetChairCount()!=2);

						//搜索结果
						SearchTable.wResultTableID=INVALID_TABLE;
						SearchTable.wResultChairID=INVALID_CHAIR;
						SearchTable.wStartTableID=pServerViewItem->m_wFindTableID+1;

						//搜索桌子
						pServerViewItem->SearchGameTable(SearchTable);
						pServerViewItem->m_wFindTableID=SearchTable.wResultTableID;
					}

					//结果判断
					if (pServerViewItem->m_wFindTableID!=INVALID_CHAIR)
					{
						//效验数据
						ASSERT(SearchTable.wResultTableID!=INVALID_TABLE);
						ASSERT(SearchTable.wResultChairID!=INVALID_CHAIR);

						//设置数据
						WORD wChairID=SearchTable.wResultChairID;
						pServerViewItem->m_TableViewFrame.VisibleTable(pServerViewItem->m_wFindTableID);
						pServerViewItem->m_TableViewFrame.FlashGameChair(pServerViewItem->m_wFindTableID,wChairID);

						//自动坐下
						CParameterGlobal * pParameterGlobal=CParameterGlobal::GetInstance();
						if (pParameterGlobal->m_bAutoSitDown==true) pServerViewItem->PerformSitDownAction(pServerViewItem->m_wFindTableID,wChairID,true);
					}
					else
					{
						//提示消息
						CInformation Information(this);
						Information.ShowMessageBox(TEXT("抱歉，现在暂时没有可以加入的游戏桌，请稍后再次尝试！"),MB_ICONINFORMATION,30L);
					}

					break;
				}
			case ACTION_SHOW_SEARCH_DLG:	//查找桌子
				{
					//发送命令
					PostMessage(WM_COMMAND,IDC_BT_TABLE_BUTTON_2,0L);

					break;
				}
			}

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_2:		//查找桌子
		{
			//创建对象
			if (pServerViewItem->m_pDlgSearchTable==NULL)
			{
				//创建对象
				try
				{
					pServerViewItem->m_pDlgSearchTable=new CDlgSearchTable;
					if (pServerViewItem->m_pDlgSearchTable==NULL) return TRUE;
				}
				catch (...)
				{
					ASSERT(FALSE);
					return TRUE;
				}

				//设置对象
				pServerViewItem->m_pDlgSearchTable->SetServerViewItem(pServerViewItem);
				pServerViewItem->m_pDlgSearchTable->SetTableViewFrame(&pServerViewItem->m_TableViewFrame);
			}

			//创建窗口
			if (pServerViewItem->m_pDlgSearchTable->m_hWnd==NULL)
			{
				pServerViewItem->m_pDlgSearchTable->Create(IDD_DLG_SEARCH_TABLE,pServerViewItem);
			}

			//显示窗口
			pServerViewItem->m_pDlgSearchTable->ShowWindow(SW_SHOW);
			pServerViewItem->m_pDlgSearchTable->SetForegroundWindow();

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_3:		//锁定按钮
		{
			//变量定义
			CDlgTablePassword DlgTablePassword;

			//设置提示
			if(pServerViewItem->m_pParameterServer->m_bTakePassword)
			{
				lstrcpyn(DlgTablePassword.m_szPassword,pServerViewItem->m_pParameterServer->m_szPassword,CountArray(DlgTablePassword.m_szPassword));
				DlgTablePassword.SetPromptString(TEXT("该桌已设置进入密码，如要更改，请输入密码！如要解锁，请清空密码。"));
			}
			else
			{
				DlgTablePassword.SetPromptString(TEXT("请输入桌子进入密码。"));
			}

			//显示窗口
			if (DlgTablePassword.DoModal()==IDOK)
			{
				CString strTablePass = DlgTablePassword.m_szPassword;
				if(strTablePass.GetLength() > 0)
				{
					//设置密码
					pServerViewItem->m_pParameterServer->m_bTakePassword=true;
					lstrcpyn(pServerViewItem->m_pParameterServer->m_szPassword,DlgTablePassword.m_szPassword,CountArray(pServerViewItem->m_pParameterServer->m_szPassword));
				}
				else
				{
					//设置密码
					pServerViewItem->m_pParameterServer->m_bTakePassword=false;
					ZeroMemory(pServerViewItem->m_pParameterServer->m_szPassword,CountArray(pServerViewItem->m_pParameterServer->m_szPassword));
				}

				//发送规则
				pServerViewItem->SendUserRulePacket();
			}

			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_4:		//游戏设置
		{
			//构造变量
			CCollocateRoom DlgCollocate;
			DlgCollocate.InitCollocate(pServerViewItem->GetParameterGame(),pServerViewItem->GetParameterServer());

			//显示配置
			if (DlgCollocate.DoModal()==IDOK)
			{
				//发送规则
				pServerViewItem->SendUserRulePacket();
			}
			return TRUE;
		}
	case IDC_BT_TABLE_BUTTON_5:		//更多按钮
		{
			//构造菜单
			CSkinMenu FunctionMenu;
			FunctionMenu.CreateMenu();

			//更多菜单
			FunctionMenu.AppendMenu(IDM_GAME_RULE,TEXT("规则介绍"));

			//插入菜单
			if (pServerViewItem->m_pIMySelfUserItem->GetMasterOrder()>0)
			{
				//插入分割
				FunctionMenu.AppendSeparator();

				//插入菜单
				FunctionMenu.AppendMenu(IDM_MANAGER_USER,TEXT("游戏玩家管理..."),MF_ENABLED);
				FunctionMenu.AppendMenu(IDM_MANAGER_SERVER,TEXT("游戏房间管理..."),MF_DISABLED);
				FunctionMenu.AppendMenu(IDM_MANAGER_MESSAGE,TEXT("系统消息管理..."),MF_DISABLED);

				//设置菜单
				if (CMasterRight::CanManagerServer(pServerViewItem->m_dwMasterRight)==true)
				{
					FunctionMenu.EnableMenuItem(IDM_MANAGER_SERVER,MF_ENABLED);
				}

				//设置菜单
				if (CMasterRight::CanIssueMessage(pServerViewItem->m_dwMasterRight)==true)
				{
					FunctionMenu.EnableMenuItem(IDM_MANAGER_MESSAGE,MF_ENABLED);
				}
			}

			//弹出菜单
			CRect rcButton;
			m_btTableButton5.GetWindowRect(&rcButton);
			FunctionMenu.TrackPopupMenu(rcButton.left,rcButton.bottom,this);

			return TRUE;
		}
	}

	//发送命令
	return pServerViewItem->PostMessage(WM_COMMAND,wCommandID,lParam);
}

//绘画背景
BOOL CServerToolBar::OnEraseBkgnd(CDC * pDC)
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
	ImageGround.LoadFromResource(AfxGetInstanceHandle(),IDB_TOOL_BAR_BACK);

	//图像尺寸
	CSize SizeImageGournd(ImageGround.GetWidth(),ImageGround.GetHeight());

	//绘画背景
	for(INT nImageWidth=0;nImageWidth<rcClient.Width();nImageWidth +=SizeImageGournd.cx)
	{
		ImageGround.BitBlt(*pBufferDC,nImageWidth,0);
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//调整控件
VOID CServerToolBar::RectifyControl(INT nWidth, INT nHeight)
{
	//状态判断
	if( m_bCreateFlag==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//变量定义
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE|SWP_SHOWWINDOW;

	//关闭按钮
	CRect rcQuitServer;
	m_btQuitServer.GetWindowRect(&rcQuitServer);
	DeferWindowPos(hDwp,m_btQuitServer,NULL,nWidth-rcQuitServer.Width(),0,0,0,uFlags|SWP_NOSIZE);

	//桌子按钮
	INT nXPosTable=nWidth-rcQuitServer.Width();
	CSkinButton * TableButtonArray[]={&m_btTableButton5,&m_btTableButton4,&m_btTableButton3,&m_btTableButton2,&m_btTableButton1};

	//桌子按钮
	for (INT i=0;i<CountArray(TableButtonArray);i++)
	{
		//获取位置
		CRect rcTableButton;
		TableButtonArray[i]->GetWindowRect(&rcTableButton);

		//移动按钮
		nXPosTable-=(rcTableButton.Width()+BUTTON_H_SPACE);
		DeferWindowPos(hDwp,TableButtonArray[i]->m_hWnd,NULL,nXPosTable,0,0,0,uFlags|SWP_NOSIZE);
	}

	//结束调整
	EndDeferWindowPos(hDwp);

	return;
}


//事件消息
LRESULT CServerToolBar::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	//事件处理
	switch (wParam)
	{
	case EVENT_SERVER_LOGON_FINIDH:			//房间登录
		{
			//大厅框架
			CPlatformFrame * pPlatformFrame = CPlatformFrame::GetInstance();
			ASSERT(pPlatformFrame!=NULL);
			if(pPlatformFrame==NULL) return 0L;

			//房间视图
			CServerViewItem * pServerViewItem = pPlatformFrame->m_pServerViewItem;
			ASSERT(pServerViewItem!=NULL);
			if(pServerViewItem==NULL) return 0L;

			//规则判断
			if (CServerRule::IsForfendGameRule(pServerViewItem->m_dwServerRule)==false)
			{
				//发送规则
				pServerViewItem->SendUserRulePacket();

				//设置按钮
				m_btTableButton4.EnableWindow(TRUE);
			}

			//锁桌判断
			if (CServerRule::IsForfendLockTable(pServerViewItem->m_dwServerRule)==false)
			{
				//设置按钮
				m_btTableButton3.EnableWindow(TRUE);
			}

			//查找按钮
			if (CServerRule::IsAllowAvertCheatMode(pServerViewItem->m_dwServerRule)==false)
			{
				m_btTableButton2.EnableWindow(TRUE);
			}

			return 0L;
		}
	}

	return 0L;
}
//////////////////////////////////////////////////////////////////////////////////
