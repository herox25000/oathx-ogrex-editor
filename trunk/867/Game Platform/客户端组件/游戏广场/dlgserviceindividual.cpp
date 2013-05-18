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

//构造函数
CDlgServiceIndividual::CDlgServiceIndividual() : CDlgServiceItem(IDD_DLG_SERVICE_INDIVIDUAL)
{
	//设置图标
	m_cbImageIndex=0;

	//服务管理
	m_bQueryMission=false;
	m_bModifyMission=false;

	//帐号资料
	m_cbGender=0;
	ZeroMemory(m_szAccounts,sizeof(m_szAccounts));
	ZeroMemory(m_szPassword,sizeof(m_szPassword));
	ZeroMemory(m_szUnderWrite,sizeof(m_szUnderWrite));

	//详细资料
	ZeroMemory(m_szQQ,sizeof(m_szQQ));
	ZeroMemory(m_szEMail,sizeof(m_szEMail));
	ZeroMemory(m_szUserNote,sizeof(m_szUserNote));
	ZeroMemory(m_szSFZ,sizeof(m_szSFZ));
	ZeroMemory(m_szMobilePhone,sizeof(m_szMobilePhone));
	ZeroMemory(m_szCompellation,sizeof(m_szCompellation));
	ZeroMemory(m_szDwellingPlace,sizeof(m_szDwellingPlace));

	return;
}

//析构函数
CDlgServiceIndividual::~CDlgServiceIndividual()
{
}

//控件绑定
VOID CDlgServiceIndividual::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//其他控件
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDC_SELECT_FACE, m_FaceSelect);
	//编辑控件
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	DDX_Control(pDX, IDC_GAMEID, m_edGameID);
	DDX_Control(pDX, IDC_PASSWORD, m_edPassword);
	DDX_Control(pDX, IDC_UNDER_WRITE, m_edUnderWrite);

	//编辑控件
	DDX_Control(pDX, IDC_QQ, m_edQQ);
	DDX_Control(pDX, IDC_EMAIL, m_edEMail);
	DDX_Control(pDX, IDC_USER_NOTE, m_edUserNote);
	DDX_Control(pDX, IDC_SFZ, m_edSFZ);
	DDX_Control(pDX, IDC_MOBILE_PHONE, m_edMobilePhone);
	DDX_Control(pDX, IDC_COMPELLATION, m_edCompellation);
	DDX_Control(pDX, IDC_DWELLING_PLACE, m_edDwellingPlace);
}


//接口查询
void * __cdecl CDlgServiceIndividual::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}


//创建函数
BOOL CDlgServiceIndividual::OnInitDialog()
{
	__super::OnInitDialog();

	//加载头像
	g_GlobalUnits.m_UserFaceRes->FillImageList(m_ImageList);
	m_FaceSelect.SetImageList(&m_ImageList);
	//插入头像
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

	//帐号信息
	m_edGameID.LimitText(10);	
	m_edAccounts.LimitText(NAME_LEN-1);
	m_edPassword.LimitText(PASS_LEN-1);
	m_edUnderWrite.LimitText(UNDER_WRITE_LEN-1);
	//限制输入
	m_edQQ.LimitText(QQ_LEN-1);
	m_edEMail.LimitText(EMAIL_LEN-1);
	m_edUserNote.LimitText(USER_NOTE_LEN-1);
	m_edSFZ.LimitText(IDCARD_LEN-1);
	m_edMobilePhone.LimitText(MOBILE_PHONE_LEN-1);
	m_edCompellation.LimitText(COMPELLATION_LEN-1);
	m_edDwellingPlace.LimitText(DWELLING_PLACE_LEN-1);
	//加载信息
	LoadAccountsInfo();

	return TRUE;
}

//取消
VOID CDlgServiceIndividual::OnDestroy()
{
	__super::OnDestroy();
	if(m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
}

//确定函数
VOID CDlgServiceIndividual::OnOK()
{
	//变量定义
	tagGlobalUserData& pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//获取密码
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_PASSWORD,szPassword,CountArray(szPassword));
	//帐号信息
	GetControlItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
	int nCharLength = strlen(m_szAccounts);
	if (nCharLength < 6 || nCharLength > 26)
	{
		ShowInformationEx(TEXT("帐号名字的长度最短6个字符,最长13个字符,请重新输入！"),0,MB_ICONERROR,TEXT("用户中心"));
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
	//用户性别
	if (((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->GetCheck()==BST_CHECKED)
		m_cbGender=GENDER_GIRL;
	if (((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->GetCheck()==BST_CHECKED)
		m_cbGender=GENDER_BOY;
	//头像ID
	m_cbFaceID = m_FaceSelect.GetCurSel();
	//加密密码
	CMD5Encrypt::EncryptData(szPassword,m_szPassword);
	//设置变量
	m_bQueryMission=false;
	m_bModifyMission=true;
	//事件处理
	OnMissionStart();
	//发起连接
	if (ConnetToServer()==false) 
	{
		OnMissionConclude();
		return;
	}
	return;
}

//连接事件
bool CDlgServiceIndividual::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//连接结果
	if (nErrorCode!=0)
	{
		//重试任务
		if (ConnetToServer()==true)
		{
			return true;
		}
		//事件处理
		OnMissionConclude();
		//错误提示
		if (m_bQueryMission==true)
		{
			//提示消息
			ShowInformationEx(TEXT("连接服务器超时，用户资料获取失败！"),0,MB_OK|MB_ICONSTOP,TEXT("用户中心"));
		}
		//错误提示
		if (m_bModifyMission==true)
		{
			//提示消息
			ShowInformationEx(TEXT("连接服务器超时，用户资料修改失败！"),0,MB_OK|MB_ICONSTOP,TEXT("用户中心"));
		}

		return true;
	}

	//修改任务
	if (m_bModifyMission==true)
	{
		SendModifyIndividualInfoMsg();
	}
	//查询任务
	if (m_bQueryMission==true)
	{
		SendQueryIndividualInfoMsg();
	}

	return true;
}

//关闭事件
bool CDlgServiceIndividual::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	//提示消息
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//重试任务
		if (ConnetToServer()==true)
		{
			return true;
		}
		//查询任务
		if (m_bQueryMission==true)
		{
			//提示消息
			ShowInformationEx(TEXT("与服务器的连接异常断开了，用户资料获取失败！"),0,MB_ICONERROR,TEXT("用户中心"));
		}

		//修改任务
		if (m_bModifyMission==true)
		{
			//提示消息
			ShowInformationEx(TEXT("与服务器的连接异常断开了，用户资料修改失败！"),0,MB_ICONERROR,TEXT("用户中心"));
		}
	}
	//事件处理
	OnMissionConclude();
	return true;
}

//读取事件
bool CDlgServiceIndividual::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	//命令处理
	if (Command.wMainCmdID==MDM_GP_USER)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_MODIFY_INDIVIDUAL_RESULT:	//修改用户资料返回
			{
				//效验参数
				ASSERT(wDataSize==sizeof(CMD_GP_ModifyIndividual_Ret));
				if (wDataSize!=sizeof(CMD_GP_ModifyIndividual_Ret)) 
					return false;
				//变量定义
				CMD_GP_ModifyIndividual_Ret * Ret=(CMD_GP_ModifyIndividual_Ret *)pData;
				//操作失败
				if(Ret->lResultCode != 0)
				{
					ShowInformationEx(Ret->szDescribeString,60,MB_ICONINFORMATION,TEXT("用户中心"));
				}
				else//处理操作成功
				{
					tagGlobalUserData * pGlobalUserData=g_GlobalUnits.GetGolbalUserDataEx();
					tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();

					//帐号资料
					pGlobalUserData->cbGender = m_cbGender;
					pGlobalUserData->wFaceID = m_cbFaceID;
					lstrcpyn(pGlobalUserData->szAccounts,m_szAccounts,CountArray(pGlobalUserData->szAccounts));
					lstrcpyn(pGlobalUserData->szUnderWrite,m_szUnderWrite,CountArray(pGlobalUserData->szUnderWrite));

					//扩展资料
					lstrcpyn(pIndividualUserData->szQQ,m_szQQ,CountArray(pIndividualUserData->szQQ));
					lstrcpyn(pIndividualUserData->szEMail,m_szEMail,CountArray(pIndividualUserData->szEMail));
					lstrcpyn(pIndividualUserData->szUserNote,m_szUserNote,CountArray(pIndividualUserData->szUserNote));
					lstrcpyn(pIndividualUserData->szSFZ,m_szSFZ,CountArray(pIndividualUserData->szSFZ));
					lstrcpyn(pIndividualUserData->szMobilePhone,m_szMobilePhone,CountArray(pIndividualUserData->szMobilePhone));
					lstrcpyn(pIndividualUserData->szCompellation,m_szCompellation,CountArray(pIndividualUserData->szCompellation));
					lstrcpyn(pIndividualUserData->szDwellingPlace,m_szDwellingPlace,CountArray(pIndividualUserData->szDwellingPlace));
					ShowInformationEx(TEXT("修改成功"),60,MB_ICONINFORMATION,TEXT("用户中心"));
				}
				//成功处理
				OnMissionConclude();
				//关闭连接
				if (m_SocketHelper.GetInterface()!=NULL)
					m_SocketHelper->CloseSocket();
				return true;
			}
		case SUB_GP_QUERYUSERINDIVIDUAL:	//个人信息查询返回
			{
				//效验参数
				ASSERT(wDataSize>=sizeof(CMD_GP_QueryIndividual));
				if (wDataSize<sizeof(CMD_GP_QueryIndividual)) 
					return false;
				//变量定义
				CMD_GP_QueryIndividual * pUserIndividual=(CMD_GP_QueryIndividual *)pData;
				//变量定义
				tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();
				//设置变量
				pIndividualUserData->dwUserID=pUserIndividual->dwUserID;
				//变量定义
				VOID * pDataBuffer=NULL;
				tagDataDescribe DataDescribe;
				CRecvPacketHelper RecvPacket(pUserIndividual+1,wDataSize-sizeof(CMD_GP_QueryIndividual));
				//扩展信息
				while (true)
				{
					pDataBuffer=RecvPacket.GetData(DataDescribe);
					if (DataDescribe.wDataDescribe==DTP_NULL) break;
					switch (DataDescribe.wDataDescribe)
					{
					case DTP_GP_UI_USER_NOTE:		//用户备注
						{
							lstrcpyn(pIndividualUserData->szUserNote,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szUserNote));
							break;
						}
					case DTP_GP_UI_COMPELLATION:	//真实名字
						{
							lstrcpyn(pIndividualUserData->szCompellation,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szCompellation));
							break;
						}
					case DTP_GP_UI_SFZ:		//身份证
						{
							lstrcpyn(pIndividualUserData->szSFZ,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szSFZ));
							break;
						}
					case DTP_GP_UI_MOBILE_PHONE:	//移动电话
						{
							lstrcpyn(pIndividualUserData->szMobilePhone,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szMobilePhone));
							break;
						}
					case DTP_GP_UI_QQ:				//Q Q 号码
						{
							lstrcpyn(pIndividualUserData->szQQ,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szQQ));
							break;
						}
					case DTP_GP_UI_EMAIL:			//电子邮件
						{
							lstrcpyn(pIndividualUserData->szEMail,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szEMail));
							break;
						}
					case DTP_GP_UI_DWELLING_PLACE:	//联系地址
						{
							lstrcpyn(pIndividualUserData->szDwellingPlace,(LPCTSTR)pDataBuffer,CountArray(pIndividualUserData->szDwellingPlace));
							break;
						}
					}
				}
				//成功处理
				OnMissionConclude();
				//更新资料
				UpdateIndividualInfo();
				//关闭连接
				if (m_SocketHelper.GetInterface()!=NULL)
					m_SocketHelper->CloseSocket();

				return true;
			}
		}
	}

	return true;
}

//开始任务
VOID CDlgServiceIndividual::OnMissionStart()
{
	m_FaceSelect.EnableWindow(FALSE);
	//信息控件
	m_edAccounts.EnableWindow(FALSE);
	m_edGameID.EnableWindow(FALSE);
	m_edPassword.EnableWindow(FALSE);
	m_edUnderWrite.EnableWindow(FALSE);

	//详细资料
	m_edQQ.EnableWindow(FALSE);
	m_edEMail.EnableWindow(FALSE);
	m_edUserNote.EnableWindow(FALSE);
	m_edSFZ.EnableWindow(FALSE);
	m_edMobilePhone.EnableWindow(FALSE);
	m_edCompellation.EnableWindow(FALSE);
	m_edDwellingPlace.EnableWindow(FALSE);

	//功能按钮
	m_btOk.EnableWindow(FALSE);
	return;
}

//终止任务
VOID CDlgServiceIndividual::OnMissionConclude()
{
	m_FaceSelect.EnableWindow(TRUE);
	//信息控件
	m_edAccounts.EnableWindow(TRUE);
	m_edGameID.EnableWindow(TRUE);
	m_edPassword.EnableWindow(TRUE);
	m_edUnderWrite.EnableWindow(TRUE);

	//详细资料
	m_edQQ.EnableWindow(TRUE);
	m_edEMail.EnableWindow(TRUE);
	m_edUserNote.EnableWindow(TRUE);
	m_edSFZ.EnableWindow(TRUE);
	m_edMobilePhone.EnableWindow(TRUE);
	m_edCompellation.EnableWindow(TRUE);
	m_edDwellingPlace.EnableWindow(TRUE);
	//功能按钮
	m_btOk.EnableWindow(TRUE);
	//设置控件
	m_edPassword.SetWindowText(TEXT(""));

	return;
}

//帐号信息
VOID CDlgServiceIndividual::LoadAccountsInfo()
{
	//变量定义
	tagGlobalUserData * pGlobalUserData=g_GlobalUnits.GetGolbalUserDataEx();
	tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();
	//用户头像
	m_FaceSelect.SetCurSel(pGlobalUserData->wFaceID);
	//基本资料
	TCHAR tGameID[32]=TEXT("");
	_sntprintf(tGameID,sizeof(tGameID),"%d",pGlobalUserData->dwGameID);
	SetDlgItemText(IDC_GAMEID,tGameID);
	SetDlgItemText(IDC_ACCOUNTS,pGlobalUserData->szAccounts);
	SetDlgItemText(IDC_UNDER_WRITE,pGlobalUserData->szUnderWrite);

	//用户性别
	if (pGlobalUserData->cbGender==GENDER_GIRL) //女 
		((CButton *)GetDlgItem(IDC_GENDER_FEMALE))->SetCheck(BST_CHECKED);
	if (pGlobalUserData->cbGender==GENDER_BOY)//男
		((CButton *)GetDlgItem(IDC_GENDER_MANKIND))->SetCheck(BST_CHECKED);

	//详细资料
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

//查询资料
VOID CDlgServiceIndividual::QueryIndividualInfo()
{
	//设置变量
	m_bQueryMission=true;
	m_bModifyMission=false;

	//事件处理
	OnMissionStart();

	//发起连接
	if (ConnetToServer()==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//更新资料
VOID CDlgServiceIndividual::UpdateIndividualInfo()
{
	//变量定义
	tagIndividualUserData * pIndividualUserData=g_GlobalUnits.GetIndividualUserData();
	//用户资料
	SetDlgItemText(IDC_USER_NOTE,pIndividualUserData->szUserNote);
	SetDlgItemText(IDC_COMPELLATION,pIndividualUserData->szCompellation);
	SetDlgItemText(IDC_SFZ,pIndividualUserData->szSFZ);
	//电话号码
	SetDlgItemText(IDC_MOBILE_PHONE,pIndividualUserData->szMobilePhone);
	//联系资料
	SetDlgItemText(IDC_QQ,pIndividualUserData->szQQ);
	SetDlgItemText(IDC_EMAIL,pIndividualUserData->szEMail);
	SetDlgItemText(IDC_DWELLING_PLACE,pIndividualUserData->szDwellingPlace);
	return;
}

//连接到服务器
bool CDlgServiceIndividual::ConnetToServer()
{
	//创建组件
	if (m_SocketHelper.GetInterface()==NULL)
	{
		//初始化内核
		IUnknownEx * pIUnknownEx=QUERY_ME_INTERFACE(IUnknownEx);
		try 
		{
			IUnknownEx * pIUnknownEx=(IUnknownEx *)QueryInterface(IID_IUnknownEx,VER_IUnknownEx);
			if (m_SocketHelper.CreateInstance()==false) 
			{
				throw TEXT("网络连接失败1，抱歉！");
			}
			if (m_SocketHelper->SetTCPSocketSink(pIUnknownEx)==false) 
			{
				throw TEXT("网络连接失败2，抱歉！");
			}
		}
		catch (...)
		{
			ShowInformationEx(TEXT("网络连接失败3，抱歉！"),0,MB_ICONQUESTION,TEXT("修改资料"));
			return false;
		}
	}
	if (m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
	if(m_SocketHelper->Connect( g_GlobalUnits.m_LogonServerIP, g_GlobalUnits.m_LogonServerPort) != CONNECT_SUCCESS)
	{
		ShowInformationEx(TEXT("网络连接失败4，抱歉"),0,MB_ICONQUESTION,TEXT("修改资料"));
		return false;
	}
	return true;
}

//发送信息查询消息
void CDlgServiceIndividual::SendQueryIndividualInfoMsg()
{
	//变量定义
	tagGlobalUserData& pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//构造数据包
	CMD_GP_QueryIndividual QueryIndividual;
	ZeroMemory(&QueryIndividual,sizeof(QueryIndividual));
	QueryIndividual.dwUserID = pGlobalUserData.dwUserID;
	m_SocketHelper->SendData(MDM_GP_USER,SUB_GP_QUERYUSERINDIVIDUAL,&QueryIndividual,sizeof(QueryIndividual));
}

//发送修改信息消息
void CDlgServiceIndividual::SendModifyIndividualInfoMsg()
{
	//变量定义
	tagGlobalUserData& pGlobalUserData=g_GlobalUnits.GetGolbalUserData();
	//变量定义
	BYTE cbBuffer[SOCKET_BUFFER];
	ZeroMemory(cbBuffer,sizeof(cbBuffer));
	//变量定义
	CMD_GP_ModifyIndividual * pModifyIndividual=(CMD_GP_ModifyIndividual *)cbBuffer;
	CSendPacketHelper SendPacket(cbBuffer+sizeof(CMD_GP_ModifyIndividual),sizeof(cbBuffer)-sizeof(CMD_GP_ModifyIndividual));
	//设置变量
	pModifyIndividual->dwUserID=pGlobalUserData.dwUserID;
	pModifyIndividual->cbGender = m_cbGender;
	pModifyIndividual->cbFaceID = m_cbFaceID;
	lstrcpyn(pModifyIndividual->szPassword,m_szPassword,CountArray(pModifyIndividual->szPassword));
	//用户名
	if (m_szAccounts[0]!=0)
	{
		SendPacket.AddPacket(m_szAccounts,CountStringBuffer(m_szAccounts),DTP_GP_UI_ACCOUNTS);
	}
	//个性签名
	if (m_szUnderWrite[0]!=0)
	{
		SendPacket.AddPacket(m_szUnderWrite,CountStringBuffer(m_szUnderWrite),DTP_GP_UI_UNDER_WRITE);
	}
	//用户备注
	if (m_szUserNote[0]!=0)
	{
		SendPacket.AddPacket(m_szUserNote,CountStringBuffer(m_szUserNote),DTP_GP_UI_USER_NOTE);
	}
	//真实名字
	if (m_szCompellation[0]!=0) 
	{
		SendPacket.AddPacket(m_szCompellation,CountStringBuffer(m_szCompellation),DTP_GP_UI_COMPELLATION);
	}
	//身份证
	if (m_szSFZ[0]!=0) 
	{
		SendPacket.AddPacket(m_szSFZ,CountStringBuffer(m_szSFZ),DTP_GP_UI_SFZ);
	}
	//手机号码
	if (m_szMobilePhone[0]!=0)
	{
		SendPacket.AddPacket(m_szMobilePhone,CountStringBuffer(m_szMobilePhone),DTP_GP_UI_MOBILE_PHONE);
	}
	//Q Q 号码
	if (m_szQQ[0]!=0) 
	{
		SendPacket.AddPacket(m_szQQ,CountStringBuffer(m_szQQ),DTP_GP_UI_QQ);
	}
	//电子邮件
	if (m_szEMail[0]!=0) 
	{
		SendPacket.AddPacket(m_szEMail,CountStringBuffer(m_szEMail),DTP_GP_UI_EMAIL);
	}
	//详细地址
	if (m_szDwellingPlace[0]!=0) 
	{
		SendPacket.AddPacket(m_szDwellingPlace,CountStringBuffer(m_szDwellingPlace),DTP_GP_UI_DWELLING_PLACE);
	}
	//发送数据
	WORD wSendSize=sizeof(CMD_GP_ModifyIndividual)+SendPacket.GetDataSize();
	m_SocketHelper->SendData(MDM_GP_USER,SUB_GP_MODIFY_INDIVIDUAL,cbBuffer,wSendSize);

}

//////////////////////////////////////////////////////////////////////////////////
