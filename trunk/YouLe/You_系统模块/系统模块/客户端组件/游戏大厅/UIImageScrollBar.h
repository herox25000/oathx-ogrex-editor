#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	enum Bar_Dir
	{
		VERTICAL = 0,	//垂直
		LEVEL			//水平
	};

	// 滚动条监听类
	class UIScrollListener
	{
	public:
		virtual void ScrollPosition(int theId, double thePosition) {};
	};

	// 滚动条类
	class UIImageScrollBar : public UIWidget, public UIProcess
	{
	public:
		UIImageScrollBar(UINT theID, UIScrollListener* ScrollListener,Bar_Dir Direction);
		~UIImageScrollBar(void);
		
	public:
		// 创建控件
		virtual BOOL		Create(INT nID, const RECT& rect,  CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		virtual BOOL		OnDraw(CDC* pDC);
		virtual BOOL		OnMouseDrag(const CPoint& cPt);
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		virtual BOOL		OnLeftUp(const CPoint& cPt);

		// 按键消息
		virtual	BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

	protected:
		UIScrollListener*	m_ScrollListener;	
		CPngImage			m_BGImage;		//背景图
		CPngImage			m_ThumbImage;	//滚动条
		Size				m_ThumbSize;	//滚动条尺寸	
		Bar_Dir				m_Direction;
		UINT				m_TheID;		//ID
		bool				m_PressedOnThumb;
		double				m_Value;
		int					m_LastMouseX;
		int					m_LastMouseY;
	};
}
