#ifndef _____UIFRAMEPage_H
#define _____UIFRAMEPage_H

#include "UIPngButton.h"

namespace YouLe
{
	class UIFramePage : public UIWidget, public UIProcess
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