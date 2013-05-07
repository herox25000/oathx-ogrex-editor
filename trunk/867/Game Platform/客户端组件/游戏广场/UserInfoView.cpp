#include "Stdafx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "UserInfoView.h"

//////////////////////////////////////////////////////////////////////////

//颜色定义
#define CR_TEXT						RGB(0,0,0)					//字体颜色
#define CR_BACKGROUP				RGB(255,232,160)			//背景颜色

#define IDC_USER_INFO_EDIT			104									//编辑控件

//////////////////////////////////////////////////////////////////////////
//编辑框
BEGIN_MESSAGE_MAP(CEditUnderWrite, CSkinEditEx)
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

//userinfo界面
BEGIN_MESSAGE_MAP(CUserInfoView, CDialog)
	//系统消息
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()

	//自定消息
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CEditUnderWrite::CEditUnderWrite()
{
	//设置变量
	m_bNeedSend=false;
	m_pParentWnd=NULL;
	ZeroMemory(m_szUnderWrite,sizeof(m_szUnderWrite));

	return;
}

//析构函数
CEditUnderWrite::~CEditUnderWrite()
{
}

//消息解释
BOOL CEditUnderWrite::PreTranslateMessage(MSG * pMsg)
{
	//取消消息
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		//关闭控件
		CloseUnderWrite();
		return TRUE;
	}

	//确定消息
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_RETURN))
	{
		//设置焦点
		ASSERT(m_pParentWnd!=NULL);
		if (m_pParentWnd!=NULL)
			m_pParentWnd->SetFocus();

		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//接口查询
void * __cdecl CEditUnderWrite::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//连接事件
bool __cdecl CEditUnderWrite::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//错误判断
	if (nErrorCode!=0L)
	{
		//错误提示
		ShowInformationEx(TEXT("服务器连接失败，个性签名更新失败！"),0,MB_ICONQUESTION,TEXT("签名"));
		return true;
	}
	//设置变量
	m_bNeedSend=false;

	tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();

	//发送更改请求
	CMD_TOOLBOX_ModifyUnderWrite Write;
	ZeroMemory(&Write,sizeof(Write));
	Write.dwUserID = GlobalUserInfo.dwUserID;
	lstrcpyn(Write.szUnderWrite,m_szUnderWrite,CountArray(Write.szUnderWrite));
	m_SocketHelper->SendData(MDM_TOOLBOX,SUB_TOOLBOX_TMODIFYUNDERWRITE,&Write,sizeof(Write));

	return true;
}
//关闭事件
bool __cdecl CEditUnderWrite::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	CloseUnderWrite();
	return true;
}
//读取事件
bool __cdecl CEditUnderWrite::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	if(Command.wMainCmdID == MDM_TOOLBOX)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_TOOLBOX_OPERATERETURN:	
			{
				if(wDataSize != sizeof(CMD_TOOLBOX_OperateReturn))
					return true;
				CMD_TOOLBOX_OperateReturn* pReturn = (CMD_TOOLBOX_OperateReturn*)pData;

				//如果返回成功
				if(pReturn->lResultCode == 0)
				{
					tagGlobalUserData * pGlobalUserData= &g_GlobalUnits.GetGolbalUserData();
					lstrcpyn(pGlobalUserData->szUnderWrite,m_szUnderWrite,CountArray(pGlobalUserData->szUnderWrite));
				}
				//设置控件
				CloseUnderWrite();
				//显示消息
				if (pReturn->szDescribeString[0]!=0)
				{
					ShowInformationEx(pReturn->szDescribeString,0,MB_ICONQUESTION,TEXT("签名"));
				}
				return true;
			}
		}
	}
	//错误断言
	ASSERT(FALSE);
	return true;
}

bool CEditUnderWrite::IsModifyStatus()
{
	//状态判断
	if (m_bNeedSend==true) return true;
	//if (GetActiveStatus()==true) return true;

	return false;
}

//设置窗口
VOID CEditUnderWrite::SetParentWindow(CWnd * pParentWnd)
{
	//设置变量
	m_pParentWnd=pParentWnd;

	return;
}

//关闭控件
VOID CEditUnderWrite::CloseUnderWrite()
{
	//关闭判断
	if ((m_bNeedSend==false))
	{
		//销毁窗口
		DestroyWindow();
	}
	else
	{
		//隐藏窗口
		ShowWindow(SW_HIDE);
	}

	//更新界面
	ASSERT(m_pParentWnd!=NULL);
	m_pParentWnd->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//更新签名
VOID CEditUnderWrite::UpdateUnderWrite()
{
	if (IsWindowVisible()==TRUE)
	{
		//获取信息
		TCHAR szUnderWrite[UNDER_WRITE_LEN]=TEXT("");
		GetWindowText(szUnderWrite,CountArray(szUnderWrite));

		tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
		//更新判断
		bool bActiveMission=false;
		if ((IsModifyStatus()==true)&&(lstrcmp(szUnderWrite,m_szUnderWrite)!=0L)) 
			bActiveMission=true;
		if ((IsModifyStatus()==false)&&(lstrcmp(szUnderWrite,GlobalUserData.szUnderWrite)!=0L))
			bActiveMission=true;

		//更新判断
		if (bActiveMission==true)
		{
			//设置信息
			m_bNeedSend=true;
			lstrcpyn(m_szUnderWrite,szUnderWrite,CountArray(m_szUnderWrite));

			//创建组件
			if (m_SocketHelper.GetInterface()==NULL)
			{
				//初始化内核
				IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
				try 
				{
					IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
					if (m_SocketHelper.CreateInstance()==false) 
					{
						throw TEXT("网络连接失败1，抱歉！");
					}
					if (m_SocketHelper->SetTCPSocketSink(pIUnknownEx)==false) 
					{
						throw TEXT("网络连接失败2，抱歉！");
					}
				}
				catch (...)
				{
					ShowInformationEx(TEXT("网络连接失败3，抱歉！"),0,MB_ICONQUESTION,TEXT("签名"));
					return ;
				}
			}

			if (m_SocketHelper.GetInterface()!=NULL)
				m_SocketHelper->CloseSocket();

			DWORD dwIP = g_GlobalUnits.m_ServerListManager.m_dwToolServerAddr;
			WORD wPort = g_GlobalUnits.m_ServerListManager.m_wToolServerPort;
			if (dwIP!=0 && wPort!=0)
			{
				m_SocketHelper->Connect( dwIP, wPort);
			}
			else
			{
				ShowInformationEx("抱歉，此功能暂时不能使用！",0,MB_ICONQUESTION,TEXT("签名"));
				return ;
			}	
			//隐藏控件
			ShowWindow(SW_HIDE);
			//更新界面
			ASSERT(m_pParentWnd!=NULL);
			m_pParentWnd->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
		}
		else
		{
			//关闭控件
			CloseUnderWrite();
		}
	}
	return;
}

//消耗消息
VOID CEditUnderWrite::OnDestroy()
{
	__super::OnDestroy();

	if(m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
	//更新界面
	ASSERT(m_pParentWnd!=NULL);
	m_pParentWnd->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	return;
}

//失去焦点
VOID CEditUnderWrite::OnKillFocus(CWnd * pNewWnd)
{
	__super::OnKillFocus(pNewWnd);
	//关闭控件
	UpdateUnderWrite();
	return;
}



//////////////////////////////////////////////////////////////////////////

//构造函数
CUserInfoView::CUserInfoView() : CDialog(IDD_USER_INFO)
{
	//状态变量
	m_nTitleHeight=0;
	m_bShowInfo=false;
	m_bCreateFlag=false;
	m_bHoverUnderWrite = false;
	m_EditUnderWrite.SetParentWindow(this);
	return;
}

//析构函数
CUserInfoView::~CUserInfoView()
{
}

//控件绑定
VOID CUserInfoView::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}

//初始化函数
BOOL CUserInfoView::OnInitDialog()
{
	__super::OnInitDialog();

	//加载资源
	UpdateSkinResource();

	//获取大小
	CImageHandle HandleTitleM(&m_ImageTitleM);
	m_nTitleHeight=m_ImageTitleM.GetHeight();

	//移动窗口
	SetWindowPos(NULL,0,0,0,m_nTitleHeight,SWP_NOMOVE|SWP_NOZORDER);

	//设置变量
	m_bCreateFlag=true;

	return TRUE;
}

//标题高度
UINT CUserInfoView::GetTitleHeight()
{
	return m_nTitleHeight;
}

//更新信息
VOID CUserInfoView::UpdateUserInfo()
{
	//更新界面
	Invalidate();

	return;
}

//显示信息
VOID CUserInfoView::ShowUserInfo(bool bShowInfo)
{
	//状态判断
	if (m_bShowInfo==bShowInfo) return;

	//设置变量
	m_bShowInfo=bShowInfo;

	//更新界面
	Invalidate();

	return;
}

//更新资源
bool CUserInfoView::UpdateSkinResource()
{
	//获取资源
	tagControlViewImage & ControlViewImage=g_GlobalUnits.m_ControlViewImage;
	HINSTANCE hInstance=g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	m_ImageTitleL.SetLoadInfo(ControlViewImage.uUserInfoL,hInstance);
	m_ImageTitleM.SetLoadInfo(ControlViewImage.uUserInfoM,hInstance);
	m_ImageTitleR.SetLoadInfo(ControlViewImage.uUserInfoR,hInstance);

	return true;
}

//绘画背景
BOOL CUserInfoView::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),24);

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//加载资源
	CImageHandle HandleTitleL(&m_ImageTitleL);
	CImageHandle HandleTitleM(&m_ImageTitleM);
	CImageHandle HandleTitleR(&m_ImageTitleR);

	//绘画背景
	m_ImageTitleL.BitBlt(BufferDC,0,0);

	//填充中间
	for (INT nXPos=m_ImageTitleL.GetWidth();nXPos<rcClient.Width();nXPos+=m_ImageTitleM.GetWidth())
	{
		m_ImageTitleM.BitBlt(BufferDC,nXPos,0);
	}

	//绘画背景
	m_ImageTitleR.BitBlt(BufferDC,rcClient.Width()-m_ImageTitleR.GetWidth(),0);

	//设置 DC
	pBufferDC->SetTextColor(CR_TEXT);
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetDefaultFont());

	//用户信息
	if (m_bShowInfo==true)
	{
		//变量定义
		tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();

		//绘制个性签名编辑框底框
		if ((m_bHoverUnderWrite==true)||((m_EditUnderWrite.m_hWnd!=NULL)&&(m_EditUnderWrite.IsWindowVisible()==TRUE)))
		{
			//加载资源
			CPngImage ImageUnderWriteL;
			CPngImage ImageUnderWriteM;
			CPngImage ImageUnderWriteR;
			ImageUnderWriteL.LoadImage(AfxGetInstanceHandle(),TEXT("UNDER_WRITE_L"));
			ImageUnderWriteM.LoadImage(AfxGetInstanceHandle(),TEXT("UNDER_WRITE_M"));
			ImageUnderWriteR.LoadImage(AfxGetInstanceHandle(),TEXT("UNDER_WRITE_R"));

			//绘画两边
			ImageUnderWriteL.DrawImage(pBufferDC,m_rcUnderWrite.left,m_rcUnderWrite.top);
			ImageUnderWriteR.DrawImage(pBufferDC,m_rcUnderWrite.right-ImageUnderWriteR.GetWidth(),m_rcUnderWrite.top);

			//绘画中间
			INT nXStart=m_rcUnderWrite.left+ImageUnderWriteL.GetWidth();
			INT nXTerminate=m_rcUnderWrite.right-ImageUnderWriteR.GetWidth();
			for (INT nXPos=nXStart;nXPos<nXTerminate;nXPos+=ImageUnderWriteM.GetWidth())
			{
				ImageUnderWriteM.DrawImage(pBufferDC,nXPos,m_rcUnderWrite.top,__min(nXTerminate-nXPos,ImageUnderWriteM.GetWidth()),ImageUnderWriteM.GetHeight(),0,0);
			}
		}

		//用户头像
		g_GlobalUnits.m_UserFaceRes->DrawNormalFace(pBufferDC,37,27,GlobalUserInfo.wFaceID,GlobalUserInfo.dwUserID,GlobalUserInfo.dwCustomFaceVer);

		//构造位置
		TCHAR szBuffer[255]=TEXT("");
		CRect rcAccounts(150, 23, rcClient.Width()-20, 37);
		CRect rcID(150, 64,rcClient.Width()-20, 37);
		//用户帐号
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%s"),GlobalUserInfo.szAccounts);
		pBufferDC->DrawText(szBuffer,lstrlen(szBuffer),&rcAccounts,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d"),GlobalUserInfo.dwGameID);
		pBufferDC->DrawText(szBuffer,lstrlen(szBuffer),&rcID,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);

		//变量定义
		TCHAR pszUnderWrite[UNDER_WRITE_LEN]=TEXT("");
		COLORREF crUnderWrite=RGB(0,0,0);
		//签名位置
		CRect rcUnderWrite(153,68,rcClient.Width()-20,80);
		//常规状态
		if ((m_EditUnderWrite.IsModifyStatus()==false)&&(GlobalUserInfo.szUnderWrite[0]!=0))
		{
			crUnderWrite=RGB(0,0,0);
			_sntprintf(pszUnderWrite,CountArray(pszUnderWrite),TEXT("%s"),GlobalUserInfo.szUnderWrite);
		}
		//修改状态
		if ((m_EditUnderWrite.IsModifyStatus()==true)&&(m_EditUnderWrite.m_szUnderWrite[0]!=0))
		{
			crUnderWrite=RGB(100,100,100);
			//pszUnderWrite=m_EditUnderWrite.m_szUnderWrite;
			_sntprintf(pszUnderWrite,CountArray(pszUnderWrite),TEXT("%s"),m_EditUnderWrite.m_szUnderWrite);

		}
		//提示状态
		if (pszUnderWrite==NULL)
		{
			crUnderWrite=RGB(255,150,150);
			//pszUnderWrite=TEXT("编辑个性签名");
			_sntprintf(pszUnderWrite,CountArray(pszUnderWrite),TEXT("编辑个性签名"));

		}
		//输出签名
		pBufferDC->SetTextColor(crUnderWrite);
		pBufferDC->DrawText(pszUnderWrite,lstrlen(pszUnderWrite),&rcUnderWrite,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//位置消息
VOID CUserInfoView::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	return;
}

//调整控件
VOID CUserInfoView::RectifyControl(INT nWidth, INT nHeight)
{
	//设置区域
	m_rcUnderWrite.SetRect(150,65,nWidth-20,85);
}
//鼠标消息
VOID CUserInfoView::OnLButtonUp(UINT nFlags, CPoint MousePoint)
{
}
//鼠标消息
VOID CUserInfoView::OnLButtonDown(UINT nFlags, CPoint MousePoint)
{
	__super::OnLButtonDown(nFlags,MousePoint);
	//设置焦点
	SetFocus();
	//编辑签名
	if (m_bHoverUnderWrite==true)
	{
		//用户信息
		tagGlobalUserData & pGlobalUserData=g_GlobalUnits.GetGolbalUserData();

		//创建控件
		if (m_EditUnderWrite.m_hWnd==NULL)
		{
			//创建控件
			m_EditUnderWrite.Create(WS_CHILD|ES_AUTOHSCROLL,CRect(0,0,0,0),this,IDC_USER_INFO_EDIT);
			//设置信息
			m_EditUnderWrite.LimitText(UNDER_WRITE_LEN-1L);
			m_EditUnderWrite.SetWindowText(pGlobalUserData.szUnderWrite);
			CFont * pFont = CFont::FromHandle(CSkinResourceManager::GetDefaultFont());
			//设置控件
			m_EditUnderWrite.SetFont(pFont);
		}

		//调整位置
		CRect rcClient;
		GetClientRect(&rcClient);
		m_EditUnderWrite.SetWindowPos(NULL,150+3,65+3,rcClient.Width()-170-6,20-6,SWP_SHOWWINDOW|SWP_NOZORDER);
		//设置控件
		m_EditUnderWrite.SetFocus();
		m_EditUnderWrite.SetSel(0L,-1L);
		//更新窗口
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
}
//光标消息
BOOL CUserInfoView::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//获取光标
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);
	bool bRedrawWindow=false;

	//盘旋判断
	if ((m_bHoverUnderWrite==false)&&(m_rcUnderWrite.PtInRect(MousePoint)==TRUE))
	{
		//设置变量
		bRedrawWindow=true;

		//设置变量
		m_bHoverUnderWrite=true;
	}

	//离开判断
	if ((m_bHoverUnderWrite==true)&&(m_rcUnderWrite.PtInRect(MousePoint)==FALSE))
	{
		//设置变量
		bRedrawWindow=true;
		//设置变量
		m_bHoverUnderWrite=false;
	}

	//更新界面
	if (bRedrawWindow==true)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//鼠标离开
LRESULT CUserInfoView::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//离开处理
	if (m_bHoverUnderWrite==true)
	{
		//设置变量
		m_bHoverUnderWrite=false;
		//更新界面
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
