#include "StdAfx.h"
#include "Resource.h"
#include "PlatformPublicize.h"

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPlatformPublicize::CPlatformPublicize()
{
	//���ñ���
	m_crBoradColor=CLR_INVALID;
	m_crBackColor=RGB(255,255,255);
	ZeroMemory(m_szSpareURL,MAX_PATH);

	return;
}

//��������
CPlatformPublicize::~CPlatformPublicize()
{
}

//λ�ú���
VOID CPlatformPublicize::GetWebBrowserRect(CRect & rcWebBrowser)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//����λ��
	if (m_crBoradColor!=CLR_INVALID)
	{
		rcWebBrowser.top=1;
		rcWebBrowser.left=1;
		rcWebBrowser.right=rcClient.Width()-1;
		rcWebBrowser.bottom=rcClient.Height()-1;
	}
	else
	{
		rcWebBrowser.top=0;
		rcWebBrowser.left=0;
		rcWebBrowser.right=rcClient.Width();
		rcWebBrowser.bottom=rcClient.Height();
	}

	return;
}

//�滭����
VOID CPlatformPublicize::DrawPublicizeView(CDC * pDC, INT nWidth, INT nHeight, BYTE cbStatus)
{
	//�滭����
	pDC->FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));

	//������Դ
	CPngImage ImagePublicize;
	ImagePublicize.LoadImage(AfxGetInstanceHandle(),TEXT("LOAD_STATUS"));

	//�滭����
	CSize SizePublicize;
	SizePublicize.SetSize(ImagePublicize.GetWidth(),ImagePublicize.GetHeight());
	ImagePublicize.DrawImage(pDC,(nWidth-SizePublicize.cx)/2,(nHeight-SizePublicize.cy)/2,SizePublicize.cx,SizePublicize.cy,0,0);

	//���߿�
	if (m_crBoradColor!=CLR_INVALID) pDC->Draw3dRect(0,0,nWidth,nHeight,m_crBoradColor,m_crBoradColor);

	return;
}

//���ñ���
VOID CPlatformPublicize::SetBackColor(COLORREF crBackColor)
{
	//���ñ���
	m_crBackColor=crBackColor;

	//���½���
	if (m_hWnd!=NULL) Invalidate(FALSE);

	return;
}

//���ñ߿�
VOID CPlatformPublicize::SetBoradColor(COLORREF crBoradColor)
{
	//���ñ���
	m_crBoradColor=crBoradColor;

	//���½���
	if (m_hWnd!=NULL) Invalidate(FALSE);

	return;
}

//״̬֪ͨ
VOID CPlatformPublicize::OnBrowserStatus(BYTE cbStatus)
{
	if(cbStatus==BROWSER_STATUS_ERROR && m_szSpareURL[0]!='\0')
	{
		Navigate(m_szSpareURL);
		return ;
	}
	__super::OnBrowserStatus(cbStatus);
}

//������ַ
VOID CPlatformPublicize::SetSpareURL(LPCTSTR pszURL)
{
	_tcsncpy(m_szSpareURL,pszURL,MAX_PATH);
}
//////////////////////////////////////////////////////////////////////////////////
