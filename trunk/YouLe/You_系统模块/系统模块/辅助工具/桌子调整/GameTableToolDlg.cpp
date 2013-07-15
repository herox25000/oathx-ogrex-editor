// GameTableToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GameTableTool.h"
#include "GameTableToolDlg.h"
#include ".\gametabletooldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameTableToolDlg �Ի���
//////////////////////////////////////////////////////////////////////////



CGameTableToolDlg::CGameTableToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGameTableToolDlg::IDD, pParent)
{
	m_bFourPixel = FALSE;
	m_bFrameAccount = FALSE;
	m_bFrameHead = FALSE;
	m_bFrameTableNo = FALSE;
	m_bHaveAccount = FALSE;
	m_bHaveHead = FALSE;
	m_bHaveLock = FALSE;

	CRect rt(0,0,0,0);
	CRect rtTableID(0,0,80,12);
	CRect rtChair(0,0,32,32);
	CRect rtName(0,0,49,37);
	m_ptLock=rt.TopLeft();
	m_rcNote=rt;
	m_rcTableID=rtTableID;

	for(int i=0;i<8;i++)
	{
		m_ptReady[i]=rtChair.TopLeft();
		m_rcName[i]=rtName;
		m_rcChair[i]=rtChair;
		m_nDrawStyle[i]=0;
	}

	m_crName=RGB(0,0,0);
	m_crNote=RGB(0,0,0);
	m_crTableID=RGB(0,0,0);

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameTableToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_COLOR, m_AccountColor);
	DDX_Control(pDX, IDC_TABLE_NOCOLOR, m_TableNoColor);
	DDX_Control(pDX, IDC_SAVE_PARAMETER, m_SaveParameter);
	DDX_Control(pDX, IDC_LOAD_PARAMETER, m_LoadParameter);
	DDX_Control(pDX, IDC_REDUCE_WIDTH, m_ReduceWidth);
	DDX_Control(pDX, IDC_REDUCE_HEIGHT, m_ReduceHeight);
	DDX_Control(pDX, IDC_ADD_WIDTH, m_AddWidth);
	DDX_Control(pDX, IDC_ADD_HEIGHT, m_AddHeight);
	DDX_Control(pDX, IDC_CURRENT_SEAT, m_CurrentSeat);
	DDX_Control(pDX, IDC_USER_NAME, m_UserName);
	DDX_Control(pDX, IDC_SEAT_COUNT, m_SeatCount);
	DDX_Control(pDX, IDC_SHOW_WND, m_ShowWnd);
	DDX_Check(pDX, IDC_FOUR_PIXEL, m_bFourPixel);
	DDX_Check(pDX, IDC_FRAME_ACCOUNT, m_bFrameAccount);
	DDX_Check(pDX, IDC_FRAME_HEAD, m_bFrameHead);
	DDX_Check(pDX, IDC_FRAME_TABLENO, m_bFrameTableNo);
	DDX_Check(pDX, IDC_HAVE_ACCOUNT, m_bHaveAccount);
	DDX_Check(pDX, IDC_HAVE_HEAD, m_bHaveHead);
	DDX_Check(pDX, IDC_HAVE_LOCK, m_bHaveLock);
	DDX_Radio(pDX, IDC_LOCAL_HEAD, m_CurrentItem);
	DDX_Radio(pDX, IDC_HALIGNMET_LEFT, m_CurrentHAlignmet);
	DDX_Radio(pDX, IDC_VALIGNMET_UP, m_CurrentVAlignmet);
}

BEGIN_MESSAGE_MAP(CGameTableToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_LOAD_IMAGE, OnLoadImage)
	ON_BN_CLICKED(IDC_LOAD_PARAMETER, OnLoadParameter)
	ON_BN_CLICKED(IDC_SAVE_PARAMETER, OnSaveParameter)
	ON_BN_CLICKED(IDC_TABLE_NOCOLOR, OnTableNocolor)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_LEFT, OnLeft)
	ON_BN_CLICKED(IDC_RIGHT, OnRight)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_BN_CLICKED(IDC_ADD_WIDTH, OnAddWidth)
	ON_BN_CLICKED(IDC_REDUCE_WIDTH, OnReduceWidth)
	ON_BN_CLICKED(IDC_ADD_HEIGHT, OnAddHeight)
	ON_BN_CLICKED(IDC_REDUCE_HEIGHT, OnReduceHeight)
	ON_BN_CLICKED(IDC_VALIGNMET_UP, OnValignmetUp)
	ON_BN_CLICKED(IDC_VALIGNMET_DOWN, OnValignmetDown)
	ON_BN_CLICKED(IDC_VALIGNMET_CENTER, OnValignmetCenter)
	ON_BN_CLICKED(IDC_HAVE_ACCOUNT, OnHaveAccount)
	ON_BN_CLICKED(IDC_HAVE_HEAD, OnHaveHead)
	ON_BN_CLICKED(IDC_HAVE_LOCK, OnHaveLock)
	ON_BN_CLICKED(IDC_FRAME_ACCOUNT, OnFrameAccount)
	ON_BN_CLICKED(IDC_FRAME_HEAD, OnFrameHead)
	ON_BN_CLICKED(IDC_FRAME_TABLENO, OnFrameTableno)
	ON_BN_CLICKED(IDC_HALIGNMET_RIGHT, OnHalignmetRight)
	ON_BN_CLICKED(IDC_HALIGNMET_CENTER, OnHalignmetCenter)
	ON_BN_CLICKED(IDC_HALIGNMET_LEFT, OnHalignmetLeft)
	ON_BN_CLICKED(IDC_LOCAL_LOCK, OnLocalLock)
	ON_BN_CLICKED(IDC_LOCAL_HAND, OnLocalHand)
	ON_BN_CLICKED(IDC_LOCAL_TABLENO, OnLocalTableno)
	ON_BN_CLICKED(IDC_LOCAL_ACCOUNT, OnLocalAccount)
	ON_BN_CLICKED(IDC_LOCAL_HEAD, OnLocalHead)
	ON_BN_CLICKED(IDC_ACCOUNT_COLOR, OnAccountColor)

	//}}AFX_MSG_MAP
	ON_CBN_SELENDOK(IDC_SEAT_COUNT, OnCbnSelendokSeatCount)
	ON_CBN_SELENDOK(IDC_USER_NAME, OnCbnSelendokUserName)
	ON_CBN_SELENDOK(IDC_CURRENT_SEAT, OnCbnSelendokCurrentSeat)
	ON_BN_CLICKED(IDC_FOUR_PIXEL, OnBnClickedFourPixel)
END_MESSAGE_MAP()


// CGameTableToolDlg ��Ϣ�������

BOOL CGameTableToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//�������������ӵĸ���
	for(int i=0;i<8;i++)
	{
		CString strSeatName;
		strSeatName.Format("%d ��",i+1);
		m_SeatCount.AddString(strSeatName);
	}
	m_SeatCount.SetCurSel(3);

	//�����û����Ƶ���ʽ
	m_UserName.AddString(TEXT("King"));
	m_UserName.AddString(TEXT("��������"));
	m_UserName.AddString(TEXT("����������������"));
	m_UserName.AddString(TEXT("������������������������"));
	m_UserName.AddString(TEXT("�������ֳ������ֳ������ֳ�������"));
	m_UserName.SetCurSel(0);
	
	//���õ�ǰ���������Ӻ�
	int nSeatCount=m_SeatCount.GetCurSel();
	if(nSeatCount!=CB_ERR)
	{
		nSeatCount=nSeatCount+1;
	}
	else
	{
		nSeatCount=10;
	}
	for(i=0;i<nSeatCount;i++)
	{
		CString strSeatName;
		strSeatName.Format("%d",i+1);
		m_CurrentSeat.AddString(strSeatName);
	}
	m_CurrentChairID=0;
	m_CurrentSeat.SetCurSel(m_CurrentChairID);

	//���ø�ѡ���ѡ��״̬
	m_bHaveAccount  =TRUE;
	m_bHaveHead     =TRUE;
	m_bHaveLock     =FALSE;
	m_bFrameAccount =TRUE;
	m_bFrameHead    =TRUE;
	m_bFrameTableNo =TRUE;

	//��ѡ��ĳ�ʼ������
	m_CurrentItem=0;
	m_CurrentHAlignmet=1;
	m_CurrentVAlignmet=0;

	//��ֹ������ť�Ĳ���
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_LoadParameter.EnableWindow(false);
	m_SaveParameter.EnableWindow(false);
	m_TableNoColor.EnableWindow(false);
	m_AccountColor.EnableWindow(false);

	this->UpdateData(FALSE);

	m_bLoadParameter=false;
	m_ChairCount=0;

	CreateMyBitMap(&m_MemBitmap);
	m_ShowWnd.SetBitmap((HBITMAP)m_MemBitmap.Detach());

	m_ImageReady.LoadFromResource(AfxGetInstanceHandle(),IDB_Ready);
	m_ImageLock.LoadFromResource(AfxGetInstanceHandle(),IDB_LOCK);
	//for(int i=0;i<8;i++)
	//{
	//	m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HEAD1+i);
	//}

	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CGameTableToolDlg::CreateMyBitMap(CBitmap *pBitmap)
{
	CClientDC dc(this);

	//��ͼ׼������
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	MemDC.SetBkMode(TRANSPARENT);
	pBitmap->CreateCompatibleBitmap(&dc, 560, 470);
	MemDC.SelectObject(pBitmap);

	//��������
	CFont DrawFont;
	DrawFont.CreateFont(-12,0,0,0,400,0,0,0,134,3,2,1,2,TEXT("����"));
	MemDC.SelectObject(&DrawFont);

	//��䱳������
	MemDC.FillSolidRect(0,0,560,470,RGB(230,249,255));

	//��ʾ����ͼƬ
	DrawTableImage(&MemDC);

	//��ʾ�û�������ʶ
	DrawParameter(&MemDC);

	DrawFont.DeleteObject();
	MemDC.DeleteDC();
}

//����ˢ�»���
void CGameTableToolDlg::UpdateShow()
{
	m_MemBitmap.DeleteObject();
	CreateMyBitMap(&m_MemBitmap);
	m_ShowWnd.SetBitmap((HBITMAP)m_MemBitmap.Detach());
}

//��ʾ����ͼƬ
void CGameTableToolDlg::DrawTableImage(CDC *pDC)
{
	if (!m_ImageTable.IsNull())
	{
		int nWidth=m_ImageTable.GetWidth();
		int nHeight=m_ImageTable.GetHeight();
		m_ImageTable.BitBlt(pDC->GetSafeHdc(),0,0,nWidth,nHeight,0,0,SRCCOPY);
	}
}
//��ʾ�û�������ʶ
void CGameTableToolDlg::DrawParameter(CDC *pDC)
{
	if(m_bLoadParameter==true)
	{
		//��ʾ������
		int nXLock=m_ptLock.x-m_ImageLock.GetWidth()/2+2;
		int nYLock=m_ptLock.y-m_ImageLock.GetHeight()/2+5;
		COLORREF cbMask=m_ImageLock.GetPixel(1,1);
		m_ImageLock.AlphaDrawImage(pDC,nXLock,nYLock,cbMask);

		//��ʾ���Ӻ�
		TCHAR szBuffer[32];
		pDC->SetTextColor(m_crTableID);
		_snprintf(szBuffer,sizeof(szBuffer),TEXT("- %d -"),123);
		pDC->DrawText(szBuffer,lstrlen(szBuffer),&m_rcTableID,DT_VCENTER|DT_CENTER|DT_NOCLIP|DT_SINGLELINE);
		if(m_bFrameTableNo==TRUE)
		{
			pDC->Draw3dRect(m_rcTableID,RGB(255,255,255),RGB(255,255,255));
		}

		CString strUserName;
		int Index=m_UserName.GetCurSel();
		int nLength=m_UserName.GetLBTextLen(Index);
		m_UserName.GetLBText(Index, strUserName.GetBuffer(nLength));
		strUserName.ReleaseBuffer();

		for(int i=0;i<m_ChairCount;i++)
		{
			//�û�ͷ��
			if(m_bHaveHead==TRUE && m_ChairCount>1)
			{
				int nWidth=m_ImagePeople[i].GetWidth();
				int nHeight=m_ImagePeople[i].GetHeight();
				m_ImagePeople[i].BitBlt(pDC->GetSafeHdc(),m_rcChair[i].left,m_rcChair[i].top,nWidth,nHeight,nWidth/2,0,SRCAND);
				m_ImagePeople[i].BitBlt(pDC->GetSafeHdc(),m_rcChair[i].left,m_rcChair[i].top,nWidth,nHeight,0,0,SRCPAINT);
			}

			//����λ��
			int nWidth=m_ImageReady.GetWidth();
			int nHeight=m_ImageReady.GetHeight();
			COLORREF cbMask=m_ImageReady.GetPixel(0,0);
			m_ImageReady.AlphaDrawImage(pDC,m_ptReady[i].x,m_ptReady[i].y,cbMask);

			if(m_bHaveLock==TRUE)
			{
				CRect ct;
				ct.left=m_ptReady[i].x-15;
				ct.right=m_ptReady[i].x+15;
				ct.top=m_ptReady[i].y-15;
				ct.bottom=m_ptReady[i].y+15;
				pDC->Draw3dRect(&ct,RGB(255,255,255),RGB(255,255,255));
			}

			//λ�ñ���
			if(m_bHaveAccount==TRUE)
			{
				int nYPos=0;
				int nDrawStyte=m_nDrawStyle[i];
				CRect rcDrawRect=m_rcName[i];
				int nDrawFormat=DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS;
				int nNameLength=strUserName.GetLength();
				int nNameHeight=pDC->DrawText(strUserName,nNameLength,&rcDrawRect,nDrawFormat|DT_CALCRECT);

				//����λ��
				if (nDrawStyte&NT_LEFT) nDrawFormat|=DT_LEFT;
				else if (nDrawStyte&NT_CENTER) nDrawFormat|=DT_CENTER;
				else nDrawFormat|=DT_RIGHT;
				if (nDrawStyte&NT_VCENTER) nYPos=(m_rcName[i].Height()-nNameHeight)/2;
				else if (nDrawStyte&NT_BOTTOM) nYPos=(m_rcName[i].Height()-nNameHeight);
				if (nYPos<0) nYPos=0;
				rcDrawRect.left=m_rcName[i].left;
				rcDrawRect.right=m_rcName[i].right;
				rcDrawRect.top=m_rcName[i].top+nYPos;
				rcDrawRect.bottom=m_rcName[i].bottom;

				//�û�����
				pDC->SetTextColor(m_crName);
				pDC->DrawText(strUserName,nNameLength,&rcDrawRect,nDrawFormat);

				if(m_bFrameAccount==TRUE)
				{
					pDC->Draw3dRect(&rcDrawRect,RGB(255,255,255),RGB(255,255,255));
				}
			}
		}
	}
}

void CGameTableToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CGameTableToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CGameTableToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGameTableToolDlg::OnLoadImage() 
{
	// TODO: Add your control notification handler code here
	//ѡ���ļ�
	LPCTSTR pszFilter=TEXT("֧�ָ�ʽ(*.bmp;*.jpg;*.gif;*.png)|*.bmp; *.jpg; *.jpeg; *.jpe;*.jfif;*.gif;*.png|�����ļ� (*.*)|*.*||");
	CFileDialog FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,pszFilter);

	if(IDOK == FileDlg.DoModal())
	{
		//����ͼƬ
		CString strName = FileDlg.GetPathName() ;

		//�ͷ��ж�
		if ( !m_ImageTable.IsNull() ) m_ImageTable.Destroy();

		HRESULT hResult = m_ImageTable.Load(strName);

		//�ɹ��ж�
		if ( SUCCEEDED(hResult) )
		{
			UpdateShow();
		}
		else
		{
			AfxMessageBox(TEXT("����ͼƬʧ�ܣ�������ѡ��"));
			return ;
		}
	}

	m_LoadParameter.EnableWindow(true);
	m_SaveParameter.EnableWindow(true);
	m_TableNoColor.EnableWindow(true);
	m_AccountColor.EnableWindow(true);
}

void CGameTableToolDlg::OnLoadParameter() 
{
	//ѡ���ļ�
	LPCTSTR pszFilter=TEXT("֧�ָ�ʽ(*.DAT;*.dat;)|*.DAT; *.dat;|�����ļ� (*.*)|*.*||");
	CFileDialog FileDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,pszFilter);

	CString szResourcePath;
	if(IDOK == FileDlg.DoModal())
	{
		szResourcePath = FileDlg.GetPathName() ;
	}
	if(szResourcePath.GetLength()>0 && szResourcePath.IsEmpty()==false)
	{
		try
		{
			CFile ResourceFile;
			tagTableConfigFile TableConfig;
			if (ResourceFile.Open(szResourcePath,CFile::modeRead,NULL)==FALSE) throw 0;

			ULONGLONG uLong=ResourceFile.GetLength();
			ASSERT(uLong==sizeof(tagTableConfigFile));
			if(uLong!=sizeof(tagTableConfigFile)) throw 0;

			UINT uReadCount=ResourceFile.Read(&TableConfig,sizeof(TableConfig));
			if (uReadCount!=sizeof(TableConfig)) throw 0;
			if (TableConfig.wFileSize!=sizeof(TableConfig)) throw 0;
			if (TableConfig.wStructVer!=1) throw 0;

			//���ò���
			tagTableResourceInfo * pResourceInfo=&TableConfig.TableResourceInfo;

			m_ptLock=pResourceInfo->ptLock;
			m_rcNote=pResourceInfo->rcNote;
			m_rcTableID=pResourceInfo->rcTableID;

			m_crName=pResourceInfo->crName;
			m_crNote=pResourceInfo->crNote;
			m_crTableID=pResourceInfo->crTableID;
			
			for (int i=0;i<8;i++)
			{
				m_ptReady[i]=pResourceInfo->ptReady[i];
				m_rcName[i]=pResourceInfo->rcName[i];
				m_rcChair[i]=pResourceInfo->rcChair[i];
				m_nDrawStyle[i]=pResourceInfo->nDrawStyle[i];
			}

			for(int j=0;j<8;j++)
			{
				if(m_rcChair[j].left==0)
				{
					m_SeatCount.SetCurSel(j-1);
					m_ChairCount=j;
					break;
				}
			}
			//����������������ͼƬ
			for(int i=0;i<8;i++)
			{
				if(!m_ImagePeople[i].IsNull())
				{
					m_ImagePeople[i].Destroy();
				}
			}
			switch(m_ChairCount)
			{
				case 2:
					for(int i=0;i<2;i++)
					{
						m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HAND+i);
					}
					break;
				case 3:
					for(int i=0;i<3;i++)
					{
						m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HAND+i);
					}
					break;
				case 4:
					for(int i=0;i<4;i++)
					{
						m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HAND+i);
					}
					break;
				case 5:
					for(int i=0;i<5;i++)
					{
						m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HAND+i);
					}
					break;
			}

			//���õ�ǰ���������Ӻ�
			m_CurrentSeat.ResetContent();
			for(i=0;i<m_ChairCount;i++)
			{
				CString strSeatName;
				strSeatName.Format("%d",i+1);
				m_CurrentSeat.AddString(strSeatName);
			}
			m_CurrentChairID=0;
			m_CurrentSeat.SetCurSel(m_CurrentChairID);

			//������ǰ���Ӻ����Ե��ı����뷽ʽ
			OnCbnSelendokCurrentSeat();

			//ˢ�½���
			m_bLoadParameter=true;
			UpdateShow();
		}
		catch(...)
		{
			AfxMessageBox(TEXT("���ز���ʧ�ܣ�������ѡ��"));
			return ;
		}
	}
	
}

void CGameTableToolDlg::OnSaveParameter() 
{
	//ѡ���ļ�
	LPCTSTR pszFilter=TEXT("֧�ָ�ʽ(*.DAT;*.dat;)|*.DAT; *.dat;|�����ļ� (*.*)|*.*||");
	CFileDialog FileDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,pszFilter);

	CString szResourcePath;
	if(IDOK == FileDlg.DoModal())
	{
		szResourcePath = FileDlg.GetPathName() ;
	}
	if(szResourcePath.GetLength()>0 && szResourcePath.IsEmpty()==false)
	{
		try
		{
			CFile ResourceFile;
			if (ResourceFile.Open(szResourcePath,CFile::modeWrite|CFile::modeCreate,NULL)==FALSE) throw 0;

			tagTableConfigFile TableConfig;
			ZeroMemory(&TableConfig,sizeof(TableConfig));
			TableConfig.wFileSize=sizeof(TableConfig);
			TableConfig.wStructVer=RESOURCE_VER;

			//���ò���
			tagTableResourceInfo * pResourceInfo=&TableConfig.TableResourceInfo;

			pResourceInfo->crName=m_crName;
			pResourceInfo->crNote=m_crNote;
			pResourceInfo->crTableID=m_crTableID;

			pResourceInfo->ptLock=m_ptLock;
			pResourceInfo->rcNote=m_rcNote;
			pResourceInfo->rcTableID=m_rcTableID;

			for (int i=0;i<m_ChairCount;i++)
			{
				pResourceInfo->rcName[i]=m_rcName[i];
				pResourceInfo->rcChair[i]=m_rcChair[i];
				pResourceInfo->ptReady[i]=m_ptReady[i];
				
				pResourceInfo->nDrawStyle[i]=m_nDrawStyle[i];
			}
			CRect rt(0,0,0,0);
			for(int i=m_ChairCount;i<8;i++)
			{
				pResourceInfo->rcName[i]=rt;
				pResourceInfo->rcChair[i]=rt;
				pResourceInfo->ptReady[i]=rt.TopLeft();
				
				pResourceInfo->nDrawStyle[i]=0;
			}

			ResourceFile.Write(&TableConfig,sizeof(TableConfig));
			ResourceFile.Flush();
			ResourceFile.Close();			
		}
		catch(...)
		{
			AfxMessageBox("�����ļ�����!");
		}
	}

}

void CGameTableToolDlg::OnTableNocolor() 
{
	CColorDialog ColorDialog(m_crTableID,CC_FULLOPEN);
	if (ColorDialog.DoModal()==IDOK)
	{
		m_crTableID=ColorDialog.GetColor();
	}
	UpdateShow();
}


void CGameTableToolDlg::OnOK() 
{
	CDialog::OnOK();
}

void CGameTableToolDlg::OnUp() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			m_rcChair[m_CurrentChairID].top-=40;
			m_rcChair[m_CurrentChairID].bottom-=40;
		}
		else
		{
			m_rcChair[m_CurrentChairID].top-=1;
			m_rcChair[m_CurrentChairID].bottom-=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].top-=10;
			m_rcName[m_CurrentChairID].bottom-=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].top-=1;
			m_rcName[m_CurrentChairID].bottom-=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			m_rcTableID.top-=10;
			m_rcTableID.bottom-=10;
		}
		else
		{
			m_rcTableID.top-=1;
			m_rcTableID.bottom-=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].y-=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].y-=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.y-=10;
		}
		else
		{
			m_ptLock.y-=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnLeft() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			m_rcChair[m_CurrentChairID].left-=40;
			m_rcChair[m_CurrentChairID].right-=40;
		}
		else
		{
			m_rcChair[m_CurrentChairID].left-=1;
			m_rcChair[m_CurrentChairID].right-=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].left-=10;
			m_rcName[m_CurrentChairID].right-=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].left-=1;
			m_rcName[m_CurrentChairID].right-=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			m_rcTableID.left-=10;
			m_rcTableID.right-=10;
		}
		else
		{
			m_rcTableID.left-=1;
			m_rcTableID.right-=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].x-=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].x-=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.x-=10;
		}
		else
		{
			m_ptLock.x-=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnRight() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			m_rcChair[m_CurrentChairID].left+=40;
			m_rcChair[m_CurrentChairID].right+=40;
		}
		else
		{
			m_rcChair[m_CurrentChairID].left+=1;
			m_rcChair[m_CurrentChairID].right+=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].left+=10;
			m_rcName[m_CurrentChairID].right+=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].left+=1;
			m_rcName[m_CurrentChairID].right+=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			m_rcTableID.left+=10;
			m_rcTableID.right+=10;
		}
		else
		{
			m_rcTableID.left+=1;
			m_rcTableID.right+=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].x+=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].x+=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.x+=10;
		}
		else
		{
			m_ptLock.x+=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnDown() 
{
	switch(m_CurrentItem)
	{
	case 0:
		if(m_bFourPixel==TRUE)
		{
			m_rcChair[m_CurrentChairID].top+=40;
			m_rcChair[m_CurrentChairID].bottom+=40;
		}
		else
		{
			m_rcChair[m_CurrentChairID].top+=1;
			m_rcChair[m_CurrentChairID].bottom+=1;
		}
		break;
	case 1:
		if(m_bFourPixel==TRUE)
		{
			m_rcName[m_CurrentChairID].top+=10;
			m_rcName[m_CurrentChairID].bottom+=10;
		}
		else
		{
			m_rcName[m_CurrentChairID].top+=1;
			m_rcName[m_CurrentChairID].bottom+=1;
		}
		break;
	case 2:
		if(m_bFourPixel==TRUE)
		{
			m_rcTableID.top+=10;
			m_rcTableID.bottom+=10;
		}
		else
		{
			m_rcTableID.top+=1;
			m_rcTableID.bottom+=1;
		}
		break;
	case 3:
		if(m_bFourPixel==TRUE)
		{
			m_ptReady[m_CurrentChairID].y+=10;
		}
		else
		{
			m_ptReady[m_CurrentChairID].y+=1;
		}
		break;
	case 4:
		if(m_bFourPixel==TRUE)
		{
			m_ptLock.y+=10;
		}
		else
		{
			m_ptLock.y+=1;
		}
		break;
	}
	UpdateShow();
}

void CGameTableToolDlg::OnAddWidth() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].left-=1;
		m_rcName[m_CurrentChairID].right+=1;
		break;
	case 2:
		m_rcTableID.left-=1;
		m_rcTableID.right+=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnReduceWidth() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].left+=1;
		m_rcName[m_CurrentChairID].right-=1;
		break;
	case 2:
		m_rcTableID.left+=1;
		m_rcTableID.right-=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnAddHeight() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].top-=1;
		m_rcName[m_CurrentChairID].bottom+=1;
		break;
	case 2:
		m_rcTableID.top-=1;
		m_rcTableID.bottom+=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnReduceHeight() 
{
	switch(m_CurrentItem)
	{
	case 1:
		m_rcName[m_CurrentChairID].top+=1;
		m_rcName[m_CurrentChairID].bottom-=1;
		break;
	case 2:
		m_rcTableID.top+=1;
		m_rcTableID.bottom-=1;
		break;
	}
	UpdateShow();	
}

void CGameTableToolDlg::OnValignmetUp() 
{
	m_nDrawStyle[m_CurrentChairID]&=0x0F;
	m_nDrawStyle[m_CurrentChairID]|=NT_TOP;
	UpdateShow();	
}

void CGameTableToolDlg::OnValignmetDown() 
{
	m_nDrawStyle[m_CurrentChairID]&=0x0F;
	m_nDrawStyle[m_CurrentChairID]|=NT_BOTTOM;
	UpdateShow();	
}

void CGameTableToolDlg::OnValignmetCenter() 
{
	m_nDrawStyle[m_CurrentChairID]&=0x0F;
	m_nDrawStyle[m_CurrentChairID]|=NT_VCENTER;
	UpdateShow();	
}

void CGameTableToolDlg::OnHaveAccount() 
{
	// TODO: Add your control notification handler code here
	m_bHaveAccount=!m_bHaveAccount;
	UpdateShow();
}

void CGameTableToolDlg::OnHaveHead() 
{
	// TODO: Add your control notification handler code here
	m_bHaveHead=!m_bHaveHead;
	UpdateShow();
}

void CGameTableToolDlg::OnHaveLock() 
{
	// TODO: Add your control notification handler code here
	m_bHaveLock=!m_bHaveLock;
	UpdateShow();
}

void CGameTableToolDlg::OnFrameAccount() 
{
	// TODO: Add your control notification handler code here
	m_bFrameAccount=!m_bFrameAccount;
	UpdateShow();
}

void CGameTableToolDlg::OnFrameHead() 
{
	// TODO: Add your control notification handler code here
	m_bFrameHead=!m_bFrameHead;
	UpdateShow();
}

void CGameTableToolDlg::OnFrameTableno() 
{
	// TODO: Add your control notification handler code here
	m_bFrameTableNo=!m_bFrameTableNo;
	UpdateShow();
}

void CGameTableToolDlg::OnHalignmetRight() 
{
	m_nDrawStyle[m_CurrentChairID]&=0xF0;
	m_nDrawStyle[m_CurrentChairID]|=NT_RIGHT;
	UpdateShow();
}

void CGameTableToolDlg::OnHalignmetCenter() 
{
	m_nDrawStyle[m_CurrentChairID]&=0xF0;
	m_nDrawStyle[m_CurrentChairID]|=NT_CENTER;
	UpdateShow();
}

void CGameTableToolDlg::OnHalignmetLeft() 
{
	m_nDrawStyle[m_CurrentChairID]&=0xF0;
	m_nDrawStyle[m_CurrentChairID]|=NT_LEFT;
	UpdateShow();
}

void CGameTableToolDlg::OnLocalLock() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_CurrentItem=10;
	
}

void CGameTableToolDlg::OnLocalHand() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_CurrentItem=3;
	
}

void CGameTableToolDlg::OnLocalTableno() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(true);
	m_AddWidth.EnableWindow(true);
	m_ReduceHeight.EnableWindow(true);
	m_ReduceWidth.EnableWindow(true);

	m_CurrentItem=2;
	
}

void CGameTableToolDlg::OnLocalAccount() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(true);
	m_AddWidth.EnableWindow(true);
	m_ReduceHeight.EnableWindow(true);
	m_ReduceWidth.EnableWindow(true);

	m_CurrentItem=1;
	
}

void CGameTableToolDlg::OnLocalHead() 
{
	// TODO: Add your control notification handler code here
	m_AddHeight.EnableWindow(false);
	m_AddWidth.EnableWindow(false);
	m_ReduceHeight.EnableWindow(false);
	m_ReduceWidth.EnableWindow(false);

	m_CurrentItem=0;
	
}

void CGameTableToolDlg::OnAccountColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDialog(m_crName,CC_FULLOPEN);
	if (ColorDialog.DoModal()==IDOK)
	{
		m_crName=ColorDialog.GetColor();
	}
	UpdateShow();
}

void CGameTableToolDlg::OnCbnSelendokSeatCount()
{
	int nSeatCount=m_SeatCount.GetCurSel();

	if(nSeatCount!=CB_ERR)
	{
		m_ChairCount=nSeatCount+1;
	}
	else
	{
		m_ChairCount=4;
	}
	m_CurrentSeat.ResetContent();
	for(int i=0;i<m_ChairCount;i++)
	{
		CString strSeatName;
		strSeatName.Format("%d",i+1);
		m_CurrentSeat.AddString(strSeatName);
	}
	m_CurrentChairID=0;
	m_CurrentSeat.SetCurSel(m_CurrentChairID);	

	//����������������ͼƬ
	for(int i=0;i<8;i++)
	{
		if(!m_ImagePeople[i].IsNull())
		{
			m_ImagePeople[i].Destroy();
		}
	}
	switch(m_ChairCount)
	{
	case 2:
		for(int i=0;i<2;i++)
		{
			m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HD20+i);
		}
		break;
	case 3:
	case 4:
		for(int i=0;i<4;i++)
		{
			m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HD00+i);
		}
		break;
	case 5:
		for(int i=0;i<5;i++)
		{
			m_ImagePeople[i].LoadFromResource(AfxGetInstanceHandle(),IDB_HD50+i);
		}
		break;
	}

	UpdateShow();
}

void CGameTableToolDlg::OnCbnSelendokUserName()
{
	UpdateShow();
}

void CGameTableToolDlg::OnCbnSelendokCurrentSeat()
{
	int index=m_CurrentSeat.GetCurSel();
	m_CurrentChairID=index;

	//�޶����ƵĶ��뷽ʽ
	switch(m_nDrawStyle[m_CurrentChairID]&0x0F)
	{
	case NT_RIGHT:
		m_CurrentHAlignmet=2;
		break;
	case NT_CENTER:
		m_CurrentHAlignmet=1;
		break;
	case NT_LEFT:
		m_CurrentHAlignmet=0;
		break;
	}
	switch(m_nDrawStyle[m_CurrentChairID]&0xF0)
	{
	case NT_TOP:
		m_CurrentVAlignmet=0;
		break;
	case NT_VCENTER:
		m_CurrentVAlignmet=1;
		break;
	case NT_BOTTOM:
		m_CurrentVAlignmet=2;
		break;
	}
	UpdateData(false);

	UpdateShow();
}

void CGameTableToolDlg::OnBnClickedFourPixel()
{
	UpdateData(TRUE);
}
