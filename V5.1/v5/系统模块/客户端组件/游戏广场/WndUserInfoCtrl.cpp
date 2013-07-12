#include "Stdafx.h"
#include "GamePlaza.h"
#include "DlgService.h"
#include "PlatformFrame.h"
#include "DlgLockMachine.h"
#include "WndUserInfoCtrl.h"

//////////////////////////////////////////////////////////////////////////////////

//控制按钮
#define IDC_USER_INFO_1				100									//用户按钮
#define IDC_USER_INFO_2				101									//用户按钮
#define IDC_USER_INFO_3				102									//用户按钮

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CWndUserInfoCtrl, CWnd)

	//系统消息
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()

	//自定消息
	ON_MESSAGE(WM_PLATFORM_EVENT, OnMessagePlatformEvent)


END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CWndUserInfoCtrl::CWndUserInfoCtrl()
{
	//变量定义
	m_pDlgInsurePlaza = NULL;
}

//析构函数
CWndUserInfoCtrl::~CWndUserInfoCtrl()
{
}

//命令函数
BOOL CWndUserInfoCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//变量定义
	UINT nCommandID=LOWORD(wParam);

	//功能按钮
	switch (nCommandID)
	{
	case IDC_USER_INFO_1:		//个人中心
		{
			//播放声音
			CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
			if(pGlobalUnits!=NULL)
			{
				pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
			}

			//个人设置
			CDlgService DlgService;
			DlgService.DoModal();
						
			return TRUE;
		}
	case IDC_USER_INFO_2:		//财务信息
		{
			//播放声音
			CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
			if(pGlobalUnits!=NULL)
			{
				pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
			}

			//设置资源
			AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

			//获取指针
			CPlatformFrame * pPlatformFrame =  (CPlatformFrame *)CPlatformFrame::GetInstance();
			if(pPlatformFrame->m_pServerViewItem != NULL )
			{
				pPlatformFrame->m_pServerViewItem->ShowInsureView();
			}
			else
			{
				//广场银行
				CDlgInsurePlaza DlgInsurePlaza;

				//设置变量
				m_pDlgInsurePlaza =&DlgInsurePlaza;
				INT_PTR nResult=DlgInsurePlaza.DoModal();

				m_pDlgInsurePlaza=NULL;
			}

			break;
		}
	case IDC_USER_INFO_3:		//历史记录
		{
			//播放声音
			CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
			if(pGlobalUnits!=NULL)
			{
				pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
			}

			//用户信息
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			DWORD dwUserID = pGlobalUserData?pGlobalUserData->dwUserID:0L;

			//变量定义
			TCHAR szOpenAddr[96] = TEXT("");
			_sntprintf(szOpenAddr,CountArray(szOpenAddr),TEXT("UserService/UService2.aspx?UID=%d&PWD=%s"),dwUserID,pGlobalUserData->szPassword);
			
			//弹出窗口
			CDlgServiceWebBrowse DlgServiceWebBrowse(TEXT("财务记录"),szOpenAddr);
			DlgServiceWebBrowse.DoModal();

			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//位置消息
VOID CWndUserInfoCtrl::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//调整控件
	RectifyControl(cx,cy);

	return;
}

//建立消息
INT CWndUserInfoCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//注册事件
	CPlatformEvent * pPlatformEvent=CPlatformEvent::GetInstance();
	if (pPlatformEvent!=NULL) pPlatformEvent->RegisterEventWnd(m_hWnd);

	//加载资源
	CBitImage ImageTitleM;
	ImageTitleM.LoadFromResource(AfxGetInstanceHandle(),IDB_USER_INFO_M);

	//创建按钮
	CRect rcCreate(0,0,0,0);
	m_btUserInfo1.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_USER_INFO_1);
	m_btUserInfo2.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_USER_INFO_2);
	m_btUserInfo3.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_USER_INFO_3);

	//设置按钮
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btUserInfo1.SetButtonImage(IDB_BK_USER_INFO,TEXT("BT_USER_INFO_1"),hInstance,true,false);
	m_btUserInfo2.SetButtonImage(IDB_BK_USER_INFO,TEXT("BT_USER_INFO_2"),hInstance,true,false);
	m_btUserInfo3.SetButtonImage(IDB_BK_USER_INFO,TEXT("BT_USER_INFO_3"),hInstance,true,false);

	//移动窗口
	CRect rcUserInfo;
	GetWindowRect(&rcUserInfo);
	SetWindowPos(NULL,0,0,rcUserInfo.Width(),ImageTitleM.GetHeight(),SWP_NOMOVE|SWP_NOZORDER);

	return 0;
}

//调整控件
VOID CWndUserInfoCtrl::RectifyControl(INT nWidth, INT nHeight)
{
	//变量定义
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE;

	//按钮大小
	CRect rcButton;
	m_btUserInfo1.GetWindowRect(&rcButton);

	//位置定义
	UINT nSpace=1;
	UINT nXStartPos=18;
	UINT nYStartPos=120;

	//调整按钮
	DeferWindowPos(hDwp,m_btUserInfo1,NULL,nXStartPos,nYStartPos,0,0,uFlags);
	DeferWindowPos(hDwp,m_btUserInfo2,NULL,nXStartPos,nYStartPos+rcButton.Height()+nSpace,0,0,uFlags);
	DeferWindowPos(hDwp,m_btUserInfo3,NULL,nXStartPos,nYStartPos+(rcButton.Height()+nSpace)*2,0,0,uFlags);

	//结束调整
	EndDeferWindowPos(hDwp);

	return;
}


//转换字符
VOID CWndUserInfoCtrl::SwitchScoreFormat(SCORE lScore, UINT uSpace,UINT uDecimalCount,LPTSTR pszBuffer, WORD wBufferSize)
{
	//转换数值
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%d"),lScore);

	//变量定义
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore)-uDecimalCount-1;

	//转换字符
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//拷贝字符
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//插入逗号
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L) && (uSwitchLength-wSourceIndex)!=0)
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//结束字符
	pszBuffer[wTargetIndex++]=0;

	return;
}

//绘画背景
BOOL CWndUserInfoCtrl::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建 DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//变量定义
	HINSTANCE hInstance=AfxGetInstanceHandle();
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	//加载资源
	CBitImage ImageTitleL;
	CBitImage ImageTitleM;
	CBitImage ImageTitleR;
	ImageTitleL.LoadFromResource(hInstance,IDB_USER_INFO_L);
	ImageTitleM.LoadFromResource(hInstance,IDB_USER_INFO_M);
	ImageTitleR.LoadFromResource(hInstance,IDB_USER_INFO_R);

	//渲染资源
	pSkinRenderManager->RenderImage(ImageTitleL);
	pSkinRenderManager->RenderImage(ImageTitleM);
	pSkinRenderManager->RenderImage(ImageTitleR);

	//绘画背景
	ImageTitleL.BitBlt(BufferDC,0,0);

	//填充中间
	for (INT nXPos=ImageTitleL.GetWidth();nXPos<rcClient.Width();nXPos+=ImageTitleM.GetWidth())
	{
		ImageTitleM.BitBlt(BufferDC,nXPos,0);
	}

	//绘画背景
	ImageTitleR.BitBlt(BufferDC,rcClient.Width()-ImageTitleR.GetWidth(),0);

	//设置环境
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SetTextColor(RGB(255,255,255));
	pBufferDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//用户信息
	CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
	tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

	//绘画用户
	if (pGlobalUserData->dwUserID!=0L)
	{
		//构造信息
		TCHAR szScore[32]=TEXT("");
		TCHAR szInsure[32]=TEXT("");
		SwitchScoreFormat(pGlobalUserData->lUserScore,3,2,szScore,CountArray(szScore));
		SwitchScoreFormat(pGlobalUserData->lUserInsure,3,2,szInsure,CountArray(szInsure));

		//输出积分
		CRect rcScore;
		rcScore.SetRect(57,36,rcClient.Width()-18,68);
		pBufferDC->SetTextColor(RGB(255,211,91));
		pBufferDC->DrawText(szScore,lstrlen(szScore),&rcScore,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		//输出银行
		CRect rcInsure;
		rcInsure.SetRect(57,65,rcClient.Width()-18,97);
		pBufferDC->SetTextColor(RGB(255,180,0));
		pBufferDC->DrawText(szInsure,lstrlen(szInsure),&rcInsure,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);

		//输出帐号
		CRect rcAccounts;
		rcAccounts.SetRect(57,8,rcClient.Width()-18,37);
		pBufferDC->SetTextColor(RGB(123,253,255));
		pBufferDC->DrawText(pGlobalUserData->szNickName,lstrlen(pGlobalUserData->szNickName),&rcAccounts,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//事件消息
LRESULT CWndUserInfoCtrl::OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case EVENT_USER_LOGON:			//登录成功
		{
			//更新窗口
			Invalidate();

			//设置按钮
			m_btUserInfo1.EnableWindow(TRUE);
			m_btUserInfo2.EnableWindow(TRUE);
			m_btUserInfo3.EnableWindow(TRUE);

			return 0L;
		}
	case EVENT_USER_LOGOUT:			//注销成功
		{
			//更新窗口
			Invalidate();

			//设置按钮
			m_btUserInfo1.EnableWindow(FALSE);
			m_btUserInfo2.EnableWindow(FALSE);
			m_btUserInfo3.EnableWindow(FALSE);

			return 0L;
		}
	case EVENT_USER_INFO_UPDATE:	//资料更新
		{
			//变量定义
			CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
			tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();
			ASSERT(pGlobalUserData!=NULL);

			//更新银行
			/*if(m_pDlgInsurePlaza!=NULL) 
				m_pDlgInsurePlaza->OnEventUpdateInsurePlaza(pGlobalUserData->lUserScore,pGlobalUserData->lUserInsure);*/

			//更新窗口
			Invalidate();

			return 0L;
		}
	}

	return 0L;
}


//////////////////////////////////////////////////////////////////////////////////
