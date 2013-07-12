#include "StdAfx.h"
#include "Resource.h"
#include "DlgManageUser.h"
#include "DlgKickUser.h"
#include "DlgDismissGame.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgManageUser, CSkinDialog)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgManageUser::CDlgManageUser() : CSkinDialog(IDD_DLG_MANAGE_USER)
{
	//���ñ���
	m_dwMasterRight = 0;
	m_pITCPSocket=NULL;

	return;
}

//��������
CDlgManageUser::~CDlgManageUser()
{
}

//�ؼ���
VOID CDlgManageUser::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KICK_ALL_USER, m_btKickAllUser);
	DDX_Control(pDX, IDC_DISMISS_GAME, m_btDismissGame);
	DDX_Control(pDX, IDC_SEE_USER_IP, m_btSeeUserIP);
}

//��ʼ������
BOOL CDlgManageUser::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("�û�����"));
	
	//��ť����
	BOOL bEnable = CMasterRight::CanKillUser(m_dwMasterRight)?TRUE:FALSE;
	m_btKickAllUser.EnableWindow(bEnable);
	bEnable = CMasterRight::CanDismissGame(m_dwMasterRight)?TRUE:FALSE;
	m_btDismissGame.EnableWindow(bEnable);
	bEnable = CMasterRight::CanSeeUserIP(m_dwMasterRight)?TRUE:FALSE;
	m_btSeeUserIP.EnableWindow(bEnable);
	m_btSeeUserIP.ShowWindow(SW_HIDE);

	return TRUE;
}

//ȷ������
VOID CDlgManageUser::OnOK()
{
	return;
}

//ȡ����Ϣ
VOID CDlgManageUser::OnCancel()
{
	//���ٴ���
	DestroyWindow();

	return;
}

//�˵�����
BOOL CDlgManageUser::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_KICK_ALL_USER:			//�������
		{
			//Ȩ��Ч��
			ASSERT( CMasterRight::CanKillUser(m_dwMasterRight) );
			if( CMasterRight::CanKillUser(m_dwMasterRight) == false ) return TRUE;

			CDlgKickUser DlgKickUser;
			if(IDOK == DlgKickUser.DoModal())
			{
				CMD_GR_KickAllUser KickAllUser = {};		
				_sntprintf(KickAllUser.szKickMessage,CountArray(KickAllUser.szKickMessage), TEXT("%s"), DlgKickUser.m_strKickMessage);

				ASSERT(m_pITCPSocket!=NULL);
				WORD wSendSize = CountStringBuffer(KickAllUser.szKickMessage);
				m_pITCPSocket->SendData(MDM_GR_MANAGE,SUB_GR_KICK_ALL_USER,&KickAllUser,wSendSize);
			}

			return TRUE;
		}
	case IDC_DISMISS_GAME:			//��ɢ��Ϸ
		{
			//Ȩ��Ч��
			ASSERT( CMasterRight::CanDismissGame(m_dwMasterRight) );
			if( CMasterRight::CanDismissGame(m_dwMasterRight) == false ) return TRUE;

			CDlgDismissGame DlgDismissGame;
			if(IDOK == DlgDismissGame.DoModal())
			{
				CMD_GR_DismissGame DismissGame;
				DismissGame.wDismissTableNum=DlgDismissGame.GetDismissTableNum();

				ASSERT(m_pITCPSocket!=NULL);
				m_pITCPSocket->SendData(MDM_GR_MANAGE,SUB_GR_DISMISSGAME,&DismissGame,sizeof(DismissGame));
			}

			return TRUE;
		}
	case IDC_SEE_USER_IP:			//�鿴���IP
		{
			return TRUE;
		}
	}

	return __super::OnCommand(wParam,lParam);
}

//���ýӿ�
bool CDlgManageUser::SetTCPSocket(IUnknownEx * pIUnknownEx)
{
	//���ýӿ�
	if (pIUnknownEx!=NULL)
	{
		//��ѯ�ӿ�
		ASSERT(QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITCPSocket)!=NULL);
		m_pITCPSocket=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITCPSocket);

		//�ɹ��ж�
		if (m_pITCPSocket==NULL) return false;
	}
	else m_pITCPSocket=NULL;

	return true;
}

//����Ȩ��
VOID CDlgManageUser::SetMasterRight( DWORD dwMasterRight )
{
	m_dwMasterRight = dwMasterRight;

	if( m_hWnd )
	{
		//��ť����
		BOOL bEnable = CMasterRight::CanKillUser(m_dwMasterRight)?TRUE:FALSE;
		m_btKickAllUser.EnableWindow( bEnable );

		bEnable = CMasterRight::CanDismissGame(m_dwMasterRight)?TRUE:FALSE;
		m_btDismissGame.EnableWindow( bEnable );
	}
}

//////////////////////////////////////////////////////////////////////////
