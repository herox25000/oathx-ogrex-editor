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

		// �����ؼ�
		virtual BOOL		Create(INT nID, const RECT& rect, LPCTSTR lpszFontName, INT nFontHeight, 
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

		// �ؼ�����
		virtual BOOL		Draw(CDC* pDC);
		
		// ��ȡ���
		virtual CPoint		GetCursorPoint(CDC* pDC, INT nStart, INT nEnd);
		// ��ȡ���
		virtual INT			GetCursor(const CPoint& cPt);
		// ���ù��
		virtual void		SetCursor(const CPoint& cPt);
		// ѡ���ı�
		virtual CString		GetSelectText(INT nStart, INT nEnd);
	public:
		// ���̰���
		virtual BOOL		OnKeyDwon(UINT nChar, 
			UINT nRepCnt, UINT nFlags);
		// ���̵���
		virtual BOOL		OnKeyUp(UINT nChar, 
			UINT nRepCnt, UINT nFlags);
		// �ַ�����
		virtual BOOL		OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	public:
		// ����ƶ�
		virtual BOOL		OnMouseMove(const CPoint& cPt);

	public:
		// ��갴��
		virtual	BOOL		OnLeftDown(const CPoint& cPt);
		// ��굯��
		virtual BOOL		OnLeftUp(const CPoint& cPt);

	protected:
		// ��¼���
		CPoint				m_ptMouse[MOUSE_KEYS];
		// �Ƿ���
		BOOL				m_bPressd;
		// ���λ��
		INT					m_nStart;
		// ����λ��
		INT					m_nEnd;
		// ѡ���ı�
		BOOL				m_bSelect;
		// ���ƹ��
		BOOL				m_bCursor;
	};
}

#endif