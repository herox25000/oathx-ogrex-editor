#ifndef SINGLE_PRO_ITEM_CONTROL_HEAD
#define SINGLE_PRO_ITEM_CONTROL_HEAD

#pragma once

#include "GamePropertyHead.h"


//////////////////////////////////////////////////////////////////////////
//���˵���
class  GAME_PROPERTY_CLASS  CDlgTrumpetItem : public CSkinDialog,public IExpressionSink
{
	//��������
protected:
	int								m_nMaxChar;						//������
	WORD                            m_wRadioSelected;               //��ѡ��ť  
	COLORREF						m_crChatTX;						//������ɫ
	CString							m_strInuptChat;					//������Ϣ
	CString							m_strPropertyInfo;				//������Ϣ

	//�ؼ�����
protected:
	CExpressionControl *			m_pExpressionControl;			//���鴰��
	CEdit							m_InputChat;					//�����
	CSkinButton						m_btOK;							//ȷ����ť
	CSkinButton						m_btCancel;						//�رհ�ť
	CSkinButton						m_btExpression;					//���鰴ť
	CSkinButton						m_btColorSet;					//��ɫ����

	//�ӿڱ���
protected:
	IGamePropertyUseSink *          m_pGameTrumpetSink;             //�ص��ӿ�
	IClientUserItem  *              m_pIClientUserItem;             //�û��ӿ�

	//��������
public:
	//���캯��
	CDlgTrumpetItem(); 

	//��������
	virtual ~CDlgTrumpetItem();

	//�󶨺���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange* pDX);    

	//����ӿ�
public:
	//ѡ���¼�
	virtual VOID OnExpressionSelect(CExpression * pExpression, tagExpressionInfo * pExpressionInfo);

	//��������
public:
	//���ýӿ�
	bool SetGameTrumpetSink(IUnknownEx * pIUnknownEx);
	//���½���
	void UpdateControlSurface();
	//��ȡ����
	void GetTrumpetContent(LPTSTR pszTrumpetContent);
	//��ȡ��ɫ
	COLORREF GetTrumpetColor() { return m_crChatTX; };
	//��ʾ����
	void ShowTrumpetWindow(CWnd * pParentWnd,IClientUserItem  * pIClientUserItem);


	//��Ϣ����
protected:
	//��ʼ���
	virtual BOOL OnInitDialog();
	//��ɫ��ť
	afx_msg void OnBnClickedColorSet();
	//���鰴ť
	afx_msg void OnBnClickedExpression();
	//���Ȱ�ť
	afx_msg void OnBnClickedTrumpet();
	//���Ȱ�ť
	afx_msg void OnBnClickedTyphon();
	//ȷ����Ϣ
	afx_msg void OnBnClickedOk();
	//�ؼ���ɫ
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//�滭����
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif
