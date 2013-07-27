#ifndef _____UIGamePage_H
#define _____UIGamePage_H

#include "UIPngButton.h"
#include "UIGameItem.h"

namespace YouLe
{
	// ��Ϸר��
	class UIGamePage : public UIWidget, public UIProcess
	{
	public:
		// ���캯��
		UIGamePage();
		// ��������
		virtual ~UIGamePage();
		
		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

	public:
		// ���õ�ǰ��ʾҳ
		virtual void		SetPage(INT nPage);

	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
	protected:
		UIGameView*			m_pGameView;
	};
}

#endif