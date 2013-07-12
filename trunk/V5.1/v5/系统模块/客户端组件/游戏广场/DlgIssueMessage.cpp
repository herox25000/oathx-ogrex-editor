#include "StdAfx.h"
#include "Resource.h"
#include "DlgIssueMessage.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgIssueMessage, CSkinDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgIssueMessage::CDlgIssueMessage() : CSkinDialog(IDD_DLG_ISSUE_MESSAGE)
{
	m_bSendALLRoom = FALSE;
	m_bSendGame = TRUE;
	m_bSendRoom = TRUE;
}

//��������
CDlgIssueMessage::~CDlgIssueMessage()
{
}

//�ؼ���
VOID CDlgIssueMessage::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control( pDX,IDOK,m_btOK );
	DDX_Control( pDX,IDCANCEL,m_btCancel );
	DDX_Check( pDX,IDC_CHECK_ALLROOM,m_bSendALLRoom);
	DDX_Check( pDX,IDC_CHEK_ROOM,m_bSendRoom );
	DDX_Check( pDX,IDC_CHEK_GAME,m_bSendGame );
	DDX_Text(pDX,IDC_EDT_MESSAGE,m_strMessage);
}

//��ʼ������
BOOL CDlgIssueMessage::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("��Ϣ����"));

	UpdateData(FALSE);

	return TRUE;
}

//ȷ������
VOID CDlgIssueMessage::OnOK()
{
	UpdateData();
	
	//Ч����Ϣ
	if( m_strMessage.IsEmpty() )
	{
		//��ʾ��Ϣ
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("��Ǹ,��ʾ��Ϣ����Ϊ��,����������!"),MB_ICONWARNING|MB_OK);
		return;
	}

	if( !m_bSendGame && !m_bSendRoom )
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("������Ϣ����Ϸ��Ϣ��������ѡ������һ����"),MB_ICONWARNING|MB_OK);
		return;
	}

	return __super::OnOK();
}

//////////////////////////////////////////////////////////////////////////
