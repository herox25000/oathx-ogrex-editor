#pragma once

namespace YouLe
{
	class UIFrameUserPage : public UIWidget, public UIProcess
	{
	public:
		UIFrameUserPage(void);
		virtual ~UIFrameUserPage(void);

	public:
		virtual BOOL		Create(INT nID, const RECT& rect,  CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

		virtual	BOOL		Draw(CDC* pDC);

		// ×ó¼ü°´ÏÂ
		virtual BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	protected:
		CPngImage			m_UserHead;

	};

}
