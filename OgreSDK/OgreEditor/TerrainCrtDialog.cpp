#include "stdafx.h"
#include "OgreEditor.h"
#include "TerrainCrtDialog.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CTerrainCrtDialog, CDialog)

/**
 *
 * \param  
 * \return 
 */
CTerrainCrtDialog::CTerrainCrtDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTerrainCrtDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CTerrainCrtDialog::~CTerrainCrtDialog()
{
}

/**
 *
 * \param pDX 
 */
void CTerrainCrtDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_TerrainSize);
}


BEGIN_MESSAGE_MAP(CTerrainCrtDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CTerrainCrtDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTerrainCrtDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


/**
 *
 * \return 
 */
BOOL CTerrainCrtDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_TerrainSize.AddString("65");
	m_TerrainSize.AddString("129");
	m_TerrainSize.AddString("257");
	m_TerrainSize.AddString("513");
	m_TerrainSize.SetCurSel(0);

	SetDlgItemText(IDC_EDIT_WORLDSIZE,  "1024");

	return TRUE;
}

/**
 *
 */
void CTerrainCrtDialog::OnBnClickedOk()
{

	CString worldSize;
	GetDlgItemText(IDC_EDIT_WORLDSIZE, worldSize);

	CString terrainSize;
	int nCurSel = m_TerrainSize.GetCurSel();
	m_TerrainSize.GetLBText(nCurSel, terrainSize);

	float	fWorldSize	= atof(worldSize.GetBuffer());
	int		nTerrainSize= atoi(terrainSize.GetBuffer());

	EditorPluginFactory* pTerrainFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_TERRAINGROUP);
	if (pTerrainFactory)
	{
		STerrainEditorAdp adp;
		adp.pluginName					= CPN::EDITOR_TERRAIN_GROUP;
		adp.fWorldSize					= fWorldSize;
		adp.nTerrainSize				= nTerrainSize;
		adp.nLightMapSize				= 1024;
		adp.nLayerBlendMapSize			= 1024;
		adp.nCompositeMapSize			= 1024;
		adp.clrCompositeMapDiffuse		= ColourValue::White;
		adp.fSkirtSize					= 4;
		adp.fCompositeMapDistance		= 2000;
		adp.fMaxPixelError				= 3;

		pTerrainFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->findPlugin(CPN::EDITOR_SCENE_MANAGER));
	}

	EditorPluginFactory* pPageFactory	= EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_TERRAINPAGE);
	if (pPageFactory)
	{
		STerrainPageEditorAdp adp;
		adp.nLayerCount					= 1;
		adp.tpl.fLayerWorldSize[0]		= 20.0f;
		adp.tpl.layerDiffuseTexture[0]	= "dirt_grayrocky_diffusespecular.dds";
		adp.tpl.layerNormalTexture[0]	= "dirt_grayrocky_normalheight.dds";
		adp.nMinBatchSize				= 33;
		adp.nMaxBatchSize				= 65;
		adp.nPageX						= 0;
		adp.nPageY						= 0;
		adp.vPos						= Vector3::ZERO;
		adp.bAtOnceLoad					= true;

		char szPluginName[MAX_PATH];
		sprintf_s(szPluginName, "%dx%d", adp.nPageX, adp.nPageY);
		adp.pluginName					= szPluginName;

		pPageFactory->createPlugin(adp, EditorPluginManager::getSingletonPtr()->findPlugin(CPN::EDITOR_TERRAIN_GROUP));
	}

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame)
		pMainFrame->ResetFileTree();
	
	OnOK();
}

/**
 *
 */
void CTerrainCrtDialog::OnBnClickedCancel()
{
	OnCancel();
}

