#pragma once

#include "UIPngButton.h"

namespace YouLe
{
	class UIUserInfoSet : public UIWidget, public UIProcess
	{
	public:
		UIUserInfoSet(void);
		virtual ~UIUserInfoSet(void);

		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		// ������Ϣ
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	public:
		// ���ô�����ʾ
		virtual void		VisibleTrigger();

	public:
		void				ShowPage(int nPageID);

	protected:
		CPngImage			m_ImageBack;

		int					m_nCurShowPageID;

	};

};
