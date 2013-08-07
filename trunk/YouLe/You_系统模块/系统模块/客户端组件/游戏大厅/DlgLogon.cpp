#include "Stdafx.h"
#include "Resource.h"
#include "DlgLogon.h"
#include "dlglogon.h"

//��¼��ʽ
#define LOGON_BY_ACCOUNTS				0						//�ʺŵ�¼
#define LOGON_BY_USERID					1						//ID ��¼

////��ɫ����
//#define SELECT_COLOR		RGB(37,56,220)						//ѡ����ɫ

//��Ļλ��
#define LAYERED_SIZE				1									//�ֲ��С
//////////////////////////////////////////////////////////////////////////
//ע���ťID
#define		WM_BT_REGISTERCLOSE		200
#define		WM_BT_REGISTEROK		201
#define		WM_BT_REGISTERMAN		202
#define		WM_BT_REGISTERWOMAN		203

//��½��ťID



BEGIN_MESSAGE_MAP(CDlgRegister, CDialog)
	//ϵͳ��Ϣ
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(WM_BT_REGISTERCLOSE,OnCancel)
	ON_BN_CLICKED(WM_BT_REGISTEROK,OnOK)
	ON_EN_CHANGE(IDC_PASSWORD, OnEnChangeLogonPass)
	ON_CBN_SELCHANGE(IDC_COMBO_CHNEGSHI, OnCbnSelchangeComboChengshi)
	ON_CBN_SELCHANGE(IDC_COMBO_DIQU, OnCbnSelchangeComboDiqu)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgLogon, CDialog)
	//ϵͳ��Ϣ
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_SETCURSOR()
	//ON_EN_CHANGE(IDC_PASSWORD, OnEnChangePassword)
	//ON_CBN_SELCHANGE(IDC_USER_ID, OnSelchangeUserID)
	//ON_CBN_SELCHANGE(IDC_ACCOUNTS, OnSelchangeAccounts)
	ON_BN_CLICKED(WM_BT_CLOSE,OnCancel)
	ON_BN_CLICKED(WM_BT_LOGON,OnOK)
	ON_BN_CLICKED(WM_BT_REGISTER, OnRegisterAccounts)
	ON_BN_CLICKED(WM_BT_WEBHOME, OnWebhome)
	ON_BN_CLICKED(WM_BT_CHONGZHI, OnChongzhi)
	ON_BN_CLICKED(WM_BT_BANBEN, OnBanben)
	ON_CONTROL_RANGE( BN_CLICKED, WM_BT_KEYBOARD_MIN, WM_BT_KEYBOARD_MAX, OnKeyBoard)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
static BOOL GetOptionItem(LPCTSTR lpAppName, LPCTSTR lpKey, LPSTR lpText, int iLen)
{
	char szPath[MAX_PATH];
	::GetModulePath(szPath, sizeof(szPath));
	SafeStrCat(szPath, "\\LogonServer.ini", sizeof(szPath));

	lpText[0]=0;
	return ::GetPrivateProfileString(lpAppName, lpKey, NULL, lpText, iLen, szPath);
}

////////////////////////////////////////////////////////////////////////////


//���캯��
CControlCheckButton::CControlCheckButton()
{
	//���ñ���
	m_cbChecked=false;
	m_pParentSink=NULL;
}

//��������
CControlCheckButton::~CControlCheckButton()
{
}

//����(ֻ�����PNG��Դ)
void CControlCheckButton::CreatCheckButton(CWnd* pParentWnd,HINSTANCE hInstance, LPCTSTR pszResourceName,INT nXPos,INT nYPos)
{
	m_pParentSink = pParentWnd;
	m_ptControlBenchmark.SetPoint(nXPos,nYPos);	
	if(m_ImageBack.IsNull())
		m_ImageBack.LoadImage(hInstance,pszResourceName);
}

//�ؼ�����
CRect CControlCheckButton::GetControlRect()
{
	int width = m_ImageBack.GetWidth();
	int wHeight = m_ImageBack.GetHeight();
	CRect rcClient(m_ptControlBenchmark.x,m_ptControlBenchmark.y,
	m_ptControlBenchmark.x+width/2,m_ptControlBenchmark.y+wHeight);

	return rcClient;
}

//����״̬
VOID  CControlCheckButton::SetButtonChecked(bool cbChecked) 
{ 
	//���ñ���
	m_cbChecked=cbChecked;
	//�������
	CRect rcClient = GetControlRect();
	//�ػ����
	if(m_pParentSink!=NULL) 
		m_pParentSink->InvalidateRect(&rcClient);
};

//���ƿؼ�
VOID  CControlCheckButton::OnDrawControl(CDC * pDC)
{
	//����У��
	if(pDC==NULL)
		return;
	//�������
	INT nImageWidth = m_ImageBack.GetWidth()/2;
	INT nImageHeight = m_ImageBack->GetHeight();
	m_ImageBack.DrawImage(pDC,m_ptControlBenchmark.x, m_ptControlBenchmark.y,
		nImageWidth, nImageHeight,m_cbChecked?nImageWidth:0, 0);
}

//����¼�
bool  CControlCheckButton::OnClickControl(CPoint Point)
{
	//�������
	CRect rcClient = GetControlRect();
	//ѡ���ж�
	if(rcClient.PtInRect(Point))
	{
		//���ñ���
		m_cbChecked=m_cbChecked==false?true:false;
		//�ػ����
		if(m_pParentSink!=NULL)	
			m_pParentSink->InvalidateRect(&rcClient);
		return true;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgRegister::CDlgRegister() : CDialog(IDD_REGISTER)
{
	//��¼��Ϣ
	m_wFaceID=0;
	m_cbGender=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLikeName[0]=0;
	m_szName[0]=0;
	m_szSFZ[0] = 0;
	m_szAddress[0]=0;
	m_cbLogonPassLevel = PASSWORD_LEVEL_0;
	InitChengShiDiQu();
	return;
}

//��������
CDlgRegister::~CDlgRegister()
{
}

//�ؼ���
void CDlgRegister::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT_NAME,m_NameEdit);
	DDX_Control(pDX,IDC_EDIT_SFZ,m_SfzEdit);
	DDX_Control(pDX,IDC_COMBO_CHNEGSHI,m_BoxChengshi);
	DDX_Control(pDX,IDC_COMBO_DIQU,m_BoxDiqu);
}

//��ʼ������
BOOL CDlgRegister::OnInitDialog()
{
	__super::OnInitDialog();
 
	tagPlatformFrameImageNew & FrameViewImage = g_GlobalUnits.m_PlatformFrameImage;
	HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	//������Դ
	if(m_ImageBack.IsNull())
	m_ImageBack.LoadImage(hInstance, FrameViewImage.pszRegisterBack);
	int With = m_ImageBack->GetWidth();
	int Height = m_ImageBack->GetHeight();
	//���ô�С
	CSize SizeWindow(With,Height);
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
	if(m_ImagePasswordLevel.IsNull())
		m_ImagePasswordLevel.LoadImage(hInstance, FrameViewImage.pszPassLevel);

	m_btEixt.CreateButton(this, FrameViewImage.pszBtCloseRegister ,_T("PNG"),With/2+80,Height-60,WM_BT_REGISTERCLOSE,4, hInstance);
	m_btRegisterOk.CreateButton(this, FrameViewImage.pszBtRegisterOk ,_T("PNG"),With/2-130,Height-60,WM_BT_REGISTEROK,4, hInstance);
	m_btMan.CreatCheckButton(this, hInstance, FrameViewImage.pszBtChose,110,277);
	m_btWoman.CreatCheckButton(this, hInstance, FrameViewImage.pszBtChose,170,277);
	m_btMan.SetButtonChecked(true);
	
	m_NameEdit.SetEnableColor(RGB(0,0,0),RGB(147,186,243),RGB(147,186,243));
	m_SfzEdit.SetEnableColor(RGB(0,0,0),RGB(147,186,243),RGB(147,186,243));

	m_BoxChengshi.ResetContent();
	for (int i=0;i<36;i++)
	{
		if(m_StrSheng[i] != NULL)
			m_BoxChengshi.InsertString(i,m_StrSheng[i]);
	}
	m_BoxChengshi.SetCurSel(0);

	m_BoxDiqu.ResetContent();
	m_BoxDiqu.InsertString(0,"����");
	m_BoxDiqu.SetCurSel(0);

	//���д���
	CenterWindow(this);
	//��ȡ����
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	//����λ��
	//CRect rcUnLayered;
	//rcUnLayered.top=LAYERED_SIZE;
	//rcUnLayered.left=LAYERED_SIZE;
	//rcUnLayered.right=rcWindow.Width()-LAYERED_SIZE;
	//rcUnLayered.bottom=rcWindow.Height()-LAYERED_SIZE;
	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);
	//��������
	SetWindowRgn(RgnWindow,FALSE);
	SetActiveWindow();
	BringWindowToTop();
	SetForegroundWindow();
	return TRUE;
}

//ȷ������
void CDlgRegister::OnOK()
{
	CString strBuffer;
	//�û��ʺ�
	GetDlgItemText(IDC_ACCOUNTS,strBuffer);
	strBuffer.TrimLeft();
	strBuffer.TrimRight();
	if (strBuffer.GetLength()<6 || strBuffer.GetLength() > 26)
	{
		ShowInformation(TEXT("�ʺ����ֵĳ������6���ַ�,�13���ַ�,����������ע���ʺţ�"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_ACCOUNTS)->SetFocus();
		return;
	}
	lstrcpyn(m_szAccounts,strBuffer,CountArray(m_szAccounts));

	//�û�����
	GetDlgItemText(IDC_PASSWORD,strBuffer);
	if (strBuffer.GetLength()<6)
	{
		ShowInformation(TEXT("��Ϸ���볤�����Ϊ 6 λ�ַ���������������Ϸ���룡"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD)->SetFocus();
		return;
	}

	//ȷ������
	GetDlgItemText(IDC_PASSWORD2,m_szPassword,CountArray(m_szPassword));
	if (lstrcmp(m_szPassword,strBuffer)!=0)
	{
		ShowInformation(TEXT("��Ϸ������ȷ�����벻һ�£�����������ȷ�����룡"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_PASSWORD2)->SetFocus();
		return;
	}

	//�ǳ�
	GetDlgItemText(IDC_LIKENAME,strBuffer);
	if (strBuffer.GetLength()<4)
	{
		ShowInformation(TEXT("�ǳƱ���4���ֽڻ����ϣ�"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_LIKENAME)->SetFocus();
		return;
	}
	lstrcpyn(m_szLikeName,strBuffer,CountArray(m_szLikeName));

	//��ַ
	if( 0 == m_BoxChengshi.GetCurSel())
	{
		ShowInformation(TEXT("�������ַ��"),10,MB_ICONQUESTION);
		return;
	}
	CString strChengshi;
	m_BoxChengshi.GetWindowText(strChengshi);
	CString strDiqu;
	m_BoxDiqu.GetWindowText(strDiqu);
	strBuffer = strChengshi+strDiqu;
	lstrcpyn(m_szAddress,strBuffer,CountArray(m_szAddress));


	//����
	GetDlgItemText(IDC_EDIT_NAME,strBuffer);
	if (strBuffer.GetLength()<1)
	{
		ShowInformation(TEXT("������������"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_EDIT_NAME)->SetFocus();
		return;
	}
	lstrcpyn(m_szName,strBuffer,CountArray(m_szName));

	//���֤
	GetDlgItemText(IDC_EDIT_SFZ,strBuffer);
	if (strBuffer.GetLength()!=18)
	{
		ShowInformation(TEXT("��������ȷ�����֤���룡"),10,MB_ICONQUESTION);
		GetDlgItem(IDC_EDIT_SFZ)->SetFocus();
		return;
	}
	lstrcpyn(m_szSFZ,strBuffer,CountArray(m_szSFZ));

	m_wFaceID = 1;
	m_cbGender = 0;
	if(m_btMan.GetButtonChecked())
		m_cbGender = 1;
	else
		m_cbGender = 2;

	__super::OnOK();
}

//ȡ����Ϣ
void CDlgRegister::OnCancel()
{
	__super::OnCancel();
}

//�����Ϣ
VOID CDlgRegister::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//ģ�����
	if (Point.y<=CAPTION_SIZE)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}

	return;
}


//��굯��
void CDlgRegister::OnLButtonUp(UINT nFlags, CPoint point)
{
	bool bClick = false;
	if(!bClick)
	{
		if(!m_btWoman.GetButtonChecked())
		{
			bClick = m_btWoman.OnClickControl(point);
			if(bClick)
				m_btMan.SetButtonChecked(false);
		}
	}
	if(!bClick)
	{
		if( !m_btMan.GetButtonChecked())
		{
			bClick = m_btMan.OnClickControl(point);
			if(bClick)
				m_btWoman.SetButtonChecked(false);
		}
	}

	CDialog::OnLButtonUp(nFlags, point);
}


//�滭����
BOOL CDlgRegister::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	//���Ʊ���
	m_ImageBack.DrawImage(pDevC,0,0);
	m_btMan.OnDrawControl(pDevC);
	m_btWoman.OnDrawControl(pDevC);
	//��������ȼ�
	CSize SizePassword;
	SizePassword.SetSize(m_ImagePasswordLevel.GetWidth()/3,m_ImagePasswordLevel.GetHeight()/2);
	m_ImagePasswordLevel.DrawImage(pDevC,100,173,SizePassword.cx*3,SizePassword.cy,0,0);
	if (m_cbLogonPassLevel>=PASSWORD_LEVEL_1)
	{
		INT nImagePos=(m_cbLogonPassLevel-PASSWORD_LEVEL_1)*SizePassword.cx;
		m_ImagePasswordLevel.DrawImage(pDevC,100+nImagePos,173,SizePassword.cx,SizePassword.cy,nImagePos,SizePassword.cy);
	}

	SetButtonBackGrounds(pDevC);

	return TRUE;
}

//��ť����
void CDlgRegister::SetButtonBackGrounds(CDC *pDC)
{
	m_btEixt.SetBkGnd(pDC);
	m_btRegisterOk.SetBkGnd(pDC);
}

//����ȼ�
BYTE CDlgRegister::GetPasswordLevel(LPCTSTR pszPassword)
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


//��½��������
VOID CDlgRegister::OnEnChangeLogonPass()
{
	//��ȡ����
	TCHAR szPassword[PASS_LEN]=TEXT("");
	GetDlgItemText(IDC_PASSWORD,szPassword,CountArray(szPassword));
	//�ȼ��ж�
	BYTE cbPasswordLevel=GetPasswordLevel(szPassword);
	//���´���
	if (m_cbLogonPassLevel!=cbPasswordLevel)
	{
		//���ñ���
		m_cbLogonPassLevel=cbPasswordLevel;
		//���´���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}
}

void CDlgRegister::OnCbnSelchangeComboChengshi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cursel = m_BoxChengshi.GetCurSel();
	TCHAR log[256];
	sprintf(log,TEXT("ʡ�� ��ǰѡ��ID % d \r\n"),cursel);
	OutputDebugString(log);

	m_BoxDiqu.ResetContent();
	for (int i=0;i<21;i++)
	{
		if(m_StrDiqu[cursel][i] != NULL)
			m_BoxDiqu.InsertString(i,m_StrDiqu[cursel][i]);
	}
	m_BoxDiqu.SetCurSel(0);
}

void CDlgRegister::OnCbnSelchangeComboDiqu()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int cursel = m_BoxDiqu.GetCurSel();
	TCHAR log[256];
	sprintf(log,TEXT(" -----������ǰѡ��ID % d \r\n"),cursel);
	OutputDebugString(log);
}

void CDlgRegister::InitChengShiDiQu()
{
	memset(m_StrSheng,0,sizeof(m_StrSheng));
	memset(m_StrDiqu,0,sizeof(m_StrDiqu));

	char* TempChengshi[36] = 
	{
		"ʡ��","����","���","�Ϻ�","����","����","����","������","�ӱ�","ɽ��","����","ɽ��","����","����","����",
			"�㽭","����","�㶫","����","����","����","�Ĵ�","����","����","����","����","�ຣ","���ɹ�","����","�½�",
			"����","����","̨��","���","����","����"
	};
	CopyMemory(m_StrSheng,TempChengshi,sizeof(m_StrSheng));

	char* TempDiqu[36][21] = 
	{
		{"����"}
		,{"����"}
		,{"���"}
		,{"�Ϻ�"}
		,{"����","����","����","����","����"}	
		,{"������","������","��ɽ��","��˳��","��Ϫ��","������","������","��«����","Ӫ����","�̽���","������","������","������","������","��Դ��","��Ʊ��"}
		,{"������","������","��ƽ��","��Դ��","ͨ����","��ɽ��","�ӱ߳�����������","�׳���","��ԭ��"}
		,{"��������","���������","�׸���","˫Ѽɽ��","������","������","������","ĵ������","��ľ˹��","̨����","�ں���","�绯��","���˰������"}
		,{"ʯ��ׯ��","��ɽ��","�ػʵ���","������","��̨��","������","�żҿ���","�е���","�ȷ���","��ˮ��","������"}
		,{"̫ԭ��","��ͬ��","��Ȫ��","������","������","˷����","������","�˳���","������","�ٷ���","��������"}
		,{"֣����","������","������","ƽ��ɽ��","������","�ױ���","������","������","�����","�����","�����","����Ͽ��","������","������","������","�ܿ���","פ�����","��Դ��"}
		,{"������","�ൺ��","�Ͳ���","��ׯ��","��Ӫ��","Ϋ����","��̨��","������","������","̩����","������","������","������","������","�ĳ���","������","������"}
		,{"�Ͼ���","������","���Ƹ���","������","��Ǩ��","�γ���","������","̩����","��ͨ��","����","������","������","������ "}
		,{"�Ϸ���","�ߺ���","������","������","��ɽ��","������","ͭ����","������","��ɽ��","������","������","������","������","������","������","������","������"}
		,{"�ϲ���","Ƽ����","�Ž���","������","ӥ̶��","������","������","�˴���","������","������"}
		,{"������","������","������","������","������","����","������","��ɽ��","̨����","��ˮ��"}
		,{"������","������","������","������","Ȫ����","������","��ƽ��","������","������"}
		,{"������","������","�麣��","��ͷ��","�ع���","������","��Դ��","÷����","��β��","��ݸ��","��ɽ��","������","��ɽ��","������","տ����","ï����","������","��Զ��","������","������","�Ƹ���"}
		,{"������","������"}
		,{"������","����ˮ��","������","��˳��","ͭ�ʵ���","�Ͻڵ���","ǭ���ϲ���������������","ǭ���������嶱��������","ǭ�ϲ���������������"}
		,{"������","��Ϫ��","��ɽ��","��ͨ��","˼é����","�ٲ׵���","��������","��ɽ׳������������","��ӹ���������������","��˫���ɴ���������","��������������","�������������","�º���徰����������","ŭ��������������","�������������"}
		,{"�ɶ���","�Թ���","��֦����","������","������","������","��Ԫ��","������","�ڽ���","��ɽ��","�ϳ���","�˱���","�㰲��","������","üɽ��","�Ű���","������","������","���Ӳ���Ǽ��������","���β���������","��ɽ����������"}
		,{"��ɳ��","������","��̶��","������","������","������","������","�żҽ���","������","������","����","������","¦����","��������������������"}
		,{"�人��","��ʯ��","�差��","ʮ����","������","�˲���","������","������","Т����","�Ƹ���","������","������","��ʩ����������������","ʡֱϽ������λ��������","������","Ǳ����","��ũ������"}
		,{"������","ͭ����","������","������","μ����","�Ӱ���","������","������","������","������"}
		,{"������","�����","������","��ˮ��","��������","������","��Ҵ��","ƽ����","��Ȫ��","������","��������","¤�ϵ���","���ϲ���������","���Ļ���������"}
		,{"������","��������","��������������","���ϲ���������","���ϲ���������","�������������","��������������","�����ɹ������������"}
		,{"���ͺ�����","��ͷ��","�ں���","�����","������˹��","���ױ�����","�����첼��","���ֹ�����","�����׶���","��������","�˰���"}
		,{"������","��������","ɽ�ϵ���","�տ������","�������","��֥����"}
		,{"��³ľ����","����������","��³������","���ܵ���","�������","�����յ���","��ʲ����","�������տ¶�����������","����������","������","����������","���������������","���ǵ���","����̩��","ʡֱϽ������λ��ʯ������","��������","ͼľ�����","�������"}
		,{"������","������","������","������","������","���Ǹ���","������","�����","������","��ɫ��","������","�ӳ���","������","������"}
		,{"������","ʯ��ɽ��","������","��ԭ��"}
		,{"̨��"}
		,{"���"}
		,{"����"}
		,{"����"}
	};
	CopyMemory(m_StrDiqu,TempDiqu,sizeof(m_StrDiqu));
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgLogon::CDlgLogon() : CDialog(IDD_LOGON)
{
	//��¼��Ϣ
	m_wFaceID=0;
	m_cbGender=0;
	m_szAccounts[0]=0;
	m_szPassword[0]=0;
	m_szLikeName[0]=0;
	m_szName[0]=0;
	m_szSFZ[0] = 0;
	m_szAddress[0]=0;
	m_LogonMode=LogonMode_Accounts;
	//������Ϣ
	m_bRegister=false;
	//λ����Ϣ
	m_nFullWidth=0;
	m_nFullHeight=0;
	m_bNetOption=false;
	//���ü�ֵ
	lstrcpyn(m_szKeyboradNumber[0],TEXT("0123456789"),CountArray(m_szKeyboradNumber[0]));
	lstrcpyn(m_szKeyboradNumber[1],TEXT(")!@#$%^&*("),CountArray(m_szKeyboradNumber[1]));
	lstrcpyn(m_szKeyboradChar[0],TEXT("abcdefghijklmnopqrstuvwxyz"),CountArray(m_szKeyboradChar[0]));
	lstrcpyn(m_szKeyboradChar[1],TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ"),CountArray(m_szKeyboradChar[1]));
	m_bCaps = false;
	m_bCreateUI = false;
	m_bHandCur = false;
	m_bLimit = false;
	return;
}

//��������
CDlgLogon::~CDlgLogon()
{
	m_pPlatformFrame = NULL;
	m_bCreateUI = false;
}

//�ؼ���
void CDlgLogon::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNTS, m_edAccounts);
	DDX_Control(pDX, IDC_PASSWORD, m_edPassWord);
}

//��ʼ������
BOOL CDlgLogon::OnInitDialog()
{
	__super::OnInitDialog();
	//������Դ
	tagPlatformFrameImageNew & FrameViewImage = g_GlobalUnits.m_PlatformFrameImage;
	HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	if(m_ImageBack.IsNull())
		m_ImageBack.LoadImage(hInstance, FrameViewImage.pszLoginBack);
	if(m_ImageLimitprompt.IsNull())
		m_ImageLimitprompt.LoadImage(hInstance,FrameViewImage.pszLimitprompt);
	if(m_ImageEighteen.IsNull())
		m_ImageEighteen.LoadImage(hInstance,FrameViewImage.pszEighteen);

	//���ô�С
	CSize SizeWindow(m_ImageBack.GetWidth(),m_ImageBack.GetHeight());
	SetWindowPos(NULL,0,0,SizeWindow.cx,SizeWindow.cy,SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);

	m_edAccounts.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edPassWord.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	//��ס����
	m_RemPwdControl.CreatCheckButton(this, hInstance, FrameViewImage.pszBtCheckBack,165,225);
	
	//���д���
	CenterWindow(this);
	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(LAYERED_SIZE,LAYERED_SIZE,SizeWindow.cx-LAYERED_SIZE+1,SizeWindow.cy-LAYERED_SIZE+1,ROUND_CX,ROUND_CY);
	//��������
	SetWindowRgn(RgnWindow,FALSE);

	LoadLogonServer();
	LoadAccountsInfo();

	CRect rcClient;
	GetClientRect(&rcClient);

	if(!m_bCreateUI)
	{
		m_LogonFramSheet.Create(0,rcClient,this,NULL,NULL);
		m_bCreateUI = true;
	}
	return FALSE;
}

//��Ϣ����
BOOL CDlgLogon::PreTranslateMessage(MSG * pMsg)
{
	return __super::PreTranslateMessage(pMsg);
}

//ȷ������
void CDlgLogon::OnOK()
{
	//Ч������
	if (CheckLogonInput(true)==false)
		return;

	//���ñ���
	m_bRegister=false;

	//��¼�㳡
	ShowWindow(SW_HIDE);
	//IPlazaViewItem * pIPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
	//ASSERT(pIPlazaViewItem!=NULL);
	//pIPlazaViewItem->SendConnectMessage();

	if(m_pPlatformFrame != NULL)
		m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_CONNECT_SERVER,0);
	return;
}

//ȡ����Ϣ
void CDlgLogon::OnCancel()
{
	DestroyWindow();
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
	return;
}

//���͵�¼��
bool CDlgLogon::SendLogonPacket(ITCPSocket * pIClientSocke)
{
	//��������
	TCHAR szPassword[33];
	BYTE cbBuffer[SOCKET_PACKET];
	CMD5Encrypt::EncryptData(m_szPassword,szPassword);

	//��������
	switch (m_LogonMode)
	{
	case LogonMode_Accounts:		//�ʺŵ�¼
		{
			if (m_bRegister==false)
			{
				//��������
				CMD_GP_LogonByAccounts * pLogonByAccounts=(CMD_GP_LogonByAccounts *)cbBuffer;
				memset(pLogonByAccounts,0,sizeof(CMD_GP_LogonByAccounts));
				pLogonByAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
				CopyMemory(pLogonByAccounts->szPassWord,szPassword,sizeof(pLogonByAccounts->szPassWord));
				lstrcpyn(pLogonByAccounts->szAccounts,m_szAccounts,CountArray(pLogonByAccounts->szAccounts));

				//�������к�
				tagClientSerial ClientSerial;
				g_GlobalUnits.GetClientSerial(ClientSerial);

				//�������ݰ�
				CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByAccounts));
				Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
				pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_LOGON_ACCOUNTS,cbBuffer,sizeof(CMD_GP_LogonByAccounts)+Packet.GetDataSize());
			}
			else
			{
				//��������
				CMD_GP_RegisterAccounts * pRegisterAccounts=(CMD_GP_RegisterAccounts *)cbBuffer;
				memset(pRegisterAccounts,0,sizeof(CMD_GP_RegisterAccounts));
				pRegisterAccounts->wFaceID=m_wFaceID;
				pRegisterAccounts->cbGender=m_cbGender;
				pRegisterAccounts->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
				lstrcpyn(pRegisterAccounts->szPassWord,szPassword,CountArray(pRegisterAccounts->szPassWord));
				lstrcpyn(pRegisterAccounts->szAccounts,m_szAccounts,CountArray(pRegisterAccounts->szAccounts));
				
				//�������к�
				tagClientSerial ClientSerial;
				g_GlobalUnits.GetClientSerial(ClientSerial);

				//�������ݰ�
				CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_RegisterAccounts),sizeof(cbBuffer)-sizeof(CMD_GP_RegisterAccounts));
				Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
				pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_REGISTER_ACCOUNTS,cbBuffer,sizeof(CMD_GP_RegisterAccounts)+Packet.GetDataSize());
			}

			break;
		}
	case LogonMode_UserID:			//I D ��¼
		{
			//��������
			CMD_GP_LogonByUserID * pLogonByUserID=(CMD_GP_LogonByUserID *)cbBuffer;
			memset(pLogonByUserID,0,sizeof(CMD_GP_LogonByUserID));
			pLogonByUserID->dwUserID=m_dwUserID;
			pLogonByUserID->dwPlazaVersion=g_GlobalUnits.GetPlazaVersion();
			CopyMemory(pLogonByUserID->szPassWord,szPassword,sizeof(pLogonByUserID->szPassWord));
			
			//�������к�
			tagClientSerial ClientSerial;
			g_GlobalUnits.GetClientSerial(ClientSerial);

			//�������ݰ�
			CSendPacketHelper Packet(cbBuffer+sizeof(CMD_GP_LogonByUserID),sizeof(cbBuffer)-sizeof(CMD_GP_LogonByUserID));
			Packet.AddPacket(&ClientSerial,sizeof(ClientSerial),DTP_COMPUTER_ID);
			pIClientSocke->SendData(MDM_GP_LOGON,SUB_GP_LOGON_USERID,cbBuffer,sizeof(CMD_GP_LogonByUserID)+Packet.GetDataSize());

			break;
		}
	}

	return true;
}

//��¼�ɹ�����
bool CDlgLogon::OnLogonSuccess()
{
	//�û���Ϣ
	tagGlobalUserData & UserData=g_GlobalUnits.GetGolbalUserData();
	//������Ϣ
	TCHAR szBuffer[256];
	_snprintf(szBuffer,sizeof(szBuffer),TEXT("%s"),REG_USER_INFO);
	//д����Ϣ
	CRegKey RegUserInfo;
	if (RegUserInfo.Create(HKEY_CURRENT_USER,szBuffer)==ERROR_SUCCESS)
	{
		RegUserInfo.SetKeyValue(TEXT(""),UserData.szAccounts,TEXT("UserAccount"));
		if (m_RemPwdControl.GetButtonChecked()==TRUE) 
		{
			TCHAR szPassBuffer[256]=TEXT("");
			CXOREncrypt::EncryptData(m_szPassword,szPassBuffer,CountArray(szPassBuffer));
			RegUserInfo.SetKeyValue(TEXT(""),szPassBuffer,TEXT("UserPassword"));
		}
		else
		{
			RegUserInfo.SetKeyValue(TEXT(""),TEXT(""),TEXT("UserPassword"));
		}
	}
	////�رմ���
	DestroyWindow();
	return true;
}

//��ȡ�ʺ�
void CDlgLogon::LoadAccountsInfo()
{
	//����������Ϣ
	CRegKey RegUserAccount;
	RegUserAccount.Open(HKEY_CURRENT_USER,REG_USER_INFO,KEY_READ);
	if (RegUserAccount!=NULL)
	{
		TCHAR szPassWord[256]=TEXT(""),szAccount[256]=TEXT("");
		DWORD dwType=REG_SZ;
		LONG lErrorCode=ERROR_SUCCESS;
		//��Ϸ�ʺ�
		DWORD dwSize=sizeof(szAccount);
		lErrorCode=RegUserAccount.QueryValue(TEXT("UserAccount"),&dwType,szAccount,&dwSize);
		if ((lErrorCode==ERROR_SUCCESS) && szAccount[0]!=0)
		{
			m_edAccounts.SetWindowText(szAccount);
		}
		//��Ϸ����
		dwSize=sizeof(szPassWord);
		lErrorCode=RegUserAccount.QueryValue(TEXT("UserPassword"),&dwType,szPassWord,&dwSize);
		if ((lErrorCode==ERROR_SUCCESS)&&(szPassWord[0]!=0))
		{
			TCHAR szPassBuffer[256]=TEXT("");
			CXOREncrypt::CrevasseData(szPassWord,szPassBuffer,CountArray(szPassWord));
			m_edPassWord.SetWindowText(szPassBuffer);
			if(szPassWord[0]!=0)
			{
				m_RemPwdControl.SetButtonChecked(true);
			}
		}
	}
	m_edAccounts.SetFocus();
	//����ѡ��
	m_edAccounts.SetSel(0,-1,FALSE);
}

//���ط�����
void CDlgLogon::LoadLogonServer()
{
	//��ȡ�����¼������
	char szAppName[256];
	char szName[256];
	char szIP[32];
	_snprintf(szAppName, sizeof(szAppName), "Server0");
	GetOptionItem(szAppName, "Name",  szName, 256);
	GetOptionItem(szAppName, "IPAddress",  szIP, 32);
	m_strLogonServer.Format("%s",szIP);
	return;
}

////������Ϣ
//void CDlgLogon::LoadProxyServerInfo()
//{
//	//��������
//	LPCTSTR szProxyType[]={TEXT("��ʹ�ô���"),TEXT("HTTP ����"),TEXT("SOCKS 4"),TEXT("SOCKS 5")};
//	enProxyServerType ProxyServerType[]={ProxyType_None,ProxyType_Http,ProxyType_Socks4,ProxyType_Socks5};
//
//	//��ȡ��Ϣ
//	enProxyServerType CurrentProxyType=g_GlobalOption.m_ProxyServerType;
//	const tagProxyServerInfo & ProxyServerInfo=g_GlobalOption.m_ProxyServerInfo;
//
//	//��������
//	for (INT i=0;i<CountArray(szProxyType);i++)
//	{
//		ASSERT(i<CountArray(ProxyServerType));
//		INT nItem=m_cmProxyServerType.AddString(szProxyType[i]);
//		m_cmProxyServerType.SetItemData(nItem,ProxyServerType[i]);
//		if (CurrentProxyType==ProxyServerType[i]) m_cmProxyServerType.SetCurSel(nItem);
//	}
//
//	//������Ϣ
//	SetDlgItemText(IDC_PROXY_USER,ProxyServerInfo.szUserName);
//	SetDlgItemText(IDC_PROXY_PASS,ProxyServerInfo.szPassword);
//	SetDlgItemText(IDC_PROXY_SERVER,ProxyServerInfo.szProxyServer);
//	if (ProxyServerInfo.wProxyPort!=0) SetDlgItemInt(IDC_PROXY_PORT,ProxyServerInfo.wProxyPort);
//
//	//����ѡ��
//	if (m_cmProxyServerType.GetCurSel()==CB_ERR) m_cmProxyServerType.SetCurSel(0);
//
//	return;
//}

////��������
//int CDlgLogon::ComboBoxFindString(CComboBox * pComboBox, LPCTSTR pszFindString)
//{
//	CString strBuffer;
//	int iItemHandle=LB_ERR,iItemFind=LB_ERR;
//	int nStringLen=lstrlen(pszFindString);
//	do 
//	{
//		iItemFind=pComboBox->FindString((iItemHandle==LB_ERR)?0:(iItemHandle+1),pszFindString);
//		if ((iItemFind==LB_ERR)||(iItemHandle==iItemFind)||(iItemFind<iItemHandle)) return LB_ERR;
//		iItemHandle=iItemFind;
//		pComboBox->GetLBText(iItemHandle,strBuffer);
//		if (pComboBox->GetLBTextLen(iItemHandle)==nStringLen) return iItemHandle;
//	} while (true);
//	return LB_ERR;
//}

//Ч������
bool CDlgLogon::CheckLogonInput(bool bShowError)
{
	UINT uControlID=0;
	try
	{
		//��ȡ��Ϣ
		GetDlgItemText(IDC_ACCOUNTS,m_szAccounts,CountArray(m_szAccounts));
		if (m_szAccounts[0] == 0)
		{
			uControlID=IDC_ACCOUNTS;
			throw TEXT("�û���¼�ʺŲ���Ϊ�գ������������¼�ʺţ�");
		}

		//��ȡ����
		GetDlgItemText(IDC_PASSWORD,m_szPassword,CountArray(m_szPassword));
		if (m_szPassword[0] == 0)
		{
			uControlID=IDC_PASSWORD;
			throw TEXT("��¼���벻��Ϊ�գ������������¼���룡");
		}
		return true;
	}
	catch (LPCTSTR pszError)
	{
		if (bShowError)
		{
			ShowWindow(SW_SHOW);
			BringWindowToTop();
			ShowInformation(pszError,0,MB_ICONQUESTION);
			if (uControlID!=0) 
				GetDlgItem(uControlID)->SetFocus();
		}

	}
	return false;
}
//
////����ѡ��
//void CDlgLogon::UpdateUserComboBox(UINT uComboBoxID)
//{
//	//��ȡ ID
//	CComboBox * pComboBox=(CComboBox *)GetDlgItem(uComboBoxID);
//	DWORD dwUserDBID=(DWORD)pComboBox->GetItemData(pComboBox->GetCurSel());
//
//	//������Ϣ
//	UpdateUserPassWord(dwUserDBID);
//	UINT uComboBoxIDs[]={IDC_ACCOUNTS,IDC_USER_ID};
//	for (int i=0;i<CountArray(uComboBoxIDs);i++)
//	{
//		pComboBox=(CComboBox *)GetDlgItem(uComboBoxIDs[i]);
//		for (int j=0;j<pComboBox->GetCount();j++)
//		{
//			DWORD dwComboBoxID=(DWORD)pComboBox->GetItemData(j);
//			if ((dwComboBoxID!=0L)&&(dwComboBoxID==dwUserDBID))
//			{
//				pComboBox->SetCurSel(j);
//				break;
//			}
//		}
//	}
//
//	return;
//}
//
////��������
//void CDlgLogon::UpdateUserPassWord(DWORD dwUserDBID)
//{
//	if (dwUserDBID!=0L)
//	{
//		//ע����ַ�
//		CString strRegKey;
//		strRegKey.Format(TEXT("%s\\%ld"),REG_USER_INFO,dwUserDBID);
//
//		//��ע���
//		CRegKey RegPassWord;
//		RegPassWord.Open(HKEY_CURRENT_USER,strRegKey,KEY_READ);
//		if (RegPassWord!=NULL)
//		{
//			DWORD dwType=REG_SZ;
//			TCHAR szPassBuffer[256]=TEXT("");
//			DWORD dwBufferLength=sizeof(szPassBuffer);
//			if (RegPassWord.QueryValue(TEXT("UserPassword"),&dwType,szPassBuffer,&dwBufferLength)==ERROR_SUCCESS)
//			{
//				m_szPassword[0]=0;
//				CXOREncrypt::CrevasseData(szPassBuffer,m_szPassword,CountArray(m_szPassword));
//				if (m_szPassword[0]==0) 
//					SetDlgItemText(IDC_PASSWORD,TEXT(""));
//				else 
//					SetDlgItemText(IDC_PASSWORD,TEXT("**********"));
//				m_bChangePassWord=false;
//				return;
//			}
//		}
//	}
//
//	//������Ϣ
//	m_szPassword[0]=0;
//	SetDlgItemText(IDC_PASSWORD,TEXT(""));
//	m_bChangePassWord=false;
//	
//	return;
//}

////����ģʽ
//void CDlgLogon::SwitchNetOption(bool bNetOption)
//{
//	//���ñ���
//	m_bNetOption=bNetOption;
//
//	//�ؼ�����
//	GetDlgItem(IDC_PROXY_TYPE)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_PORT)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_USER)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_PASS)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_TEST)->EnableWindow(m_bNetOption);
//	GetDlgItem(IDC_PROXY_SERVER)->EnableWindow(m_bNetOption);
//
//	//�ƶ�λ��
//	INT nHeight=m_bNetOption?m_nFullHeight:m_rcNormalFrame.Height();
//	SetWindowPos(NULL,0,0,m_nFullWidth,nHeight,SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);
//
//	return;
//}
//
////����ı�
//void CDlgLogon::OnEnChangePassword()
//{
//	m_bChangePassWord=true;
//}
//
////ѡ��ı�
//void CDlgLogon::OnSelchangeAccounts()
//{
//	UpdateUserComboBox(IDC_ACCOUNTS);
//	return;
//}
//
////ѡ��ı�
//void CDlgLogon::OnSelchangeUserID()
//{
//	UpdateUserComboBox(IDC_USER_ID);
//	return;
//}


//ע���ʺ�
void CDlgLogon::OnRegisterAccounts()
{
	CDlgRegister DlgRegister;
	ShowWindow(SW_HIDE);
	if (DlgRegister.DoModal()!=IDOK) 
	{
		ShowWindow(SW_SHOW);
		return;
	}
	//���ñ���
	m_bRegister=true;
	m_wFaceID=DlgRegister.m_wFaceID;
	m_cbGender=DlgRegister.m_cbGender;
	lstrcpy(m_szAccounts,DlgRegister.m_szAccounts);
	lstrcpy(m_szPassword,DlgRegister.m_szPassword);
	lstrcpy(m_szSFZ,DlgRegister.m_szSFZ);
	lstrcpy(m_szName,DlgRegister.m_szName);
	lstrcpy(m_szAddress,DlgRegister.m_szAddress);
	lstrcpy(m_szLikeName,DlgRegister.m_szLikeName);

	//��¼�㳡
	ShowWindow(SW_HIDE);
	//IPlazaViewItem * pIPlazaViewItem=((CGameFrame*)AfxGetMainWnd())->GetPlazaViewItem();
	//ASSERT(pIPlazaViewItem!=NULL);
	//pIPlazaViewItem->SendConnectMessage();
	if(m_pPlatformFrame != NULL)
		m_pPlatformFrame->PostMessage(WM_COMMAND,IDM_CONNECT_SERVER,0);
	return;
}

void CDlgLogon::OnWebhome()
{
	ShellExecute(NULL,TEXT("OPEN"),TEXT("www.youle8.com"),NULL,NULL,SW_NORMAL);
}

void CDlgLogon::OnChongzhi()
{
	ShellExecute(NULL,TEXT("OPEN"),TEXT("www.youle8.com"),NULL,NULL,SW_NORMAL);
}

void CDlgLogon::OnBanben()
{
	ShellExecute(NULL,TEXT("OPEN"),TEXT("www.youle8.com"),NULL,NULL,SW_NORMAL);
}


//�ػ���Ϣ
void CDlgLogon::OnPaint()
{
	return;
}

//�滭����
BOOL CDlgLogon::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);
	CMemDC pDevC(pDC, rcClient);
	m_ImageBack.DrawImage(pDevC,0,0);
	m_RemPwdControl.OnDrawControl(pDevC);
	m_LogonFramSheet.Draw(pDevC);
	m_ImageEighteen.DrawImage(pDevC,350,225);
	if(m_bLimit)
		m_ImageLimitprompt.DrawImage(pDevC,268,225+20);

	return TRUE;
}


//�����Ϣ
VOID CDlgLogon::OnLButtonDown(UINT nFlags, CPoint Point)
{
	m_LogonFramSheet.InjectLeftDown(Point);
	//ģ�����
	CRect client;
	GetClientRect(&client);
	if (Point.y<=CAPTION_SIZE && (IsZoomed()==FALSE) && (Point.x <= (client.Width() - 50)))
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));
	}
	return __super::OnLButtonDown(nFlags,Point);
}


//��굯��
void CDlgLogon::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_LogonFramSheet.InjectLeftUp(point);
	//ѡ���¼�
	m_RemPwdControl.OnClickControl(point);
	__super::OnLButtonUp(nFlags, point);
}

//
void CDlgLogon::OnMouseMove(UINT nFlags, CPoint point)
{
	m_LogonFramSheet.InjectMouseMove(point);
	m_bHandCur = false;
	CRect rcClient;
	GetClientRect(&rcClient);
	if(point.x >= 27 && point.x <= rcClient.right-27 
		&& point.y >= 272 && point.y <= rcClient.bottom-65 )
		m_bHandCur = true;
	if(point.x >= 350 && point.x < 350+27 
		&& point.y >= 225 && point.y < 225+20)
	{
		if(!m_bLimit)
			Invalidate(TRUE);
		m_bLimit = true;
	}
	else
	{
		if(m_bLimit)
			Invalidate(TRUE);
		m_bLimit = false;
	}
	__super::OnMouseMove(nFlags,point);
}

//�����Ϣ
BOOL CDlgLogon::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//���ù��
	if (m_bHandCur)
	{
		SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_HAND_CUR)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

////�ؼ��ı�
//void CDlgLogon::OnEnChangeAccounts()
//{
//	//�������
//	if(m_PasswordControl.m_hWnd!=NULL && m_PasswordControl.IsFalsityPassword()==true)
//	{
//		//��������
//		m_PasswordControl.SetUserPassword(TEXT(""));
//
//		//��ȫ����
//		m_RemPwdControl.SetButtonChecked(FALSE);
//	}
//}
//
////��ȡ����
//void CDlgLogon::GetProxyInfo(enProxyServerType &ProxyServerType, tagProxyServerInfo &ProxyServerInfo)
//{
//	//��������
//	CComboBox * pComProxyType=(CComboBox *)GetDlgItem(IDC_PROXY_TYPE);
//	ProxyServerType=(enProxyServerType)pComProxyType->GetItemData(pComProxyType->GetCurSel());
//
//	//������Ϣ
//	ZeroMemory(&ProxyServerInfo,sizeof(ProxyServerInfo));
//	ProxyServerInfo.wProxyPort=GetDlgItemInt(IDC_PROXY_PORT);
//	GetDlgItemText(IDC_PROXY_USER,ProxyServerInfo.szUserName,CountArray(ProxyServerInfo.szUserName));
//	GetDlgItemText(IDC_PROXY_PASS,ProxyServerInfo.szPassword,CountArray(ProxyServerInfo.szPassword));
//	GetDlgItemText(IDC_PROXY_SERVER,ProxyServerInfo.szProxyServer,CountArray(ProxyServerInfo.szProxyServer));
//
//	//Ч�����
//	if (ProxyServerType!=ProxyType_None)
//	{
//		//�����ַ
//		if (ProxyServerInfo.szProxyServer[0]==0)
//		{
//			if (m_bNetOption==false) SwitchNetOption(true);
//			m_edProxyServer.SetFocus();
//			throw TEXT("�����������ַ����Ϊ�գ����������룡");
//		}
//
//		//����˿�
//		if (ProxyServerInfo.wProxyPort==0)
//		{
//
//			if (m_bNetOption==false) SwitchNetOption(true);
//			m_edProxyPort.SetFocus();
//			throw TEXT("���������������˿ںţ����磺1080��");
//		}
//	}
//}

//��Ӧ�����
void CDlgLogon::OnKeyBoard(UINT uID)
{
	int nInx = uID - WM_BT_KEYBOARD_MIN;
	switch(nInx)
	{
	case 0: //ɾ����ť
		{
			m_edPassWord.SetFocus();
			m_edPassWord.SendMessage(WM_CHAR,VK_BACK,0L);
			break;
		}
	case 1: //��д
		{
			OutputDebugString("��д \r\n");
			m_bCaps = !m_bCaps;
			for (int i=0;i<52;i++)
			{
				if(i<26)
					m_LogonFramSheet.m_pBtAlphabet[i]->VisibleWidget(!m_bCaps);
				else
					m_LogonFramSheet.m_pBtAlphabet[i]->VisibleWidget(m_bCaps);
			}

			CRect rcClient;
			GetClientRect(&rcClient);
			rcClient.top = 250;
			InvalidateRect(rcClient,TRUE);
			break;
		}
	default:
		{
			m_edPassWord.SetFocus();
			//���ּ�
			WORD wViraulCode = 0;
			if((nInx >= 2) && (nInx < 12))
			{
				OutputDebugString("��������ּ� \r\n");

				if((GetKeyState(VK_SHIFT)&0xF0)>0)
					wViraulCode = (WORD)m_szKeyboradNumber[1][nInx-2];
				else
					wViraulCode = (WORD)m_szKeyboradNumber[0][nInx-2];
			}
			else//��ĸ��
			{
				OutputDebugString("�������ĸ \r\n");
				
				if(m_bCaps)
					wViraulCode = (WORD)m_szKeyboradChar[1][nInx-12-26];
				else
					wViraulCode = (WORD)m_szKeyboradChar[0][nInx-12];
			}
			TCHAR log[256];
			sprintf(log,_T("ֵ��%d  \r\n"),wViraulCode);
			OutputDebugString(log);
			m_edPassWord.SendMessage(WM_CHAR,wViraulCode,0L);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

