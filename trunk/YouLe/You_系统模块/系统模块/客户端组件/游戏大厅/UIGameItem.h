#ifndef _____UIGameItem_H
#define _____UIGameItem_H

#include "UIPngButton.h"

namespace YouLe
{
	// ��Ϸ�б���
	class UIGameItem : public UIWidget , public UIProcess
	{
	public:
		// ���캯��
		UIGameItem();
		// ��������
		virtual ~UIGameItem();
		// ������Ч
		virtual void		EnabledWidget(bool bEnabled);
		// ������Ϣ
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		// �����ؼ�
		virtual BOOL		Create(INT nID, INT nDestX, INT nDestY, 
			HINSTANCE hInstance, LPCTSTR lpszBackResouceName, LPCTSTR lpszBillResouceName, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		
		// ���ƿؼ�
		virtual BOOL		Draw(CDC* pDC);
	public:
		// ���ñ���ͼ
		virtual bool		SetBackPng(LPCTSTR pszFileName);
		// ���ñ���ͼ
		virtual bool		SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName);
		// ���ù��ͼ
		virtual bool		SetBillPng(LPCTSTR pszFileName);
		// ���ù��ͼ
		virtual bool		SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName);
		// ���뷿��
		virtual bool		OnClickedEnterRoom();

	protected:
		CPngImage			m_PngBack;
		CPngImage			m_PngBill;
		UIPngButton*		m_pRegular;
		UIPngButton*		m_pJoinBtn; 
		
	public:
		// ��Ϸ��Ϣ
		tagGameKind*		m_GameKind;	

	};

	// ��Ϸ��ͼ
	class UIGameView : public UIWidget,public UIProcess
	{
	public:
		// ���캯��
		UIGameView();
		// ��������
		virtual ~UIGameView();
		// ������Ϣ
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		// ������Ϸ��ͼ
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
	
		// ���ܺ���
	public:
		// ��������GameItem�Ƿ����
		void				EnabledAllGameItem(bool bEnabled);
		// ö��GameItem
		bool				EnumGameItem();
		// ��ʾ��ҳ
		void				ShowFirstPage();
		// ��Ӧ��һҳ
		void				OnClickLastPage();
		// ��Ӧ��һҳ
		void				OnClickNextPage();
		
	public:
		// ��Ϸҳ
		UIGameItem*			m_pGameItem[MAX_GICOL*MAX_GIROW];
		// ö������
		int					m_EnumIndex;
	};
}

#endif