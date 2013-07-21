#pragma once

//////////////////////////////////////////////////////////////////////////
// 基本逻辑页面控件
//////////////////////////////////////////////////////////////////////////
class CTabPage
{
public:
	// 构造函数
	CTabPage();
	// 析构函数
	virtual ~CTabPage(void);
	// 创建页
	virtual BOOL	Create(INT nID, const RECT& rect, CWnd* pParent);
	// 获取ID
	virtual	INT		GetID() const;
	// 显示状态
	virtual void	ShowWindow(int nCmdShow);
protected:
	// 页ID
	INT				m_nID;
	// 页父窗口
	CWnd*			m_pWnd;
	// 窗口区域
	CRect			m_rect;
};
