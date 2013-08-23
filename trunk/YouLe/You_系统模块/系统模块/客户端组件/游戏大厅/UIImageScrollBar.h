#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	enum Bar_Dir
	{
		VERTICAL = 0,	//��ֱ
		LEVEL			//ˮƽ
	};

	// ������������
	class UIScrollListener
	{
	public:
		virtual void ScrollPosition(int theId, double thePosition) {};
	};

	// ��������
	class UIImageScrollBar : public UIWidget, public UIProcess
	{
	public:
		UIImageScrollBar(UINT theID, UIScrollListener* ScrollListener,Bar_Dir Direction);
		~UIImageScrollBar(void);
		
	public:
		// �����ؼ�
		virtual BOOL		Create(INT nID, const RECT& rect,  CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		virtual BOOL		OnDraw(CDC* pDC);
		virtual BOOL		OnMouseDrag(const CPoint& cPt);
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		virtual BOOL		OnLeftUp(const CPoint& cPt);

		// ������Ϣ
		virtual	BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

	protected:
		UIScrollListener*	m_ScrollListener;	
		CPngImage			m_BGImage;		//����ͼ
		CPngImage			m_ThumbImage;	//������
		Size				m_ThumbSize;	//�������ߴ�	
		Bar_Dir				m_Direction;
		UINT				m_TheID;		//ID
		bool				m_PressedOnThumb;
		double				m_Value;
		int					m_LastMouseX;
		int					m_LastMouseY;
	};
}
