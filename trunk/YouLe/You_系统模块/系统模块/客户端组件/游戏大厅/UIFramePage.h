#ifndef _____UIFramePage_H
#define _____UIFramePage_H

#include "UISheet.h"

namespace YouLe
{
	class UIFramePage : public UISheet, public UIProcess
	{
	public:
		// ���캯��
		UIFramePage();
		// ��������
		virtual ~UIFramePage();

		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	};
}

#endif