#ifndef _____UIFRAMECLOSE_H
#define _____UIFRAMECLOSE_H

#include "UIPngButton.h"

namespace YouLe
{
	class UIFrameClose : public UIWidget, public UIProcess
	{
	public:
		// ���캯��
		UIFrameClose();
		// ��������
		virtual ~UIFrameClose();

		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
				UIProcess* pProcess, UIWidget* pParent);
		
		// ��д����
		virtual BOOL		Draw(CDC* pDC);

	public:
		// ����ƶ�
		virtual BOOL		OnMouseMove(const CPoint& cPt);
		// ��갴��
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		// ��굯��
		virtual BOOL		OnLeftUp(const CPoint& cPt);

	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
	protected:
		CPngImage			m_PngBack;
		BOOL				m_bPress;

	};
};
#endif