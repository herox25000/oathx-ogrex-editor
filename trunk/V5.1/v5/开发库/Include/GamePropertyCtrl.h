#ifndef GAME_PROPERTY_CTRL_HEAD_FILE
#define GAME_PROPERTY_CTRL_HEAD_FILE

#pragma once

#include "GamePropertyHead.h"
#include "GamePropertyItem.h"

//////////////////////////////////////////////////////////////////////////////////

//��Ϸ����
class GAME_PROPERTY_CLASS CGamePropertyCtrl : public CWnd
{
	//״̬����
protected:
	bool							m_bHovering;						//������־
	WORD							m_wDownItem;						//�������
	WORD							m_wHoverItem;						//��������

	//���ñ���
protected:
	INT                             m_nItemExcursion;                   //����ƫ��
	CSize							m_SizeImageItem;					//����ͼƬ
	tagPropertyResource				m_PropertyResource;					//��Դ����

	//��ť����
protected:
	CSkinButton                     m_btLeftMove;                      //���ư�ť
	CSkinButton                     m_btRightMove;                     //���ư�ť

	//��������
protected:
	BYTE                            m_cbStartIndex;                     //��ʼ����
	BYTE							m_cbPropertyCount;					//������Ŀ
	CGamePropertyItem *             m_pCurrPropertyItem;                //��ǰ����
	CGamePropertyItem *				m_pGamePropertyItem[MAX_PROPERTY];	//��������

	//�ӿڱ���
protected:
	IGamePropertySink *				m_pIGamePropertySink;				//�ص��ӿ�

	//��������
public:
	//���캯��
	CGamePropertyCtrl();
	//��������
	virtual ~CGamePropertyCtrl();

	//���溯��
private:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);

	//���ú���
public:
	//���ýӿ�
	bool SetGamePropertySink(IUnknownEx * pIUnknownEx);
	//������Դ
	bool SetPropertyResource(tagPropertyResource & PropertyResource);
	//���õ���
	bool SetGamePropertyInfo(tagPropertyInfo PropertyInfo[], BYTE cbPropertyCount, WORD wIssueArea);

	//�¼�����
public:
	//�ı��¼�
	VOID OnSelectedUserItemChange(IClientUserItem * pIClintUserItem);

	//�ڲ�����
protected:
	//����ж�
	WORD SwitchItemFromPoint(CPoint MousePoint);

	//��Ϣӳ��
protected:
	//��������
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//����ƶ�
	VOID OnMouseMove(UINT nFlags, CPoint MousePoint);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint MousePoint);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint MousePoint);
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	//�����Ϣ
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);
	//���ư�ť
	VOID OnBtnLeftMoveClicked();
	//���ư�ť
	VOID OnBtnRightMoveClicked();

	DECLARE_MESSAGE_MAP()	
};

//////////////////////////////////////////////////////////////////////////////////

#endif