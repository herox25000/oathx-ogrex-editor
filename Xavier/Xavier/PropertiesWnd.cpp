#include "stdafx.h"
#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Xavier.h"
#include "OgreAppEdit.h"

using namespace Ogre;

#ifndef SetAlpha
#define SetAlpha(col,a)			(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#endif

#ifndef	GetAlpha
#define GetAlpha(argb)			((BYTE)(((DWORD)(argb))>>24))
#endif

#define ARGBNORMAL(a, r, g, b)	(((DWORD)(a*255.0f)<<24)|((DWORD)(r*255.0f)<<16)|((DWORD)(g*255.0f)<<8)|((BYTE)(b*255.0f)))

#define GetB(argb)				((BYTE)(argb))
#define GetG(argb)				((BYTE)(((WORD)(argb))>>8))
#define GetR(argb)				((BYTE)((((DWORD)(argb))>>16) & 0xff))


#define SetB(col,r)				(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SetG(col,g)				(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SetR(col,b)				(((col) & 0xFFFFFF00) + DWORD(b))


#define NormalValue(a)	(a/255.0f)
/**
 *
 * \return 
 */
CPropertiesWnd::CPropertiesWnd() : m_pSelectEditor(NULL)
{
}

/**
 *
 * \return 
 */
CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SELECT_EDITOR,			&CPropertiesWnd::OnSelectEditor)
	ON_COMMAND(ID_EXPAND_ALL,				OnExpandAllProperties)
	//ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL,		OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES,			OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	//ON_COMMAND(ID_PROPERTIES1,				OnProperties1)
	//ON_UPDATE_COMMAND_UI(ID_PROPERTIES1,	OnUpdateProperties1)
	//ON_COMMAND(ID_PROPERTIES2,				OnProperties2)
	//ON_UPDATE_COMMAND_UI(ID_PROPERTIES2,	OnUpdateProperties2)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/**
 *
 */
void	CPropertiesWnd::AdjustLayout()
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
int		CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
void	CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
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
CMFCPropertyGridProperty*	CPropertiesWnd::CreateProperty(DWORD dwColour, LPCTSTR lpszGroupName, 
															   LPCTSTR lpszName, LPCTSTR lpszHelp)
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszGroupName);
	if (pGroup != NULL)
	{
		CMFCPropertyGridColorProperty* gp = new CMFCPropertyGridColorProperty(
			lpszGroupName, 
			(_variant_t)dwColour, 
			NULL, 
			lpszHelp
			);
		gp->EnableOtherButton(_T("其他..."));
		gp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));

		pGroup->Expand();
		pGroup->AddSubItem(gp);

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
CMFCPropertyGridProperty*	CPropertiesWnd::CreateProperty(float fValue, LPCTSTR lpszName, LPCTSTR lpszHelp, BOOL bEnable,
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
LRESULT	CPropertiesWnd::OnSelectEditor(WPARAM wParam, LPARAM lParam)
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
					Ogre::ColourValue backgroud;
					m_pSelectEditor->getPropertyValue(it->second->getName(), backgroud);
					
					ARGB argb = backgroud.getAsARGB();
					m_wPropList.AddProperty(
						CreateProperty(RGB(GetR(argb), GetG(argb), GetB(argb)), it->second->getName().c_str(), it->second->getName().c_str(), 
						it->second->getDescribe().c_str())
						);

					m_pSelectEditor->subscribeEvent(PropertySet::EventValueChanged, Event::Subscriber(&CPropertiesWnd::OnValueChanged, this));

				}
				break;
			case PROPERTY_VECTOR2:
				{
					Vector2 vSize;
					m_pSelectEditor->getPropertyValue(it->second->getName(), vSize);
					
					m_wPropList.AddProperty(
						CreateProperty(vSize.x, it->second->getName().c_str(), it->second->getDescribe().c_str(), NULL)
						);
					m_wPropList.AddProperty(
						CreateProperty(vSize.y, it->second->getName().c_str(), it->second->getDescribe().c_str(), NULL)
						);
				}
				break;
			case PROPERTY_UNSIGNED_INT:
				{
					unsigned int nValue;
					m_pSelectEditor->getPropertyValue(it->second->getName(), nValue);

					m_wPropList.AddProperty(
						CreateProperty((float)nValue, it->second->getName().c_str(), it->second->getDescribe().c_str(), FALSE, NULL)
						);
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
LRESULT	CPropertiesWnd::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{
	if (m_pSelectEditor != NULL)
	{
		CMFCPropertyGridProperty* pProperty = (CMFCPropertyGridProperty*)(lParam);
		if (pProperty != NULL)
		{
			TKLogEvent(pProperty->GetName());

			COleVariant backgroud = pProperty->GetValue();
			ColourValue clr;
			clr.setAsARGB(SetAlpha(backgroud.uintVal,255));
			m_pSelectEditor->setPropertyValue(pProperty->GetName(), clr);
		}
	}

	return 0;
}

bool	CPropertiesWnd::OnValueChanged(const EventArgs& args)
{
	const PropertyEventArgs& evt = static_cast<const PropertyEventArgs&>(args);
	if (m_pSelectEditor != NULL)
	{
		ViewPortEditor* pEditor = static_cast<ViewPortEditor*>(m_pSelectEditor);
		pEditor->getViewPort()->setBackgroundColour(any_cast<ColourValue>(evt.pProperty->getValue()));
		//m_pSelectEditor->setPropertyValue(evt.pProperty->getName(), evt.pProperty->getValue());
	}

	return 0;
}

/**
 *
 */
void	CPropertiesWnd::OnExpandAllProperties()
{
	m_wPropList.ExpandAll();
}


/**
 *
 */
void	CPropertiesWnd::OnSortProperties()
{
	m_wPropList.SetAlphabeticMode(!m_wPropList.IsAlphabeticMode());
}

/**
 *
 * \param pCmdUI 
 */
void	CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wPropList.IsAlphabeticMode());
}


/**
 *
 */
void	CPropertiesWnd::InitPropList()
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
void	CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wPropList.SetFocus();
}

/**
 *
 * \param uFlags 
 * \param lpszSection 
 */
void	CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

/**
 *
 */
void	CPropertiesWnd::SetPropListFont()
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
