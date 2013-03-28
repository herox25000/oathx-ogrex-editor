#ifndef GOLD_CONTROL_HEAD_FILE
#define GOLD_CONTROL_HEAD_FILE

#pragma once

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////

//��ҿ���
class CGoldControl : public CWnd
{
	//��������
protected:
	__int64								m_lAllGold;						//�ܱ���Ŀ
	__int64								m_lGoldCount[3];				//�����Ŀ
	__int64								m_lMaxGold;						//�����
	__int64								m_lGoldCell[7];					//��Ԫ���
	__int64								m_lMinGold;						//���ٽ��
	CPoint								m_BasicPoint;					//����λ��

	//λ�ñ���
protected:
	int									m_nWidth;						//�ؼ����
	int									m_nCellCount;					//��Ԫ��Ŀ
	int									m_AppendWidth;					//���ӿ��

	//��Դ����
protected:
	CSkinImage							m_ImageBack;					//������Դ
	CSkinImage							m_ImageMoney;					//�����Դ
	CSkinImage							m_ImageNumber;					//������Դ

	//��������
public:
	//���캯��
	CGoldControl();
	//��������
	virtual ~CGoldControl();

	//���ܺ���
public:
	//��ȡ���
	__int64 GetGold(){return m_lAllGold;};
	//���ó���
	void SetGoldCount(__int64 lCellSocre);
	//���ý��
	void SetGold(__int64 lGold);
	//������ע
	void SetMaxGold(__int64 lMaxGold);
	//���Ƶ�Ԫ
	void SetMinGold(__int64 lMinGold);
	//����λ��
	void SetBasicPoint(int nXPos, int nYPos);

	//�ڲ�����
private:
	//�����ؼ�
	void RectifyControl();

	//��Ϣӳ��
protected:
	//�ػ�����
	afx_msg void OnPaint();
	//���������Ϣ
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//���ù��
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	DECLARE_MESSAGE_MAP()
};


//////////////////////////////////////////////////////////////////////////

#endif