#ifndef SERVICE_THREAD_HEAD_FILE
#define SERVICE_THREAD_HEAD_FILE

#pragma once

#include "ComService.h"

//////////////////////////////////////////////////////////////////////////
//�ӿڶ���

//ͬ������ӿ�
interface IThreadLock
{
	//��������
	virtual void Lock()=NULL;
	//�������� 
	virtual void UnLock()=NULL;
};

//�߳̽ӿ�
interface IServiceThread
{
	//״̬�ж�
	virtual bool IsRuning()=NULL;
	//�����߳�
	virtual bool StartThead()=NULL;
	//ֹͣ�߳�
	virtual bool StopThread(DWORD dwWaitSeconds)=NULL;
	//��ֹ�߳�
	virtual bool TerminateThread(DWORD dwExitCode)=NULL;
};

//////////////////////////////////////////////////////////////////////////

//�ٽ���ͬ����
class COM_SERVICE_CLASS CThreadLock : public IThreadLock
{
	//��������
private:
	CRITICAL_SECTION					m_csLock;					//�ٽ����

	//��������
public:
	//���캯��
	inline CThreadLock() { ::InitializeCriticalSection(&m_csLock); }
	//��������
	inline ~CThreadLock() { ::DeleteCriticalSection(&m_csLock); }

	//���ܺ���
public:
	//��������
	virtual inline void Lock() { ::EnterCriticalSection(&m_csLock); }
	//�������� 
	virtual inline void UnLock() { ::LeaveCriticalSection(&m_csLock); }
};

//////////////////////////////////////////////////////////////////////////

//��ȫͬ���������
class COM_SERVICE_CLASS CThreadLockHandle
{
	//��������
private:
	int								m_nLockCount;				//��������
	IThreadLock						* m_pIThreadLock;			//��������

	//��������
public:
	//���캯��
	CThreadLockHandle(IThreadLock * pIThreadLock, bool bAutoLock=true);
	//��������
	virtual ~CThreadLockHandle();

	//���ܺ���
public:
	//��������
	void Lock();
	//�������� 
	void UnLock();
	//��ȡ��������
	int inline GetLockCount() { return m_nLockCount; }
};

//////////////////////////////////////////////////////////////////////////

//�̶߳�����
class COM_SERVICE_CLASS CServiceThread : public IServiceThread
{
	//��������
private:
	volatile bool						m_bRun;							//���б�־
	UINT								m_uThreadID;					//�̱߳�ʶ
	HANDLE								m_hThreadHandle;				//�߳̾��

	//��������
protected:
	//���캯��
	CServiceThread(void);
	//��������
	virtual ~CServiceThread(void);

	//�ӿں���
public:
	//��ȡ״̬
	virtual bool IsRuning();
	//�����߳�
	virtual bool StartThead();
	//ֹͣ�߳�
	virtual bool StopThread(DWORD dwWaitSeconds=INFINITE);
	//��ֹ�߳�
	virtual bool TerminateThread(DWORD dwExitCode);

	//���ܺ���
public:
	//��ȡ��ʶ
	UINT GetThreadID() { return m_uThreadID; }
	//��ȡ���
	HANDLE GetThreadHandle() { return m_hThreadHandle; }
	//Ͷ����Ϣ
	bool PostThreadMessage(UINT uMessage, WPARAM wParam, LPARAM lParam);

	//�¼�����
private:
	//��ʼ�¼�
	virtual bool OnThreadStratEvent() { return true; }
	//ֹͣ�¼�
	virtual bool OnThreadStopEvent() { return true; }

	//�ڲ�����
private:
	//���к���
	virtual bool RepetitionRun()=NULL;
	//�̺߳���
	static unsigned __stdcall ThreadFunction(LPVOID pThreadData);
};

//////////////////////////////////////////////////////////////////////////

#endif