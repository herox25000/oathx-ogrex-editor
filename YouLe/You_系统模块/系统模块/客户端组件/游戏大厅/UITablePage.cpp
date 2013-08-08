#include "StdAfx.h"
#include "UITablepage.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子构造
	//////////////////////////////////////////////////////////////////////////
	UITableItem::UITableItem(void)
	{

	}

	UITableItem::~UITableItem(void)
	{

	}

	// 创建控件
	BOOL	UITableItem::Create(INT nID, INT nDestX, INT nDestY,
								CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		//加载资源
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		m_PngBill.LoadImage(hInstance == NULL ? AfxGetInstanceHandle() : hInstance, 
			PlazaViewImage.pszGameRoomBill);

		CRect rect;
		rect.SetRect(nDestX, nDestY,
			nDestX + m_PngBill.GetWidth(), nDestY + m_PngBill.GetHeight());

		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		m_pJoinBtn = new UIPngButton();
		m_pJoinBtn->Create(100, 7, 106, m_pAttach, this,
			hInstance, PlazaViewImage.pszGameRoomJoin, 4, this);

		return TRUE;
	}

	// 绘制控件
	BOOL	UITableItem::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_PngBill.DrawImage(pDC, cPt.x, cPt.y);

		if(m_pTableInfo)
		{
			TCHAR	szTempStr[32];
			//第几桌
			sprintf(szTempStr,_T("%d 号桌子"),m_pTableInfo->wTableID);
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x+10,cPt.y+5,cPt.x+100,cPt.y+30),DT_CENTER);
			//状态
			if(m_pTableInfo->bPlayStatus == true)
				sprintf(szTempStr,_T("正在游戏"));
			else
				sprintf(szTempStr,_T("空桌"));
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x+10,cPt.y+35,cPt.x+100,cPt.y+20),DT_CENTER);
			//人数
			sprintf(szTempStr,_T("游戏人数：%d/%d"),m_pTableInfo->lPlayerCount,m_pTableInfo->wChairCount);
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x+10,cPt.y+55,cPt.x+100,cPt.y+20),DT_CENTER);
		}
		return TRUE;
	}

	// 响应页控件
	BOOL	UITableItem::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if(pWidget)
		{
			switch(pWidget->GetID())
			{
			case 100:	// 加入按钮
				{
					::AfxMessageBox("准备确定游戏！！");
					return TRUE;
				}
			}
		}
		return TRUE;
	}



	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子视图构造
	//////////////////////////////////////////////////////////////////////////
	UITablePage::UITablePage(void)
	{

	}

	UITablePage::~UITablePage(void)
	{
	}

	// 创建控件
	BOOL	UITablePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//加载资源
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		// 标题图片
		m_TilteImage.LoadImage(hInstance,PlazaViewImage.pszTilteImage);

		// 创建返回按钮
		UIPngButton* pBtReturn = new UIPngButton();
		pBtReturn->Create(IDB_GPRETURN, rect.right - 320, 5, pAttach, this, hInstance, PlazaViewImage.pszBtReturn, 4, this);

		// 桌子列表
		for (int c=0; c<MAX_GICOL; c++)
		{
			for (int r=0; r<MAX_GIROW; r++)
			{
				int index = c*MAX_GIROW + r;
				m_pTableItem[index] = new UITableItem();
				m_pTableItem[index] ->Create(c * MAX_GIROW + r , r * 180, 40+c * 145,pAttach, pProcess, this);
				m_pTableItem[index] ->VisibleWidget(false);
			}
		}

		CRect rc;
		GetClientRect(&rc);
		// 绘制翻页按钮，上一页
		UIPngButton* pBtLast = new UIPngButton();
		pBtLast->Create(100, rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);

		// 绘制翻页按钮，下一页
		UIPngButton* pBtNext = new UIPngButton();
		pBtNext->Create(101, rc.right/2 ,		rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLNext, 4, this);
		return TRUE;
	}

	// 绘制
	BOOL	UITablePage::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_TilteImage.DrawImage(pDC, cPt.x, cPt.y);

		if(m_pListServer)
		{
			TCHAR	szTempStr[32];
			CopyMemory(szTempStr,m_pListServer->m_GameServer.szServerName,sizeof(szTempStr));
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x,cPt.y+5,cPt.x+100,cPt.y+30),DT_CENTER);
		}

		return UIWidget::Draw(pDC);
	}

	// 响应页控件
	BOOL	UITablePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			switch(pWidget->GetID())
			{
			case IDB_GPRETURN:	// 返回按钮
				{
					g_UIPageManager.m_pTablePage->VisibleWidget(false);
					g_UIPageManager.m_pRoomPage->VisibleWidget(true);
					return TRUE;
				}
			case 100:	// 上一页
				{
					OnClickLastPage();
					return TRUE;
				}
			case 101:	// 下一页
				{
					OnClickNextPage();
					return TRUE;
				}
			}
		}
		return TRUE;
	}

	// 响应上一页
	void	UITablePage::OnClickLastPage()
	{
		m_EnumIndex -= MAX_GICOL*MAX_GIROW;
		if(m_EnumIndex < 0)
		{
			m_EnumIndex = 0;
			return;
		}
		EnumTableItem();
	}

	// 响应下一页
	void	UITablePage::OnClickNextPage()
	{
		m_EnumIndex += MAX_GICOL*MAX_GIROW;
		EnumTableItem();
	}

	// 枚举GameItem
	bool	UITablePage::EnumTableItem()
	{
		TableInfo*  pTableInfo= NULL;
		int			TableIndex = 0;
		for (int nIndex = m_EnumIndex; nIndex < (m_EnumIndex+MAX_GICOL*MAX_GIROW); nIndex++)
		{
			pTableInfo = g_GlobalUnits.m_GameRoomManager.EnumTableItem(nIndex);
			if (pTableInfo == NULL) 
				return false;
			UITableItem* pTableItem = m_pTableItem[TableIndex];
			if(pTableItem)
			{
				pTableItem->VisibleWidget(true);
				pTableItem->m_pTableInfo = pTableInfo;
			}
			TableIndex++;
		}
		return true;
	}

	// 显示首页
	void	UITablePage::ShowFirstPage()
	{
		m_EnumIndex = 0;
		EnumTableItem();
	}

}