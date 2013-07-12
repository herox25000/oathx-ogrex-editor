#ifndef WND_GAME_TYPE_CTRL_HEAD_FILE
#define WND_GAME_TYPE_CTRL_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerListData.h"

//////////////////////////////////////////////////////////////////////////////////

//��Ϸ����
class CWndGameTypeCtrl : public CWnd
{
	//�����Ϣ
protected:
	bool							m_bHovering;						//������־
	WORD							m_wItemDown;						//��������
	WORD							m_wItemHover;						//��������
	WORD							m_wItemActive;						//��������

	//������Ϣ
protected:
	CSize							m_SizeButton;						//��ť��С
	CGameTypeItemArray				m_GameTypeItemArray;				//��������

	//��������
public:
	//���캯��
	CWndGameTypeCtrl();
	//��������
	virtual ~CWndGameTypeCtrl();

	//���ܺ���
public:
	//��ȡ��С
	VOID GetControlSize(CSize & ResultSize);
	//��������
	VOID InsertGameType(CGameTypeItem * pGameTypeItem);

	//�ڲ�����
private:
	//��������
	WORD GetTypeItemIndex(WORD wTypeID);
	//��������
	WORD GetTypeItemIndex(CPoint MousePoint);

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//����ƶ�
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif