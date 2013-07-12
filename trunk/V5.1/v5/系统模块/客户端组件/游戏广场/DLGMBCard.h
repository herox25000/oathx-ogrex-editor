#pragma once
#include "stdafx.h"

// CDLGMBCard dialog

class CDLGMBCard : public CSkinDialog
{
public:
	UINT								m_uMBCardID;						//��������
	CHAR								m_szRandLetter[3];
	BYTE								m_szRandNumber[3];
	BYTE								m_cbErrorCount;
	UINT								m_uCoorNumber[6][4];

	CSkinButton							m_btOK;
	CSkinButton							m_btCancel;

	//��������
public:
	CDLGMBCard(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDLGMBCard();

	//��������
public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//���غ���
public:
	//������Ϣ
	virtual BOOL OnInitDialog();
	//��ť��Ϣ
	void OnOK();
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

	//��������
public:
	void RandCoordinate();
	void SetMBCard(UINT uMBCardID);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CDLGMBCard)
};
