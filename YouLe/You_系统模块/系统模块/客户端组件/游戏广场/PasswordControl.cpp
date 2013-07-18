#include "StdAfx.h"
#include "Winable.h"
#include "Resource.h"
#include "PasswordControl.h"

//////////////////////////////////////////////////////////////////////////////////


//控件标识
#define IDC_BT_KEYBOARD				100									//键盘按钮
#define IDC_ED_PASSWORD				200									//密码控件

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPasswordControl, CWnd)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_ED_PASSWORD, OnEnChangePassword)
	ON_BN_CLICKED(IDC_BT_KEYBOARD, OnBnClickedKeyboard)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////////////

//构造函数
CPasswordControl::CPasswordControl()
{
	//设置变量
	m_bModify=false;
	m_bFalsity=false;
	m_bDrawBorad=true;
	m_bRenderImage=true;
	ZeroMemory(m_szPassword,sizeof(m_szPassword));

	return;
}

//析构函数
CPasswordControl::~CPasswordControl()
{
}

//绑定函数
VOID CPasswordControl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//获取位置
	CRect rcClient;
	CRect rcWindow;
	GetClientRect(&rcClient);
	GetWindowRect(&rcWindow);

	//创建按钮
	CRect rcButton(0,0,0,0);

	//创建控件
	CRect rcEditCreate;
	rcEditCreate.top=4;
	rcEditCreate.left=4;
	rcEditCreate.bottom=16;
	rcEditCreate.right=rcClient.Width();
	m_edPassword.Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_PASSWORD,rcEditCreate,this,IDC_ED_PASSWORD);

	//设置控件
	m_edPassword.LimitText(LEN_PASSWORD-1);
	m_edPassword.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edPassword.SetFont(CFont::FromHandle(CSkinResourceManager::GetDefaultFont()));

	//移动窗口
	SetWindowPos(NULL,0,0,rcWindow.Width(),24,SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);
	return;
}

//边框设置
VOID CPasswordControl::SetDrawBorad(bool bDrawBorad)
{
	//设置变量
	m_bDrawBorad=bDrawBorad;

	//更新界面
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}



//设置密码
VOID CPasswordControl::SetUserPassword(LPCTSTR pszPassword)
{
	//设置控件
	INT nPasswordLen=lstrlen(pszPassword);
	m_edPassword.SetWindowText((nPasswordLen>0)?TEXT("********"):TEXT(""));

	//设置变量
	m_bModify=false;
	m_bFalsity=true;
	lstrcpyn(m_szPassword,pszPassword,CountArray(m_szPassword));

	return;
}

//获取密码
LPCTSTR CPasswordControl::GetUserPassword(TCHAR szPassword[LEN_PASSWORD])
{
	//控件密码
	if (m_bModify==true)
	{
		m_bModify=false;
		m_edPassword.GetWindowText(m_szPassword,CountArray(m_szPassword));
	}

	//拷贝密码
	lstrcpyn(szPassword,m_szPassword,LEN_PASSWORD);

	return szPassword;
}

//设置颜色
VOID CPasswordControl::SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorad)
{
	m_edPassword.SetEnableColor(crEnableText,crEnableBK,crEnableBorad);
}

//重画消息
VOID CPasswordControl::OnPaint()
{
	CPaintDC dc(this);

	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	////绘画背景
	//if (IsWindowEnabled()==TRUE)
	//{
	//	dc.FillSolidRect(rcClient,CSkinEdit::m_SkinAttribute.m_crFocusBK);
	//}
	//else
	//{
	//	dc.FillSolidRect(rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);
	//}


	//绘画背景
	if (IsWindowEnabled()==TRUE)
	{
		dc.FillSolidRect(rcClient,RGB(255,255,255));
	}
	else
	{
		dc.FillSolidRect(rcClient,RGB(255,255,255));
	}
	return;
}

//重画消息
VOID CPasswordControl::OnNcPaint()
{
	//获取位置
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	ScreenToClient(&rcWindow);
	
	//颜色定义
	COLORREF crBackGround=CSkinEdit::m_SkinAttribute.m_crNoFocusBK;
	COLORREF crFrameBorad=CSkinEdit::m_SkinAttribute.m_crFocusBK;

	//禁用状态
	if (IsWindowEnabled()==FALSE)
	{
		if (m_bRenderImage==false)
		{
			crBackGround=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
			crFrameBorad=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		}
		else
		{
			crBackGround=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
			crFrameBorad=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		}
	}
	else
	{
		//crBackGround=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		//crFrameBorad=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		crBackGround=RGB(255,255,255);
		crFrameBorad=RGB(255,255,255);
	}

	//边框判断
	if (m_bDrawBorad==false)
	{
		crFrameBorad=crBackGround;
	}

	//绘画边框
	CClientDC ClientDC(this);
	ClientDC.Draw3dRect(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),crFrameBorad,crFrameBorad);
	ClientDC.Draw3dRect(rcWindow.left+1,rcWindow.top+1,rcWindow.Width()-2,rcWindow.Height()-2,crBackGround,crBackGround);

	return;

}

//绘画背景
BOOL CPasswordControl::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

//获取焦点
VOID CPasswordControl::OnSetFocus(CWnd * pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	//设置焦点
	m_edPassword.SetFocus();

	//设置选择
	m_edPassword.SetSel(0,-1,FALSE);

	return;
}

//密码改变
VOID CPasswordControl::OnEnChangePassword()
{
	//设置变量
	m_bModify=true;
	m_bFalsity=false;

	//发送消息
	CWnd * pParent=GetParent();
	if (pParent!=NULL) pParent->SendMessage(WM_COMMAND,MAKELONG(GetWindowLong(m_hWnd,GWL_ID),EN_CHANGE),(LPARAM)m_hWnd);

	return;
}

//键盘按钮
VOID CPasswordControl::OnBnClickedKeyboard()
{
	//获取位置
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//密码清理
	if (m_bFalsity==true)
	{
		m_bFalsity=false;
		m_edPassword.SetWindowText(TEXT(""));
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

