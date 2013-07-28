#pragma once
#include "stdafx.h"
#include "GamePlazaDlg.h"
#include "GdipButton.h"
#include "DlgLogon.h"
#include "GlobalUnits.h"
#include "FrameSet.h"
#include "PlatformSocket.h"
#include "DlgEnquire.h"
#include "UIFrameSheet.h"

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
	YouLe::UIFrameSheet				m_FrameSheet;
public:
	//����ͼƬ��Դ
	void LoadImages();
	//���ƽ�ɫ��Ϣ
	void DrawUserInfo(CDC *pDC);

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
	//�򿪴�������
	afx_msg void OnOpenFrameSet();
	afx_msg void OnTabGame();
	afx_msg void OnTabCard();
	afx_msg void OnTabMahj();
	afx_msg void OnTabLeis();
public:
	void SaveBossKey(int nCtrlKey, int nHelpKey);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


