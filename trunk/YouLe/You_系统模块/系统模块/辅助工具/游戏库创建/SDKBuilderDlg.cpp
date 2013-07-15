#include "Stdafx.h"
#include "Direct.h"
#include "SDKBuilder.h"
#include "SDKBuilderDlg.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSDKBuilderDlg, CDialog)
	ON_BN_CLICKED(IDC_BULID, OnBnClickedBulid)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CSDKBuilderDlg::CSDKBuilderDlg() : CDialog(IDD_SDKBUILDER_DIALOG)
{
}

//�ؼ���
void CSDKBuilderDlg::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SDK_LIST, m_SDKFileList);
	DDX_Control(pDX, IDC_LIB_LIST, m_LIBFileList);
}

//��ʼ������
BOOL CSDKBuilderDlg::OnInitDialog()
{
	__super::OnInitDialog();

	//����ͼ��
	HICON hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	//���ز���
	TCHAR szBuffer[MAX_PATH]=TEXT("");
	TCHAR szWordDir[MAX_PATH]=TEXT("");
	TCHAR szIniFileName[MAX_PATH]=TEXT("");
	GetCurrentDirectory(sizeof(szWordDir),szWordDir);
	_snprintf(szIniFileName,sizeof(szIniFileName),TEXT("%s\\Builder.INI"),szWordDir);
	GetPrivateProfileString(TEXT("FILE_PATH"),TEXT("SourePath"),TEXT(""),szBuffer,sizeof(szBuffer),szIniFileName);
	m_strSourcePath=szBuffer;
	GetPrivateProfileString(TEXT("FILE_PATH"),TEXT("TargetPath"),TEXT(""),szBuffer,sizeof(szBuffer),szIniFileName);
	m_strTargetPath=szBuffer;

	//�����ļ�
	LoadSDKFileList();
	LoadLIBFileList();
	LoadConversionList();

	//��ʼ���ؼ�
	SetDlgItemText(IDC_SOURCE_PATH,m_strSourcePath);
	SetDlgItemText(IDC_TARGER_PATH,m_strTargetPath);
	m_SDKFileList.SetBackgroundColor(FALSE,RGB(200,200,200));
	m_LIBFileList.SetBackgroundColor(FALSE,RGB(200,200,200));

	return TRUE;
}

//����ͷ�ļ�
void CSDKBuilderDlg::LoadSDKFileList()
{
	//�������
	m_SDKFileList.Clear();

	//���ļ�
	CFile SDKFile;
	if (SDKFile.Open(TEXT("SDKList.TXT"),CFile::modeRead,NULL)==FALSE) return;

	//��ȡ�ļ�
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

//�������ӿ�
void CSDKBuilderDlg::LoadLIBFileList()
{
	//�������
	m_LIBFileList.Clear();

	//���ļ�
	CFile LIBFile;
	if (LIBFile.Open(TEXT("LIBList.TXT"),CFile::modeRead,NULL)==FALSE) return;

	//��ȡ�ļ�
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

//����ת���ַ�
void CSDKBuilderDlg::LoadConversionList()
{
	m_strConversion.Add(TEXT("..\\��ϵ����\\"));
	m_strConversion.Add(TEXT("..\\��Ϸ�ȼ�\\"));
	m_strConversion.Add(TEXT("..\\ͷ�����\\"));
	m_strConversion.Add(TEXT("..\\�ŵ�ģ��\\"));
	m_strConversion.Add(TEXT("..\\�ͻ��˹���\\"));
	m_strConversion.Add(TEXT("..\\..\\ģ���\\"));
	m_strConversion.Add(TEXT("..\\..\\�����ļ�\\"));
	m_strConversion.Add(TEXT("..\\..\\��Ϣ����\\"));
	m_strConversion.Add(TEXT("..\\..\\����ӿ�\\"));
	m_strConversion.Add(TEXT("..\\..\\�������\\�������\\"));
	m_strConversion.Add(TEXT("..\\..\\�������\\����ؼ�\\"));
	m_strConversion.Add(TEXT("..\\..\\�������\\��������\\"));
	m_strConversion.Add(TEXT("..\\..\\���������\\�ں����\\"));
	m_strConversion.Add(TEXT("..\\..\\���������\\�б����\\"));
	m_strConversion.Add(TEXT("..\\..\\���������\\��Ϸ����\\"));

	return;
}

//����Ŀ¼
void CSDKBuilderDlg::CreateDirectory(LPCTSTR pszDirectory)
{
	//��������
	int nExcursion=0;
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	lstrcpyn(szDirectory,pszDirectory,CountArray(szDirectory));

	//����Ŀ¼
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

//ת���ļ�
bool CSDKBuilderDlg::ConversionSDKFile(LPCTSTR pszSDKFile)
{
	//��������
	CString strBuffer;
	CFile SourceFile,TargetFile;

	//��ԭ�ļ�
	if (SourceFile.Open(pszSDKFile,CFile::modeRead,NULL)==FALSE)
	{
		strBuffer.Format(TEXT("��%s���ļ���ȡʧ�ܣ�"),pszSDKFile);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//��Ŀ���ļ�
	TCHAR szTargerName[MAX_PATH]=TEXT("");
	_snprintf(szTargerName,sizeof(szTargerName),TEXT("%s\\Include\\%s"),m_strTargetPath,SourceFile.GetFileName());
	if (TargetFile.Open(szTargerName,CFile::modeCreate|CFile::modeWrite,NULL)==FALSE)
	{
		strBuffer.Format(TEXT("��%s���ļ�д��ʧ�ܣ�"),szTargerName);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//��ȡ�ļ�
	DWORD dwFileLength=(DWORD)SourceFile.GetLength();
	SourceFile.Read(strBuffer.GetBufferSetLength(dwFileLength),dwFileLength);
	strBuffer.ReleaseBuffer();

	//ת���ļ�
	for (INT_PTR i=0;i<m_strConversion.GetCount();i++) strBuffer.Replace(m_strConversion[i],TEXT(""));

	//д���ļ�
	TargetFile.Write(strBuffer.GetBuffer(),strBuffer.GetLength());
	strBuffer.ReleaseBuffer();

	//�ر��ļ�
	TargetFile.Close();
	SourceFile.Close();

	return true;
}

//�����ļ�
bool CSDKBuilderDlg::CopyBinaryFile(LPCTSTR pszSourceFile, LPCTSTR pszTargetPath)
{
	//��������
	CFile SourceFile,TargetFile;

	//��ԭ�ļ�
	if (SourceFile.Open(pszSourceFile,CFile::modeRead,NULL)==FALSE)
	{
		CString strBuffer;
		strBuffer.Format(TEXT("��%s���ļ���ȡʧ�ܣ�"),pszSourceFile);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//��Ŀ���ļ�
	TCHAR szTargerName[MAX_PATH]=TEXT("");
	_snprintf(szTargerName,sizeof(szTargerName),TEXT("%s\\%s"),pszTargetPath,SourceFile.GetFileName());
	if (TargetFile.Open(szTargerName,CFile::modeCreate|CFile::modeWrite,NULL)==FALSE)
	{
		CString strBuffer;
		strBuffer.Format(TEXT("��%s���ļ�д��ʧ�ܣ�"),szTargerName);
		AfxMessageBox(strBuffer,MB_ICONINFORMATION);
		return false;
	}

	//�����ļ�
	UINT uReadCount=0;
	BYTE szBuffer[10240];
	do
	{
		uReadCount=SourceFile.Read(szBuffer,sizeof(szBuffer));
		if (uReadCount==0) break;
		TargetFile.Write(szBuffer,uReadCount);
	} while (true);

	//�ر��ļ�
	TargetFile.Close();
	SourceFile.Close();

	return true;
}

//��������
void CSDKBuilderDlg::OnBnClickedBulid()
{
	//��������
	TCHAR szFileName[MAX_PATH]=TEXT("");
	CString strPath,strTemp,strSourceFile;

	//����Ŀ¼
	strPath.Format(TEXT("%s\\Lib"),m_strTargetPath);
	CreateDirectory(strPath);
	strPath.Format(TEXT("%s\\Include"),m_strTargetPath);
	CreateDirectory(strPath);

	//��ȡͷ�ļ�
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

	//��ȡ���ļ�
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

	//ת�����
	AfxMessageBox(TEXT("�ļ�ת����ɣ�"),MB_ICONINFORMATION);

	return;
}

//////////////////////////////////////////////////////////////////////////
