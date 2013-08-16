#pragma once

#include "UIPngButton.h"
#include "UIPngRadioButton.h"

namespace YouLe
{
	class UIFrameSet : public UIWidget, public UIProcess
	{
	public:
		UIFrameSet(void);
		virtual ~UIFrameSet(void);

		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		// �������
		virtual BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

	protected:
		CPngImage			m_ImageBack;

	};
};
