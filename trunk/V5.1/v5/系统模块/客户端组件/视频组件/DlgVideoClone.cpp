#include "stdafx.h"
#include "DlgVideoClone.h"
#include "resource.h"
#include "VideoServiceModule.h"

BEGIN_MESSAGE_MAP(CDlgVideoClone, CDialog)
END_MESSAGE_MAP()
IMPLEMENT_DYNAMIC(CDlgVideoClone, CDialog)


//���캯��
CDlgVideoClone::CDlgVideoClone(CWnd* pParent)
	: CDialog(IDD_VIDEO_CLONE, pParent)
{
	AfxSetResourceHandle(GetModuleHandle(VIDEO_SERVICE_DLL_NAME));
	m_hIcon = AfxGetApp()->LoadIcon(IDI_GAME_VIDEO);
	AfxSetResourceHandle(GetModuleHandle(NULL));
}

//��������
CDlgVideoClone::~CDlgVideoClone()
{
}

//���ݰ�
void CDlgVideoClone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

//������Ƶ
void CDlgVideoClone::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
	//����λͼ
	BITMAPINFOHEADER  *lpbmi = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER)+dwLen);  
	ZeroMemory(lpbmi,sizeof(BITMAPINFOHEADER)+dwLen);
    memcpy((LPBYTE)lpbmi,&bmiHeader,sizeof(bmiHeader));
	memcpy(((LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER)),lpBuf,dwLen);  

	HDC hdc=::GetDC(m_hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,lpbmi,CBM_INIT,(LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)lpbmi,DIB_RGB_COLORS);  

	//����λ��
	CRect rcVideo;
	GetClientRect(rcVideo);

	//��ͼλͼ 
	HBITMAP holdbm = (HBITMAP)SelectObject(dcMem,hBitmap);  
	::SetStretchBltMode(hdc,COLORONCOLOR);
	::StretchBlt(hdc,rcVideo.left,rcVideo.top,rcVideo.Width(),rcVideo.Height(),dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);

	//�ͷ���Դ
	SelectObject(dcMem,holdbm);  
	DeleteObject(dcMem);
	DeleteObject(hBitmap);
	DeleteObject(hdc);
	free(lpbmi);
	lpbmi = NULL;
}


BOOL CDlgVideoClone::OnInitDialog()
{
	CDialog::OnInitDialog();

	//����ͼ��
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}
