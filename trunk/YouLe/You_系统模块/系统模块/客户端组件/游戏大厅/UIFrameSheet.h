#ifndef _____UIFrameSheet_H
#define _____UIFrameSheet_H

#include "UISheet.h"

namespace YouLe
{
	// UI ������
	class UIFrameSheet : public UISheet
	{
	public:
		// ���캯��
		UIFrameSheet();
		// ��������
		virtual ~UIFrameSheet();

		// ��������
		virtual BOOL			Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
	};
}

#endif