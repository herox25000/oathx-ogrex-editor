#include "stdafx.h"
#include "GamePlaza.h"
#include "GamePlazaDlg.h"
#include "PlatformFrame.h"
#include "Platform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CGamePlazaApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CGamePlazaApp::CGamePlazaApp()
{

}

BOOL CGamePlazaApp::InitInstance()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	bool bPlazaExist=false;
	CMutex Mutex(FALSE,SZ_PLAZACLASS,NULL);
	if (Mutex.Lock(0)==FALSE)
		bPlazaExist=true;

	//搜索窗口
	CWnd * pWndGamePlaza=CWnd::FindWindow(SZ_PLAZACLASS,NULL);
	if (pWndGamePlaza!=NULL) 
	{
		//设置变量
		bPlazaExist=true;

		//还原窗口
		if (pWndGamePlaza->IsIconic()) 
		{
			pWndGamePlaza->ShowWindow(SW_RESTORE);
		}

		//激活窗口
		pWndGamePlaza->SetActiveWindow();
		pWndGamePlaza->BringWindowToTop();
		pWndGamePlaza->SetForegroundWindow();
	}

	//结果处理
	if (bPlazaExist == true) 
		return FALSE;

	//环境配置
	AfxOleInit();
	AfxInitRichEdit2();

	InitCommonControls();
	AfxEnableControlContainer();

	//随机种子
	srand((DWORD)time(NULL));

	//变量定义
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//注册窗口
	WndClasss.style			= CS_DBLCLKS;
	WndClasss.hIcon			= LoadIcon(IDR_MAINFRAME);
	WndClasss.lpfnWndProc	= DefWindowProc;
	WndClasss.lpszClassName	= SZ_PLAZACLASS;
	WndClasss.hInstance		= AfxGetInstanceHandle();
	WndClasss.hCursor		= LoadStandardCursor(MAKEINTRESOURCE(IDC_ARROW));
	if (AfxRegisterClass(&WndClasss)==FALSE)
		AfxThrowResourceException();

	//建立窗口
	CPlatformFrame * pPlatformFrame=new CPlatformFrame();
	pPlatformFrame->Create(SZ_PLAZACLASS, SZ_PLAZANAME, WS_CLIPCHILDREN|WS_CLIPSIBLINGS, CRect(0,0,0,0));
	m_pMainWnd=pPlatformFrame;

	return TRUE;
}

int CGamePlazaApp::ExitInstance()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}

CGamePlazaApp theApp;
