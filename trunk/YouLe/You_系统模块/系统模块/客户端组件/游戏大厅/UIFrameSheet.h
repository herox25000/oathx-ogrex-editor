#ifndef _____UIFrameSheet_H
#define _____UIFrameSheet_H

#include "UIGamePage.h"

namespace YouLe
{
	// UI ������
	class UIFrameSheet : public UIWidget
	{
	public:
		// ���캯��
		UIFrameSheet();
		// ��������
		virtual ~UIFrameSheet();

		// ��������
		virtual BOOL			Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

	public:
		// ע������ƶ�
		virtual BOOL			InjectMouseMove(const CPoint& cPt);
		// ע����갴��
		virtual BOOL			InjectLeftDown(const CPoint& cPt);
		// ע����굯��
		virtual BOOL			InjectLeftUp(const CPoint& cPt);
	};
}

#endif