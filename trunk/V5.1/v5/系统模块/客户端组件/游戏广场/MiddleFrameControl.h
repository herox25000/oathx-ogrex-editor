#ifndef MIDDLE_FRAME_CONTROL_HEAD_FILE
#define MIDDLE_FRAME_CONTROL_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//�û���Ϣ
class CMiddleFrameControl
{
	//���Ʊ���
protected:
	bool						m_bAfficheTitle;			    //�����ʶ

	//�������
protected:
	CRect                       m_rcControl;					//�ؼ�����

	//��������
public:
	//���캯��
	CMiddleFrameControl();
	//��������
	virtual ~CMiddleFrameControl();

	//��Ϣ����
public:
	//���ñ�ʶ
	VOID SetAfficheTitleFlag(bool bAfficheTitle) { m_bAfficheTitle=bAfficheTitle; };
	//��ȡ����
	VOID GetControlRect(CRect & rcControl) { rcControl=m_rcControl; }
	//��������
	VOID SetControlRect(CRect rcControl) { m_rcControl=rcControl; }
	//��������
	VOID SetControlRect(INT nLeftPos,INT nTopPos,INT nRightPos,INT nBottomPos);
	//�滭����
	BOOL OnDrawFrameControl(CDC * pDC);
};

//////////////////////////////////////////////////////////////////////////////////

#endif