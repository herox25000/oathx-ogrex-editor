#ifndef _____UIFrameSheet_H
#define _____UIFrameSheet_H

#include "UISheet.h"


namespace YouLe
{
	// UI ������
	class UIFrameSheet : public UISheet, public UIProcess
	{
	public:
		// ���캯��
		UIFrameSheet();
		// ��������
		virtual ~UIFrameSheet();

		// ��������
		virtual BOOL			Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

	public:
		// ��ť����
		virtual	BOOL			OnClicked(UIWidget* pWidget,
			const CPoint& cPt);

	public:
		// ����ָ��
		void					ProcessCommand(int nCommand);
	};
}

#endif