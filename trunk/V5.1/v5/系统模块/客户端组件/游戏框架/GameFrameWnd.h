#ifndef GAME_FRAME_WND_HEAD_FILE
#define GAME_FRAME_WND_HEAD_FILE

#pragma once

#include "GameFrameHead.h"
#include "GameFrameControl.h"
#include "DlgGameRule.h"

//////////////////////////////////////////////////////////////////////////////////

//�����Դ
class CFrameEncircle : public CEncircleBMP
{
	//��������
public:
	//���캯��
	CFrameEncircle();
	//��������
	virtual ~CFrameEncircle();

	//���غ���
protected:
	//�滭����
	virtual bool PreDrawEncircleImage(tagEncircleBMP & EncircleImage);
};

//////////////////////////////////////////////////////////////////////////////////

//��Ϸ����
class GAME_FRAME_CLASS CGameFrameWnd : public CFrameWnd, public IGameFrameWnd,public IFlashControlSink,public IClientPropertySink,public ISplitterEvent
{
	//״̬����
protected:
	bool							m_bMaxShow;							//����־
	bool							m_bShowControl;						//��ʾ��־
	CRect							m_rcNormalSize;						//����λ��
	CSize                           m_ScreenMetrics;                    //��Ļ�ߴ� 

	//��������
protected:
	INT								m_nScrollXPos;						//����λ��
	INT								m_nScrollYPos;						//����λ��
	INT								m_nScrollXMax;						//���λ��
	INT								m_nScrollYMax;						//���λ��

	//����ӿ�
protected:
	IClientKernel *					m_pIClientKernel;					//�ں˽ӿ�
	IGameFrameView *				m_pIGameFrameView;					//��ͼ�ӿ�

	//�ؼ�����
public:
	CSkinButton						m_btMin;							//��С��ť
	CSkinButton						m_btMax;							//���ť
	CSkinButton						m_btClose;							//�رհ�ť
	CSkinButton						m_btOption;							//ѡ�ť
	CSkinButton						m_btMuteContrl;						//������ť
	CSkinButton						m_btRule;							//�Թ۰�ť
	CSkinButton                     m_btControl;                        //���ư�ť
	CSkinScrollBar					m_SkinScrollBar;					//��������

	//�ؼ�ָ��
protected:
	CDlgGameRule *					m_pDlgGameRule;						//��Ϸ����

	//���ܿؼ�
public:
	CFlashControl					m_FlashControl;						//�����ؼ�
	CToolTipCtrl					m_ToolTipCtrl;						//��ʾ�ؼ�
	CSkinSplitter					m_SkinSplitter;						//��ֿؼ�
	CGameFrameControl				m_GameFrameControl;					//���ƿ��

	//��Դ����
protected:
	CFrameEncircle					m_FrameEncircle;					//�����Դ

	//��������
public:
	//���캯��
	CGameFrameWnd();
	//��������
	virtual ~CGameFrameWnd();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//��������
protected:
	//�޸ķֱ���
	VOID ChangeScreenSetting(INT nScreencx,INT nScreency,bool bRecordResol);

	//���ڿ���
public:
	//��Ϸ����
	virtual bool ShowGameRule();
	//��󴰿�
	virtual bool MaxSizeWindow();
	//��ԭ����
	virtual bool RestoreWindow();

	//���ƽӿ�
public:
	//��������
	virtual bool AllowGameSound(bool bAllowSound);
	//�Թۿ���
	virtual bool AllowGameLookon(DWORD dwUserID, bool bAllowLookon);
	//���ƽӿ�
	virtual bool OnGameOptionChange();

	//��ֽӿ�
protected:
	//����¼�
	virtual VOID OnSplitterEvent(UINT uControlID, INT nXPos, INT nYPos);

	//���߽ӿ�
public:
	//�������
	virtual VOID OnEventFlashFinish();
	//���߳ɹ�
	virtual VOID OnPropertySuccess(LPCTSTR szTargerNickName,DWORD dwSourceUserID,DWORD dwTargerUserID,WORD wPropertyIndex,WORD wPropertyCount);
	//����ʧ��
	virtual VOID OnPropertyFailure( LONG lErrorCode,LPCTSTR szDescribeString);

	//���غ���
protected:
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//���溯��
protected:
	//��ԭ����
//	bool RestoreWindow();
	//��󴰿�
//	bool MaxSizeWindow();

	//�������
protected:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��������
	UINT OnNcHitTest(CPoint Point);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//λ����Ϣ
	VOID OnGetMinMaxInfo(MINMAXINFO * lpMMI);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDblClk(UINT nFlags, CPoint Point);
	//�ı���Ϣ
	VOID OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	//�Զ���Ϣ
protected:
	//������Ϣ
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);

	//ϵͳ��Ϣ
public:
	//��������
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

};

//////////////////////////////////////////////////////////////////////////////////

#endif