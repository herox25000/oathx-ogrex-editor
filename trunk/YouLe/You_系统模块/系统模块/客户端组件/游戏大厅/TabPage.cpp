#include "StdAfx.h"
#include "TabPage.h"

// ���캯��
CTabPage::CTabPage(void) : m_nID(0), m_pWnd(NULL)
{
}

// ��������
CTabPage::~CTabPage(void)
{
}

// ���ݴ���
BOOL CTabPage::Create(INT nID, const RECT& rect, CWnd* pParent)
{
	m_nID	= nID;
	m_pWnd	= pParent;
	m_rect	= rect;
	
	return TRUE;
}

// ��ȡID
INT	CTabPage::GetID() const
{
	return m_nID;
}

// ��ʾ����
void CTabPage::ShowWindow(int nCmdShow)
{

}
