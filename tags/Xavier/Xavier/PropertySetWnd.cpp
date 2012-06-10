#include "stdafx.h"
#include "PropertySetWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Xavier.h"
#include "XavierAppEditor.h"

using namespace Ogre;

/**
 *
 * \return 
 */
CPropertySetWnd::CPropertySetWnd()
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
		TRACE0("δ�ܴ���������� \n");
		return -1;
	}

	m_wObjectCombo.AddString(_T("Ӧ�ó���"));
	m_wObjectCombo.AddString(_T("���Դ���"));
	m_wObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
	m_wObjectCombo.SetCurSel(0);

	if (!m_wPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("δ�ܴ�����������\n");
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
CMFCPropertyGridProperty*	CPropertySetWnd::CreateColourValueProperty(DWORD dwColour, float fAlpha, 
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
		gp->EnableOtherButton(_T("����..."));
		gp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
		
		CMFCPropertyGridProperty* al = new CMFCPropertyGridProperty("alpha", 
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
 * \param nMode 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
//CMFCPropertyGridProperty*	CPropertySetWnd::CreatePlygonModeProperty(int nMode, LPCTSTR lpszName, LPCTSTR lpszHelp)
//{
//	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszName);
//	if (pGroup != NULL)
//	{
//		CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T(lpszName), _T("PM_SOLID"),
//			_T(lpszHelp));
//		pProp->AddOption(_T("PM_POINTS"));
//		pProp->AddOption(_T("PM_WIREFRAME"));
//		pProp->AddOption(_T("PM_SOLID"));
//		pProp->AllowEdit(FALSE);
//		pGroup->AddSubItem(pProp);
//
//		return pGroup;
//	}
//
//	return NULL;
//}

/**
 *
 * \param szWnd 
 * \param lpszGroupName 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
//CMFCPropertyGridProperty*	CPropertySetWnd::CreateProperty(float fValue, LPCTSTR lpszName, LPCTSTR lpszHelp, BOOL bEnable,
//														   CMFCPropertyGridProperty* pParent)
//{
//	CMFCPropertyGridProperty* pProperty = new CMFCPropertyGridProperty(lpszName, (_variant_t)fValue, NULL, NULL);
//	pProperty->Enable(bEnable);
//	if (pParent != NULL)
//		pParent->AddSubItem(pProperty);
//
//	return pProperty;
//}

/**
 *
 * \param bValue 
 * \param lpszName 
 * \param lpszHelp 
 * \return 
 */
//CMFCPropertyGridProperty*	CPropertySetWnd::CreateBoolProperty(bool bValue, LPCTSTR lpszName, LPCTSTR lpszHelp)
//{
//	CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(lpszName);
//	if (pGroup != NULL)
//	{
//		CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T(lpszName), _T("true"),
//			_T(lpszHelp));
//		pProp->AddOption(_T("true"));
//		pProp->AddOption(_T("false"));
//		pProp->AllowEdit(FALSE);
//		pGroup->AddSubItem(pProp);
//
//		return pGroup;
//	}
//
//	return NULL;
//}

/**
 *
 */
void	CPropertySetWnd::ClearProperty()
{
	// ��������
	SetPropListFont();

	// ���ԭ������
	m_wPropList.RemoveAll();
	m_wPropList.EnableHeaderCtrl(FALSE);
	m_wPropList.EnableDescriptionArea();
	m_wPropList.SetVSDotNetLook();
	m_wPropList.MarkModifiedProperties();
}

/**
 *
 * \param pTool 
 */
void	CPropertySetWnd::CreateToolProperty(XavierEditor* pTool)
{
	// ��ȡ���Ե�����
	HashPropertyIter hash_property_iter = pTool->getHashPropertyIter();
	
	// ���������б�
	for (HashPropertyIter::iterator it=hash_property_iter.begin();
		it!=hash_property_iter.end(); it++)
	{
		String name = it->second->getName();

		switch (it->second->getType())
		{
		case PVT_COLOUR:
			{
				// ת����ɫ
				ColourValue clr = any_cast<ColourValue>(it->second->getValue());

				ARGB argb = clr.getAsARGB();
				m_wPropList.AddProperty(CreateColourValueProperty(argb, clr.a, name.c_str(), name.c_str(), 
					it->second->getDescribe().c_str()));
			}
			break;
		}
	}

	m_wPropList.ExpandAll();
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
		// ��ȥѡ��ı༭��
		XavierEditor* pSelectTool = XavierEditorManager::getSingleton().getTool(
			evt->Name
			);
		if (pSelectTool)
		{
			// ��ȡ��ǰѡ��ı༭��
			XavierEditor* pCurrentTool = XavierEditorManager::getSingleton().getCurrentTool();
			if (pCurrentTool != pSelectTool)
			{
				XavierEditorManager::getSingleton().setCurrentTool(
					pSelectTool
					);
				
				// �������
				ClearProperty();

				// �����༭��������
				CreateToolProperty(pSelectTool);
			}
		}
		//BaseEditor* pSelect = AppEdit::getSingletonPtr()->getEditor(evt->Name);
		//if (m_pSelectEditor != pSelect)
		//{
		//	m_pSelectEditor = pSelect;
		//	TKLogEvent("��ѡ��༭�� " + m_pSelectEditor->getTypeName());
		//}
	}

	//if (m_pSelectEditor != NULL)
	//{
	//	SetPropListFont();

	//	m_wPropList.RemoveAll();
	//	m_wPropList.EnableHeaderCtrl(FALSE);
	//	m_wPropList.EnableDescriptionArea();
	//	m_wPropList.SetVSDotNetLook();
	//	m_wPropList.MarkModifiedProperties();

	//	HashProperty& py = m_pSelectEditor->getHashProperty();
	//	for (HashProperty::iterator it=py.begin();
	//		it!=py.end(); it++)
	//	{
	//		String name = it->second->getName();
	//		String help = it->second->getDescribe();

	//		switch (it->second->getType())
	//		{
	//		case PROPERTY_COLOUR:
	//			{
	//				ARGB argb;
	//				m_pSelectEditor->getPropertyValue(name, argb);
	//				
	//				m_wPropList.AddProperty(
	//					CreateColourValueProperty(argb, GetAlpha(argb), name.c_str(), name.c_str(), help.c_str())
	//					);
	//			}
	//			break;
	//		case PROPERTY_POLYGONMODE:
	//			{
	//				PolygonMode mode;
	//				m_pSelectEditor->getPropertyValue(name, mode);
	//				
	//				m_wPropList.AddProperty(
	//					CreatePlygonModeProperty(mode, name.c_str(), help.c_str())
	//					);
	//			}
	//			break;
	//		case PROPERTY_VECTOR2:
	//			{
	//				Vector2 vSize;
	//				m_pSelectEditor->getPropertyValue(name, vSize);
	//			}
	//			break;
	//		case PROPERTY_INT:
	//			{

	//			}
	//			break;
	//		case PROPERTY_BOOL:
	//			{
	//				bool bValue;
	//				m_pSelectEditor->getPropertyValue(name, bValue);

	//				m_wPropList.AddProperty(
	//					CreateBoolProperty(bValue, name.c_str(), help.c_str())
	//					);
	//			}
	//			break;
	//		case PROPERTY_UNSIGNED_INT:
	//			{

	//			}
	//			break;
	//		}
	//	}

	//	m_wPropList.ExpandAll();
	//}

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
	//if (m_pSelectEditor != NULL)
	//{
	//	CMFCPropertyGridProperty* pProperty = (CMFCPropertyGridProperty*)(lParam);
	//	if (pProperty != NULL)
	//	{
	//		//TKLogEvent(pProperty->GetName());
	//		String name = _T(pProperty->GetName());

	//		COleVariant oleValue = pProperty->GetValue();
	//		switch(oleValue.vt)
	//		{
	//			// nothing
	//		case VT_EMPTY: 
	//			break;
	//			// SQL style Null
	//		case VT_NULL: 
	//			break;
	//			// 2 byte signed int
	//		case VT_I2: 
	//			break;
	//			// 4 byte signed int
	//		case VT_I4:
	//			{
	//				// mfc bug? ���������������һ���޷��ŵģ�ΪʲôҪ�����ӽ���Ϊ�з��ŵģ�����
	///*				if (name == "Background")
	//					m_pSelectEditor->setPropertyValue(name, (UINT)(oleValue.intVal));*/
	//			}
	//			break;
	//			// 4 byte real
	//		case VT_R4:
	//			break;
	//			// 8 byte real
	//		case VT_R8:
	//			break;
	//			// True=-1, False=0
	//		case VT_BOOL:
	//			break;
	//			// signed char
	//		case VT_I1:
	//			break;
	//			// unsigned char
	//		case VT_UI1:
	//			break;
	//			// unsigned short
	//		case VT_UI2:
	//			break;
	//			// unsigned long
	//		case VT_UI4:
	//			break;
	//			// signed machine int
	//		case VT_INT:
	//			break;
	//			// unsigned machine int
	//		case VT_UINT:
	//			{
	//				//m_pSelectEditor->setPropertyValue(name, oleValue.uintVal);
	//			}
	//			break;
	//		case VT_BSTR:
	//			{
	//			/*	CString vtBSTR(_T(oleValue.bstrVal));
	//				if (vtBSTR == "PM_POINTS")
	//				{
	//					m_pSelectEditor->setPropertyValue(name, PM_POINTS);
	//					return 0;
	//				}

	//				if (vtBSTR == "PM_WIREFRAME")
	//				{
	//					m_pSelectEditor->setPropertyValue(name, PM_WIREFRAME);
	//					return 0;
	//				}

	//				if (vtBSTR == "PM_SOLID")
	//				{
	//					m_pSelectEditor->setPropertyValue(name, PM_SOLID);
	//					return 0;
	//				}
	//				
	//				if (vtBSTR == "true")
	//				{
	//					m_pSelectEditor->setPropertyValue(name, true);
	//					return 0;
	//				}

	//				if (vtBSTR == "false")
	//				{
	//					m_pSelectEditor->setPropertyValue(name, false);
	//					return 0;
	//				}*/
	//			}
	//			break;
	//		}
	//	}
	//}

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

	//CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("���"));

	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("��ά���"), (_variant_t) false, _T("ָ�����ڵ����岻ʹ�ô��壬���ҿؼ���ʹ����ά�߿�")));

	//CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�߿�"), _T("Dialog Frame"), _T("����֮һ: ��(None)��ϸ(Thin)���ɵ�����С(Resizable)���Ի������(Dialog Frame)"));
	//pProp->AddOption(_T("None"));
	//pProp->AddOption(_T("Thin"));
	//pProp->AddOption(_T("Resizable"));
	//pProp->AddOption(_T("Dialog Frame"));
	//pProp->AllowEdit(FALSE);

	//pGroup1->AddSubItem(pProp);
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("����"), (_variant_t) _T("����"), _T("ָ�����ڱ���������ʾ���ı�")));

	//m_wPropList.AddProperty(pGroup1);

	//CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("���ڴ�С"), 0, TRUE);

	//pProp = new CMFCPropertyGridProperty(_T("�߶�"), (_variant_t) 250l, _T("ָ�����ڵĸ߶�"));
	//pProp->EnableSpinControl(TRUE, 50, 300);
	//pSize->AddSubItem(pProp);

	//pProp = new CMFCPropertyGridProperty( _T("���"), (_variant_t) 150l, _T("ָ�����ڵĿ��"));
	//pProp->EnableSpinControl(TRUE, 50, 200);
	//pSize->AddSubItem(pProp);

	//m_wPropList.AddProperty(pSize);

	//CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("����"));

	//LOGFONT lf;
	//CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	//font->GetLogFont(&lf);

	//lstrcpy(lf.lfFaceName, _T("����, Arial"));

	//pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("����"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("ָ�����ڵ�Ĭ������")));
	//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ʹ��ϵͳ����"), (_variant_t) true, _T("ָ������ʹ�á�MS Shell Dlg������")));

	//m_wPropList.AddProperty(pGroup2);

	//CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("����"));
	//pProp = new CMFCPropertyGridProperty(_T("(����)"), _T("Ӧ�ó���"));
	//pProp->Enable(FALSE);
	//pGroup3->AddSubItem(pProp);

	//CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("������ɫ"), RGB(210, 192, 254), NULL, _T("ָ��Ĭ�ϵĴ�����ɫ"));
	//pColorProp->EnableOtherButton(_T("����..."));
	//pColorProp->EnableAutomaticButton(_T("Ĭ��"), ::GetSysColor(COLOR_3DFACE));
	//pGroup3->AddSubItem(pColorProp);

	//static TCHAR BASED_CODE szFilter[] = _T("ͼ���ļ�(*.ico)|*.ico|�����ļ�(*.*)|*.*||");
	//pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("ͼ��"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("ָ������ͼ��")));

	//pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("�ļ���"), _T("c:\\")));

	//m_wPropList.AddProperty(pGroup3);

	//CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("��νṹ"));

	//CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("��һ���Ӽ�"));
	//pGroup4->AddSubItem(pGroup41);

	//CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("�ڶ����Ӽ�"));
	//pGroup41->AddSubItem(pGroup411);

	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 1"), (_variant_t) _T("ֵ 1"), _T("��Ϊ˵��")));
	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 2"), (_variant_t) _T("ֵ 2"), _T("��Ϊ˵��")));
	//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("�� 3"), (_variant_t) _T("ֵ 3"), _T("��Ϊ˵��")));

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
