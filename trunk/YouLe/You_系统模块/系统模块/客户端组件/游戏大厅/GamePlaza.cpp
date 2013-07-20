// GamePlaza.cpp : ����Ӧ�ó��������Ϊ��
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


// CGamePlazaApp ����

CGamePlazaApp::CGamePlazaApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CGamePlazaApp ����

CGamePlazaApp theApp;


// CGamePlazaApp ��ʼ��

BOOL CGamePlazaApp::InitInstance()
{
	__super::InitInstance();

	//�ж��Ƿ�����
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

	//��������
	AfxOleInit();
	AfxInitRichEdit();
	AfxInitRichEdit2();
	InitCommonControls();
	AfxEnableControlContainer();

	//���ñ���
	SetRegistryKey(szSystemRegKey);

	//��������
	g_GlobalOption.LoadOptionParameter();

	//ȫ����Ϣ
	if (g_GlobalUnits.InitGlobalUnits()==false)
	{
		ShowInformation(TEXT("��Ϸ�㳡��ʼ��ʧ�ܣ����򼴽��˳���"),0,MB_ICONSTOP);
		return FALSE;
	}

	//��������
	WNDCLASS WndClasss;
	ZeroMemory(&WndClasss,sizeof(WndClasss));

	//ע�ᴰ��
	WndClasss.style=CS_DBLCLKS;
	WndClasss.lpfnWndProc=DefWindowProc;
	WndClasss.lpszClassName=MAIN_DLG_CLASSNAME;
	WndClasss.hInstance=AfxGetInstanceHandle();
	WndClasss.hIcon=LoadIcon(MAKEINTRESOURCE(IDR_MAINFRAME));
	WndClasss.hCursor=LoadStandardCursor(MAKEINTRESOURCE(IDC_ARROW));
	if (AfxRegisterClass(&WndClasss)==FALSE) AfxThrowResourceException();

	//��������
	CGameFrame * pMainFrame=new CGameFrame();
	pMainFrame->Create(MAIN_DLG_CLASSNAME,TEXT(""),WS_CLIPCHILDREN|WS_CLIPSIBLINGS,CRect(0,0,0,0));
	m_pMainWnd=pMainFrame;

	return TRUE;
}
