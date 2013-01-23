#include "stdafx.h"
#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "XavierEditor.h"
#include "EditorTool.h"
#include "EditorToolManager.h"

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

		CMFCPropertyGridProperty* x = new CMFCPropertyGridProperty("x", 
			(_variant_t)vPos.x, 
			NULL,
			NULL);
		
		CMFCPropertyGridProperty* y = new CMFCPropertyGridProperty("y", 
			(_variant_t)vPos.y, 
			NULL,
			NULL);
		
		CMFCPropertyGridProperty* z = new CMFCPropertyGridProperty("z", 
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
void	CPropertiesWnd::CreateToolProperty(Ogre::EditorTool* pTool)
{
	// 获取属性迭代器
	HashPropertyIter hash_property_iter = pTool->getHashPropertyIter();
	
	// 创建属性列表
	for (HashPropertyIter::iterator it=hash_property_iter.begin();
		it!=hash_property_iter.end(); it++)
	{
		String name = it->second->getName();

		switch (it->second->getType())
		{
		case PVT_UNSIGNED_SHORT:
			{
				uint16 val = any_cast<uint16>(it->second->getValue());
				m_wndPropList.AddProperty(CreateProperty<uint16>(name.c_str(), val, it->second->getDescribe().c_str(), 
					it->second->canWrite(), NULL));
			}
			break;
		case PVT_REAL:
			{
				Real val = any_cast<Real>(it->second->getValue());
				m_wndPropList.AddProperty(CreateProperty<Real>(name.c_str(), val, it->second->getDescribe().c_str(), 
					it->second->canWrite(), NULL));
			}
			break;
		case PVT_COLOUR:
			{
				// 转换颜色
				ColourValue clr = any_cast<ColourValue>(it->second->getValue());

				ARGB argb = clr.getAsARGB();
				m_wndPropList.AddProperty(CreateColourValueProperty(argb, clr.a, name.c_str(), name.c_str(), 
					it->second->getDescribe().c_str()));
			}
			break;
		case PVT_STRING:
			{
				String val = any_cast<String>(it->second->getValue());
				m_wndPropList.AddProperty(CreateProperty<LPCTSTR>(name.c_str(), val.c_str(), it->second->getDescribe().c_str(),
					it->second->canWrite(), NULL));
			}
			break;
		case PVT_VECTOR3:
			{
				Vector3 val = any_cast<Vector3>(it->second->getValue());
				m_wndPropList.AddProperty(CreateVector3ValueProperty( val, name.c_str(), it->second->getDescribe().c_str()));
			}
			break;
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
		EditorTool* pTool = EditorToolManager::getSingleton().getEditorTool(evt->Name);
		if (pTool)
		{
			// 获取当前选择的编辑器
			EditorTool* pSelect = EditorToolManager::getSingleton().getSelectEditorTool();
			if (pSelect != pTool)
			{
				EditorToolManager::getSingleton().setSelectEditorTool(pTool);

				// 清空属性
				ClearProperty();
				// 创建属性
				CreateToolProperty(pTool);
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
	EditorTool* pSelectTool = EditorToolManager::getSingleton().getSelectEditorTool();
	if (pSelectTool == NULL)
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
				pSelectTool->OnPropertyChanged(parentName, typeName, Any(oldValue.uintVal), PVT_UNSIGNED_INT);
			}
			break;
		case VT_R4:
			{
				pSelectTool->OnPropertyChanged(parentName, typeName, Any(oldValue.fltVal), PVT_REAL);
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