#include "StdAfx.h"
#include "Resource.h"
#include ".\dlgmatchawards.h"


BEGIN_MESSAGE_MAP(CDlgMatchAwards, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


CDlgMatchAwards::CDlgMatchAwards(void):CDialog(IDD_DLG_MATCH_AWARDS)
{
	m_pMatchResult=NULL;

}

CDlgMatchAwards::~CDlgMatchAwards(void)
{

}


void CDlgMatchAwards::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//��������
	CPngImage ImageBack;

	//����ͼƬ
	ImageBack.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME), TEXT("MATCH_AWARDS"));

	ImageBack.DrawImage(&dc, 0,0);

	//��������
	CFont DrawFont;
	DrawFont.CreateFont(20,0,0,0,300,0,0,0,134,3,2,1,2,TEXT("����"));
	CFont * pOldFont=pBufferDC->SelectObject(&DrawFont);
	pBufferDC->SetTextColor(RGB(218,31,23));

	//��������
	CPngImage ImageAwards;

	//����ͼƬ
	ImageAwards.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME), TEXT("MATCH_AWARDS"));

	//����λ��
	INT nXPos=(rcClient.Width()-ImageAwards.GetWidth())/2;
	INT nYPos=(rcClient.Height()-ImageAwards.GetHeight())/2;

	//�滭����
	if(m_pMatchResult!=NULL)
	{
		ImageAwards.DrawImage(pBufferDC,nXPos,nYPos);
		pBufferDC->DrawText(m_pMatchResult->szDescribe, &CRect(nXPos+60,nYPos+115,nXPos+382,nYPos+195),DT_TOP|DT_WORDBREAK);

		pBufferDC->SelectObject(pOldFont);
		pBufferDC->SetTextColor(RGB(0,0,0));

		int nIndex=0;
		CString strText;

		//��Ϸ�ҽ���
		if(m_pMatchResult->dwGold>0)
		{
			strText.Format(TEXT("�� %d��Ϸ��"), m_pMatchResult->dwGold);
			pBufferDC->DrawText(strText, &CRect(nXPos+60,nYPos+205,nXPos+360,nYPos+230),DT_TOP|DT_LEFT|DT_SINGLELINE);
			nIndex++;
		}

		//���ƽ���
		if(m_pMatchResult->dwMedal>0)
		{
			strText.Format(TEXT("�� %d����"), m_pMatchResult->dwMedal);
			pBufferDC->DrawText(strText, &CRect(nXPos+60,nYPos+205+nIndex*30,nXPos+360,nYPos+230+nIndex*30),DT_TOP|DT_LEFT|DT_SINGLELINE);
			nIndex++;
		}

		//���齱��
		if(m_pMatchResult->dwExperience>0)
		{
			strText.Format(TEXT("�� %d����"), m_pMatchResult->dwExperience);
			pBufferDC->DrawText(strText, &CRect(nXPos+60,nYPos+205+nIndex*30,nXPos+360,nYPos+230+nIndex*30),DT_TOP|DT_LEFT|DT_SINGLELINE);
			nIndex++;
		}

		//������Դ
		DrawFont.DeleteObject();
	}

	//�滭����
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);
}

void CDlgMatchAwards::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDOK, m_btCloseAwards);

	CWnd::DoDataExchange(pDX);
}

BOOL CDlgMatchAwards::OnInitDialog()
{
	CDialog::OnInitDialog();

	//��������
	CPngImage ImageBack;

	//����ͼƬ
	ImageBack.LoadImage(GetModuleHandle(GAME_FRAME_DLL_NAME), TEXT("MATCH_AWARDS"));
	m_btCloseAwards.SetButtonImage(IDB_BT_CLOSE_AWARDS,GetModuleHandle(GAME_FRAME_DLL_NAME),false,false);
	m_btCloseAwards.SetWindowPos(NULL,ImageBack.GetWidth()-55,30,27,22,SWP_NOZORDER);

    SetWindowPos(NULL, 0,0,ImageBack.GetWidth(),ImageBack.GetHeight(),SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW);
	CenterWindow();

	//��ȡ����
	CRect rcWindow;
	GetWindowRect(&rcWindow);

	//����λ��
	CRect rcUnLayered;
	rcUnLayered.top=20;
	rcUnLayered.left=20;
	rcUnLayered.right=rcWindow.Width()-20;
	rcUnLayered.bottom=rcWindow.Height()-20;

	//���ô�С
	CSize SizeWindow(ImageBack.GetWidth(),ImageBack.GetHeight());

	//��������
	CRgn RgnWindow;
	RgnWindow.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,7,7);

	//��������
	SetWindowRgn(RgnWindow,FALSE);

	//�ֲ㴰��
	m_SkinLayered.CreateLayered(this,rcWindow);
	m_SkinLayered.InitLayeredArea(ImageBack,255,rcUnLayered,CPoint(7,7),false);

	return TRUE; 
}

void CDlgMatchAwards::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	//��ʾ�ֲ�
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

void CDlgMatchAwards::OnWindowPosChanged(WINDOWPOS* lpWndPos)
{
	CDialog::OnWindowPosChanged(lpWndPos);

	//�ƶ��ֲ�
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}
}



//ȷ������
VOID CDlgMatchAwards::OnOK()
{
	ShowWindow(SW_HIDE);
}