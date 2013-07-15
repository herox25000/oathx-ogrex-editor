#include "stdafx.h"
#include "DownloadMgr.h"
#include <Wininet.h>
#include <atlmem.h>
#include <atlstr.h>

#define MAX_BUFFER		8192

//��ȡ���� HTML
const TCHAR szErrorHtml1[]=TEXT("<html>");
const TCHAR szErrorHtml2[]=TEXT("<!DOCTYPE HTML PUBLIC");

CRITICAL_SECTION CDownloadMgr::m_Critical;

CDownloadMgr::CDownloadMgr()
{
	m_pDownloadSink=NULL;
	m_nTaskCount=0L;
	m_hEvent=NULL;
	m_hThread=NULL;
	m_bCancel=FALSE;
	m_pInteSession=NULL;
	m_ulTotalProgress=0L;

	// Initialize the critical section object
	InitializeCriticalSection(&m_Critical);
}

CDownloadMgr::~CDownloadMgr()
{
	RemoveAllTask();

	if( m_hThread )
	{
		CloseHandle(m_hThread);
		m_hThread=NULL;
	}

	if( m_hEvent )
	{
		CloseHandle(m_hEvent);
		m_hEvent=NULL;
	}

	if (m_pInteSession)
	{
		delete m_pInteSession;
		m_pInteSession = NULL;
	}

	DeleteCriticalSection(&m_Critical);
}

BOOL CDownloadMgr::Initialize(IDownloadSink* pDownloadSink, LPCTSTR pszDownloadURL, LPCTSTR pszTempPath, LPCTSTR pszSetupPath)
{
	ASSERT(pDownloadSink != NULL);
	if( pDownloadSink == NULL )
		return FALSE;

	//���ñ���
	m_pDownloadSink = pDownloadSink;
	m_strDownloadURL = pszDownloadURL;
	m_strTempPath =  pszTempPath;
	m_strSetupPath = pszSetupPath;

	//����·��
	if (m_strDownloadURL.Right(1) != _T("/"))
		m_strDownloadURL += _T("/");

	//����Ŀ¼
	if( !PathIsDirectory(m_strTempPath) )
	{
		VERIFY(CreateDirectory(m_strTempPath, NULL));
	}

	m_pInteSession = new CInternetSession();
	ASSERT(m_pInteSession!=NULL);

	// Create event object
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if( m_hEvent==NULL )
		return FALSE;

	return TRUE;
}

BOOL CDownloadMgr::AddTask(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile)
{
	ASSERT(pszRemoteFile!=NULL);
	if( pszRemoteFile==NULL )
		return FALSE;
	
	DOWNLOADTASK* pDownloadTask = new DOWNLOADTASK;
	ZeroMemory(pDownloadTask, sizeof(DOWNLOADTASK));

	pDownloadTask->dwTaskId = ++m_nTaskCount;
	pDownloadTask->bFinishd = FALSE;
	strcpy(pDownloadTask->szRemoteFile, pszRemoteFile);
	strcpy(pDownloadTask->szLocalFile, (pszLocalFile ? pszLocalFile : pszRemoteFile));

	// Add a task to the task list
	CThreadLockHandle LockHandle;
	m_DownloadList.Add(pDownloadTask);

	return TRUE;
}

void CDownloadMgr::Start()
{
	// Create the work thread
	m_ulTotalProgress = 0L;
	DWORD dwThreadId;
	m_hThread=CreateThread(NULL, 0, ThreadProc, (LPVOID)this, 0, &dwThreadId);
	SetEvent(m_hEvent);
}

void CDownloadMgr::RemoveAllTask()
{
	CThreadLockHandle LockHandle;
	INT_PTR nCount = m_DownloadList.GetCount();
	for (INT_PTR i = 0; i < nCount; i++)
	{
		DOWNLOADTASK* pDownloadTask=m_DownloadList.GetAt(i);
		if (pDownloadTask)
		{
			delete pDownloadTask;
		}
	}
	m_DownloadList.RemoveAll();
}

DWORD WINAPI CDownloadMgr::ThreadProc(LPVOID lpParam)
{
	CDownloadMgr* pDownloadMgr=reinterpret_cast<CDownloadMgr*>(lpParam);

	WaitForSingleObject(pDownloadMgr->m_hEvent, INFINITE);

	//�����ļ�
	DWORD dwExitCode = pDownloadMgr->OnDownloadProc();

	//��װ�ļ�
	if (dwExitCode == 0)
	{
		dwExitCode = pDownloadMgr->OnSetupFilesProc();
	}

	if (dwExitCode == 0)
	{
		pDownloadMgr->RemoveAllTask();
	}
	TRACE("The download thread has exited with error %d\n", dwExitCode);
	
	return dwExitCode;
}

DWORD CDownloadMgr::OnDownloadProc()
{
	ASSERT(m_pInteSession!=NULL);
	ASSERT(m_pDownloadSink!=NULL);

	char buffer[MAX_BUFFER];
	TCHAR szLocalPath[MAX_PATH];
	DOWNLOADTASK* pDownloadTask;
	CHttpFile* pHttpFile;
	CFileException	fe;
	CFile LocalFile;
	DWORD dwFileLenght;
	UINT nReadBytes, nLeft;

	try
	{
		INT_PTR nCount = m_DownloadList.GetCount();
		for (INT_PTR i = 0; i < nCount; i++)
		{
			//��ʼ����
			pHttpFile = NULL;
			pDownloadTask = NULL;
			dwFileLenght = 0L;
			nReadBytes = 0, nLeft = 0;

			pDownloadTask = m_DownloadList.GetAt(i);
			ASSERT(pDownloadTask);


			m_nStatus = DMS_SENDREQUEST;
			m_pDownloadSink->OnStatusCallback(0, 0, DMS_SENDREQUEST, NULL);
			pHttpFile=(CHttpFile*)m_pInteSession->OpenURL(m_strDownloadURL+pDownloadTask->szRemoteFile, 1, 
				INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_DONT_CACHE);
			ASSERT(pHttpFile!=NULL);

			// Query length of file
			pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH|HTTP_QUERY_FLAG_NUMBER, dwFileLenght);

			nReadBytes = pHttpFile->Read(buffer, MAX_BUFFER);
			if (nReadBytes<sizeof(szErrorHtml1))
				throw (0);
			if (nReadBytes<sizeof(szErrorHtml2))
				throw (0);

			if (memcmp(szErrorHtml1,buffer,lstrlen(szErrorHtml1))==0) throw 0;
			if (memcmp(szErrorHtml2,buffer,lstrlen(szErrorHtml2))==0) throw 0;

			// Sent status callback
			m_nStatus = DMS_BEGINDOWNLOAD;
			m_pDownloadSink->OnStatusCallback(0, dwFileLenght, DMS_BEGINDOWNLOAD, pDownloadTask->szRemoteFile);

			// Create local file
			sprintf(szLocalPath, _T("%s\\%s.dtm"), m_strTempPath, pDownloadTask->szLocalFile);
			if( !LocalFile.Open(szLocalPath, CFile::modeCreate|CFile::modeReadWrite, &fe) )
				throw &(fe);

			//д��ǰ��
			LocalFile.Write(buffer, nReadBytes);
			nLeft = nReadBytes;
			m_ulTotalProgress += nReadBytes;
			m_nStatus = DMS_DOWNLOADDATA;
			m_pDownloadSink->OnStatusCallback(nLeft, m_ulTotalProgress, DMS_DOWNLOADDATA, pDownloadTask->szRemoteFile);

			// Downloading data
			while( nLeft < dwFileLenght && !m_bCancel )
			{
				nReadBytes = pHttpFile->Read(buffer, MAX_BUFFER);
				LocalFile.Write(buffer, nReadBytes);
				nLeft += nReadBytes;
				m_ulTotalProgress += nReadBytes;
				m_nStatus = DMS_DOWNLOADDATA;
				m_pDownloadSink->OnStatusCallback(nLeft, m_ulTotalProgress, DMS_DOWNLOADDATA, pDownloadTask->szRemoteFile);
			}

			//�����Դ
			if( pHttpFile )
			{
				pHttpFile->Close();
				delete pHttpFile;
			}

			if( LocalFile.m_hFile != INVALID_HANDLE_VALUE )
				LocalFile.Close();


			// Cancel all tasks
			if (!m_bCancel)
			{
				pDownloadTask->bFinishd = TRUE;
				m_nStatus = DMS_ENDDOWNLOADDATA;
				m_pDownloadSink->OnStatusCallback(0, 0, DMS_ENDDOWNLOADDATA, pDownloadTask->szRemoteFile);
			}
			else
			{
				m_nStatus = DMS_CANCELDOWNLOAD;
				m_pDownloadSink->OnStatusCallback(0, 0, DMS_CANCELDOWNLOAD, NULL);
				return 2;
			}
		}

		//�������
		m_nStatus = DMS_FINISHDOWNLOAD;
		m_pDownloadSink->OnStatusCallback(0, 0, DMS_FINISHDOWNLOAD, NULL);
		return 0;
	}
	catch(CInternetException* e)
	{
		TCHAR szError[512]={0};
		e->GetErrorMessage(szError, sizeof(szError)/sizeof(TCHAR));

		if( pHttpFile )
		{
			pHttpFile->Close();
			delete pHttpFile;
		}

		if( LocalFile.m_hFile != INVALID_HANDLE_VALUE )
			LocalFile.Close();

		m_nStatus = DMS_ERROR;
		m_pDownloadSink->OnStatusCallback(0, 0, DMS_ERROR, szError);
		return 1;
	}
	catch(CFileException* e)
	{
		TCHAR szError[512]={0};
		e->GetErrorMessage(szError, sizeof(szError)/sizeof(TCHAR));
		if( pHttpFile )
		{
			pHttpFile->Close();
			delete pHttpFile;
		}

		if( LocalFile.m_hFile != INVALID_HANDLE_VALUE )
			LocalFile.Close();

		m_nStatus = DMS_ERROR;
		m_pDownloadSink->OnStatusCallback(0, 0, DMS_ERROR, szError);
		return 1;
	}
	catch(...)
	{
		if( pHttpFile )
		{
			pHttpFile->Close();
			delete pHttpFile;
		}

		if( LocalFile.m_hFile != INVALID_HANDLE_VALUE )
			LocalFile.Close();

		TCHAR szError[512]={0};
		sprintf(szError, _T("���� %s �ļ�ʧ��"), pDownloadTask->szRemoteFile);
		m_nStatus = DMS_ERROR;
		m_pDownloadSink->OnStatusCallback(0, 0, DMS_ERROR, szError);
		return 1;
	}

	return 0;
}

DWORD CDownloadMgr::OnSetupFilesProc()
{
	m_pDownloadSink->OnStatusCallback(0, 0, DMS_BEGINSETUP, _T("��ʼ��װ���£����Ժ�..."));

	TCHAR szSrcFile[MAX_PATH]={0};
	TCHAR szDesFile[MAX_PATH]={0};
	TCHAR szModuleFile[MAX_PATH]={0};

	//������ѵ�����
	GetModuleFileName(AfxGetInstanceHandle(), szModuleFile, MAX_PATH);
	LPCTSTR pszFileName = PathFindFileName(szModuleFile);

	INT_PTR nCount = m_DownloadList.GetCount();
	for (INT_PTR i = 0; i < nCount; i++)
	{
		DOWNLOADTASK* pDownloadTask = m_DownloadList.GetAt(i);
		ASSERT(pDownloadTask!=NULL);
		ASSERT(pDownloadTask->bFinishd==TRUE);

		//�����ļ�
		sprintf(szSrcFile, _T("%s\\%s.dtm"), m_strTempPath, pDownloadTask->szLocalFile);
		if (_strcmpi(pszFileName, pDownloadTask->szLocalFile) == 0)
		{
			//�Ƴ���չ��
			PathRemoveExtension(pDownloadTask->szLocalFile);
			sprintf(szDesFile,_T("%s\\%s.EX_"), m_strSetupPath, pDownloadTask->szLocalFile);
		}
		else sprintf(szDesFile, _T("%s\\%s"), m_strSetupPath, pDownloadTask->szLocalFile);
		MoveFileEx(szSrcFile, szDesFile, MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED);
	}
	m_pDownloadSink->OnStatusCallback(0, 0, DMS_ENDSETUP, NULL);

	return 0;
}