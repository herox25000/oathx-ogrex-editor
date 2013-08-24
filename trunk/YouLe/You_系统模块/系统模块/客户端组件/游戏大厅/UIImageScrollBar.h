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
		UIImageScrollBar(UINT theID, UIScrollListener* ScrollListener,Bar_Dir Direction = VERTICAL);
		~UIImageScrollBar(void);
		
	public:
		// �����ؼ�
		virtual BOOL		Create(INT nID, const RECT& rect,  CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		virtual BOOL		Create(INT nID, const RECT& rect,  CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		virtual BOOL		OnDraw(CDC* pDC);
		virtual BOOL		OnMouseDrag(const CPoint& cPt);
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		virtual BOOL		OnLeftUp(const CPoint& cPt);
		// ������Ϣ
		virtual	BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

		// �ⲿ����
	public:
		virtual void		SetInvisIfNoScroll(bool invisIfNoScroll);
		virtual void		SetMaxValue(double theNewMaxValue);
		virtual void		SetPageSize(double theNewPageSize);
		virtual void		SetValue(double theNewValue);

	protected:	
		//
		virtual bool		AtBottom();
		virtual void		GoToBottom();
		virtual int			GetTrackSize();
		virtual int			GetThumbSize();
		virtual int			GetThumbPosition();
		virtual void		ClampValue();
		virtual void		SetThumbPosition(int thePosition);
		virtual int			ThumbCompare(int x, int y);

	protected:
		UIScrollListener*	m_ScrollListener;	
		CPngImage			m_BGImage;		//����ͼ
		CPngImage			m_ThumbImage;	//������
		UIPngButton*		m_btUp;
		UIPngButton*		m_btDown;
		int					m_ThumbSize;	//�������ߴ�	
		Size				m_BtSize;
		Bar_Dir				m_Direction;
		UINT				m_TheID;		//ID
		bool				m_PressedOnThumb;
		int					m_MouseDownThumbPos;
		int					m_MouseDownX;
		int					m_MouseDownY;
		double				m_Value;
		double				m_MaxValue;
		double				m_PageSize;
		int					m_LastMouseX;
		int					m_LastMouseY;
		int					m_UpdateAcc;
		int					m_ButtonAcc;
		bool				m_InvisIfNoScroll;
	};
}
