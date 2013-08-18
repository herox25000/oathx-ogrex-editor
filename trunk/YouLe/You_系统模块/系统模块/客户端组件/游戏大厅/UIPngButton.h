#ifndef _____UIPngButton_H
#define _____UIPngButton_H

#include "UIWidget.h"

namespace YouLe
{
	class UIPngButton : public UIWidget
	{
		enum {
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

		// ���ð�ť״̬
		virtual void	SetButtonState(int nType);
		
	public:
		// ����ƶ�
		virtual BOOL	OnMouseMove(const CPoint& cPt);
		// �������
		virtual BOOL	OnLeftDown(const CPoint& cPt);
		// �������
		virtual BOOL	OnLeftUp(const CPoint& cPt);
		// ����뿪
		virtual BOOL	OnMouseLeave(const CPoint& cPt);
		// ������
		virtual BOOL	OnMouseEnter(const CPoint& cPt);
	protected:
		CPngImage*		m_pImage;
		INT				m_nSlice;
		INT				m_nState;
		BOOL			m_bPress;
		INT				m_nCount;
	};

	// ��ѡ��
	class UIPngRadioButton : public UIWidget
	{
		enum {
			PNG_BTNNORMAL,
			PNG_BTNDOWN,
		};	
	public:
		UIPngRadioButton(void);
		virtual ~UIPngRadioButton(void);

		// �����ؼ�
		virtual	BOOL	Create(INT nID, INT x, INT y, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

	public:
		// �������
		virtual BOOL	OnLeftDown(const CPoint& cPt);
		// ��д����
		virtual BOOL	Draw(CDC* pDC);

	public:
		//�Ƿ�ѡ��
		virtual void	SetCheck(BOOL bCheck);

	protected:
		CPngImage*		m_pImage;
		INT				m_nState;
		INT				m_nSlice;
	};
}

#endif