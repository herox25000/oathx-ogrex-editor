#include "Stdafx.h"
#include "Resource.h"
#include "DlgGameRule.h"
#include "GlobalUnits.h"
#include "GlobalUnits.h"
//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgGameRule, CSkinDialog)
	ON_WM_SIZE()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgGameRule::CDlgGameRule() : CSkinDialog(IDD_GAME_RULE)
{
	//���ñ���
	m_pHtmlBrowser=NULL;

	return;
}

//��������
CDlgGameRule::~CDlgGameRule()
{
	//ɾ���ؼ�
	SafeDelete(m_pHtmlBrowser);
	
	return;
}

//�ؼ���
VOID CDlgGameRule::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
}

//��ʼ������
BOOL CDlgGameRule::OnInitDialog()
{
	__super::OnInitDialog();

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	INT nTViewBorder=m_SkinAttribute.m_EncircleInfoView.nTBorder;
	INT nBViewBorder=m_SkinAttribute.m_EncircleInfoView.nBBorder;
	INT nLViewBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRViewBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;

	//��������
	CGlobalUnits *pGlobalUnits=CGlobalUnits::GetInstance();
	tagGameAttribute * pGameAttribute=pGlobalUnits->m_ClientKernelModule->GetGameAttribute();

	//�����ؼ�
	try
	{
		//λ�ö���
		CRect rcBrowse;
		rcBrowse.left=nLViewBorder;
		rcBrowse.top=nTViewBorder;
		rcBrowse.right=rcClient.Width()-nLViewBorder;
		rcBrowse.bottom=rcClient.Height()-nBViewBorder;

		//�����ؼ�
		m_pHtmlBrowser=new CWebBrowser;
		m_pHtmlBrowser->Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rcBrowse,this,101);

		//�����ַ
		TCHAR szRuleUrl[256]=TEXT("");
		_sntprintf(szRuleUrl,CountArray(szRuleUrl),TEXT("%sGameRules.aspx?KindID=%ld"),szPlatformLink,pGameAttribute->wKindID);

		//�������
		m_pHtmlBrowser->Navigate(szRuleUrl,NULL,NULL,NULL,NULL);
	}
	catch (...) { ASSERT(FALSE); }

	//�������
	TCHAR szTitle[128]=TEXT("");
	_sntprintf(szTitle,CountArray(szTitle),TEXT("��%s������˵��"),pGameAttribute->szGameName);

	//���ô���
	SetWindowText(szTitle);
//	EnableButton(WS_MAXIMIZEBOX|WS_MINIMIZEBOX);

	return TRUE;
}

//ȷ����Ϣ
VOID CDlgGameRule::OnOK() 
{
	return;
}

//ȡ����Ϣ
VOID CDlgGameRule::OnCancel()
{
	//���ٴ���
	DestroyWindow(); 

	return;
}

//������Ϣ
VOID CDlgGameRule::OnNcDestroy()
{
	//���ٿؼ�
	if(m_pHtmlBrowser && m_pHtmlBrowser->GetSafeHwnd()) m_pHtmlBrowser->DestroyWindow();

	//ɾ���ؼ�
	SafeDelete(m_pHtmlBrowser);

	__super::OnNcDestroy();
}

//λ����Ϣ
VOID CDlgGameRule::OnSize(UINT nType, INT cx, INT cy) 
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	if (m_pHtmlBrowser->GetSafeHwnd()!=NULL)
	{
		m_pHtmlBrowser->MoveWindow(m_SkinAttribute.m_EncircleInfoView.nLBorder,m_SkinAttribute.m_EncircleInfoView.nTBorder,
			cx-m_SkinAttribute.m_EncircleInfoView.nLBorder*2,cy-m_SkinAttribute.m_EncircleInfoView.nTBorder-m_SkinAttribute.m_EncircleInfoView.nRBorder);
	}

	return;
}

//////////////////////////////////////////////////////////////////////////
