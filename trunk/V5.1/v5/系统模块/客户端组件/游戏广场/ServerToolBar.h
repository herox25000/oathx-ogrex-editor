#ifndef SERVER_TOOL_BAR_HEAD_FILE
#define SERVER_TOOL_BAR_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//��Ϸ�㳡
class CServerToolBar : public CDialog, public IUnknownEx
{
	//��ʶ����
protected:
	bool                            m_bCreateFlag;                      //������ʶ 

	//��ť����
protected:
	CSkinButton						m_btQuitServer;						//�뿪����
	CSkinButton						m_btTableButton1;					//���Ӱ�ť
	CSkinButton						m_btTableButton2;					//���Ӱ�ť
	CSkinButton						m_btTableButton3;					//���Ӱ�ť
	CSkinButton						m_btTableButton4;					//���Ӱ�ť
	CSkinButton						m_btTableButton5;					//���Ӱ�ť

	//��������
public:
	//���캯��
	CServerToolBar();
	//��������
	virtual ~CServerToolBar();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange* pDX);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK() { return; };
	//ȡ������
	virtual VOID OnCancel() { return; };	
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//�ڲ�����
protected:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);

	//�Զ���Ϣ
protected:
	//�¼���Ϣ
	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);	

	DECLARE_MESSAGE_MAP()	
};

//////////////////////////////////////////////////////////////////////////////////

#endif