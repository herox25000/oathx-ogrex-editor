#include "Stdafx.h"
#include "Resource.h"
#include "GlobalUnits.h"
#include "UserInfoView.h"

//////////////////////////////////////////////////////////////////////////

//��ɫ����
#define CR_TEXT						RGB(0,0,0)					//������ɫ
#define CR_BACKGROUP				RGB(255,232,160)			//������ɫ

#define IDC_USER_INFO_EDIT			104									//�༭�ؼ�

//////////////////////////////////////////////////////////////////////////
//�༭��
BEGIN_MESSAGE_MAP(CEditUnderWrite, CSkinEditEx)
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

//userinfo����
BEGIN_MESSAGE_MAP(CUserInfoView, CDialog)
	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()

	//�Զ���Ϣ
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CEditUnderWrite::CEditUnderWrite()
{
	//���ñ���
	m_bNeedSend=false;
	m_pParentWnd=NULL;
	ZeroMemory(m_szUnderWrite,sizeof(m_szUnderWrite));

	return;
}

//��������
CEditUnderWrite::~CEditUnderWrite()
{
}

//��Ϣ����
BOOL CEditUnderWrite::PreTranslateMessage(MSG * pMsg)
{
	//ȡ����Ϣ
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		//�رտؼ�
		CloseUnderWrite();
		return TRUE;
	}

	//ȷ����Ϣ
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_RETURN))
	{
		//���ý���
		ASSERT(m_pParentWnd!=NULL);
		if (m_pParentWnd!=NULL)
			m_pParentWnd->SetFocus();

		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//�ӿڲ�ѯ
void * __cdecl CEditUnderWrite::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITCPSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITCPSocketSink,Guid,dwQueryVer);
	return NULL;
}

//�����¼�
bool __cdecl CEditUnderWrite::OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode)
{
	//�����ж�
	if (nErrorCode!=0L)
	{
		//������ʾ
		ShowInformationEx(TEXT("����������ʧ�ܣ�����ǩ������ʧ�ܣ�"),0,MB_ICONQUESTION,TEXT("ǩ��"));
		return true;
	}
	//���ñ���
	m_bNeedSend=false;

	tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();

	//���͸�������
	CMD_TOOLBOX_ModifyUnderWrite Write;
	ZeroMemory(&Write,sizeof(Write));
	Write.dwUserID = GlobalUserInfo.dwUserID;
	lstrcpyn(Write.szUnderWrite,m_szUnderWrite,CountArray(Write.szUnderWrite));
	m_SocketHelper->SendData(MDM_TOOLBOX,SUB_TOOLBOX_TMODIFYUNDERWRITE,&Write,sizeof(Write));

	return true;
}
//�ر��¼�
bool __cdecl CEditUnderWrite::OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason)
{
	CloseUnderWrite();
	return true;
}
//��ȡ�¼�
bool __cdecl CEditUnderWrite::OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize)
{
	if(Command.wMainCmdID == MDM_TOOLBOX)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_TOOLBOX_OPERATERETURN:	
			{
				if(wDataSize != sizeof(CMD_TOOLBOX_OperateReturn))
					return true;
				CMD_TOOLBOX_OperateReturn* pReturn = (CMD_TOOLBOX_OperateReturn*)pData;

				//������سɹ�
				if(pReturn->lResultCode == 0)
				{
					tagGlobalUserData * pGlobalUserData= &g_GlobalUnits.GetGolbalUserData();
					lstrcpyn(pGlobalUserData->szUnderWrite,m_szUnderWrite,CountArray(pGlobalUserData->szUnderWrite));
				}
				//���ÿؼ�
				CloseUnderWrite();
				//��ʾ��Ϣ
				if (pReturn->szDescribeString[0]!=0)
				{
					ShowInformationEx(pReturn->szDescribeString,0,MB_ICONQUESTION,TEXT("ǩ��"));
				}
				return true;
			}
		}
	}
	//�������
	ASSERT(FALSE);
	return true;
}

bool CEditUnderWrite::IsModifyStatus()
{
	//״̬�ж�
	if (m_bNeedSend==true) return true;
	//if (GetActiveStatus()==true) return true;

	return false;
}

//���ô���
VOID CEditUnderWrite::SetParentWindow(CWnd * pParentWnd)
{
	//���ñ���
	m_pParentWnd=pParentWnd;

	return;
}

//�رտؼ�
VOID CEditUnderWrite::CloseUnderWrite()
{
	//�ر��ж�
	if ((m_bNeedSend==false))
	{
		//���ٴ���
		DestroyWindow();
	}
	else
	{
		//���ش���
		ShowWindow(SW_HIDE);
	}

	//���½���
	ASSERT(m_pParentWnd!=NULL);
	m_pParentWnd->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//����ǩ��
VOID CEditUnderWrite::UpdateUnderWrite()
{
	if (IsWindowVisible()==TRUE)
	{
		//��ȡ��Ϣ
		TCHAR szUnderWrite[UNDER_WRITE_LEN]=TEXT("");
		GetWindowText(szUnderWrite,CountArray(szUnderWrite));

		tagGlobalUserData & GlobalUserData=g_GlobalUnits.GetGolbalUserData();
		//�����ж�
		bool bActiveMission=false;
		if ((IsModifyStatus()==true)&&(lstrcmp(szUnderWrite,m_szUnderWrite)!=0L)) 
			bActiveMission=true;
		if ((IsModifyStatus()==false)&&(lstrcmp(szUnderWrite,GlobalUserData.szUnderWrite)!=0L))
			bActiveMission=true;

		//�����ж�
		if (bActiveMission==true)
		{
			//������Ϣ
			m_bNeedSend=true;
			lstrcpyn(m_szUnderWrite,szUnderWrite,CountArray(m_szUnderWrite));

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
					ShowInformationEx(TEXT("��������ʧ��3����Ǹ��"),0,MB_ICONQUESTION,TEXT("ǩ��"));
					return ;
				}
			}

			if (m_SocketHelper.GetInterface()!=NULL)
				m_SocketHelper->CloseSocket();

			DWORD dwIP = g_GlobalUnits.m_ServerListManager.m_dwToolServerAddr;
			WORD wPort = g_GlobalUnits.m_ServerListManager.m_wToolServerPort;
			if (dwIP!=0 && wPort!=0)
			{
				m_SocketHelper->Connect( dwIP, wPort);
			}
			else
			{
				ShowInformationEx("��Ǹ���˹�����ʱ����ʹ�ã�",0,MB_ICONQUESTION,TEXT("ǩ��"));
				return ;
			}	
			//���ؿؼ�
			ShowWindow(SW_HIDE);
			//���½���
			ASSERT(m_pParentWnd!=NULL);
			m_pParentWnd->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
		}
		else
		{
			//�رտؼ�
			CloseUnderWrite();
		}
	}
	return;
}

//������Ϣ
VOID CEditUnderWrite::OnDestroy()
{
	__super::OnDestroy();

	if(m_SocketHelper.GetInterface()!=NULL)
		m_SocketHelper->CloseSocket();
	//���½���
	ASSERT(m_pParentWnd!=NULL);
	m_pParentWnd->RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	return;
}

//ʧȥ����
VOID CEditUnderWrite::OnKillFocus(CWnd * pNewWnd)
{
	__super::OnKillFocus(pNewWnd);
	//�رտؼ�
	UpdateUnderWrite();
	return;
}



//////////////////////////////////////////////////////////////////////////

//���캯��
CUserInfoView::CUserInfoView() : CDialog(IDD_USER_INFO)
{
	//״̬����
	m_nTitleHeight=0;
	m_bShowInfo=false;
	m_bCreateFlag=false;
	m_bHoverUnderWrite = false;
	m_EditUnderWrite.SetParentWindow(this);
	return;
}

//��������
CUserInfoView::~CUserInfoView()
{
}

//�ؼ���
VOID CUserInfoView::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
}

//��ʼ������
BOOL CUserInfoView::OnInitDialog()
{
	__super::OnInitDialog();

	//������Դ
	UpdateSkinResource();

	//��ȡ��С
	CImageHandle HandleTitleM(&m_ImageTitleM);
	m_nTitleHeight=m_ImageTitleM.GetHeight();

	//�ƶ�����
	SetWindowPos(NULL,0,0,0,m_nTitleHeight,SWP_NOMOVE|SWP_NOZORDER);

	//���ñ���
	m_bCreateFlag=true;

	return TRUE;
}

//����߶�
UINT CUserInfoView::GetTitleHeight()
{
	return m_nTitleHeight;
}

//������Ϣ
VOID CUserInfoView::UpdateUserInfo()
{
	//���½���
	Invalidate();

	return;
}

//��ʾ��Ϣ
VOID CUserInfoView::ShowUserInfo(bool bShowInfo)
{
	//״̬�ж�
	if (m_bShowInfo==bShowInfo) return;

	//���ñ���
	m_bShowInfo=bShowInfo;

	//���½���
	Invalidate();

	return;
}

//������Դ
bool CUserInfoView::UpdateSkinResource()
{
	//��ȡ��Դ
	tagControlViewImage & ControlViewImage=g_GlobalUnits.m_ControlViewImage;
	HINSTANCE hInstance=g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

	m_ImageTitleL.SetLoadInfo(ControlViewImage.uUserInfoL,hInstance);
	m_ImageTitleM.SetLoadInfo(ControlViewImage.uUserInfoM,hInstance);
	m_ImageTitleR.SetLoadInfo(ControlViewImage.uUserInfoR,hInstance);

	return true;
}

//�滭����
BOOL CUserInfoView::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),24);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//������Դ
	CImageHandle HandleTitleL(&m_ImageTitleL);
	CImageHandle HandleTitleM(&m_ImageTitleM);
	CImageHandle HandleTitleR(&m_ImageTitleR);

	//�滭����
	m_ImageTitleL.BitBlt(BufferDC,0,0);

	//����м�
	for (INT nXPos=m_ImageTitleL.GetWidth();nXPos<rcClient.Width();nXPos+=m_ImageTitleM.GetWidth())
	{
		m_ImageTitleM.BitBlt(BufferDC,nXPos,0);
	}

	//�滭����
	m_ImageTitleR.BitBlt(BufferDC,rcClient.Width()-m_ImageTitleR.GetWidth(),0);

	//���� DC
	pBufferDC->SetTextColor(CR_TEXT);
	pBufferDC->SetBkMode(TRANSPARENT);
	pBufferDC->SelectObject(CSkinResourceManager::GetDefaultFont());

	//�û���Ϣ
	if (m_bShowInfo==true)
	{
		//��������
		tagGlobalUserData & GlobalUserInfo=g_GlobalUnits.GetGolbalUserData();

		//���Ƹ���ǩ���༭��׿�
		if ((m_bHoverUnderWrite==true)||((m_EditUnderWrite.m_hWnd!=NULL)&&(m_EditUnderWrite.IsWindowVisible()==TRUE)))
		{
			//������Դ
			CPngImage ImageUnderWriteL;
			CPngImage ImageUnderWriteM;
			CPngImage ImageUnderWriteR;
			ImageUnderWriteL.LoadImage(AfxGetInstanceHandle(),TEXT("UNDER_WRITE_L"));
			ImageUnderWriteM.LoadImage(AfxGetInstanceHandle(),TEXT("UNDER_WRITE_M"));
			ImageUnderWriteR.LoadImage(AfxGetInstanceHandle(),TEXT("UNDER_WRITE_R"));

			//�滭����
			ImageUnderWriteL.DrawImage(pBufferDC,m_rcUnderWrite.left,m_rcUnderWrite.top);
			ImageUnderWriteR.DrawImage(pBufferDC,m_rcUnderWrite.right-ImageUnderWriteR.GetWidth(),m_rcUnderWrite.top);

			//�滭�м�
			INT nXStart=m_rcUnderWrite.left+ImageUnderWriteL.GetWidth();
			INT nXTerminate=m_rcUnderWrite.right-ImageUnderWriteR.GetWidth();
			for (INT nXPos=nXStart;nXPos<nXTerminate;nXPos+=ImageUnderWriteM.GetWidth())
			{
				ImageUnderWriteM.DrawImage(pBufferDC,nXPos,m_rcUnderWrite.top,__min(nXTerminate-nXPos,ImageUnderWriteM.GetWidth()),ImageUnderWriteM.GetHeight(),0,0);
			}
		}

		//�û�ͷ��
		g_GlobalUnits.m_UserFaceRes->DrawNormalFace(pBufferDC,37,27,GlobalUserInfo.wFaceID,GlobalUserInfo.dwUserID,GlobalUserInfo.dwCustomFaceVer);

		//����λ��
		TCHAR szBuffer[255]=TEXT("");
		CRect rcAccounts(150, 23, rcClient.Width()-20, 37);
		CRect rcID(150, 64,rcClient.Width()-20, 37);
		//�û��ʺ�
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%s"),GlobalUserInfo.szAccounts);
		pBufferDC->DrawText(szBuffer,lstrlen(szBuffer),&rcAccounts,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);
		_sntprintf(szBuffer,CountArray(szBuffer),TEXT("%d"),GlobalUserInfo.dwGameID);
		pBufferDC->DrawText(szBuffer,lstrlen(szBuffer),&rcID,DT_VCENTER|DT_WORD_ELLIPSIS|DT_SINGLELINE);

		//��������
		TCHAR pszUnderWrite[UNDER_WRITE_LEN]=TEXT("");
		COLORREF crUnderWrite=RGB(0,0,0);
		//ǩ��λ��
		CRect rcUnderWrite(153,68,rcClient.Width()-20,80);
		//����״̬
		if ((m_EditUnderWrite.IsModifyStatus()==false)&&(GlobalUserInfo.szUnderWrite[0]!=0))
		{
			crUnderWrite=RGB(0,0,0);
			_sntprintf(pszUnderWrite,CountArray(pszUnderWrite),TEXT("%s"),GlobalUserInfo.szUnderWrite);
		}
		//�޸�״̬
		if ((m_EditUnderWrite.IsModifyStatus()==true)&&(m_EditUnderWrite.m_szUnderWrite[0]!=0))
		{
			crUnderWrite=RGB(100,100,100);
			//pszUnderWrite=m_EditUnderWrite.m_szUnderWrite;
			_sntprintf(pszUnderWrite,CountArray(pszUnderWrite),TEXT("%s"),m_EditUnderWrite.m_szUnderWrite);

		}
		//��ʾ״̬
		if (pszUnderWrite==NULL)
		{
			crUnderWrite=RGB(255,150,150);
			//pszUnderWrite=TEXT("�༭����ǩ��");
			_sntprintf(pszUnderWrite,CountArray(pszUnderWrite),TEXT("�༭����ǩ��"));

		}
		//���ǩ��
		pBufferDC->SetTextColor(crUnderWrite);
		pBufferDC->DrawText(pszUnderWrite,lstrlen(pszUnderWrite),&rcUnderWrite,DT_SINGLELINE|DT_VCENTER|DT_END_ELLIPSIS);
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//λ����Ϣ
VOID CUserInfoView::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	return;
}

//�����ؼ�
VOID CUserInfoView::RectifyControl(INT nWidth, INT nHeight)
{
	//��������
	m_rcUnderWrite.SetRect(150,65,nWidth-20,85);
}
//�����Ϣ
VOID CUserInfoView::OnLButtonUp(UINT nFlags, CPoint MousePoint)
{
}
//�����Ϣ
VOID CUserInfoView::OnLButtonDown(UINT nFlags, CPoint MousePoint)
{
	__super::OnLButtonDown(nFlags,MousePoint);
	//���ý���
	SetFocus();
	//�༭ǩ��
	if (m_bHoverUnderWrite==true)
	{
		//�û���Ϣ
		tagGlobalUserData & pGlobalUserData=g_GlobalUnits.GetGolbalUserData();

		//�����ؼ�
		if (m_EditUnderWrite.m_hWnd==NULL)
		{
			//�����ؼ�
			m_EditUnderWrite.Create(WS_CHILD|ES_AUTOHSCROLL,CRect(0,0,0,0),this,IDC_USER_INFO_EDIT);
			//������Ϣ
			m_EditUnderWrite.LimitText(UNDER_WRITE_LEN-1L);
			m_EditUnderWrite.SetWindowText(pGlobalUserData.szUnderWrite);
			CFont * pFont = CFont::FromHandle(CSkinResourceManager::GetDefaultFont());
			//���ÿؼ�
			m_EditUnderWrite.SetFont(pFont);
		}

		//����λ��
		CRect rcClient;
		GetClientRect(&rcClient);
		m_EditUnderWrite.SetWindowPos(NULL,150+3,65+3,rcClient.Width()-170-6,20-6,SWP_SHOWWINDOW|SWP_NOZORDER);
		//���ÿؼ�
		m_EditUnderWrite.SetFocus();
		m_EditUnderWrite.SetSel(0L,-1L);
		//���´���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
}
//�����Ϣ
BOOL CUserInfoView::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);
	bool bRedrawWindow=false;

	//�����ж�
	if ((m_bHoverUnderWrite==false)&&(m_rcUnderWrite.PtInRect(MousePoint)==TRUE))
	{
		//���ñ���
		bRedrawWindow=true;

		//���ñ���
		m_bHoverUnderWrite=true;
	}

	//�뿪�ж�
	if ((m_bHoverUnderWrite==true)&&(m_rcUnderWrite.PtInRect(MousePoint)==FALSE))
	{
		//���ñ���
		bRedrawWindow=true;
		//���ñ���
		m_bHoverUnderWrite=false;
	}

	//���½���
	if (bRedrawWindow==true)
	{
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//����뿪
LRESULT CUserInfoView::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//�뿪����
	if (m_bHoverUnderWrite==true)
	{
		//���ñ���
		m_bHoverUnderWrite=false;
		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
