#pragma once

#include "GamePage.h"
#include "TabPage.h"

//////////////////////////////////////////////////////////////////////////
// ��Ϸר��ҳ��
//////////////////////////////////////////////////////////////////////////
class CGameZonePage : public CTabPage
{
public:
	// ���캯��
	CGameZonePage();
	// ��������
	virtual ~CGameZonePage();

	// ����ר��
	virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pParent);
	// ��ʾ״̬
	virtual void		ShowWindow(int nCmdShow);
	// ����ˢ��
	virtual	void		EraseBkgnd(CDC* pDC);
protected:
	// ��Ŀ����
	CGamePage			m_GamePage;
	// ҳ�水ť
	CGdipButton			m_GameBnts[4];
};