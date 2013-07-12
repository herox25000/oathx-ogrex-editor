#ifndef PLATFORM_FRAME_HEAD_FILE
#define PLATFORM_FRAME_HEAD_FILE

#pragma once

//ϵͳ�ļ�
#include "Stdafx.h"
#include "Resource.h"

//�����ļ�
#include "MissionList.h"
#include "MissionLogon.h"

//�ؼ��ļ�
#include "DlgWhisper.h"
#include "DlgCollocate.h"
#include "PlazaViewItem.h"
#include "ServerViewItem.h"
#include "ServerToolBar.h"

//���ڿؼ�
#include "WndGameTypeCtrl.h"
#include "WndUserInfoCtrl.h"
#include "MiddleFrameControl.h"
#include "PlatformPublicize.h"
#include "DlgLockMachine.h"
#include "DlgCustomFace.h"

//�б�״̬
enum enServerListControl
{
	ServerListControl_Hide,			//�����б�
	ServerListControl_Show,			//��ʾ�б�
	ServerListControl_Turn,			//��ת�б�
};

//////////////////////////////////////////////////////////////////////////////////

//�ȼ�����
#define IDI_HOT_KEY_BOSS			0x0100								//�ϰ��ȼ�

//////////////////////////////////////////////////////////////////////////////////

//ƽ̨���
class CPlatformFrame : public CFrameWnd, public IServerListDataSink, public ICustomFaceEvent
{
	//״̬����
protected:
	bool							m_bMaxShow;							//����־
	bool							m_bRectify;							//������־
	bool							m_bWhisperIcon;						//˽��ͼ��
	bool							m_bShowLeftPanel;					//���ر�־
	CRect                           m_rcPlazaView;                      //������ͼ 
	CRect							m_rcServerView;						//��ͼ��С
	CRect                           m_rcGameType;                       //��Ϸ����
	CRect                           m_rcToolBar;                        //������  
	CRect							m_rcNormalSize;						//����λ��
	CSize                           m_ScreenMetrics;                    //��Ļ�ߴ� 

	//���ư�ť
public:
	CSkinButton						m_btMin;							//��С��ť
	CSkinButton                     m_btMax;                            //���ť
	CSkinButton						m_btClose;							//�رհ�ť
	CSkinButton						m_btNavigation[7];					//������ť

	//��ܿؼ�
protected:
	CWndGameTypeCtrl				m_WndGameTypeCtrl;					//��������
	CWndUserInfoCtrl				m_WndUserInfoCtrl;					//�û���Ϣ
	CMiddleFrameControl             m_MiddleFrameControl;               //�м���

	//�ؼ�����
protected:
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��
	CSkinSplitter					m_SkinSplitter;						//��ֿؼ�
	CServerListData					m_ServerListData;					//��Ϸ����
	CSystemTrayIcon					m_SystemTrayIcon;					//����ͼ��
	CPlatformPublicize              m_PlatFormNoticePublicize;          //����ؼ� 

	//�������
protected:
	CMissionList					m_MissionList;						//�б�����
	CMissionLogon					m_MissionLogon;						//��¼����
	CMissionManager					m_MissionManager;					//�������

	//�ؼ�����
public:
	CPlazaViewItem					m_PlazaViewItem;					//��Ϸ�㳡
	CServerViewItem	*				m_pServerViewItem;					//��ǰ����
	CServerToolBar                  m_ServerToolBar;                    //���乤�� 
	CDlgWhisperItemArray			m_DlgWhisperItemArray;				//˽������

	//��Դ����
protected:
	CBitImage						m_ImageFrame;						//���ͼƬ
	CEncirclePNG					m_FrameEncircle;					//�����Դ
	CEncircleBMP					m_AfficheEncircle;					//�����Դ
	CEncircleBMP					m_ItemFrameEncircle;				//�����Դ

	//��̬����
protected:
	static CPlatformFrame *			m_pPlatformFrame;					//���ָ��

	//��������
public:
	//���캯��
	CPlatformFrame();
	//��������
	virtual ~CPlatformFrame();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//ͷ��ӿ�
protected:
	//����ʧ��
	virtual VOID OnEventSystemFace(DWORD dwUserID, WORD wFaceID);
	//ͷ������
	virtual VOID OnEventCustomFace(DWORD dwUserID, DWORD dwCustomID, tagCustomFaceInfo & CustomFaceInfo);

	//״̬֪ͨ
public:
	//��ȡ֪ͨ
	virtual VOID OnGameItemFinish();
	//��ȡ֪ͨ
	virtual VOID OnGameKindFinish(WORD wKindID);
	//����֪ͨ
	virtual VOID OnGameItemUpdateFinish();

	//����֪ͨ
public:
	//����֪ͨ
	virtual VOID OnGameItemInsert(CGameListItem * pGameListItem);
	//����֪ͨ
	virtual VOID OnGameItemUpdate(CGameListItem * pGameListItem);
	//ɾ��֪ͨ
	virtual VOID OnGameItemDelete(CGameListItem * pGameListItem);

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//���溯��
private:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);
	//������Դ
	VOID RectifyResource(INT nWidth, INT nHeight);
	//�滭����
	VOID DrawControlView(CDC * pDC, INT nWidth, INT nHeight);
	//�޸ķֱ���
	VOID ChangeScreenSetting(INT nScreencx,INT nScreency,bool bRecordResol);

	//�������
public:
	//�����
	bool ActiveServerViewItem();
	//ɾ������
	bool DeleteServerViewItem();
	//���뷿��
	bool EntranceServerItem(CGameServerItem * pGameServerItem);

	//˽�ĺ���
public:
	//��ȡ˽��
	bool ShowWhisperItem();
	//����˽��
	bool InsertWhisperItem(CDlgWhisper * pDlgWhisper);
	//ɾ��˽��
	bool RemoveWhisperItem(CDlgWhisper * pDlgWhisper);

	//���ܺ���
public:
	//��ʾ���
	VOID ShowPlazaLeftPanel(bool bShowPanel);
	//��󴰿�
	virtual bool MaxSizeWindow();
	//��ԭ����
	virtual bool RestoreWindow();

	//��Ϣ����
protected:
	//�ر���Ϣ
	VOID OnClose();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//ʱ����Ϣ
	VOID OnTimer(UINT_PTR nIDEvent);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);

	//�Զ���Ϣ
protected:
	//�¼���Ϣ
	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);
	//���и���
	LRESULT OnMessageInsureUpdate(WPARAM wParam, LPARAM lParam);

	//���ܺ���
public:
	//��ȡʵ��
	static CPlatformFrame * GetInstance() { return m_pPlatformFrame; }

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif