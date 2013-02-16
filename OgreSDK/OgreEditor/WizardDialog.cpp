#include "stdafx.h"
#include "OgreEditor.h"
#include "WizardDialog.h"
#include "MainFrm.h"
#include "FolderDialog.h"

IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

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
void CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CWizardDialog::OnBnClickedButtonPath)
	ON_BN_CLICKED(IDOK, &CWizardDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWizardDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


/**
 *
 * \return 
 */
BOOL CWizardDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

/**
 *
 */
void CWizardDialog::OnBnClickedButtonPath()
{
	if (CFolderDialog::GetFolder(m_Path))
	{
		SetDlgItemText(IDC_EDIT_PATH, m_Path);
	}
}

/**
 *
 */
void CWizardDialog::OnBnClickedOk()
{
	GetDlgItemText(IDC_EDIT_PATH, m_Path);
	GetDlgItemText(IDC_EDIT_NAME, m_Name);

	// get root plug
	EditorPlugin* pRootPlugin = EditorPluginManager::getSingletonPtr()->getRootPlugin();
	if (pRootPlugin)
	{
		// modify the root plug name
		pRootPlugin->setName(m_Name.GetBuffer());

		// create scene mananegr plugin
		EditorPluginFactory* pSceneFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_SCENEMANAGER);
		if (pSceneFactory)
		{
			SEditorPluginSceneManagerAdp adp;
			adp.pluginName			= CPN::EDITOR_SCENEPLUGIN_NAME;
			adp.typeMask			= ST_EXTERIOR_FAR;
			adp.fogMode				= FOG_LINEAR;
			adp.clrFog				= ColourValue(1.0f, 1.0f, 0.8f);
			adp.expDensity			= 0.001;
			adp.linearStart			= 15;
			adp.linearEnd			= 500;
			adp.clrAmbientLight		= ColourValue::White;

			// add to root plugin
			pSceneFactory->createPlugin(adp, pRootPlugin);
		}

		// create viewport and camera
		EditorPluginFactory* pViewportFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_VIEWPORT);
		if (pViewportFactory)
		{
			SEditorPluginViewportAdp adp;
			adp.pluginName					= CPN::EDITOR_VIEWPORT;
			adp.background					= ColourValue::Black;

			// camera param
			adp.cameraAdp.pluginName		= CPN::EDITOR_MAIN_CAMER;
			adp.cameraAdp.vPos				= Vector3(0, 5, 5);
			adp.cameraAdp.q					= Quaternion::IDENTITY;
			adp.cameraAdp.fFarClipDistance	= 50000.0f;
			adp.cameraAdp.fNearClipDistance	= 0.1f;
			adp.cameraAdp.nQueryFlags		= 0;
			adp.cameraAdp.fFov				= 1.0f;

			// add to root plugin
			pViewportFactory->createPlugin(adp, pRootPlugin);
		}

		// sending the project to create the message
		CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
		if (pMainFrame != NULL)
		{
			wmProjectCreated pc;
			strcpy(pc.Path, m_Path.GetBuffer());
			strcpy(pc.Name, m_Name.GetBuffer());

			// 通知文件窗口
			::SendMessage(pMainFrame->GetActiveView()->m_hWnd,
				WM_WIZARD_FNISHED, (WPARAM)&pc, NULL);
		}
	}

	OnOK();
}

/**
 *
 */
void CWizardDialog::OnBnClickedCancel()
{
	OnCancel();
}
