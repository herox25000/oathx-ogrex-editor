#pragma once
#include "stdafx.h"
#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "PlatformSocket.h"
#include "UIFrameSheet.h"
#include "FrameSet.h"

class CPlatformSocket;
class CPlatformFrame : public CFrameWnd 
{
	friend class CPlatformSocket;
	DECLARE_DYNCREATE(CPlatformFrame)
public:
	CPlatformFrame(); 

protected:
	virtual ~CPlatformFrame();

protected:
	CPlatformSocket					m_PlatformSocket;
	CGamePlazaDlg*					m_pGamePlazaDlg;
	CDlgLogon						m_DlgLogon;				//��¼�Ի���

	//��Դ
protected:
	CPngImage						m_ImageHead;
	CPngImage						m_ImageBack;
	CPngImage						m_ImageUserInfo;
	CPngImage						m_ImageGamePublic;
	
protected:
	YouLe::UIFrameSheet				m_FrameSheet;
public:
	//����ͼƬ��Դ
	void LoadImages();

public:
	//��Դ���
	HINSTANCE GetResInstanceHandle();
	//��ȡ��Դ
	tagPlatformFrameImageNew GetPlatformRes();

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
	//IPC ��Ϣ
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT * pCopyDataStruct);
public:
	void		SaveBossKey(int nCtrlKey, int nHelpKey);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


