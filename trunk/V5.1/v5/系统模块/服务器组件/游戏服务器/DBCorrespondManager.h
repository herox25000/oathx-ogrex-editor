#ifndef DBCORRESPONDMANAGER_HEAD_FILE
#define DBCORRESPONDMANAGER_HEAD_FILE


#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////
//����ṹ
struct tagDBRequestHead
{
	BYTE  cbCache;
	DWORD dwUserID;
	DWORD dwContextID;
	WORD  wRequestID;
	WORD  wDataSize;
};

typedef CList<tagDBRequestHead *> CDBRequestList;
typedef CWHArray<DWORD> CDBRequestUserArray;

//////////////////////////////////////////////////////////////////////////
class CDBCorrespondManager : public IDBCorrespondManager
{
	//��������
protected:
	bool							m_bService;							//����״̬
	CCriticalSection				m_AsyncCritical;					//��������

	//��������
public:
	IDataBaseEngine *				m_pIKernelDataBaseEngine;			//��������

	//���ݼ�¼
public:
	CDBRequestList                  m_DBRequestList;                    //��������
	CDBRequestUserArray             m_DBRequestUserArray;               //�����û�

public:
	CDBCorrespondManager(void);
	~CDBCorrespondManager(void);

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//�����ӿ�
public:
	//��������
	virtual bool StartService();
	//ֹͣ����
	virtual bool ConcludeService();

	//���ýӿ�
public:
	//����ģ��
	virtual bool __cdecl InitDBCorrespondManager(IDataBaseEngine * pIDataBaseEngine);

	//�����¼�
public:
	//�����¼�
	virtual bool __cdecl PostDataBaseRequest(DWORD dwUserID, WORD wRequestID, DWORD dwContextID, VOID * pData, WORD wDataSize, BYTE  cbCache = FALSE);

	//ͬ���¼�
public:
	//�������
	virtual bool __cdecl OnPostRequestComplete(DWORD dwUserID, bool bSucceed);

	//��ʱ�¼�
public:
	//��ʱ�¼�
	virtual bool __cdecl OnTimerNotify();

	//���ܺ���
public:
	//�Ѿ��ύ����
	bool IsPostDBRequest(DWORD dwUserID);
	//�������
	INT_PTR GetUserArrayIndex(DWORD dwUserID);
	//��������
	bool AmortizeSyncData(DWORD dwUserID, WORD wRequestID, DWORD dwContextID, VOID * pData, WORD wDataSize, BYTE  cbCache = FALSE);
	//ִ�л���
	VOID PerformAmortisation();
	//�������
	VOID ClearAmortizeData();
};

//////////////////////////////////////////////////////////////////////////

#endif