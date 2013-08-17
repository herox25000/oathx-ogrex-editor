#pragma once

namespace YouLe
{
	class UIUserinfoView : public UIWidget
	{
	public:
		UIUserinfoView(void);
		virtual ~UIUserinfoView(void);

	public:
		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	protected:
		CPngImage			m_ImageBack;
	};

	// �޸��û�����
	class UIModifyUserInfoView : public UIWidget
	{
	public:
		UIModifyUserInfoView(void);
		virtual ~UIModifyUserInfoView(void);

	public:
		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	protected:
		CPngImage			m_ImageBack;
	};

	// �޸��û�����
	class UIModifyPasswordView : public UIWidget
	{
	public:
		UIModifyPasswordView(void);
		virtual ~UIModifyPasswordView(void);

	public:
		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	protected:
		CPngImage			m_ImageBack;
	};

}
