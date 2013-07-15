#ifndef USER_COMPANION_LIST_HEAD_FILE
#define USER_COMPANION_LIST_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//��ϵ�б�
class CUserCompanionList : public CTreeCtrl
{
	//��������
protected:
	HTREEITEM						m_hItemRoot;						//�����
	HTREEITEM						m_hItemDetest;						//�������
	HTREEITEM						m_hItemFriend;						//��������
	HTREEITEM						m_hItemNormal;						//İ������

	//��Դ����
protected:
	CImageList						m_ImageCompanionList;				//ͼƬ��Դ

	//��������
public:
	//���캯��
	CUserCompanionList();
	//��������
	virtual ~CUserCompanionList();

	//��ϵ�ӿ�
public:
	//����֪ͨ
	virtual bool __cdecl OnCompanionInsert(tagCompanionItem * pCompanionInfo);
	//����֪ͨ
	virtual bool __cdecl OnCompanionUpdate(tagCompanionItem * pCompanionInfo);
	//ɾ��֪ͨ
	virtual bool __cdecl OnCompanionDelete(tagCompanionItem * pCompanionInfo);

	//������
private:
	//������Ϣ
	bool InsertCompanionInfo(const tagCompanionItem * pCompanionInfo);
	//ɾ����ϵ
	bool DeleteCompanionInfo(tagCompanionItem * pCompanionInfo);
	//������Ϣ
	bool UpdateCompanionInfo(HTREEITEM hTreeItem, tagCompanionItem * pCompanionInfo);

	//�ڲ�����
private:
	//��ȡ��ϵ
	BYTE GetTreeItemCompanion(HTREEITEM hTreeItem);
	//Ѱ������
	HTREEITEM SearchCompanionInfo(HTREEITEM hRootTreeItem, tagCompanionItem * pCompanionInfo);

	//��Ϣӳ��
protected:
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif