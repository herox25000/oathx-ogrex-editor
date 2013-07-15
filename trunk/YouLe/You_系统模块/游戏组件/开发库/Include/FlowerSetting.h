#ifndef FLOWER_SETTING_HEAD_FILE
#define FLOWER_SETTING_HEAD_FILE
#pragma once

#include "PropertyModule.h"
#include "GameFrame.h"
///////////////////////////////////////////////////////////////////////////////////

class PROPERTY_MODULE_CLASS CFlowerSetting : public CSkinDialogEx
{
	//��������
public:
	int								m_nFlowerCount;						//�ʻ���Ŀ
	int								m_nFlowerID;						//�ʻ�ID

	//�󶨱���
public:
	CComboBox						m_ComboBoxTargetUser;				//Ŀ�����
	DWORD							m_dwTargetUserID;					//Ŀ�����
	CString							m_strDescribe;						//��ͨ�۸�
	CString							m_strNormalUserPrice;				//��ͨ�۸�
	CString							m_strMemberUserPrice;				//��Ա�۸�
	CString							m_strGoldDescribe;					//������

	//�ؼ�����
protected:
	CSkinButton						m_btOK;								//ȷ����ť
	CSkinButton						m_btCancel;							//ȡ����ť

	//����ӿ�
protected:
	IClientKernel					*m_pIClientKernel;					//��ܽӿ�

	//��������
public:
	//���캯��
	CFlowerSetting(CWnd* pParent = NULL);
	//��������
	virtual ~CFlowerSetting();

	//��������
public:
	//����ID
	void SetFlowerID(int nFlowerID) { m_nFlowerID = nFlowerID ;}
	//���ýӿ�
	void SetClientKernel(IClientKernel *pIClientKernel) {ASSERT(pIClientKernel!=NULL); m_pIClientKernel = pIClientKernel;}
	//���½���
	void UpdateView();
	//����Ŀ��
	void SetTargetUserID(DWORD dwTargetUserID){m_dwTargetUserID = dwTargetUserID;}

	//�̳к���
protected:
	//�󶨺���
	virtual void DoDataExchange(CDataExchange* pDX);

	//��Ϣ����
public:
	//��ť��Ϣ
	afx_msg void OnBnClickedOk();
	//��ʼ����
	virtual BOOL OnInitDialog();
	//������ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//�ƶ���Ϣ
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	//��Ϣӳ��
	DECLARE_MESSAGE_MAP()
};
///////////////////////////////////////////////////////////////////////////////////
#endif
