#include "Stdafx.h"
#include "SkinEdit.h"

//////////////////////////////////////////////////////////////////////////

//静态变量
CSkinEditAttribute					CSkinEdit::m_SkinAttribute;				//界面属性

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinEdit, CEdit)

BEGIN_MESSAGE_MAP(CSkinEdit, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSkinEditEx, CSkinEdit)
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CSkinEditAttribute::CSkinEditAttribute() 
{
	//初始化变量
	m_crFocusTX=RGB(0,0,0);
	m_crFocusBK=RGB(0,0,0);
	m_crNoFocusTX=RGB(0,0,0);
	m_crNoFocusBK=RGB(0,0,0);
	m_crDisFocusTX=RGB(0,0,0);
	m_crDisFocusBK=RGB(0,0,0);

	return;
}

//析构函数
CSkinEditAttribute::~CSkinEditAttribute() 
{
}

//加载配置
bool CSkinEditAttribute::UpdateSkinResource(ISkinResource * pISkinResource)
{
	//获取信息
	tagSkinEditResource SkinEditResource;
	if (pISkinResource!=NULL) pISkinResource->GetResourceInfo(SkinEditResource);

	//设置变量
	m_crFocusTX=SkinEditResource.crFocusTX;
	m_crFocusBK=SkinEditResource.crFocusBK;
	m_crNoFocusTX=SkinEditResource.crNoFocusTX;
	m_crNoFocusBK=SkinEditResource.crNoFocusBK;
	m_crDisFocusTX=SkinEditResource.crDisFocusTX;
	m_crDisFocusBK=SkinEditResource.crDisFocusBK;

	//创建画刷
	m_brFocus.DeleteObject();
	m_brNoFocus.DeleteObject();
	m_brDisbale.DeleteObject();
	m_brFocus.CreateSolidBrush(m_crFocusBK);
	m_brNoFocus.CreateSolidBrush(m_crNoFocusBK);

	return true;
}

//////////////////////////////////////////////////////////////////////////

//构造函数
CSkinEdit::CSkinEdit()
{
	m_bFocus=false;
}

//析构函数
CSkinEdit::~CSkinEdit()
{
}

//绘画控件
HBRUSH CSkinEdit::CtlColor(CDC * pDC, UINT nCtlColor)
{
	pDC->SetBkMode(OPAQUE);
	if (IsWindowEnabled())
	{
		if (m_bFocus) 
		{
			pDC->SetTextColor(m_SkinAttribute.m_crFocusTX);
			pDC->SetBkColor(m_SkinAttribute.m_crFocusBK);
			return m_SkinAttribute.m_brFocus;
		}
		pDC->SetTextColor(m_SkinAttribute.m_crNoFocusTX);
		pDC->SetBkColor(m_SkinAttribute.m_crNoFocusBK);
		return m_SkinAttribute.m_brNoFocus;
	}
	pDC->SetTextColor(m_SkinAttribute.m_crDisFocusBK);
	pDC->SetBkColor(m_SkinAttribute.m_crDisFocusBK);
	return m_SkinAttribute.m_brDisbale;
}

//得到焦点
void CSkinEdit::OnSetFocus(CWnd * pOldWnd)
{
	m_bFocus=true;
	Invalidate(TRUE);
	__super::OnSetFocus(pOldWnd);
}

//失去焦点
void CSkinEdit::OnKillFocus(CWnd * pNewWnd)
{
	m_bFocus=false;
	Invalidate(TRUE);
	__super::OnKillFocus(pNewWnd);
}

//绘画控件
VOID CSkinEdit::DrawControlView(CDC * pDC, COLORREF crColorBorad,  COLORREF crColorBK)
{
	//获取位置
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	ScreenToClient(&rcWindow);

	//绘画边框
	if (GetExStyle()&WS_EX_CLIENTEDGE)
	{
		pDC->Draw3dRect(&rcWindow,crColorBorad,crColorBorad);
		pDC->Draw3dRect(rcWindow.left+1,rcWindow.top+1,rcWindow.Width()-2,rcWindow.Height()-2,crColorBK,crColorBK);
	}
	else
	{
		pDC->Draw3dRect(&rcWindow,crColorBK,crColorBK);
		pDC->Draw3dRect(rcWindow.left+1,rcWindow.top+1,rcWindow.Width()-2,rcWindow.Height()-2,crColorBK,crColorBK);
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CSkinEditEx::CSkinEditEx()
{
	//背景颜色
	m_crEnableBK=m_SkinAttribute.m_crFocusBK;
	m_crDisableBK=m_SkinAttribute.m_crNoFocusBK;

	//字体颜色
	m_crEnableText=m_SkinAttribute.m_crFocusTX;
	m_crDisableText=m_SkinAttribute.m_crNoFocusTX;

	//边框颜色
	m_crEnableBorad=m_SkinAttribute.m_crDisFocusTX;
	m_crDisableBorad=m_SkinAttribute.m_crDisFocusBK;
	return;
}

//析构函数
CSkinEditEx::~CSkinEditEx()
{
}

//设置颜色
VOID CSkinEditEx::SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorad)
{
	//设置颜色
	m_crEnableBK=crEnableBK;
	m_crEnableText=crEnableText;
	m_crEnableBorad=crEnableBorad;

	//创建画刷
	m_brEnable.DeleteObject();
	m_brEnable.CreateSolidBrush(m_crEnableBK);

	//更新界面
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//设置颜色
VOID CSkinEditEx::SetDisableColor(COLORREF crDisableText, COLORREF crDisableBK, COLORREF crDisableBorad)
{
	//设置颜色
	m_crDisableBK=crDisableBK;
	m_crDisableText=crDisableText;
	m_crDisableBorad=crDisableBorad;

	//创建画刷
	m_brDisable.DeleteObject();
	m_brDisable.CreateSolidBrush(m_crDisableBK);

	//更新界面
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//重画消息
VOID CSkinEditEx::OnNcPaint()
{
	//状态变量
	bool bDisable=(IsWindowEnabled()==FALSE);
	COLORREF crColorBK=(bDisable==false)?m_crEnableBK:m_crDisableBK;
	COLORREF crColorBorad=(bDisable==false)?m_crEnableBorad:m_crDisableBorad;

	//绘画边框
	CClientDC ClientDC(this);
	DrawControlView(&ClientDC,crColorBorad,crColorBK);

	return;
}

//绘画控件
HBRUSH CSkinEditEx::CtlColor(CDC * pDC, UINT nCtlColor)
{
	//设置环境
	if (IsWindowEnabled()==FALSE)
	{
		//禁用状态
		pDC->SetBkColor((m_crDisableBK==CLR_INVALID)?m_SkinAttribute.m_crNoFocusTX:m_crDisableBK);
		pDC->SetTextColor((m_crDisableText==CLR_INVALID)?m_SkinAttribute.m_crNoFocusTX:m_crDisableText);
		return (m_brDisable.GetSafeHandle()==NULL)?m_SkinAttribute.m_brDisbale:m_brDisable;
	}
	else
	{
		//启用状态
		pDC->SetBkColor((m_crEnableBK==CLR_INVALID)?m_SkinAttribute.m_crFocusBK:m_crEnableBK);
		pDC->SetTextColor((m_crEnableText==CLR_INVALID)?m_SkinAttribute.m_crFocusTX:m_crEnableText);
		return (m_brEnable.GetSafeHandle()==NULL)?m_SkinAttribute.m_brDisbale:m_brEnable;
	}

	return NULL;
}