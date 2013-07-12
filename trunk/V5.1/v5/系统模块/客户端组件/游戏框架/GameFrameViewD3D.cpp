#include "StdAfx.h"
#include "GameFrameAvatar.h"
#include "GameFrameViewD3D.h"
#include ".\gameframeviewd3d.h"

//////////////////////////////////////////////////////////////////////////////////
#define IDI_ROLL_TEXT				30									//��������
//��Ⱦ��Ϣ
#define WM_D3D_RENDER				WM_USER+300							//��Ⱦ��Ϣ

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameFrameViewD3D, CGameFrameView)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()

	//�Զ���Ϣ
	ON_MESSAGE(WM_D3D_RENDER, OnMessageD3DRender)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameViewD3D::CGameFrameViewD3D()
{
	//״̬����
	m_bInitD3D=false;
	m_hRenderThread=NULL;

	//֡��ͳ��
	m_dwDrawBenchmark=0;
	m_dwDrawLastCount=0;
	m_dwDrawCurrentCount=0L;

	//��������
	m_RectDirtySurface.SetRect(0,0,0,0);
	m_rcText.SetRect(0,0,1,1);

	return;
}

//��������
CGameFrameViewD3D::~CGameFrameViewD3D()
{
}

//���ý���
VOID CGameFrameViewD3D::ResetGameView()
{
	return;
}

//�����ؼ�
VOID CGameFrameViewD3D::RectifyControl(INT nWidth, INT nHeight)
{
	return;
}

//�������
VOID CGameFrameViewD3D::InvalidGameView(INT nXPos, INT nYPos, INT nWidth, INT nHeight)
{
	//����λ��
	CRect rcInvalid;
	rcInvalid.SetRect(nXPos,nYPos,nXPos+nWidth,nYPos+nHeight);

	//λ�õ���
	if (rcInvalid.IsRectNull()==TRUE) GetClientRect(&rcInvalid);

	//���þ���
	if (m_RectDirtySurface.IsRectEmpty()==FALSE)
	{
		//���ñ���
		m_RectDirtySurface.top=__min(m_RectDirtySurface.top,rcInvalid.top);
		m_RectDirtySurface.left=__min(m_RectDirtySurface.left,rcInvalid.left);
		m_RectDirtySurface.right=__max(m_RectDirtySurface.right,rcInvalid.right);
		m_RectDirtySurface.bottom=__max(m_RectDirtySurface.bottom,rcInvalid.bottom);
	}
	else
	{
		//���ñ���
		m_RectDirtySurface=rcInvalid;
	}

	//ˢ�´���
	InvalidateRect(&rcInvalid,FALSE);

	return;
}

//�����豸
VOID CGameFrameViewD3D::OnInitDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	//���ñ���
	m_bInitD3D=true;

	//��ȡ����
	ASSERT(CSkinResourceManager::GetInstance()!=NULL);
	CSkinResourceManager * pSkinResourceManager=CSkinResourceManager::GetInstance();

	//��ȡ����
	LOGFONT LogFont;
	pSkinResourceManager->GetDefaultFont().GetLogFont(&LogFont);

	//��������
	m_D3DFont.CreateFont(LogFont,0L);

	LOGFONT LogRollFont;
	ZeroMemory(&LogRollFont,sizeof(LogRollFont));
	LogRollFont.lfHeight=20;
	_sntprintf(LogRollFont.lfFaceName,CountArray(LogRollFont.lfFaceName),TEXT("����"));
	LogRollFont.lfWeight=200;
	LogRollFont.lfCharSet=134;
	m_D3DRollFont.CreateFont(LogRollFont,0L);

	//�����豸
	m_VirtualEngine.SetD3DDevice(&m_D3DDevice);

	//����ͷ��
	CGameFrameAvatar * pGameFrameAvatar=CGameFrameAvatar::GetInstance();
	if (pGameFrameAvatar!=NULL) pGameFrameAvatar->Initialization(pD3DDevice);

	//������Դ
	HINSTANCE hInstance=GetModuleHandle(GAME_FRAME_DLL_NAME);
	m_D3DTextureReady.LoadImage(pD3DDevice,hInstance,TEXT("USER_READY"),TEXT("PNG"));
	m_D3DTextureMember.LoadImage(pD3DDevice,hInstance,TEXT("MEMBER_FLAG"),TEXT("PNG"));
	m_D3DTextureClockItem.LoadImage(pD3DDevice,hInstance,TEXT("USER_CLOCK_ITEM"),TEXT("PNG"));
	m_D3DTextureClockBack.LoadImage(pD3DDevice,hInstance,TEXT("USER_CLOCK_BACK"),TEXT("PNG"));

	//���ô���
	InitGameView(pD3DDevice,nWidth,nHeight);

	return;
}

//��ʧ�豸
VOID CGameFrameViewD3D::OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//�����豸
VOID CGameFrameViewD3D::OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	return;
}

//��Ⱦ����
VOID CGameFrameViewD3D::OnRenderWindow(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight)
{
	//��������
	CartoonMovie();

	//�滭����
	DrawGameView(pD3DDevice,nWidth,nHeight);

	//�滭����
	DrawMatchInfo(pD3DDevice);

	//������
	m_VirtualEngine.DrawWindows(pD3DDevice);

	//���ñ���
	m_dwDrawCurrentCount++;

	//�ۼ��ж�
	if ((GetTickCount()-m_dwDrawBenchmark)>=1000L)
	{
		//���ñ���
		m_dwDrawLastCount=m_dwDrawCurrentCount;

		//ͳ�ƻ�ԭ
		m_dwDrawCurrentCount=0L;
		m_dwDrawBenchmark=GetTickCount();
	}

	return;
}

//��Ϣ����
BOOL CGameFrameViewD3D::PreTranslateMessage(MSG * pMsg)
{
	//������
	if (m_VirtualEngine.PreTranslateMessage(pMsg->message,pMsg->wParam,pMsg->lParam)==true)
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//��Ϣ����
LRESULT CGameFrameViewD3D::DefWindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	//������
	if (m_VirtualEngine.DefWindowProc(nMessage,wParam,lParam)==true)
	{
		return 0L;
	}

	return __super::DefWindowProc(nMessage,wParam,lParam);
}

//��Ⱦ�߳�
VOID CGameFrameViewD3D::StartRenderThread()
{
	//Ч��״̬
	ASSERT(m_hRenderThread==NULL);
	if (m_hRenderThread!=NULL) return;

	//�����߳�
	m_hRenderThread=(HANDLE)::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)D3DRenderThread,(LPVOID)(m_hWnd),0L,0L);

	return;
}

//�滭׼��
VOID CGameFrameViewD3D::DrawUserReady(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos)
{
	//��ȡ��С
	CSize SizeUserReady;
	SizeUserReady.SetSize(m_D3DTextureReady.GetWidth(),m_D3DTextureReady.GetHeight());

	//�滭׼��
	m_D3DTextureReady.DrawImage(pD3DDevice,nXPos-SizeUserReady.cx/2,nYPos-SizeUserReady.cy/2);

	return;
}

//�滭��־
VOID CGameFrameViewD3D::DrawOrderFlag(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, BYTE cbImageIndex)
{
	//��ȡ��С
	CSize SizeMember;
	SizeMember.SetSize(m_D3DTextureMember.GetWidth()/3,m_D3DTextureMember.GetHeight());

	//�滭��־
	m_D3DTextureMember.DrawImage(pD3DDevice,nXPos,nYPos,SizeMember.cx,SizeMember.cy,SizeMember.cx*cbImageIndex,0);

	return;
}

//�滭ʱ��
VOID CGameFrameViewD3D::DrawUserClock(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, WORD wUserClock)
{
	//�滭ʱ��
	if ((wUserClock>0)&&(wUserClock<100))
	{
		//��ȡ��С
		CSize SizeClockItem;
		CSize SizeClockBack;
		SizeClockBack.SetSize(m_D3DTextureClockBack.GetWidth(),m_D3DTextureClockBack.GetHeight());
		SizeClockItem.SetSize(m_D3DTextureClockItem.GetWidth()/10,m_D3DTextureClockItem.GetHeight());

		//�滭����
		INT nXDrawPos=nXPos-SizeClockBack.cx/2;
		INT nYDrawPos=nYPos-SizeClockBack.cy/2;
		m_D3DTextureClockBack.DrawImage(pD3DDevice,nXDrawPos,nYDrawPos);

		//�滭ʱ��
		WORD nClockItem1=wUserClock/10;
		WORD nClockItem2=wUserClock%10;
		m_D3DTextureClockItem.DrawImage(pD3DDevice,nXDrawPos+13,nYDrawPos+27,SizeClockItem.cx,SizeClockItem.cy,nClockItem1*SizeClockItem.cx,0);
		m_D3DTextureClockItem.DrawImage(pD3DDevice,nXDrawPos+28,nYDrawPos+27,SizeClockItem.cx,SizeClockItem.cy,nClockItem2*SizeClockItem.cx,0);
	}

	return;
}

//�滭ͷ��
VOID CGameFrameViewD3D::DrawUserAvatar(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, IClientUserItem * pIClientUserItem)
{
	//����ͷ��
	CGameFrameAvatar * pGameFrameAvatar=CGameFrameAvatar::GetInstance();
	if (pGameFrameAvatar!=NULL) pGameFrameAvatar->DrawUserAvatar(pD3DDevice,nXPos,nYPos,pIClientUserItem);

	return;
}

//�滭ͷ��
VOID CGameFrameViewD3D::DrawUserAvatar(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, INT nWidth, INT nHeight, IClientUserItem * pIClientUserItem)
{
	//����ͷ��
	CGameFrameAvatar * pGameFrameAvatar=CGameFrameAvatar::GetInstance();
	if (pGameFrameAvatar!=NULL) pGameFrameAvatar->DrawUserAvatar(pD3DDevice,nXPos,nYPos,nWidth,nHeight,pIClientUserItem);

	return;
}

//�滭����
VOID CGameFrameViewD3D::DrawViewImage(CD3DDevice * pD3DDevice, CD3DTexture & D3DTexture, BYTE cbDrawMode)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//�滭λͼ
	switch (cbDrawMode)
	{
	case DRAW_MODE_SPREAD:		//ƽ��ģʽ
		{
			//��ȡ��С
			CSize SizeTexture;
			SizeTexture.SetSize(D3DTexture.GetWidth(),D3DTexture.GetHeight());

			//�滭λͼ
			for (INT nXPos=0;nXPos<rcClient.right;nXPos+=SizeTexture.cx)
			{
				for (INT nYPos=0;nYPos<rcClient.bottom;nYPos+=SizeTexture.cy)
				{
					D3DTexture.DrawImage(pD3DDevice,nXPos,nYPos);
				}
			}

			return;
		}
	case DRAW_MODE_CENTENT:		//����ģʽ
		{
			//��ȡ��С
			CSize SizeTexture;
			SizeTexture.SetSize(D3DTexture.GetWidth(),D3DTexture.GetHeight());

			//λ�ü���
			INT nXPos=(rcClient.Width()-SizeTexture.cx)/2;
			INT nYPos=(rcClient.Height()-SizeTexture.cy)/2;

			//�滭λͼ
			D3DTexture.DrawImage(pD3DDevice,nXPos,nYPos);

			return;
		}
	case DRAW_MODE_ELONGGATE:	//����ģʽ
		{
			//��ȡ��С
			CSize SizeTexture;
			SizeTexture.SetSize(D3DTexture.GetWidth(),D3DTexture.GetHeight());

			//�滭λͼ
			D3DTexture.DrawImage(pD3DDevice,0,0,rcClient.Width(),rcClient.Height(),0,0,SizeTexture.cx,SizeTexture.cy);

			return;
		}
	}

	return;
}

//�滭����
VOID CGameFrameViewD3D::DrawNumberString(CD3DDevice * pD3DDevice, CD3DTexture & D3DTexture, LONG lNumber, INT nXPos, INT nYPos)
{
	//Ч��״̬
	ASSERT(D3DTexture.IsNull()==false);
	if (D3DTexture.IsNull()==true) return;

	//��ȡ��С
	CSize SizeNumber;
	SizeNumber.SetSize(D3DTexture.GetWidth()/10,D3DTexture.GetHeight());

	//��������
	LONG lNumberCount=0;
	LONG lNumberTemp=lNumber;

	//������Ŀ
	do
	{
		lNumberCount++;
		lNumberTemp/=10L;
	} while (lNumberTemp>0);

	//λ�ö���
	INT nYDrawPos=nYPos-SizeNumber.cy/2;
	INT nXDrawPos=nXPos+lNumberCount*SizeNumber.cx/2-SizeNumber.cx;

	//�滭����
	for (LONG i=0;i<lNumberCount;i++)
	{
		//�滭����
		LONG lCellNumber=lNumber%10L;
		D3DTexture.DrawImage(pD3DDevice,nXDrawPos,nYDrawPos,SizeNumber.cx,SizeNumber.cy,lCellNumber*SizeNumber.cx,0);

		//���ñ���
		lNumber/=10;
		nXDrawPos-=SizeNumber.cx;
	};

	return;
}

//�滭����
VOID CGameFrameViewD3D::DrawViewImage(CD3DDevice * pD3DDevice, CD3DSprite & D3DSprite, BYTE cbDrawMode)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//�滭λͼ
	switch (cbDrawMode)
	{
	case DRAW_MODE_SPREAD:		//ƽ��ģʽ
		{
			//��ȡ��С
			CSize SizeTexture;
			SizeTexture.SetSize(D3DSprite.GetWidth(),D3DSprite.GetHeight());

			//�滭λͼ
			for (INT nXPos=0;nXPos<rcClient.right;nXPos+=SizeTexture.cx)
			{
				for (INT nYPos=0;nYPos<rcClient.bottom;nYPos+=SizeTexture.cy)
				{
					D3DSprite.DrawImage(pD3DDevice,nXPos,nYPos);
				}
			}

			return;
		}
	case DRAW_MODE_CENTENT:		//����ģʽ
		{
			//��ȡ��С
			CSize SizeTexture;
			SizeTexture.SetSize(D3DSprite.GetWidth(),D3DSprite.GetHeight());

			//λ�ü���
			INT nXPos=(rcClient.Width()-SizeTexture.cx)/2;
			INT nYPos=(rcClient.Height()-SizeTexture.cy)/2;

			//�滭λͼ
			D3DSprite.DrawImage(pD3DDevice,nXPos,nYPos);

			return;
		}
	case DRAW_MODE_ELONGGATE:	//����ģʽ
		{
			//��ȡ��С
			CSize SizeTexture;
			SizeTexture.SetSize(D3DSprite.GetWidth(),D3DSprite.GetHeight());

			//�滭λͼ
			D3DSprite.DrawImage(pD3DDevice,0,0,rcClient.Width(),rcClient.Height(),0,0,SizeTexture.cx,SizeTexture.cy);

			return;
		}
	}

	return;
}

//�滭����
VOID CGameFrameViewD3D::DrawNumberString(CD3DDevice * pD3DDevice, CD3DSprite & D3DSprite, LONG lNumber, INT nXPos, INT nYPos)
{
	//Ч��״̬
	ASSERT(D3DSprite.IsNull()==false);
	if (D3DSprite.IsNull()==true) return;

	//��ȡ��С
	CSize SizeNumber;
	SizeNumber.SetSize(D3DSprite.GetWidth()/10,D3DSprite.GetHeight());

	//��������
	LONG lNumberCount=0;
	LONG lNumberTemp=lNumber;

	//������Ŀ
	do
	{
		lNumberCount++;
		lNumberTemp/=10L;
	} while (lNumberTemp>0);

	//λ�ö���
	INT nYDrawPos=nYPos-SizeNumber.cy/2;
	INT nXDrawPos=nXPos+lNumberCount*SizeNumber.cx/2-SizeNumber.cx;

	//�滭����
	for (LONG i=0;i<lNumberCount;i++)
	{
		//�滭����
		LONG lCellNumber=lNumber%10L;
		D3DSprite.DrawImage(pD3DDevice,nXDrawPos,nYDrawPos,SizeNumber.cx,SizeNumber.cy,lCellNumber*SizeNumber.cx,0);

		//���ñ���
		lNumber/=10;
		nXDrawPos-=SizeNumber.cx;
	};

	return;
}

//�滭�ַ�
VOID CGameFrameViewD3D::DrawTextString(CD3DDevice * pD3DDevice, LPCTSTR pszString, CRect rcDraw, UINT nFormat, D3DCOLOR crText, D3DCOLOR crFrame)
{
	//��������
	INT nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	INT nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//�滭�߿�
	for (INT i=0;i<CountArray(nXExcursion);i++)
	{
		//����λ��
		CRect rcFrame;
		rcFrame.top=rcDraw.top+nYExcursion[i];
		rcFrame.left=rcDraw.left+nXExcursion[i];
		rcFrame.right=rcDraw.right+nXExcursion[i];
		rcFrame.bottom=rcDraw.bottom+nYExcursion[i];

		//�滭�ַ�
		m_D3DFont.DrawText(pD3DDevice,pszString,&rcFrame,nFormat,crFrame);
	}

	//�滭�ַ�
	m_D3DFont.DrawText(pD3DDevice,pszString,&rcDraw,nFormat,crText);

	return;
}

//�滭�ַ�
VOID CGameFrameViewD3D::DrawTextString(CD3DDevice * pD3DDevice, LPCTSTR pszString, INT nXPos, INT nYPos, UINT nFormat, D3DCOLOR crText, D3DCOLOR crFrame)
{
	//��������
	INT nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	INT nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//�滭�߿�
	for (INT i=0;i<CountArray(nXExcursion);i++)
	{
		m_D3DFont.DrawText(pD3DDevice,pszString,nXPos+nXExcursion[i],nYPos+nYExcursion[i],nFormat,crFrame);
	}

	//�滭�ַ�
	m_D3DFont.DrawText(pD3DDevice,pszString,nXPos,nYPos,nFormat,crText);

	return;
}

//�������
VOID CGameFrameViewD3D::DrawTextString(CD3DDevice * pD3DDevice, LPCTSTR pszString, CRect rcDraw,UINT uFormat, D3DCOLOR D3DColor)
{
	//�������
	m_D3DFont.DrawText(pD3DDevice,pszString,rcDraw,uFormat,D3DColor);

	return;
}

//�������
VOID CGameFrameViewD3D::DrawTextString(CD3DDevice * pD3DDevice, LPCTSTR pszString, INT nXPos, INT nYPos, UINT uFormat, D3DCOLOR D3DColor)
{
	//�������
	m_D3DFont.DrawText(pD3DDevice,pszString,nXPos,nYPos,uFormat,D3DColor);

	return;
}

//�滭����
VOID CGameFrameViewD3D::OnPaint()
{
	CPaintDC dc(this);

	//��Ⱦ�豸
	if (m_bInitD3D==true) m_D3DDevice.RenderD3DDevice();

	return;
}

//λ�ñ仯
VOID CGameFrameViewD3D::OnSize(UINT nType, INT cx, INT cy)
{
	//�����豸
	if (m_bInitD3D==false)
	{
		if ((cx>=0L)&&(cy>0L))
		{
			//���û���
			if (m_D3DDirect.CreateD3DDirect()==false)
			{
				ASSERT(FALSE);
				return;
			}

			//�����豸
			if (m_D3DDevice.CreateD3DDevice(m_hWnd,this)==false)
			{
				ASSERT(FALSE);
				return;
			}
		}
	}
	else
	{
		//�����豸
		m_D3DDevice.ResetD3DDevice();
	}

	__super::OnSize(nType, cx, cy);
}

//��Ⱦ��Ϣ
LRESULT CGameFrameViewD3D::OnMessageD3DRender(WPARAM wParam, LPARAM lParam)
{
	//��Ⱦ�豸
	if (m_bInitD3D==true)
	{
		m_D3DDevice.RenderD3DDevice();
	}

	return 0L;
}

//��Ⱦ�߳�
VOID CGameFrameViewD3D::D3DRenderThread(LPVOID pThreadData)
{
	//Ч�����
	ASSERT(pThreadData!=NULL);
	if (pThreadData==NULL) return;

	int nPaintingTime = 0;
	//��Ⱦѭ��
	while (TRUE)
	{
		//��Ⱦ�ȴ�
		if( nPaintingTime >= 15 )
		{
			Sleep(1);
		}
		else
		{
			Sleep(15 - nPaintingTime);
		}
		
		//������Ϣ
		int nTime = timeGetTime();
		::SendMessage((HWND)pThreadData,WM_D3D_RENDER,0L,0L);
		nPaintingTime = timeGetTime() - nTime;

		TRACE(TEXT(" F [%d] \n"), nPaintingTime);
	}

	return;
}

//������Ϣ
void CGameFrameViewD3D::AddGameTableMessage(LPCTSTR pszMessage,WORD wLen,WORD wType)
{
	if(wType&SMT_TABLE_ROLL)
	{
		m_strRollText=CString(pszMessage,wLen);
		if(m_vecText.empty())
		{
			m_wRollTextCount=160;
			SetTimer(IDI_ROLL_TEXT,20,NULL);
		}
		m_vecText.push_back(m_strRollText);
	}
	// 	else if(wType&SMT_TABLE_FIX)
	// 	{
	// 		m_strFixText="";
	// 		m_strFixText=CString(pszMessage,wLen);
	// 		UpdateGameView(&CRect(m_wTextLeft,400,m_wTextLeft+500,600));
	// 	}

}


//������Ϣ
VOID CGameFrameViewD3D::DrawMatchInfo(CD3DDevice * pD3DDevice)
{
	//���ڳߴ�
	CRect rcClient;
	GetClientRect(&rcClient);

	//������Ϣ
	if(m_pMatchInfo!=NULL)
	{
		CD3DSprite ImageMatchInfo;
		ImageMatchInfo.LoadImage(pD3DDevice,GetModuleHandle(GAME_FRAME_DLL_NAME),TEXT("MATCH_INFO"),TEXT("PNG"));
		ImageMatchInfo.DrawImage(pD3DDevice,0,0,(BYTE)210);
		
		CString strNum;
		strNum.Format(TEXT("%d"),m_pMatchInfo->wGameCount);
		DrawTextString(pD3DDevice,strNum,12,40,DT_LEFT,D3DCOLOR_XRGB(255,255,255));
		
		DrawTextString(pD3DDevice,m_pMatchInfo->szTitle[0],38,10,DT_LEFT,D3DCOLOR_XRGB(196,221,239));
		DrawTextString(pD3DDevice,m_pMatchInfo->szTitle[1],38,30,DT_LEFT,D3DCOLOR_XRGB(196,221,239));
		DrawTextString(pD3DDevice,m_pMatchInfo->szTitle[2],38,50,DT_LEFT,D3DCOLOR_XRGB(196,221,239));
		DrawTextString(pD3DDevice,m_pMatchInfo->szTitle[3],38,70,DT_LEFT,D3DCOLOR_XRGB(255,221,35));
	}

	//�ȴ���ʾ
	if(m_pMatchWaitTip!=NULL)
	{
		//�������
		CD3DSprite ImageWaitTip;
		CD3DSprite ImageNumberOrange;
		CD3DSprite ImageNumberGreen;
		CD3DSprite ImageLine;
		HMODULE hModule=GetModuleHandle(GAME_FRAME_DLL_NAME);

		//����ͼƬ
		ImageWaitTip.LoadImage(pD3DDevice,hModule,TEXT("MATCH_WAIT_TIP"),TEXT("PNG"));				
		ImageNumberOrange.LoadImage(pD3DDevice,hModule,TEXT("NUMBER_ORANGE"),TEXT("PNG"));
		ImageNumberGreen.LoadImage(pD3DDevice,hModule, TEXT("NUMBER_GREEN"),TEXT("PNG"));
		ImageLine.LoadImage(pD3DDevice,hModule, TEXT("MATCH_LINE"),TEXT("PNG"));

		//����λ��
		INT nXPos=(rcClient.Width()-ImageWaitTip.GetWidth())/2;
		INT nYPos=(rcClient.Height()-ImageWaitTip.GetHeight())-40;

		//��ȡ����
		LOGFONT LogFont;
		ZeroMemory(&LogFont,sizeof(LogFont));
		LogFont.lfHeight=22;
		LogFont.lfWeight=200;

		//��������
		CD3DFont DrawFont;
		DrawFont.CreateFont(LogFont,0L);
		
		

		//�滭��Ϣ
		ImageWaitTip.DrawImage(pD3DDevice,nXPos,nYPos-20,(BYTE)220);
		DrawFont.DrawText(pD3DDevice,m_pMatchWaitTip->szMatchName,&CRect(nXPos+20,nYPos+10, nXPos+ImageWaitTip.GetWidth()-40,nYPos+40),
			DT_VCENTER|DT_SINGLELINE|DT_CENTER,D3DCOLOR_XRGB(255,225,0));
		DrawFont.DeleteFont();

		//�������
		CString strDrawText;
		strDrawText.Format(TEXT("��Ŀǰ���֣�            ������"));
		m_D3DFont.DrawText(pD3DDevice,strDrawText, &CRect(nXPos+18,nYPos+64, nXPos+ImageWaitTip.GetWidth()-36, nYPos+90),
			DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS,D3DCOLOR_XRGB(200,246,244));
		DrawNumberString(pD3DDevice, ImageNumberOrange, (LONG)m_pMatchWaitTip->lScore, nXPos+118, nYPos+68);
		DrawNumberString(pD3DDevice, ImageNumberOrange, m_pMatchWaitTip->wRank, nXPos+210,nYPos+68); 
		ImageLine.DrawImage(pD3DDevice, nXPos+215, nYPos+57);
		DrawNumberString(pD3DDevice, ImageNumberOrange, m_pMatchWaitTip->wUserCount, nXPos+250,nYPos+68/*,TA_RIGHT*/);
		strDrawText.Format(TEXT("�����ĵȴ�������      ��δ��ɱ���"));
		m_D3DFont.DrawText(pD3DDevice,strDrawText, &CRect(nXPos+18,nYPos+104, nXPos+ImageWaitTip.GetWidth()-36, nYPos+130),
			DT_TOP|DT_SINGLELINE|DT_END_ELLIPSIS,D3DCOLOR_XRGB(200,246,244));
		DrawNumberString(pD3DDevice, ImageNumberGreen, m_pMatchWaitTip->wPlayingTable, nXPos+135,nYPos+108/*,TA_RIGHT*/);
		strDrawText.Format(TEXT("���Ѿ�������ɱ��֣����ڱ�����%d������ȴ���������Ϸ����"),m_pMatchWaitTip->wCurTableRank);
		m_D3DFont.DrawText(pD3DDevice,strDrawText, &CRect(nXPos+18,nYPos+144, nXPos+ImageWaitTip.GetWidth()-36, nYPos+200),
			DT_TOP|DT_WORDBREAK,D3DCOLOR_XRGB(200,246,244));
		m_D3DFont.DrawText(pD3DDevice,TEXT("��ȷ�����������"), &CRect(nXPos+18,nYPos+168, nXPos+ImageWaitTip.GetWidth()-36, nYPos+200),
			DT_TOP|DT_WORDBREAK,D3DCOLOR_XRGB(200,246,244));
		
	}

	if (m_strRollText.GetLength()>0)
	{
		//��������
		TCHAR szMsg[256]=TEXT("");
		_sntprintf(szMsg,CountArray(szMsg),TEXT("%s"),m_strRollText);
		TCHAR szSub1[64]=TEXT("");
		TCHAR szSub2[128]=TEXT("");
		TCHAR szSub3[256]=TEXT("");
		TCHAR *pSub[]={szSub1,szSub2,szSub3};
		int nPos=0;
		int nTextLine=0;
		INT nLen=m_strRollText.GetLength();
		int  nWide=sizeof(TCHAR)==sizeof(CHAR)?2:1;

		for (INT i=0;i<nLen;)
		{
			i+=((BYTE)(szMsg[i])>=128)?2:1;
			if ((pSub[nTextLine][0]=='\0')&&(i>=(20*(nTextLine+1)*nWide)))
			{
				_tcsncpy(pSub[nTextLine++],&szMsg[nPos],i-nPos);
				nPos=i;
				if(nTextLine==CountArray(pSub))
				{
					nPos=nLen;
					break;
				}
			}
		}
		if(nPos<nLen)
		{
			_tcsncpy(pSub[nTextLine++],&szMsg[nPos],nLen-nPos);
		}
		
 		if (nTextLine==3)
 		{
 			m_D3DRollFont.DrawText(pD3DDevice,szSub1, &m_rcText,DT_CENTER,D3DCOLOR_XRGB(255,255,255));
 			CRect rcLine=m_rcText;
 			rcLine.top+=25;
 			if (rcLine.top<rcLine.bottom)
 				m_D3DRollFont.DrawText(pD3DDevice,szSub2, &rcLine,DT_CENTER,D3DCOLOR_XRGB(255,255,255));
 			rcLine.top+=25;
 			if(rcLine.top<rcLine.bottom)
 				m_D3DRollFont.DrawText(pD3DDevice,szSub3, &rcLine,DT_CENTER,D3DCOLOR_XRGB(255,255,255));
 		}
 		else if(nTextLine==2)
 		{
 			m_D3DRollFont.DrawText(pD3DDevice,szSub1, &m_rcText,DT_CENTER,D3DCOLOR_XRGB(255,255,255));
 			CRect rcLine=m_rcText;
 			rcLine.top+=25;
 			if(rcLine.top<rcLine.bottom)
 				m_D3DRollFont.DrawText(pD3DDevice,szSub2, &rcLine,DT_CENTER,D3DCOLOR_XRGB(255,255,255));
 		}
 		else
 		{
 			m_D3DRollFont.DrawText(pD3DDevice,m_strRollText, &m_rcText,DT_CENTER,D3DCOLOR_XRGB(255,255,255));
 		}
	}
}

void CGameFrameViewD3D::OnTimer(UINT nIDEvent)
{
	if(IDI_ROLL_TEXT==nIDEvent)
	{	
		m_wRollTextCount--;

		LONG lLeft=m_rcText.left;
		if(m_wRollTextCount<50)
		{
			m_rcText=CRect(m_wTextLeft,319,m_wTextLeft+500,319+m_wRollTextCount*2);
		}
		else if(m_wRollTextCount>=110)
		{
			m_rcText=CRect(m_wTextLeft,430-(160-m_wRollTextCount),m_wTextLeft+500,430);
		}
		else
		{
			m_rcText=CRect(m_wTextLeft,m_wRollTextCount+270,m_wTextLeft+500,m_wRollTextCount+370);
		}	

		if(m_wRollTextCount==0)
		{
			if(m_vecText.size()<=1)
			{
				InvalidateRect(NULL);
				m_vecText.clear();
				KillTimer(IDI_ROLL_TEXT);
				m_wRollTextCount=160;
				m_strRollText="";
				m_rcText.SetRect(0,0,1,1);
			}
			else
			{
				InvalidateRect(NULL);
				vector <CString>::iterator Iter;
				Iter=m_vecText.begin();
				m_vecText.erase(Iter);
				m_strRollText=m_vecText.at(0);
				m_wRollTextCount=160;
				m_rcText=CRect(m_wTextLeft,m_wRollTextCount+270,m_wTextLeft+500,m_wRollTextCount+370);
			}

		}
	}
	__super::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////////////
