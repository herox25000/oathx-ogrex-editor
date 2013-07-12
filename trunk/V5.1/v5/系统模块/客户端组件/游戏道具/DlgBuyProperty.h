#ifndef DLG_BUY_PROPERTY_HEAD_FILE
#define DLG_BUY_PROPERTY_HEAD_FILE

#pragma once

#include "GamePropertyHead.h"

//////////////////////////////////////////////////////////////////////////////////

//��˵��
class CGamePropertyItem;

//////////////////////////////////////////////////////////////////////////////////

//���߹���
class CDlgBuyProperty : public CSkinDialog
{
	//��Ԫ����
	friend class CGamePropertyItem;

	//��������
protected:
	LONGLONG                        m_lCanBuyCount;                     //�����Ŀ 

	//���ܰ�ť
protected:
	CSkinButton			 			m_btOk;								//ȷ����ť
	CSkinButton			 			m_btCancel;							//������ť

	//�ؼ�����
protected:
	CSkinEdit						m_edNickName;						//�û��ǳ�
	CSkinEdit						m_edPropertyCount;					//������Ŀ

	//�ӿڱ���
protected:
	CGamePropertyItem *				m_pGamePropertyItem;				//���߶���
	IGamePropertySink *				m_pIGamePropertySink;				//�ص��ӿ�

	//��̬����
protected:
	static CDlgBuyProperty *		m_pDlgBuyProperty;					//����ָ��

	//��������
public:
	//���캯��
	CDlgBuyProperty();
	//��������
	virtual ~CDlgBuyProperty();

	//���ú���
protected:
	//�ؼ���
	virtual VOID DoDataExchange(CDataExchange * pDX);
	//��Ϣ����
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK();
	//ȡ����Ϣ
	virtual VOID OnCancel();

	//���ú���
protected:
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

	//���ܺ���
protected:
	//����״̬
	VOID UpdateCtrlStatus();

	//��̬����
protected:
	//��ʾ����
	static VOID ShowBuyPropertyWnd(CGamePropertyItem * pGamePropertyItem, IGamePropertySink * pIGamePropertySink);
	//ִ������
	static VOID OnEventPerformCommand(WORD wCommandID,VOID * pCmdData);
	

	//��Ϣ����
protected:
	//�ı��¼�
	afx_msg void OnEnChangePropertyCount();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif