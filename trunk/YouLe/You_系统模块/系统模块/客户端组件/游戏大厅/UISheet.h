#ifndef _____UISheet_H
#define _____UISheet_H

#include "UIWidget.h"

namespace YouLe
{
	// ����UI����
	class UISheet : public UIWidget
	{
	public:
		// ���캯��
		UISheet();
		// ��������
		virtual ~UISheet();

		// ���ý���
		virtual void		SetFocus(UIWidget* pFocus);
		// ��ȡ����
		virtual UIWidget*	GetFocus() const;
		// �Ƿ񽹵�
		virtual BOOL		IsFocus(UIWidget* pFocus);
	public:
		// ����ƶ�
		virtual BOOL		InjectMouseMove(const CPoint& cPt);
		// ��갴��
		virtual BOOL		InjectLeftDown(const CPoint& cPt);
		// ��굯��
		virtual BOOL		InjectLeftUp(const CPoint& cPt);

	protected:
		// ��ǰ����
		UIWidget*			m_pFocus;
		// ��ǰ����
		UIWidget*			m_pInput;
		// �Ƿ���
		BOOL				m_bPress;
	};
}

#endif