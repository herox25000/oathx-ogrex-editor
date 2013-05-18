#include "StdAfx.h"
#include "Resource.h"
#include "DlgCustomFace.h"
#include "GlobalUnits.h"
#include "DlgServiceIndividual.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgServiceIndividual, CDlgServiceItem)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgServiceIndividual::CDlgServiceIndividual() : CDlgServiceItem(IDD_DLG_SERVICE_INDIVIDUAL)
{
	//����ͼ��
	m_cbImageIndex=0;

	//�������
	m_bQueryMission=false;
	m_bModifyMission=false;

	//�ʺ�����
	m_cbGender=0;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));
	ZeroMemory(m_szPassword,sizeof(m_szPassword));
	ZeroMemory(m_szUnderWrite,sizeof(m_szUnderWrite));

	//��ϸ����
	ZeroMemory(m_szQQ,sizeof(m_szQQ));
	ZeroMemory(m_szEMail,sizeof(m_szEMail));
	ZeroMemory(m_szUserNote,sizeof(m_szUserNote));
	ZeroMemory(m_szSFZ,sizeof(m_szSFZ));
	ZeroMemory(m_szMobilePhone,sizeof(m_szMobilePhone));
	ZeroMemory(m_szCompellation,sizeof(m_szCompellation));
	ZeroMemory(m_szDwellingPlace,sizeof(m_szDwellingPlace));

	return;
}

//��������
CDlgServiceIndividual::~CDlgServiceIndividual()
{
}

//�ؼ���
VOID CDlgServiceIndividual::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�����ؼ�
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDC_SELECT_FACE, m_FaceSelect);
	//�༭�ؼ�
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	DDX_Control(pDX, IDC_GAMEID, m_edGameID);
	DDX_Control(pDX, IDC_PASSWORD, m_edPassword);
	DDX_Control(pDX, IDC_UNDER_WRITE, m_edUnderWrite);

	//�༭�ؼ�
	DDX_Control(pDX, IDC_QQ, m_edQQ);
	DDX_Control(pDX, IDC_EMAIL, m_edEMail);
	DDX_Control(pDX, IDC_USER_NOTE, m_edUserNote);
	DDX_Control(pDX, IDC_SFZ, m_edSFZ);
	DDX_Control(pDX, IDC_MOBILE_PHONE, m_edMobilePhone);
	DDX_Control(pDX, IDC_COMPELLATION, m_edCompellation);
	DDX_Control(pDX, IDC_DWELLING_PLACE, m_edDwellingPlace);
}


//�ӿڲ�ѯ
void * __cdecl CDlgServiceIndividual::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}


//��������
BOOL CDlgServiceIndividual::OnInitDialog()
{
	__super::OnInitDialog();

	//����ͷ��
	g_GlobalUnits.m_UserFaceRes->FillImageList(m_ImageList);
	m_FaceSelect.SetImageList(&m_ImageList);
	//����ͷ��
	COMBOBOXEXITEM Item;
	ZeroMemory(&Item,sizeof(Item));
	Item.mask=CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	for (int i=g_GlobalUnits.m_UserFaceRes->GetFaceCount()-1;i>=0;i--) 
	{
		Item.lParam=i;
		Item.iImage=i;
		Item.iSelectedImage=i;
		m_FaceSelect.InsertItem(&Item);
	}

	//�ʺ���Ϣ
	m_edGameID.LimitText(10);	
	m_edAccounts.LimitText(NAME_LEN-1);
	m_edPassword.LimitText(PASS_LEN-1);
	m_edUnderWrite.LimitText(UNDER_WRITE_LEN-1);
	//��������
	m_edQQ.LimitText(QQ_LEN-1);
	m_edEMail.LimitText(EMAIL_LEN-1);
	m_edUserNote.LimitText(USER_NOTE_LEN-1);
	m_edSFZ.LimitText(IDCARD_LEN-1);
	m_edMobilePhone.LimitText(MOBILE_PHONE_LEN-1);
	m_edCompellation.LimitText(COMPELLATION_LEN-1);
	m_edDwellingPlace.LimitText(DWELLING_PLACE_LEN-1);
	//������Ϣ
	LoadAccountsInfo();

	return TRUE;
}

//ȡ��
VOID CDlgServiceIndividual::OnDestroy()
{
	__super::OnDestroy();
	if(m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
}

//ȷ������
VOID CDlgServiceIndividual::OnOK()
{
	//��������
	tagGlobalUserData& pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//��ȡ����
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_PASSWORD,szPassword,CountArray(szPassword));
	//�ʺ���Ϣ
	GetControlItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	int nCharLength = strlen(m_szAccounts);
	if (nCharLength < 6 || nCharLength > 26)
	{
		ShowInformationEx(TEXT("�ʺ����ֵĳ������6���ַ�,�13���ַ�,���������룡"),0,MB_ICONERROR,TEXT("�û�����"));
		GetDlgItem(IDC_ACCOUNTS)->SetFocus();
		return;
	}

	GetControlItemText(IDC_UNDER_WRITE,m_szUnderWrite,CountArray(m_szUnderWrite));
	GetDlgItemText(IDC_USER_NOTE,m_szUserNote,CountArray(m_szUserNote));
	GetDlgItemText(IDC_COMPELLATION,m_szCompellation,CountArray(m_szCompellation));
	GetDlgItemText(IDC_SFZ,m_szSFZ,CountArray(m_szSFZ));
	GetDlgItemText(IDC_MOBILE_PHONE,m_szMobilePhone,CountArray(m_szMobilePhone));
	GetDlgItemText(IDC_QQ,m_szQQ,CountArray(m_szQQ));
	GetDlgItemText(IDC_EMAIL,m_szEMail,CountArray(m_szEMail));
	GetDlgItemText(IDC_DWELLING_PLACE,m_szDwellingPlace,CountArray(m_szDwellingPlace));
	//�û��Ա�
	if (((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->GetCheck()==BST_CHECKED)
		m_cbGender=GENDER_GIRL;
	if (((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->GetCheck()==BST_CHECKED)
		m_cbGender=GENDER_BOY;
	//ͷ��ID
	m_cbFaceID = m_FaceSelect.GetCurSel();
	//��������
	CMD5Encrypt::EncryptData(szPassword,m_szPassword);
	//���ñ���
	m_bQueryMission=false;
	m_bModifyMission=true;
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

//�����¼�
bool CDlgServiceIndividual::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//���ӽ��
	if (nErrorCode!=0)
	{
		//��������
		if (ConnetToServer()==true)
		{
			return true;
		}
		//�¼�����
		OnMissionConclude();
		//������ʾ
		if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			ShowInformationEx(TEXT("���ӷ�������ʱ���û����ϻ�ȡʧ�ܣ�"),0,MB_OK|MB_ICONSTOP,TEXT("�û�����"));
		}
		//������ʾ
		if (m_bModifyMission==true)
		{
			//��ʾ��Ϣ
			ShowInformationEx(TEXT("���ӷ�������ʱ���û������޸�ʧ�ܣ�"),0,MB_OK|MB_ICONSTOP,TEXT("�û�����"));
		}

		return true;
	}

	//�޸�����
	if (m_bModifyMission==true)
	{
		SendModifyIndividualInfoMsg();
	}
	//��ѯ����
	if (m_bQueryMission==true)
	{
		SendQueryIndividualInfoMsg();
	}

	return true;
}

//�ر��¼�
bool CDlgServiceIndividual::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	//��ʾ��Ϣ
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		if (ConnetToServer()==true)
		{
			return true;
		}
		//��ѯ����
		if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			ShowInformationEx(TEXT("��������������쳣�Ͽ��ˣ��û����ϻ�ȡʧ�ܣ�"),0,MB_ICONERROR,TEXT("�û�����"));
		}

		//�޸�����
		if (m_bModifyMission==true)
		{
			//��ʾ��Ϣ
			ShowInformationEx(TEXT("��������������쳣�Ͽ��ˣ��û������޸�ʧ�ܣ�"),0,MB_ICONERROR,TEXT("�û�����"));
		}
	}
	//�¼�����
	OnMissionConclude();
	return true;
}

//��ȡ�¼�
bool CDlgServiceIndividual::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_MODIFY_INDIVIDUAL_RESULT:	//�޸��û����Ϸ���
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GP_ModifyIndividual_Ret));
				if (wDataSize!=sizeof(CMD_GP_ModifyIndividual_Ret)) 
					return false;
				//��������
				CMD_GP_ModifyIndividual_Ret * Ret=(CMD_GP_ModifyIndividual_Ret *)pData;
				//����ʧ��
				if(Ret->lResultCode != 0)
				{
					ShowInformationEx(Ret->szDescribeString,60,MB_ICONINFORMATION,TEXT("�û�����"));
				}
				else//��������ɹ�
				{
					tagGlobalUserData * pGlobalUserData=g_GlobalUnits.GetGolbalUserDataEx();
					tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();

					//�ʺ�����
					pGlobalUserData->cbGender = m_cbGender;
					pGlobalUserData->wFaceID = m_cbFaceID;
					lstrcpyn(pGlobalUserData->szAccounts,m_szAccounts,CountArray(pGlobalUserData->szAccounts));
					lstrcpyn(pGlobalUserData->szUnderWrite,m_szUnderWrite,CountArray(pGlobalUserData->szUnderWrite));

					//��չ����
					lstrcpyn(pIndividualUserData->szQQ,m_szQQ,CountArray(pIndividualUserData->szQQ));
					lstrcpyn(pIndividualUserData->szEMail,m_szEMail,CountArray(pIndividualUserData->szEMail));
					lstrcpyn(pIndividualUserData->szUserNote,m_szUserNote,CountArray(pIndividualUserData->szUserNote));
					lstrcpyn(pIndividualUserData->szSFZ,m_szSFZ,CountArray(pIndividualUserData->szSFZ));
					lstrcpyn(pIndividualUserData->szMobilePhone,m_szMobilePhone,CountArray(pIndividualUserData->szMobilePhone));
					lstrcpyn(pIndividualUserData->szCompellation,m_szCompellation,CountArray(pIndividualUserData->szCompellation));
					lstrcpyn(pIndividualUserData->szDwellingPlace,m_szDwellingPlace,CountArray(pIndividualUserData->szDwellingPlace));
					ShowInformationEx(TEXT("�޸ĳɹ�"),60,MB_ICONINFORMATION,TEXT("�û�����"));
				}
				//�ɹ�����
				OnMissionConclude();
				//�ر�����
				if (m_SocketHelper.GetInterface()!=NULL)
					m_SocketHelper->CloseSocket();
				return true;
			}
		case SUB_GP_QUERYUSERINDIVIDUAL:	//������Ϣ��ѯ����
			{
				//Ч�����
				ASSERT(wDataSize>=sizeof(CMD_GP_QueryIndividual));
				if (wDataSize<sizeof(CMD_GP_QueryIndividual)) 
					return false;
				//��������
				CMD_GP_QueryIndividual * pUserIndividual=(CMD_GP_QueryIndividual *)pData;
				//��������
				tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();
				//���ñ���
				pIndividualUserData->dwUserID=pUserIndividual->dwUserID;
				//��������
				VOID * pDataBuffer=NULL;
				tagDataDescribe DataDescribe;
				CRecvPacketHelper RecvPacket(pUserIndividual+1,wDataSize-sizeof(CMD_GP_QueryIndividual));
				//��չ��Ϣ
				while (true)
				{
					pDataBuffer=RecvPacket.GetData(DataDescribe);
					if (DataDescribe.wDataDescribe==DTP_NULL) break;
					switch (DataDescribe.wDataDescribe)
					{
					case DTP_GP_UI_USER_NOTE:		//�û���ע
						{
							lstrcpyn(pIndividualUserData->szUserNote,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szUserNote));
							break;
						}
					case DTP_GP_UI_COMPELLATION:	//��ʵ����
						{
							lstrcpyn(pIndividualUserData->szCompellation,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szCompellation));
							break;
						}
					case DTP_GP_UI_SFZ:		//���֤
						{
							lstrcpyn(pIndividualUserData->szSFZ,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szSFZ));
							break;
						}
					case DTP_GP_UI_MOBILE_PHONE:	//�ƶ��绰
						{
							lstrcpyn(pIndividualUserData->szMobilePhone,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szMobilePhone));
							break;
						}
					case DTP_GP_UI_QQ:				//Q Q ����
						{
							lstrcpyn(pIndividualUserData->szQQ,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szQQ));
							break;
						}
					case DTP_GP_UI_EMAIL:			//�����ʼ�
						{
							lstrcpyn(pIndividualUserData->szEMail,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szEMail));
							break;
						}
					case DTP_GP_UI_DWELLING_PLACE:	//��ϵ��ַ
						{
							lstrcpyn(pIndividualUserData->szDwellingPlace,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szDwellingPlace));
							break;
						}
					}
				}
				//�ɹ�����
				OnMissionConclude();
				//��������
				UpdateIndividualInfo();
				//�ر�����
				if (m_SocketHelper.GetInterface()!=NULL)
					m_SocketHelper->CloseSocket();

				return true;
			}
		}
	}

	return true;
}

//��ʼ����
VOID CDlgServiceIndividual::OnMissionStart()
{
	m_FaceSelect.EnableWindow(FALSE);
	//��Ϣ�ؼ�
	m_edAccounts.EnableWindow(FALSE);
	m_edGameID.EnableWindow(FALSE);
	m_edPassword.EnableWindow(FALSE);
	m_edUnderWrite.EnableWindow(FALSE);

	//��ϸ����
	m_edQQ.EnableWindow(FALSE);
	m_edEMail.EnableWindow(FALSE);
	m_edUserNote.EnableWindow(FALSE);
	m_edSFZ.EnableWindow(FALSE);
	m_edMobilePhone.EnableWindow(FALSE);
	m_edCompellation.EnableWindow(FALSE);
	m_edDwellingPlace.EnableWindow(FALSE);

	//���ܰ�ť
	m_btOk.EnableWindow(FALSE);
	return;
}

//��ֹ����
VOID CDlgServiceIndividual::OnMissionConclude()
{
	m_FaceSelect.EnableWindow(TRUE);
	//��Ϣ�ؼ�
	m_edAccounts.EnableWindow(TRUE);
	m_edGameID.EnableWindow(TRUE);
	m_edPassword.EnableWindow(TRUE);
	m_edUnderWrite.EnableWindow(TRUE);

	//��ϸ����
	m_edQQ.EnableWindow(TRUE);
	m_edEMail.EnableWindow(TRUE);
	m_edUserNote.EnableWindow(TRUE);
	m_edSFZ.EnableWindow(TRUE);
	m_edMobilePhone.EnableWindow(TRUE);
	m_edCompellation.EnableWindow(TRUE);
	m_edDwellingPlace.EnableWindow(TRUE);
	//���ܰ�ť
	m_btOk.EnableWindow(TRUE);
	//���ÿؼ�
	m_edPassword.SetWindowText(TEXT(""));

	return;
}

//�ʺ���Ϣ
VOID CDlgServiceIndividual::LoadAccountsInfo()
{
	//��������
	tagGlobalUserData * pGlobalUserData=g_GlobalUnits.GetGolbalUserDataEx();
	tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();
	//�û�ͷ��
	m_FaceSelect.SetCurSel(pGlobalUserData->wFaceID);
	//��������
	TCHAR tGameID[32]=TEXT("");
	_sntprintf(tGameID,sizeof(tGameID),"%d",pGlobalUserData->dwGameID);
	SetDlgItemText(IDC_GAMEID,tGameID);
	SetDlgItemText(IDC_ACCOUNTS,pGlobalUserData->szAccounts);
	SetDlgItemText(IDC_UNDER_WRITE,pGlobalUserData->szUnderWrite);

	//�û��Ա�
	if (pGlobalUserData->cbGender==GENDER_GIRL) //Ů 
		((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->SetCheck(BST_CHECKED);
	if (pGlobalUserData->cbGender==GENDER_BOY)//��
		((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->SetCheck(BST_CHECKED);

	//��ϸ����
	if (pIndividualUserData->dwUserID==0L)
	{
		QueryIndividualInfo();
	}
	else
	{
		UpdateIndividualInfo();
	}

	return;
}

//��ѯ����
VOID CDlgServiceIndividual::QueryIndividualInfo()
{
	//���ñ���
	m_bQueryMission=true;
	m_bModifyMission=false;

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

//��������
VOID CDlgServiceIndividual::UpdateIndividualInfo()
{
	//��������
	tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();
	//�û�����
	SetDlgItemText(IDC_USER_NOTE,pIndividualUserData->szUserNote);
	SetDlgItemText(IDC_COMPELLATION,pIndividualUserData->szCompellation);
	SetDlgItemText(IDC_SFZ,pIndividualUserData->szSFZ);
	//�绰����
	SetDlgItemText(IDC_MOBILE_PHONE,pIndividualUserData->szMobilePhone);
	//��ϵ����
	SetDlgItemText(IDC_QQ,pIndividualUserData->szQQ);
	SetDlgItemText(IDC_EMAIL,pIndividualUserData->szEMail);
	SetDlgItemText(IDC_DWELLING_PLACE,pIndividualUserData->szDwellingPlace);
	return;
}

//���ӵ�������
bool CDlgServiceIndividual::ConnetToServer()
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

//������Ϣ��ѯ��Ϣ
void CDlgServiceIndividual::SendQueryIndividualInfoMsg()
{
	//��������
	tagGlobalUserData& pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//�������ݰ�
	CMD_GP_QueryIndividual QueryIndividual;
	ZeroMemory(&QueryIndividual,sizeof(QueryIndividual));
	QueryIndividual.dwUserID = pGlobalUserData.dwUserID;
	m_SocketHelper->SendData(MDM_GP_USER,SUB_GP_QUERYUSERINDIVIDUAL,&QueryIndividual,sizeof(QueryIndividual));
}

//�����޸���Ϣ��Ϣ
void CDlgServiceIndividual::SendModifyIndividualInfoMsg()
{
	//��������
	tagGlobalUserData& pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//��������
	BYTE cbBuffer[SOCKET_BUFFER];
	ZeroMemory(cbBuffer,sizeof(cbBuffer));
	//��������
	CMD_GP_ModifyIndividual * pModifyIndividual=(CMD_GP_ModifyIndividual *)cbBuffer;
	CSendPacketHelper SendPacket(cbBuffer+sizeof(CMD_GP_ModifyIndividual),sizeof(cbBuffer)-sizeof(CMD_GP_ModifyIndividual));
	//���ñ���
	pModifyIndividual->dwUserID=pGlobalUserData.dwUserID;
	pModifyIndividual->cbGender = m_cbGender;
	pModifyIndividual->cbFaceID = m_cbFaceID;
	lstrcpyn(pModifyIndividual->szPassword,m_szPassword,CountArray(pModifyIndividual->szPassword));
	//�û���
	if (m_szAccounts[0]!=0)
	{
		SendPacket.AddPacket(m_szAccounts,CountStringBuffer(m_szAccounts),DTP_GP_UI_ACCOUNTS);
	}
	//����ǩ��
	if (m_szUnderWrite[0]!=0)
	{
		SendPacket.AddPacket(m_szUnderWrite,CountStringBuffer(m_szUnderWrite),DTP_GP_UI_UNDER_WRITE);
	}
	//�û���ע
	if (m_szUserNote[0]!=0)
	{
		SendPacket.AddPacket(m_szUserNote,CountStringBuffer(m_szUserNote),DTP_GP_UI_USER_NOTE);
	}
	//��ʵ����
	if (m_szCompellation[0]!=0) 
	{
		SendPacket.AddPacket(m_szCompellation,CountStringBuffer(m_szCompellation),DTP_GP_UI_COMPELLATION);
	}
	//���֤
	if (m_szSFZ[0]!=0) 
	{
		SendPacket.AddPacket(m_szSFZ,CountStringBuffer(m_szSFZ),DTP_GP_UI_SFZ);
	}
	//�ֻ�����
	if (m_szMobilePhone[0]!=0)
	{
		SendPacket.AddPacket(m_szMobilePhone,CountStringBuffer(m_szMobilePhone),DTP_GP_UI_MOBILE_PHONE);
	}
	//Q Q ����
	if (m_szQQ[0]!=0) 
	{
		SendPacket.AddPacket(m_szQQ,CountStringBuffer(m_szQQ),DTP_GP_UI_QQ);
	}
	//�����ʼ�
	if (m_szEMail[0]!=0) 
	{
		SendPacket.AddPacket(m_szEMail,CountStringBuffer(m_szEMail),DTP_GP_UI_EMAIL);
	}
	//��ϸ��ַ
	if (m_szDwellingPlace[0]!=0) 
	{
		SendPacket.AddPacket(m_szDwellingPlace,CountStringBuffer(m_szDwellingPlace),DTP_GP_UI_DWELLING_PLACE);
	}
	//��������
	WORD wSendSize=sizeof(CMD_GP_ModifyIndividual)+SendPacket.GetDataSize();
	m_SocketHelper->SendData(MDM_GP_USER,SUB_GP_MODIFY_INDIVIDUAL,cbBuffer,wSendSize);

}

//////////////////////////////////////////////////////////////////////////////////
