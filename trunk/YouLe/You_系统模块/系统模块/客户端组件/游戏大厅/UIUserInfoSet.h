#pragma once

#include "UIPngButton.h"

namespace YouLe
{
	class UIUserInfoSet : public UIWidget, public UIProcess
	{
	public:
		UIUserInfoSet(void);
		virtual ~UIUserInfoSet(void);

		// ´´½¨¿Ø¼þ
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	public:

	protected:
		CPngImage			m_ImageBack;

	};

};
