#ifndef CHAT_HISTORY_HEAD_FILE
#define CHAT_HISTORY_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"
#include "GamePlazaHead.h"

//////////////////////////////////////////////////////////////////////////

class CChatHistory;
class CChatHistoryManager;

//��Ϣ��
class CChatMsgItem: public CObject, public IChatMsgItem
{
	//��Ԫ��
	friend class CChatHistory;

	//��������
protected:
	CString							m_strSendUser;						//�������
	CString							m_strMsg;							//������Ϣ
	COLORREF						m_crChatColor;						//������ɫ
	BYTE							m_bSelfMsg;							//�Ƿ��Լ�����Ϣ
	SYSTEMTIME						m_Time;								//��Ϣʱ��

	//��������
public:
	//���캯��
	CChatMsgItem();
	//��������
	virtual ~CChatMsgItem();

	//���غ���
public:
	//���л�
	virtual void Serialize( CArchive& ar );

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID  Release(){}
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//���ܺ���
public:
	//������Ŀ
	virtual VOID __cdecl ResetChatMsg();
	//��ȡ���
	virtual LPCTSTR __cdecl GetSendUserAccounts() { return m_strSendUser; }
	//��ȡ������Ϣ
	virtual LPCTSTR __cdecl GetMsg() { return m_strMsg; }
	//��ȡ������ɫ
	virtual COLORREF __cdecl GetChatColor() { return m_crChatColor; }
	//�Ƿ��Լ���Ϣ
	virtual bool __cdecl IsSelfMsg() { return (m_bSelfMsg>0); }
	//��ȡʱ��
	virtual const SYSTEMTIME& GetMsgTime() { return m_Time; }

protected:
	DECLARE_SERIAL(CChatMsgItem)
};

//////////////////////////////////////////////////////////////////////////

//��Ϣ����
typedef CWHArray<CChatMsgItem *>	CChatMsgItemArray;

//��Ϣ��¼��
class CChatHistory: public CObject, public IChatHistory
{
	//��Ԫ��
	friend class CChatHistoryManager;

	//��������
protected:
	DWORD								m_dwChatID;							//��¼ID
	CChatMsgItemArray					m_ChatMsgItemActive;				//��Ϣ����
	static CChatMsgItemArray			m_ChatMsgItemStorge;				//��Ϣ���
	IChatHistoryManager*				m_pIChatHistoryManager;				//����ӿ�

	//��������
public:
	//���캯��
	CChatHistory();
	//��������
	virtual ~CChatHistory();
	
	//���غ���
public:
	//���л�
	virtual void Serialize( CArchive& ar );

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release();
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//��ѯ����
public:
	//��ȡ��¼ID
	virtual DWORD __cdecl GetChatID() { return m_dwChatID; }
	//��ȡ��Ϣ��
	virtual INT_PTR __cdecl GetMsgItemCount() { return m_ChatMsgItemActive.GetCount(); }
	//ö����Ϣ
	virtual IChatMsgItem* __cdecl EnumChatMsgItem(INT_PTR nEnumIndex);

	//���ܺ���
public:
	//���ü�¼
	virtual VOID __cdecl ResetChatHistory();
	//�����Ϣ
	virtual bool __cdecl AddMsgItem(LPCTSTR lpszSendUser,LPCTSTR lpszMsg,COLORREF crColor,bool bMySelfString);
	//�����¼
	virtual bool __cdecl ClearHistory();

	//�ļ�����
public:
	//�����¼
	virtual bool __cdecl Save();

	//��������
protected:
	//������Ϣ��
	CChatMsgItem* ActiveChatMsgItem();

protected:
	DECLARE_SERIAL(CChatHistory)
};

//////////////////////////////////////////////////////////////////////////

//�����¼����
typedef CWHArray<CChatHistory *>	CChatHistoryArray;

//��¼ӳ��
typedef CMap<DWORD,DWORD,CChatHistory *,CChatHistory *> CMapChatHistory;

//////////////////////////////////////////////////////////////////////////

//�����¼������
class CChatHistoryManager:public IChatHistoryManager
{
	//��������
protected:
	IClientUserItem*						m_pIMyselfUserItem;			//��ҽӿ�
	CChatHistoryArray						m_ChatHistoryActive;		//��¼����
	static CChatHistoryArray				m_ChatHistoryStorge;		//��¼���
	CMapChatHistory							m_MapChatHistory;			//��¼ӳ��

	//��������
public:
	//���캯��
	CChatHistoryManager();
	//��������
	virtual ~CChatHistoryManager();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release(){}
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//���ýӿ�
public:
	//��ʼ��
	virtual VOID SetMyselftUserItem(IClientUserItem *pIMyselfUserItem);

	//��ѯ�ӿ�
public:
	//��ȡ��ҽӿ�
	virtual IClientUserItem * __cdecl GetMyselftUserItem() { return m_pIMyselfUserItem; }

	//���ܽӿ�
public:
	//�����¼
	virtual IChatHistory* __cdecl ActiveChatHistory(DWORD dwChatID);
	//�رռ�¼
	virtual bool __cdecl CloseChatHistory(DWORD dwChatID);
	//�����¼
	virtual bool __cdecl SaveChatHistory(DWORD dwChatID);
};

//////////////////////////////////////////////////////////////////////////

#endif