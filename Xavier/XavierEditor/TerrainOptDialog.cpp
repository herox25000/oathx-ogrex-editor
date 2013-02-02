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
	DDX_Control(pDX, IDC_SLIDER_BRUSHSIZE, m_BrushSize);
	DDX_Control(pDX, IDC_SLIDER_INTENSITY, m_Intensity);
}

#define BRUSH_UPDATE_TIMER	1

BEGIN_MESSAGE_MAP(CTerrainOptDialog, CDialog)
	ON_BN_CLICKED(IDC_RADIO_SPLAT, &CTerrainOptDialog::OnBnClickedRadioSplat)
	ON_BN_CLICKED(IDC_RADIO_DEFORM, &CTerrainOptDialog::OnBnClickedRadioDeform)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_STAMP, &CTerrainOptDialog::OnBnClickedRadioStamp)
END_MESSAGE_MAP()

BOOL CTerrainOptDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_BrushSize.SetRange(2, 128);
	m_BrushSize.SetPos(6);

	m_Intensity.SetRange(2, 128);
	m_Intensity.SetPos(25);

	SetTimer(BRUSH_UPDATE_TIMER, 60, NULL);

	return TRUE;
}


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

/**
 *
 */
void CTerrainOptDialog::OnBnClickedRadioStamp()
{
	EditorTerrain* pPlugin = static_cast<EditorTerrain*>(
		EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
		);
	if (pPlugin)
	{
		pPlugin->setActionValue(ETM_SMOOTH);
	}
}

/**
 *
 */
void CTerrainOptDialog::OnPaint()
{
	CPaintDC dc(this);
}

/**
 *
 * \param nIDEvent 
 */
void CTerrainOptDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == BRUSH_UPDATE_TIMER)
	{
		EditorTerrain* pPlugin = static_cast<EditorTerrain*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
			);
		if (pPlugin)
		{
			MeshBrush* pBrush = pPlugin->getMeshBrush();
			if (pBrush)
			{
				pBrush->setRadius(m_BrushSize.GetPos());
				pBrush->setIntensity(m_Intensity.GetPos());
			}
		}

		char szTmp[MAX_PATH];
		sprintf_s(szTmp, "Brush size: %d Intensity: %d", m_BrushSize.GetPos(), m_Intensity.GetPos());
		SetDlgItemText(IDC_STATIC_DESC, szTmp);
	}

	CDialog::OnTimer(nIDEvent);
}


