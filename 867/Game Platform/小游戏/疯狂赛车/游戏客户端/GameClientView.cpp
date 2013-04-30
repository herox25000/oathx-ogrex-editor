#include "StdAfx.h"
#include "Math.h"
#include "Resource.h"
#include "GameClientView.h"

//////////////////////////////////////////////////////////////////////////

#define CELL_CX		80
#define CELL_CY		58

//筹码定义
#define JETTON_COUNT				6									//筹码数目
#define JETTON_RADII				68									//筹码半径

static const __int64 s_lScoreJetton[JETTON_COUNT]={100L,1000L,10000L,100000L,1000000L,5000000L};

#define SHOW_HISTROY_COUNT		8

struct ANIMAL_CELL{
	int x;
	int y;
	int animal;
};

static ANIMAL_CELL allcell[32]={
	{-380+0*CELL_CX, -286, 0 },
	{-380+1*CELL_CX, -286, 1 },
	{-380+2*CELL_CX, -286, 2 },
	{-380+3*CELL_CX, -286, 3 },
	{-380+4*CELL_CX, -286, 4 },
	{-380+5*CELL_CX, -286, 5 },
	{-380+6*CELL_CX, -286, 6 },
	{-380+7*CELL_CX, -286, 7 },
	//------------------------
	{-380+8*CELL_CX, -286+0*CELL_CY, 0 },
	{-380+8*CELL_CX, -286+1*CELL_CY, 1 },
	{-380+8*CELL_CX, -286+2*CELL_CY, 2 },
	{-380+8*CELL_CX, -286+3*CELL_CY, 3 },
	{-380+8*CELL_CX, -286+4*CELL_CY, 4 },
	{-380+8*CELL_CX, -286+5*CELL_CY, 5 },
	{-380+8*CELL_CX, -286+6*CELL_CY, 6 },
	{-380+8*CELL_CX, -286+7*CELL_CY, 7 },
	//------------------------
	{-380+8*CELL_CX, -286+8*CELL_CY, 0 },
	{-380+7*CELL_CX, -286+8*CELL_CY, 1 },
	{-380+6*CELL_CX, -286+8*CELL_CY, 2 },
	{-380+5*CELL_CX, -286+8*CELL_CY, 3 },
	{-380+4*CELL_CX, -286+8*CELL_CY, 4 },
	{-380+3*CELL_CX, -286+8*CELL_CY, 5 },
	{-380+2*CELL_CX, -286+8*CELL_CY, 6 },
	{-380+1*CELL_CX, -286+8*CELL_CY, 7 },
	//------------------------
	{-380, -286+8*CELL_CY, 0 },
	{-380, -286+7*CELL_CY, 1 },
	{-380, -286+6*CELL_CY, 2 },
	{-380, -286+5*CELL_CY, 3 },
	{-380, -286+4*CELL_CY, 4 },
	{-380, -286+3*CELL_CY, 5 },
	{-380, -286+2*CELL_CY, 6 },
	{-380, -286+1*CELL_CY, 7 },
};

//时间标识
#define IDI_FLASH_WINNER			100									//闪动标识
#define IDI_SHOW_CHANGE_BANKER		101									//轮换庄家

//按钮标识
#define IDC_JETTON_BUTTON_100		201									//按钮标识
#define IDC_JETTON_BUTTON_1000		202									//按钮标识
#define IDC_JETTON_BUTTON_10000		203									//按钮标识
#define IDC_JETTON_BUTTON_100000	204									//按钮标识
#define IDC_JETTON_BUTTON_500000	205									//按钮标识
#define IDC_JETTON_BUTTON_1000000	206									//按钮标识
#define IDC_JETTON_BUTTON_5000000	207									//按钮标识
#define IDC_APPY_BANKER				208									//按钮标识
#define IDC_CANCEL_BANKER			209									//按钮标识
#define IDC_SCORE_MOVE_L			210									//按钮标识
#define IDC_SCORE_MOVE_R			211									//按钮标识
#define IDC_APPLY_UP				212									//按钮标识
#define IDC_APPLY_DOWN				213									//按钮标识
#define IDC_GET_MONEY				214									//按钮标识
#define IDC_STORE_MONEY				215									//按钮标识

//庄家信息
#define BANKER_INFO_LEN				150									//庄家信息


//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGameClientView, CGameFrameView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_JETTON_BUTTON_100, OnJettonButton100)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_1000, OnJettonButton1000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_10000, OnJettonButton10000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_100000, OnJettonButton100000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_500000, OnJettonButton500000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_1000000, OnJettonButton1000000)
	ON_BN_CLICKED(IDC_JETTON_BUTTON_5000000, OnJettonButton5000000)
	ON_BN_CLICKED(IDC_APPY_BANKER, OnApplyBanker)
	ON_BN_CLICKED(IDC_CANCEL_BANKER, OnCancelBanker)
	ON_BN_CLICKED(IDC_SCORE_MOVE_L, OnScoreMoveL)
	ON_BN_CLICKED(IDC_SCORE_MOVE_R, OnScoreMoveR)
	ON_BN_CLICKED(IDC_APPLY_UP, OnApplyUp)
	ON_BN_CLICKED(IDC_APPLY_DOWN, OnApplyDown)
	ON_BN_CLICKED(IDC_GET_MONEY, OnGetMoneyFromBank)
	ON_BN_CLICKED(IDC_STORE_MONEY, OnGetMoneyFromBank)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CGameClientView::CGameClientView() : CGameFrameView(true,24)
{
	//状态信息
	m_lCurrentJetton=0L;
	m_cbWinnerSide=0xFF;
	m_cbWinnerFlash=0xFF;
	m_wMeChairID=INVALID_CHAIR;
	m_cbPreJettonArea = 255;
	m_bShowGameResult = false;
	m_lMeCurGameScore=0L;			
	m_lMeCurGameReturnScore=0L;	
	m_lBankerCurGameScore=0L;		
	m_bPlayAnimal =false;
	m_cbAnimalBox=0;
	m_cbNowAnimalBox=0;

	//下注信息
	m_lAllBigTigerScore=0L;			
	m_lAllSmlTigerScore=0L;		
	m_lAllBigBogScore=0L;		
	m_lAllSmlBogScore=0L;
	m_lAllBigHorseScore=0L;	
	m_lAllSmlHorseScore=0L;
	m_lAllBigSnakeScore=0L;	
	m_lAllSmlSnakeScore=0L;

	//位置信息
	m_nScoreHead = 0;
	m_nRecordFirst= 0;	
	m_nRecordLast= 0;	

	//历史成绩
	m_wDrawCount=0;
	m_lMeResultCount=0;

	//下注信息
	m_lMeMaxScore=0L;
	
	m_lMeBigTigerScore=0L;
	m_lMeSmlTigerScore=0L;
	m_lMeBigBogScore=0L;
	m_lMeSmlBogScore=0L;
	m_lMeBigHorseScore=0L;
	m_lMeSmlHorseScore=0L;
	m_lMeBigSnakeScore=0L;
	m_lMeSmlSnakeScore=0L;

	//庄家信息
	m_bShowChangeBanker = false;
	m_wCurrentBankerChairID = INVALID_CHAIR;
	m_cbBankerTime = 0;			
	m_lBankerWinScore = 0;		
	m_lBankerTreasure=0;
	m_bstate = 0;

	//加载位图
	HINSTANCE hInstance=AfxGetInstanceHandle();
	//m_ImageViewFill.SetLoadInfo(IDB_VIEW_FILL,hInstance);
	//m_ImageViewBack.SetLoadInfo(IDB_VIEW_BACK,hInstance);
	//m_ImageWinFlags.SetLoadInfo(IDB_WIN_FLAGS,hInstance);
	m_ImageViewBack.LoadImage(GetModuleHandle(0), TEXT("WIN_FLAGS_BACK"));
	m_ImageWinFlags.LoadImage(GetModuleHandle(0), TEXT("WIN_FLAGS_CHE"));
	m_ImageJettonView.SetLoadInfo(IDB_JETTOM_VIEW,hInstance);
	m_ImageScoreNumber.SetLoadInfo(IDB_SCORE_NUMBER,hInstance);
	m_ImageMeScoreNumber.SetLoadInfo(IDB_ME_SCORE_NUMBER,hInstance);

	m_ImageFrame.SetLoadInfo( IDB_FRAME, hInstance );
	//m_ImageGameEnd.SetLoadInfo( IDB_GAME_END, hInstance );
	m_ImageGameEnd.LoadImage( GetModuleHandle(0),TEXT("WIN_GAME_END") );
	m_ImageCard.SetLoadInfo(IDB_GAME_CARD,hInstance);

	m_pngCHART_XIAN.LoadImage(GetModuleHandle(0),TEXT("CHART_XIAN"));
	m_pngCHART_XIAN_EX.LoadImage(GetModuleHandle(0),TEXT("CHART_XIAN_EX"));

	m_pngCHART_ZHUAN_EX.LoadImage(GetModuleHandle(0),TEXT("CHART_ZHUANG_EX"));

	m_ImageMeBanker.SetLoadInfo( IDB_ME_BANKER, hInstance );
	m_ImageChangeBanker.SetLoadInfo( IDB_CHANGE_BANKER, hInstance );
	m_ImageNoBanker.SetLoadInfo( IDB_NO_BANKER, hInstance );	

	//m_ImageTimeFlag.SetLoadInfo(IDB_TIME_FLAG, hInstance);
	m_ImageTimeFlag.LoadImage(GetModuleHandle(0),TEXT("WIN_TIME_FLAG"));

	return;
}

//析构函数
CGameClientView::~CGameClientView(void)
{
}

//建立消息
int CGameClientView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	m_AllhCursor[0]=AfxGetApp()->LoadCursor(IDC_SCORE_100);
	m_AllhCursor[1]=AfxGetApp()->LoadCursor(IDC_SCORE_1000);
	m_AllhCursor[2]=AfxGetApp()->LoadCursor(IDC_SCORE_10000);
	m_AllhCursor[3]=AfxGetApp()->LoadCursor(IDC_SCORE_100000);
	m_AllhCursor[4]=AfxGetApp()->LoadCursor(IDC_SCORE_1000000);
	m_AllhCursor[5]=AfxGetApp()->LoadCursor(IDC_SCORE_5000000);

	//创建控件
	CRect rcCreate(0,0,0,0);
	m_GameRecord.Create(IDD_DLG_GAME_RECORD,this);
	m_ApplyUser.Create( IDD_DLG_GAME_RECORD	, this );
	m_GameRecord.ShowWindow(SW_HIDE);

	//创建按钮
	m_btJetton100.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_100);
	m_btJetton1000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_1000);
	m_btJetton10000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_10000);
	m_btJetton100000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_100000);
	m_btJetton1000000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_1000000);
	m_btJetton5000000.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_JETTON_BUTTON_5000000);	
	
	m_btApplyBanker.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_APPY_BANKER);
	m_btCancelBanker.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_CANCEL_BANKER);
	m_btApplyBanker.ShowWindow(SW_SHOW);
	m_btApplyBanker.EnableWindow(FALSE);
	m_btCancelBanker.ShowWindow(SW_HIDE);

	m_btScoreMoveL.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_SCORE_MOVE_L);
	m_btScoreMoveR.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_SCORE_MOVE_R);

	m_btApplyUp.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_APPLY_UP);
	m_btApplyDown.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_APPLY_DOWN);

	m_btGetMoney.Create(NULL,WS_CHILD|WS_VISIBLE,rcCreate,this,IDC_GET_MONEY);
//	m_btStoreMoney.Create(NULL,WS_CHILD|WS_VISIBLE|WS_DISABLED,rcCreate,this,IDC_STORE_MONEY);

	//设置按钮
	HINSTANCE hResInstance=AfxGetInstanceHandle();
	m_btJetton100.SetButtonImage(IDB_BT_JETTON_100,hResInstance,false);
	m_btJetton1000.SetButtonImage(IDB_BT_JETTON_1000,hResInstance,false);
	m_btJetton10000.SetButtonImage(IDB_BT_JETTON_10000,hResInstance,false);
	m_btJetton100000.SetButtonImage(IDB_BT_JETTON_100000,hResInstance,false);
	m_btJetton1000000.SetButtonImage(IDB_BT_JETTON_1000000,hResInstance,false);
	m_btJetton5000000.SetButtonImage(IDB_BT_JETTON_5000000,hResInstance,false);	
	
	m_btApplyBanker.SetButtonImage(IDB_BT_APPLY_BANKER,hResInstance,false);
	m_btCancelBanker.SetButtonImage(IDB_BT_CANCEL_APPLY,hResInstance,false);

	m_btApplyUp.SetButtonImage(IDB_APPLY_UP, hResInstance, false);
	m_btApplyDown.SetButtonImage(IDB_APPLY_DOWN, hResInstance, false);

	m_btScoreMoveL.SetButtonImage(IDB_BT_SCORE_MOVE_L,hResInstance,false);
	m_btScoreMoveR.SetButtonImage(IDB_BT_SCORE_MOVE_R,hResInstance,false);

	m_btGetMoney.SetButtonImage(IDB_GET_MONEY, hResInstance, false);
//	m_btStoreMoney.SetButtonImage(IDB_STORE_MONEY, hResInstance, false);

	return 0;
}

//重置界面
void CGameClientView::ResetGameView()
{
	//庄家信息
	m_bShowChangeBanker = false;
	m_wCurrentBankerChairID = INVALID_CHAIR;
	m_cbBankerTime = 0;
	m_lBankerWinScore = 0;	
	m_lMeMaxScore=0L;

	m_lMeBigTigerScore=0L;
	m_lMeSmlTigerScore=0L;
	m_lMeBigBogScore=0L;
	m_lMeSmlBogScore=0L;
	m_lMeBigHorseScore=0L;
	m_lMeSmlHorseScore=0L;
	m_lMeBigSnakeScore=0L;
	m_lMeSmlSnakeScore=0L;

	m_bShowGameResult = false;
	m_lMeCurGameScore=0L;			
	m_lMeCurGameReturnScore=0L;	
	m_lBankerCurGameScore=0L;
	m_nScoreHead = 0;
	m_nRecordFirst= 0;	
	m_nRecordLast= 0;	
	m_lBankerTreasure=0;

	m_bPlayAnimal =false;
	m_cbAnimalBox=0;
	m_cbNowAnimalBox=0;

	//下注信息
	m_lAllBigTigerScore=0L;			
	m_lAllSmlTigerScore=0L;		
	m_lAllBigBogScore=0L;		
	m_lAllSmlBogScore=0L;
	m_lAllBigHorseScore=0L;	
	m_lAllSmlHorseScore=0L;
	m_lAllBigSnakeScore=0L;	
	m_lAllSmlSnakeScore=0L;

	//清空列表
	m_ApplyUser.ClearAll();

	//设置按钮
	m_btApplyBanker.ShowWindow(SW_SHOW);
	m_btApplyBanker.EnableWindow(FALSE);
	m_btCancelBanker.ShowWindow(SW_HIDE);
	m_btCancelBanker.SetButtonImage(IDB_BT_CANCEL_APPLY,AfxGetInstanceHandle(),false);

	return;
}

//调整控件
void CGameClientView::RectifyGameView(int nWidth, int nHeight)
{
	//筹码位置
	m_PointJetton[0].SetPoint(nWidth / 2 - 203, nHeight / 2 - 106);
	m_PointJetton[1].SetPoint(nWidth / 2 - 203, nHeight / 2 + 72);
	m_PointJetton[2].SetPoint(nWidth / 2 - 64,  nHeight / 2 - 106);
	m_PointJetton[3].SetPoint(nWidth / 2 - 64,  nHeight / 2 + 72);
	m_PointJetton[4].SetPoint(nWidth / 2 + 73,  nHeight / 2 - 106);
	m_PointJetton[5].SetPoint(nWidth / 2 + 73,  nHeight / 2 + 72);
 	m_PointJetton[6].SetPoint(nWidth / 2 + 212, nHeight / 2 - 106);
 	m_PointJetton[7].SetPoint(nWidth / 2 + 212, nHeight / 2 + 72);

	//移动控件
	HDWP hDwp=BeginDeferWindowPos(32);
	const UINT uFlags=SWP_NOACTIVATE|SWP_NOZORDER|SWP_NOCOPYBITS;

	m_ApplyUser.m_viewHandle = m_hWnd;
	//列表控件
	DeferWindowPos(hDwp, m_ApplyUser,NULL, nWidth/2+188,nHeight/2-336,180,42,uFlags);	//193,58
	//庄家列表按钮
	DeferWindowPos(hDwp,m_btApplyUp,NULL,nWidth/2+282,nHeight/2-294,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btApplyDown,NULL,nWidth/2+322,nHeight/2-294,0,0,uFlags|SWP_NOSIZE);
	m_btApplyUp.ShowWindow(SW_HIDE);
	m_btApplyUp.EnableWindow(true);
	m_btApplyDown.ShowWindow(SW_HIDE);
	m_btApplyDown.EnableWindow(true);

	//筹码按钮
	CRect rcJetton;
	m_btJetton100.GetWindowRect(&rcJetton);
	int nYPos = nHeight/2+210+52;
	int nXPos = nWidth/2-185;
	int nSpace = 2;
	DeferWindowPos(hDwp,m_btJetton100,NULL,nXPos,nYPos,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btJetton1000,NULL,nXPos + nSpace + rcJetton.Width(),nYPos,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btJetton10000,NULL,nXPos + nSpace * 2 + rcJetton.Width() * 2,nYPos,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btJetton100000,NULL,nXPos + nSpace * 3 + rcJetton.Width() * 3,nYPos,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btJetton1000000,NULL,nXPos + nSpace * 4 + rcJetton.Width() * 4,nYPos,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btJetton5000000,NULL,nXPos + nSpace * 5 + rcJetton.Width() * 5,nYPos,0,0,uFlags|SWP_NOSIZE);

	//上庄按钮
	DeferWindowPos(hDwp,m_btApplyBanker,NULL,nWidth/2+188,nHeight/2-295,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btCancelBanker,NULL,nWidth/2+188,nHeight/2-295,0,0,uFlags|SWP_NOSIZE);

	DeferWindowPos(hDwp,m_btScoreMoveL,NULL,nWidth/2-186,nHeight/2+318,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btScoreMoveR,NULL,nWidth/2+165,nHeight/2+318,0,0,uFlags|SWP_NOSIZE);

	//DeferWindowPos(hDwp,m_btStoreMoney,NULL,nWidth/2+202,nYPos-2,0,0,uFlags|SWP_NOSIZE);
	DeferWindowPos(hDwp,m_btGetMoney,NULL,nWidth/2+202,nYPos+43,0,0,uFlags|SWP_NOSIZE);
	m_btGetMoney.ShowWindow(SW_SHOW);
	m_btGetMoney.EnableWindow(TRUE);

	//结束移动
	EndDeferWindowPos(hDwp);

	return;
}

void CGameClientView::DrawFrame(CDC * pDC, BYTE cbJettonArea, int nWidth, int nHeight)
{
	if ( m_lCurrentJetton==0 ) 
		m_cbPreJettonArea=255;

	if (cbJettonArea>=ID_BIG_TIGER && cbJettonArea<=ID_SML_SNAKE )
	{
		CImageHandle ImageHandleFrame(&m_ImageFrame);

		int xPos = m_PointJetton[cbJettonArea-ID_BIG_TIGER].x - 76;
		int yPos = m_PointJetton[cbJettonArea-ID_BIG_TIGER].y - 60;

		m_ImageFrame.AlphaDrawImage(pDC, xPos, yPos, 0xFF00FF);
	}
}

void CGameClientView::DrawPlayAnimal(CDC *pDC, int nWidth, int nHeight)
{
	if ( m_bPlayAnimal==false )
		return;

	LONG xCenter=nWidth/2;
	LONG yCenter=nHeight/2;

	ANIMAL_CELL ac=allcell[m_cbNowAnimalBox%32];
	//绘画准备
	CSize SizeImage(m_pngCHART_XIAN.GetWidth()/MAX_ANIMAL_COUNT,m_pngCHART_XIAN.GetHeight());
	
	m_pngCHART_XIAN.DrawImage(pDC, 
		xCenter+ac.x,
		yCenter+ac.y,
		SizeImage.cx,
		SizeImage.cy,
		SizeImage.cx*ac.animal, 0,
		SizeImage.cx,
		SizeImage.cy);
}

void CGameClientView::DrawMaxPutJetton(CDC* pDC)
{
// 	pDC->SetTextColor(RGB(255,234,0));

// 	CString strLimitScore;
// 	for ( int i=0;i<MAX_ANIMAL_COUNT; i++ )
// 	{
// 		__int64 lMaxPutScore=GetMaxPutScore(ID_BIG_TIGER+i);
// 
// 		if (( m_wCurrentBankerChairID != INVALID_CHAIR ) && m_bShowKXF )
// 			strLimitScore.Format(TEXT("%I64d"), lMaxPutScore);
// 
// 		CRect rect(m_PointJetton[i].x-50, m_PointJetton[i].y+55, m_PointJetton[i].x+50, m_PointJetton[i].y+75);
// 		pDC->DrawText( strLimitScore, rect, DT_CENTER | DT_LEFT | DT_TOP| DT_SINGLELINE );
// 	}
}

void CGameClientView::DrawMySelfInfo(CDC *pDC, int nWidth, int nHeight)
{
	//绘画用户
	if ( m_wMeChairID!=INVALID_CHAIR )
	{
		const tagUserData *pMeUserData = GetUserInfo(m_wMeChairID);
		if ( pMeUserData != NULL )
		{
			//游戏信息
			TCHAR szResultScore[16]=TEXT("");
			TCHAR szGameScore[16]=TEXT("");
			pDC->SetTextColor(0xFFFF);

			__int64 lMeJetton = 0L;
			lMeJetton+=m_lMeBigTigerScore;
			lMeJetton+=m_lMeSmlTigerScore;
			lMeJetton+=m_lMeBigBogScore;
			lMeJetton+=m_lMeSmlBogScore;
			lMeJetton+=m_lMeBigHorseScore;
			lMeJetton+=m_lMeSmlHorseScore;
			lMeJetton+=m_lMeBigSnakeScore;
			lMeJetton+=m_lMeSmlSnakeScore;

			_sntprintf(szGameScore,CountArray(szGameScore),TEXT("%s"), ChangNumber(pMeUserData->lScore-lMeJetton));
			_sntprintf(szResultScore,CountArray(szResultScore),TEXT("%s"),ChangNumber(m_lMeResultCount));

			CRect rcAccount(CPoint(nWidth/2-340,nHeight/2+274),CPoint(nWidth/2-340+180,nHeight/2+274+16));
			CRect rcGameScore(CPoint(nWidth/2-340,nHeight/2+296),CPoint(nWidth/2-340+180,nHeight/2+296+16));
			CRect rcResultScore(CPoint(nWidth/2-340,nHeight/2+317),CPoint(nWidth/2-340+180,nHeight/2+317+16));

			CString strBankerTime;
			strBankerTime.Format( "昵称：%s", pMeUserData->szName );
			pDC->DrawText(strBankerTime,lstrlen(strBankerTime),rcAccount,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
			CString strGameScore;
			strGameScore.Format( "财富：%s", szGameScore );
			pDC->DrawText(strGameScore,lstrlen(strGameScore),rcGameScore,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
			CString strGameResult;
			strGameResult.Format( "成绩：%s", szResultScore );
			pDC->DrawText(strGameResult,lstrlen(strGameResult),rcResultScore,DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
		}
	}
}

void CGameClientView::DrawBankerInfo(CDC *pDC, int nWidth, int nHeight)
{
	//庄家信息																											
	pDC->SetTextColor(RGB(255,234,0));
	if ( m_wCurrentBankerChairID != INVALID_CHAIR )
	{
		//获取玩家
		tagUserData const *pUserData = GetUserInfo( m_wCurrentBankerChairID );
		if ( pUserData )
		{
			//位置信息
			CRect StrRect;
			StrRect.left = nWidth/2 - 354;
			StrRect.top = nHeight/2 - 336;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;

			CString strBankName;
			strBankName.Format("当前庄家：%s", pUserData->szName);
			//庄家名字
			pDC->DrawText( strBankName, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

			//庄家局数
			CString strBankerTime;
			strBankerTime.Format( "连庄盘数：%d", m_cbBankerTime );
			StrRect.left = nWidth/2 - 354;
			StrRect.top = nHeight/2 - 320;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;
			pDC->DrawText( strBankerTime, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

			//庄家总分
			CString strBankerTotalScore;
			strBankerTotalScore.Format( "庄家财富：%s", ChangNumber(pUserData->lScore) );
			StrRect.left = nWidth/2 - 354;
			StrRect.top = nHeight/2 - 304;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;
			pDC->DrawText( strBankerTotalScore, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

			//庄家成绩
			CString strBankerScore;
			strBankerScore.Format( "庄家输赢：%s", ChangNumber(m_lBankerWinScore) );
			StrRect.left = nWidth/2-354;
			StrRect.top = nHeight/2-288;
			StrRect.right = StrRect.left + 190;
			StrRect.bottom = StrRect.top + 15;
			pDC->DrawText( strBankerScore, StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
		}
	}
	else
	{
		//位置信息
		CRect StrRect;
		StrRect.left = nWidth/2-354;
		StrRect.top  = nHeight/2-336;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;

		//庄家名字
		pDC->DrawText( TEXT("当前庄家：无人做庄"), StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

		//庄家局数
		StrRect.left = nWidth/2-354;
		StrRect.top = nHeight/2-320;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;
		pDC->DrawText( "连庄盘数：...", StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

		//庄家成绩
		StrRect.left = nWidth/2-354;
		StrRect.top = nHeight/2-304;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;
		pDC->DrawText( "庄家财富：......", StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );

		//庄家成绩
		StrRect.left = nWidth/2-354;
		StrRect.top = nHeight/2-288;
		StrRect.right = StrRect.left + 190;
		StrRect.bottom = StrRect.top + 15;
		pDC->DrawText( "庄家输赢：......", StrRect, DT_END_ELLIPSIS | DT_LEFT | DT_TOP| DT_SINGLELINE );
	}
}

//绘画界面
void CGameClientView::DrawGameView(CDC * pDC, int nWidth, int nHeight)
{
	//DrawViewImage(pDC,m_ImageViewFill,enMode_Spread);

	RECT rcClient;
	GetClientRect(&rcClient);
	int nXPos=(rcClient.right-m_ImageViewBack.GetWidth())/2;
	int nYPos=(rcClient.bottom-m_ImageViewBack.GetHeight())/2 + 120;
	m_ImageViewBack.DrawImage(pDC,nXPos,nYPos);
	//DrawViewImage(pDC,m_ImageViewBack,enMode_Centent);

	DrawWinFlags(pDC, nWidth, nHeight);

	DrawPlayAnimal(pDC, nWidth, nHeight);

	DrawRandAnimal(pDC, nWidth, nHeight);

	DrawTimeFlag(pDC, nWidth, nHeight);

	DrawMaxPutJetton(pDC);

	DrawFrame( pDC, m_cbPreJettonArea, nWidth, nHeight );

	DrawFlashWinner(pDC, nWidth, nHeight );

	DrawShowChangeBanker(pDC, nWidth, nHeight );

	DrawBankerInfo(pDC, nWidth, nHeight);
	
	DrawDesktopJetton(pDC);
	
	DrawMeJettonNumber(pDC);

	//绘画时间
	if (m_wMeChairID!=INVALID_CHAIR)
	{
		WORD wUserTimer=GetUserTimer(m_wMeChairID);
		if (wUserTimer!=0)
		{
			//DrawUserTimer(pDC,nWidth/2,nHeight/2-180,wUserTimer);
			//获取属性
			const INT nNumberHeight=m_pngCHART_XIAN_EX.GetHeight();
			const INT nNumberWidth=m_pngCHART_XIAN_EX.GetWidth()/10;
			//计算数目
			LONG lNumberCount=0;
			WORD wNumberTemp=wUserTimer;
			do
			{
				lNumberCount++;
				wNumberTemp/=10;
			} while (wNumberTemp>0L);

			//位置定义
			INT nYDrawPos=nHeight/2-180-nNumberHeight/2+1 - 6;
			INT nXDrawPos=nWidth/2+(lNumberCount*nNumberWidth)/2-nNumberWidth + 30;
			//绘画号码
			for (LONG i=0;i<lNumberCount;i++)
			{
				//绘画号码
				WORD wCellNumber=wUserTimer%10;
				m_pngCHART_XIAN_EX.DrawImage(pDC,nXDrawPos,nYDrawPos,nNumberWidth,nNumberHeight,wCellNumber*nNumberWidth,0);

				//设置变量
				wUserTimer/=10;
				nXDrawPos-=nNumberWidth;
			}
		}
	}

	DrawMySelfInfo(pDC, nWidth, nHeight);

	//显示结果
	ShowGameResult(pDC, nWidth, nHeight);
	return;
}

//设置信息
void CGameClientView::SetMeMaxScore(__int64 lMeMaxScore)
{
	if (m_lMeMaxScore!=lMeMaxScore)
	{
		//设置变量
		m_lMeMaxScore=lMeMaxScore;

		//更新界面
		UpdateGameView(NULL);
	}

	return;
}


//设置信息
void CGameClientView::SetMeBigTigerScore(__int64 lMeBigTigerScore)
{
	if (m_lMeBigTigerScore!=lMeBigTigerScore)
	{
		m_lMeBigTigerScore=lMeBigTigerScore;
		UpdateGameView(NULL);
	}
	return;
}

//设置信息
void CGameClientView::SetMeSmlTigerScore(__int64 lMeSmlTigerScore)
{
	if (m_lMeSmlTigerScore!=lMeSmlTigerScore)
	{
		m_lMeSmlTigerScore=lMeSmlTigerScore;
		UpdateGameView(NULL);
	}
	return;
}

//设置信息
void CGameClientView::SetMeBigDogScore(__int64 lMeBigBogScore)
{
	if (m_lMeBigBogScore!=lMeBigBogScore)
	{
		m_lMeBigBogScore=lMeBigBogScore;
		UpdateGameView(NULL);
	}
	return;
}

//设置信息
void CGameClientView::SetMeSmlDogScore(__int64 lMeSmlBogScore)
{
	if (m_lMeSmlBogScore!=lMeSmlBogScore)
	{
		m_lMeSmlBogScore=lMeSmlBogScore;
		UpdateGameView(NULL);
	}
}

//设置信息
void CGameClientView::SetMeBigHorseScore(__int64 lMeBigHorseScore)
{
	if (m_lMeBigHorseScore!=lMeBigHorseScore)
	{
		m_lMeBigHorseScore=lMeBigHorseScore;
		UpdateGameView(NULL);
	}
}

//设置信息
void CGameClientView::SetMeSmlHorseScore(__int64 lMeSmlHorseScore)
{
	if (m_lMeSmlHorseScore!=lMeSmlHorseScore)
	{
		m_lMeSmlHorseScore=lMeSmlHorseScore;
		UpdateGameView(NULL);
	}
}

//设置信息
void CGameClientView::SetMeBigSnakeScore(__int64 lMeBigSnakeScore)
{
	if (m_lMeBigSnakeScore!=lMeBigSnakeScore)
	{
		m_lMeBigSnakeScore=lMeBigSnakeScore;
		UpdateGameView(NULL);
	}
}

//设置信息
void CGameClientView::SetMeSmlSnakeScore(__int64 lMeSmlSnakeScore)
{
	if (m_lMeSmlSnakeScore!=lMeSmlSnakeScore)
	{
		m_lMeSmlSnakeScore=lMeSmlSnakeScore;
		UpdateGameView(NULL);
	}
}

//设置筹码
void CGameClientView::SetCurrentJetton(__int64 lCurrentJetton)
{
	//设置变量
	ASSERT(lCurrentJetton>=0L);
	m_lCurrentJetton=lCurrentJetton;

	return;
}


//历史记录
void CGameClientView::SetGameHistory(enOperateResult OperateResult, BYTE cbWinner)
{
	//设置数据
	tagClientGameRecord &GameRecord = m_GameRecordArrary[m_nRecordLast];

	GameRecord.enOperateFlags = OperateResult;
	GameRecord.cbWinnerAnimal = cbWinner;

	//移动下标
	m_nRecordLast = (m_nRecordLast+1) % MAX_SCORE_HISTORY;
	if ( m_nRecordLast == m_nRecordFirst )
	{
		m_nRecordFirst = (m_nRecordFirst+1) % MAX_SCORE_HISTORY;
		if ( m_nScoreHead < m_nRecordFirst ) m_nScoreHead = m_nRecordFirst;
	}

	int nHistoryCount = (m_nRecordLast - m_nRecordFirst + MAX_SCORE_HISTORY) % MAX_SCORE_HISTORY;
	if ( SHOW_HISTROY_COUNT < nHistoryCount ) m_btScoreMoveR.EnableWindow(TRUE);

	//移到最新记录
	if ( SHOW_HISTROY_COUNT < nHistoryCount )
	{
		m_nScoreHead = (m_nRecordLast - SHOW_HISTROY_COUNT + MAX_SCORE_HISTORY) % MAX_SCORE_HISTORY;
		m_btScoreMoveL.EnableWindow(TRUE);
		m_btScoreMoveR.EnableWindow(FALSE);
	}

	//更新界面
	UpdateGameView(NULL);

	return;
}

//历史成绩
void CGameClientView::SetHistoryScore(WORD wDrawCount,__int64 lMeResultCount)
{
	//设置变量
	m_wDrawCount=wDrawCount;
	m_lMeResultCount=lMeResultCount;

	//更新界面
	UpdateGameView(NULL);

	return;
}

//清理筹码
void CGameClientView::CleanUserJetton()
{
	//清理数组
	for (BYTE i=0;i<CountArray(m_JettonInfoArray);i++)
	{
		m_JettonInfoArray[i].RemoveAll();
	}

	//下注信息
	m_lAllBigTigerScore=0L;			
	m_lAllSmlTigerScore=0L;		
	m_lAllBigBogScore=0L;		
	m_lAllSmlBogScore=0L;
	m_lAllBigHorseScore=0L;	
	m_lAllSmlHorseScore=0L;
	m_lAllBigSnakeScore=0L;	
	m_lAllSmlSnakeScore=0L;
	//更新界面
	UpdateGameView(NULL);

	return;
}

//设置筹码
void CGameClientView::PlaceUserJetton(BYTE cbJettonArea, __int64 lScoreCount)
{
	//效验参数
	ASSERT( cbJettonArea>=ID_BIG_TIGER && cbJettonArea<=ID_SML_SNAKE);
	if (cbJettonArea<ID_BIG_TIGER || cbJettonArea>ID_SML_SNAKE ) return;

	//变量定义
	bool bPlaceJetton=false;

	switch ( cbJettonArea )
	{
	case ID_BIG_TIGER:
		{
			m_lAllBigTigerScore += lScoreCount;
			break;
		}
	case ID_SML_TIGER:
		{
			m_lAllSmlTigerScore += lScoreCount;
			break;
		}
	case ID_BIG_DOG:
		{ 
			m_lAllBigBogScore += lScoreCount;
			break;
		}
	case ID_SML_DOG:
		{ 
			m_lAllSmlBogScore += lScoreCount;
			break;
		}
	case ID_BIG_HORSE:
		{ 
			m_lAllBigHorseScore += lScoreCount;
			break;
		}
	case ID_SML_HORSE:
		{ 
			m_lAllSmlHorseScore += lScoreCount;
			break;
		}
	case ID_BIG_SNAKE:
		{ 
			m_lAllBigSnakeScore += lScoreCount;
			break;
		}
	case ID_SML_SNAKE:
		{
			m_lAllSmlSnakeScore += lScoreCount;
			break;
		}
	}

	//边框宽度
	LONG nFrameWidth  = 128;
	LONG nFrameHeight = 115;

	//增加筹码
	for (BYTE i=0;i<CountArray(s_lScoreJetton);i++)
	{
		//计算数目
		BYTE cbScoreIndex=JETTON_COUNT-i-1;
		__int64 lCellCount=lScoreCount/s_lScoreJetton[cbScoreIndex];

		//插入过虑
		if (lCellCount==0L) continue;

		//加入筹码
		for (__int64 j=0; j<lCellCount; j++)
		{
			//计算位置
			INT nXPos=rand()%JETTON_RADII;
			INT nYPos=(INT)sqrt((FLOAT)(rand()%(JETTON_RADII*JETTON_RADII-nXPos*nXPos)));

			//构造变量
			tagJettonInfo JettonInfo;
			JettonInfo.cbJettonIndex=cbScoreIndex;
			JettonInfo.nXPos=rand()%(nFrameWidth-46);
			JettonInfo.nYPos=rand()%(nFrameHeight-46);
			JettonInfo.nXPos-=nFrameWidth/2;
			JettonInfo.nYPos-=nFrameHeight/2;

			//插入数组
			bPlaceJetton=true;
			m_JettonInfoArray[cbJettonArea-ID_BIG_TIGER].Add(JettonInfo);
		}

		//减少数目
		lScoreCount-=lCellCount*s_lScoreJetton[cbScoreIndex];
	}

	//更新界面
	if ( bPlaceJetton==true ) UpdateGameView(NULL);

	return;
}

//设置胜方
void CGameClientView::SetWinnerSide(BYTE cbWinnerSide)
{
	//设置变量
	m_cbWinnerSide=cbWinnerSide;
	m_cbWinnerFlash=cbWinnerSide;

	//设置时间
	if (cbWinnerSide!=0xFF)
	{
		SetTimer(IDI_FLASH_WINNER,500,NULL);
	}
	else KillTimer(IDI_FLASH_WINNER);

	//更新界面
	UpdateGameView(NULL);

	return;
}

//获取区域
BYTE CGameClientView::GetJettonArea(CPoint MousePoint)
{
	//获取大小
	CRect rcClient ;
	GetClientRect(rcClient);

	int nWidth = rcClient.Width();
	int nHeight = rcClient.Height();

	CRect rect;
	rect.SetRect(0, 0, 120, 160);

	//------------------------------------------------------------------
	rect.MoveToXY(nWidth / 2-270, nHeight / 2 - 170);
	if ( rect.PtInRect(MousePoint) ) return ID_BIG_TIGER;

	rect.MoveToXY(nWidth / 2-270, nHeight / 2 +20 );
	if ( rect.PtInRect(MousePoint) ) return ID_SML_TIGER;
	//------------------------------------------------------------------
	rect.MoveToXY(nWidth / 2-140, nHeight / 2 - 170);
	if ( rect.PtInRect(MousePoint) ) return ID_BIG_DOG;

	rect.MoveToXY(nWidth / 2-140, nHeight / 2 +20 );
	if ( rect.PtInRect(MousePoint) ) return ID_SML_DOG;
	//------------------------------------------------------------------
	rect.MoveToXY(nWidth / 2-10, nHeight / 2 - 170);
	if ( rect.PtInRect(MousePoint) ) return ID_BIG_HORSE;

	rect.MoveToXY(nWidth / 2-10, nHeight / 2 +20 );
	if ( rect.PtInRect(MousePoint) ) return ID_SML_HORSE;
	//------------------------------------------------------------------
	rect.MoveToXY(nWidth / 2+120, nHeight / 2 - 170);
	if ( rect.PtInRect(MousePoint) ) return ID_BIG_SNAKE;

	rect.MoveToXY(nWidth / 2+120, nHeight / 2 +20 );
	if ( rect.PtInRect(MousePoint) ) return ID_SML_SNAKE;
	//------------------------------------------------------------------

	return 0xFF;
}

//绘画数字
void CGameClientView::DrawNumberString(CDC * pDC, __int64 lNumber, INT nXPos, INT nYPos, bool bMeScore)
{
	//加载资源
	CImageHandle HandleScoreNumber(&m_ImageScoreNumber);
	CImageHandle HandleMeScoreNumber(&m_ImageMeScoreNumber);

	//计算数目
	int lNumberCount=0;
	__int64 lNumberTemp=lNumber;
	do
	{
		lNumberCount++;
		lNumberTemp/=10;
	} while (lNumberTemp>0);

	const INT nNumberHeight=m_pngCHART_ZHUAN_EX.GetHeight();
	const INT nNumberWidth=m_pngCHART_ZHUAN_EX.GetWidth()/11;

	CSize SizeScoreNumber(nNumberWidth, nNumberHeight);

	if ( bMeScore ) 
		SizeScoreNumber.SetSize(m_ImageMeScoreNumber.GetWidth()/10, m_ImageMeScoreNumber.GetHeight());

	//位置定义
	INT nYDrawPos=nYPos-SizeScoreNumber.cy/2;
	INT nXDrawPos=nXPos+lNumberCount*SizeScoreNumber.cx/2-SizeScoreNumber.cx;

	INT nYDrawPosEx=nYPos-nNumberHeight/2;
	INT nXDrawPosEx=nXPos+lNumberCount*nNumberWidth/2-nNumberWidth;

	//绘画桌号
	for (__int64 i=0;i<lNumberCount;i++)
	{
		//绘画号码
		int lCellNumber=(int)(lNumber%10);
		if ( bMeScore )
		{
			m_ImageMeScoreNumber.AlphaDrawImage(pDC,nXDrawPos,nYDrawPos,SizeScoreNumber.cx,SizeScoreNumber.cy,
				lCellNumber*SizeScoreNumber.cx,0,RGB(255,0,255));
		}
		else
		{
			m_pngCHART_ZHUAN_EX.DrawImage(pDC,nXDrawPosEx,nYDrawPosEx,nNumberWidth,nNumberHeight,lCellNumber*nNumberWidth,0);
			if ( i != 0 && (int)((i+1)%4) == 0 && (lNumberCount-1) > i )
			{
				nXDrawPosEx -= 6;
				m_pngCHART_ZHUAN_EX.DrawImage(pDC,nXDrawPosEx,nYDrawPosEx,nNumberWidth,nNumberHeight,10*nNumberWidth,0);
			}
			//m_ImageScoreNumber.AlphaDrawImage(pDC,nXDrawPos,nYDrawPos,SizeScoreNumber.cx,SizeScoreNumber.cy, lCellNumber*SizeScoreNumber.cx,0,);
		}

		//设置变量
		lNumber/=10;
		nXDrawPos-=SizeScoreNumber.cx;
		nXDrawPosEx -= nNumberWidth;
	};

	return;
}

//筹码按钮
void CGameClientView::OnJettonButton100()
{
	//设置变量
	m_lCurrentJetton=100L;

	return;
}

//筹码按钮
void CGameClientView::OnJettonButton1000()
{
	//设置变量
	m_lCurrentJetton=1000L;
	return;
}

//筹码按钮
void CGameClientView::OnJettonButton10000()
{
	//设置变量
	m_lCurrentJetton=10000L;

	return;
}

//筹码按钮
void CGameClientView::OnJettonButton100000()
{
	//设置变量
	m_lCurrentJetton=100000L;

	return;
}

//筹码按钮
void CGameClientView::OnJettonButton500000()
{
	//设置变量
	m_lCurrentJetton=500000L;

	return;
}

//筹码按钮
void CGameClientView::OnJettonButton1000000()
{
	//设置变量
	m_lCurrentJetton=1000000L;

	return;
}

//筹码按钮
void CGameClientView::OnJettonButton5000000()
{
	//设置变量
	m_lCurrentJetton=5000000L;

	return;
}

//定时器消息
void CGameClientView::OnTimer(UINT nIDEvent)
{
	//闪动胜方
	if (nIDEvent==IDI_FLASH_WINNER)
	{
		//设置变量
		if (m_cbWinnerFlash!=m_cbWinnerSide)
		{
			m_cbWinnerFlash=m_cbWinnerSide;
		}
		else 
		{
			m_cbWinnerFlash=0xFF;
		}

		//更新界面
		UpdateGameView(NULL);

		return;
	}

	//轮换庄家
	if ( nIDEvent == IDI_SHOW_CHANGE_BANKER )
	{
		ShowChangeBanker( false );

		return;
	}

	__super::OnTimer(nIDEvent);
}

//鼠标消息
void CGameClientView::OnLButtonDown(UINT nFlags, CPoint Point)
{
	if (m_lCurrentJetton!=0L)
	{
		BYTE cbJettonArea=GetJettonArea(Point);

		//大小判断
		__int64 lMaxPutScore=GetMaxPutScore(cbJettonArea, 1);
		if ( lMaxPutScore < m_lCurrentJetton )
			return ;

		__int64* pSend=&m_lCurrentJetton;
		if (cbJettonArea!=0xFF) AfxGetMainWnd()->SendMessage(IDM_PLACE_JETTON, cbJettonArea, (LPARAM)pSend);
	}

	__super::OnLButtonDown(nFlags,Point);
}

//鼠标消息
void CGameClientView::OnRButtonDown(UINT nFlags, CPoint Point)
{
	//设置变量
	m_lCurrentJetton=0L;

	__super::OnLButtonDown(nFlags,Point);
}

//光标消息
BOOL CGameClientView::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	if (m_lCurrentJetton!=0L)
	{
		//获取区域
		CPoint MousePoint;
		GetCursorPos(&MousePoint);
		ScreenToClient(&MousePoint);
		BYTE cbJettonArea=GetJettonArea(MousePoint);

		//设置变量
		if ( m_cbPreJettonArea != cbJettonArea )
		{
			m_cbPreJettonArea = cbJettonArea;
			UpdateGameView(NULL);
		}

		//区域判断
		if (cbJettonArea==0xFF)
		{
			SetCursor(LoadCursor(NULL,IDC_NO));
			return TRUE;
		}

		if ( GetMaxPutScore(cbJettonArea) < m_lCurrentJetton )
		{
			SetCursor(LoadCursor(NULL,IDC_NO));
			return TRUE;
		}

		//设置光标
		switch (m_lCurrentJetton)
		{
		case 100:
			{
				SetCursor(m_AllhCursor[0]);
				return TRUE;
			}
		case 1000:
			{
				SetCursor(m_AllhCursor[1]);
				return TRUE;
			}
		case 10000:
			{
				SetCursor(m_AllhCursor[2]);
				return TRUE;
			}
		case 100000:
			{
				SetCursor(m_AllhCursor[3]);
				return TRUE;
			}
		case 500000:
			{
				SetCursor(m_AllhCursor[4]);
				return TRUE;
			}
		case 1000000:
			{
				SetCursor(m_AllhCursor[5]);
				return TRUE;
			}
		case 5000000:
			{
				SetCursor(m_AllhCursor[6]);
				return TRUE;
			}
		}
	}

	return __super::OnSetCursor(pWnd, nHitTest, uMessage);
}

//轮换庄家
void CGameClientView::ShowChangeBanker( bool bChangeBanker )
{
	//轮换庄家
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

	//更新界面
	UpdateGameView(NULL);
}

//上庄按钮
void CGameClientView::OnApplyBanker()
{
	AfxGetMainWnd()->SendMessage(IDM_APPLY_BANKER,1,0);
}

//下庄按钮
void CGameClientView::OnCancelBanker()
{
	AfxGetMainWnd()->SendMessage(IDM_APPLY_BANKER,0,0);
}

//艺术字体
void CGameClientView::DrawTextString(CDC * pDC, LPCTSTR pszString, COLORREF crText, COLORREF crFrame, int nXPos, int nYPos)
{
	//变量定义
	int nStringLength=lstrlen(pszString);
	int nXExcursion[8]={1,1,1,0,-1,-1,-1,0};
	int nYExcursion[8]={-1,0,1,1,1,0,-1,-1};

	//绘画边框
	pDC->SetTextColor(crFrame);
	for (int i=0;i<CountArray(nXExcursion);i++)
	{
		pDC->TextOut(nXPos+nXExcursion[i],nYPos+nYExcursion[i],pszString,nStringLength);
	}

	//绘画字体
	pDC->SetTextColor(crText);
	pDC->TextOut(nXPos,nYPos,pszString,nStringLength);

	return;
}

//庄家信息
void CGameClientView::SetBankerInfo( WORD wChairID, BYTE cbBankerTime, __int64 lBankerWinScore )
{
	//设置变量
	m_wCurrentBankerChairID = wChairID;
	m_cbBankerTime = cbBankerTime;
	m_lBankerWinScore = lBankerWinScore;

	//更新界面
	UpdateGameView( NULL );
}

//庄家金币
void CGameClientView::SetBankerTreasure(__int64 lBankerTreasure)
{
	m_lBankerTreasure = lBankerTreasure;
	UpdateGameView(NULL);
}

//绘画标识
void CGameClientView::DrawWinFlags(CDC * pDC, int nWidth, int nHeight)
{
	//CImageHandle ImageHandleWinFlags(&m_ImageWinFlags);
	LONG x = nWidth/2-154;	
	LONG y = nHeight/2+319;

	int nIndex = m_nScoreHead;

	const INT nPigHeight = m_ImageWinFlags.GetHeight();
	const INT nPigWidth = m_ImageWinFlags.GetWidth()/8;

	int nDrawCount = 0;
	while ( nIndex != m_nRecordLast && ( m_nRecordLast!=m_nRecordFirst ) && nDrawCount < SHOW_HISTROY_COUNT )
	{
		tagClientGameRecord &ClientGameRecord = m_GameRecordArrary[nIndex];
		BYTE nFlagsIndex=ClientGameRecord.cbWinnerAnimal-1;

		m_ImageWinFlags.DrawImage( pDC, x+nDrawCount*38, y, nPigWidth, nPigHeight, nPigWidth*nFlagsIndex, 0);	//0xFF00FF
		nIndex = (nIndex+1) % MAX_SCORE_HISTORY;
		nDrawCount++;
	}
}

//移动按钮
void CGameClientView::OnScoreMoveL()
{
	if ( m_nRecordFirst == m_nScoreHead ) return;

	m_nScoreHead = (m_nScoreHead - 1 + MAX_SCORE_HISTORY) % MAX_SCORE_HISTORY;
	if ( m_nScoreHead == m_nRecordFirst ) m_btScoreMoveL.EnableWindow(FALSE);

	m_btScoreMoveR.EnableWindow(TRUE);

	//更新界面
	UpdateGameView(NULL);
}

//移动按钮
void CGameClientView::OnScoreMoveR()
{
	int nHistoryCount = ( m_nRecordLast - m_nScoreHead + MAX_SCORE_HISTORY ) % MAX_SCORE_HISTORY;
	if ( nHistoryCount == 12 ) return;

	m_nScoreHead = ( m_nScoreHead + 1 ) % MAX_SCORE_HISTORY;
	if ( nHistoryCount-1 == 12 ) m_btScoreMoveR.EnableWindow(FALSE);

	m_btScoreMoveL.EnableWindow(TRUE);

	//更新界面
	UpdateGameView(NULL);
}

//显示结果
void CGameClientView::ShowGameResult(CDC *pDC, int nWidth, int nHeight)
{
	//显示判断
	if ( m_bShowGameResult == false ) return;

	int	nXPos = nWidth / 2 - 200;
	int	nYPos = nHeight / 2 - 208;

	//CImageHandle ImageHandleGameEnd(&m_ImageGameEnd);

	//加载位图
	CImageHandle HandleCard(&m_ImageCard);
	CSize CardSize;
	CardSize.cx=m_ImageCard.GetWidth()/13;
	CardSize.cy=m_ImageCard.GetHeight()/5;

	//时间标
	//CImageHandle ImageHandleTimeFlag(&m_ImageTimeFlag);
	int nTimeFlagWidth = m_ImageTimeFlag.GetWidth()/3;

	//---------

	CRect rcAlpha(nXPos+2, nYPos+70, nXPos+2 + m_ImageGameEnd.GetWidth(), nYPos+70+m_ImageGameEnd.GetHeight());
	DrawAlphaRect(pDC, &rcAlpha, RGB(74,70,73), 0.8f);
	m_ImageGameEnd.DrawImage(pDC, nXPos+2, nYPos+70);		//RGB(255,0,255)

	pDC->SetTextColor(RGB(255,234,0));
	CRect rcMeWinScore, rcMeReturnScore;
	rcMeWinScore.left = nXPos+2 + 120;
	rcMeWinScore.top = nYPos+70 + 66;
	rcMeWinScore.right = rcMeWinScore.left + 111;
	rcMeWinScore.bottom = rcMeWinScore.top + 34;

	rcMeReturnScore.left = nXPos+2 + 260;
	rcMeReturnScore.top = nYPos+70 + 66;
	rcMeReturnScore.right = rcMeReturnScore.left + 111;
	rcMeReturnScore.bottom = rcMeReturnScore.top + 34;

	pDC->DrawText(ChangNumber(m_lMeCurGameScore), rcMeWinScore, DT_END_ELLIPSIS | DT_VCENTER | DT_CENTER | DT_SINGLELINE );
	pDC->DrawText(ChangNumber(m_lMeCurGameReturnScore), rcMeReturnScore, DT_END_ELLIPSIS | DT_VCENTER | DT_CENTER | DT_SINGLELINE );

	CRect rcBankerWinScore;
	rcBankerWinScore.left = nXPos+2 + 120;
	rcBankerWinScore.top = nYPos+70 + 102;
	rcBankerWinScore.right = rcBankerWinScore.left + 111;
	rcBankerWinScore.bottom = rcBankerWinScore.top + 34;

	pDC->DrawText(ChangNumber(m_lBankerCurGameScore), rcBankerWinScore, DT_END_ELLIPSIS | DT_VCENTER | DT_CENTER | DT_SINGLELINE );
}

//透明绘画
bool CGameClientView::DrawAlphaRect(CDC* pDC, LPRECT lpRect, COLORREF clr, FLOAT fAlpha)
{
	ASSERT(pDC != 0 && lpRect != 0 && clr != CLR_NONE);
	if(pDC == 0 || lpRect == 0 || clr == CLR_NONE)
	{
		return false;
	}
	//全透明
	if( abs(fAlpha) <= 0.000001 )
	{
		return true;
	}

	for(int l=lpRect->top; l<lpRect->bottom; l++)
	{
		for(int k=lpRect->left; k<lpRect->right; k++)
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

//得到所有人下注的积分
__int64 CGameClientView::Get_ALL_MultiDesktopScore()
{
	__int64  sxDesktopScore=0L;

	sxDesktopScore+=m_lAllBigTigerScore*s_Multiple[0];		//大家买大虎总注
	sxDesktopScore+=m_lAllSmlTigerScore*s_Multiple[1];		//大家买小虎总注
	sxDesktopScore+=m_lAllBigBogScore  *s_Multiple[2];		//大家买大狗总注
	sxDesktopScore+=m_lAllSmlBogScore  *s_Multiple[3];		//大家买大狗总注
	sxDesktopScore+=m_lAllBigHorseScore*s_Multiple[4];		//大家买大马总注
	sxDesktopScore+=m_lAllSmlHorseScore*s_Multiple[5];		//大家买小马总注
	sxDesktopScore+=m_lAllBigSnakeScore*s_Multiple[6];		//大家买大蛇总注
	sxDesktopScore+=m_lAllSmlSnakeScore*s_Multiple[7];		//大家买小蛇总注

	return sxDesktopScore;
}

//得到自己总的下注
__int64 CGameClientView::Get_Me_DesktopJetton()
{
	__int64 lMeDesktopJetton = 0;

	lMeDesktopJetton += m_lMeBigTigerScore;		//我买大虎总注
	lMeDesktopJetton += m_lMeSmlTigerScore;		//我买小虎总注
	lMeDesktopJetton += m_lMeBigBogScore;		//我买大狗总注
	lMeDesktopJetton += m_lMeSmlBogScore;		//我买大狗总注
	lMeDesktopJetton += m_lMeBigHorseScore;		//我买大马总注
	lMeDesktopJetton += m_lMeSmlHorseScore;		//我买小马总注
	lMeDesktopJetton += m_lMeBigSnakeScore;		//我买大蛇总注
	lMeDesktopJetton += m_lMeSmlSnakeScore;		//我买小蛇总注

	return lMeDesktopJetton;
}

//最大下注
__int64 CGameClientView::GetMaxPutScore(BYTE cbJettonArea, BOOL bDebug)
{
	if ( m_wCurrentBankerChairID == INVALID_CHAIR ) return 0;
	if ( cbJettonArea<ID_BIG_TIGER || cbJettonArea>ID_SML_SNAKE ) return 0;

	//大家已下注额
	__int64 sxAllDesktopJetton=GetAllAreaScore(cbJettonArea);
	__int64 sxAllLeftSpace = m_lBankerTreasure-sxAllDesktopJetton;
	sxAllLeftSpace = max(sxAllLeftSpace, 0);
	sxAllLeftSpace=sxAllLeftSpace/s_Multiple[cbJettonArea-ID_BIG_TIGER];

	//我已下注额
	__int64 sxMeDesktopJetton = Get_Me_DesktopJetton();
	__int64 sxMeLeftJetton = m_lMeMaxScore-sxMeDesktopJetton;
	sxMeLeftJetton = max(sxMeLeftJetton, 0);

	//最小的剩余空间
	__int64 sxMinJetton = min(sxMeLeftJetton, sxAllLeftSpace);

	return sxMinJetton;
}

__int64 CGameClientView::GetAllAreaScore(BYTE cbJettonArea)
{
	if ( cbJettonArea<ID_BIG_TIGER || cbJettonArea>ID_SML_SNAKE ) return 0;
	switch(cbJettonArea)
	{
	case ID_BIG_TIGER:
		return m_lAllBigTigerScore * s_Multiple[0];
	case ID_SML_TIGER:
		return m_lAllSmlTigerScore * s_Multiple[1];
	case ID_BIG_DOG:
		return m_lAllBigBogScore * s_Multiple[2];
	case ID_SML_DOG:
		return m_lAllSmlBogScore * s_Multiple[3];
	case ID_BIG_HORSE:
		return m_lAllBigHorseScore * s_Multiple[4];
	case ID_SML_HORSE:
		return m_lAllSmlHorseScore * s_Multiple[5];
	case ID_BIG_SNAKE:
		return m_lAllBigSnakeScore * s_Multiple[6];
	case ID_SML_SNAKE:
		return m_lAllSmlSnakeScore * s_Multiple[7];
	}
	return 0;
}

__int64 CGameClientView::GetMaxDesktopPutScore(BYTE& cbJettonArea)
{
	__int64 nMaxScore = 0;
	__int64 nLeftScore[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	nLeftScore[0] = m_lAllBigTigerScore * s_Multiple[0];
	nLeftScore[1] = m_lAllSmlTigerScore * s_Multiple[1];
	nLeftScore[2] = m_lAllBigBogScore * s_Multiple[2];
	nLeftScore[3] = m_lAllSmlBogScore * s_Multiple[3];
	nLeftScore[4] = m_lAllBigHorseScore * s_Multiple[4];
	nLeftScore[5] = m_lAllSmlHorseScore * s_Multiple[5];
	nLeftScore[6] = m_lAllBigSnakeScore * s_Multiple[6];
	nLeftScore[7] = m_lAllSmlSnakeScore * s_Multiple[7];

	for (int i = 0; i < 8; i++)
	{
		if ( nMaxScore == 0 || nMaxScore > nLeftScore[i] )
		{
			nMaxScore = nLeftScore[i];
			cbJettonArea = i;
		}
	}
	return nMaxScore;
}

//成绩设置
void CGameClientView::SetGameScore(__int64 lMeCurGameScore, __int64 lMeCurGameReturnScore, __int64 lBankerCurGameScore)
{
	m_lMeCurGameScore=lMeCurGameScore;
	m_lMeCurGameReturnScore=lMeCurGameReturnScore;
	m_lBankerCurGameScore=lBankerCurGameScore;
}

//设置标识
void CGameClientView::SetShowGameFlag(bool bShowGameResult)
{
	m_bShowGameResult = bShowGameResult;
	UpdateGameView(NULL);
}

//绘画数字
void CGameClientView::DrawMeJettonNumber(CDC *pDC)
{
	//绘画数字
	if ( 0 < m_lMeBigTigerScore ) DrawNumberString(pDC,m_lMeBigTigerScore, m_PointJetton[0].x, m_PointJetton[0].y+25, true);
	if ( 0 < m_lMeSmlTigerScore)  DrawNumberString(pDC,m_lMeSmlTigerScore, m_PointJetton[1].x, m_PointJetton[1].y+25, true);
	if ( 0 < m_lMeBigBogScore )   DrawNumberString(pDC,m_lMeBigBogScore,   m_PointJetton[2].x, m_PointJetton[2].y+25, true);
	if ( 0 < m_lMeSmlBogScore )   DrawNumberString(pDC,m_lMeSmlBogScore,   m_PointJetton[3].x, m_PointJetton[3].y+25, true);
	if ( 0 < m_lMeBigHorseScore ) DrawNumberString(pDC,m_lMeBigHorseScore, m_PointJetton[4].x, m_PointJetton[4].y+25, true);
	if ( 0 < m_lMeSmlHorseScore ) DrawNumberString(pDC,m_lMeSmlHorseScore, m_PointJetton[5].x, m_PointJetton[5].y+25, true);
	if ( 0 < m_lMeBigSnakeScore ) DrawNumberString(pDC,m_lMeBigSnakeScore, m_PointJetton[6].x, m_PointJetton[6].y+25, true);
	if ( 0 < m_lMeSmlSnakeScore ) DrawNumberString(pDC,m_lMeSmlSnakeScore, m_PointJetton[7].x, m_PointJetton[7].y+25, true);
}

//绘画数字
void CGameClientView::DrawDesktopJetton(CDC *pDC)
{
	//筹码资源
	CImageHandle HandleJettonView(&m_ImageJettonView);
	CSize SizeJettonItem(m_ImageJettonView.GetWidth()/JETTON_COUNT,m_ImageJettonView.GetHeight());

	//绘画筹码
	for (int i=0; i<MAX_ANIMAL_COUNT; i++)
	{
		//变量定义
		__int64 lScoreCount=0L;

		//绘画筹码
		for ( INT_PTR j=0; j<m_JettonInfoArray[i].GetCount(); j++)
		{
			//获取信息
			tagJettonInfo * pJettonInfo=&m_JettonInfoArray[i][j];

			//累计数字
			ASSERT(pJettonInfo->cbJettonIndex<JETTON_COUNT);
			lScoreCount+=s_lScoreJetton[pJettonInfo->cbJettonIndex];

			//绘画界面
			m_ImageJettonView.AlphaDrawImage(pDC,
				pJettonInfo->nXPos+m_PointJetton[i].x,
				pJettonInfo->nYPos+m_PointJetton[i].y,
				SizeJettonItem.cx,
				SizeJettonItem.cy,
				pJettonInfo->cbJettonIndex*SizeJettonItem.cx,
				0,
				0xFF00FF);
		}

		//绘画数字
		if (lScoreCount>0L)	DrawNumberString(pDC,lScoreCount,m_PointJetton[i].x,m_PointJetton[i].y-10);
	}
}

//绘画数字
void CGameClientView::DrawFlashWinner(CDC *pDC, int nWidth, int nHeight)
{
	//胜利标志
	if ( m_cbWinnerFlash!=0xFF )
	{
		//加载资源
		//CImageHandle HandleWinFlags(&m_ImageWinFlags);
		CSize SizeWinFlags(m_ImageWinFlags.GetWidth()/3,m_ImageWinFlags.GetHeight());
		DrawFrame( pDC, m_cbWinnerFlash, nWidth, nHeight );

		LONG xCenter=nWidth/2;
		LONG yCenter=nHeight/2;

		ANIMAL_CELL ac=allcell[m_cbAnimalBox%32];
		//绘画准备
		CSize SizeImage(m_pngCHART_XIAN.GetWidth()/MAX_ANIMAL_COUNT,m_pngCHART_XIAN.GetHeight());
		m_pngCHART_XIAN.DrawImage(pDC, 
			xCenter+ac.x, yCenter+ac.y, 
			SizeImage.cx,
			SizeImage.cy,
			SizeImage.cx*ac.animal, 0,
			SizeImage.cx,
			SizeImage.cy);
	}
}

//绘画数字
void CGameClientView::DrawTimeFlag(CDC *pDC, int nWidth, int nHeight)
{
	//时间标识
	bool bDispatchCard = (m_cbAnimalBox>0) ? true : false;

	//CImageHandle ImageHandleTimeFlag(&m_ImageTimeFlag);
	int nTimeFlagWidth = m_ImageTimeFlag.GetWidth()/3;

// 	if ( bDispatchCard ) 
// 		m_ImageTimeFlag.BitBlt(pDC->GetSafeHdc(), nWidth/2-98, nHeight/2-192, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), 2 * nTimeFlagWidth, 0);
// 	else if ( m_wCurrentBankerChairID != INVALID_CHAIR )
// 		m_ImageTimeFlag.BitBlt(pDC->GetSafeHdc(), nWidth/2-98, nHeight/2-192, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), nTimeFlagWidth, 0);
// 	else
// 		m_ImageTimeFlag.BitBlt(pDC->GetSafeHdc(), nWidth/2-98, nHeight/2-192, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), 0, 0);

	if ( m_bstate == Status_DisCard ) 
		m_ImageTimeFlag.DrawImage(pDC, nWidth/2-106, nHeight/2-200, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), 2 * nTimeFlagWidth, 0);
	else if ( m_bstate == Status_Jetton )
		m_ImageTimeFlag.DrawImage(pDC, nWidth/2-106, nHeight/2-200, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), nTimeFlagWidth, 0);
	else
		m_ImageTimeFlag.DrawImage(pDC, nWidth/2-106, nHeight/2-200, nTimeFlagWidth, m_ImageTimeFlag.GetHeight(), 0, 0);

}

//绘画数字
void CGameClientView::DrawShowChangeBanker(CDC *pDC, int nWidth, int nHeight)
{
	//切换庄家
	if ( m_bShowChangeBanker )
	{
		int	nXPos = nWidth / 2 - 130;
		int	nYPos = nHeight / 2 - 160;

		//由我做庄
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
}

void CGameClientView::OnApplyUp()
{
	m_ApplyUser.m_AppyUserList.SendMessage(WM_VSCROLL, MAKELONG(SB_LINEUP,0),NULL);
	m_ApplyUser.m_AppyUserList.Invalidate(TRUE);
	double nPos = m_ApplyUser.m_AppyUserList.GetScrollPos(SB_VERT);
	double nMax = m_ApplyUser.m_AppyUserList.GetScrollLimit(SB_VERT);
}

void CGameClientView::OnApplyDown()
{
	double nPos = m_ApplyUser.m_AppyUserList.GetScrollPos(SB_VERT);
	if(m_ApplyUser.m_AppyUserList.GetItemCount()>3)
	{
		if(nPos>m_ApplyUser.m_AppyUserList.GetItemCount()-4)
		{
			return ;
		}
	}
	m_ApplyUser.m_AppyUserList.SendMessage(WM_VSCROLL, MAKELONG(SB_LINEDOWN,0),NULL);
	m_ApplyUser.m_AppyUserList.Invalidate(TRUE);
	double nMax = m_ApplyUser.m_AppyUserList.GetScrollLimit(SB_VERT);
}

void CGameClientView::OnGetMoneyFromBank()
{
	AfxGetMainWnd()->SendMessage(IDM_ONBANK,0,0);
}

void CGameClientView::OnStoreMoneyToBank()
{
	AfxGetMainWnd()->SendMessage(IDM_ONBANK,0,0);
}

void CGameClientView::DrawRandAnimal(CDC *pDC, int nWidth, int nHeight)
{
	if (m_bstate == Status_DisCard)
		return;
	LONG xCenter=nWidth/2;
	LONG yCenter=nHeight/2;

	int nRand = rand()%32;
	ANIMAL_CELL ac=allcell[nRand];
	//绘画准备
	CSize SizeImage(m_pngCHART_XIAN.GetWidth()/MAX_ANIMAL_COUNT,m_pngCHART_XIAN.GetHeight());

	m_pngCHART_XIAN.DrawImage(pDC, 
		xCenter+ac.x,
		yCenter+ac.y,
		SizeImage.cx,
		SizeImage.cy,
		SizeImage.cx*ac.animal, 0,
		SizeImage.cx,
		SizeImage.cy);
}

//计算所有下注总和
__int64 CGameClientView::CalcAllJetton()
{
	__int64 uAllScoreCount=0;
	uAllScoreCount=m_lAllBigTigerScore+m_lAllSmlTigerScore+m_lAllBigBogScore
		+m_lAllSmlBogScore+m_lAllBigHorseScore+m_lAllSmlHorseScore+m_lAllBigSnakeScore+m_lAllSmlSnakeScore;
	return uAllScoreCount;
}

//////////////////////////////////////////////////////////////////////////

