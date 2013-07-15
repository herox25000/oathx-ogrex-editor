#ifndef DATA_STORAGE_HEAD_FILE
#define DATA_STORAGE_HEAD_FILE

#include "ComService.h"

#pragma once

//////////////////////////////////////////////////////////////////////////
//�ṹ�嶨��

//���ݶ���ͷ
struct tagDataHead
{
	WORD							wDataSize;							//���ݴ�С
	WORD							wIdentifier;						//���ͱ�ʶ
	DWORD							dwInsertTime;						//����ʱ��
};

//������Ϣ
struct tagBurthenInfo
{
	DWORD							dwDataSize;							//���ݴ�С
	DWORD							dwBufferSize;						//����������
	DWORD							dwDataPacketCount;					//���ݰ���Ŀ
};

//////////////////////////////////////////////////////////////////////////

//���ݴ洢��
class COM_SERVICE_CLASS CDataStorage
{
	//���ݱ���
protected:
	DWORD							m_dwDataSize;						//���ݴ�С
	DWORD							m_dwBufferSize;						//����������
	DWORD							m_dwInsertPos;						//���ݲ���λ
	DWORD							m_dwTerminalPos;					//���ݽ���λ
	DWORD							m_dwDataQueryPos;					//���ݲ�ѯλ
	DWORD							m_dwDataPacketCount;				//���ݰ���Ŀ
	BYTE							* m_pDataStorageBuffer;				//����ָ��

	//��������
public:
	//���캯��
	CDataStorage(void);
	//��������
	virtual ~CDataStorage(void);

	//���ܺ���
public:
	//������Ϣ
	bool GetBurthenInfo(tagBurthenInfo & BurthenInfo);
	//��������
	bool AddData(WORD wIdentifier, void * const pBuffer, WORD wDataSize);
	//��ȡ����
	bool GetData(tagDataHead & DataHead, void * pBuffer, WORD wBufferSize);
	//ɾ������
	void RemoveData(bool bFreeMemroy);
};

//////////////////////////////////////////////////////////////////////////

#endif