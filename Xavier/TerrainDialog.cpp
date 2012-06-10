#include "stdafx.h"
#include "Xavier.h"
#include "MainFrm.h"
#include "XavierAppEditor.h"
#include "TerrainDialog.h"

using namespace Ogre;

IMPLEMENT_DYNAMIC(CTerrainDialog, CDialog)

/**
 *
 * \param /* 
 * \return 
 */
CTerrainDialog::CTerrainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTerrainDialog::IDD, pParent)
{

}

/**
 *
 * \return 
 */
CTerrainDialog::~CTerrainDialog()
{
}

/**
 *
 * \param pDX 
 */
void CTerrainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTerrainDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CTerrainDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTerrainDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


/**
 *
 * \return 
 */
BOOL CTerrainDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetDlgItemText(IDC_EDIT1, CString("1200.0"));
	SetDlgItemText(IDC_EDIT2, CString("513"));
	SetDlgItemText(IDC_EDIT4, CString("3000.0"));
	SetDlgItemText(IDC_EDIT5, CString("8"));

	return TRUE;
}


/**
 *
 */
void CTerrainDialog::OnBnClickedOk()
{
	CString szWorldSize;
	GetDlgItemText(IDC_EDIT1, szWorldSize);

	CString szTerrainSize;
	GetDlgItemText(IDC_EDIT2, szTerrainSize);

	CString szCompositeMapDistance;
	GetDlgItemText(IDC_EDIT4, szCompositeMapDistance);

	CString szMaxPixelError;
	GetDlgItemText(IDC_EDIT5, szMaxPixelError);

	XavierEditorFactory* pTerrainGroupFactory = XavierEditorManager::getSingleton().getEditorFactory(
		XavierTerrainEditorFactory::FACTORY_NAME
		);
	if (pTerrainGroupFactory != NULL)
	{
		STerrainGroupServerAdp adp;
		adp.depServerName			= SERVER_WORLDSPACE;
		adp.typeName				= SERVER_TERRAIN_GROUP;
		adp.fWorldSize				= atof(szWorldSize.GetBuffer());
		adp.nTerrainSize			= atoi(szTerrainSize.GetBuffer());
		adp.vOrigin					= Vector3::ZERO;
		adp.clrCompositeMapDiffuse	= ColourValue(1,1,1,1);
		adp.fCompositeMapDistance	= atof(szCompositeMapDistance.GetBuffer());
		adp.fMaxPixelError			= atoi(szMaxPixelError.GetBuffer());;
		adp.vLightMapDirection		= Vector3(0,0,0);
		
		XavierEditorManager::getSingleton().addTool(pTerrainGroupFactory->create(adp));
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
void CTerrainDialog::OnBnClickedCancel()
{
	OnCancel();
}
