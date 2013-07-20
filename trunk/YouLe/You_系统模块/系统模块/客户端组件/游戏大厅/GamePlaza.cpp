// GamePlaza.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "GamePlaza.h"
#include "GamePlazaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGamePlazaApp

BEGIN_MESSAGE_MAP(CGamePlazaApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CGamePlazaApp 构造

CGamePlazaApp::CGamePlazaApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CGamePlazaApp 对象

CGamePlazaApp theApp;


// CGamePlazaApp 初始化

BOOL CGamePlazaApp::InitInstance()
{
	__super::InitInstance();

	//判断是否重入
#ifndef ADMIN_PLAZA
#ifndef _DEBUG
	bool bExistIGame=false;
	CMutex Mutex(FALSE,MAIN_DLG_CLASSNAME,NULL);
	if (Mutex.Lock(0)==FALSE) bExistIGame=true;
	CWnd * pIGameWnd=CWnd::FindWindow(MAIN_DLG_CLASSNAME,NULL);
	if (pIGameWnd!=NULL) 
	{
		bExistIGame=true;
		if (pIGameWnd->IsIconic()) pIGameWnd->ShowWindow(SW_RESTORE);
		pIGameWnd->SetActiveWindow();
		pIGameWnd->BringWindowToTop();
		pIGameWnd->SetForegroundWindow();
	}
	if (bExistIGame==true) return FALSE;
#endif
#endif

	//环境配置
	AfxOleInit();
	AfxInitRichEdit();
	AfxInitRichEdit2();
	InitCommonControls();
	AfxEnableControlContainer();

	//设置表名
	SetRegistryKey(szSystemRegKey);

	//加载配置
	g_GlobalOption.LoadOptionParameter();

	//全局信息
	if (g_GlobalUnits.InitGlobalUnits()==false)
	{
		ShowInformation(TEXT("游戏广场初始化失败，程序即将退出！"),0,MB_ICONSTOP);
		return FALSE;
	}

	//变量定义
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//注册窗口
	WndClasss.style=CS_DBLCLKS;
	WndClasss.lpfnWndProc=DefWindowProc;
	WndClasss.lpszClassName=MAIN_DLG_CLASSNAME;
	WndClasss.hInstance=AfxGetInstanceHandle();
	WndClasss.hIcon=LoadIcon(MAKEINTRESOURCE(IDR_MAINFRAME));
	WndClasss.hCursor=LoadStandardCursor(MAKEINTRESOURCE(IDC_ARROW));
	if (AfxRegisterClass(&WndClasss)==FALSE) AfxThrowResourceException();

	//建立窗口
	CGameFrame * pMainFrame=new CGameFrame();
	pMainFrame->Create(MAIN_DLG_CLASSNAME,TEXT(""),WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CRect(0,0,0,0));
	m_pMainWnd=pMainFrame;

	return TRUE;
}
