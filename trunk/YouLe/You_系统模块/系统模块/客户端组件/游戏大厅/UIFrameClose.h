#ifndef _____UIFRAMECLOSE_H
#define _____UIFRAMECLOSE_H

#include "UIPngButton.h"

namespace YouLe
{
	class UIFrameClose : public UIWidget, public UIProcess
	{
	public:
		// 构造函数
		UIFrameClose();
		// 析构函数
		virtual ~UIFrameClose();

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
				UIProcess* pProcess, UIWidget* pParent);
		
		// 重写绘制
		virtual BOOL		Draw(CDC* pDC);

	public:
		// 鼠标移动
		virtual BOOL		OnMouseMove(const CPoint& cPt);
		// 鼠标按下
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		// 鼠标弹起
		virtual BOOL		OnLeftUp(const CPoint& cPt);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
	protected:
		CPngImage			m_PngBack;
		BOOL				m_bPress;

	};
};
#endif