
#include "StdAfx.h"
#include "Resource.h"
#include "Drawcard.h"
#include "GameClientView.h"

bool					CDrawCard::m_bLoad=false;					//加载标志
CSize					CDrawCard::m_CardSize;						//扑克大小
CSkinImage				CDrawCard::m_ImageCard;						//图片资源
CSkinImage				CDrawCard::m_ImageCardHand;						//图片资源

CDrawCard::CDrawCard()
{
	m_bfirstCard = false;
}
void CDrawCard::Init(CWnd *pWnd,int posX,int posY)
{
	//资源变量
	if (m_bLoad==false)
	{
		//加载资源
		m_bLoad=true;
		m_ImageCard.SetLoadInfo(IDB_GAME_CARD,AfxGetInstanceHandle());
		m_ImageCardHand.SetLoadInfo(IDB_CARDHAND,AfxGetInstanceHandle());

		//获取大小
		CImageHandle CardImageHandle(&m_ImageCard);
		m_CardSize.cx=m_ImageCard.GetWidth()/13;
		m_CardSize.cy=m_ImageCard.GetHeight()/5;	
	}
	m_dwCardHSpace=17;
	m_pWnd=pWnd;
	m_nCardPosX=posX;
	m_nCardPosY=posY;

}

CDrawCard::CDrawCard(CWnd *pWnd,int posX,int posY)
{
	m_OffsetX=0;
	m_OffsetY=0;
	m_SecondCardRect.SetRect(0,0,0,0);
	m_bShow=false;
	m_bPushDown=false;
	m_cpPushDown=0;
	m_bIsTuiPaiOver=false;
	m_IsPreCard=false;
	m_bYouTui=false;
	m_bShowCard=false;
	m_bShowHand=false;
	Init(pWnd,posX,posY);
}
void CDrawCard::Clear()
{
	m_CardDataItem.RemoveAll();
}
CDrawCard::~CDrawCard(void)
{
}
void CDrawCard::Draw(CDC *pDC)
{
	CGameClientView *pWnd=((CGameClientView*)m_pWnd);
	if(m_bShow)
	{
		//加载位图
		CImageHandle HandleCard(&m_ImageCard);
		CImageHandle CardHandImage(&m_ImageCardHand);
		//绘画扑克
		DWORD dwXImagePos,dwYImagePos;
		DWORD dwXScreenPos,dwYScreenPos;
		for (INT i=0;i<m_CardDataItem.GetCount();i++)
		{
			//获取扑克
			BYTE cbCardItem=0x00;
			cbCardItem=m_CardDataItem[i];
			//图片位置
			if (cbCardItem!=0)
			{
				if(m_bYouTui && i==0)
				{
					dwXImagePos=((cbCardItem&CARD_MASK_VALUE)-1)*m_CardSize.cx;
					dwYImagePos=((cbCardItem&CARD_MASK_COLOR)>>4)*m_CardSize.cy;
				}
				else if(i==0 && m_IsPreCard)
				{
					dwXImagePos=((cbCardItem&CARD_MASK_VALUE)-1)*m_CardSize.cx;
					dwYImagePos=((cbCardItem&CARD_MASK_COLOR)>>4)*m_CardSize.cy;
				}
				else if(i==0)
				{
					dwXImagePos=m_CardSize.cx*5;
					dwYImagePos=m_CardSize.cy*4;
				}
				else 
				{
					dwXImagePos=((cbCardItem&CARD_MASK_VALUE)-1)*m_CardSize.cx;
					dwYImagePos=((cbCardItem&CARD_MASK_COLOR)>>4)*m_CardSize.cy;
				}
				
			}
			else
			{
				dwXImagePos=m_CardSize.cx*5;
				dwYImagePos=m_CardSize.cy*4;
			}

			if(i==1)
			{
				if(m_bIsTuiPaiOver && m_bShowHand)
				{
					dwYScreenPos=m_OffsetY;
					dwXScreenPos=m_OffsetX;
				}
				else
				{
					dwYScreenPos=m_OffsetY;
					dwXScreenPos=m_dwCardHSpace*i+m_OffsetX;
				}
				
			}
			else
			{
				dwYScreenPos=0;
				dwXScreenPos=m_dwCardHSpace*i;
			}

			m_ImageCard.AlphaDrawImage(pDC,
				dwXScreenPos+m_nCardPosX,
				dwYScreenPos+m_nCardPosY,
				m_CardSize.cx,
				m_CardSize.cy,
				dwXImagePos,
				dwYImagePos,
				0xFF00FF);
		}
		if(!pWnd->m_bAutoCard && m_bYouTui && m_bShowCard && m_bShowHand)
			m_ImageCardHand.AlphaDrawImage( pDC, m_nCardPosX-32, m_nCardPosY-10,RGB(255, 0, 255) );
		else if(m_bYouTui && !m_bIsTuiPaiOver && m_bShowHand)
			m_ImageCardHand.AlphaDrawImage( pDC, m_nCardPosX-32, m_nCardPosY-10,RGB(255, 0, 255) );
	}
}

void CDrawCard::GameEnd()
{
}

void CDrawCard::TuiPai()
{
	CGameClientView *pWnd=((CGameClientView*)m_pWnd);
	if(!m_bIsTuiPaiOver)
	{
		if(m_bYouTui && pWnd->m_bAutoCard)
			m_OffsetX+=2;
		else
			m_OffsetX-=2;
		if(m_OffsetX<=-17 && m_bYouTui==false)
		{
			if(!pWnd->m_bAutoCard)
			{
				m_bIsTuiPaiOver=true;
				m_bShowCard=true;
			
			}
			m_bYouTui=true;
			m_bShowHand=true;
			m_OffsetX=0;
			m_OffsetY=0;	
			
		}
		if(m_bYouTui && pWnd->m_bAutoCard)
		{
			if(m_OffsetX>30)
			{
				m_OffsetX=17;
				m_OffsetY=0;
				m_bIsTuiPaiOver=true;
			}
		}
		

	}
}
void CDrawCard::SetTuiPai(bool bTuiPai)
{
	m_bIsTuiPaiOver=bTuiPai;
	m_bYouTui=false;
	m_bShowCard=false;
}

void CDrawCard::SetPreCard(bool bPreCard)
{
	m_IsPreCard=bPreCard;
}
DWORD CDrawCard::GetCardCount()
{
	return (DWORD)m_CardDataItem.GetCount();
}
DWORD CDrawCard::SetCardData(const BYTE bCardData[], DWORD dwCardCount)
{
	//设置扑克
	m_OffsetX=0;
	m_OffsetY=0;
	m_CardDataItem.SetSize(dwCardCount);
	for (DWORD i=0;i<dwCardCount;i++)
		m_CardDataItem[i]=bCardData[i];
	m_bIsTuiPaiOver=false;
	m_bShowCard=false;
	if(m_pWnd->GetSafeHwnd())
		m_pWnd->Invalidate(true);
	if(dwCardCount==2)
		m_SecondCardRect.SetRect(m_nCardPosX+m_dwCardHSpace,m_nCardPosY,m_nCardPosX+m_dwCardHSpace+m_CardSize.cx,m_nCardPosY+m_CardSize.cy);
	return dwCardCount;
}
void CDrawCard::ShowCard(bool bShow)
{
	m_bShow=bShow;
}


void CDrawCard::OnLButtonDown(CPoint point)
{
	m_cpPushDown=point;
	m_bPushDown=true;
}
void CDrawCard::OnLButtonUp(CPoint point)
{
	if(m_bPushDown)
	{
		m_bPushDown=false;
		if(m_CardDataItem.GetCount()==2)
		{
			m_SecondCardRect.SetRect(m_nCardPosX+m_dwCardHSpace,m_nCardPosY,m_nCardPosX+m_dwCardHSpace+m_CardSize.cx,m_nCardPosY+m_CardSize.cy);
			m_OffsetX=0;
			m_OffsetY=0;
		}
		
	}
}
void CDrawCard::OnMouseMove(CPoint point)
{
	if(m_bPushDown)
	{
		CPoint pt=point-m_cpPushDown;
		m_OffsetX=pt.x;
		m_OffsetY=pt.y;
		if(m_CardDataItem.GetCount()==2)
		{
			
			m_SecondCardRect.SetRect(m_nCardPosX+m_dwCardHSpace+m_OffsetX,m_nCardPosY+m_OffsetY,m_nCardPosX+m_dwCardHSpace+m_CardSize.cx+m_OffsetX,m_nCardPosY+m_CardSize.cy+m_OffsetY);

		}
		if(!m_bShowHand)
		{
			m_bPushDown=false;
			if(m_CardDataItem.GetCount()==2)
			{
				m_SecondCardRect.SetRect(m_nCardPosX+m_dwCardHSpace,m_nCardPosY,m_nCardPosX+m_dwCardHSpace+m_CardSize.cx,m_nCardPosY+m_CardSize.cy);
				m_OffsetX=0;
				m_OffsetY=0;
			}
		}
	}
}
bool CDrawCard::PtInSecondCardRect(CPoint pt)
{
	return m_SecondCardRect.PtInRect(pt)!=0;
}

void CDrawCard::IsFirstCard(bool bFirst)
{
	m_bfirstCard=bFirst;
}
