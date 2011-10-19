#include "stdafx.h"
#include "Editor.h"
#include "TerrainDialog.h"
#include "MainFrm.h"
#include "Serialize.h"

IMPLEMENT_DYNAMIC(CTerrainDialog, CDialogEx)

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CTerrainDialog::CTerrainDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTerrainDialog::IDD, pParent)
{

}

//////////////////////////////////////////////////////////////////////////
CTerrainDialog::~CTerrainDialog()
{
}

//////////////////////////////////////////////////////////////////////////
void		CTerrainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TR_MGR, m_wTrBox);
}

BEGIN_MESSAGE_MAP(CTerrainDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTerrainDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTerrainDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
BOOL		CTerrainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_wTrBox.AddString("ETM2.3.1");

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void		CTerrainDialog::OnBnClickedOk()
{
	CString sName;
	GetDlgItemText(IDC_TR_NAME, sName);

	CString sTemp;
	GetDlgItemText(IDC_TR_W, sTemp);
	int w = atoi(sTemp.GetBuffer());

	GetDlgItemText(IDC_TR_H, sTemp);
	int h = atoi(sTemp.GetBuffer());

	int nSel = m_wTrBox.GetCurSel();
	m_wTrBox.GetLBText(nSel, sTemp);
	
	TiXmlDocument* pDoc = Serialize::GetSingleton().GetDocument();
	if (pDoc != NULL)
	{
		TiXmlElement* root = pDoc->RootElement();
		ASSERT(root != NULL);
		
		if (root->FirstChildElement(STR_TERRAIN) == NULL)
		{
			TiXmlElement* terr = new TiXmlElement(STR_TERRAIN);
			terr->SetAttribute(STR_NAME,  sName);
			terr->SetAttribute(STR_WIDTH, w);
			terr->SetAttribute(STR_HEIGHT,h);
			terr->SetAttribute(STR_MGR, sTemp);

			root->LinkEndChild(terr);

			BOOL bResult = Serialize::GetSingleton().Save();
			if (bResult)
			{
				CMainFrame* pFrame = (CMainFrame*)(AfxGetMainWnd());
				ASSERT(pFrame != NULL);
				pFrame->GetFileView()->UpdateSolution();
			}			
		}
		else
		{
			AfxMessageBox(IDS_ERR_TRNAME);
		}
	}
	
	OnOK();
}

//////////////////////////////////////////////////////////////////////////
void		CTerrainDialog::OnBnClickedCancel()
{
	OnCancel();
}
