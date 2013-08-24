#ifndef _____UIText_H
#define _____UIText_H

#include "UIWidget.h"

namespace YouLe
{
	class UIText : public UIWidget
	{
	public:
		UIText();
		virtual ~UIText();

		// �����ؼ�
		virtual BOOL		Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight, 
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

		// �����ı�
		virtual	void		SetText(LPCTSTR lpszText);
		// ��ȡ�ı�
		virtual CString		GetText() const;

		// �����ʽ
		virtual void		SetTextFormat(UINT nFormat);
		// ��ȡ��ʽ
		virtual	UINT		GetTextFormat() const;

		// ������ɫ
		virtual void		SetColour(DWORD dwColour);
		// ��ȡ��ɫ
		virtual DWORD		GetColour() const;

		// �ؼ�����
		virtual	BOOL		Draw(CDC* pDC);
	protected:
		// �ı���ɫ
		DWORD				m_dwColour;
		// �ı�����
		CString				m_szText;
		// �ı�����
		UINT				m_uFormat;
	};
}

#endif