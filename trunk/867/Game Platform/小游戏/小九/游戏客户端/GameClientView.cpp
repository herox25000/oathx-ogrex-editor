#include "StdAfx.h"
#include "Math.h"
#include "Resource.h"
#include "GameClientView.h"
#include "GameClientView.h"

//////////////////////////////////////////////////////////////////////////

//ʱ���ʶ
#define IDI_FLASH_WINNER			100									//������ʶ
#define IDI_SHOW_CHANGE_BANKER		101									//�ֻ�ׯ��
#define IDI_UNKNOWN_TIME			102									//

//��ť��ʶ
#define IDC_APPY_BANKER				206									//��ť��ʶ
#define IDC_CANCEL_BANKER			207									//��ť��ʶ
#define IDC_SCORE_MOVE_L			209									//��ť��ʶ
#define IDC_SCORE_MOVE_R			210									//��ť��ʶ
#define IDC_JETTON_BUTTON_50000		301									//��ť��ʶ
#define IDC_JETTON_BUTTON_1000		302									//��ť��ʶ
#define IDC_JETTON_BUTTON_10000		303									//��ť��ʶ
#define IDC_JETTON_BUTTON_100000	304									//��ť��ʶ
#define IDC_JETTON_BUTTON_500000	305									//��ť��ʶ
#define IDC_JETTON_BUTTON_1000000	306									//��ť��ʶ
#define IDC_JETTON_BUTTON_5000000	307									//��ť��ʶ
#define IDC_JETTON_BUTTON_10000000  308				
#define IDC_CUOPAI					215
#define IDC_MONEY					216
#define	IDC_SHENGYIN				217




//ׯ����Ϣ
#define BANKER_INFO_LEN				150									//ׯ����Ϣ


//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientView, CGameFrameView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_JETTON_BUTTON_500000, OnJettonButton500000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_1000000, OnJettonButton1000000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_5000000, OnJettonButton5000000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_10000000, OnJettonButton10000000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_1000, OnJettonButton1000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_10000, OnJettonButton10000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_100000, OnJettonButton100000)
	ON_BN_CLICKED(IDC_APPY_BANKER, OnApplyBanker)
	ON_BN_CLICKED(IDC_CANCEL_BANKER, OnCancelBanker)
	ON_BN_CLICKED(IDC_SCORE_MOVE_L, OnScoreMoveL)
	ON_BN_CLICKED(IDC_SCORE_MOVE_R, OnScoreMoveR)
	ON_BN_CLICKED(IDC_CUOPAI, OnCuoPaiModel)
	ON_BN_CLICKED(IDC_MONEY, OnBank)

	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


JettonButton::JettonButton() : m_nState(0)
{

}

JettonButton::~JettonButton()
{

}

void	JettonButton::Create(const CRect& rect, UINT uIDResource, HINSTANCE hResourceDLL)
{
	m_SkinRect	= rect;
	SetImageResource(uIDResource, hResourceDLL);
}

void	JettonButton::SetImageResource(UINT uIDResource, HINSTANCE hResourceDLL)
{
	m_SkinImage.SetLoadInfo(uIDResource, hResourceDLL);
}

void	JettonButton::SetState(int nState)
{
	m_nState = nState;
}

int		JettonButton::GetState() const
{
	return m_nState;
}

void	JettonButton::SetClientRect(const CRect& rect)
{
	m_SkinRect = rect;
}

CRect	JettonButton::GetClientRect() const
{
	return m_SkinRect;
}

void	JettonButton::Enabled(BOOL bEnabled)
{
	m_nState = bEnabled ? JBST_DISABLE : JBST_NORMAL;
}

void	JettonButton::Draw(CDC* pDC)
{
	CImageHandle skin(&m_SkinImage);

	int nDrawRectFlage = 0;
	switch( m_nState )
	{
	case JBST_NORMAL:
		nDrawRectFlage = 0;
		break;
	case JBST_OVER:
		nDrawRectFlage = 2;
		break;
	case JBST_PUSHDOWN:
		nDrawRectFlage = 1;
		break;
	case JBST_PUSHUP:
		nDrawRectFlage = 3;
		break;
	case JBST_DISABLE:
		nDrawRectFlage = 4;
		break;
	}

	m_SkinImage.AlphaDrawImage(pDC, m_SkinRect.left, m_SkinRect.top, m_SkinRect.right - m_SkinRect.left,
		m_SkinRect.bottom - m_SkinRect.top, nDrawRectFlage * (m_SkinRect.right - m_SkinRect.left), 0, RGB(255,0, 255));
}

//////////////////////////////////////////////////////////////////////////

//���캯��
CGameClientView::CGameClientView() : CGameFrameView(true,24)
{
	//״̬��Ϣ
	m_lCurrentJetton=0L;
	m_cbWinnerSide=0xFF;
	m_cbWinnerFlash=0xFF;
//	m_cbKingWinner=0xFF;
	m_wMeChairID=INVALID_CHAIR;
	m_cbPreJettonArea = 255;

	m_bShowGameResult = false;
	m_lMeCurGameScore=0L;			
	m_lMeCurGameReturnScore=0L;	
	m_lBankerCurGameScore=0L;		

	m_bDispatchCard = false;

	//��ע��Ϣ
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

	//λ����Ϣ
	m_nScoreHead = 0;
	m_nRecordFirst= 0;	
	m_nRecordLast= 0;	

	//��ʷ�ɼ�
	m_wDrawCount=0;
	m_lMeResultCount=0;

	//��ע��Ϣ
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;

	//ׯ����Ϣ
	m_bShowChangeBanker = false;
	m_wCurrentBankerChairID = INVALID_CHAIR;
	m_cbBankerTime = 0;			
	m_lBankerScore = 0;		
	m_lBankerTreasure=0;

	m_JettonButtonPushDown	= FALSE;


	//����λͼ
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_ImageViewFill.SetLoadInfo(IDB_VIEW_FILL,hInstance);
	m_ImageViewBack.SetLoadInfo(IDB_VIEW_BACK,hInstance);
	m_ImageWinFlags.SetLoadInfo(IDB_WIN_FLAGS,hInstance);
	m_ImageJettonView.SetLoadInfo(IDB_JETTOM_VIEW,hInstance);
	m_ImageScoreNumber.SetLoadInfo(IDB_SCORE_NUMBER,hInstance);
	m_ImageMeScoreNumber.SetLoadInfo(IDB_ME_SCORE_NUMBER,hInstance);

	m_ImageFrameXianJia.SetLoadInfo( IDB_FRAME_XIAN_JIA, hInstance );
	m_ImageFrameZhuangJia.SetLoadInfo( IDB_FRAME_ZHUANG_JIA, hInstance );
	m_ImageFrameXianTianWang.SetLoadInfo( IDB_FRAME_XIAN_TIAN_WANG, hInstance );
	m_ImageFrameZhuangTianWang.SetLoadInfo( IDB_FRAME_ZHUANG_TIAN_WANG, hInstance );
	m_ImageFramePingJia.SetLoadInfo( IDB_FRAME_PING_JIA, hInstance );
	m_ImageFrameTongDianPing.SetLoadInfo( IDB_FRAME_TONG_DIAN_PING, hInstance );

	m_ImageFrameXianJia1.SetLoadInfo( IDB_FRAME_XIAN_JIA1, hInstance );
	m_ImageFrameZhuangJia1.SetLoadInfo( IDB_FRAME_ZHUANG_JIA1, hInstance );
	m_ImageFrameXianTianWang1.SetLoadInfo( IDB_FRAME_XIAN_TIAN_WANG1, hInstance );
	m_ImageFrameZhuangTianWang1.SetLoadInfo( IDB_FRAME_ZHUANG_TIAN_WANG1, hInstance );
	m_ImageFramePingJia1.SetLoadInfo( IDB_FRAME_PING_JIA1, hInstance );
	m_ImageFrameTongDianPing1.SetLoadInfo( IDB_FRAME_TONG_DIAN_PING1, hInstance );

	m_ImageGameEnd.SetLoadInfo( IDB_GAME_END, hInstance );
	//m_ImageGameEndFrame.SetLoadInfo( IDB_GAME_END_FRAME, hInstance );
	m_ImageGamePoint.SetLoadInfo( IDB_GAME_POINT, hInstance );
	m_ImageCard.SetLoadInfo(IDB_GAME_CARD,hInstance);

	m_ImageMeBanker.SetLoadInfo( IDB_ME_BANKER, hInstance );
	m_ImageChangeBanker.SetLoadInfo( IDB_CHANGE_BANKER, hInstance );
	m_ImageNoBanker.SetLoadInfo( IDB_NO_BANKER, hInstance );	

	m_ImageTimeFlag.SetLoadInfo(IDB_TIME_FLAG, hInstance);

	char szPath[MAX_PATH];
	::GetModulePath(szPath, sizeof(szPath));
	CString str;
	str.Format(TEXT("%s\\Resource\\Games\\XiaoJiu\\RES\\PNG_IDB_IDB_TIPC_PNG.png"),szPath);
	m_pngc.LoadImage(str);
	str.Format(TEXT("%s\\Resource\\Games\\XiaoJiu\\RES\\PNG_IDB_IDB_TIPP_PNG.png"),szPath);
	m_pngp.LoadImage(str);


	UINT IDBT_JETTON[]=
	{
		IDB_BT_JETTON_1000, 
		IDB_BT_JETTON_10000,
		IDB_BT_JETTON_100000,
		IDB_BT_JETTON_500000,
		IDB_BT_JETTON_1000000,
		IDB_BT_JETTON_5000000,
		IDB_BT_JETTON_10000000,
	};

	int x = 300;
	int y = 530;
	for (int i=0; i<7; i++)
	{
		int dx = x + i * JETTON_WIDTH;
		m_JettonButton[i].Create(CRect(dx, y, dx + JETTON_WIDTH, y + JETTON_HEIGHT), IDBT_JETTON[i], hInstance);
	}
	
	GetMaxTieScore();
	m_bCanGo=false;
	m_bSet=false;
	m_bAutoCard=true;
	m_bJettonstate=true;
	m_fWinCount[0]=0.00f;
	m_fWinCount[1]=0.00f;
	m_fWinCount[2]=0.00f;

	return;
}

//��������
CGameClientView::~CGameClientView(void)
{
}

//������Ϣ
int CGameClientView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	//�����ؼ�
	CRect rcCreate(0,0,0,0);
	m_GameRecord.Create(IDD_DLG_GAME_RECORD,this);
	m_ApplyUser.Create( IDD_DLG_GAME_RECORD	, this );
	m_GameRecord.ShowWindow(SW_HIDE);
	
	m_DrawCard[4].SetPreCard(true);

	//������ť

	//m_btJetton1000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_1000);
	//m_btJetton10000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_10000);
	//m_btJetton100000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_100000);
	//m_btJetton500000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_500000);	
	//m_btJetton1000000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_1000000);
	//m_btJetton5000000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_5000000);
	//m_btJetton10000000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_10000000);
	m_btApplyBanker.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_APPY_BANKER);
	m_btCancelBanker.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_CANCEL_BANKER);
	m_btApplyBanker.ShowWindow(SW_SHOW);
	m_btApplyBanker.EnableWindow(FALSE);
	m_btCancelBanker.ShowWindow(SW_HIDE);
	m_btScoreMoveL.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_SCORE_MOVE_L);
	m_btScoreMoveR.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_SCORE_MOVE_R);
	m_btnZiDongCuoPai.Create(NULL,WS_CHILD,rcCreate,this,IDC_CUOPAI);
	m_btnShouDongCuoPai.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_CUOPAI);
	m_btnShengyin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SHENGYIN);
	m_btnNoShengyin.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_SHENGYIN);
	m_btnQuqian.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MONEY);
	m_btnCunqian.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_MONEY);

	//���ð�ť
	HINSTANCE hResInstance=AfxGetInstanceHandle();

	//m_btJetton1000.SetButtonImage(IDB_BT_JETTON_1000,hResInstance,false);
	//m_btJetton10000.SetButtonImage(IDB_BT_JETTON_10000,hResInstance,false);
	//m_btJetton100000.SetButtonImage(IDB_BT_JETTON_100000,hResInstance,false);
	//m_btJetton500000.SetButtonImage(IDB_BT_JETTON_500000,hResInstance,false);
	//m_btJetton1000000.SetButtonImage(IDB_BT_JETTON_1000000,hResInstance,false);	
	//m_btJetton5000000.SetButtonImage(IDB_BT_JETTON_5000000,hResInstance,false);
	//m_btJetton10000000.SetButtonImage(IDB_BT_JETTON_10000000,hResInstance,false);
	m_btApplyBanker.SetButtonImage(IDB_BT_APPLY_BANKER,hResInstance,false);
	m_btCancelBanker.SetButtonImage(IDB_BT_CANCEL_APPLY,hResInstance,false);
	m_btScoreMoveL.SetButtonImage(IDB_BT_SCORE_MOVE_L,hResInstance,false);
	m_btScoreMoveR.SetButtonImage(IDB_BT_SCORE_MOVE_R,hResInstance,false);
	m_btnZiDongCuoPai.SetButtonImage(IDB_ZiDONGCUOPAI,hResInstance,false);
	m_btnShouDongCuoPai.SetButtonImage(IDB_SHOUDONDCUOPAI,hResInstance,false);
	m_btnShengyin.SetButtonImage(IDB_BT_SHENGYIN,hResInstance,false);
	m_btnNoShengyin.SetButtonImage(IDB_BT_NOSHENGYIN,hResInstance,false);
	m_btnQuqian.SetButtonImage(IDB_BT_QUQIAN,hResInstance,false);
	m_btnCunqian.SetButtonImage(IDB_BT_CUNQIAN,hResInstance,false);
		

	return 0;
}

//���ý���
void CGameClientView::ResetGameView()
{
	//ׯ����Ϣ
	m_bShowChangeBanker = false;
	m_wCurrentBankerChairID = INVALID_CHAIR;
	m_cbBankerTime = 0;
	m_lBankerScore = 0;	
	m_lMeMaxScore=0L;
	m_lMeTianMenScore=0L;
	m_lMeDaoMenScore=0L;
	m_lMeShunMenScore=0L;
	m_lMeQiaoScore=0L;
	m_lMeZuoJiaoScore=0L;
	m_lMeYouJiaoScore=0L;


	m_bShowGameResult = false;
	m_lMeCurGameScore=0L;			
	m_lMeCurGameReturnScore=0L;	
	m_lBankerCurGameScore=0L;
	m_nScoreHead = 0;
	m_nRecordFirst= 0;	
	m_nRecordLast= 0;	
	m_lBankerTreasure=0;

	m_bDispatchCard = false;
	m_strDispatchCardTips=TEXT("");

	//��ע��Ϣ
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;	

	//����б�
	m_ApplyUser.ClearAll();

	//���ð�ť
	m_btApplyBanker.ShowWindow(SW_SHOW);
	m_btApplyBanker.EnableWindow(FALSE);
	m_btCancelBanker.ShowWindow(SW_HIDE);
	m_btCancelBanker.SetButtonImage(IDB_BT_CANCEL_APPLY,AfxGetInstanceHandle(),false);
	return;
}

//�����ؼ�
void CGameClientView::RectifyGameView(int nWidth, int nHeight)
{
	//λ����Ϣ
	m_nWinFlagsExcursionX = nWidth/2-205;	
	m_nWinFlagsExcursionY = nHeight/2 + 241;
	m_nWinPointsExcursionX = nWidth/2-353;
	m_nWinPointsExcursionY = nHeight/2 - 267;	

	m_PointJetton[0].SetPoint(nWidth / 2 - 145-120 ,nHeight / 2 - 120);
	m_PointJetton[1].SetPoint(nWidth / 2 - 20,nHeight / 2 - 50);
	m_PointJetton[2].SetPoint(nWidth / 2 +140+90,nHeight / 2 - 120);

	//�˿˿ؼ�
	m_DrawCard[0].Init(this,nWidth/2-35,nHeight/2-235-100);
	m_DrawCard[1].Init(this,nWidth/2+25-15-370,nHeight/2-235+80);
	m_DrawCard[2].Init(this,nWidth/2-35,nHeight/2-235+300);
	m_DrawCard[3].Init(this,nWidth/2+25-15+260,nHeight/2-235+80);
	m_DrawCard[4].Init(this,nWidth/2-35,nHeight/2-125);

	//�ƶ��ؼ�
	HDWP hDwp=BeginDeferWindowPos(32);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS;
	//�б�ؼ�
	DeferWindowPos(hDwp,m_ApplyUser,NULL,nWidth/2 + 138,nHeight/2-300,220,52,uFlags);
	//���밴ť
	CRect rcJetton;
	//m_btJetton10000000.GetWindowRect(&rcJetton);
	int nXPos = nWidth/2-220;
	int nYPos = nHeight/2+170;
	int nSpace = 2;
	//DeferWindowPos(hDwp,m_btJetton1000,HWND_BOTTOM,nXPos,nYPos,0,0,uFlags|SWP_NOSIZE);
	//DeferWindowPos(hDwp,m_btJetton10000,HWND_BOTTOM,nXPos + nSpace + rcJetton.Width(),nYPos,0,0,uFlags|SWP_NOSIZE);
	//DeferWindowPos(hDwp,m_btJetton100000,HWND_BOTTOM,nXPos + (nSpace + rcJetton.Width()) * 2,nYPos,0,0,uFlags|SWP_NOSIZE);
	//DeferWindowPos(hDwp,m_btJetton500000,HWND_BOTTOM,nXPos + (nSpace + rcJetton.Width()) * 3,nYPos,0,0,uFlags|SWP_NOSIZE);
	//DeferWindowPos(hDwp,m_btJetton1000000,HWND_BOTTOM,nXPos + (nSpace + rcJetton.Width()) * 4,nYPos,0,0,uFlags|SWP_NOSIZE);
	//DeferWindowPos(hDwp,m_btJetton5000000,HWND_BOTTOM,nXPos + (nSpace + rcJetton.Width()) * 5,nYPos,0,0,uFlags|SWP_NOSIZE);
	//DeferWindowPos(hDwp,m_btJetton10000000,HWND_BOTTOM,nXPos + (nSpace + rcJetton.Width()) * 6,nYPos,0,0,uFlags|SWP_NOSIZE);
	//��ׯ��ť
	DeferWindowPos(hDwp,m_btApplyBanker,NULL,nWidth/2+273,nHeight/2-340,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btCancelBanker,NULL,nWidth/2+273,nHeight/2-340,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btScoreMoveL,NULL,nWidth/2-237,nHeight/2+272-30,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btScoreMoveR,NULL,nWidth/2+337,nHeight/2+272-30,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btnZiDongCuoPai,NULL,nWidth/2+210,nHeight/2+160,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btnShouDongCuoPai,NULL,nWidth/2+210,nHeight/2+160,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btnShengyin,NULL,nWidth/2+290,nHeight/2+160,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btnNoShengyin,NULL,nWidth/2+290,nHeight/2+160,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btnQuqian,NULL,nWidth/2+210,nHeight/2+195,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btnCunqian,NULL,nWidth/2+290,nHeight/2+195,0,0,uFlags|SWP_NOSIZE);
	m_btnCunqian.EnableWindow(FALSE);
	//�����ƶ�
	EndDeferWindowPos(hDwp);

	return;
}

//�滭����
void CGameClientView::DrawGameView(CDC * pDC, int nWidth, int nHeight)
{
	//�滭����
	DrawViewImage(pDC,m_ImageViewFill,enMode_Spread);
	DrawViewImage(pDC,m_ImageViewBack,enMode_Centent);

	//ʤ����־
	DrawWinFlags(pDC);

	//�滭�߿�
	int nXPos=0, nYPos=0;
	if ( m_lCurrentJetton == 0 ) m_cbPreJettonArea = 255;
	switch ( m_cbPreJettonArea )
	{
	case ID_SHUN_MEN:
		{
			CImageHandle ImageHandleXianJia(&m_ImageFrameXianJia);
			nXPos = nWidth / 2 - 145-200;
			nYPos = nHeight / 2 - 230;
			m_ImageFrameXianJia.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
			break;
		}
	case ID_TIAN_MEN:
		{
			CImageHandle ImageHandlePingJia(&m_ImageFramePingJia);
			nXPos = nWidth / 2 - 145;
			nYPos = nHeight / 2 - 135;
			m_ImageFramePingJia.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
			break;
		}
	case ID_DAO_MEN:
		{
			CImageHandle ImageHandleZhuangJia(&m_ImageFrameZhuangJia);
			nXPos = nWidth / 2 +140;
			nYPos = nHeight / 2 - 230;
			m_ImageFrameZhuangJia.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
			break;
		}
	}

	//ʤ����־
	if (m_cbWinnerFlash!=0xFF)
	{
		//������Դ
		CImageHandle HandleWinFlags(&m_ImageWinFlags);
		CSize SizeWinFlags(m_ImageWinFlags.GetWidth()/3,m_ImageWinFlags.GetHeight());

		//�мұ�־
		if(m_cbWinnerFlash & ID_SHUN_MEN)
		{
			CImageHandle ImageHandleXianJia(&m_ImageFrameXianJia);
			nXPos = nWidth / 2 - 145-200;
			nYPos = nHeight / 2 - 230;
			m_ImageFrameXianJia.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
		}
		if(m_cbWinnerFlash & ID_TIAN_MEN)
		{
			CImageHandle ImageHandlePingJia(&m_ImageFramePingJia);
			nXPos = nWidth / 2 - 145;
			nYPos = nHeight / 2 - 135;
			m_ImageFramePingJia.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
		}
		if(m_cbWinnerFlash & ID_DAO_MEN)
		{
			CImageHandle ImageHandleZhuangJia(&m_ImageFrameZhuangJia);
			nXPos = nWidth / 2 +140;
			nYPos = nHeight / 2 - 230;
			m_ImageFrameZhuangJia.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));				
		}
		if(!(m_cbWinnerFlash & ID_SHUN_MEN) && !(m_cbWinnerFlash & ID_TIAN_MEN) && !(m_cbWinnerFlash & ID_DAO_MEN))
		{
			CImageHandle ImageHandleXianJia1(&m_ImageFrameXianJia1);
			nXPos = nWidth / 2 - 145-200;
			nYPos = nHeight / 2 - 230;
			m_ImageFrameXianJia1.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
			CImageHandle ImageHandlePingJia1(&m_ImageFramePingJia1);
			nXPos = nWidth / 2 - 145;
			nYPos = nHeight / 2 - 135;
			m_ImageFramePingJia1.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
			CImageHandle ImageHandleZhuangJia1(&m_ImageFrameZhuangJia1);
			nXPos = nWidth / 2 +140;
			nYPos = nHeight / 2 - 230;
			m_ImageFrameZhuangJia1.AlphaDrawImage(pDC,nXPos, nYPos , RGB(255,0,255));
		}
	}

	//�л�ׯ��
	if ( m_bShowChangeBanker )
	{
		int	nXPos = nWidth / 2 - 120;
		int	nYPos = nHeight / 2 - 160;

		//������ׯ
		if ( m_wMeChairID == m_wCurrentBankerChairID )
		{
			CImageHandle ImageHandleBanker(&m_ImageMeBanker);
			m_ImageMeBanker.AlphaDrawImage(pDC, nXPos, nYPos,RGB(255,0,255));
		}
		else if ( m_wCurrentBankerChairID != INVALID_CHAIR )
		{
			CImageHandle ImageHandleBanker(&m_ImageChangeBanker);
			m_ImageChangeBanker.AlphaDrawImage(pDC, nXPos, nYPos,RGB(255,0,255));
		}
		else
		{
			CImageHandle ImageHandleBanker(&m_ImageNoBanker);
			m_ImageNoBanker.AlphaDrawImage(pDC, nXPos, nYPos,RGB(255,0,255));
		}
	}
	//ׯ����Ϣ																											
	pDC->SetTextColor(RGB(255,234,0));
	if ( m_wCurrentBankerChairID != INVALID_CHAIR )
	{
		//��ȡ���
		tagUserData const *pUserData = GetUserInfo( m_wCurrentBankerChairID );
		if ( pUserData )
		{
			//λ����Ϣ
			CRect StrRect;
			StrRect.left = nWidth/2-295;
			StrRect.top = nHeight/2 - 328;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;
			//ׯ������
			pDC->DrawText( pUserData->szName, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
			//ׯ���ܷ�
			StrRect.left = nWidth/2-295;
			StrRect.top = nHeight/2 - 309;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;
			pDC->DrawText( ChangNumber(pUserData->lScore), StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
			//ׯ�ҳɼ�
			StrRect.left = nWidth/2-295;
			StrRect.top = nHeight/2 - 287;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;
			pDC->DrawText( ChangNumber(m_lBankerScore), StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
			//ׯ�Ҿ���
			StrRect.left = nWidth/2-295;
			StrRect.top = nHeight/2 - 266;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;
			pDC->DrawText( ChangNumber(m_cbBankerTime), StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

		}
	}
	else
	{
		//λ����Ϣ
		CRect StrRect;
		StrRect.left = nWidth/2-295;
		StrRect.top = nHeight/2 - 328;//337;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;
		//ׯ������
		pDC->DrawText( TEXT("������ׯ"), StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
		//ׯ�Ҿ���
		StrRect.left = nWidth/2-295;
		StrRect.top = nHeight/2 - 310;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;
		pDC->DrawText( "......", StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
		//ׯ�ҳɼ�
		StrRect.left = nWidth/2-295;
		StrRect.top = nHeight/2 - 291;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;
		pDC->DrawText( "......", StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
		//ׯ�ҳɼ�
		StrRect.left = nWidth/2-295;
		StrRect.top = nHeight/2 - 270;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;
		pDC->DrawText( "......", StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
	}

	//������Դ
	CImageHandle HandleJettonView(&m_ImageJettonView);
	CSize SizeJettonItem(m_ImageJettonView.GetWidth()/JETTON_COUNT,m_ImageJettonView.GetHeight());

	// ������ҵ���ע�ܺ�
	__int64	uAllScoreCount = 0;

	//�滭����
	for (INT i=0;i<3;i++)
	{
		//��������
		__int64 lScoreCount=0L;
		__int64 lScoreJetton[JETTON_COUNT]={1000L,10000L,100000L,500000L,1000000L,5000000L,10000000L};
		//�滭����
		for (INT_PTR j=0;j<m_JettonInfoArray[i].GetCount();j++)
		{
			//��ȡ��Ϣ
			tagJettonInfo * pJettonInfo=&m_JettonInfoArray[i][j];

			//�ۼ�����
			ASSERT(pJettonInfo->cbJettonIndex<JETTON_COUNT);
			lScoreCount+=lScoreJetton[pJettonInfo->cbJettonIndex];

			//�滭����
			m_ImageJettonView.AlphaDrawImage(pDC,pJettonInfo->nXPos+m_PointJetton[i].x-SizeJettonItem.cx/2-30,
				pJettonInfo->nYPos+m_PointJetton[i].y-SizeJettonItem.cy/2,SizeJettonItem.cx,SizeJettonItem.cy,
				pJettonInfo->cbJettonIndex*SizeJettonItem.cx,0,RGB(255,0,255));
		}
		//�滭����
		if (lScoreCount>0L)
			DrawNumberString(pDC,lScoreCount,m_PointJetton[i].x,m_PointJetton[i].y);

		uAllScoreCount += lScoreCount;
	}

	//�ҵ���ע
	DrawMeJettonNumber(pDC);
	//��ʾ���
	ShowGameResult(pDC, nWidth, nHeight);	
	//�滭ʱ��
	if (m_wMeChairID!=INVALID_CHAIR)
	{
		WORD wUserTimer=GetUserTimer(m_wMeChairID);
		if (wUserTimer!=0)
			DrawUserTimer(pDC,nWidth/2-110,50,wUserTimer);
	}
	//���ƽ׶�(ʱ���������)
	bool bDispatchCard = (0< m_DrawCard[4].GetCardCount() || 0 < m_DrawCard[0].GetCardCount() || 0 < m_DrawCard[1].GetCardCount() || m_DrawCard[2].GetCardCount() || m_DrawCard[3].GetCardCount()) ? true : false;
	CImageHandle ImageHandleTimeFlag(&m_ImageTimeFlag);
	int nTimeFlagWidth = m_ImageTimeFlag.GetWidth()/3;
	if ( bDispatchCard ) 
		m_ImageTimeFlag.AlphaDrawImage(pDC,nWidth/2-140, 80, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), 2 * nTimeFlagWidth, 0,RGB(255,0,255));
	else if ( m_wCurrentBankerChairID != INVALID_CHAIR )
		m_ImageTimeFlag.AlphaDrawImage(pDC, nWidth/2-140, 80, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), nTimeFlagWidth, 0,RGB(255,0,255));
	else 
		m_ImageTimeFlag.AlphaDrawImage(pDC, nWidth/2-140, 80, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), 0, 0,RGB(255,0,255));


	//�滭�û�
	if (m_wMeChairID!=INVALID_CHAIR)
	{
		const tagUserData *pMeUserData = GetUserInfo(m_wMeChairID);
		if ( pMeUserData != NULL )
		{
			////��Ϸ��Ϣ
			pDC->SetTextColor(RGB(255,234,0));
			__int64 lMeJetton = m_lMeTianMenScore+m_lMeDaoMenScore+m_lMeShunMenScore+m_lMeQiaoScore+m_lMeZuoJiaoScore+m_lMeYouJiaoScore;
			CRect rcAccount(CPoint(nWidth/2-380+70,nHeight/2+370-203),CPoint(nWidth/2-380+70+200,nHeight/2+370-203+15));
			CRect rcGameScore(CPoint(nWidth/2-380+70,nHeight/2+370-185),CPoint(nWidth/2-380+70+200,nHeight/2+370-185+15));
			CRect rcResultScore(CPoint(nWidth/2-380+70,nHeight/2+370-167),CPoint(nWidth/2-380+70+200,nHeight/2+370-167+15));
			pDC->DrawText(pMeUserData->szName,lstrlen(pMeUserData->szName),rcAccount,DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE);
			pDC->DrawText(ChangNumber(pMeUserData->lScore-lMeJetton),rcGameScore,DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE);
			pDC->DrawText(ChangNumber(m_lMeResultCount),rcResultScore,DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE);
		}
	}

	// �������ע״̬
	if(m_bJettonstate )
	{
		//������ע������
		int iStatrX=nWidth/2-130;
		int iStatrY=nHeight/2-230;
		//��ǰ����
		m_pngc.DrawImage(pDC,iStatrX-10,iStatrY,m_pngc.GetWidth(),m_pngc.GetHeight()/2,0,0);
		//��ǰ��ע
		m_pngc.DrawImage(pDC,iStatrX-10,iStatrY+42,m_pngc.GetWidth(),m_pngc.GetHeight()/2,0,m_pngc.GetHeight()/2);
		//������
		m_pngp.DrawImage(pDC,iStatrX,iStatrY+15,m_pngp.GetWidth(),m_pngp.GetHeight()/2,0,0,m_pngp.GetWidth(),m_pngp.GetHeight()/2);
		
		const tagUserData* pBankerInfo = GetUserInfo(m_wCurrentBankerChairID);
		if (pBankerInfo)
		{
			__int64 uCurrntReamtionScore = pBankerInfo->lScore - uAllScoreCount;			
			float fProportion	= uCurrntReamtionScore*1.0f / pBankerInfo->lScore;
			int nOffset			= floor(m_pngp.GetWidth()*fProportion);
			m_pngp.DrawImage(pDC,iStatrX,iStatrY+15,nOffset,m_pngp.GetHeight()/2,0,m_pngp.GetHeight()/2,nOffset,m_pngp.GetHeight()/2);
			//����ע
			DrawNumberString(pDC, uCurrntReamtionScore, nWidth/2,iStatrY+10,true);
			//�Ѿ���ע
			DrawNumberString(pDC, uAllScoreCount, nWidth/2,iStatrY+60,true);
		}
	}

	for (int i=0; i<7; i++)
	{
		m_JettonButton[i].Draw(pDC);
	}
	

	//������
	for(int i=0;i<5;i++)
	{
		m_DrawCard[i].Draw(pDC);
	}

	return;
}

//������Ϣ
void CGameClientView::SetMeMaxScore(__int64 lMeMaxScore)
{
	if (m_lMeMaxScore!=lMeMaxScore)
	{
		//���ñ���
		m_lMeMaxScore=lMeMaxScore;

		//���½���
		UpdateGameView(NULL);
	}

	return;
}


//������Ϣ
void CGameClientView::SetMeTieScore(__int64 lMeTieScore)
{
	if (m_lMeTianMenScore!=lMeTieScore)
	{
		//���ñ���
		m_lMeTianMenScore=lMeTieScore;

		//���½���
		UpdateGameView(NULL);
	}

	return;
}

//������Ϣ
void CGameClientView::SetMeBankerScore(__int64 lMeBankerScore)
{
	if (m_lMeDaoMenScore!=lMeBankerScore)
	{
		//���ñ���
		m_lMeDaoMenScore=lMeBankerScore;

		//���½���
		UpdateGameView(NULL);
	}

	return;
}

//������Ϣ
void CGameClientView::SetMePlayerScore(__int64 lMePlayerScore)
{
	if (m_lMeShunMenScore!=lMePlayerScore)
	{
		//���ñ���
		m_lMeShunMenScore=lMePlayerScore;
		//���½���
		UpdateGameView(NULL);
	}

	return;
}

//������Ϣ
void CGameClientView::SetMePlayerKingScore(__int64 lMePlayerKingScore)
{
	if (m_lMeZuoJiaoScore!=lMePlayerKingScore)
	{
		//���ñ���
		m_lMeZuoJiaoScore=lMePlayerKingScore;

		//���½���
		UpdateGameView(NULL);
	}
}
//������Ϣ
void CGameClientView::SetMeBankerKingScore(__int64 lMeBankerKingScore)
{
	if (m_lMeYouJiaoScore!=lMeBankerKingScore)
	{
		//���ñ���
		m_lMeYouJiaoScore=lMeBankerKingScore;

		//���½���
		UpdateGameView(NULL);
	}
}
//������Ϣ
void CGameClientView::SetMeTieSamePointScore(__int64 lMeTieSamePointScore)
{
	if (m_lMeQiaoScore!=lMeTieSamePointScore)
	{
		//���ñ���
		m_lMeQiaoScore=lMeTieSamePointScore;

		//���½���
		UpdateGameView(NULL);
	}
}

//���ó���
void CGameClientView::SetCurrentJetton(__int64 lCurrentJetton)
{
	//���ñ���
	ASSERT(lCurrentJetton>=0L);
	m_lCurrentJetton=lCurrentJetton;

	return;
}


//��ʷ��¼
void CGameClientView::SetGameHistory(enOperateResult OperateResult, BYTE cbPlayerCount, BYTE cbBankerCount,WORD wWinnerSide)
{
	//��������
	tagClientGameRecord &GameRecord = m_GameRecordArrary[m_nRecordLast];
	GameRecord.enOperateFlags = OperateResult;
	GameRecord.cbPlayerCount = cbPlayerCount;
	GameRecord.cbBankerCount = cbBankerCount;
	GameRecord.wWinner=wWinnerSide;
	GameRecord.lMeDaoMenScore=m_lMeDaoMenScore;
	GameRecord.lMeQiaoScore=m_lMeQiaoScore;
	GameRecord.lMeShunMenScore=m_lMeShunMenScore;
	GameRecord.lMeTianMenScore=m_lMeTianMenScore;
	GameRecord.lMeYouJiaoScore=m_lMeYouJiaoScore;
	GameRecord.lMeZuoJiaoScore=m_lMeZuoJiaoScore;

	//�ƶ��±�
	m_nRecordLast = (m_nRecordLast+1) % MAX_SCORE_HISTORY;
	if ( m_nRecordLast == m_nRecordFirst )
	{
		m_nRecordFirst = (m_nRecordFirst+1) % MAX_SCORE_HISTORY;
		if ( m_nScoreHead < m_nRecordFirst ) m_nScoreHead = m_nRecordFirst;
	}

	int nHistoryCount = (m_nRecordLast - m_nRecordFirst + MAX_SCORE_HISTORY) % MAX_SCORE_HISTORY;
	if ( 14 < nHistoryCount )
		m_btScoreMoveR.EnableWindow(TRUE);

	//�Ƶ����¼�¼
	if ( 14 < nHistoryCount )
	{
		m_nScoreHead = (m_nRecordLast - 14 + MAX_SCORE_HISTORY) % MAX_SCORE_HISTORY;
		m_btScoreMoveL.EnableWindow(TRUE);
		m_btScoreMoveR.EnableWindow(FALSE);
	}

	//���½���
	UpdateGameView(NULL);

	return;
}

//��ʷ�ɼ�
void CGameClientView::SetHistoryScore(WORD wDrawCount,__int64 lMeResultCount)
{
	//���ñ���
	m_wDrawCount=wDrawCount;
	m_lMeResultCount=lMeResultCount;

	//���½���
	UpdateGameView(NULL);

	return;
}

//�������
void CGameClientView::CleanUserJetton()
{
	//��������
	for (BYTE i=0;i<CountArray(m_JettonInfoArray);i++)
	{
		m_JettonInfoArray[i].RemoveAll();
	}

	//��ע��Ϣ
	m_lAllTieScore=0L;			
	m_lAllBankerScore=0L;		
	m_lAllPlayerScore=0L;		
	m_lAllTieSamePointScore=0L;
	m_lAllBankerKingScore=0L;	
	m_lAllPlayerKingScore=0L;

	//���½���
	UpdateGameView(NULL);

	return;
}

//���ó���
void CGameClientView::PlaceUserJetton(BYTE cbViewIndex, __int64 lScoreCount)
{
	//Ч�����
	ASSERT(cbViewIndex<=ID_DAO_MEN);
	if (cbViewIndex>ID_DAO_MEN) return;

	//��������
	bool bPlaceJetton=false;
	__int64 lScoreIndex[JETTON_COUNT]={1000L,10000L,100000L,500000L,1000000L,5000000L,10000000L};

	//�߿���
	int nFrameWidth = 120, nFrameHeight = 150;

	switch ( cbViewIndex )
	{
	case ID_SHUN_MEN:
		{ 
			m_lAllPlayerScore += lScoreCount;
			break;
		}
	case ID_TIAN_MEN:
		{
			m_lAllTieScore += lScoreCount;
			break;
		}
	case ID_DAO_MEN:
		{ 
			m_lAllBankerScore += lScoreCount;
			break;
		}
	}

	//���ӳ���
	for (BYTE i=0;i<CountArray(lScoreIndex);i++)
	{
		//������Ŀ
		BYTE cbScoreIndex=JETTON_COUNT-i-1;
		__int64 lCellCount=lScoreCount/lScoreIndex[cbScoreIndex];

		//�������
		if (lCellCount==0L) continue;

		//�������
		for (LONG j=0;j<lCellCount;j++)
		{
			//����λ��
			INT nXPos=rand()%JETTON_RADII;
			INT nYPos=(INT)sqrt((FLOAT)(rand()%(JETTON_RADII*JETTON_RADII-nXPos*nXPos)));

			//�������
			tagJettonInfo JettonInfo;
			JettonInfo.cbJettonIndex=cbScoreIndex;
			JettonInfo.nXPos=rand()%(nFrameWidth);
			JettonInfo.nYPos=rand()%(nFrameHeight);

			int nIndex=0;
			switch(cbViewIndex)
			{
			case ID_SHUN_MEN:
				nIndex=1;
				break;
			case ID_TIAN_MEN:
				nIndex=2;
				break;
			case ID_DAO_MEN:
				nIndex=3;
				break;
			}
			//��������
			bPlaceJetton=true;
			m_JettonInfoArray[nIndex-1].Add(JettonInfo);
		}
		//������Ŀ
		lScoreCount-=lCellCount*lScoreIndex[cbScoreIndex];
	}
	//���½���
	if (bPlaceJetton==true)
		UpdateGameView(NULL);

	return;
}

//����ʤ��
void CGameClientView::SetWinnerSide(LPCTSTR pszGameResult, WORD cbWinnerSide)
{
	//���ñ���
	m_cbWinnerSide=cbWinnerSide;
	m_cbWinnerFlash=cbWinnerSide;
	m_strGameCardResult=pszGameResult;

	//����ʱ��
	if (cbWinnerSide!=0xFF)
	{
		SetTimer(IDI_FLASH_WINNER,500,NULL);
	}
	else 
		KillTimer(IDI_FLASH_WINNER);

	//���½���
	UpdateGameView(NULL);

	return;
}

//��ȡ����
BYTE CGameClientView::GetJettonArea(CPoint MousePoint)
{
	//��ȡ��С
	CRect rcClient ;
	GetClientRect(rcClient);

	int nWidth = rcClient.Width();
	int nHeight = rcClient.Height();

	// ˳��
	CRect rcXianJia;
	rcXianJia.left = nWidth / 2 - 145-200;
	rcXianJia.top = nHeight / 2 - 230;
	rcXianJia.right = rcXianJia.left + 200;
	rcXianJia.bottom = rcXianJia.top + 300;
	if ( rcXianJia.PtInRect(MousePoint) ) return ID_SHUN_MEN;
	
	//����
	CRect rcPingJia;
	rcPingJia.left = nWidth / 2  - 145;
	rcPingJia.top = nHeight / 2 - 135;
	rcPingJia.right = rcPingJia.left + 285;
	rcPingJia.bottom = rcPingJia.top + 260;
	if ( rcPingJia.PtInRect(MousePoint) ) return ID_TIAN_MEN;

	//����
	CRect rcZhuangJia;
	rcZhuangJia.left = nWidth / 2 +140;
	rcZhuangJia.top = nHeight / 2 - 230;
	rcZhuangJia.right = rcZhuangJia.left + 200;
	rcZhuangJia.bottom = rcZhuangJia.top + 300;
	if ( rcZhuangJia.PtInRect(MousePoint) ) return ID_DAO_MEN;
	return 0xFF;
}

//�滭����
void CGameClientView::DrawNumberString(CDC * pDC, __int64 lNumber, INT nXPos, INT nYPos, bool bMeScore)
{
	//������Դ
	CImageHandle HandleScoreNumber(&m_ImageScoreNumber);
	CImageHandle HandleMeScoreNumber(&m_ImageMeScoreNumber);
	CSize SizeScoreNumber(m_ImageScoreNumber.GetWidth()/10,m_ImageScoreNumber.GetHeight());

	if ( bMeScore )
		SizeScoreNumber.SetSize(m_ImageMeScoreNumber.GetWidth()/10, m_ImageMeScoreNumber.GetHeight());

	//������Ŀ
	LONG lNumberCount=0;
	__int64 lNumberTemp=lNumber;
	do
	{
		lNumberCount++;
		lNumberTemp/=10;
	} while (lNumberTemp>0);

	//λ�ö���
	INT nYDrawPos=nYPos-SizeScoreNumber.cy/2;
	INT nXDrawPos=nXPos+lNumberCount*SizeScoreNumber.cx/2-SizeScoreNumber.cx;

	//�滭����
	for (LONG i=0;i<lNumberCount;i++)
	{
		//�滭����
		LONG lCellNumber=(LONG)(lNumber%10);
		if ( bMeScore )
		{
			m_ImageMeScoreNumber.AlphaDrawImage(pDC,nXDrawPos,nYDrawPos,SizeScoreNumber.cx,SizeScoreNumber.cy,
				lCellNumber*SizeScoreNumber.cx,0,RGB(255,0,255));
		}
		else
		{
			m_ImageScoreNumber.AlphaDrawImage(pDC,nXDrawPos,nYDrawPos,SizeScoreNumber.cx,SizeScoreNumber.cy,
				lCellNumber*SizeScoreNumber.cx,0,RGB(255,0,255));
		}

		//���ñ���
		lNumber/=10;
		nXDrawPos-=SizeScoreNumber.cx;
	};

	return;
}

//���밴ť
void CGameClientView::OnJettonButton500000()
{
	//���ñ���
	m_lCurrentJetton=500000L;

	return;
}
void CGameClientView::OnJettonButton1000000()
{
	//���ñ���
	m_lCurrentJetton=1000000L;

	return;
}
void CGameClientView::OnJettonButton5000000()
{
	//���ñ���
	m_lCurrentJetton=5000000L;

	return;
}
//���밴ť
void CGameClientView::OnJettonButton10000000()
{
	//���ñ���
	m_lCurrentJetton=10000000L;
	return;
}

//���밴ť
void CGameClientView::OnJettonButton1000()
{
	//���ñ���
	m_lCurrentJetton=1000L;

	return;
}

//���밴ť
void CGameClientView::OnJettonButton10000()
{
	//���ñ���
	m_lCurrentJetton=10000L;

	return;
}

//���밴ť
void CGameClientView::OnJettonButton100000()
{
	//���ñ���
	//--
	m_lCurrentJetton=100000L;
	return;
}

//��ʱ����Ϣ
void CGameClientView::OnTimer(UINT nIDEvent)
{
	//����ʤ��
	if (nIDEvent==IDI_FLASH_WINNER)
	{
		//���ñ���
		if (m_cbWinnerFlash!=m_cbWinnerSide)
		{
			m_cbWinnerFlash=m_cbWinnerSide;
		}
		else 
		{
			m_cbWinnerFlash=0xFF;
		}

		//���½���
		UpdateGameView(NULL);

		return;
	}

	//�ֻ�ׯ��
	if ( nIDEvent == IDI_SHOW_CHANGE_BANKER )
	{
		ShowChangeBanker( false );

		return;
	}

	if(nIDEvent==IDI_UNKNOWN_TIME)
	{
		UpdateGameView(NULL);
	}
	__super::OnTimer(nIDEvent);
}

//�����Ϣ
void CGameClientView::OnLButtonDown(UINT nFlags, CPoint Point)
{
	if(!m_bAutoCard)
	{
		for(int i=0;i<4;i++)
		{
			if(m_DrawCard[i].GetShowState() && m_DrawCard[i].PtInSecondCardRect(Point) && m_DrawCard[i].GetShowHand())
			{
				m_DrawCard[i].OnLButtonDown(Point);
				SetCapture();
				SetTimer(IDI_UNKNOWN_TIME,50,NULL);
			}
		}
	}

	if (m_lCurrentJetton!=0L)
	{
		BYTE cbJettonArea=GetJettonArea(Point);

		//��С�ж�
		switch( cbJettonArea )
		{
		case ID_SHUN_MEN:
			{
				__int64 lMaxPlayerScore = GetMaxPlayerScore();
				if ( lMaxPlayerScore < m_lCurrentJetton )
					return ;
				break;
			}
		case ID_TIAN_MEN:
			{
				__int64 lMaxTieScore  = GetMaxTieScore();
				if ( lMaxTieScore < m_lCurrentJetton )
					return ;
				break;
			}
		case ID_DAO_MEN:
			{
				__int64 lMaxBankerScore = GetMaxBankerScore();
				if ( lMaxBankerScore < m_lCurrentJetton )
					return ;
				break;
			}
		}

		if (cbJettonArea!=0xFF)
			AfxGetMainWnd()->SendMessage(IDM_PLACE_JETTON, cbJettonArea, (LPARAM)(&m_lCurrentJetton));
	}

	for (int i=0; i<7; i++)
	{
		if ( m_JettonButton[i].GetState() != JBST_DISABLE)
		{
			CRect rc	= m_JettonButton[i].GetClientRect();
			if (rc.PtInRect(Point))
			{
				m_JettonButton[i].SetState(JBST_PUSHDOWN);
				m_JettonButtonPushDown = TRUE;

				switch( i )
				{
				case 0:
					OnJettonButton1000();
					break;
				case 1:
					OnJettonButton10000();
					break;
				case 2:
					OnJettonButton100000();
					break;
				case 3:
					OnJettonButton500000();
					break;
				case 4:
					OnJettonButton1000000();
					break;
				case 5:
					OnJettonButton5000000();
					break;
				case 6:
					OnJettonButton10000000();
					break;
				}
			}
			else
			{
				m_JettonButton[i].SetState(JBST_NORMAL);
			}
		}
	}

	UpdateGameView(NULL);

	__super::OnLButtonDown(nFlags,Point);
}

//�����Ϣ
void CGameClientView::OnRButtonDown(UINT nFlags, CPoint Point)
{
	//���ñ���
	m_lCurrentJetton=0L;

	for (int i=0; i<7; i++)
	{
		CRect rc = m_JettonButton[i].GetClientRect();
		if (rc.PtInRect(Point))
		{
			m_JettonButton[i].SetState(JBST_PUSHUP);
		}
		else
		{
			m_JettonButton[i].SetState(JBST_NORMAL);
		}
	}

	__super::OnLButtonDown(nFlags,Point);
}

//�����Ϣ
BOOL CGameClientView::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	if (m_lCurrentJetton!=0L)
	{
		//��ȡ����
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		ScreenToClient(&MousePoint);
		BYTE cbJettonArea=GetJettonArea(MousePoint);

		//���ñ���
		if ( m_cbPreJettonArea != cbJettonArea )
		{
			m_cbPreJettonArea = cbJettonArea;
			UpdateGameView(NULL);
		}

		//�����ж�
		if (cbJettonArea==0xFF)
		{
			SetCursor(LoadCursor(NULL,IDC_NO));
			return TRUE;
		}

		//��С�ж�
		switch( cbJettonArea )
		{
		case ID_SHUN_MEN:
			{
				__int64 lMaxPlayerScore = GetMaxPlayerScore();
				if ( lMaxPlayerScore < m_lCurrentJetton )
				{
					SetCursor(LoadCursor(NULL,IDC_NO));
					return TRUE;
				}
				break;
			}
		case ID_TIAN_MEN:
			{
				__int64 lMaxTieScore  = GetMaxTieScore();
				if ( lMaxTieScore < m_lCurrentJetton )
				{
					SetCursor(LoadCursor(NULL,IDC_NO));
					return TRUE;
				}
				break;
			}
		case ID_DAO_MEN:
			{
				__int64 lMaxBankerScore = GetMaxBankerScore();
				if ( lMaxBankerScore < m_lCurrentJetton  )
				{
					SetCursor(LoadCursor(NULL,IDC_NO));
					return TRUE;
				};
				break;
			}
		//case ID_QIAO:
		//	{
		//		__int64 lMaxTieKingScore= GetMaxTieKingScore();
		//		if ( lMaxTieKingScore < m_lCurrentJetton )
		//		{
		//			SetCursor(LoadCursor(NULL,IDC_NO));
		//			return TRUE;
		//		}
		//		break;
		//	}
		//case ID_ZUO_JIAO:
		//	{
		//		__int64 lMaxPlayerKingScore = GetMaxPlayerKingScore();
		//		if ( lMaxPlayerKingScore < m_lCurrentJetton )
		//		{
		//			SetCursor(LoadCursor(NULL,IDC_NO));
		//			return TRUE;
		//		}
		//		break;
		//	}
		//case ID_YOU_JIAO:
		//	{
		//		__int64 lMaxBankerKingScore = GetMaxBankerKingScore();
		//		if ( lMaxBankerKingScore < m_lCurrentJetton )
		//		{
		//			SetCursor(LoadCursor(NULL,IDC_NO));
		//			return TRUE;
		//		}
		//		break;
		//	}
		}

		//���ù��
		switch (m_lCurrentJetton)
		{
		case 1000:
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SCORE_1000)));
				return TRUE;
			}
		case 10000:
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SCORE_10000)));
				return TRUE;
			}
		case 100000:
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SCORE_100000)));
				return TRUE;
			}
		case 500000:
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SCORE_500000)));
				return TRUE;
			}
		case 1000000:
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SCORE_1000000)));
				return TRUE;
			}
		case 5000000:
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SCORE_5000000)));
				return TRUE;
			}
		case 10000000:
			{
				SetCursor(LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDC_SCORE_10000000)));
				return TRUE;
			}
		}
	}

	return __super::OnSetCursor(pWnd, nHitTest, uMessage);
}

//�ֻ�ׯ��
void CGameClientView::ShowChangeBanker( bool bChangeBanker )
{
	//�ֻ�ׯ��
	if ( bChangeBanker )
	{
		SetTimer( IDI_SHOW_CHANGE_BANKER, 3000, NULL );
		m_bShowChangeBanker = true;
	}
	else
	{
		KillTimer( IDI_SHOW_CHANGE_BANKER );
		m_bShowChangeBanker = false ;
	}

	//���½���
	UpdateGameView(NULL);
}

//��ׯ��ť
void CGameClientView::OnApplyBanker()
{
	AfxGetMainWnd()->SendMessage(IDM_APPLY_BANKER,1,0);

}

//��ׯ��ť
void CGameClientView::OnCancelBanker()
{
	AfxGetMainWnd()->SendMessage(IDM_APPLY_BANKER,0,0);
}

//��������
void CGameClientView::DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos)
{
	//��������
	int nStringLength=lstrlen(pszString);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//�滭�߿�
	pDC->SetTextColor(crFrame);
	for (int i=0;i<CountArray(nXExcursion);i++)
	{
		pDC->TextOut(nXPos+nXExcursion[i],nYPos+nYExcursion[i],pszString,nStringLength);
	}

	//�滭����
	pDC->SetTextColor(crText);
	pDC->TextOut(nXPos,nYPos,pszString,nStringLength);

	return;
}

//ׯ����Ϣ
void CGameClientView::SetBankerInfo( WORD wChairID, BYTE cbBankerTime, __int64 lScore )
{
	//���ñ���
	m_wCurrentBankerChairID = wChairID;
	m_cbBankerTime = cbBankerTime;
	m_lBankerScore = lScore;

	//���½���
	UpdateGameView( NULL );
}

//ׯ�ҽ��
void CGameClientView::SetBankerTreasure(__int64 lBankerTreasure)
{
	m_lBankerTreasure = lBankerTreasure;
	//m_lZhuangScore=lBankerTreasure;
	UpdateGameView(NULL);
}

//�滭��ʶ	��¼
void CGameClientView::DrawWinFlags(CDC * pDC)
{
	CImageHandle ImageHandleWinFlags(&m_ImageWinFlags);
	int nIndex = m_nScoreHead;
	COLORREF clrOld ;
	clrOld = pDC->SetTextColor(RGB(255,234,0));
	CString strPoint;
	int nDrawCount = 0;
	while ( nIndex != m_nRecordLast && ( m_nRecordLast!=m_nRecordFirst ) && nDrawCount < 14 )
	{
		tagClientGameRecord &ClientGameRecord = m_GameRecordArrary[nIndex];

		int nXPos = m_nWinFlagsExcursionX + ((nIndex - m_nScoreHead + MAX_SCORE_HISTORY) % MAX_SCORE_HISTORY) * 39;
		int nYPos = m_nWinFlagsExcursionY+3;

		if(ClientGameRecord.enOperateFlags == enOperateResult_NULL)
		{
			int nCount=0;	
			for(WORD i=ID_SHUN_MEN; i<=ID_DAO_MEN ;i*=2)
			{
				switch(i)
				{
				case ID_SHUN_MEN:
					nCount=0;
					break;
				case ID_TIAN_MEN:
					nCount=1;
					break;
				case ID_DAO_MEN:
					nCount=2;
					break;
				}
				if ( ClientGameRecord.wWinner & i)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*nCount, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(), 0, 0, RGB(255, 0, 255) );
				}
				else
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*nCount, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 2, 0, RGB(255, 0, 255) );
				}
				nCount++;
			}
		}
		else
		{
			if(ClientGameRecord.wWinner & ID_SHUN_MEN)
			{
				if(ClientGameRecord.lMeShunMenScore>0)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 , 0, RGB(255, 0, 255) );
				}
				else if(ClientGameRecord.lMeZuoJiaoScore>0 && ClientGameRecord.wWinner & ID_TIAN_MEN ||	\
						ClientGameRecord.lMeQiaoScore>0 && ClientGameRecord.wWinner & ID_DAO_MEN)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 , 0, RGB(255, 0, 255) );
				}
				else
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos,m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(), 0 , 0, RGB(255, 0, 255) );
				}
			}
			else
			{
				if(ClientGameRecord.lMeShunMenScore>0)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 3, 0, RGB(255, 0, 255) );
				}
				else if(ClientGameRecord.lMeZuoJiaoScore>0 && !(ClientGameRecord.wWinner & ID_TIAN_MEN) ||	\
					ClientGameRecord.lMeQiaoScore>0 && !(ClientGameRecord.wWinner & ID_DAO_MEN))
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 3 , 0, RGB(255, 0, 255) );
				}
				else
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 2, 0, RGB(255, 0, 255) );
				}

			}


			//--
			if(ClientGameRecord.wWinner & ID_DAO_MEN)
			{
				if(ClientGameRecord.lMeDaoMenScore>0)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*2, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 , 0, RGB(255, 0, 255) );
				}
				else if(ClientGameRecord.lMeYouJiaoScore>0 && ClientGameRecord.wWinner & ID_TIAN_MEN ||	\
					ClientGameRecord.lMeQiaoScore>0 && ClientGameRecord.wWinner & ID_SHUN_MEN)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*2, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 , 0, RGB(255, 0, 255) );
				}
				else
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*2,m_ImageWinFlags.GetWidth()/6, 
						m_ImageWinFlags.GetHeight(),0, 0, RGB(255, 0, 255) );
				}
			}
			else
			{
				if(ClientGameRecord.lMeDaoMenScore>0)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*2, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 3, 0, RGB(255, 0, 255) );
				}
				else if(ClientGameRecord.lMeYouJiaoScore>0 && !(ClientGameRecord.wWinner & ID_TIAN_MEN) ||	\
					ClientGameRecord.lMeQiaoScore>0 && !(ClientGameRecord.wWinner & ID_SHUN_MEN))
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*2, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 3 , 0, RGB(255, 0, 255) );
				}
				else
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32*2, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 2, 0, RGB(255, 0, 255) );
				}

			}

			if(ClientGameRecord.wWinner & ID_TIAN_MEN)
			{
				if(ClientGameRecord.lMeTianMenScore>0)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 , 0, RGB(255, 0, 255) );
				}
				else if(ClientGameRecord.lMeYouJiaoScore>0 && ClientGameRecord.wWinner & ID_DAO_MEN ||	\
					ClientGameRecord.lMeZuoJiaoScore>0 && ClientGameRecord.wWinner & ID_SHUN_MEN)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 , 0, RGB(255, 0, 255) );
				}
				else
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32,m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),0 , 0, RGB(255, 0, 255) );
				}
			}
			else
			{
				if(ClientGameRecord.lMeTianMenScore>0)
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 3, 0, RGB(255, 0, 255) );
				}
				else if(ClientGameRecord.lMeYouJiaoScore>0 && !(ClientGameRecord.wWinner & ID_DAO_MEN) ||	\
					ClientGameRecord.lMeZuoJiaoScore>0 && !(ClientGameRecord.wWinner & ID_SHUN_MEN))
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 3, 0, RGB(255, 0, 255) );
				}
				else
				{
					m_ImageWinFlags.AlphaDrawImage( pDC, nXPos, nYPos+32, m_ImageWinFlags.GetWidth()/6 , 
						m_ImageWinFlags.GetHeight(),m_ImageWinFlags.GetWidth()/6 * 2, 0, RGB(255, 0, 255) );
				}
			}
		}
		nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
		nDrawCount++;
	}


	long posx=200;
	long posy=605;
	CString StrwinCount;
	StrwinCount.Format("%.2f %%",m_fWinCount[0]);
	CRect StrRect;
	StrRect.left = posx;
	StrRect.top = posy;
	StrRect.right = StrRect.left + 100;
	StrRect.bottom = StrRect.top + 15;
	pDC->DrawText(StrwinCount, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

	StrwinCount.Format("%.2f %%",m_fWinCount[1]);
	StrRect.left = posx;
	StrRect.top = posy+30;
	StrRect.right = StrRect.left + 100;
	StrRect.bottom = StrRect.top + 15;
	pDC->DrawText(StrwinCount, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

	StrwinCount.Format("%.2f %%",m_fWinCount[1]);
	StrRect.left = posx;
	StrRect.top = posy+60;
	StrRect.right = StrRect.left + 100;
	StrRect.bottom = StrRect.top + 15;
	pDC->DrawText(StrwinCount, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
}

//�ƶ���ť
void CGameClientView::OnScoreMoveL()
{
	if ( m_nRecordFirst == m_nScoreHead ) return;

	m_nScoreHead = (m_nScoreHead - 1 + MAX_SCORE_HISTORY) % MAX_SCORE_HISTORY;
	if ( m_nScoreHead == m_nRecordFirst ) m_btScoreMoveL.EnableWindow(FALSE);

	m_btScoreMoveR.EnableWindow(TRUE);

	//���½���
	UpdateGameView(NULL);
}

//�ƶ���ť
void CGameClientView::OnScoreMoveR()
{
	int nHistoryCount = ( m_nRecordLast - m_nScoreHead + MAX_SCORE_HISTORY ) % MAX_SCORE_HISTORY;
	if ( nHistoryCount == 12 ) return;

	m_nScoreHead = ( m_nScoreHead + 1 ) % MAX_SCORE_HISTORY;
	if ( nHistoryCount-1 == 12 ) m_btScoreMoveR.EnableWindow(FALSE);

	m_btScoreMoveL.EnableWindow(TRUE);

	//���½���
	UpdateGameView(NULL);
}

//��ʾ���
void CGameClientView::ShowGameResult(CDC *pDC, int nWidth, int nHeight)
{
	//��ʾ�ж�
	if ( m_bShowGameResult == false ) return;

	int	nXPos = nWidth / 2 - 129;
	int	nYPos = nHeight / 2 - 208;

	//CImageHandle ImageHandleGameEndFrame(&m_ImageGameEndFrame);
	//m_ImageGameEndFrame.AlphaDrawImage(pDC, nXPos, nYPos, RGB(255,0,255));

	CImageHandle ImageHandleGameEnd(&m_ImageGameEnd);
	CRect rcAlpha(nXPos+2, nYPos+70, nXPos+2 + m_ImageGameEnd.GetWidth(), nYPos+70+m_ImageGameEnd.GetHeight());
	DrawAlphaRect(pDC, &rcAlpha, RGB(74,70,73), 0.8f);
	m_ImageGameEnd.AlphaDrawImage(pDC, nXPos+2, nYPos+70, RGB(255,0,255));

	pDC->SetTextColor(RGB(255,234,0));
	CRect rcMeWinScore, rcMeReturnScore;
	rcMeWinScore.left = nXPos+2 + 40;
	rcMeWinScore.top = nYPos+70 + 32;
	rcMeWinScore.right = rcMeWinScore.left + 111;
	rcMeWinScore.bottom = rcMeWinScore.top + 34;

	rcMeReturnScore.left = nXPos+2 + 150;
	rcMeReturnScore.top = nYPos+70 + 32;
	rcMeReturnScore.right = rcMeReturnScore.left + 111;
	rcMeReturnScore.bottom = rcMeReturnScore.top + 34;

	CString strMeGameScore, strMeReturnScore;
	strMeGameScore.Format(TEXT("%I64d"), m_lMeCurGameScore);
	strMeReturnScore.Format(TEXT("%I64d"), m_lMeCurGameReturnScore);
	pDC->DrawText(strMeGameScore, rcMeWinScore, DT_END_ELLIPSIS | DT_VCENTER | DT_CENTER | DT_SINGLELINE );
	pDC->DrawText(strMeReturnScore, rcMeReturnScore, DT_END_ELLIPSIS | DT_VCENTER | DT_CENTER | DT_SINGLELINE );

	CRect rcBankerWinScore;
	rcBankerWinScore.left = nXPos+2 + 40;
	rcBankerWinScore.top = nYPos+70 + 69;
	rcBankerWinScore.right = rcBankerWinScore.left + 111;
	rcBankerWinScore.bottom = rcBankerWinScore.top + 34;

	CString strBankerCurGameScore;
	strBankerCurGameScore.Format(TEXT("%I64d"), m_lBankerCurGameScore);
	pDC->DrawText(strBankerCurGameScore, rcBankerWinScore, DT_END_ELLIPSIS | DT_VCENTER | DT_CENTER | DT_SINGLELINE );
}

//͸���滭
bool CGameClientView::DrawAlphaRect(CDC* pDC, LPRECT lpRect, COLORREF clr, FLOAT fAlpha)
{
	ASSERT(pDC != 0 && lpRect != 0 && clr != CLR_NONE);
	if(pDC == 0 || lpRect == 0 || clr == CLR_NONE)
	{
		return false;
	}
	//ȫ͸��
	if( abs(fAlpha) <= 0.000001 )
	{
		return true;
	}

	for(LONG l=lpRect->top; l<lpRect->bottom; l++)
	{
		for(LONG k=lpRect->left; k<lpRect->right; k++)
		{
			COLORREF clrBk = pDC->GetPixel(k, l);
			COLORREF clrBlend = RGB(GetRValue(clrBk)*(1-fAlpha)+GetRValue(clr)*fAlpha, 
								GetGValue(clrBk)*(1-fAlpha)+GetGValue(clr)*fAlpha,
								GetBValue(clrBk)*(1-fAlpha)+GetBValue(clr)*fAlpha);
			pDC->SetPixel(k, l, clrBlend);
		}
	}

	return true;
}

//�����ע
__int64 CGameClientView::GetMaxPlayerScore()
{
	if ( m_wCurrentBankerChairID == INVALID_CHAIR ) return 0;

	//��������
	__int64 lAllAreaScore = m_lAllTieScore + 
		m_lAllTieSamePointScore + 
		m_lAllBankerScore+ 
		m_lAllBankerKingScore+
		m_lAllPlayerScore+
		m_lAllPlayerKingScore;

	//�����ע
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

////�����ע
//__int64 CGameClientView::GetMaxPlayerKingScore()
//{
//	if ( m_wCurrentBankerChairID == INVALID_CHAIR ) return 0;
//
//	//��������
//	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
//
//	//�����ע
//	__int64 lMaxPlayerScore = m_lBankerTreasure-lAllAreaScore;
//	return lMaxPlayerScore;
//}

//�����ע
__int64 CGameClientView::GetMaxBankerScore()
{
	if ( m_wCurrentBankerChairID == INVALID_CHAIR ) return 0;

	//��������
	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;


	//�����ע
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	return lMaxPlayerScore;
}

////�����ע
//__int64 CGameClientView::GetMaxBankerKingScore()
//{
//	if ( m_wCurrentBankerChairID == INVALID_CHAIR ) return 0;
//	//��������
//	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
//
//	//�����ע
//	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;
//
//	return lMaxPlayerScore;
//}

//�����ע
__int64 CGameClientView::GetMaxTieScore()
{
	if ( m_wCurrentBankerChairID == INVALID_CHAIR ) return 0;

	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;

	__int64 lMaxTieScore = lMaxPlayerScore;

	return lMaxTieScore;
}
//
////�����ע
//__int64 CGameClientView::GetMaxTieKingScore()
//{
//	if ( m_wCurrentBankerChairID == INVALID_CHAIR ) return 0;
//
//	__int64 lAllAreaScore = m_lAllTieScore + m_lAllTieSamePointScore + m_lAllBankerScore + m_lAllBankerKingScore+m_lAllPlayerScore+m_lAllPlayerKingScore;
//	__int64 lMaxPlayerScore =m_lBankerTreasure-lAllAreaScore;
//	//���ػ���
//	__int64 lMaxTieScore = lMaxPlayerScore;
//
//	return lMaxTieScore;
//}

//�ɼ�����
void CGameClientView::SetGameScore(__int64 lMeCurGameScore, __int64 lMeCurGameReturnScore, __int64 lBankerCurGameScore)
{
	m_lMeCurGameScore=lMeCurGameScore;
	m_lMeCurGameReturnScore=lMeCurGameReturnScore;
	m_lBankerCurGameScore=lBankerCurGameScore;
}

//���ñ�ʶ
void CGameClientView::SetShowGameFlag(bool bShowGameResult)
{
	m_bShowGameResult = bShowGameResult;
	UpdateGameView(NULL);
}

//�滭����
void CGameClientView::DrawMeJettonNumber(CDC *pDC)
{
	//�滭����
	if ( 0 < m_lMeShunMenScore ) 
		DrawNumberString(pDC,m_lMeShunMenScore,m_PointJetton[0].x,m_PointJetton[0].y+25, true);
	if ( 0 < m_lMeTianMenScore)
		DrawNumberString(pDC,m_lMeTianMenScore,m_PointJetton[1].x,m_PointJetton[1].y+25, true);
	if ( 0 < m_lMeDaoMenScore ) 
		DrawNumberString(pDC,m_lMeDaoMenScore,m_PointJetton[2].x,m_PointJetton[2].y+25, true);
}

//////////////////////////////////////////////////////////////////////////


void CGameClientView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!m_bAutoCard)
	{
		for(int i=0;i<4;i++)
		{
			if(m_DrawCard[i].GetShowState())
			{
				m_DrawCard[i].OnLButtonUp(point);
			}
		}
		UpdateGameView(NULL);
		KillTimer(IDI_UNKNOWN_TIME);
		ReleaseCapture();
	}

	m_JettonButtonPushDown = FALSE;
	for (int i=0; i<7; i++)
	{
		if ( m_JettonButton[i].GetState() != JBST_DISABLE )
		{
			m_JettonButton[i].SetState(JBST_NORMAL);
		}
	}

	UpdateGameView(NULL);
	CGameFrameView::OnLButtonUp(nFlags, point);
}

void CGameClientView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!m_bAutoCard)
	{
		for(int i=0;i<4;i++)
		{
			if(m_DrawCard[i].GetShowHand())
			{
				if(m_DrawCard[i].GetShowState())
				{
					m_DrawCard[i].OnMouseMove(point);
				}
			}
			else
			{
				KillTimer(IDI_UNKNOWN_TIME);
				ReleaseCapture();
			}

		}
	}

	if (!m_JettonButtonPushDown)
	{
		for (int i=0; i<7; i++)
		{
			if ( m_JettonButton[i].GetState() != JBST_DISABLE)
			{
				CRect rc	= m_JettonButton[i].GetClientRect();
				if (rc.PtInRect(point))
				{
					m_JettonButton[i].SetState(JBST_OVER);
				}
				else
				{
					m_JettonButton[i].SetState(JBST_NORMAL);
				}
			}
		}

		UpdateGameView(NULL);
	}

	CGameFrameView::OnMouseMove(nFlags, point);
}

void CGameClientView::OnCuoPaiModel()
{
	AfxGetMainWnd()->SendMessage(IDM_CUOPAI,0,0);
}


void CGameClientView:: OnBank()
{
	AfxGetMainWnd()->SendMessage(IDM_ONBANK,0,0);
}

CString CGameClientView::ChangNumber(__int64 iNumber)
{
	CString strNumber;
	strNumber.Format("%I64d",iNumber);
	int len=strNumber.GetLength();
	for(int index = len-3; index > 0; index -= 3)
	{
		if(strNumber.Left(index)!="-")
			strNumber.Insert(index, ",");
	}
	return strNumber;
}

CString CGameClientView::ChangNumber(int iNumber)
{
	CString strNumber;
	strNumber.Format("%d",iNumber);
	int len=strNumber.GetLength();
	for(int index = len-3; index > 0; index -= 3)
	{
		if(strNumber.Left(index)!="-")
			strNumber.Insert(index, ",");
	}
	return strNumber;
}

//����������ע�ܺ�
__int64 CGameClientView::CalcAllJetton()
{
	__int64 uAllScoreCount=0;
	//�滭����
	for (INT i=0;i<3;i++)
	{
		//��������
		__int64 lScoreCount=0L;
		__int64 lScoreJetton[JETTON_COUNT]={1000L,10000L,100000L,500000L,1000000L,5000000L,10000000L};
		//�滭����
		for (INT_PTR j=0;j<m_JettonInfoArray[i].GetCount();j++)
		{
			//��ȡ��Ϣ
			tagJettonInfo * pJettonInfo=&m_JettonInfoArray[i][j];
			//�ۼ�����
			ASSERT(pJettonInfo->cbJettonIndex<JETTON_COUNT);
			lScoreCount+=lScoreJetton[pJettonInfo->cbJettonIndex];
		}
		uAllScoreCount += lScoreCount;
	}
	return uAllScoreCount;
};
