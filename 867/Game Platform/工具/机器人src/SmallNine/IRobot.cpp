#include "StdAfx.h"
#include ".\irobot.h"

IRobot::IRobot(DWORD dwUserID) : m_dwUserID(dwUserID)
{
}

IRobot::~IRobot(void)
{
}

DWORD			IRobot::GetUserID() const
{
	return m_dwUserID;
}

//网卡地址
WORD			IRobot::GetMACAddress(BYTE cbMacBuffer[], WORD wBufferSize)
{
	//变量定义
	WORD wMacSize=0;
	HINSTANCE hInstance=NULL;
	typedef BYTE __stdcall NetBiosProc(NCB * Ncb);

	try
	{
		//加载 DLL
		hInstance=LoadLibrary(TEXT("NetApi32.dll"));
		if (hInstance==NULL) 
			throw TEXT("加载 NetApi32.dll 失败");

		//获取函数
		NetBiosProc * pNetBiosProc=(NetBiosProc *)GetProcAddress(hInstance,"Netbios");
		if (pNetBiosProc==NULL) 
			throw TEXT("无法找到 NetBios 函数");

		//变量定义
		NCB Ncb;
		LANA_ENUM LanaEnum;
		ZeroMemory(&Ncb,sizeof(Ncb));
		ZeroMemory(&LanaEnum,sizeof(LanaEnum));

		//枚举网卡
		Ncb.ncb_command=NCBENUM;
		Ncb.ncb_length=sizeof(LanaEnum);
		Ncb.ncb_buffer=(BYTE *)&LanaEnum;
		if (pNetBiosProc(&Ncb)!=NRC_GOODRET) throw TEXT("枚举网卡失败");
		if (LanaEnum.length==0)
			throw TEXT("找不到任何网卡");

		//获取地址
		tagAstatInfo Adapter;
		for (BYTE i=0;i<LanaEnum.length;i++)
		{
			//重置网卡
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBRESET;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET) 
				throw TEXT("重置网卡失败");

			//获取状态
			ZeroMemory(&Ncb,sizeof(Ncb));
			Ncb.ncb_command=NCBASTAT;
			Ncb.ncb_length=sizeof(Adapter);
			Ncb.ncb_buffer=(BYTE *)&Adapter;
			Ncb.ncb_lana_num=LanaEnum.lana[i];
			strcpy((char *)Ncb.ncb_callname,"*");
			if (pNetBiosProc(&Ncb)!=NRC_GOODRET)
				throw TEXT("获取网卡状态失败");

			//获取地址
			if (wMacSize<wBufferSize)
			{
				//拷贝地址
				WORD wCopySize=__min((wBufferSize-wMacSize),sizeof(BYTE)*6);
				CopyMemory(cbMacBuffer,Adapter.AdapterStatus.adapter_address,wCopySize);

				//完成判断
				wMacSize+=wCopySize;
				if (wMacSize==wBufferSize) break;
			}
		}

		//释放资源
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}

		return wMacSize;
	}
	catch (...) 
	{ 
		//释放资源
		if (hInstance!=NULL)
		{
			FreeLibrary(hInstance);
			hInstance=NULL;
		}
	}

	return wMacSize;
}


//获取序列
void		IRobot::GetClientSerial(tagClientSerial & ClientSerial)
{
	//获取版本
	OSVERSIONINFO OSVerInfo;
	OSVerInfo.dwOSVersionInfoSize=sizeof(OSVerInfo);
	GetVersionEx(&OSVerInfo);
	ClientSerial.dwSystemVer=MAKELONG(OSVerInfo.dwMajorVersion,OSVerInfo.dwMinorVersion);

	//网卡标识
	ZeroMemory(ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));
	WORD wMacSize=GetMACAddress((BYTE *)ClientSerial.dwComputerID,sizeof(ClientSerial.dwComputerID));

	//硬盘标识
	WORD wIndex=(wMacSize+sizeof(DWORD)-1)/sizeof(DWORD);
	LPCTSTR pszHardDisk[]={TEXT("C:\\"),TEXT("D:\\"),TEXT("E:\\")};
	for (WORD i=wIndex;i<CountArray(ClientSerial.dwComputerID);i++)
	{
		ASSERT(CountArray(pszHardDisk)>(i-wIndex));
		GetVolumeInformation(pszHardDisk[i-wIndex],NULL,0,&ClientSerial.dwComputerID[i],NULL,NULL,0,NULL);
	}

	return;
}

bool __cdecl	IRobot::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	return 0;
}

bool __cdecl	IRobot::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	return 0;
}

bool __cdecl	IRobot::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	return 0;
}