#ifndef GAME_FRAME_USER_VIEW_HEAD_FILE
#define GAME_FRAME_USER_VIEW_HEAD_FILE

#pragma once

#include "GameFrameHead.h"
#include "GameFramePublicize.h"

//////////////////////////////////////////////////////////////////////////////////

//�û���Ϣ
class GAME_FRAME_CLASS CGameFrameUserView : public CWnd
{
	//�ӿڱ���
protected:
	IClientKernel *					m_pIClientKernel;					//�ں˽ӿ�
	IClientUserItem *				m_pICurrentUserItem;				//��ǰ�û�

	//�ؼ�����
protected:
	CGameFramePublicize				m_GameFramePublicize;				//���ؼ�
	CWnd *							m_pCustomPanel;						//�Զ����

	//��������
public:
	//���캯��
	CGameFrameUserView();
	//��������
	virtual ~CGameFrameUserView();

	//���ܺ���
public:
	//���ù��
	VOID SetGameBillInfo(WORD wKindID, WORD wServerID);
	//�����û�
	VOID SetUserViewInfo(IClientUserItem * pIClientUserItem);
	//�Զ����
	VOID SetCustomPanel(CWnd * pCustomPanel);

	//���溯��
private:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);

	//��ť��Ϣ
protected:
	//���ƶһ�
	VOID OnBnClickedUserMedal();
	//�����һ�
	VOID OnBnClickedLoveLiness();

	//��Ϣӳ��
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//������Ϣ
	INT OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif