#pragma once

namespace YouLe
{
	class UIMatchPage : public UIWidget, public UIProcess
	{
	public:
		UIMatchPage(void);
		virtual ~UIMatchPage(void);

	public:
		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);
	};
}

