#include "StdAfx.h"
#include "Resource.h"
#include "DlgKickUser.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgKickUser, CSkinDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgKickUser::CDlgKickUser() : CSkinDialog(IDD_DLG_KICK_USER)
{
}

//��������
CDlgKickUser::~CDlgKickUser()
{
}

//�ؼ���
VOID CDlgKickUser::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control( pDX,IDOK,m_btOK );
	DDX_Control( pDX,IDCANCEL,m_btCancel );
	DDX_Text(pDX,IDC_EDT_MESSAGE,m_strKickMessage);
}

//��ʼ������
BOOL CDlgKickUser::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("��ʾ"));
	
	//Ĭ����ʾ
	m_strKickMessage = TEXT("��Ǹ����������Ա������䣬�����κ����ʣ�����ϵ��Ϸ�ͷ���");

	UpdateData(FALSE);

	return TRUE;
}

//ȷ������
VOID CDlgKickUser::OnOK()
{
	UpdateData();
	
	return __super::OnOK();
}

//////////////////////////////////////////////////////////////////////////
