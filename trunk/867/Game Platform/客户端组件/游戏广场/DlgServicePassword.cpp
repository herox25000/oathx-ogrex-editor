#include "StdAfx.h"
#include "GlobalUnits.h"
#include "DlgServicePassword.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgServicePassword, CDlgServiceItem)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_LOGON_PASSWORD2, OnEnChangeLogonPassword)
	ON_EN_CHANGE(IDC_INSURE_PASSWORD2, OnEnChangeInserePassword)
	ON_BN_CLICKED(IDC_MODIFY_LOGON_PASSWORD, OnBnClickedLogonPassword)
	ON_BN_CLICKED(IDC_MODIFY_INSURE_PASSWORD, OnBnClickedInsurePassword)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgServicePassword::CDlgServicePassword() : CDlgServiceItem(IDD_DLG_SERVICE_PASSWORD)
{
	//����ͼ��
	m_cbImageIndex=1;

	//���ñ���
	m_cbLogonPasswordLevel=PASSWORD_LEVEL_0;
	m_cbInsurePasswordLevel=PASSWORD_LEVEL_0;

	//���ñ���
	m_bLogonMission=false;
	ZeroMemory(m_szSrcPassword,sizeof(m_szSrcPassword));
	ZeroMemory(m_szDesPassword,sizeof(m_szDesPassword));

	return;
}

//��������
CDlgServicePassword::~CDlgServicePassword()
{;
}

//�ؼ���
VOID CDlgServicePassword::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ʺ�����
	DDX_Control(pDX, IDC_LOGON_PASSWORD1, m_edLogonPassword1);
	DDX_Control(pDX, IDC_LOGON_PASSWORD2, m_edLogonPassword2);
	DDX_Control(pDX, IDC_LOGON_PASSWORD3, m_edLogonPassword3);

	//��������
	DDX_Control(pDX, IDC_INSURE_PASSWORD1, m_edInsurePassword1);
	DDX_Control(pDX, IDC_INSURE_PASSWORD2, m_edInsurePassword2);
	DDX_Control(pDX, IDC_INSURE_PASSWORD3, m_edInsurePassword3);

	//��ť����
	DDX_Control(pDX, IDC_MODIFY_LOGON_PASSWORD, m_btLogonPassword);
	DDX_Control(pDX, IDC_MODIFY_INSURE_PASSWORD, m_btInsurePassword);
}

//�ӿڲ�ѯ
void * __cdecl CDlgServicePassword::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//ȡ��
VOID CDlgServicePassword::OnDestroy()
{
	__super::OnDestroy();
	if(m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
}

//��Ϣ����
BOOL CDlgServicePassword::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_RETURN))
	{
		//��������
		CWnd * pWndFouns=GetFocus();
		TCHAR szPassword[PASS_LEN]=TEXT("");

		//�����ж�
		if (m_edLogonPassword1.IsChild(pWndFouns))
		{
			m_edLogonPassword1.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edLogonPassword2.SetFocus();

			return TRUE;
		}

		//�����ж�
		if (m_edLogonPassword2.IsChild(pWndFouns))
		{
			m_edLogonPassword2.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edLogonPassword3.SetFocus();

			return TRUE;
		}

		//�����ж�
		if (m_edLogonPassword3.IsChild(pWndFouns))
		{
			m_edLogonPassword3.GetUserPassword(szPassword);
			if (szPassword[0]!=0) OnBnClickedLogonPassword();

			return TRUE;
		}

		//�����ж�
		if (m_edInsurePassword1.IsChild(pWndFouns))
		{
			m_edInsurePassword1.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edInsurePassword2.SetFocus();

			return TRUE;
		}

		//�����ж�
		if (m_edInsurePassword2.IsChild(pWndFouns))
		{
			m_edInsurePassword2.GetUserPassword(szPassword);
			if (szPassword[0]!=0) m_edInsurePassword3.SetFocus();

			return TRUE;
		}

		//�����ж�
		if (m_edInsurePassword3.IsChild(pWndFouns))
		{
			m_edInsurePassword3.GetUserPassword(szPassword);
			if (szPassword[0]!=0) OnBnClickedInsurePassword();

			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}


//�����¼�
bool CDlgServicePassword::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//���ӽ��
	if (nErrorCode!=0)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("���ӷ�������ʱ�������޸�ʧ�ܣ�"),0,MB_ICONQUESTION,TEXT("�û�����"));
		return true;
	}

	//��������
	tagGlobalUserData & pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//��������
	TCHAR szSrcPassword[PASS_LEN]=TEXT("");
	TCHAR szDesPassword[PASS_LEN]=TEXT("");
	CMD5Encrypt::EncryptData(m_szSrcPassword,szSrcPassword);
	CMD5Encrypt::EncryptData(m_szDesPassword,szDesPassword);
	//��������
	CMD_GP_ModifyPassword Modofiy;
	Modofiy.lUserID = pGlobalUserData.dwUserID;
	Modofiy.lType = m_bLogonMission==true?1:2;
	lstrcpyn(Modofiy.szOLDPassword,szSrcPassword,CountArray(Modofiy.szOLDPassword));
	lstrcpyn(Modofiy.szNEWPassword,szDesPassword,CountArray(Modofiy.szNEWPassword));
	m_SocketHelper->SendData(MDM_GP_USER,SUB_GP_MODIFYPASSWORD,&Modofiy,sizeof(Modofiy));	

	return true;
}

//�ر��¼�
bool CDlgServicePassword::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	//��ʾ��Ϣ
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("��������������쳣�Ͽ��ˣ��û������޸�ʧ�ܣ�"),30,MB_ICONERROR,TEXT("�û�����"));
	}
	OnMissionConclude();
	return true;
}

//��ȡ�¼�
bool CDlgServicePassword::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_MODIFYPASSWORD_RESULT:	//����ʧ��
			{
				if(pData == NULL || sizeof(CMD_GP_ModifyPassword_Ret) != wDataSize)
				{
					ASSERT(FALSE);
					return true;
				}
				CMD_GP_ModifyPassword_Ret* pRet = (CMD_GP_ModifyPassword_Ret*)pData;

				//�ɹ�
				if(pRet->lResultCode == 0)
				{
					ShowInformationEx(TEXT("�޸ĳɹ�,�����µ�¼,����Ը��������Ӱ�죡"),60,MB_ICONERROR,TEXT("�û�����"));
				}
				else
				{
					ShowInformationEx(pRet->szDescribeString,60,MB_ICONERROR,TEXT("�û�����"));
				}
				OnMissionConclude();

				if (m_SocketHelper.GetInterface()!=NULL)
					m_SocketHelper->CloseSocket();
				return true;
			}
		}
	}
	//�������
	ASSERT(FALSE);
	return true;
}

//��ʼ����
VOID CDlgServicePassword::OnMissionStart()
{
	//���ܰ�ť
	m_btLogonPassword.EnableWindow(FALSE);
	m_btInsurePassword.EnableWindow(FALSE);
	return;
}

//��ֹ����
VOID CDlgServicePassword::OnMissionConclude()
{
	//���ܰ�ť
	m_btLogonPassword.EnableWindow(TRUE);
	m_btInsurePassword.EnableWindow(TRUE);
	//���ÿؼ�
	m_edLogonPassword1.SetUserPassword(TEXT(""));
	m_edLogonPassword2.SetUserPassword(TEXT(""));
	m_edLogonPassword3.SetUserPassword(TEXT(""));
	//���ÿؼ�
	m_edInsurePassword1.SetUserPassword(TEXT(""));
	m_edInsurePassword2.SetUserPassword(TEXT(""));
	m_edInsurePassword3.SetUserPassword(TEXT(""));
	return;
}

//�滭����
BOOL CDlgServicePassword::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//������Դ
	CPngImage ImagePassword;
	ImagePassword.LoadImage(AfxGetInstanceHandle(),TEXT("PASSWORD_LEVEL"));

	//��ȡ��С
	CSize SizePassword;
	SizePassword.SetSize(ImagePassword.GetWidth()/3,ImagePassword.GetHeight()/2);

	//��䱳��
	pBufferDC->FillSolidRect(&rcClient,CSkinPngDialog::m_SkinAttribute.m_crBackGround);

	//�滭�ȼ�
	ImagePassword.DrawImage(pBufferDC,230,76,SizePassword.cx*3,SizePassword.cy,0,0);
	ImagePassword.DrawImage(pBufferDC,230,256,SizePassword.cx*3,SizePassword.cy,0,0);

	//�滭����
	if (m_cbLogonPasswordLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbLogonPasswordLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		ImagePassword.DrawImage(pBufferDC,230+nImagePos,76,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	//�滭����
	if (m_cbInsurePasswordLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbInsurePasswordLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		ImagePassword.DrawImage(pBufferDC,230+nImagePos,256,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//��������
VOID CDlgServicePassword::OnEnChangeLogonPassword()
{
	//��ȡ����
	TCHAR szPassword[PASS_LEN]=TEXT("");
	m_edLogonPassword2.GetUserPassword(szPassword);
	//�ȼ��ж�
	BYTE cbPasswordLevel=GetPasswordLevel(szPassword);
	//���´���
	if (m_cbLogonPasswordLevel!=cbPasswordLevel)
	{
		//���ñ���
		m_cbLogonPasswordLevel=cbPasswordLevel;
		//���´���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
	return;
}

//��������
VOID CDlgServicePassword::OnEnChangeInserePassword()
{
	//��ȡ����
	TCHAR szPassword[PASS_LEN]=TEXT("");
	m_edInsurePassword2.GetUserPassword(szPassword);
	//�ȼ��ж�
	BYTE cbPasswordLevel=GetPasswordLevel(szPassword);
	//���´���
	if (m_cbInsurePasswordLevel!=cbPasswordLevel)
	{
		//���ñ���
		m_cbInsurePasswordLevel=cbPasswordLevel;
		//���´���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
	return;
}

//�޸ĵ�½����
VOID CDlgServicePassword::OnBnClickedLogonPassword()
{
	//��������
	TCHAR szSrcPassword[ PASS_LEN];
	TCHAR szDesPassword[2][PASS_LEN];
	//��ȡ��Ϣ
	m_edLogonPassword1.GetUserPassword(szSrcPassword);
	m_edLogonPassword2.GetUserPassword(szDesPassword[0]);
	m_edLogonPassword3.GetUserPassword(szDesPassword[1]);
	//�����ж�
	if (szSrcPassword[0]==0)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("ԭ�ʺ�����������������룡"),0,MB_ICONERROR,TEXT("�û�����"));
		//���ý���
		m_edLogonPassword1.SetFocus();
		return;
	}

	//�����ж�
	if (lstrcmp(szDesPassword[0],szDesPassword[1])!=0)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("������������ʺ����벻һ�£����������룡"),0,MB_ICONERROR,TEXT("�û�����"));
		//���ý���
		m_edLogonPassword2.SetFocus();

		return;
	}
	//��������
	INT nCharLength=lstrlen(szDesPassword[0]);
	INT nDataLength=nCharLength*sizeof(TCHAR);
	if(nDataLength  < 6)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("��������Ҫ6λ������������"),0,MB_ICONERROR,TEXT("�û�����"));
		//���ý���
		m_edLogonPassword2.SetFocus();
		return;
	}
	//һ���ж�
	if (lstrcmp(szSrcPassword,szDesPassword[0])==0)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("�����������������ԭ����һ�£����������������룡"),0,MB_ICONERROR,TEXT("�û�����"));
		//���ý���
		m_edLogonPassword2.SetFocus();
		//��������
		m_edLogonPassword2.SetUserPassword(TEXT(""));
		m_edLogonPassword3.SetUserPassword(TEXT(""));
		return;
	}
	//���ñ���
	m_bLogonMission=true;
	lstrcpyn(m_szSrcPassword,szSrcPassword,CountArray(m_szSrcPassword));
	lstrcpyn(m_szDesPassword,szDesPassword[0],CountArray(m_szDesPassword));
	//�¼�����
	OnMissionStart();
	//��������
	if (ConnetToServer()==false) 
	{
		OnMissionConclude();
		return;
	}
	return;
}

//�޸���������
VOID CDlgServicePassword::OnBnClickedInsurePassword()
{
	//��������
	TCHAR szSrcPassword[PASS_LEN];
	TCHAR szDesPassword[2][PASS_LEN];

	//��ȡ��Ϣ
	m_edInsurePassword1.GetUserPassword(szSrcPassword);
	m_edInsurePassword2.GetUserPassword(szDesPassword[0]);
	m_edInsurePassword3.GetUserPassword(szDesPassword[1]);

	//�����ж�
	if (szSrcPassword[0]==0)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("ԭ��������������������룡"),0,MB_ICONERROR,TEXT("�û�����"));
		m_edLogonPassword1.SetFocus();
		return;
	}

	//�����ж�
	if (lstrcmp(szDesPassword[0],szDesPassword[1])!=0)
	{
		ShowInformationEx(TEXT("��������������в�һ�£����������룡"),0,MB_ICONERROR,TEXT("�û�����"));
		//���ý���
		m_edInsurePassword2.SetFocus();
		return;
	}

	//��������
	INT nCharLength=lstrlen(szDesPassword[0]);
	INT nDataLength=nCharLength*sizeof(TCHAR);
	if(nDataLength  < 6)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("��������Ҫ6λ������������"),0,MB_ICONERROR,TEXT("�û�����"));
		//���ý���
		m_edInsurePassword2.SetFocus();
		return;
	}
	//һ���ж�
	if (lstrcmp(szSrcPassword,szDesPassword[0])==0)
	{
		//��ʾ��Ϣ
		ShowInformationEx(TEXT("�����������������ԭ����һ�£����������������룡"),0,MB_ICONERROR,TEXT("�û�����"));
		//���ý���
		m_edInsurePassword2.SetFocus();
		//��������
		m_edInsurePassword2.SetUserPassword(TEXT(""));
		m_edInsurePassword3.SetUserPassword(TEXT(""));
		return;
	}

	//���ñ���
	m_bLogonMission=false;
	lstrcpyn(m_szSrcPassword,szSrcPassword,CountArray(m_szSrcPassword));
	lstrcpyn(m_szDesPassword,szDesPassword[0],CountArray(m_szDesPassword));

	//�¼�����
	OnMissionStart();

	//��������
	if (ConnetToServer()==false) 
	{
		OnMissionConclude();
		return;
	}

	return;
}

//����ȼ�
BYTE CDlgServicePassword::GetPasswordLevel(LPCTSTR pszPassword)
{
	//��������
	BYTE cbPasswordInfo[4]={0,0,0,0};
	UINT uPasswordLength=lstrlen(pszPassword);

	//�����ж�
	if (lstrlen(pszPassword)<6)
	{
		return PASSWORD_LEVEL_0;
	}

	//Сд��ĸ
	for (UINT i=0;i<uPasswordLength;i++)
	{
		//Сд��ĸ
		if ((pszPassword[i]>=TEXT('a'))&&((pszPassword[i]<=TEXT('z'))))
		{
			cbPasswordInfo[0]=1;
			continue;
		}

		//��д��ĸ
		if ((pszPassword[i]>=TEXT('A'))&&((pszPassword[i]<=TEXT('Z'))))
		{
			cbPasswordInfo[1]=1;
			continue;
		}

		//�����ַ�
		if ((pszPassword[i]>=TEXT('0'))&&((pszPassword[i]<=TEXT('9'))))
		{
			cbPasswordInfo[2]=1;
			continue;
		}

		//�����ַ�
		cbPasswordInfo[3]=1;
	}

	//�жϵȼ�
	BYTE cbLevelCount=0;
	for (BYTE i=0;i<CountArray(cbPasswordInfo);i++)
	{
		if (cbPasswordInfo[i]>0)
		{
			cbLevelCount++;
		}
	}
	return PASSWORD_LEVEL_0+__min(cbLevelCount,(PASSWORD_LEVEL_3-PASSWORD_LEVEL_0));
}

//���ӵ�������
bool CDlgServicePassword::ConnetToServer()
{
	//�������
	if (m_SocketHelper.GetInterface()==NULL)
	{
		//��ʼ���ں�
		IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
		try 
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_SocketHelper.CreateInstance()==false) 
			{
				throw TEXT("��������ʧ��1����Ǹ��");
			}
			if (m_SocketHelper->SetTCPSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("��������ʧ��2����Ǹ��");
			}
		}
		catch (...)
		{
			ShowInformationEx(TEXT("��������ʧ��3����Ǹ��"),0,MB_ICONQUESTION,TEXT("�޸�����"));
			return false;
		}
	}
	if (m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
	if(m_SocketHelper->Connect( g_GlobalUnits.m_LogonServerIP, g_GlobalUnits.m_LogonServerPort) != CONNECT_SUCCESS)
	{
		ShowInformationEx(TEXT("��������ʧ��4����Ǹ"),0,MB_ICONQUESTION,TEXT("�޸�����"));
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////
