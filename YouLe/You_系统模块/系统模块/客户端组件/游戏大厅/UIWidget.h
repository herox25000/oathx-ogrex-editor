#ifndef _____UIWidget_H
#define _____UIWidget_H

namespace YouLe
{
	class UIWidget;

	// UI 消息处理器
	class UIProcess
	{
	public:
		// 析构函数
		virtual ~UIProcess(){}

		// 按下消息
		virtual	BOOL		OnClicked(UIWidget* pWidget, 
			const CPoint& cPt)
		{
			return FALSE;
		}
		// 鼠标移动
		virtual BOOL		OnMouseMove(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}

		// 鼠标拖动
		virtual BOOL		OnMouseDrag(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}

		// 鼠标离开
		virtual BOOL		OnMouseLeave(UIWidget* pWidget, 
			const CPoint& cPt)
		{
			return FALSE;
		}
		// 鼠标进入
		virtual BOOL		OnMouseEnter(UIWidget* pWidget, 
			const CPoint& cPt)
		{
			return FALSE;
		}
		// 左键按下
		virtual BOOL		OnLeftDown(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}
		// 左键弹起
		virtual BOOL		OnLeftUp(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}
		// 键盘按下
		virtual BOOL		OnKeyDwon(UINT nChar, UINT nRepCnt, UINT nFlags)
		{
			return FALSE;
		}
		// 键盘弹起
		virtual BOOL		OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
		{
			return FALSE;
		}
		// 字符输入
		virtual BOOL		OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
		{
			return FALSE;
		}
	};

	// GDI+ 自绘UI基础类
	class UIWidget
	{
		// 子控件表
		typedef std::vector< 
			UIWidget*>	UIWidgetRegister;

	public:
		// 构造函数
		UIWidget();
		// 析构函数
		virtual ~UIWidget();

		// 创建控件
		virtual BOOL		Create(INT nID, const RECT& rect,  CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

		// 重设ID
		virtual void		SetID(const INT nID);

		// 获取ID
		virtual INT			GetID() const;

		// 刷新控件
		virtual void		Invalidate(BOOL bErase);

	public:
		// 是否有效
		virtual	BOOL		IsWidgetEnabled() const;
		// 是否显示
		virtual BOOL		IsWidgetVisible() const;

	public:
		// 设置有效
		virtual void		EnabledWidget(bool bEnabled);
		// 设置显示
		virtual void		VisibleWidget(bool bVisible);
		// 设置触发显示
		virtual void		VisibleTrigger();
		// 不显示时触发
		virtual void		InvisibleTrigger();		

	public:
		// 获取区域
		virtual	void		GetWidgetRect(LPRECT lpRect);
		// 位置检测
		virtual BOOL		PtInRect(const CPoint& cPt);		
		// 获取客户区
		virtual void		GetClientRect(LPRECT lpRect);
		
	public:
		// 设置位置
		virtual void		SetWidgetPos(INT nTop, INT x, INT y, INT w, INT h);
		// 强制置顶
		virtual BOOL		MoveToFront();

	public:
		// 发送消息
		virtual	LRESULT		SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);

	public:
		// 控件绘制
		virtual	BOOL		Draw(CDC* pDC);
		
	public:
		// 添加控件
		virtual BOOL		Add(UIWidget* pWidget);
		// 搜索控件
		virtual UIWidget*	Search(INT nID);
		// 移除控件
		virtual void		Remove(INT nID, BOOL bDestroy=TRUE);
	public:
		// 鼠标查找
		virtual UIWidget*	GetChildWidget(const CPoint& cPt);
		// 移除控件
		virtual void		Remove(UIWidget* pWidget, BOOL bDestroy=TRUE);
		// 子控件数
		virtual	INT			GetWidgetCount() const;

	public:
		// 设置父亲
		virtual void		SetParent(UIWidget* pParent);
		// 获取父亲
		virtual	UIWidget*	GetParent() const;

	public:
		// 鼠标移动
		virtual BOOL		OnMouseMove(const CPoint& cPt);
		// 鼠标拖动
		virtual BOOL		OnMouseDrag(const CPoint& cPt); 
		// 左键按下
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		// 左键弹起
		virtual BOOL		OnLeftUp(const CPoint& cPt);

	public:
		// 键盘按下
		virtual BOOL		OnKeyDwon(UINT nChar, UINT nRepCnt, UINT nFlags);
		// 键盘弹起
		virtual BOOL		OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		// 字符输入
		virtual BOOL		OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	public:
		// 鼠标离开
		virtual BOOL		OnMouseLeave(const CPoint& cPt);
		// 鼠标进入
		virtual BOOL		OnMouseEnter(const CPoint& cPt);

	public:
		// 鼠标响应
		virtual BOOL		OnClicked(const CPoint& cPt);
	protected:
		CWnd*				m_pAttach;
		UIWidget*			m_pParent;
		UIWidgetRegister	m_WidgetReg;
		INT					m_nID;
		BOOL				m_bEnabled;
		BOOL				m_bVisible;
		CRect				m_rect;
		UIProcess*			m_pProcess;
	};

}

#endif