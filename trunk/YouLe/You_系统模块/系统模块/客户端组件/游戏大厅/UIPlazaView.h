//////////////////////////////////////////////////////////////////////////
/************************ ��Ϸ��������***********************************/
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "UIPngButton.h"

namespace YouLe
{
	class UIPlazaView : public UIWidget, public UIProcess
	{
	public:
		UIPlazaView(void);
		virtual ~UIPlazaView(void);

	public:
		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
									UIProcess* pProcess, UIWidget* pParent);

	public:
		// ��갴��
		virtual BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

	public:
		//��ʾ��ҳ
		void				ShowPage(int nPageID);

	protected:
		//ҳ�б�
		std::map<int, int >		m_mViewList;
		//��ǰ��ʾ��ҳ
		int						m_nCurDispView;

	};

};
