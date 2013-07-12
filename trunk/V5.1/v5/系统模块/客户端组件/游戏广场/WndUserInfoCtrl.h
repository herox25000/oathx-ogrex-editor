#ifndef WND_USER_INFO_CTRL_HEAD_FILE
#define WND_USER_INFO_CTRL_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//�û���Ϣ
class CWndUserInfoCtrl : public CWnd
{
	//�ؼ�����
public:
	CSkinButton						m_btUserInfo1;						//�û���ť
	CSkinButton						m_btUserInfo2;						//�û���ť
	CSkinButton						m_btUserInfo3;						//�û���ť

	//�ؼ�����
public:
	CDlgInsurePlaza *               m_pDlgInsurePlaza;                 //��������

	//��������
public:
	//���캯��
	CWndUserInfoCtrl();
	//��������
	virtual ~CWndUserInfoCtrl();

	//���غ���
protected:
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//���溯��
private:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);
	//ת���ַ�
	VOID SwitchScoreFormat(SCORE lScore, UINT uSpace, UINT uDecimalCount, LPTSTR pszBuffer, WORD wBufferSize);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	//�Զ���Ϣ
protected:
	//�¼���Ϣ
	LRESULT OnMessagePlatformEvent(WPARAM wParam, LPARAM lParam);


	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif