#ifndef _____UIGamePage_H
#define _____UIGamePage_H

#include "UIPngButton.h"
#include "UIGameItem.h"
#include "UIRoomPage.h"
#include "UITablePage.h"

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
		virtual void		VisibleTrigger();
	public:
		void				ShowRoomView(CListKind* pKind);

	public:
		//��Ϸ��ͼ
		UIGameView*			m_pGameView;
		//������ͼ
		UIRoomPage*			m_pRoomView;
		//������ͼ
		UITablePage*		m_pTableView;
	};
}

#endif