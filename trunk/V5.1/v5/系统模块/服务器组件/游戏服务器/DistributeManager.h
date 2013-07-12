#ifndef DISTRIBUTE_MANAGER_HEAD_FILE
#define DISTRIBUTE_MANAGER_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
struct tagDistributeInfo
{
	WORD							wDistribute;						//����ȼ�
	WORD							wLastTableID;						//�ϴ�����
	DWORD							dwClientAddr;						//��ҵ�ַ
	IServerUserItem *				pIServerUserItem;					//�û��ӿ�
	VOID *                          pPertainNode;                       //������� 
};

//������
struct tagDistributeNode
{
	tagDistributeNode *             pPrepDistributeNode;               //ǰһ���
	tagDistributeNode *			    pNextDistributeNode;               //��һ���
	tagDistributeNode *			    pNextSameTableNode;                //ͬ�����
	tagDistributeInfo               DistributeInfo;                    //������Ϣ

	tagDistributeNode()
	{
		pPrepDistributeNode=NULL;
		pNextDistributeNode=NULL;
		pNextSameTableNode=NULL;
	}
	~tagDistributeNode()
	{
		pPrepDistributeNode=NULL;
		pNextDistributeNode=NULL;
		pNextSameTableNode=NULL;
	}

};  

//////////////////////////////////////////////////////////////////////////////////

typedef CWHArray<tagDistributeInfo> CDistributeInfoArray;				//��������

//////////////////////////////////////////////////////////////////////////////////

//����
class  CDistributeNodePool
{
	//�������
public:
	static const int BLOCK_SIZE;
	static tagDistributeNode * m_pHeadOfFreeList;

	//��������
public:
	//���캯��
	CDistributeNodePool();
	//��������
	~CDistributeNodePool();

	//���ܺ���
public:
	//������
	tagDistributeNode * AllocNode();
	//�ͷŽ��
	VOID FreeNode(void * pNode);
};

//////////////////////////////////////////////////////////////////////////////////

//�������
class CDistributeManager
{
	//��Ŀ����
protected:
	WORD							m_wNodeCount;				      //�����Ŀ
	WORD                            m_wRealCount;	                  //������Ŀ
	WORD                            m_wAndroidCount;		          //������Ŀ 

	//�������
protected:
	CDistributeNodePool             m_DistributeNodePool;             //���� 
	tagDistributeNode *				m_pHeadNode;					  //ͷ�����

	//�������
protected:
	BYTE							m_cbDistributeRule;				  //�������

	//��������
public:
	//���캯��
	CDistributeManager();
	//��������
	virtual ~CDistributeManager();

	//��������
public:
	//�����Ŀ
	inline WORD  GetCount() { return m_wNodeCount; }
	//������Ŀ
	inline WORD  GetRealCount() { return m_wRealCount; };
	//������Ŀ
	inline WORD  GetAndroidCount() { return m_wAndroidCount; };
	//���ù���
	inline VOID  SetDistributeRule(BYTE cbDistributeRule) { m_cbDistributeRule=cbDistributeRule; }

	//�ڲ�����
protected:
	//���ҽ��
	tagDistributeNode* SearchNode(const IServerUserItem  * const pIServerUserItem);

	//���ܺ���
public:	
	//������
	BOOL InsertDistributeNode(const tagDistributeInfo & DistributeInfo);
	//�Ƴ����
	VOID RemoveDistributeNode(tagDistributeNode * pDistributeNode);
	//�Ƴ����
	VOID RemoveDistributeNode(const IServerUserItem  *  pIServerUserItem);
	//�Ƴ����
	VOID RemoveAll();
	//ִ�з���
	WORD PerformDistribute(CDistributeInfoArray & DistributeInfoArray,WORD wNeedCount);

	//������
protected:
	//IPַͬ
	inline BOOL  FilterRuleExitsIPAddr(const CDistributeInfoArray & DistributeInfoArray,DWORD dwClientAddr);	
	//��������
	inline BOOL  FilterRuleIsAllAndroid(const CDistributeInfoArray & DistributeInfoArray, IServerUserItem  * const pIServerUserItem);
};

//////////////////////////////////////////////////////////////////////////////////

#endif