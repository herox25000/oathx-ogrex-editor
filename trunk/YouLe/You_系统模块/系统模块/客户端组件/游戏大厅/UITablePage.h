#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ���ӹ���
	//////////////////////////////////////////////////////////////////////////
	class UITableItem : public UIWidget, public UIProcess
	{
	public:
		UITableItem(void);

		virtual ~UITableItem(void);

		// �����ؼ�
		virtual	BOOL		Create(INT nID, INT nDestX, INT nDestY,
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		// ����
		virtual BOOL		Draw(CDC* pDC);
	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	protected:
		CPngImage			m_PngBill;
		UIPngButton*		m_pJoinBtn; 
	};


	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ������ͼ����
	//////////////////////////////////////////////////////////////////////////
	class UITablePage : public UIWidget, public UIProcess
	{
	public:
		UITablePage(void);

		virtual ~UITablePage(void);

		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);
		
		// ����
		virtual BOOL		Draw(CDC* pDC);

	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	public:
		// 
		UITableItem*		m_pTableItem[MAX_GICOL*MAX_GIROW];
		// ���ذ�ť
		UIPngButton*		m_pBtBack;
		// ����
		CPngImage			m_TilteImage;
		// �������ƣ���Ϸ���֣�
		TCHAR				szKindName[KIND_LEN];
	};
}