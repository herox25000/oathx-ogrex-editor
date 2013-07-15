#ifndef __DOWNLOADMGR_H_H
#define __DOWNLOADMGR_H_H

#pragma once
#include <afxinet.h>
#include <afxtempl.h>


//////////////////////////////////////////////////////////////////////////

// Download status
#define DMS_SENDREQUEST					0x00000001L			//��������
#define DMS_READYDOWNLOAD				0x00000002L         //׼������
#define DMS_BEGINDOWNLOAD				0x00000003L			//��ʼ����
#define DMS_DOWNLOADDATA				0x00000004L			//��������
#define DMS_ENDDOWNLOADDATA				0x00000005L			//��������
#define DMS_FINISHDOWNLOAD				0x00000006L			//�������
#define DMS_CANCELDOWNLOAD				0x00000007L			//ȡ������
#define DMS_BEGINSETUP					0x00000008L			//��ʼ��װ
#define DMS_ENDSETUP					0x00000009L         //������װ
#define DMS_ERROR						0x00000020L			//������Ϣ


///////////////////////////////////////////////////////////////////////////////
// Download task structure
typedef struct tagDownloadTask {
	DWORD	dwTaskId;
	DWORD   dwFileSize;
	BOOL	bFinishd;
	TCHAR	szRemoteFile[32];
	TCHAR	szLocalFile[32];
} DOWNLOADTASK;

///////////////////////////////////////////////////////////////////////////////
// Status callback interface
interface IDownloadSink
{
	virtual void OnStatusCallback(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCTSTR pszStatusText) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// CDownloadMgr class
class CDownloadMgr
{
	//�������
protected:
	UINT					m_nTaskCount;			//�������
	ULONG					m_ulTotalProgress;		//�������
	UINT					m_nStatus;				//��ǰ״̬
	CArray<DOWNLOADTASK*>   m_DownloadList;			//�����б�
	
	//�̱߳���
protected:
	HANDLE					m_hThread;				//�߳̾��
	HANDLE					m_hEvent;				//�¼����
	BOOL					m_bCancel;				//ȡ������

	//���ñ���
protected:
	IDownloadSink*			m_pDownloadSink;		//�ص��ӿ�
	CString					m_strDownloadURL;		//���ص�ַ
	CString					m_strTempPath;			//���·��
	CString					m_strSetupPath;			//��װ·��
	CInternetSession*		m_pInteSession;

public:
	static CRITICAL_SECTION	m_Critical;				//�ٽ����

public:
	class CThreadLockHandle
	{
	public:
		CThreadLockHandle()  
		{ 
			EnterCriticalSection(&CDownloadMgr::m_Critical);
		}

		~CThreadLockHandle() 
		{ 
			LeaveCriticalSection(&CDownloadMgr::m_Critical);
		}
	};
	
public:
	//���캯��
	CDownloadMgr();
	//��������
	~CDownloadMgr();

	//��ʼ����
	BOOL Initialize(IDownloadSink* pDownloadSink, LPCTSTR pszDownloadURL, LPCTSTR pszTempPath, LPCTSTR pszSetupPath);
	//�õ�״̬
	UINT GetStatus() const { return m_nStatus; }

	//��������
public:
	//�������
	BOOL AddTask(LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile=NULL);
	//��������
	void Start();
	//�Ƴ�����
	void RemoveAllTask();
	//��������
	void CancelTask() { m_bCancel=TRUE; }

protected:
	//�̺߳���
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
	//�ص�����
	virtual DWORD OnDownloadProc();
	//��װ�ļ�
	virtual DWORD OnSetupFilesProc();
};

#endif