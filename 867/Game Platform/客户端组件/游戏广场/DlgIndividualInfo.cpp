#include "Stdafx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "DlgIndividualInfo.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgIndividualInfo, CSkinPngDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//构造函数
CDlgIndividualInfo::CDlgIndividualInfo() : CSkinPngDialog(IDD_MODIFY_INDIVIDUAL)
{

	return;
}

//析构函数
CDlgIndividualInfo::~CDlgIndividualInfo()
{
}

//控件绑定
void CDlgIndividualInfo::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}

//初始化函数
BOOL CDlgIndividualInfo::OnInitDialog()
{
	__super::OnInitDialog();

	//设置标题
	SetWindowText(TEXT("用户基本信息"));

	//广告控件
	m_BrowerAD.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,100,NULL);
	//m_BrowerAD.Navigate(TEXT("www.game541.com"),NULL,NULL,NULL,NULL);
	//m_BrowerAD.ShowWindow(SW_HIDE);
	//广告位置
	m_BrowerAD.MoveWindow(5+4,5+5,327,248);

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

