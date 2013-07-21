#pragma once
#include "stdafx.h"
#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "GameZonePage.h"
#include "GlobalUnits.h"
#include "FrameSet.h"

class CPlatformFrame : public CFrameWnd ,public ITCPSocketSink
{
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
	//�����¼�
public:
	//�����¼�
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);
public:
	//������Ϣ
	void SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);
	//��ʾ��Ϣ
	int ShowMessageBox(LPCTSTR pszMessage, UINT nType);
	
	//��Ӧ��������Ϣ����
public:
	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pData, WORD wDataSize);
	//�б���Ϣ
	bool OnSocketMainServerList(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//ϵͳ��Ϣ
	bool OnSocketMainSystem(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool OnSocketMainUser(CMD_Command Command, void * pBuffer, WORD wDataSize);


protected:
	CTCPSocketHelper				m_ClientSocket;						//��������
	bool							m_bLogonPlaza;		//�Ƿ��Ѿ���½

	CGamePlazaDlg*					m_pGamePlazaDlg;
	CDlgLogon						m_DlgLogon;				//��¼�Ի���
	CFrameSet						m_DlgFrameSet;			//�򿪴�������

	//��Դ
protected:
	CPngImage						m_ImageHead;
	CPngImage						m_ImageBack;
	CPngImage						m_ImageUserInfo;
	CPngImage						m_ImageGamePublic;

	CPngImage						m_UserHead;

	//�ؼ���ť
protected:
	CGdipButton						m_btMin;
	CGdipButton						m_btClose;
	CGdipButton						m_LobbySet;

	CGdipButton						m_btGame;
	CGdipButton						m_btMatch;
	CGdipButton						m_btProperty;
	CGdipButton						m_btPrize;
	CGdipButton						m_btRecharge;
	CGdipButton						m_btReflash;
	CGdipButton						m_btUserInfoSet;
	CGdipButton						m_btReturn;

	CGdipButton						m_btUserBag;
	CGdipButton						m_btSquare;
	CGdipButton						m_btTill;
	CGdipButton						m_btIm;
	
protected:
	CGameZonePage					m_ZonePage;

public:
	//���ذ�ť
	void LoadButtons();
	//����ͼƬ��Դ
	void LoadImages();
	//��ť��������
	void SetButtonBackGrounds(CDC *pDC);
	//���ƽ�ɫ��Ϣ
	void DrawUserInfo(CDC *pDC);

	//���غ���
public:
	virtual BOOL RectifyResource(int nWidth, int nHeight);
	virtual void SetFrameSize(int nWidth, int nHeight);
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);	
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�ر���Ϣ
	VOID OnClose();
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//��¼
	afx_msg void OnCommandLogon();
	//���ӷ�����
	afx_msg void OnCommandConnect();
	//ȡ������
	afx_msg void OnCommandCancelConnect();
	//�򿪴�������
	afx_msg void OnOpenFrameSet();

protected:
	DECLARE_MESSAGE_MAP()
};


