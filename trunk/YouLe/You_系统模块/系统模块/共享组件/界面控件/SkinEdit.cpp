#include "Stdafx.h"
#include "SkinEdit.h"

//////////////////////////////////////////////////////////////////////////

//��̬����
CSkinEditAttribute					CSkinEdit::m_SkinAttribute;				//��������

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinEdit, CEdit)

BEGIN_MESSAGE_MAP(CSkinEdit, CEdit)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSkinEditEx, CSkinEdit)
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CSkinEditAttribute::CSkinEditAttribute() 
{
	//��ʼ������
	m_crFocusTX=RGB(0,0,0);
	m_crFocusBK=RGB(0,0,0);
	m_crNoFocusTX=RGB(0,0,0);
	m_crNoFocusBK=RGB(0,0,0);
	m_crDisFocusTX=RGB(0,0,0);
	m_crDisFocusBK=RGB(0,0,0);

	return;
}

//��������
CSkinEditAttribute::~CSkinEditAttribute() 
{
}

//��������
bool CSkinEditAttribute::UpdateSkinResource(ISkinResource * pISkinResource)
{
	//��ȡ��Ϣ
	tagSkinEditResource SkinEditResource;
	if (pISkinResource!=NULL) pISkinResource->GetResourceInfo(SkinEditResource);

	//���ñ���
	m_crFocusTX=SkinEditResource.crFocusTX;
	m_crFocusBK=SkinEditResource.crFocusBK;
	m_crNoFocusTX=SkinEditResource.crNoFocusTX;
	m_crNoFocusBK=SkinEditResource.crNoFocusBK;
	m_crDisFocusTX=SkinEditResource.crDisFocusTX;
	m_crDisFocusBK=SkinEditResource.crDisFocusBK;

	//������ˢ
	m_brFocus.DeleteObject();
	m_brNoFocus.DeleteObject();
	m_brDisbale.DeleteObject();
	m_brFocus.CreateSolidBrush(m_crFocusBK);
	m_brNoFocus.CreateSolidBrush(m_crNoFocusBK);

	return true;
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CSkinEdit::CSkinEdit()
{
	m_bFocus=false;
}

//��������
CSkinEdit::~CSkinEdit()
{
}

//�滭�ؼ�
HBRUSH CSkinEdit::CtlColor(CDC * pDC, UINT nCtlColor)
{
	pDC->SetBkMode(OPAQUE);
	if (IsWindowEnabled())
	{
		if (m_bFocus) 
		{
			pDC->SetTextColor(m_SkinAttribute.m_crFocusTX);
			pDC->SetBkColor(m_SkinAttribute.m_crFocusBK);
			return m_SkinAttribute.m_brFocus;
		}
		pDC->SetTextColor(m_SkinAttribute.m_crNoFocusTX);
		pDC->SetBkColor(m_SkinAttribute.m_crNoFocusBK);
		return m_SkinAttribute.m_brNoFocus;
	}
	pDC->SetTextColor(m_SkinAttribute.m_crDisFocusBK);
	pDC->SetBkColor(m_SkinAttribute.m_crDisFocusBK);
	return m_SkinAttribute.m_brDisbale;
}

//�õ�����
void CSkinEdit::OnSetFocus(CWnd * pOldWnd)
{
	m_bFocus=true;
	Invalidate(TRUE);
	__super::OnSetFocus(pOldWnd);
}

//ʧȥ����
void CSkinEdit::OnKillFocus(CWnd * pNewWnd)
{
	m_bFocus=false;
	Invalidate(TRUE);
	__super::OnKillFocus(pNewWnd);
}

//�滭�ؼ�
VOID CSkinEdit::DrawControlView(CDC * pDC, COLORREF crColorBorad,  COLORREF crColorBK)
{
	//��ȡλ��
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	ScreenToClient(&rcWindow);

	//�滭�߿�
	if (GetExStyle()&WS_EX_CLIENTEDGE)
	{
		pDC->Draw3dRect(&rcWindow,crColorBorad,crColorBorad);
		pDC->Draw3dRect(rcWindow.left+1,rcWindow.top+1,rcWindow.Width()-2,rcWindow.Height()-2,crColorBK,crColorBK);
	}
	else
	{
		pDC->Draw3dRect(&rcWindow,crColorBK,crColorBK);
		pDC->Draw3dRect(rcWindow.left+1,rcWindow.top+1,rcWindow.Width()-2,rcWindow.Height()-2,crColorBK,crColorBK);
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinEditEx::CSkinEditEx()
{
	//������ɫ
	m_crEnableBK=m_SkinAttribute.m_crFocusBK;
	m_crDisableBK=m_SkinAttribute.m_crNoFocusBK;

	//������ɫ
	m_crEnableText=m_SkinAttribute.m_crFocusTX;
	m_crDisableText=m_SkinAttribute.m_crNoFocusTX;

	//�߿���ɫ
	m_crEnableBorad=m_SkinAttribute.m_crDisFocusTX;
	m_crDisableBorad=m_SkinAttribute.m_crDisFocusBK;
	return;
}

//��������
CSkinEditEx::~CSkinEditEx()
{
}

//������ɫ
VOID CSkinEditEx::SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorad)
{
	//������ɫ
	m_crEnableBK=crEnableBK;
	m_crEnableText=crEnableText;
	m_crEnableBorad=crEnableBorad;

	//������ˢ
	m_brEnable.DeleteObject();
	m_brEnable.CreateSolidBrush(m_crEnableBK);

	//���½���
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//������ɫ
VOID CSkinEditEx::SetDisableColor(COLORREF crDisableText, COLORREF crDisableBK, COLORREF crDisableBorad)
{
	//������ɫ
	m_crDisableBK=crDisableBK;
	m_crDisableText=crDisableText;
	m_crDisableBorad=crDisableBorad;

	//������ˢ
	m_brDisable.DeleteObject();
	m_brDisable.CreateSolidBrush(m_crDisableBK);

	//���½���
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	return;
}

//�ػ���Ϣ
VOID CSkinEditEx::OnNcPaint()
{
	//״̬����
	bool bDisable=(IsWindowEnabled()==FALSE);
	COLORREF crColorBK=(bDisable==false)?m_crEnableBK:m_crDisableBK;
	COLORREF crColorBorad=(bDisable==false)?m_crEnableBorad:m_crDisableBorad;

	//�滭�߿�
	CClientDC ClientDC(this);
	DrawControlView(&ClientDC,crColorBorad,crColorBK);

	return;
}

//�滭�ؼ�
HBRUSH CSkinEditEx::CtlColor(CDC * pDC, UINT nCtlColor)
{
	//���û���
	if (IsWindowEnabled()==FALSE)
	{
		//����״̬
		pDC->SetBkColor((m_crDisableBK==CLR_INVALID)?m_SkinAttribute.m_crNoFocusTX:m_crDisableBK);
		pDC->SetTextColor((m_crDisableText==CLR_INVALID)?m_SkinAttribute.m_crNoFocusTX:m_crDisableText);
		return (m_brDisable.GetSafeHandle()==NULL)?m_SkinAttribute.m_brDisbale:m_brDisable;
	}
	else
	{
		//����״̬
		pDC->SetBkColor((m_crEnableBK==CLR_INVALID)?m_SkinAttribute.m_crFocusBK:m_crEnableBK);
		pDC->SetTextColor((m_crEnableText==CLR_INVALID)?m_SkinAttribute.m_crFocusTX:m_crEnableText);
		return (m_brEnable.GetSafeHandle()==NULL)?m_SkinAttribute.m_brDisbale:m_brEnable;
	}

	return NULL;
}