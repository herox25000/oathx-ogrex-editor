#include "Stdafx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "DlgGameOption.h"

//////////////////////////////////////////////////////////////////////////

//λ�ö���
#define SPACE_TOP					10									//����С
#define SPACE_LEFT					10									//����С
#define SPACE_RIGHT					10									//����С
#define SPACE_BOTTOM				40									//����С

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgGameOption, CSkinDialog)
	ON_WM_SIZE()
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_DEFAULT, OnBnClickedDefault)
	ON_NOTIFY(TCN_SELCHANGE, IDC_ITEM_TAB, OnTcnSelchangeTabControl)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CGeneralOptionItem::CGeneralOptionItem()
{
	//Ĭ�ϲ���
	DefaultParameter();

	return;
}

//�����ؼ�
bool __cdecl CGeneralOptionItem::CreateOptionItem(CWnd * pParentWnd)
{
	//��������
	if (m_hWnd==NULL)
	{
		AfxSetResourceHandle(GetModuleHandle(GAME_FRAME_DLL_NAME));
		Create(IDD_GENERAL_OPTION,pParentWnd);
		AfxSetResourceHandle(GetModuleHandle(NULL));
	}

	//���¿���
	UpdateItemControl();

	return true;
}

//��������
bool __cdecl CGeneralOptionItem::SaveParameter()
{
	//��ȡ����
	if (m_hWnd!=NULL)
	{
		//�Թ�ѡ��
		m_bAllowLookon=(IsDlgButtonChecked(IDC_ALLOW_LOOKON)==BST_CHECKED)?true:false;
		m_bAllowFriendLookon=(IsDlgButtonChecked(IDC_ALLOW_FRIEND_LOOKON)==BST_CHECKED)?true:false;

		//����ѡ��
		m_bAllowSound=(IsDlgButtonChecked(IDC_ALLOW_SOUND)==BST_CHECKED)?true:false;
		m_bAllowBackGroundSound=(IsDlgButtonChecked(IDC_ALLOW_BACK_SOUND)==BST_CHECKED)?true:false;
		m_bFullGameView=(IsDlgButtonChecked(IDC_FULL_GAME_VIEW)==BST_CHECKED)?true:false;
		m_bDebarDetestChat=(IsDlgButtonChecked(IDC_DEBAR_DETEST_CHAT)==BST_CHECKED)?true:false;
		m_bNotifyUserInOut=(IsDlgButtonChecked(IDC_NOTIFY_USER_INOUT)==BST_CHECKED)?true:false;
	}

	return true;
}

//Ĭ�ϲ���
bool __cdecl CGeneralOptionItem::DefaultParameter()
{
	//�Թ�ѡ��
	m_bAllowLookon=false;
	m_bAllowFriendLookon=false;
	
	//����ѡ��
	m_bAllowSound=true;
	m_bAllowBackGroundSound=true;
	m_bFullGameView=true;
	m_bDebarDetestChat=true;
	m_bNotifyUserInOut=true;

	//���¿���
	UpdateItemControl();

	return true;
}

//���¿���
VOID CGeneralOptionItem::UpdateItemControl()
{
	//���ÿؼ�
	if (m_hWnd!=NULL)
	{
		//�Թ�ѡ��
		CheckDlgButton(IDC_ALLOW_LOOKON,(m_bAllowLookon==true)?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_ALLOW_FRIEND_LOOKON,(m_bAllowFriendLookon==true)?BST_CHECKED:BST_UNCHECKED);

		//����ѡ��
		CheckDlgButton(IDC_ALLOW_SOUND,(m_bAllowSound==true)?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_ALLOW_BACK_SOUND,(m_bAllowBackGroundSound==true)?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_FULL_GAME_VIEW,(m_bFullGameView==true)?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_DEBAR_DETEST_CHAT,(m_bDebarDetestChat==true)?BST_CHECKED:BST_UNCHECKED);
		CheckDlgButton(IDC_NOTIFY_USER_INOUT,(m_bNotifyUserInOut==true)?BST_CHECKED:BST_UNCHECKED);
	}

	return;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CDlgGameOption::CDlgGameOption() : CSkinDialog(IDD_GAME_OPTION)
{
	//���ñ���
	m_pIGameOptionItem=NULL;

	return;
}

//��������
CDlgGameOption::~CDlgGameOption()
{
	return;
}

//�ؼ���
VOID CDlgGameOption::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDCANCEL, m_btCancel);
	DDX_Control(pDX, IDC_DEFAULT, m_btDefault);
	DDX_Control(pDX, IDC_ITEM_TAB, m_SkinTabControl);
}

//��ʼ������
BOOL CDlgGameOption::OnInitDialog()
{
	__super::OnInitDialog();

	//��������
	CSize ItemSize(0,0);
	m_SkinTabControl.SetItemSize(CSize(150,25));

	//�����
	for (INT_PTR i=0;i<m_GameOptionItemArray.GetCount();i++)
	{
		//��ȡ����
		IGameOptionItem * pIGameOptionItem=m_GameOptionItemArray[i];

		//��������
		pIGameOptionItem->CreateOptionItem(&m_SkinTabControl);
		m_SkinTabControl.InsertItem((INT)i,pIGameOptionItem->GetItemTitle());

		//����λ��
		CSize CurrentSize;
		pIGameOptionItem->GetControlMinSize(CurrentSize);
		ItemSize.SetSize(__max(CurrentSize.cx,ItemSize.cx),__max(CurrentSize.cy,ItemSize.cy));
	}

	//����λ��
	CRect rcControl(0,0,ItemSize.cx,ItemSize.cy);
	m_SkinTabControl.AdjustRect(TRUE,&rcControl);

	//��ʾ����
	if (m_GameOptionItemArray.GetCount()>0)
	{
		m_pIGameOptionItem=m_GameOptionItemArray[0];
		::ShowWindow(m_pIGameOptionItem->GetWindowHwnd(),SW_SHOW);
	}

	//��������
	INT nTViewBorder=m_SkinAttribute.m_EncircleInfoView.nTBorder;
	INT nBViewBorder=m_SkinAttribute.m_EncircleInfoView.nBBorder;
	INT nLViewBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRViewBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;
	
	//�����ؼ�
	INT nWindowWidth=rcControl.Width()+SPACE_RIGHT+SPACE_LEFT+nLViewBorder*2;
	INT nWindowHeight=nTViewBorder+rcControl.Height()+SPACE_TOP+SPACE_BOTTOM+nBViewBorder;
	SetWindowPos(NULL,0,0,nWindowWidth,nWindowHeight,SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE);

	//���д���
	CenterWindow(AfxGetMainWnd());

	//���ñ���
	SetWindowText(TEXT("��Ϸ���ã�"));

	return FALSE;
}

//ȷ����Ϣ
VOID CDlgGameOption::OnOK() 
{
	//��������
	for (INT_PTR i=0;i<m_GameOptionItemArray.GetCount();i++)
	{
		//��ȡ����
		IGameOptionItem * pIGameOptionItem=m_GameOptionItemArray[i];

		//��������
		if (pIGameOptionItem->SaveParameter()==false)
		{
			//��ʾ����
			if (m_pIGameOptionItem!=pIGameOptionItem)
			{
				//��ʾ����
				::ShowWindow(pIGameOptionItem->GetWindowHwnd(),SW_SHOW);
				if (m_pIGameOptionItem!=NULL) ::ShowWindow(m_pIGameOptionItem->GetWindowHwnd(),SW_HIDE);

				//���ñ���
				m_pIGameOptionItem=pIGameOptionItem;
			}

			return;
		}
	}

	__super::OnOK();
}

//��Ϸ����
bool CDlgGameOption::CreateGameOption(IUnknownEx * pIUnknownEx[], WORD wItemCount)
{
	CGlobalUnits *pGlobalUnits=CGlobalUnits::GetInstance();
	//���ò���
	m_GeneralOptionItem.m_bAllowLookon=pGlobalUnits->m_bAllowLookon;
	m_GeneralOptionItem.m_bAllowFriendLookon=pGlobalUnits->m_bAllowFriendLookon;

	//����ѡ��
	m_GeneralOptionItem.m_bAllowSound=pGlobalUnits->m_bAllowSound;
	m_GeneralOptionItem.m_bAllowBackGroundSound=pGlobalUnits->m_bAllowBackGroundSound;
	m_GeneralOptionItem.m_bFullGameView=pGlobalUnits->m_bFullGameView;
	m_GeneralOptionItem.m_bDebarDetestChat=pGlobalUnits->m_bDebarDetestChat;
	m_GeneralOptionItem.m_bNotifyUserInOut=pGlobalUnits->m_bNotifyUserInOut;

	//��������
	m_GameOptionItemArray.Add(QUERY_OBJECT_INTERFACE(m_GeneralOptionItem,IGameOptionItem));

	//��Ϸ����
	for (WORD i=0;i<wItemCount;i++)
	{
		//��ѯ�ӿ�
		ASSERT(pIUnknownEx[i]!=NULL);
		IGameOptionItem * pIGameOptionItem=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx[i],IGameOptionItem);

		//��������
		ASSERT(pIGameOptionItem!=NULL);
		if (pIGameOptionItem!=NULL) m_GameOptionItemArray.Add(pIGameOptionItem);
	}

	//��ʾ����
	if (DoModal()==IDOK)
	{
		//�Թ�ѡ��
		pGlobalUnits->m_bAllowLookon=m_GeneralOptionItem.m_bAllowLookon;
		pGlobalUnits->m_bAllowFriendLookon=m_GeneralOptionItem.m_bAllowFriendLookon;

		//����ѡ��
		pGlobalUnits->m_bAllowSound=m_GeneralOptionItem.m_bAllowSound;
		pGlobalUnits->m_bAllowBackGroundSound=m_GeneralOptionItem.m_bAllowBackGroundSound;
		pGlobalUnits->m_bFullGameView=m_GeneralOptionItem.m_bFullGameView;
		pGlobalUnits->m_bDebarDetestChat=m_GeneralOptionItem.m_bDebarDetestChat;
		pGlobalUnits->m_bNotifyUserInOut=m_GeneralOptionItem.m_bNotifyUserInOut;

		//��ѯ�ӿ�
		ASSERT(g_GlobalUnits.QueryGlobalModule(MODULE_GAME_FRAME_WND,IID_IGameFrameWnd,VER_IGameFrameWnd));
		IGameFrameWnd * pIGameFrameWnd=(IGameFrameWnd *)g_GlobalUnits.QueryGlobalModule(MODULE_GAME_FRAME_WND,IID_IGameFrameWnd,VER_IGameFrameWnd);

		//Ӧ��ѡ��
		if (pIGameFrameWnd!=NULL) 
		{
			pIGameFrameWnd->OnGameOptionChange();
		}

		return true;
	}

	return false;
}

//Ĭ�ϰ�ť
VOID CDlgGameOption::OnBnClickedDefault()
{
	//Ĭ�ϲ���
	for (INT_PTR i=0;i<m_GameOptionItemArray.GetCount();i++)
	{
		IGameOptionItem * pIGameOptionItem=m_GameOptionItemArray[i];
		if (pIGameOptionItem!=NULL) pIGameOptionItem->DefaultParameter();
	}

	return;
}

//������Ϣ
VOID CDlgGameOption::OnNcDestroy()
{
	//ɾ������
	m_pIGameOptionItem=NULL;
	m_GameOptionItemArray.RemoveAll();

	__super::OnNcDestroy();
}

//λ����Ϣ
VOID CDlgGameOption::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType,cx,cy);

	//��������
	INT nTViewBorder=m_SkinAttribute.m_EncircleInfoView.nTBorder;
	INT nBViewBorder=m_SkinAttribute.m_EncircleInfoView.nBBorder;
	INT nLViewBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRViewBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;

	//�ƶ�����
	if (m_SkinTabControl.m_hWnd!=NULL)
	{
		//�ƶ�ѡ��
		m_SkinTabControl.MoveWindow(SPACE_LEFT+nLViewBorder,nTViewBorder+SPACE_TOP,
			cx-SPACE_LEFT-SPACE_RIGHT-nLViewBorder*2,cy-nTViewBorder-SPACE_TOP-SPACE_BOTTOM-nRViewBorder);

		//����λ��
		CRect rcItem;
		m_SkinTabControl.GetClientRect(&rcItem);
		m_SkinTabControl.AdjustRect(FALSE,&rcItem);

		//��������
		for (INT_PTR i=0;i<m_GameOptionItemArray.GetCount();i++)
		{
			IGameOptionItem * pIGameOptionItem=m_GameOptionItemArray[i];
			::MoveWindow(pIGameOptionItem->GetWindowHwnd(),1,27,rcItem.Width()-2,rcItem.Height()-28,FALSE);
		}
	}

	//�ƶ���ť
	if (m_btOk.m_hWnd!=NULL)
	{
		//��ȡ��С
		CRect rcButton;
		m_btOk.GetWindowRect(&rcButton);

		//�ƶ���ť
		INT nButtonSpace=(cx-rcButton.Width()*3-nLViewBorder*2)/6;
		INT nYButtonPos=cy-nRViewBorder-SPACE_BOTTOM/2-rcButton.Height()/2;
		m_btOk.SetWindowPos(NULL,nLViewBorder+nButtonSpace*2,nYButtonPos,0,0,SWP_NOZORDER|SWP_NOSIZE);
		m_btCancel.SetWindowPos(NULL,rcButton.Width()+nLViewBorder+nButtonSpace*3,nYButtonPos,0,0,SWP_NOZORDER|SWP_NOSIZE);
		m_btDefault.SetWindowPos(NULL,rcButton.Width()*2+nLViewBorder+nButtonSpace*4,nYButtonPos,0,0,SWP_NOZORDER|SWP_NOSIZE);
	}

	return;
}

//����ı�
VOID CDlgGameOption::OnTcnSelchangeTabControl(NMHDR * pNMHDR, LRESULT * pResult)
{
	//��ȡѡ��
	INT nCurrentSel=m_SkinTabControl.GetCurSel();
	IGameOptionItem * pISelectItem=m_GameOptionItemArray[nCurrentSel];

	//�ı䴦��
	if (pISelectItem!=m_pIGameOptionItem)
	{
		//��ʾ����
		::ShowWindow(pISelectItem->GetWindowHwnd(),SW_SHOW);
		if (m_pIGameOptionItem!=NULL) ::ShowWindow(m_pIGameOptionItem->GetWindowHwnd(),SW_HIDE);

		//���ñ���
		m_pIGameOptionItem=pISelectItem;
	}

	return;
}

//////////////////////////////////////////////////////////////////////////
