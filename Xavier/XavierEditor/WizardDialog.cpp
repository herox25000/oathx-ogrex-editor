#include "stdafx.h"
#include "XavierEditor.h"
#include "WizardDialog.h"
#include "XavierEditorInclude.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CWizardDialog, CDialog)

CWizardDialog::CWizardDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDialog::IDD, pParent)
{

}

CWizardDialog::~CWizardDialog()
{
}

void CWizardDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWizardDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CWizardDialog::OnBnClickedOk)
END_MESSAGE_MAP()

void CWizardDialog::OnBnClickedOk()
{
	EditorPluginFactory* pSceneFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_SCENEMANAGER);
	if (pSceneFactory)
	{
		SEditorPluginSceneManagerAdp adp;
		adp.pluginName			= EDITOR_SCENEPLUGIN_NAME;
		adp.typeMask			= ST_EXTERIOR_FAR;
		adp.fogMode				= FOG_NONE;
		adp.clrFog				= ColourValue::White;
		adp.expDensity			= 0.001;
		adp.linearStart			= 0.0;
		adp.linearEnd			= 1.0;

		pSceneFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->getRootPlugin());
	}

	EditorPluginFactory* pCameraFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_CAMERA);
	if (pCameraFactory)
	{
		SEditorCamearAdp adp;
		adp.pluginName			= EDITOR_MIAN_CAMER;
		adp.vPos				= Vector3::ZERO;
		adp.q					= Quaternion::IDENTITY;
		adp.fFarClipDistance	= 0.1f;
		adp.fNearClipDistance	= 1000.0f;
		adp.nQueryFlags			= 0;
		adp.fFov				= 1.0f;

		pCameraFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->getRootPlugin());
	}
	
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		// 通知文件窗口
		::SendMessage(pMainFrame->GetActiveView()->m_hWnd,
			WM_WIZARD_FNISHED, NULL, NULL);
	}

	OnOK();
}
