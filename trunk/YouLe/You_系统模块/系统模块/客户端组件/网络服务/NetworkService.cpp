#include "Stdafx.h"
#include "AfxDLLx.h"
#include "WinSock2.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
static AFX_EXTENSION_MODULE NetworkServiceDLL={NULL,NULL};

//////////////////////////////////////////////////////////////////////////

//DLL ������
extern "C" INT APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason==DLL_PROCESS_ATTACH)
	{
		if (!AfxInitExtensionModule(NetworkServiceDLL, hInstance)) return 0;
		new CDynLinkLibrary(NetworkServiceDLL);

		//��ʼ������
		WSADATA WSAData;
		WORD wVersionRequested=MAKEWORD(1,1);
		if (WSAStartup(wVersionRequested,&WSAData)!=0) return 0;
	}
	else if (dwReason==DLL_PROCESS_DETACH)
	{
		AfxTermExtensionModule(NetworkServiceDLL);

		//��������
		WSACleanup();
	}

	return 1;
}

//////////////////////////////////////////////////////////////////////////
