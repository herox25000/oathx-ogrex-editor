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

		// 创建控件
		virtual BOOL		Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight, 
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

		// 设置文本
		virtual	void		SetText(LPCTSTR lpszText);
		// 获取文本
		virtual CString		GetText() const;

		// 对齐格式
		virtual void		SetTextFormat(UINT nFormat);
		// 获取格式
		virtual	UINT		GetTextFormat() const;

		// 设置颜色
		virtual void		SetColour(DWORD dwColour);
		// 获取颜色
		virtual DWORD		GetColour() const;

		// 控件绘制
		virtual	BOOL		Draw(CDC* pDC);
	protected:
		// 文本颜色
		DWORD				m_dwColour;
		// 文本内容
		CString				m_szText;
		// 文本对齐
		UINT				m_uFormat;
	};
}

#endif