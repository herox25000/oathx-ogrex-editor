#ifndef _____UIPngButton_H
#define _____UIPngButton_H

#include "UIWidget.h"

namespace YouLe
{
	class UIPngButton : public UIWidget
	{
		enum {
			PNG_BTNNORMAL,
			PNG_BTNDOWN,
			PNG_BTNHOVER,
			PNG_BTNENABLE,
		};
	public:
		// 构造函数
		UIPngButton();
		// 析构函数
		virtual ~UIPngButton();

		// 创建控件
		virtual	BOOL	Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, HINSTANCE hInstance, LPCTSTR lpResourceName,
			INT nStatCount, UIWidget* pParent);

		// 创建控件
		virtual	BOOL	Create(INT nID, INT x, INT y, CWnd* pAttach, UIProcess* pProcess, HINSTANCE hInstance, LPCTSTR lpResourceName,
			INT nStatCount, UIWidget* pParent);

		// 重写绘制
		virtual BOOL	Draw(CDC* pDC);
		
		// 无效控件
		virtual void	EnabledWidget(bool bEnabled);

		// 设置按钮状态
		virtual void	SetButtonState(int nType);
		
	public:
		// 鼠标移动
		virtual BOOL	OnMouseMove(const CPoint& cPt);
		// 左键按下
		virtual BOOL	OnLeftDown(const CPoint& cPt);
		// 左键弹起
		virtual BOOL	OnLeftUp(const CPoint& cPt);
		// 鼠标离开
		virtual BOOL	OnMouseLeave(const CPoint& cPt);
		// 鼠标进入
		virtual BOOL	OnMouseEnter(const CPoint& cPt);
	protected:
		CPngImage*		m_pImage;
		INT				m_nSlice;
		INT				m_nState;
		BOOL			m_bPress;
		INT				m_nCount;
	};

	// 单选框
	class UIPngRadioButton : public UIWidget
	{
		enum {
			PNG_BTNNORMAL,
			PNG_BTNDOWN,
		};	
	public:
		UIPngRadioButton(void);
		virtual ~UIPngRadioButton(void);

		// 创建控件
		virtual	BOOL	Create(INT nID, INT x, INT y, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

	public:
		// 左键按下
		virtual BOOL	OnLeftDown(const CPoint& cPt);
		// 重写绘制
		virtual BOOL	Draw(CDC* pDC);

	public:
		//是否选中
		virtual void	SetCheck(BOOL bCheck);

	protected:
		CPngImage*		m_pImage;
		INT				m_nState;
		INT				m_nSlice;
	};
}

#endif