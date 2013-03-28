#ifndef GOLD_VIEW_HEAD_FILE
#define GOLD_VIEW_HEAD_FILE

#pragma once

#include "Stdafx.h"
//�궨��
#define GOLD_IMAGE_WIDTH		20										//�����
#define GOLD_IMAGE_HEIGHT		19										//�����

//////////////////////////////////////////////////////////////////////////

//������ͼ��
class CGoldView
{
	//��������
public:
	__int64								m_lGold;						//������Ŀ
	__int64								m_lMaxLayer;					//������
	__int64								m_lGoldCount[7];	 			//������Ŀ

	//��������
protected:
	static bool							m_bInit;						//��ʼ��־
	static CSkinImage					m_ImageGold;					//����ͼƬ
	CSkinImage							m_ImageNumber;					//����ͼƬ

	//��������
public:
	//���캯��
	CGoldView();
	//��������
	virtual ~CGoldView();

	//���ܺ���
public:
	//���ó���
	void SetGold(__int64 lGold);
	//��ȡ����
	__int64 GetGold() { return m_lGold; };
	//���ò���
	void SetMaxGoldLayer(__int64 lMaxLayer);
	//��ȡ����
	__int64 GetMaxGoldLayer(){return m_lMaxLayer;}
	//�滭����
	void DrawGoldView(CDC * pDC, int nXPos, int nYPos, bool bCount,bool bCenter=false,BYTE bDUser=0);
	//���Ա��ַ�
	LPCTSTR GetGlodString(__int64 lGold, TCHAR szString[]);

	//�ڲ�����
private:
	//���������
	void RectifyGoldLayer();
};

//////////////////////////////////////////////////////////////////////////

#endif