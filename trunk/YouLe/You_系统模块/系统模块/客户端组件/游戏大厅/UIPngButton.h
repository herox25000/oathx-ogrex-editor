#ifndef _____UIPngButton_H
#define _____UIPngButton_H

#include "UIWidget.h"

namespace YouLe
{
	class UIPngButton : public UIWidget
	{
		enum{
			PNG_BTNNORMAL,
			PNG_BTNDOWN,
			PNG_BTNHOVER,
			PNG_BTNENABLE,
		};
	public:
		// ���캯��
		UIPngButton();
		// ��������
		virtual ~UIPngButton();

		// �����ؼ�
		virtual	BOOL	Create(INT nID, const RECT& rect, CWnd* pAttach, UIProcess* pProcess, HINSTANCE hInstance, LPCTSTR lpResourceName,
			INT nStatCount, UIWidget* pParent);

		// �����ؼ�
		virtual	BOOL	Create(INT nID, INT x, INT y, CWnd* pAttach, UIProcess* pProcess, HINSTANCE hInstance, LPCTSTR lpResourceName,
			INT nStatCount, UIWidget* pParent);

		// ��д����
		virtual BOOL	Draw(CDC* pDC);
		
		// ��Ч�ؼ�
		virtual void	EnabledWidget(bool bEnabled);
		
	public:
		// ����ƶ�
		virtual BOOL	OnMouseMove(const CPoint& cPt);
		// �������
		virtual BOOL	OnLeftDown(const CPoint& cPt);
		// �������
		virtual BOOL	OnLeftUp(const CPoint& cPt);
	protected:
		CPngImage*		m_pImage;
		INT				m_nSlice;
		INT				m_nState;
		BOOL			m_bPress;
		INT				m_nCount;
	};
}

#endif