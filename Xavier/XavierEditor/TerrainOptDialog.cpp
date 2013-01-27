#include "stdafx.h"
#include "XavierEditor.h"
#include "TerrainOptDialog.h"
#include "XavierEditorInclude.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CTerrainOptDialog, CDialog)

/**
 *
 * \param 
 * \return 
 */
CTerrainOptDialog::CTerrainOptDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTerrainOptDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CTerrainOptDialog::~CTerrainOptDialog()
{
}

/**
 *
 * \param pDX 
 */
void CTerrainOptDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTerrainOptDialog, CDialog)
	ON_BN_CLICKED(IDC_RADIO_SPLAT, &CTerrainOptDialog::OnBnClickedRadioSplat)
	ON_BN_CLICKED(IDC_RADIO_DEFORM, &CTerrainOptDialog::OnBnClickedRadioDeform)
END_MESSAGE_MAP()


/**
 *
 */
void CTerrainOptDialog::OnBnClickedRadioSplat()
{
	EditorTerrain* pPlugin = static_cast<EditorTerrain*>(
		EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
		);
	if (pPlugin)
	{
		pPlugin->setActionValue(ETM_SPLAT);
	}
}

/**
 *
 */
void CTerrainOptDialog::OnBnClickedRadioDeform()
{
	EditorTerrain* pPlugin = static_cast<EditorTerrain*>(
		EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
		);
	if (pPlugin)
	{
		pPlugin->setActionValue(ETM_DEFORM);
	}
}
