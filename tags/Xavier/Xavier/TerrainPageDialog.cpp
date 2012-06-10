#include "stdafx.h"
#include "Xavier.h"
#include "XavierAppEditor.h"
#include "TerrainPageDialog.h"
#include "MainFrm.h"

using namespace Ogre;

IMPLEMENT_DYNAMIC(CTerrainPageDialog, CDialog)

/**
 *
 * \param /* 
 * \return 
 */
CTerrainPageDialog::CTerrainPageDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTerrainPageDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CTerrainPageDialog::~CTerrainPageDialog()
{
}

/**
 *
 * \param pDX 
 */
void CTerrainPageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTerrainPageDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CTerrainPageDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTerrainPageDialog::OnBnClickedCancel)
END_MESSAGE_MAP()



/**
 *
 * \return 
 */
BOOL CTerrainPageDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT1, CString("33"));
	SetDlgItemText(IDC_EDIT2, CString("65"));
	SetDlgItemText(IDC_EDIT3, CString("desert_0_diffusespecular.dds"));
	SetDlgItemText(IDC_EDIT4, CString("desert_0_normalheight.dds"));
	SetDlgItemText(IDC_EDIT5, CString("100"));
	SetDlgItemText(IDC_EDIT6, CString("0"));
	SetDlgItemText(IDC_EDIT7, CString("0"));

	return TRUE;
}


/**
 *
 */
void CTerrainPageDialog::OnBnClickedOk()
{
	CString szMinBatchSize;
	GetDlgItemText(IDC_EDIT1, szMinBatchSize);

	CString szMaxBatchSize;
	GetDlgItemText(IDC_EDIT2, szMaxBatchSize);

	CString szDiffuseTexture;
	GetDlgItemText(IDC_EDIT3, szDiffuseTexture);

	CString szNormalheightTexture;
	GetDlgItemText(IDC_EDIT4, szNormalheightTexture);

	CString szLayerWorldSize;
	GetDlgItemText(IDC_EDIT5, szLayerWorldSize);

	CString szPageX;
	GetDlgItemText(IDC_EDIT6, szPageX);

	CString szPageY;
	GetDlgItemText(IDC_EDIT7, szPageY);

	CString szPageName;
	GetDlgItemText(IDC_EDIT8, szPageName);

	XavierEditorFactory* pTerrainPageFactory = XavierEditorManager::getSingleton().getEditorFactory(
		XavierTerrainPageEditorFactory::FACTORY_NAME
		);
	if (pTerrainPageFactory != NULL)
	{
		STerrainPageServerAdp adp;
		adp.depServerName			= SERVER_TERRAIN_GROUP;
		adp.typeName				= szPageName.GetBuffer();
		adp.nPageX					= atoi(szPageX.GetBuffer());
		adp.nPageY					= atoi(szPageY.GetBuffer());
		adp.nMinBatchSize			= atoi(szMinBatchSize.GetBuffer());
		adp.nMaxBatchSzie			= atoi(szMaxBatchSize.GetBuffer());
		adp.diffuseTexture			= szDiffuseTexture.GetBuffer();
		adp.normalheightTexture		= szNormalheightTexture.GetBuffer();
		adp.fLayerWorldSize			= atof(szLayerWorldSize.GetBuffer());

		XavierEditorManager::getSingleton().addTool(pTerrainPageFactory->create(adp));
	}
	
	// 创建地形贴花光标
	XavierEditor* pWorldSpaceTool = XavierEditorManager::getSingleton().getTool(
		SERVER_WORLDSPACE
		);
	if (pWorldSpaceTool)
	{
		XavierEditor* pTerrainTool = XavierEditorManager::getSingleton().getTool(
			SERVER_TERRAIN_GROUP
			);
		if (pTerrainTool)
		{
			// 世界服务
			WorldSpaceServer*	pWorld = static_cast<WorldSpaceServer*>(pWorldSpaceTool->getServer());
			
			// 地形服务
			TerrainGroupServer*	pGroup = static_cast<TerrainGroupServer*>(
				pTerrainTool->getServer()
				);

			// 创建地形贴花光标
			new XavierDecalCursor(pWorld, 
				pGroup);
		}
	}

	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		// 通知文件窗口
		::SendMessage(pMainFrame->GetFileView()->m_hWnd, WM_CREATE_FNISHED, NULL, NULL);
	}

	OnOK();
}

/**
 *
 */
void CTerrainPageDialog::OnBnClickedCancel()
{
	OnCancel();
}

