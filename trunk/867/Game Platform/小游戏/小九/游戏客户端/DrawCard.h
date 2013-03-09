#pragma once

#include "Stdafx.h"

#define	CARD_MASK_COLOR				0xF0								//��ɫ����
#define	CARD_MASK_VALUE				0x0F								//��ֵ����
class CDrawCard
{
public:
	CDrawCard(CWnd *pWnd,int posX,int posY);
	~CDrawCard(void);

	void Draw(CDC *pDC);

	CDrawCard();
	void Init(CWnd *pWnd,int posX,int posY);

	void Clear();


	DWORD GetCardCount();
	DWORD SetCardData(const BYTE bCardData[], DWORD dwCardCount);
	
	void ShowCard(bool);

	void OnLButtonDown(CPoint point);
	void OnLButtonUp(CPoint point);
	void OnMouseMove(CPoint point);
	bool GetShowState(){return m_bShow;};

	bool PtInSecondCardRect(CPoint pt);


	void SetTuiPai(bool bTuiPai);
	bool GetIsTuiPai(){return m_bIsTuiPaiOver;};
	void TuiPai();
	void SetPreCard(bool bPreCard);

	void GameEnd();
	void SetShowHandFalse(){
		m_bShowHand=false;m_OffsetX=0;
		m_OffsetY=0;};

	bool GetShowHand(){return m_bShowHand;};
	void IsFirstCard(bool bFirst);
	
protected:
	CArrayTemplate<BYTE,BYTE>		m_CardDataItem;						//�˿�����

	static bool						m_bLoad;							//���ر�־
	static CSize					m_CardSize;							//�˿˴�С
	static CSkinImage				m_ImageCard;						//ͼƬ��Դ
	static CSkinImage				m_ImageCardHand;

	bool							m_bShow;   //��ʾ��


	bool							m_bIsTuiPaiOver;   // ����
	bool							m_bfirstCard;		// �Ƿ��ǵ�һ�ŷ�����

	bool							m_IsPreCard;

	bool							m_bShowCard;

	int m_nCardPosX;
	int m_nCardPosY;
	bool							m_bShowHand;  //�Ƿ���ʾ��

//	CRect							m_CardRect;
	CRect							m_SecondCardRect;
	DWORD							m_dwCardHSpace;		
	CWnd							*m_pWnd;

	int 							m_OffsetX;
	int								m_OffsetY;

	bool							m_bPushDown;
	CPoint							m_cpPushDown;
	bool							m_bYouTui;
};
