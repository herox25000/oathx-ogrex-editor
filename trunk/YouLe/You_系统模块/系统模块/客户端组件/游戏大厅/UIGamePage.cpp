#include "Stdafx.h"
#include "UIGamePage.h"

namespace YouLe
{
	static const INT idList[] = {
		1, 2, 3, 4
	};

	// ���캯��
	UIGamePage::UIGamePage()
		: m_pGameView(NULL)
	{

	}

	// ��������
	UIGamePage::~UIGamePage()
	{
		
	}

	// ���ڿؼ�
	BOOL	UIGamePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		m_pGameView = new UIGameView();
		m_pGameView->Create(0, CRect(GTP_OFFSETX, GTP_OFFSETY,GTP_WITH, GTP_HEIGHT),pAttach, NULL, this);

		//������Դ
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		// ����ҳ�水ť
		const TCHAR* chBtnImageResouceName[] = {
			PlazaViewImage.pszGameTabGame,
			PlazaViewImage.pszGameTabCard,
			PlazaViewImage.pszGameTabMahj,
			PlazaViewImage.pszGameTabLeis
		};

		for (int i=0; i<4; i++)
		{
			UIPngButton* pPngButton = new UIPngButton();
			pPngButton->Create(idList[i], i * 96, 0, m_pAttach, this,
				hInstance, chBtnImageResouceName[i], 3, this);
		}

		SetPage(idList[0]);

		// �������ذ�ť
		UIPngButton* pBtReturn = new UIPngButton();
		pBtReturn->Create(IDB_GPRETURN, rect.right - 320, 5, pAttach, this, hInstance, PlazaViewImage.pszBtReturn, 4, this);

		return TRUE;
	}

	// ����ҳ��
	void	UIGamePage::SetPage(INT nID)
	{
		for (int i=0; i<4; i++)
		{
			UIWidget* pWidget = Search(idList[i]);
			if (pWidget)
				pWidget->EnabledWidget(idList[i] == nID ? FALSE : TRUE);
		}
	}

	// ��������Ϣ
	BOOL	UIGamePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			INT nID = pWidget->GetID();
			if (nID == IDB_GPRETURN )
			{
				m_pGameView->ShowFirstPage();
			}
			else
			{
				if(nID == 1)
					m_pGameView->ShowFirstPage();
				else
					m_pGameView->ShowFirstPage(nID);
				SetPage(nID);
			}
		}

		return FALSE;
	}
}