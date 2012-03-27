#include "stdafx.h"
#include "Xavier.h"
#include "WizardDialog.h"
#include "FolderDialog.h"
#include "MainFrm.h"
#include "OgreEditor.h"


IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

using namespace Ogre;

/**
 *
 * \param /* 
 * \return 
 */
CWizardDialog::CWizardDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CWizardDialog::~CWizardDialog()
{
}

/**
 *
 * \param pDX 
 */
void	CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SCENEMANAGER, m_cbSceneTypeMask);
}


BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDOK,							&CWizardDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL,						&CWizardDialog::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_SCENEMANAGER,	&CWizardDialog::OnCbnSelchangeComboScenemanager)
	ON_BN_CLICKED(IDC_BUTTON_FINDDIR,			&CWizardDialog::OnBnClickedButtonFinddir)
END_MESSAGE_MAP()

/**
 *
 * \param typeMask 
 * \return 
 */
Ogre::SceneTypeMask		GetSceneTypeMask(const CString& typeMask)
{
	if (typeMask == "ST_EXTERIOR_CLOSE")
		return ST_EXTERIOR_CLOSE;

	if (typeMask == "ST_EXTERIOR_FAR")
		return ST_EXTERIOR_FAR;

	if (typeMask == "ST_EXTERIOR_REAL_FAR")
		return ST_EXTERIOR_REAL_FAR;

	if (typeMask == "ST_INTERIOR")
		return ST_INTERIOR;

	return ST_GENERIC;
}

/**
 *
 * \return 
 */
BOOL	CWizardDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_cbSceneTypeMask.AddString("ST_GENERIC");
	m_cbSceneTypeMask.AddString("ST_EXTERIOR_CLOSE");
	m_cbSceneTypeMask.AddString("ST_EXTERIOR_FAR");
	m_cbSceneTypeMask.AddString("ST_EXTERIOR_REAL_FAR");
	m_cbSceneTypeMask.AddString("ST_INTERIOR");

	SetDlgItemText(IDC_EDIT_PROJECT_NAME, CString("aa"));
	SetDlgItemText(IDC_EDIT_PROJECT_DIR,CString("d:\\sda"));
	return TRUE;
}

/**
 *
 */
void	CWizardDialog::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_PROJECT_NAME,	m_csName);
	GetDlgItemText(IDC_EDIT_PROJECT_DIR,	m_csPath);
	if (m_csName.IsEmpty() || m_csPath.IsEmpty())
	{
		CString err;
		err.LoadString(IDS_STR_PROJECT_CREATE_ERR);

		TKLogEvent(err.GetBuffer(), LML_CRITICAL);
		AfxMessageBox(IDS_STR_PROJECT_CREATE_ERR);
	}
	else
	{
		// 清空原有的编辑工具
		AppEdit::getSingletonPtr()->clearPlugin();
		AppEdit::getSingletonPtr()->clearEditor();

		// 窗口编辑器
		BaseEditorFactory* pWindowFactory = AppEdit::getSingletonPtr()->getEditorFactory(FACTORY_RENDERWINDOW);
		if (pWindowFactory != NULL)
		{
			SRenderWindowCreateParams pm;
			pm.typeName				= EDIT_RENDERWINDOW;

			AppEdit::getSingleton().addEditor(pWindowFactory->create(&pm));
		}
		
		// 场景编辑器
		BaseEditorFactory* pSceneFactory = AppEdit::getSingletonPtr()->getEditorFactory(FACTORY_SCENEMANAGER);
		if (pSceneFactory != NULL)
		{
			SSceneManagerCreateParam cm;
			cm.sName				= NAME_SCENEMANAGER;
			cm.typeMask				= GetSceneTypeMask(m_typeMask);

			AppEdit::getSingletonPtr()->addEditor(pSceneFactory->create(&cm));
		}
		
		// 摄像机编辑器
		BaseEditorFactory* pCameraFactory = AppEdit::getSingletonPtr()->getEditorFactory(FACTORY_CAMERA);
		if (pCameraFactory != NULL)
		{
			SCameraCreateParam cm;
			cm.typeName				= EDIT_CAMERA;
			cm.vPos					= Vector3(0, 5, 5);
			cm.vLookAt				= Vector3(0,0,0);
			cm.fNearClipDistance	= 0.1;
			cm.fFarClipDistance		= 3000;
			cm.fYaw					= 0;
			cm.fPitch				= 0;

			AppEdit::getSingletonPtr()->addEditor(pCameraFactory->create(&cm));
		}
		
		// 视口编辑器
		BaseEditorFactory* pViewFactory	= AppEdit::getSingletonPtr()->getEditorFactory(FACTORY_VIEWPORT);
		if (pViewFactory != NULL)
		{
			SViewPortCreateParam cm;
			cm.background			= ColourValue(0,0,0,0);

			AppEdit::getSingletonPtr()->addEditor(pViewFactory->create(&cm));
		}
		
		// 文档编辑器
		BaseEditorFactory* pXMLSerFactory = AppEdit::getSingletonPtr()->getEditorFactory(FACTORY_XMLSERIALIZE);
		if (pXMLSerFactory != NULL)
		{
			SXMLSerializeCreateParam cm;
			cm.typeName				= EDIT_XMLSERIALIZE;

			AppEdit::getSingletonPtr()->addEditor(pXMLSerFactory->create(&cm));
		}

		// 格子编辑器
		BaseEditorFactory* pGirdEditor = AppEdit::getSingletonPtr()->getEditorFactory(FACTORY_GRID);
		if (pGirdEditor != NULL)
		{
			SGridCreateParam cm;
			cm.fSize				= 1;
			cm.fWidth				= 32;
			cm.fDepth				= 32;

			AppEdit::getSingletonPtr()->addEditor(pGirdEditor->create(&cm));
		}

		Ogre::AppEdit::getSingletonPtr()->loadPlugin("OgreTerrainEditor_d.dll");
		
		CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
		if (pMainFrame != NULL)
		{
			// 通知文件窗口
			::SendMessage(pMainFrame->GetFileView()->m_hWnd, WM_CREATE_FNISHED, NULL, NULL);
		}
	}

	OnOK();
}

/**
 *
 */
void	CWizardDialog::OnBnClickedCancel()
{

	OnCancel();
}

/**
 *
 */
void	CWizardDialog::OnCbnSelchangeComboScenemanager()
{
	m_cbSceneTypeMask.GetLBText(m_cbSceneTypeMask.GetCurSel(),
		m_typeMask);
}

/**
 *
 */
void	CWizardDialog::OnBnClickedButtonFinddir()
{
	if (CFolderDialog::GetFolder(m_csPath))
	{
		SetDlgItemText(IDC_EDIT_PROJECT_DIR, m_csPath);
	}
}
