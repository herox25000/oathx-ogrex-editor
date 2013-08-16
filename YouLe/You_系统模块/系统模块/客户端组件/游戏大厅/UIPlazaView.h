//////////////////////////////////////////////////////////////////////////
/************************ 游戏大厅界面***********************************/
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
		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
									UIProcess* pProcess, UIWidget* pParent);

	public:
		// 鼠标按下
		virtual BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

	public:
		//显示哪页
		void				ShowPage(int nPageID);

	protected:
		//页列表
		std::map<int, int >		m_mViewList;
		//当前显示的页
		int						m_nCurDispView;

	};

};
