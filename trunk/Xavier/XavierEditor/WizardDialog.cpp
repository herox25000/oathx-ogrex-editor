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
	//EditorToolFactory* pWorldFactory = EditorToolFactoryManager::getSingletonPtr()->getEditorToolFactory(EDITOR_WORLD);
	//if (pWorldFactory)
	//{
	//	SEditorSceneManagerAdp adp;
	//	adp.worldName			= "App";
	//	adp.name				= EDITOR_TOOL_WORLD_NAME;
	//	adp.background			= ColourValue(0, 0, 0, 0);
	//	adp.typeMask			= ST_EXTERIOR_FAR;
	//	adp.clrAmbientLight		= ColourValue(0.5, 0.5, 0.5, 0.5);
	//	adp.vPos				= Vector3(0, 5, 5);
	//	adp.vLookAt				= Vector3(0,0,0);
	//	adp.fNearClipDistance	= 0.1f;
	//	adp.fFarClipDistance	= 3000;
	//	adp.fYaw				= 0;
	//	adp.fPitch				= 0;

	//	EditorToolManager::getSingletonPtr()->addEditorTool(pWorldFactory->createEditorTool(adp), NULL);
	//}

	//EditorToolFactory* pTerrainFactory = EditorToolFactoryManager::getSingletonPtr()->getEditorToolFactory(EDITOR_TERRAIN);
	//if (pTerrainFactory)
	//{
	//	SEditorTerrainAdp adp;
	//	adp.name					= EDITOR_TOOL_TERRAIN_NAME;
	//	adp.clrCompositeMapDiffuse	= ColourValue(1,1,1,1);
	//	adp.fCompositeMapDistance	= 3000;
	//	adp.fMaxPixelError			= 8;
	//	adp.fWorldSize				= 129;
	//	adp.nTerrainSize			= 129;
	//	adp.vOrigin					= Vector3::ZERO;
	//	adp.fInputScale				= 2;
	//	adp.nMinBatchSize			= 33;
	//	adp.nMaxBatchSize			= 65;
	//	adp.texture					= "desert_0_diffuse.png";

	//	EditorToolManager::getSingletonPtr()->addEditorTool(pTerrainFactory->createEditorTool(adp), NULL);
	//}

	//CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	//if (pMainFrame != NULL)
	//{
	//	// 通知文件窗口
	//	::SendMessage(pMainFrame->GetActiveView()->m_hWnd,
	//		WM_WIZARD_FNISHED, NULL, NULL);
	//}

	OnOK();
}
