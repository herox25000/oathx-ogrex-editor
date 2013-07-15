#include "Stdafx.h"
#include "Direct.h"
#include "SDKBuilder.h"
#include "SDKBuilderDlg.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSDKBuilderDlg, CDialog)
	ON_BN_CLICKED(IDC_BULID, OnBnClickedBulid)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CSDKBuilderDlg::CSDKBuilderDlg() : CDialog(IDD_SDKBUILDER_DIALOG)
{
}

//控件绑定
void CSDKBuilderDlg::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SDK_LIST, m_SDKFileList);
	DDX_Control(pDX, IDC_LIB_LIST, m_LIBFileList);
}

//初始化函数
BOOL CSDKBuilderDlg::OnInitDialog()
{
	__super::OnInitDialog();

	//设置图标
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//加载参数
	TCHAR szBuffer[MAX_PATH]=TEXT("");
	TCHAR szWordDir[MAX_PATH]=TEXT("");
	TCHAR szIniFileName[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szWordDir),szWordDir);
	_snprintf(szIniFileName,sizeof(szIniFileName),TEXT("%s\\Builder.INI"),szWordDir);
	GetPrivateProfileString(TEXT("FILE_PATH"),TEXT("SourePath"),TEXT(""),szBuffer,sizeof(szBuffer),szIniFileName);
	m_strSourcePath=szBuffer;
	GetPrivateProfileString(TEXT("FILE_PATH"),TEXT("TargetPath"),TEXT(""),szBuffer,sizeof(szBuffer),szIniFileName);
	m_strTargetPath=szBuffer;

	//加载文件
	LoadSDKFileList();
	LoadLIBFileList();
	LoadConversionList();

	//初始化控件
	SetDlgItemText(IDC_SOURCE_PATH,m_strSourcePath);
	SetDlgItemText(IDC_TARGER_PATH,m_strTargetPath);
	m_SDKFileList.SetBackgroundColor(FALSE,RGB(200,200,200));
	m_LIBFileList.SetBackgroundColor(FALSE,RGB(200,200,200));

	return TRUE;
}

//加载头文件
void CSDKBuilderDlg::LoadSDKFileList()
{
	//清理界面
	m_SDKFileList.Clear();

	//打开文件
	CFile SDKFile;
	if (SDKFile.Open(TEXT("SDKList.TXT"),CFile::modeRead,NULL)==FALSE) return;

	//读取文件
	DWORD dwFileSize=(DWORD)SDKFile.GetLength();
	if (dwFileSize>0)
	{
		LPTSTR pszBuffer=new TCHAR [dwFileSize+1];
		SDKFile.Read(pszBuffer,dwFileSize);
		pszBuffer[dwFileSize]=0;
		m_SDKFileList.InsertString(pszBuffer,RGB(0,0,0));
		SafeDelete(pszBuffer);
	}

	return;
}

//加载链接库
void CSDKBuilderDlg::LoadLIBFileList()
{
	//清理界面
	m_LIBFileList.Clear();

	//打开文件
	CFile LIBFile;
	if (LIBFile.Open(TEXT("LIBList.TXT"),CFile::modeRead,NULL)==FALSE) return;

	//读取文件
	DWORD dwFileSize=(DWORD)LIBFile.GetLength();
	if (dwFileSize>0)
	{
		LPTSTR pszBuffer=new TCHAR [dwFileSize+1];
		LIBFile.Read(pszBuffer,dwFileSize);
		pszBuffer[dwFileSize]=0;
		m_LIBFileList.InsertString(pszBuffer,RGB(0,0,0));
		SafeDelete(pszBuffer);
	}

	return;
}

//加载转化字符
void CSDKBuilderDlg::LoadConversionList()
{
	m_strConversion.Add(TEXT("..\\关系管理\\"));
	m_strConversion.Add(TEXT("..\\游戏等级\\"));
	m_strConversion.Add(TEXT("..\\头像组件\\"));
	m_strConversion.Add(TEXT("..\\信道模块\\"));
	m_strConversion.Add(TEXT("..\\客户端共享\\"));
	m_strConversion.Add(TEXT("..\\..\\模板库\\"));
	m_strConversion.Add(TEXT("..\\..\\公共文件\\"));
	m_strConversion.Add(TEXT("..\\..\\消息定义\\"));
	m_strConversion.Add(TEXT("..\\..\\组件接口\\"));
	m_strConversion.Add(TEXT("..\\..\\共享组件\\网络组件\\"));
	m_strConversion.Add(TEXT("..\\..\\共享组件\\界面控件\\"));
	m_strConversion.Add(TEXT("..\\..\\共享组件\\公共服务\\"));
	m_strConversion.Add(TEXT("..\\..\\服务器组件\\内核组件\\"));
	m_strConversion.Add(TEXT("..\\..\\服务器组件\\列表服务\\"));
	m_strConversion.Add(TEXT("..\\..\\服务器组件\\游戏服务\\"));

	return;
}

//创建目录
void CSDKBuilderDlg::CreateDirectory(LPCTSTR pszDirectory)
{
	//变量定义
	int nExcursion=0;
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	lstrcpyn(szDirectory,pszDirectory,CountArray(szDirectory));

	//创建目录
	do
	{
		if (szDirectory[nExcursion]==0) 
		{
			::CreateDirectory(szDirectory,NULL);
			break;
		}
		if (szDirectory[nExcursion]==TEXT('\\'))
		{
			szDirectory[nExcursion]=0;
			::CreateDirectory(szDirectory,NULL);
			szDirectory[nExcursion]=TEXT('\\');
		}
		nExcursion++;

	} while (true);

	return;
}

//转换文件
bool CSDKBuilderDlg::ConversionSDKFile(LPCTSTR pszSDKFile)
{
	//变量定义
	CString strBuffer;
	CFile SourceFile,TargetFile;

	//打开原文件
	if (SourceFile.Open(pszSDKFile,CFile::modeRead,NULL)==FALSE)
	{
		strBuffer.Format(TEXT("“%s”文件读取失败！"),pszSDKFile);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//打开目标文件
	TCHAR szTargerName[MAX_PATH]=TEXT("");
	_snprintf(szTargerName,sizeof(szTargerName),TEXT("%s\\Include\\%s"),m_strTargetPath,SourceFile.GetFileName());
	if (TargetFile.Open(szTargerName,CFile::modeCreate|CFile::modeWrite,NULL)==FALSE)
	{
		strBuffer.Format(TEXT("“%s”文件写入失败！"),szTargerName);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//读取文件
	DWORD dwFileLength=(DWORD)SourceFile.GetLength();
	SourceFile.Read(strBuffer.GetBufferSetLength(dwFileLength),dwFileLength);
	strBuffer.ReleaseBuffer();

	//转换文件
	for (INT_PTR i=0;i<m_strConversion.GetCount();i++) strBuffer.Replace(m_strConversion[i],TEXT(""));

	//写入文件
	TargetFile.Write(strBuffer.GetBuffer(),strBuffer.GetLength());
	strBuffer.ReleaseBuffer();

	//关闭文件
	TargetFile.Close();
	SourceFile.Close();

	return true;
}

//拷贝文件
bool CSDKBuilderDlg::CopyBinaryFile(LPCTSTR pszSourceFile, LPCTSTR pszTargetPath)
{
	//变量定义
	CFile SourceFile,TargetFile;

	//打开原文件
	if (SourceFile.Open(pszSourceFile,CFile::modeRead,NULL)==FALSE)
	{
		CString strBuffer;
		strBuffer.Format(TEXT("“%s”文件读取失败！"),pszSourceFile);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//打开目标文件
	TCHAR szTargerName[MAX_PATH]=TEXT("");
	_snprintf(szTargerName,sizeof(szTargerName),TEXT("%s\\%s"),pszTargetPath,SourceFile.GetFileName());
	if (TargetFile.Open(szTargerName,CFile::modeCreate|CFile::modeWrite,NULL)==FALSE)
	{
		CString strBuffer;
		strBuffer.Format(TEXT("“%s”文件写入失败！"),szTargerName);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//拷贝文件
	UINT uReadCount=0;
	BYTE szBuffer[10240];
	do
	{
		uReadCount=SourceFile.Read(szBuffer,sizeof(szBuffer));
		if (uReadCount==0) break;
		TargetFile.Write(szBuffer,uReadCount);
	} while (true);

	//关闭文件
	TargetFile.Close();
	SourceFile.Close();

	return true;
}

//生成命令
void CSDKBuilderDlg::OnBnClickedBulid()
{
	//变量定义
	TCHAR szFileName[MAX_PATH]=TEXT("");
	CString strPath,strTemp,strSourceFile;

	//创建目录
	strPath.Format(TEXT("%s\\Lib"),m_strTargetPath);
	CreateDirectory(strPath);
	strPath.Format(TEXT("%s\\Include"),m_strTargetPath);
	CreateDirectory(strPath);

	//获取头文件
	int nLineCount=m_SDKFileList.GetLineCount();
	for (int i=0;i<nLineCount;i++)
	{
		if (m_SDKFileList.GetLine(i,szFileName,CountArray(szFileName))==0) continue;
		if ((szFileName[0]==0)||(szFileName[0]==TEXT('\r'))||(szFileName[0]==TEXT('\n'))) continue;
		for (int j=0;j<MAX_PATH;j++) 
		{
			if (szFileName[j]==0) break;
			if ((szFileName[j]==TEXT('\r'))||(szFileName[j]==TEXT('\n')))
			{
				szFileName[j]=0;
				break;
			}
		}
		strSourceFile.Format(TEXT("%s\\%s"),m_strSourcePath,szFileName);
		if (ConversionSDKFile(strSourceFile)==false) return;
	}

	//获取库文件
	CString strLibTargetPath;
	nLineCount=m_LIBFileList.GetLineCount();
	strLibTargetPath.Format(TEXT("%s\\Lib\\"),m_strTargetPath);
	for (int i=0;i<nLineCount;i++)
	{
		if (m_LIBFileList.GetLine(i,szFileName,CountArray(szFileName))==0) continue;
		if ((szFileName[0]==0)||(szFileName[0]==TEXT('\r'))||(szFileName[0]==TEXT('\n'))) continue;
		for (int j=0;j<MAX_PATH;j++)
		{
			if (szFileName[j]==0) break;
			if ((szFileName[j]==TEXT('\r'))||(szFileName[j]==TEXT('\n')))
			{
				szFileName[j]=0;
				break;
			}
		}
		strSourceFile.Format(TEXT("%s\\%s"),m_strSourcePath,szFileName);
		if (CopyBinaryFile(strSourceFile,strLibTargetPath)==false) return;
	}

	//转化完成
	AfxMessageBox(TEXT("文件转化完成！"),MB_ICONINFORMATION);

	return;
}

//////////////////////////////////////////////////////////////////////////
