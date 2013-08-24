#ifndef _____UIEditBox_H
#define _____UIEditBox_H

#include "UIText.h"

namespace YouLe
{
	//////////////////////////////////////////////////////////////////////////
	// 
	//////////////////////////////////////////////////////////////////////////
	class UIEditBox : public UIText
	{
		enum{
			MOUSE_DOWN,
			MOUSE_MOVE,
			MOUSE_KEYS
		};
	public:
		UIEditBox();
		virtual ~UIEditBox();

		// 创建控件
		virtual BOOL		Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight, 
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

		// 控件绘制
		virtual BOOL		Draw(CDC* pDC);
		
		// 获取光标
		virtual CPoint		GetCursorPoint(CDC* pDC, INT nStart, INT nEnd);
		// 获取光标
		virtual INT			GetCursor(const CPoint& cPt);
		// 设置光标
		virtual void		SetCursor(const CPoint& cPt);
		// 选择文本
		virtual CString		GetSelectText(INT nStart, INT nEnd);
	public:
		// 键盘按下
		virtual BOOL		OnKeyDwon(UINT nChar, 
			UINT nRepCnt, UINT nFlags);
		// 键盘弹起
		virtual BOOL		OnKeyUp(UINT nChar, 
			UINT nRepCnt, UINT nFlags);
		// 字符输入
		virtual BOOL		OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	public:
		// 鼠标移动
		virtual BOOL		OnMouseMove(const CPoint& cPt);

	public:
		// 鼠标按下
		virtual	BOOL		OnLeftDown(const CPoint& cPt);
		// 鼠标弹起
		virtual BOOL		OnLeftUp(const CPoint& cPt);

	protected:
		// 记录鼠标
		CPoint				m_ptMouse[MOUSE_KEYS];
		// 是否按下
		BOOL				m_bPressd;
		// 光标位置
		INT					m_nStart;
		// 结束位置
		INT					m_nEnd;
		// 选择文本
		BOOL				m_bSelect;
		// 绘制光标
		BOOL				m_bCursor;
	};
}

#endif