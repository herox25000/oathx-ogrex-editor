#include "stdafx.h"
#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "XavierEditor.h"
#include "XavierEditorInclude.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/**
 *
 * \return 
 */
CPropertiesWnd::CPropertiesWnd()
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
	ON_MESSAGE(WM_SELECT_EDITOR,		&CPropertiesWnd::OnSelectEditor)
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

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

	m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
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

	// 创建组合:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}

	m_wndObjectCombo.AddString(_T("应用程序"));
	m_wndObjectCombo.AddString(_T("属性窗口"));
	m_wndObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

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
 */
void	CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

/**
 *
 * \param pCmdUI 
 */
void	CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* pCmdUI)
{
}

/**
 *
 */
void	CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

/**
 *
 * \param pCmdUI 
 */
void	CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

/**
 *
 */
void	CPropertiesWnd::OnProperties1()
{
	
}

/**
 *
 * \param pCmdUI
 */
void	CPropertiesWnd::OnUpdateProperties1(CCmdUI* pCmdUI)
{
	
}

/**
 *
 */
void	CPropertiesWnd::OnProperties2()
{
	
}

/**
 *
 * \param pCmdUI 
 */
void	CPropertiesWnd::OnUpdateProperties2(CCmdUI* pCmdUI)
{
	
}

/**
 *
 */
void	CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
}

/**
 *
 * \param pOldWnd 
 */
void	CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
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

	m_wndPropList.SetFont(&m_fntPropList);
}

/**
 *
 * \param dwColour 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertiesWnd::CreateColourValueProperty(DWORD dwColour, float fAlpha, 
																	   LPCTSTR lpszGroupName, LPCTSTR lpszName, LPCTSTR lpszHelp)
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszGroupName);
	if (pGroup != NULL)
	{
		CMFCPropertyGridColorProperty* gp = new CMFCPropertyGridColorProperty(
			"RGB", 
			dwColour, 
			NULL, 
			lpszHelp
			);
		gp->EnableOtherButton(_T("其他..."));
		gp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
		
		CMFCPropertyGridProperty* al = new CMFCPropertyGridProperty("Alpha", 
			(_variant_t)fAlpha, 
			NULL,
			NULL);

		pGroup->Expand();
		pGroup->AddSubItem(gp);
		pGroup->AddSubItem(al);
		
		return pGroup;
	}

	return NULL;
}

/**
 *
 * \param Ogre::PolygonMode 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertiesWnd::CreatePolygonValueProperty(LPCTSTR lpszName, Ogre::PolygonMode nMode,LPCTSTR lpszHelp)
{
	static const String PolygonModeString[] = 
	{
		/// Only points are rendered.
		"PM_POINTS",
		/// Wireframe models are rendered.
		"PM_WIREFRAME",
		/// Solid polygons are rendered.
		"PM_SOLID"
	};

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(lpszName, (_variant_t)PolygonModeString[nMode].c_str(),
		lpszHelp);
	if (pProp)
	{
		pProp->AddOption(PolygonModeString[0].c_str());
		pProp->AddOption(PolygonModeString[1].c_str());
		pProp->AddOption(PolygonModeString[2].c_str());
		pProp->AllowEdit(FALSE);

		return pProp;
	}
	
	return NULL;
}

/**
 *
 * \param lpszName 
 * \param fogMode 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertiesWnd::CreateFogModeValueProperty(LPCTSTR lpszName, Ogre::FogMode fogMode, LPCTSTR lpszHelp)
{
	static const String FogModeString[] = 
	{
		/// No fog. Duh.
		"FOG_NONE",
		/// Fog density increases  exponentially from the camera (fog = 1/e^(distance * density))
		"FOG_EXP",
		/// Fog density increases at the square of FOG_EXP, i.e. even quicker (fog = 1/e^(distance * density)^2)
		"FOG_EXP2",
		/// Fog density increases linearly between the start and end distances
		"FOG_LINEAR"
	};

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(lpszName, (_variant_t)FogModeString[fogMode].c_str(),
		lpszHelp);
	if (pProp)
	{
		pProp->AddOption(FogModeString[0].c_str());
		pProp->AddOption(FogModeString[1].c_str());
		pProp->AddOption(FogModeString[2].c_str());
		pProp->AddOption(FogModeString[3].c_str());
		pProp->AllowEdit(FALSE);

		return pProp;
	}

	return NULL;
}

/**
 *
 * \param lpszName 
 * \param q 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertiesWnd::CreateQuaternionValueProperty(LPCTSTR lpszName, Ogre::Quaternion q, LPCTSTR lpszHelp)
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszName);
	if (pGroup != NULL)
	{
		pGroup->SetDescription(lpszHelp);

		static const LPCTSTR QuaternionString[] = 
		{
			"w",
			"x",
			"y",
			"z",
		};

		CMFCPropertyGridProperty* w = new CMFCPropertyGridProperty(QuaternionString[0], 
			(_variant_t)q.w, 
			NULL,
			NULL);

		CMFCPropertyGridProperty* x = new CMFCPropertyGridProperty(QuaternionString[1], 
			(_variant_t)q.x, 
			NULL,
			NULL);

		CMFCPropertyGridProperty* y = new CMFCPropertyGridProperty(QuaternionString[2], 
			(_variant_t)q.y, 
			NULL,
			NULL);

		CMFCPropertyGridProperty* z = new CMFCPropertyGridProperty(QuaternionString[3], 
			(_variant_t)q.z, 
			NULL,
			NULL);

		pGroup->Expand();
		pGroup->AddSubItem(w);
		pGroup->AddSubItem(x);
		pGroup->AddSubItem(y);
		pGroup->AddSubItem(z);

		return pGroup;
	}

	return NULL;
}

/**
 *
 * \param vPos 
 * \param lpszGroupName 
 * \param lpszHelp 
 * \return 
 */
CMFCPropertyGridProperty*	CPropertiesWnd::CreateVector3ValueProperty(Ogre::Vector3 vPos, LPCTSTR lpszGroupName, LPCTSTR lpszHelp)
{
	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszGroupName);
	if (pGroup != NULL)
	{
		pGroup->SetDescription(lpszHelp);

		static const LPCTSTR Vector3String[] = 
		{
			"x",
			"y",
			"z",
		};

		CMFCPropertyGridProperty* x = new CMFCPropertyGridProperty(Vector3String[0], 
			(_variant_t)vPos.x, 
			NULL,
			NULL);
		
		CMFCPropertyGridProperty* y = new CMFCPropertyGridProperty(Vector3String[1], 
			(_variant_t)vPos.y, 
			NULL,
			NULL);
		
		CMFCPropertyGridProperty* z = new CMFCPropertyGridProperty(Vector3String[2], 
			(_variant_t)vPos.z, 
			NULL,
			NULL);
		
		pGroup->Expand();
		pGroup->AddSubItem(x);
		pGroup->AddSubItem(y);
		pGroup->AddSubItem(z);

		return pGroup;
	}

	return NULL;
}


/**
 *
 */
void	CPropertiesWnd::ClearProperty()
{
	// 设置字体
	SetPropListFont();

	// 清空原有属性
	m_wndPropList.RemoveAll();
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
}

/**
 *
 * \param pTool 
 */
void	CPropertiesWnd::CreatePluginProperty(Ogre::EditorPlugin* pPlugin)
{
	// 获取属性迭代器
	HashPropertyIter hashProperty = pPlugin->getHashPropertyIter();
	while( hashProperty.hasMoreElements() )
	{
		Property* pProperty = hashProperty.getNext();
		if (pProperty)
		{
			Any		anyValue	= pProperty->getValue();
			String	describe	= pProperty->getDescribe();
			String	name		= pProperty->getName();
			bool	bWrite		= pProperty->canWrite();

			switch( pProperty->getType() )
			{
			case PVT_USHORT:
				{
					uint16 val = any_cast<uint16>(anyValue);
					m_wndPropList.AddProperty(CreateProperty<uint16>(name.c_str(), val, describe.c_str(), 
						bWrite, NULL));
				}
				break;
			case PVT_INT:
				{
					int val = any_cast<int>(anyValue);
					m_wndPropList.AddProperty(CreateProperty<int>(name.c_str(), val, describe.c_str(), 
						bWrite, NULL));
				}
				break;
			case PVT_REAL:
				{
					Real val = any_cast<Real>(anyValue);
					m_wndPropList.AddProperty(CreateProperty<Real>(name.c_str(), val, describe.c_str(), 
						bWrite, NULL));
				}
				break;
			case PVT_COLOUR:
				{
					// 转换颜色
					ColourValue clr = any_cast<ColourValue>(anyValue);

					ARGB argb = clr.getAsARGB();
					m_wndPropList.AddProperty(CreateColourValueProperty(argb, clr.a, name.c_str(), name.c_str(), 
						describe.c_str()));
				}
				break;
			case PVT_STRING:
				{
					String val = any_cast<String>(anyValue);
					m_wndPropList.AddProperty(CreateProperty<LPCTSTR>(name.c_str(), val.c_str(), describe.c_str(),
						bWrite, NULL));
				}
				break;
			case PVT_VECTOR3:
				{
					Vector3 val = any_cast<Vector3>(anyValue);
					m_wndPropList.AddProperty(CreateVector3ValueProperty( val, name.c_str(), 
						describe.c_str()));
				}
				break;
			case PVT_POLYGONMODE:
				{
					PolygonMode val = any_cast<PolygonMode>(anyValue);
					m_wndPropList.AddProperty(CreatePolygonValueProperty(name.c_str(), val,
						describe.c_str()));
				}
				break;
			case PVT_QUATERNION:
				{
					Quaternion val = any_cast<Quaternion>(anyValue);
					m_wndPropList.AddProperty(CreateQuaternionValueProperty(name.c_str(), val,
						describe.c_str()));
				}
				break;
			case PVT_FOGMODE:
				{
					FogMode val = any_cast<FogMode>(anyValue);
					m_wndPropList.AddProperty(CreateFogModeValueProperty(name.c_str(), val,
						describe.c_str()));
				}
				break;
			}
		}
	}

	m_wndPropList.ExpandAll();
}

/**
 *
 * \param wParam 
 * \param lParam 
 * \return 
 */
LRESULT CPropertiesWnd::OnSelectEditor(WPARAM wParam, LPARAM lParam)
{
	wmSelectEvent* evt = (wmSelectEvent*)(wParam);
	if (evt != NULL)
	{
		// 后去选择的编辑器
		EditorPlugin* pPlugin = EditorPluginManager::getSingleton().findPlugin(evt->Name);
		if (pPlugin)
		{
			// 获取当前选择的编辑器
			EditorPlugin* pSelect = EditorPluginManager::getSingleton().getSelectPlugin();
			if (pSelect != pPlugin)
			{
				EditorPluginManager::getSingleton().setSelectPlugin(pPlugin);

				// 清空属性
				ClearProperty();
				// 创建属性
				CreatePluginProperty(pPlugin);
			}
		}
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
	EditorPlugin* pSelectPlugin = EditorPluginManager::getSingleton().getSelectPlugin();
	if (pSelectPlugin == NULL)
		return 0;

	CMFCPropertyGridProperty* pProperty = (CMFCPropertyGridProperty*)(lParam);
	if (pProperty != NULL)
	{
		String parentName;
		CMFCPropertyGridProperty* pParent = pProperty->GetParent();
		if (pParent)
			parentName = pParent->GetName();

		// 类型名称
		String typeName(_T(pProperty->GetName()));

		// 变量类型
		COleVariant oldValue = pProperty->GetValue();
		switch( oldValue.vt )
		{
		case VT_I4:
			{
				pSelectPlugin->OnPropertyChanged(parentName, typeName,
					Any(oldValue.uintVal), PVT_UINT);
			}
			break;
		case VT_R4:
			{
				pSelectPlugin->OnPropertyChanged(parentName, typeName,
					Any(oldValue.fltVal), PVT_REAL);
			}
			break;
		case VT_BSTR:
			{

			}
			break;
		}
	}

	return 0;
}