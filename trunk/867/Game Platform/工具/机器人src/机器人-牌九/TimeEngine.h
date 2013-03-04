#pragma once

#include <vector>

//��˵��
class CTimerEngine;
class CGameBase;
//////////////////////////////////////////////////////////////////////////

//��ʱ���߳�
class CTimerThread : public CServiceThread
{
	//��������
protected:
	DWORD								m_dwTimerSpace;					//ʱ����
	CTimerEngine						* m_pTimerEngine;				//��ʱ������

	//��������
public:
	//���캯��
	CTimerThread(void);
	//��������
	virtual ~CTimerThread(void);

	//���ܺ���
public:
	//���ú���
	bool InitThread(CTimerEngine * pTimerEngine, DWORD dwTimerSpace);

	//���غ���
private:
	////���к���
	//virtual bool RepetitionRun();
	//���к���
	virtual bool OnEventThreadRun();
};

//��ʱ������
struct tagTimerItem
{
	WORD								wTimerID;						//��ʱ�� ID
	DWORD								dwElapse;						//��ʱʱ��
	DWORD								dwTimeLeave;					//����ʱ��
	DWORD								dwRepeatTimes;					//�ظ�����
	CGameBase							*pGame;							//��Ϸָ��
};

typedef std::vector<tagTimerItem*> CTimerItemPtr;

class CTimerEngine
{
	friend class CTimerThread;

	//���ö���
protected:
	DWORD								m_dwTimerSpace;					//ʱ����

	//״̬����
protected:
	bool								m_bService;						//���б�־
	DWORD								m_dwTimePass;					//����ʱ��
	DWORD								m_dwTimeLeave;					//����ʱ��
	CTimerItemPtr						m_TimerItemFree;				//��������
	CTimerItemPtr						m_TimerItemActive;				//�����

	//�������
protected:
	CTimerThread						m_TimerThread;					//��ʱ���߳�
	CCriticalSection					m_CriticalSection; //	//�߳���
public:
	CTimerEngine(void);
	~CTimerEngine(void);

	//�ӿں���
public:
	//���ö�ʱ��
	virtual bool SetTimer(CGameBase *pGame, WORD wTimerID, DWORD dwElapse, DWORD dwRepeat);
	//ɾ����ʱ��
	virtual bool KillTimer(CGameBase *pGame, WORD wTimerID);
	//ɾ����ʱ��
	virtual bool KillAllTimer();

	//��ʼ����
	virtual bool BeginService();
	//ֹͣ����
	virtual bool EndService();

	//�ڲ�����
private:
	//��ʱ��֪ͨ
	void OnTimerThreadSink();
};
