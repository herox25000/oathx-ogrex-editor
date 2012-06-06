#include "stdafx.h"
#include "Xavier.h"
#include "WizardDialog.h"
#include "FolderDialog.h"
#include "MainFrm.h"
#include "OgreSSSDK.h"
#include "OgreTSSDK.h"


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
		System::getSingleton().clearServer();
		System::getSingleton().clearPlugin();
		
		ServerFactory* pWorldSpaceFactory = System::getSingleton().getServerFactory(WorldSpaceServerFactory::FactoryTypeName);
		if (pWorldSpaceFactory != NULL)
		{
			SWorldSpaceServerAdp adp;
			adp.typeName			= SERVER_WORLDSPACE;
			adp.name				= XAVIER_WORLDSPACE;
			adp.clrAmbientLight		= ColourValue(0.5, 0.5, 0.5, 0.5);
			adp.typeMask			= GetSceneTypeMask(m_typeMask);
			
			System::getSingleton().addServer(pWorldSpaceFactory->createServer(adp));
		}

		ServerFactory* pCameraFacotry = System::getSingleton().getServerFactory(CameraServerFactory::FactoryTypeName);
		if (pCameraFacotry != NULL)
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

			System::getSingleton().addServer(pCameraFacotry->createServer(adp));			
		}

		ServerFactory* pViewportFactory = System::getSingleton().getServerFactory(ViewportServerFactory::FactoryTypeName);
		if (pViewportFactory != NULL)
		{
			SViewportServerAdp adp;
			adp.depServerName		= SERVER_SDKCAMERA;
			adp.typeName			= SERVER_SDKVIEWPORT;
			adp.background			= ColourValue(0,0,0,0);

			System::getSingleton().addServer(pViewportFactory->createServer(adp));
		}

		ServerFactory* pBaseGridFactory = System::getSingleton().getServerFactory(BaseGridServerFactory::FactoryTypeName);
		if (pBaseGridFactory != NULL)
		{
			SBaseGridServerAdp adp;
			adp.depServerName		= SERVER_WORLDSPACE;
			adp.typeName			= SERVER_BASEGRID;
			adp.fSize				= 1;
			adp.fWidth				= 32;
			adp.fDepth				= 32;

			System::getSingleton().addServer(pBaseGridFactory->createServer(adp));
		}


		// 加载地形插件
#ifdef _DEBUG
		System::getSingleton().loadPlugin("Plugin_Terrain_d.dll");
#else
		System::getSingleton().loadPlugin("Plugin_Terrain.dll");
#endif
		ServerFactory* pTerrainGroupFactory = System::getSingleton().getServerFactory("Terrain/TerrainGroupServerFactory");
		if (pTerrainGroupFactory != NULL)
		{
			STerrainGroupServerAdp adp;
			adp.depServerName			= SERVER_WORLDSPACE;
			adp.typeName				= SERVER_TERRAIN_GROUP;
			adp.fWorldSize				= 1200.0f;
			adp.nTerrainSize			= 513;
			adp.vOrigin					= Vector3::ZERO;
			adp.clrCompositeMapDiffuse	= ColourValue(1,1,1,1);
			adp.fCompositeMapDistance	= 3000;
			adp.fMaxPixelError			= 8;
			adp.vLightMapDirection		= Vector3(0,0,0);
			
			System::getSingleton().addServer(pTerrainGroupFactory->createServer(adp));
		}

		ServerFactory* pTerrainPageFactory = System::getSingleton().getServerFactory("Terrain/TerrainPageServerFactory");
		if (pTerrainPageFactory != NULL)
		{
			STerrainPageServerAdp adp;
			adp.depServerName			= SERVER_TERRAIN_GROUP;
			adp.typeName				= SERVER_TERRAIN_PAGE;
			adp.nPageX					= 0;
			adp.nPageY					= 0;
			adp.nMinBatchSize			= 33;
			adp.nMaxBatchSzie			= 65;
			adp.diffuseTexture			= "dirt_grayrocky_diffusespecular.dds";
			adp.normalheightTexture		= "dirt_grayrocky_normalheight.dds";
			adp.fLayerWorldSize			= 80;

			System::getSingleton().addServer(pTerrainPageFactory->createServer(adp));
		}


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
