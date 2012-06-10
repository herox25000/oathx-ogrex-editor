#include "stdafx.h"
#include "Xavier.h"
#include "WizardDialog.h"
#include "FolderDialog.h"
#include "MainFrm.h"
#include "XavierAppEditor.h"

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

	m_cbSceneTypeMask.SetCurSel(3);

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
		// ������б༭����
		XavierEditorManager::getSingleton().clearTool();
		
		// ����ռ�༭����
		XavierEditorFactory* pWorldSpaceFactory = XavierEditorManager::getSingleton().getEditorFactory(
			XavierWorldSpaceEditorFactory::FACTORY_NAME
			);
		if (pWorldSpaceFactory)
		{
			SWorldSpaceServerAdp adp;
			adp.typeName			= SERVER_WORLDSPACE;
			adp.name				= XAVIER_WORLDSPACE;
			adp.clrAmbientLight		= ColourValue(0.5, 0.5, 0.5, 0.5);
			adp.typeMask			= GetSceneTypeMask(m_typeMask);
			
			XavierEditorManager::getSingleton().addTool(pWorldSpaceFactory->create(adp));
		}

		// ������༭����
		XavierEditorFactory* pCameraFactory = XavierEditorManager::getSingleton().getEditorFactory(
			XavierCameraEditorFactory::FACTORY_NAME
			);
		if (pCameraFactory)
		{
			SSdkCameraServerAdp adp;
			adp.depServerName		= SERVER_WORLDSPACE;
			adp.typeName			= SERVER_SDKCAMERA;
			adp.name				= XAVIER_SDKCAMERA;
			adp.nMode				= CS_FREELOOK;
			adp.vPos				= Vector3(0, 5, 5);
			adp.vLookAt				= Vector3(0,0,0);
			adp.fNearClipDistance	= 0.1f;
			adp.fFarClipDistance	= 3000;
			adp.fYaw				= 0;
			adp.fPitch				= 0;

			XavierEditorManager::getSingleton().addTool(pCameraFactory->create(adp));
		}

		// �ӿڱ༭��
		XavierEditorFactory* pViewportFactory = XavierEditorManager::getSingleton().getEditorFactory(
			XavierViewportEditorFactory::FACTORY_NAME
			);
		if (pViewportFactory)
		{
			SViewportServerAdp adp;
			adp.depServerName		= SERVER_SDKCAMERA;
			adp.typeName			= SERVER_SDKVIEWPORT;
			adp.background			= ColourValue(0,0,0,0);

			XavierEditorManager::getSingleton().addTool(pViewportFactory->create(adp));
		}

		// �����߸�༭��
		XavierEditorFactory* pBaseGridFactory = XavierEditorManager::getSingleton().getEditorFactory(
			XavierBaseGridEditorFactory::FACTORY_NAME
			);
		if (pBaseGridFactory)
		{
			SBaseGridServerAdp adp;
			adp.depServerName		= SERVER_WORLDSPACE;
			adp.typeName			= SERVER_BASEGRID;
			adp.fSize				= 1;
			adp.fWidth				= 32;
			adp.fDepth				= 32;

			XavierEditorManager::getSingleton().addTool(pBaseGridFactory->create(adp));		
		}

//
//		// ���ص��β��
//#ifdef _DEBUG
//		System::getSingleton().loadPlugin("Plugin_Terrain_d.dll");
//#else
//		System::getSingleton().loadPlugin("Plugin_Terrain.dll");
//#endif
//		ServerFactory* pTerrainGroupFactory = System::getSingleton().getServerFactory("Terrain/TerrainGroupServerFactory");
//		if (pTerrainGroupFactory != NULL)
//		{
//			STerrainGroupServerAdp adp;
//			adp.depServerName			= SERVER_WORLDSPACE;
//			adp.typeName				= SERVER_TERRAIN_GROUP;
//			adp.fWorldSize				= 1200.0f;
//			adp.nTerrainSize			= 513;
//			adp.vOrigin					= Vector3::ZERO;
//			adp.clrCompositeMapDiffuse	= ColourValue(1,1,1,1);
//			adp.fCompositeMapDistance	= 3000;
//			adp.fMaxPixelError			= 8;
//			adp.vLightMapDirection		= Vector3(0,0,0);
//			
//			System::getSingleton().addServer(pTerrainGroupFactory->createServer(adp));
//		}
//
//		ServerFactory* pTerrainPageFactory = System::getSingleton().getServerFactory("Terrain/TerrainPageServerFactory");
//		if (pTerrainPageFactory != NULL)
//		{
//			STerrainPageServerAdp adp;
//			adp.depServerName			= SERVER_TERRAIN_GROUP;
//			adp.typeName				= SERVER_TERRAIN_PAGE;
//			adp.nPageX					= 0;
//			adp.nPageY					= 0;
//			adp.nMinBatchSize			= 33;
//			adp.nMaxBatchSzie			= 65;
//			adp.diffuseTexture			= "dirt_grayrocky_diffusespecular.dds";
//			adp.normalheightTexture		= "dirt_grayrocky_normalheight.dds";
//			adp.fLayerWorldSize			= 80;
//
//			System::getSingleton().addServer(pTerrainPageFactory->createServer(adp));
//		}
//
//
		CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
		if (pMainFrame != NULL)
		{
			// ֪ͨ�ļ�����
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
