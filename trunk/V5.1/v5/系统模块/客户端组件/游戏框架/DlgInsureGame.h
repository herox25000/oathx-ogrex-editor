#ifndef DLG_INSURE_GAME_HEAD_FILE
#define DLG_INSURE_GAME_HEAD_FILE

#pragma once

#include "GameFrameHead.h"
//////////////////////////////////////////////////////////////////////////

void MakeString(CString &strNum,SCORE lNumber);
void MakeStringToNum(CString str,SCORE &Num);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// CDlgInsureGame dialog
#define  WM_CREADED						WM_USER+1
class CDlgInsureGame : public CSkinDialog
{
	//��������
public:
	bool							m_bBankStorage;					//�洢��ʶ
	IClientUserItem					*m_pMeUserData;					//�û���Ϣ
	WORD							m_wRevenueTake;					//˰�ձ���
	WORD							m_wRevenueTransfer;				//˰�ձ���
	SCORE							m_lGameGold;					//������Ŀ
	SCORE							m_lStorageGold;					//�洢��Ŀ
	SCORE							m_lInCount;						//������Ϸ��
	SCORE							m_OrInCount;                    //
	bool							m_blCanStore;                   //�ܴ�
	bool                            m_blCanGetOnlyFree;             //��������ȡ

	//�ؼ�����
protected:
	CSkinButton						m_btOK;							//ȷ����ť
	CSkinButton						m_btCancel;						//ȡ����ť
	CSkinButton						m_btFresh;						//ˢ�°�ť
	CEdit							m_Edit;
	CStatic							m_Static;
	bool							m_blUsingPassWord;
	CPngImage						m_ImageFrame;					//	
	CPngImage						m_ImageNumber;

	//�ӿڱ���
protected:	
	IClientKernel					* m_pIClientKernel;				//�ں˽ӿ�

public:
	CDlgInsureGame(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgInsureGame();

	//��������
public:
	//���½���
	void UpdateView();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange* pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ˢ�°�ť
	afx_msg void OnBnClickedFresh();
	//ȷ����ť
	afx_msg void OnBnClickedOk();
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//������Ϣ
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//ʱ����Ϣ
	afx_msg void OnTimer(UINT nIDEvent);
	//������Ϣ
	afx_msg void OnEnChangeInCount();
	//��ѡ
	afx_msg void OnBnClickedCheck();
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);
	//������Ϣ
    int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//������Ϣ
	afx_msg LRESULT  OnCreateEd(WPARAM wparam,LPARAM lparam);

	//�ӿں���
public:
	//��������
	void SetBankerActionType(bool bStorage);
	//����λ��
	void SetPostPoint(CPoint Point);
	//��ʾ����
	void ShowItem();

	//���ܺ���
public:
	//�Ƿ�ѡ��
	bool IsButtonSelected(UINT uButtonID);
	//ѡ�а�ť
	void SetButtonSelected(UINT uButtonID, bool bSelected);
	//�������
	void SetSendInfo(IClientKernel *pClientKernel,IClientUserItem const*pMeUserDatas);
	//������Ϣ
	void SendSocketData(WORD wMainCmdID, WORD wSubCmdID, void * pBuffer, WORD wDataSize);
	void OnCancelEvent();
	//�滭����
	VOID DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CDlgInsureGame)
protected:
	virtual void OnCancel();
	virtual void OnOK();
};

//////////////////////////////////////////////////////////////////////////

#endif