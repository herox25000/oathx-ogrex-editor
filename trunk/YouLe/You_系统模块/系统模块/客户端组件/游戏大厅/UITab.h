#ifndef _____UITab_H
#define _____UITab_H

#include "UIPngButton.h"

namespace YouLe
{
	// Tab �ؼ�
	class UITab : public UIWidget
	{
	public:
		// ���캯��
		UITab();
		// ��������
		virtual ~UITab();

		// �����ؼ�
		virtual BOOL	Create(INT nID, const RECT& rect, CWnd* pAttach, UIWidget* pParent);
		
		// ���õ�ǰҳ
		virtual void	SetCurPage(INT nPage);
		// ��ȡ��ǰҳ
		virtual INT		GetCurPage() const;
	public:
		virtual BOOL	OnMouseMove(const CPoint& cPt);
	protected:
		INT				m_nCurPage;
	};
}

#endif