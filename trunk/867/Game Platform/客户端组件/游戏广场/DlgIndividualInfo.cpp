#include "Stdafx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "DlgIndividualInfo.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgIndividualInfo, CSkinPngDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//���캯��
CDlgIndividualInfo::CDlgIndividualInfo() : CSkinPngDialog(IDD_MODIFY_INDIVIDUAL)
{

	return;
}

//��������
CDlgIndividualInfo::~CDlgIndividualInfo()
{
}

//�ؼ���
void CDlgIndividualInfo::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}

//��ʼ������
BOOL CDlgIndividualInfo::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("�û�������Ϣ"));

	//���ؼ�
	m_BrowerAD.Create(NULL,NULL,WS_VISIBLE|WS_CHILD,CRect(0,0,0,0),this,100,NULL);
	//m_BrowerAD.Navigate(TEXT("www.game541.com"),NULL,NULL,NULL,NULL);
	//m_BrowerAD.ShowWindow(SW_HIDE);
	//���λ��
	m_BrowerAD.MoveWindow(5+4,5+5,327,248);

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////

