#include "Stdafx.h"
#include "UIFrameSheet.h"
#include "UIGamePage.h"
#include "UIFramePage.h"
#include "UIFrameClose.h"

namespace YouLe
{

#define IDB_FRAME_CLOSE						65535
#define IDB_FRAME_MIN						65534
#define IDB_FRAME_SET						65533

#define IDP_FRAME_PAGE						55535
#define IDP_GAME_PAGE						55534
#define IDP_FRAME_CLOSE						55533

#define PFS_CAPTION_HEIGHT					40
#define PGP_OFFSETX							245
#define PGP_OFFSETY							206
#define PGP_ITEMWIDTH						176
#define PGP_ITEMHEIGHT						140


	// ϵͳ��ťID
	const static INT idFrameList[] = {
		IDB_FRAME_CLOSE, IDB_FRAME_MIN, IDB_FRAME_SET
	};

	// ���캯��
	UIFrameSheet::UIFrameSheet()
	{

	}
	
	// ��������
	UIFrameSheet::~UIFrameSheet()
	{

	}

	// ��������
	UIFrameSheet::Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;
		
		//������Դ
		tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
		ASSERT(hInstance != NULL);

		// ��ť��Դ
		const TCHAR* chSystemResouceName[] = {
			PlazaViewImage.pszBtClose,
			PlazaViewImage.pszBtMin,
			PlazaViewImage.pszBtFrameSet,
		};

		for (int i=0; i<3; i++)
		{
			UIPngButton* pSystemButton = new UIPngButton();
			pSystemButton->Create(idFrameList[i], rect.right - (i + 1) * 40, 3, pAttach, this, hInstance, chSystemResouceName[i], 4, this);
		}

		// �������ҳ
		UIFramePage* pFramePage = new UIFramePage();
		pFramePage->Create(IDP_FRAME_PAGE, 
			CRect(rect.left, rect.top + PFS_CAPTION_HEIGHT, rect.right, rect.top), pAttach, pProcess, this);

		// ������Ϸҳ
		UIGamePage* pGamePage	= new UIGamePage();
		pGamePage->Create(IDP_GAME_PAGE, 
			CRect(PGP_OFFSETX, PGP_OFFSETY, PGP_OFFSETX+PGP_ITEMWIDTH*3, PGP_OFFSETY+PGP_ITEMHEIGHT*3), pAttach, pProcess, this);

		// �����˳���
		UIFrameClose* pClose	= new UIFrameClose();
		INT x = rect.right	/ 2 - 180;
		INT y = rect.bottom / 2 - 109;
		pClose->Create(IDP_FRAME_CLOSE, CRect(x, y, x + 360, y+218), pAttach, this, this);
		pClose->VisibleWidget(FALSE);

		return TRUE;
	}

	// ��ť����
	BOOL UIFrameSheet::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		switch(pWidget->GetID())
		{
		case IDB_FRAME_SET:
			{
				SendMessage(WM_COMMAND, WM_SHOW_LOBBYSET, NULL);
			}
			break;
		case IDB_FRAME_MIN:
			{
				if (m_pAttach)
					m_pAttach->ShowWindow(SW_MINIMIZE);
			}
			break;
		case IDB_FRAME_CLOSE:
			{
				UIWidget* pClose = Search(IDP_FRAME_CLOSE);
				if (pClose)
					pClose->VisibleWidget(TRUE);
			}
			break;
		}

		return TRUE;
	}

}