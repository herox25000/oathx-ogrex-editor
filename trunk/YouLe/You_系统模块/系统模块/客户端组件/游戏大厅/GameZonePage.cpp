#include "Stdafx.h"
#include "GameZonePage.h"

#define GTP_OFFSETX			0
#define GTP_OFFSETY			40
#define GTP_WINDOWX			176
#define GTP_WINDOWY			140
#define GTP_ITEMCOL			3
#define GTP_ITEMROW			3

// ���캯��
CGameZonePage::CGameZonePage()
{

}

// ��������
CGameZonePage::~CGameZonePage()
{

}

// ������Ϸҳ��
BOOL CGameZonePage::Create(INT nID, const RECT& rect, CWnd* pParent)
{
	BOOL bResult = CTabPage::Create(nID, rect, pParent);
	ASSERT(bResult == TRUE);
	
	INT nLeft	= rect.left + GTP_OFFSETX;
	int nTop	= rect.top + GTP_OFFSETY;

	m_GamePage.Create(GTP_ITEMCOL, GTP_ITEMROW, NULL, 
		CRect(nLeft, nTop, nLeft + GTP_WINDOWX * GTP_ITEMCOL, nTop + GTP_WINDOWY * GTP_ITEMROW), pParent, 0);

	// ����ҳ�水ť
	const TCHAR* chBtnImageResouceName[] = {
		TEXT("GAMETAB_GAME"),
		TEXT("GAMETAB_CARD"),
		TEXT("GAMETAB_MAHJ"),
		TEXT("GAMETAB_LEIS")
	};

	for (int i=0; i<4; i++)
	{
		m_GameBnts[i].CreateButton(pParent, 
			chBtnImageResouceName[i], _T("PNG"), rect.left + i * 100, rect.top, 0, 3);
	}

	return bResult;
}

// ����ˢ��
void CGameZonePage::EraseBkgnd(CDC* pDC)
{
	ASSERT(pDC != NULL);

	for (int i=0; i<4; i++)
	{
		m_GameBnts[i].SetBkGnd(pDC);
	}
}

// ��ʾ״̬
void CGameZonePage::ShowWindow(int nCmdShow)
{
	for (int i=0; i<4; i++)
	{
		m_GameBnts[i].ShowWindow(nCmdShow);
	}

	m_GamePage.ShowWindow(nCmdShow);
}
