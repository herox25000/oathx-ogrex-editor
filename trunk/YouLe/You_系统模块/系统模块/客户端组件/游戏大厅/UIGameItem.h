#ifndef _____UIGameItem_H
#define _____UIGameItem_H

#include "UIPngButton.h"

namespace YouLe
{
	// ��Ϸ�б���
	class UIGameItem : public UIWidget
	{
	public:
		// ���캯��
		UIGameItem();
		// ��������
		virtual ~UIGameItem();
		
		// �����ؼ�
		virtual BOOL		Create(INT nID, INT nDestX, INT nDestY, 
			HINSTANCE hInstance, LPCTSTR lpszBackResouceName, LPCTSTR lpszBillResouceName, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		
		// ���ƿؼ�
		virtual BOOL		Draw(CDC* pDC);
	public:
		// ���ñ���ͼ
		virtual void		SetBackPng(HINSTANCE hInstance, LPCTSTR lpszBackResouceName);
		// ���ù��ͼ
		virtual void		SetBillPng(HINSTANCE hInstance, LPCTSTR lpszBillResouceName);
	protected:
		CPngImage			m_PngBack;
		CPngImage			m_PngBill;
	};

	// ��Ϸ��ͼ
	class UIGameView : public UIWidget
	{
	public:
		// ���캯��
		UIGameView();
		// ��������
		virtual ~UIGameView();
		
		// ������Ϸ��ͼ
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
	};
}

#endif