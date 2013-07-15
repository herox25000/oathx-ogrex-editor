// DeskMagicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DeskMagic.h"
#include "DeskMagicDlg.h"
#include ".\deskmagicdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDeskMagicDlg 对话框
///////////////////////////////////////////////////////


#define MAX_CHAIR						100								//最大椅子


//资源配置结构
struct tagTableResourceInfo
{
	COLORREF							crName;								//名字颜色
	COLORREF							crNote;								//备注颜色
	COLORREF							crTableID;							//号码颜色
	POINT								ptLock;								//锁位置
	RECT								rcNote;								//备注位置
	RECT								rcTableID;							//桌号位置
	RECT								rcName[MAX_CHAIR];					//名字位置
	RECT								rcChair[MAX_CHAIR];					//椅子位置
	POINT								ptReady[MAX_CHAIR];					//准备位置
	INT									nDrawStyle[MAX_CHAIR];				//输出格式
};


//配置文件结构
struct tagTableConfigFile
{
	WORD								wFileSize;							//文件大小
	WORD								wStructVer;							//结构版本
	tagTableResourceInfo				TableResourceInfo;					//配置参数
};


tagTableConfigFile g_TableConfig;

///////////////////////////////////////////////////////



CDeskMagicDlg::CDeskMagicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeskMagicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeskMagicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDeskMagicDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CDeskMagicDlg 消息处理程序

BOOL CDeskMagicDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDeskMagicDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CDeskMagicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDeskMagicDlg::LoadFileDat(LPCTSTR szFile)
{
	CFile ResourceFile;
	TCHAR szResourcePath[MAX_PATH];
	_snprintf(szResourcePath,sizeof(szResourcePath),szFile);
	if (ResourceFile.Open(szResourcePath,CFile::modeRead,NULL)==FALSE) throw 0;

	//读取配置
	ZeroMemory(&g_TableConfig,sizeof(g_TableConfig));
	ULONGLONG uLong=ResourceFile.GetLength();
	if(uLong!=sizeof(tagTableConfigFile))	return FALSE;

	UINT uReadCount=ResourceFile.Read(&g_TableConfig,sizeof(g_TableConfig));

	ResourceFile.Close();

	return 0;
}

BOOL CDeskMagicDlg::SaveFileDat(LPCTSTR szFile)
{
	CFile ResourceFile;
	TCHAR szResourcePath[MAX_PATH];
	_snprintf(szResourcePath,sizeof(szResourcePath),szFile);
	if (ResourceFile.Open(szResourcePath,CFile::modeCreate|CFile::modeWrite,NULL)==FALSE) return FALSE;

	ResourceFile.Write(&g_TableConfig,sizeof(g_TableConfig));

	ResourceFile.Close();

	return TRUE;
}

BOOL CDeskMagicDlg::LoadFileIni(LPCTSTR szFile)
{
	CString szAppName=TEXT("Main");
	CString szKeyName=TEXT("FileSize");
	TCHAR szResult[128];

	ZeroMemory(&g_TableConfig,sizeof(g_TableConfig));
	g_TableConfig.wFileSize=sizeof(g_TableConfig);

	szKeyName=TEXT("FileVers");
	g_TableConfig.wStructVer=GetPrivateProfileInt(szAppName,szKeyName,2,szFile);

	szKeyName=TEXT("crName");
	g_TableConfig.TableResourceInfo.crName=GetPrivateProfileInt(szAppName,szKeyName,0xC8C8C8,szFile);
	szKeyName=TEXT("crNote");
	g_TableConfig.TableResourceInfo.crNote=GetPrivateProfileInt(szAppName,szKeyName,RGB(0,0,0),szFile);
	szKeyName=TEXT("crTableID");
	g_TableConfig.TableResourceInfo.crTableID=GetPrivateProfileInt(szAppName,szKeyName,0xC8C8C8,szFile);

	g_TableConfig.TableResourceInfo.ptLock.x=3000;
	g_TableConfig.TableResourceInfo.ptLock.y=3000;	

	g_TableConfig.TableResourceInfo.rcNote.left=3000;
	g_TableConfig.TableResourceInfo.rcNote.top=3000;
	g_TableConfig.TableResourceInfo.rcNote.right=3000;
	g_TableConfig.TableResourceInfo.rcNote.bottom=3000;

	g_TableConfig.TableResourceInfo.rcTableID.left=3000;
	g_TableConfig.TableResourceInfo.rcTableID.top=3000;
	g_TableConfig.TableResourceInfo.rcTableID.right=3000;
	g_TableConfig.TableResourceInfo.rcTableID.bottom=3000;

	for(int i=0; i<MAX_CHAIR; i++)
	{
		g_TableConfig.TableResourceInfo.rcName[i].left=3000;
		g_TableConfig.TableResourceInfo.rcName[i].top=3000;
		g_TableConfig.TableResourceInfo.rcName[i].right=3000;
		g_TableConfig.TableResourceInfo.rcName[i].bottom=3000;
		g_TableConfig.TableResourceInfo.ptReady[i].x=3000;
		g_TableConfig.TableResourceInfo.ptReady[i].y=3000;
		g_TableConfig.TableResourceInfo.nDrawStyle[i]=3000;

		szKeyName.Format("rcChair[%d]",i);
		ZeroMemory(szResult,sizeof(szResult));
		GetPrivateProfileString(szAppName,szKeyName,TEXT("0,0,0,0"),szResult,sizeof(szResult),szFile);
		ParseRect(szResult,g_TableConfig.TableResourceInfo.rcChair[i]);

	}

	return TRUE;
}

BOOL CDeskMagicDlg::SaveFileIni(LPCTSTR szFile)
{
	if(g_TableConfig.wFileSize==0) return FALSE;

	CString szAppName=TEXT("Main");
	CString szKeyName=TEXT("FileSize");
	CString strResult;

	szKeyName=TEXT("crName");
	strResult.Format("0x%X",g_TableConfig.TableResourceInfo.crName);
	WritePrivateProfileString(szAppName,szKeyName,strResult,szFile);

	szKeyName=TEXT("crNote");
	strResult.Format("0x%X",g_TableConfig.TableResourceInfo.crNote);
	WritePrivateProfileString(szAppName,szKeyName,strResult,szFile);

	szKeyName=TEXT("crTableID");
	strResult.Format("0x%X",g_TableConfig.TableResourceInfo.crTableID);
	WritePrivateProfileString(szAppName,szKeyName,strResult,szFile);

	for(int i=0; i<MAX_CHAIR; i++)
	{
		szKeyName.Format("rcChair[%d]",i);
		strResult.Format("%d,%d,%d,%d",g_TableConfig.TableResourceInfo.rcChair[i].left,
			g_TableConfig.TableResourceInfo.rcChair[i].top,
			g_TableConfig.TableResourceInfo.rcChair[i].right,
			g_TableConfig.TableResourceInfo.rcChair[i].bottom);
		WritePrivateProfileString(szAppName,szKeyName,strResult,szFile);
	}

	return 0;
}

BOOL CDeskMagicDlg::ParseRect(TCHAR* szRect, RECT& rcRect)
{
	CString strRect=szRect;
	int iIndex=strRect.Find(',');
	int iTemp=0;
	CString strLeft=strRect.Left(iIndex);

	iTemp=iIndex+1;
	iIndex=strRect.Find(',',iTemp);
	CString strTop=strRect.Mid(iTemp,iIndex-iTemp);

	iTemp=iIndex+1;
	iIndex=strRect.Find(',',iTemp);
	CString strRight=strRect.Mid(iTemp,iIndex-iTemp);

	CString strBottom=strRect.Right(strRect.GetLength()-iIndex-1);

	rcRect.left=atoi(strLeft);
	rcRect.top=atoi(strTop);
	rcRect.right=atoi(strRight);
	rcRect.bottom=atoi(strBottom);

	return TRUE;
}

BOOL CDeskMagicDlg::ParsePoint(TCHAR* szPoint, POINT& ptPoint)
{
	CString strPoint=szPoint;
	int iIndex=strPoint.Find(',');
	CString strX=strPoint.Left(iIndex);
	CString strY=strPoint.Right(strPoint.GetLength()-iIndex-1);

	ptPoint.x=atoi(strX);
	ptPoint.y=atoi(strY);

	return TRUE;
}

void CDeskMagicDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UINT iFileCount = ::DragQueryFile(hDropInfo,0xFFFFFFFF,NULL,0);
	if(iFileCount>1)  MessageBox("一次只能处理一个文件","错误");

	DWORD nBuffer=DragQueryFile(hDropInfo, 0, NULL, 0);

	TCHAR *pszSFile=new TCHAR[nBuffer+1];
	TCHAR *pszDFile=new TCHAR[nBuffer+1];
	ZeroMemory(pszSFile,sizeof(TCHAR)*(nBuffer+1));
	::DragQueryFile(hDropInfo,0,pszSFile,sizeof(TCHAR)*(nBuffer+1));

	CopyMemory(pszDFile,pszSFile,sizeof(TCHAR)*(nBuffer+1));

	BOOL bOk=FALSE;

	if((pszDFile[nBuffer-1]=='i') || (pszDFile[nBuffer-1]=='I'))
	{
		pszDFile[nBuffer-3]='d';
		pszDFile[nBuffer-2]='a';
		pszDFile[nBuffer-1]='t';

		LoadFileIni(pszSFile);
		SaveFileDat(pszDFile);

		bOk=TRUE;
	}

	if((pszDFile[nBuffer-1]=='t') || (pszDFile[nBuffer-1]=='T'))
	{
		pszDFile[nBuffer-3]='i';
		pszDFile[nBuffer-2]='n';
		pszDFile[nBuffer-1]='i';

		LoadFileDat(pszSFile);
		SaveFileIni(pszDFile);

		bOk=TRUE;
	}

	delete  []pszDFile;
	delete  []pszSFile;

	if(bOk) MessageBox("处理完成");
	else	MessageBox("格式错误");

	CDialog::OnDropFiles(hDropInfo);
}
