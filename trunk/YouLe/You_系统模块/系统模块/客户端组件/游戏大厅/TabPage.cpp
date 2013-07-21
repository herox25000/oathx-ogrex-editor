#include "StdAfx.h"
#include "TabPage.h"

// 构造函数
CTabPage::CTabPage(void) : m_nID(0), m_pWnd(NULL)
{
}

// 析构函数
CTabPage::~CTabPage(void)
{
}

// 数据创建
BOOL CTabPage::Create(INT nID, const RECT& rect, CWnd* pParent)
{
	m_nID	= nID;
	m_pWnd	= pParent;
	m_rect	= rect;
	
	return TRUE;
}

// 获取ID
INT	CTabPage::GetID() const
{
	return m_nID;
}

// 显示窗口
void CTabPage::ShowWindow(int nCmdShow)
{

}
