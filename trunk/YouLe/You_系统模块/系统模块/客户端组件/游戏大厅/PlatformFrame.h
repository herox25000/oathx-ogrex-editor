#pragma once

#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "GameItemWnd.h"
#include "GameRoomWnd.h"
#include "TabGamePage.h"


class CPlatformFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

protected:
	CGamePlazaDlg*					m_pGamePlazaDlg;
	CDlgLogon						m_DlgLogon;							//��¼�Ի���

	//��Դ
protected:
	CPngImage				m_ImageHead;
	CPngImage				m_ImageBack;

	//�ؼ���ť
protected:
	CGdipButton						m_btMin;
	CGdipButton						m_btClose;
	
	CTabGamePage					m_pGamePage;
public:
	//���ذ�ť
	void LoadButtons();
	//����ͼƬ��Դ
	void LoadImages();
	//��ť��������
	void SetButtonBackGrounds(CDC *pDC);
public:
	//��¼��Ϣ
	virtual bool __cdecl SendLogonMessage();
	//������Ϣ
	virtual bool __cdecl SendConnectMessage();

public:
	virtual BOOL					RectifyResource(int nWidth, int nHeight);
	virtual void					SetFrameSize(int nWidth, int nHeight);

//���غ���
protected:
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);

protected:	
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

protected:
	DECLARE_MESSAGE_MAP()
};


