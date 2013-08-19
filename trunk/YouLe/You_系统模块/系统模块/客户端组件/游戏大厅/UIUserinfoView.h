#pragma once

namespace YouLe
{
	class UIUserinfoView : public UIWidget
	{
	public:
		UIUserinfoView(void);
		virtual ~UIUserinfoView(void);

	public:
		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	protected:
		CPngImage			m_ImageBack;
	};

	// 修改用户资料
	class UIModifyUserInfoView : public UIWidget
	{
	public:
		UIModifyUserInfoView(void);
		virtual ~UIModifyUserInfoView(void);

	public:
		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

		virtual void		VisibleWidget(bool bVisible);
	protected:
		CPngImage			m_ImageBack;
		CSkinEditEx			m_Password;
	};

	// 修改用户密码
	class UIModifyPasswordView : public UIWidget
	{
	public:
		UIModifyPasswordView(void);
		virtual ~UIModifyPasswordView(void);

	public:
		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);

		virtual BOOL		Draw(CDC* pDC);

	protected:
		CPngImage			m_ImageBack;
	};

}
