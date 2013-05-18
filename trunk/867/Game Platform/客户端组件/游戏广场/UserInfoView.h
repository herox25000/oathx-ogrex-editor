#ifndef PLAZA_USER_INFO_VIEW_HEAD_FILE
#define PLAZA_USER_INFO_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "Resource.h"

//////////////////////////////////////////////////////////////////////////

//�༭�ؼ�
class CEditUnderWrite : public CSkinEditEx, public ITCPSocketSink
{
	//��Ԫ����
	friend class CUserInfoView;
	//��������
protected:
	bool							m_bNeedSend;						//�����־
	TCHAR							m_szUnderWrite[UNDER_WRITE_LEN];	//����ǩ��

	//��������
protected:
	CWnd *							m_pParentWnd;						//���ڶ���
	CTCPSocketHelper				m_SocketHelper;					//��������

	//�����ӿ�
public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//���غ���
public:
	//�����¼�
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);


	//��������
public:
	//���캯��
	CEditUnderWrite();
	//��������
	virtual ~CEditUnderWrite();

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//���ܺ���
public:
	//�޸��ж�
	bool IsModifyStatus();
	//���ô���
	VOID SetParentWindow(CWnd * pParentWnd);

	//�ڲ�����
protected:
	//�رտؼ�
	VOID CloseUnderWrite();
	//����ǩ��
	VOID UpdateUnderWrite();

	//��Ϣ����
protected:
	//������Ϣ
	VOID OnDestroy();
	//ʧȥ����
	VOID OnKillFocus(CWnd * pNewWnd);

	DECLARE_MESSAGE_MAP()
};



//�û���Ϣ
class CUserInfoView : public CDialog
{
	//״̬����
protected:
	bool							m_bShowInfo;						//��ʾ��־
	bool							m_bCreateFlag;						//������־
	UINT							m_nTitleHeight;						//����߶�

	//��Դ����
protected:
	CSkinImage						m_ImageTitleL;						//λͼ����
	CSkinImage						m_ImageTitleM;						//λͼ����
	CSkinImage						m_ImageTitleR;						//λͼ����

	//�û�ǩ��
public:
	bool							m_bHoverUnderWrite;					//������־
	CRect							m_rcUnderWrite;						//ǩ������
	CEditUnderWrite					m_EditUnderWrite;					//�༭�ؼ�

	//ͷ���û����ģ�
public:
	bool							m_bClickFace;						//�����־
	bool							m_bHoverFace;						//������־
	CRect							m_rcFaceArea;						//ͷ������
	CSize							m_SizeItemFrame;					//��ܴ�С
	CPngImage						m_ImageItemFrame;					//ͷ����
	//��������
public:
	//���캯��
	CUserInfoView();
	//��������
	virtual ~CUserInfoView();

	//���غ���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK() { return; };
	//ȡ������
	virtual VOID OnCancel() { return; };

	//���ܺ���
public:
	//����߶�
	UINT GetTitleHeight();
	//������Ϣ
	VOID UpdateUserInfo();
	//��ʾ��Ϣ
	VOID ShowUserInfo(bool bShowInfo);
	//������Դ
	bool UpdateSkinResource();

	//���溯��
private:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint MousePoint);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint MousePoint);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);

	//�Զ���Ϣ
protected:
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif