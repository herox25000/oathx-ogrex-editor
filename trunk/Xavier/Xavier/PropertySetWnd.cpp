#include "stdafx.h"
#include "PropertySetWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Xavier.h"
#include "OgreAppEdit.h"

using namespace Ogre;

/**
 *
 * \return 
 */
CPropertySetWnd::CPropertySetWnd() : m_pSelectEditor(NULL)
{
}

/**
 *
 * \return 
 */
CPropertySetWnd::~CPropertySetWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertySetWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SELECT_EDITOR,			&CPropertySetWnd::OnSelectEditor)
	ON_COMMAND(ID_EXPAND_ALL,				OnExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES,			OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1,	OnUpdateBaseProperty)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2,	OnUpdateEventDefine)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/**
 *
 */
void	CPropertySetWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	m_wObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wObjectCombo.SetWindowPos(NULL, 
		rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);

	m_wToolBar.SetWindowPos(NULL, 
							rectClient.left,
							rectClient.top + cyCmb, 
							rectClient.Width(),
							cyTlb, 
							SWP_NOACTIVATE | SWP_NOZORDER);

	m_wPropList.SetWindowPos(NULL, rectClient.left, 
		rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), 
		SWP_NOACTIVATE | SWP_NOZORDER);
}

/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int		CPropertySetWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_wObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;
	}

	m_wObjectCombo.AddString(_T("应用程序"));
	m_wObjectCombo.AddString(_T("属性窗口"));
	m_wObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	m_wObjectCombo.SetCurSel(0);

	if (!m_wPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;
	}

	InitPropList();

	m_wToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE);
	m_wToolBar.CleanUpLockedImages();
	m_wToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE);

	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wToolBar.SetPaneStyle(m_wToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wToolBar.SetOwner(this);
	m_wToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();

	return 0;
}

/**
 *
 * \param nType 
 * \param cx 
 * \param cy 
 */
void	CPropertySetWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

/**
 *
 * \param dwColour 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertySetWnd::CreateColourValueProperty(UINT dwColour, UINT dwAlpha, 
																	   LPCTSTR lpszGroupName, LPCTSTR lpszName, LPCTSTR lpszHelp)
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszGroupName);
	if (pGroup != NULL)
	{
		CMFCPropertyGridColorProperty* gp = new CMFCPropertyGridColorProperty(
			lpszGroupName, 
			dwColour, 
			NULL, 
			lpszHelp
			);
		gp->EnableOtherButton(_T("其他..."));
		gp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
		
		CMFCPropertyGridProperty* pAlpha = new CMFCPropertyGridProperty("Alpha", (_variant_t)dwAlpha,  NULL, NULL);

		pGroup->Expand();
		pGroup->AddSubItem(gp);
		pGroup->AddSubItem(pAlpha);

		return pGroup;
	}

	return NULL;
}

/**
 *
 * \param nMode 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertySetWnd::CreatePlygonModeProperty(int nMode, LPCTSTR lpszName, LPCTSTR lpszHelp)
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszName);
	if (pGroup != NULL)
	{
		CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T(lpszName), _T("PM_SOLID"),
			_T("其中之一: 点(PM_POINTS)、线(PM_WIREFRAME)、面(PM_SOLID)"));
		pProp->AddOption(_T("PM_POINTS"));
		pProp->AddOption(_T("PM_WIREFRAME"));
		pProp->AddOption(_T("PM_SOLID"));
		pProp->AllowEdit(FALSE);
		pGroup->AddSubItem(pProp);

		return pGroup;
	}

	return NULL;
}

/**
 *
 * \param szWnd 
 * \param lpszGroupName 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertySetWnd::CreateProperty(float fValue, LPCTSTR lpszName, LPCTSTR lpszHelp, BOOL bEnable,
														   CMFCPropertyGridProperty* pParent)
{
	CMFCPropertyGridProperty* pProperty = new CMFCPropertyGridProperty(lpszName, (_variant_t)fValue, NULL, NULL);
	pProperty->Enable(bEnable);
	if (pParent != NULL)
		pParent->AddSubItem(pProperty);

	return pProperty;
}

/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LRESULT	CPropertySetWnd::OnSelectEditor(WPARAM wParam, LPARAM lParam)
{
	wmSelectEvent* evt = (wmSelectEvent*)(wParam);
	if (evt != NULL)
	{
		BaseEditor* pSelect = AppEdit::getSingletonPtr()->getEditor(evt->Name);
		if (m_pSelectEditor != pSelect)
			m_pSelectEditor = pSelect;
	}

	if (m_pSelectEditor != NULL)
	{
		SetPropListFont();

		m_wPropList.RemoveAll();
		m_wPropList.EnableHeaderCtrl(FALSE);
		m_wPropList.EnableDescriptionArea();
		m_wPropList.SetVSDotNetLook();
		m_wPropList.MarkModifiedProperties();

		HashProperty& py = m_pSelectEditor->getHashProperty();
		for (HashProperty::iterator it=py.begin();
			it!=py.end(); it++)
		{
			switch (it->second->getType())
			{
			case PROPERTY_COLOUR:
				{
					ARGB argb;
					m_pSelectEditor->getPropertyValue(it->second->getName(), argb);
					
					m_wPropList.AddProperty(
						CreateColourValueProperty(RGB(GetR(argb), GetG(argb), GetB(argb)), GetAlpha(argb),
						it->second->getName().c_str(), it->second->getName().c_str(), it->second->getDescribe().c_str())
						);
				}
				break;
			case PROPERTY_POLYGONMODE:
				{
					PolygonMode mode;
					m_pSelectEditor->getPropertyValue(it->second->getName(), mode);
					
					m_wPropList.AddProperty(
						CreatePlygonModeProperty(mode, it->second->getName().c_str(), it->second->getDescribe().c_str())
						);
				}
				break;
			case PROPERTY_VECTOR2:
				{
					Vector2 vSize;
					m_pSelectEditor->getPropertyValue(it->second->getName(), vSize);
				}
				break;
			case PROPERTY_INT:
				{

				}
				break;
			case PROPERTY_UNSIGNED_INT:
				{

				}
				break;
			}
		}

		m_wPropList.ExpandAll();
	}

	return 0;
}

/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LRESULT	CPropertySetWnd::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	if (m_pSelectEditor != NULL)
	{
		CMFCPropertyGridProperty* pProperty = (CMFCPropertyGridProperty*)(lParam);
		if (pProperty != NULL)
		{
			TKLogEvent(pProperty->GetName());

			COleVariant oleValue = pProperty->GetValue();
			switch(oleValue.vt)
			{
				// 变量未初始化
			case 0: 
				break;
				// 无有效数据
			case 1: 
				break;
				// 整数
			case 2: 
				break;
				// 长整数
			case 3:
				{
					m_pSelectEditor->setPropertyValue(pProperty->GetName(), oleValue.uintVal);
				}
				break;
			case 8:
				{
					CString val(_T(oleValue.bstrVal));
					if (val == "PM_POINTS")
					{
						m_pSelectEditor->setPropertyValue(pProperty->GetName(),PM_POINTS);
						return 0;
					}

					if (val == "PM_WIREFRAME")
					{
						m_pSelectEditor->setPropertyValue(pProperty->GetName(),PM_WIREFRAME);
						return 0;
					}

					if (val == "PM_SOLID")
					{
						m_pSelectEditor->setPropertyValue(pProperty->GetName(),PM_SOLID);
						return 0;
					}
				}
				break;
			}
		}
	}

	return 0;
}

/**
 *
 * \param pCmdUI 
 */
void	CPropertySetWnd::OnUpdateBaseProperty(CCmdUI* pCmdUI)
{

}

/**
 *
 * \param pCmdUI 
 */
void	CPropertySetWnd::OnUpdateEventDefine(CCmdUI* pCmdUI)
{

}


/**
 *
 */
void	CPropertySetWnd::OnExpandAllProperties()
{
	m_wPropList.ExpandAll();
}


/**
 *
 */
void	CPropertySetWnd::OnSortProperties()
{
	m_wPropList.SetAlphabeticMode(!m_wPropList.IsAlphabeticMode());
}

/**
 *
 * \param pCmdUI 
 */
void	CPropertySetWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wPropList.IsAlphabeticMode());
}


/**
 *
 */
void	CPropertySetWnd::InitPropList()
{
	SetPropListFont();

	m_wPropList.EnableHeaderCtrl(FALSE);
	m_wPropList.EnableDescriptionArea();
	m_wPropList.SetVSDotNetLook();
	m_wPropList.MarkModifiedProperties();

	//CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("外观"));

	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("三维外观"), (_variant_t) false, _T("指定窗口的字体不使用粗体，并且控件将使用三维边框")));

	//CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("边框"), _T("Dialog Frame"), _T("其中之一: 无(None)、细(Thin)、可调整大小(Resizable)、对话框外框(Dialog Frame)"));
	//pProp->AddOption(_T("None"));
	//pProp->AddOption(_T("Thin"));
	//pProp->AddOption(_T("Resizable"));
	//pProp->AddOption(_T("Dialog Frame"));
	//pProp->AllowEdit(FALSE);

	//pGroup1->AddSubItem(pProp);
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("标题"), (_variant_t) _T("关于"), _T("指定窗口标题栏中显示的文本")));

	//m_wPropList.AddProperty(pGroup1);

	//CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("窗口大小"), 0, TRUE);

	//pProp = new CMFCPropertyGridProperty(_T("高度"), (_variant_t) 250l, _T("指定窗口的高度"));
	//pProp->EnableSpinControl(TRUE, 50, 300);
	//pSize->AddSubItem(pProp);

	//pProp = new CMFCPropertyGridProperty( _T("宽度"), (_variant_t) 150l, _T("指定窗口的宽度"));
	//pProp->EnableSpinControl(TRUE, 50, 200);
	//pSize->AddSubItem(pProp);

	//m_wPropList.AddProperty(pSize);

	//CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("字体"));

	//LOGFONT lf;
	//CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	//font->GetLogFont(&lf);

	//lstrcpy(lf.lfFaceName, _T("宋体, Arial"));

	//pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("字体"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("指定窗口的默认字体")));
	//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("使用系统字体"), (_variant_t) true, _T("指定窗口使用“MS Shell Dlg”字体")));

	//m_wPropList.AddProperty(pGroup2);

	//CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("杂项"));
	//pProp = new CMFCPropertyGridProperty(_T("(名称)"), _T("应用程序"));
	//pProp->Enable(FALSE);
	//pGroup3->AddSubItem(pProp);

	//CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("窗口颜色"), RGB(210, 192, 254), NULL, _T("指定默认的窗口颜色"));
	//pColorProp->EnableOtherButton(_T("其他..."));
	//pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	//pGroup3->AddSubItem(pColorProp);

	//static TCHAR BASED_CODE szFilter[] = _T("图标文件(*.ico)|*.ico|所有文件(*.*)|*.*||");
	//pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("图标"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("指定窗口图标")));

	//pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("文件夹"), _T("c:\\")));

	//m_wPropList.AddProperty(pGroup3);

	//CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("层次结构"));

	//CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("第一个子级"));
	//pGroup4->AddSubItem(pGroup41);

	//CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("第二个子级"));
	//pGroup41->AddSubItem(pGroup411);

	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 1"), (_variant_t) _T("值 1"), _T("此为说明")));
	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 2"), (_variant_t) _T("值 2"), _T("此为说明")));
	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 3"), (_variant_t) _T("值 3"), _T("此为说明")));

	//pGroup4->Expand(FALSE);
	//m_wPropList.AddProperty(pGroup4);
}

/**
 *
 * \param pOldWnd 
 */
void	CPropertySetWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wPropList.SetFocus();
}

/**
 *
 * \param uFlags 
 * \param lpszSection 
 */
void	CPropertySetWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

/**
 *
 */
void	CPropertySetWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wPropList.SetFont(&m_fntPropList);
}
