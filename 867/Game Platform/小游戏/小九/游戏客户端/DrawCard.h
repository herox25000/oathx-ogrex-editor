#pragma once

#include "Stdafx.h"

#define	CARD_MASK_COLOR				0xF0								//花色掩码
#define	CARD_MASK_VALUE				0x0F								//数值掩码
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
	CArrayTemplate<BYTE,BYTE>		m_CardDataItem;						//扑克数据

	static bool						m_bLoad;							//加载标志
	static CSize					m_CardSize;							//扑克大小
	static CSkinImage				m_ImageCard;						//图片资源
	static CSkinImage				m_ImageCardHand;

	bool							m_bShow;   //显示牌


	bool							m_bIsTuiPaiOver;   // 推牌
	bool							m_bfirstCard;		// 是否是第一张发的牌

	bool							m_IsPreCard;

	bool							m_bShowCard;

	int m_nCardPosX;
	int m_nCardPosY;
	bool							m_bShowHand;  //是否显示手

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
