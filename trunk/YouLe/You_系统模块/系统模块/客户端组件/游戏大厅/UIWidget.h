#ifndef _____UIWidget_H
#define _____UIWidget_H

namespace YouLe
{
	class UIWidget;

	// UI ��Ϣ������
	class UIProcess
	{
	public:
		// ��������
		virtual ~UIProcess(){}

		// ������Ϣ
		virtual	BOOL		OnClicked(UIWidget* pWidget, 
			const CPoint& cPt)
		{
			return FALSE;
		}
		// ����ƶ�
		virtual BOOL		OnMouseMove(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}

		// ����϶�
		virtual BOOL		OnMouseDrag(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}

		// ����뿪
		virtual BOOL		OnMouseLeave(UIWidget* pWidget, 
			const CPoint& cPt)
		{
			return FALSE;
		}
		// ������
		virtual BOOL		OnMouseEnter(UIWidget* pWidget, 
			const CPoint& cPt)
		{
			return FALSE;
		}
		// �������
		virtual BOOL		OnLeftDown(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}
		// �������
		virtual BOOL		OnLeftUp(UIWidget* pWidget,
			const CPoint& cPt)
		{
			return FALSE;
		}

	};

	// GDI+ �Ի�UI������
	class UIWidget
	{
		// �ӿؼ���
		typedef std::vector< 
			UIWidget*>	UIWidgetRegister;

	public:
		// ���캯��
		UIWidget();
		// ��������
		virtual ~UIWidget();

		// �����ؼ�
		virtual BOOL		Create(INT nID, const RECT& rect,  CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);

		// ����ID
		virtual void		SetID(const INT nID);

		// ��ȡID
		virtual INT			GetID() const;

		// ˢ�¿ؼ�
		virtual void		Invalidate(BOOL bErase);

	public:
		// �Ƿ���Ч
		virtual	BOOL		IsWidgetEnabled() const;
		// �Ƿ���ʾ
		virtual BOOL		IsWidgetVisible() const;

	public:
		// ������Ч
		virtual void		EnabledWidget(bool bEnabled);
		// ������ʾ
		virtual void		VisibleWidget(bool bVisible);
		// ���ô�����ʾ
		virtual void		VisibleTrigger();
		// ����ʾʱ����
		virtual void		InvisibleTrigger();		

	public:
		// ��ȡ����
		virtual	void		GetWidgetRect(LPRECT lpRect);
		// ��ȡ�ͻ���
		virtual void		GetClientRect(LPRECT lpRect);
		
		// ����λ��
		virtual void		SetWidgetPos(INT nTop, INT x, INT y, INT w, INT h);
		// λ�ü��
		virtual BOOL		PtInRect(const CPoint& cPt);

		// ǿ���ö�
		virtual BOOL		MoveToFront();
	public:
		// ������Ϣ
		virtual	LRESULT		SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);

	public:
		// �ؼ�����
		virtual	BOOL		Draw(CDC* pDC);
		
	public:
		// ��ӿؼ�
		virtual BOOL		Add(UIWidget* pWidget);
		// �����ؼ�
		virtual UIWidget*	Search(INT nID);
		// �Ƴ��ؼ�
		virtual void		Remove(INT nID, BOOL bDestroy=TRUE);
	public:
		// ������
		virtual UIWidget*	GetChildWidget(const CPoint& cPt);
		// �Ƴ��ؼ�
		virtual void		Remove(UIWidget* pWidget, BOOL bDestroy=TRUE);
		// �ӿؼ���
		virtual	INT			GetWidgetCount() const;

	public:
		// ���ø���
		virtual void		SetParent(UIWidget* pParent);
		// ��ȡ����
		virtual	UIWidget*	GetParent() const;

	public:
		// ����ƶ�
		virtual BOOL		OnMouseMove(const CPoint& cPt);
		// ����϶�
		virtual BOOL		OnMouseDrag(const CPoint& cPt); 
		// �������
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		// �������
		virtual BOOL		OnLeftUp(const CPoint& cPt);
		// ����뿪
		virtual BOOL		OnMouseLeave(const CPoint& cPt);
		// ������
		virtual BOOL		OnMouseEnter(const CPoint& cPt);
		// �����Ӧ
		virtual BOOL		OnClicked(const CPoint& cPt);
	protected:
		CWnd*				m_pAttach;
		UIWidget*			m_pParent;
		UIWidgetRegister	m_WidgetReg;
		INT					m_nID;
		BOOL				m_bEnabled;
		BOOL				m_bVisible;
		CRect				m_rect;
		UIProcess*			m_pProcess;
	};

}

#endif