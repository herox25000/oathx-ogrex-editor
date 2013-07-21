#ifndef PASSWORD_CONTROL_HEAD_FILE
#define PASSWORD_CONTROL_HEAD_FILE

#pragma once
#define  LEN_PASSWORD 32

//密码编辑
class  CPasswordControl : public CWnd
{
	//状态变量
protected:
	bool							m_bModify;							//修改标志
	bool							m_bFalsity;							//虚假标志
	bool							m_bDrawBorad;						//绘画边框
	bool							m_bRenderImage;						//渲染标志
	TCHAR							m_szPassword[LEN_PASSWORD];					//用户密码

	//控件变量
public:
	CSkinEditEx						m_edPassword;						//密码控件

	//函数定义
public:
	//构造函数
	CPasswordControl();
	//析构函数
	virtual ~CPasswordControl();

	//重载函数
protected:
	//绑定函数
	virtual VOID PreSubclassWindow();

	//状态函数
public:
	//修改状态
	bool IsModifyPassword() { return m_bModify; }
	//虚假状态
	bool IsFalsityPassword() { return m_bFalsity; }

	//功能函数
public:
	//边框设置
	VOID SetDrawBorad(bool bDrawBorad);
	//设置密码
	VOID SetUserPassword(LPCTSTR pszPassword);
	//获取密码
	LPCTSTR GetUserPassword(TCHAR szPassword[LEN_PASSWORD]);
	//设置颜色
	VOID SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorad);

	//消息定义
protected:
	//重画消息
	VOID OnPaint();
	//重画消息
	VOID OnNcPaint();
	//绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	//获取焦点
	VOID OnSetFocus(CWnd * pOldWnd);

	//控件消息
protected:
	//密码改变
	VOID OnEnChangePassword();
	//键盘按钮
	VOID OnBnClickedKeyboard();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif