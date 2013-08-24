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

	public:
		// ����ƶ�
		virtual BOOL		InjectMouseMove(const CPoint& cPt);
		// ��갴��
		virtual BOOL		InjectLeftDown(const CPoint& cPt);
		// ��굯��
		virtual BOOL		InjectLeftUp(const CPoint& cPt);
		// ���̰���
		virtual BOOL		InjectKeyDwon(UINT nChar, UINT nRepCnt, UINT nFlags);
		// ���̵���
		virtual BOOL		InjectKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
		// �ַ�����
		virtual BOOL		InjectChar(UINT nChar, UINT nRepCnt, UINT nFlags);
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