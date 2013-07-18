#include "StdAfx.h"
#include "Winable.h"
#include "Resource.h"
#include "PasswordControl.h"

//////////////////////////////////////////////////////////////////////////////////


//�ؼ���ʶ
#define IDC_BT_KEYBOARD				100									//���̰�ť
#define IDC_ED_PASSWORD				200									//����ؼ�

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPasswordControl, CWnd)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_ED_PASSWORD, OnEnChangePassword)
	ON_BN_CLICKED(IDC_BT_KEYBOARD, OnBnClickedKeyboard)
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPasswordControl::CPasswordControl()
{
	//���ñ���
	m_bModify=false;
	m_bFalsity=false;
	m_bDrawBorad=true;
	m_bRenderImage=true;
	ZeroMemory(m_szPassword,sizeof(m_szPassword));

	return;
}

//��������
CPasswordControl::~CPasswordControl()
{
}

//�󶨺���
VOID CPasswordControl::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	//��ȡλ��
	CRect rcClient;
	CRect rcWindow;
	GetClientRect(&rcClient);
	GetWindowRect(&rcWindow);

	//������ť
	CRect rcButton(0,0,0,0);

	//�����ؼ�
	CRect rcEditCreate;
	rcEditCreate.top=4;
	rcEditCreate.left=4;
	rcEditCreate.bottom=16;
	rcEditCreate.right=rcClient.Width();
	m_edPassword.Create(WS_CHILD|WS_VISIBLE|ES_AUTOHSCROLL|ES_PASSWORD,rcEditCreate,this,IDC_ED_PASSWORD);

	//���ÿؼ�
	m_edPassword.LimitText(LEN_PASSWORD-1);
	m_edPassword.SetEnableColor(RGB(0,0,0),RGB(255,255,255),RGB(255,255,255));
	m_edPassword.SetFont(CFont::FromHandle(CSkinResourceManager::GetDefaultFont()));

	//�ƶ�����
	SetWindowPos(NULL,0,0,rcWindow.Width(),24,SWP_NOMOVE|SWP_NOZORDER|SWP_NOCOPYBITS);
	return;
}

//�߿�����
VOID CPasswordControl::SetDrawBorad(bool bDrawBorad)
{
	//���ñ���
	m_bDrawBorad=bDrawBorad;

	//���½���
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}



//��������
VOID CPasswordControl::SetUserPassword(LPCTSTR pszPassword)
{
	//���ÿؼ�
	INT nPasswordLen=lstrlen(pszPassword);
	m_edPassword.SetWindowText((nPasswordLen>0)?TEXT("********"):TEXT(""));

	//���ñ���
	m_bModify=false;
	m_bFalsity=true;
	lstrcpyn(m_szPassword,pszPassword,CountArray(m_szPassword));

	return;
}

//��ȡ����
LPCTSTR CPasswordControl::GetUserPassword(TCHAR szPassword[LEN_PASSWORD])
{
	//�ؼ�����
	if (m_bModify==true)
	{
		m_bModify=false;
		m_edPassword.GetWindowText(m_szPassword,CountArray(m_szPassword));
	}

	//��������
	lstrcpyn(szPassword,m_szPassword,LEN_PASSWORD);

	return szPassword;
}

//������ɫ
VOID CPasswordControl::SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorad)
{
	m_edPassword.SetEnableColor(crEnableText,crEnableBK,crEnableBorad);
}

//�ػ���Ϣ
VOID CPasswordControl::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	////�滭����
	//if (IsWindowEnabled()==TRUE)
	//{
	//	dc.FillSolidRect(rcClient,CSkinEdit::m_SkinAttribute.m_crFocusBK);
	//}
	//else
	//{
	//	dc.FillSolidRect(rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);
	//}


	//�滭����
	if (IsWindowEnabled()==TRUE)
	{
		dc.FillSolidRect(rcClient,RGB(255,255,255));
	}
	else
	{
		dc.FillSolidRect(rcClient,RGB(255,255,255));
	}
	return;
}

//�ػ���Ϣ
VOID CPasswordControl::OnNcPaint()
{
	//��ȡλ��
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	ScreenToClient(&rcWindow);
	
	//��ɫ����
	COLORREF crBackGround=CSkinEdit::m_SkinAttribute.m_crNoFocusBK;
	COLORREF crFrameBorad=CSkinEdit::m_SkinAttribute.m_crFocusBK;

	//����״̬
	if (IsWindowEnabled()==FALSE)
	{
		if (m_bRenderImage==false)
		{
			crBackGround=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
			crFrameBorad=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		}
		else
		{
			crBackGround=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
			crFrameBorad=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		}
	}
	else
	{
		//crBackGround=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		//crFrameBorad=CSkinEdit::m_SkinAttribute.m_crDisFocusBK;
		crBackGround=RGB(255,255,255);
		crFrameBorad=RGB(255,255,255);
	}

	//�߿��ж�
	if (m_bDrawBorad==false)
	{
		crFrameBorad=crBackGround;
	}

	//�滭�߿�
	CClientDC ClientDC(this);
	ClientDC.Draw3dRect(rcWindow.left,rcWindow.top,rcWindow.Width(),rcWindow.Height(),crFrameBorad,crFrameBorad);
	ClientDC.Draw3dRect(rcWindow.left+1,rcWindow.top+1,rcWindow.Width()-2,rcWindow.Height()-2,crBackGround,crBackGround);

	return;

}

//�滭����
BOOL CPasswordControl::OnEraseBkgnd(CDC * pDC)
{
	return TRUE;
}

//��ȡ����
VOID CPasswordControl::OnSetFocus(CWnd * pOldWnd)
{
	__super::OnSetFocus(pOldWnd);

	//���ý���
	m_edPassword.SetFocus();

	//����ѡ��
	m_edPassword.SetSel(0,-1,FALSE);

	return;
}

//����ı�
VOID CPasswordControl::OnEnChangePassword()
{
	//���ñ���
	m_bModify=true;
	m_bFalsity=false;

	//������Ϣ
	CWnd * pParent=GetParent();
	if (pParent!=NULL) pParent->SendMessage(WM_COMMAND,MAKELONG(GetWindowLong(m_hWnd,GWL_ID),EN_CHANGE),(LPARAM)m_hWnd);

	return;
}

//���̰�ť
VOID CPasswordControl::OnBnClickedKeyboard()
{
	//��ȡλ��
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//��������
	if (m_bFalsity==true)
	{
		m_bFalsity=false;
		m_edPassword.SetWindowText(TEXT(""));
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

