#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//���Ի�����
class CMakeGUIDDlg : public CDialog
{
	//��������
public:
	//���캯��
	CMakeGUIDDlg();

	//�Ի�������
	enum { IDD = IDD_MAKEGUID_DIALOG };

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual void OnOK();

	//��Ϣ����
public:
	//XOR ��ť
	afx_msg void OnBnClickedXOR();
	//MD5 ��ť
	afx_msg void OnBnClickedMD5();
	//������ť
	afx_msg void OnBnClickedCopy();
	//������ť
	afx_msg void OnBnClickedPrime();
	//�汾��ť
	afx_msg void OnBnClickedVersion();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
