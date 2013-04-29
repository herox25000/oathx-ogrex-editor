#include "Stdafx.h"
#include "Resource.h"
#include "AfxPriv.h"
#include "SkinDialog.h"
#include "BitImage.h"


//圆角大小
#define ROUND_CX					5									//圆角宽度
#define ROUND_CY					5									//圆角高度

//阴影定义
#define SHADOW_CX					5									//阴影宽度
#define SHADOW_CY					5									//阴影高度

//按钮标识
#define BST_CLOSE					0									//关闭按钮
#define BST_MAX_SIZE				1									//还原按钮
#define BST_MIN_SIZE				2									//缩小按钮

//按钮状态
#define BUT_EXIST					0x01								//按钮存在
#define BUT_NORMAL					0x02								//按钮正常
#define BUT_DISABLE					0x04								//按钮禁止

//////////////////////////////////////////////////////////////////////////////////
//过渡变量

//时间标识
#define IDI_TRANSITION				10									//过渡标识
#define TIME_TRANSITION				30									//过渡时间

//常量定义
#define MIN_TRANSITION_INDEX		0									//过渡索引
#define MAX_TRANSITION_INDEX		8									//过渡索引

//////////////////////////////////////////////////////////////////////////////////

//枚举结构
struct tagEnumChildInfo
{
	CWnd *							pWndControl;						//控制窗口
	CWnd *							pWndLayered;						//分层窗口
	CRgn *							pRegionResult;						//结果区域
};

//////////////////////////////////////////////////////////////////////////////////
//静态变量

CSkinDialogAttribute				CSkinPngDialog::m_SkinAttribute;		//资源变量


IMPLEMENT_DYNAMIC(CSkinDialog, CDialog)
BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETTINGCHANGE()
	ON_WM_WINDOWPOSCHANGED()
	ON_MESSAGE(WM_SETTEXT,OnSetTextMesage)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinDialogEx, CSkinDialog)
BEGIN_MESSAGE_MAP(CSkinDialogEx,CSkinDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CRgnDialog, CDialog)
BEGIN_MESSAGE_MAP(CRgnDialog,CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CSkinPngDialog, CDialog)
BEGIN_MESSAGE_MAP(CSkinPngDialog, CDialog)
	//系统消息
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGED()

	//鼠标消息
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()

	//自定消息
	ON_MESSAGE(WM_SETTEXT,OnSetTextMesage)

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CSkinDialog::CSkinDialog(UINT nIDTemplate, CWnd * pParentWnd) 
	: CDialog(nIDTemplate,pParentWnd), CSkinWndObject(this)
{
}

//析构函数
CSkinDialog::~CSkinDialog()
{
}

//初始化消息
BOOL CSkinDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//初始化
	InitSkinObject();
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return TRUE;
}

//激活消息
void CSkinDialog::OnActivate(UINT nState, CWnd * pWndOther, BOOL bMinimized)
{
	__super::OnActivate(nState,pWndOther,bMinimized);

	m_bActive=(nState!=WA_INACTIVE);
	DrawSkinView(NULL);

	return;
}

//激活消息
void CSkinDialog::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	__super::OnActivateApp(bActive,dwThreadID);

	m_bActive=bActive?true:false;
	DrawSkinView(NULL);

	return;
}

//鼠标消息
void CSkinDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	__super::OnLButtonDblClk(nFlags,point);
	OnLMouseDoubleEvent(point);
	return;
}

//鼠标消息
void CSkinDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	__super::OnLButtonDown(nFlags,point);
	OnLMouseDownEvent(point);
	return;
}

//鼠标消息
void CSkinDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	__super::OnLButtonUp(nFlags,point);
	OnLMouseUpEvent(point);
	return;
}

//鼠标消息
void CSkinDialog::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	__super::OnRButtonDblClk(nFlags,point);
	OnRMouseDoubleEvent(point);
	return;
}

//鼠标消息
void CSkinDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
	__super::OnRButtonDown(nFlags,point);
	OnRMouseDownEvent(point);
	return;
}

//鼠标消息
void CSkinDialog::OnRButtonUp(UINT nFlags, CPoint point)
{
	__super::OnRButtonUp(nFlags,point);
	OnRMouseUpEvent(point);
	return;
}

//鼠标消息
void CSkinDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	__super::OnMouseMove(nFlags,point);
	OnMouseMoveEvent(point);
	return;
}

//绘画消息 
void CSkinDialog::OnPaint()
{
	CPaintDC dc(this);
	DrawSkinView(&dc);
	return;
}

//位置改变
void CSkinDialog::OnWindowPosChanged(WINDOWPOS * lpwndpos)
{
	__super::OnWindowPosChanged(lpwndpos);

	//调整位置
	CRect rcClient;
	m_cbNowHotButton=255;
	m_cbNowDownButton=255;
	GetClientRect(&rcClient);
	AdjustTitleButton(rcClient.Width(),rcClient.Height());

	//重画界面
	DrawSkinView(NULL);

	return;
}

//设置改变
void CSkinDialog::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	__super::OnSettingChange(uFlags, lpszSection);

	//调整框架大小
	CSkinWndObject::OnSettingChange();

	return;
}

//绘画背景
BOOL CSkinDialog::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//控件颜色
HBRUSH CSkinDialog::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(m_SkinAttribute.m_crBackGround);
			pDC->SetTextColor(m_SkinAttribute.m_crControlTXColor);
			return m_SkinAttribute.m_brBackGround;
		}
	}
	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//标题消息
LRESULT	CSkinDialog::OnSetTextMesage(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult=DefWindowProc(WM_SETTEXT,wParam,lParam);
	DrawSkinView(NULL);
	return lResult;
}

//////////////////////////////////////////////////////////////////////////

//构造函数
CSkinDialogEx::CSkinDialogEx(UINT nIDTemplate, CWnd * pParentWnd) : CSkinDialog(nIDTemplate,pParentWnd)
{
}

//析构函数
CSkinDialogEx::~CSkinDialogEx()
{
}

//绘画边框
void CSkinDialogEx::DrawBorder(CDC * pDC)
{
	//获取位置
	CRect ClientRect;
	GetClientRect(&ClientRect);
	int nXExcursion=GetXExcursionPos();
	int nYExcursion=GetYExcursionPos();

	//创建笔画
	CPen BorderPen(PS_SOLID,1,m_SkinAttribute.m_crInsideBorder);
	CPen * pOldPen=pDC->SelectObject(&BorderPen);

	//绘画内框
	CRect rcDrawRect(nXExcursion,nYExcursion,ClientRect.Width()-2*nXExcursion,ClientRect.Height());
	pDC->SelectObject(m_SkinAttribute.m_brBackGround);
	if (m_bMaxSize==true) rcDrawRect.DeflateRect(3,3,3,2);
	else rcDrawRect.DeflateRect(3,4,2,4);
	pDC->RoundRect(&rcDrawRect,CPoint(8,8));

	//清理资源
	pDC->SelectObject(pOldPen);
	BorderPen.DeleteObject();

	return ;
}

//绘画标题
void CSkinDialogEx::DrawCaption(CDC * pDC)
{
	//绘画标题
	DrawSkinView(pDC);

	return ;
}

//绘画背景
void CSkinDialogEx::DrawBackGround(CDC * pDC)
{
	//获取位置
	CRect ClientRect;
	GetClientRect(&ClientRect);

	//绘画背景
	int nXExcursion=GetXExcursionPos();
	int nYExcursion=GetYExcursionPos();
	pDC->FillSolidRect(nXExcursion,nYExcursion,ClientRect.Width()-2*nXExcursion,4,m_SkinAttribute.m_crBackFrame);
	pDC->FillSolidRect(nXExcursion,ClientRect.Height()-8,ClientRect.Width()-2*nXExcursion,7,m_SkinAttribute.m_crBackFrame);
	pDC->FillSolidRect(nXExcursion,nYExcursion+4,12,ClientRect.Height()-nYExcursion-9,m_SkinAttribute.m_crBackFrame);
	pDC->FillSolidRect(ClientRect.Width()-nXExcursion-12,nYExcursion+4,12,ClientRect.Height()-nYExcursion-9,m_SkinAttribute.m_crBackFrame);

	return;
}

//重画消息
void CSkinDialogEx::OnPaint()
{
	CPaintDC dc(this);

	//绘画标题
	DrawCaption(&dc);

	//绘画背景
	DrawBackGround(&dc);

	//绘画边框
	DrawBorder(&dc);

	return;
}

//位置消息
void CSkinDialogEx::OnSize(UINT nType, int cx, int cy)
{
	CSkinDialog::OnSize(nType, cx, cy);

	//刷新界面
	Invalidate(FALSE);

	return;
}

//////////////////////////////////////////////////////////////////////////

//构造函数
CRgnDialog::CRgnDialog(UINT uTemplate, CWnd * pParent) : CDialog(uTemplate,pParent)
{
}

//析构函数
CRgnDialog::~CRgnDialog()
{
}

//初始化函数
BOOL CRgnDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//删除窗口标题和获取属性
	ModifyStyle(WS_CAPTION,0,SWP_DRAWFRAME);
	SetClassLong(m_hWnd,GCL_HBRBACKGROUND,NULL);

	return TRUE;
}

//重画函数
void CRgnDialog::OnPaint()
{
	CPaintDC dc(this);

	//绘画底图
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CImageHandle ImageHandle(&m_ImageBack);
	if (m_ImageBack.IsNull()==false) m_ImageBack.BitBlt(dc,0,0);

	return;
}

//加载位图
bool CRgnDialog::LoadRgnImage(HINSTANCE hInstance, UINT uBitmapID, COLORREF crTrans)
{
	m_ImageBack.SetLoadInfo(uBitmapID,hInstance);
	return CreateControlRgn(crTrans);
}

//加载位图
bool CRgnDialog::LoadRgnImage(LPCTSTR pszFileName, COLORREF crTrans)
{
	m_ImageBack.SetLoadInfo(pszFileName);
	return CreateControlRgn(crTrans);
}

//创建区域
bool CRgnDialog::CreateControlRgn(COLORREF crTrans)
{
	//加载资源
	CImageHandle ImageHandle(&m_ImageBack);

	//创建区域
	CRgn RgnControl;
	m_ImageBack.CreateImageRegion(RgnControl,crTrans);

	//设置窗口
	if (RgnControl.GetSafeHandle()!=NULL)
	{
		//移动窗口
		SetWindowRgn(RgnControl,TRUE);
		SetWindowPos(NULL,0,0,m_ImageBack.GetWidth(),m_ImageBack.GetHeight(),SWP_NOMOVE);

		//删除区域
		m_DialogRgn.DeleteObject();
		m_DialogRgn.Attach(RgnControl.Detach());

		return true;
	}

	return false;
}

//鼠标右键按下消息
void CRgnDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	__super::OnLButtonDown(nFlags, point);

	//模拟按标题
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

//背景函数
BOOL CRgnDialog::OnEraseBkgnd(CDC * pDC)
{
	Invalidate(FALSE);
	UpdateWindow();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSkinLayered, CWnd)
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

//构造函数
CSkinLayered::CSkinLayered()
{
	//设置变量
	m_pWndControl=NULL;

	return;
}

//析构函数
CSkinLayered::~CSkinLayered()
{
}

//创建窗口
VOID CSkinLayered::CreateLayered(CWnd * pWndControl, CRect & rcWindow)
{
	//效验参数
	ASSERT((pWndControl!=NULL)&&(pWndControl->m_hWnd!=NULL));
	if ((pWndControl==NULL)||(pWndControl->m_hWnd==NULL)) return;

	//设置变量
	m_pWndControl=pWndControl;

	//创建窗口
	CreateEx(WS_EX_LAYERED,TEXT("STATIC"),TEXT(""),0,rcWindow,pWndControl,0L);

	return;
}

//设置区域
VOID CSkinLayered::InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild)
{
	//效验参数
	ASSERT((pDCImage!=NULL)&&(pDCImage->m_hDC!=NULL));
	if ((pDCImage==NULL)||(pDCImage->m_hDC==NULL)) return;

	//变量定义
	BITMAP Bitmap;
	ZeroMemory(&Bitmap,sizeof(Bitmap));

	//获取图像
	CBitmap * pBitmap=pDCImage->GetCurrentBitmap();
	if (pBitmap!=NULL) pBitmap->GetBitmap(&Bitmap);

	//获取大小
	CSize SizeImage;
	SizeImage.SetSize(Bitmap.bmWidth,Bitmap.bmHeight);

	//效验大小
	ASSERT((SizeImage.cx>0)&&(SizeImage.cy>0));
	if ((SizeImage.cx==0)||(SizeImage.cy==0)) return;

	//变量定义
	BLENDFUNCTION BlendFunction;
	ZeroMemory(&BlendFunction,sizeof(BlendFunction));

	//设置参数
	BlendFunction.BlendOp=0;
	BlendFunction.BlendFlags=0;
	BlendFunction.AlphaFormat=AC_SRC_ALPHA;
	BlendFunction.SourceConstantAlpha=cbAlpha;

	//设置分层
	CPoint ImagePoint(0,0);
	CClientDC ClientDC(this);
	UpdateLayeredWindow(&ClientDC,NULL,&SizeImage,pDCImage,&ImagePoint,0L,&BlendFunction,ULW_ALPHA);

	//创建区域
	CRgn RegionResult;
	RegionResult.CreateRectRgn(0,0,SizeImage.cx,SizeImage.cy);

	//窗口排除
	if (bUnLayeredChild==true)
	{
		//变量定义
		tagEnumChildInfo EnumChildInfo;
		ZeroMemory(&EnumChildInfo,sizeof(EnumChildInfo));

		//设置变量
		EnumChildInfo.pWndLayered=this;
		EnumChildInfo.pWndControl=m_pWndControl;
		EnumChildInfo.pRegionResult=&RegionResult;

		//枚举窗口
		ASSERT(m_pWndControl->GetSafeHwnd()!=NULL);
		EnumChildWindows(m_pWndControl->m_hWnd,EnumChildProc,(LPARAM)&EnumChildInfo);
	}

	//区域排除
	if (rcUnLayered.IsRectEmpty()==FALSE)
	{
		//创建区域
		CRgn RegionUnLayered;
		RegionUnLayered.CreateRoundRectRgn(rcUnLayered.left,rcUnLayered.top,rcUnLayered.right+1,rcUnLayered.bottom+1,PointRound.x,PointRound.y);

		//合并区域
		RegionResult.CombineRgn(&RegionResult,&RegionUnLayered,RGN_DIFF);
	}

	//设置区域
	SetWindowRgn(RegionResult,TRUE);

	return;
}

//设置区域
VOID CSkinLayered::InitLayeredArea(CPngImage & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild)
{
	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(Image.GetWidth(),Image.GetHeight(),32);

	//绘画界面
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//绘画界面
	ASSERT(pBufferDC!=NULL);
	if (pBufferDC!=NULL) Image.DrawImage(pBufferDC,0,0);

	//创建分层
	InitLayeredArea(pBufferDC,cbAlpha,rcUnLayered,PointRound,bUnLayeredChild);

	return;
}

//关闭消息
VOID CSkinLayered::OnClose()
{
	//投递消息
	if (m_pWndControl!=NULL)
	{
		m_pWndControl->PostMessage(WM_CLOSE);
	}

	return;
}

//焦点消息
VOID CSkinLayered::OnSetFocus(CWnd * pOldWnd)
{
	//设置焦点
	if (m_pWndControl!=NULL)
	{
		m_pWndControl->SetFocus();
	}
}

//枚举函数
BOOL CALLBACK CSkinLayered::EnumChildProc(HWND hWndChild, LPARAM lParam)
{
	//获取位置
	CRect rcWindow;
	::GetWindowRect(hWndChild,&rcWindow);

	//创建区域
	if ((rcWindow.Width()>0)&&(rcWindow.Height()>0))
	{
		//变量定义
		ASSERT(lParam!=0L);
		tagEnumChildInfo * pEnumChildInfo=(tagEnumChildInfo *)lParam;

		//窗口判断
		HWND hWndParent=::GetParent(hWndChild);
		if (hWndParent!=pEnumChildInfo->pWndControl->GetSafeHwnd())
		{
			return TRUE;
		}

		//转换位置
		ASSERT(pEnumChildInfo->pWndControl!=NULL);
		pEnumChildInfo->pWndControl->ScreenToClient(&rcWindow);

		//创建区域
		CRgn RgnChild;
		RgnChild.CreateRectRgn(rcWindow.left,rcWindow.top,rcWindow.right,rcWindow.bottom);

		//合并区域
		ASSERT(pEnumChildInfo->pRegionResult!=NULL);
		pEnumChildInfo->pRegionResult->CombineRgn(pEnumChildInfo->pRegionResult,&RgnChild,RGN_DIFF);
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////
static ULONG_PTR g_lGdiPlusToken=0L;

//构造函数
CSkinDialogAttribute::CSkinDialogAttribute()
{
	GdiplusStartupInput StartupInput;
	GdiplusStartup(&g_lGdiPlusToken,&StartupInput,NULL);


	//设置颜色
	m_crTitleText=RGB(0,0,0);
	m_crTitleFrame=RGB(0,0,0);
	m_crBackGround=RGB(0,0,0);
	m_crControlText=RGB(0,0,0);

	//变量定义
	tagEncircleResource EncircleResource;
	HINSTANCE hResInstance=GetModuleHandle(SKIN_CONTROL_DLL_NAME);

	//环绕资源
	EncircleResource.pszImageTL=TEXT("SKIN_WND_TL");
	EncircleResource.pszImageTM=TEXT("SKIN_WND_TM");
	EncircleResource.pszImageTR=TEXT("SKIN_WND_TR");
	EncircleResource.pszImageML=TEXT("SKIN_WND_ML");
	EncircleResource.pszImageMR=TEXT("SKIN_WND_MR");
	EncircleResource.pszImageBL=TEXT("SKIN_WND_BL");
	EncircleResource.pszImageBM=TEXT("SKIN_WND_BM");
	EncircleResource.pszImageBR=TEXT("SKIN_WND_BR");
	m_PNGEncircleFrame.InitEncircleResource(EncircleResource,hResInstance);

	//获取大小
	CBitImage ImageButtonClose;
	ImageButtonClose.LoadFromResource(hResInstance,IDB_SKIN_WND_CLOSE);
	m_SizeButton.SetSize(ImageButtonClose.GetWidth()/5,ImageButtonClose.GetHeight());

	//设置视图
	m_PNGEncircleFrame.GetEncircleInfo(m_EncircleInfoFrame);

	//设置视图
	m_EncircleInfoView.nBBorder=8;
	m_EncircleInfoView.nTBorder=m_EncircleInfoFrame.nTBorder;
	m_EncircleInfoView.nLBorder=m_EncircleInfoFrame.nLBorder;
	m_EncircleInfoView.nRBorder=m_EncircleInfoFrame.nRBorder;

	//标题颜色
	m_crTitleText=RGB(0,0,0);
	m_crTitleFrame=RGB(200,200,200);

	//控件颜色
	m_crControlText=RGB(10,10,10);
	m_crBackGround=RGB(250,250,250);

	//设置资源
	m_brBackGround.DeleteObject();
	m_brBackGround.CreateSolidBrush(m_crBackGround);

	return;
}

//析构函数
CSkinDialogAttribute::~CSkinDialogAttribute()
{
	GdiplusShutdown(g_lGdiPlusToken);
	//销毁资源
	if (m_brBackGround.GetSafeHandle()!=NULL)
	{
		m_brBackGround.DeleteObject();
	}

	return;
}

//配置资源
bool CSkinDialogAttribute::Initialization(CSkinRenderManager * pSkinRenderManager)
{
	//标题颜色
	m_crTitleText=RGB(0,0,0);
	m_crTitleFrame=RGB(200,200,200);

	//控件颜色
	m_crControlText=RGB(10,10,10);
	m_crBackGround=RGB(250,250,250);

	//设置资源
	m_brBackGround.DeleteObject();
	m_brBackGround.CreateSolidBrush(m_crBackGround);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//构造函数
CSkinPngDialog::CSkinPngDialog(UINT nIDTemplate, CWnd * pParentWnd) : CDialog(nIDTemplate,pParentWnd)
{
	//过渡状态
	m_bTransition=false;
	ZeroMemory(m_wImageIndex,sizeof(m_wImageIndex));

	//按钮状态
	m_cbNowHotIndex=INVALID_BYTE;
	m_cbNowHitIndex=INVALID_BYTE;
	ZeroMemory(m_cbButtonState,sizeof(m_cbButtonState));

	return;
}

//析构函数
CSkinPngDialog::~CSkinPngDialog()
{
}

//配置函数
BOOL CSkinPngDialog::OnInitDialog()
{
	__super::OnInitDialog();

	//设置属性
	ModifyStyle(WS_CAPTION,0,SWP_DRAWFRAME);

	//按钮状态
	m_cbNowHotIndex=INVALID_BYTE;
	m_cbNowHitIndex=INVALID_BYTE;
	ZeroMemory(m_cbButtonState,sizeof(m_cbButtonState));

	//属性判断
	LONG lWindowStyte=GetWindowLongPtr(m_hWnd,GWL_STYLE);
	if (lWindowStyte&WS_SYSMENU)
	{
		//设置按钮
		m_cbButtonState[BST_CLOSE]=BUT_EXIST|BUT_NORMAL;
		m_cbButtonState[BST_MAX_SIZE]=BUT_EXIST|((lWindowStyte&WS_MAXIMIZEBOX)?BUT_NORMAL:BUT_DISABLE);
		m_cbButtonState[BST_MIN_SIZE]=BUT_EXIST|(((lWindowStyte&WS_MINIMIZEBOX)||(GetParent()==NULL))?BUT_NORMAL:BUT_DISABLE);

		//按钮调整
		if (((m_cbButtonState[BST_MAX_SIZE]&BUT_DISABLE)!=0)&&((m_cbButtonState[BST_MIN_SIZE]&BUT_DISABLE)!=0))
		{
			m_cbButtonState[BST_MAX_SIZE]=0;
			m_cbButtonState[BST_MIN_SIZE]=0;
		}
	}

	//创建分层
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	m_SkinLayered.CreateLayered(this,rcWindow);

	//调整资源
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(),rcClient.Height());

	return FALSE;
}

//绘画消息
VOID CSkinPngDialog::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	return;
}

//调整资源
VOID CSkinPngDialog::RectifyResource(INT nWidth, INT nHeight)
{
	//设置变量
	m_cbNowHotIndex=INVALID_BYTE;
	m_cbNowHitIndex=INVALID_BYTE;

	//过渡状态
	m_bTransition=false;
	ZeroMemory(m_wImageIndex,sizeof(m_wImageIndex));

	//调整判断
	if ((nWidth!=0)&&(nHeight!=0))
	{
		//调整按钮
		CaleTitleButton(nWidth,nHeight);

		//框架位置
		CRect rcFrame;
		rcFrame.SetRect(SHADOW_CX,SHADOW_CY,nWidth-SHADOW_CX,nHeight-SHADOW_CY);

		//窗口区域
		CRgn RegionWindow;
		RegionWindow.CreateRoundRectRgn(rcFrame.left,rcFrame.top,rcFrame.right+1,rcFrame.bottom+1,ROUND_CX,ROUND_CY);

		//设置区域
		SetWindowRgn(RegionWindow,TRUE);

		//分层窗口
		if (m_SkinLayered.m_hWnd!=NULL)
		{
			//建立缓冲
			CImage ImageBuffer;
			ImageBuffer.Create(nWidth,nHeight,32);

			//创建 DC
			CImageDC ImageDC(ImageBuffer);
			CDC * pBufferDC=CDC::FromHandle(ImageDC);

			//绘画界面
			DrawControlView(pBufferDC,nWidth,nHeight);

			//更新分层
			m_SkinLayered.InitLayeredArea(pBufferDC,255,rcFrame,CPoint(ROUND_CX,ROUND_CX),false);
		}
	}

	return;
}

//调整按钮
VOID CSkinPngDialog::CaleTitleButton(INT nWidth, INT nHeight)
{
	//调整按钮
	for (INT i=0;i<CountArray(m_rcButton);i++)
	{
		//计算偏移
		INT nYPos=10;
		INT nXPos=nWidth-(m_SkinAttribute.m_SizeButton.cx+2)*(i+1)-12;

		//设置位置
		m_rcButton[i].top=nYPos;
		m_rcButton[i].left=nXPos;
		m_rcButton[i].right=nXPos+m_SkinAttribute.m_SizeButton.cx;
		m_rcButton[i].bottom=nYPos+m_SkinAttribute.m_SizeButton.cy;
	}

	return;
}

//绘画阴影
VOID CSkinPngDialog::DrawControlView(CDC * pDC, INT nWdith, INT nHeight)
{
	//设置缓冲
	pDC->SetBkMode(TRANSPARENT);
	pDC->SelectObject(CSkinResourceManager::GetDefaultFont());

	//框架位置
	CRect rcFrame;
	rcFrame.SetRect(0,0,nWdith,nHeight);

	//视图位置
	CRect rcClientView;
	rcClientView.top=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
	rcClientView.left=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
	rcClientView.right=nWdith-m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
	rcClientView.bottom=nHeight-m_SkinAttribute.m_EncircleInfoFrame.nBBorder;

	//绘画视图
	pDC->FillSolidRect(&rcClientView,m_SkinAttribute.m_crBackGround);

	//绘画框架
	m_SkinAttribute.m_PNGEncircleFrame.DrawEncircleFrame(pDC,rcFrame);

	//绘画标题
	DrawSystemTitle(pDC,nWdith,nHeight);
	DrawSystemButton(pDC,nWdith,nHeight);

	//绘画界面
	OnDrawClientArea(pDC,nWdith,nHeight);

	return;
}

//绘画标题
VOID CSkinPngDialog::DrawSystemTitle(CDC * pDC, INT nWdith, INT nHeight)
{
	//获取标题
	CString strTitle;
	GetWindowText(strTitle);

	//加载图标
	CPngImage ImageLogo;
	ImageLogo.LoadImage(GetModuleHandle(SKIN_CONTROL_DLL_NAME),TEXT("SKIN_WND_LOGO"));

	//绘画图标
	if (ImageLogo.IsNull()==false)
	{
		ImageLogo.DrawImage(pDC,11,6);
	}

	//绘画标题
	if (strTitle.IsEmpty()==false)
	{
		//计算区域
		CRect rcTitle;
		rcTitle.SetRect(48,16,nWdith-95,28);

		//变量定义
		INT nXMove[8]={1,1,1,0,-1,-1,-1,0};
		INT nYMove[8]={-1,0,1,1,1,0,-1,-1};

		//设置环境
		pDC->SetTextColor(m_SkinAttribute.m_crTitleFrame);

		//绘画边框
		for (INT i=0;i<CountArray(nXMove);i++)
		{
			//计算位置
			CRect rcTitleFrame;
			rcTitleFrame.top=rcTitle.top+nYMove[i];
			rcTitleFrame.left=rcTitle.left+nXMove[i];
			rcTitleFrame.right=rcTitle.right+nXMove[i];
			rcTitleFrame.bottom=rcTitle.bottom+nYMove[i];

			//绘画字符
			pDC->DrawText(strTitle,&rcTitleFrame,DT_SINGLELINE|DT_END_ELLIPSIS|DT_VCENTER);
		}

		//绘画文字
		pDC->SetTextColor(m_SkinAttribute.m_crTitleText);
		pDC->DrawText(strTitle,&rcTitle,DT_SINGLELINE|DT_END_ELLIPSIS|DT_VCENTER);
	}

	return;
}

//绘画按钮
VOID CSkinPngDialog::DrawSystemButton(CDC * pDC, INT nWdith, INT nHeight)
{
	//变量定义
	HINSTANCE hResInstance=GetModuleHandle(SKIN_CONTROL_DLL_NAME);

	//绘画按钮
	for (BYTE nIndex=0;nIndex<3;nIndex++)
	{
		if ((m_cbButtonState[nIndex]&BUT_EXIST)!=0)
		{
			//变量定义
			CBitImage ImageButton;

			//加载按钮
			switch (nIndex)
			{
			case BST_CLOSE:		//关闭按钮
				{
					ImageButton.LoadFromResource(hResInstance,IDB_SKIN_WND_CLOSE);
					break;
				}
			case BST_MIN_SIZE:	//最小按钮
				{
					ImageButton.LoadFromResource(hResInstance,IDB_SKIN_WND_MIN);
					break;
				}
			case BST_MAX_SIZE:	//还原按钮
				{
					ImageButton.LoadFromResource(hResInstance,(IsZoomed()==FALSE)?IDB_SKIN_WND_MAX:IDB_SKIN_WND_RESORE);
					break;
				}
			}

			//变量定义
			INT nDrawPos=0;
			BYTE cbButtonState=m_cbButtonState[nIndex];
			CSize SizeImageButton=m_SkinAttribute.m_SizeButton;

			//绘画位置
			if (cbButtonState&BUT_DISABLE) nDrawPos=m_SkinAttribute.m_SizeButton.cx*4;
			else if (m_cbNowHitIndex==nIndex) nDrawPos=m_SkinAttribute.m_SizeButton.cx;
			else if (m_cbNowHotIndex==nIndex) nDrawPos=m_SkinAttribute.m_SizeButton.cx*2;

			//状态判断
			bool bTransitionDraw=false;
			if ((m_cbNowHotIndex==nIndex)&&(m_wImageIndex[nIndex]<MAX_TRANSITION_INDEX)) bTransitionDraw=true;
			if ((m_cbNowHotIndex!=nIndex)&&(m_wImageIndex[nIndex]>MIN_TRANSITION_INDEX)) bTransitionDraw=true;

			//绘画背景
			if ((bTransitionDraw==true)&&((cbButtonState&BUT_DISABLE)==0)&&(m_cbNowHitIndex!=nIndex))
			{
				//创建缓冲
				CBitImage BufferImage;
				BufferImage.Create(SizeImageButton.cx,SizeImageButton.cy,16);

				//获取设备
				HDC hBufferDC=BufferImage.GetDC();
				CDC * pBufferDC=CDC::FromHandle(hBufferDC);

				//绘画底图
				if (m_wImageIndex[nIndex]<MAX_TRANSITION_INDEX)
				{
					ImageButton.BitBlt(hBufferDC,0,0,SizeImageButton.cx,SizeImageButton.cy,0,0,SRCCOPY);
				}

				//绘画过渡
				if (m_wImageIndex[nIndex]>MIN_TRANSITION_INDEX)
				{
					BYTE cbAlphaDepth=m_wImageIndex[nIndex]*255/MAX_TRANSITION_INDEX;
					ImageButton.AlphaDrawImage(pBufferDC,0,0,SizeImageButton.cx,SizeImageButton.cy,
						SizeImageButton.cx*2,0,SizeImageButton.cx,SizeImageButton.cy,cbAlphaDepth);
				}

				//绘画界面
				BufferImage.BitBlt(pDC->m_hDC,m_rcButton[nIndex].left,m_rcButton[nIndex].top,SizeImageButton.cx,SizeImageButton.cy,0,0);

				//释放资源
				BufferImage.ReleaseDC();
			}
			else
			{
				//常规界面
				ImageButton.BitBlt(pDC->m_hDC,m_rcButton[nIndex].left,m_rcButton[nIndex].top,SizeImageButton.cx,SizeImageButton.cy,nDrawPos,0);
			}
		}
	}

	return;
}

//按键测试
UINT CSkinPngDialog::ControlHitTest(CPoint Point)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//获取信息
	tagEncircleInfo EncircleInfo;
	m_SkinAttribute.m_PNGEncircleFrame.GetEncircleInfo(EncircleInfo);

	//关闭按钮
	if ((m_cbButtonState[BST_CLOSE]&BUT_EXIST)&&(m_rcButton[BST_CLOSE].PtInRect(Point)))
	{
		return HTCLOSE;
	}

	//最大按钮
	if ((m_cbButtonState[BST_MAX_SIZE]&BUT_EXIST)&&(m_rcButton[BST_MAX_SIZE].PtInRect(Point)))
	{
		return HTMAXBUTTON;
	}

	//最小按钮
	if ((m_cbButtonState[BST_MIN_SIZE]&BUT_EXIST)&&(m_rcButton[BST_MIN_SIZE].PtInRect(Point)))
	{
		return HTMINBUTTON;
	}

	//标题测试
	if (Point.y<=m_SkinAttribute.m_EncircleInfoView.nTBorder) return HTCAPTION;

	return HTCLIENT;
}

//鼠标消息
VOID CSkinPngDialog::OnMouseMove(UINT nFlags, CPoint Point)
{
	//判断按下
	if (m_cbNowHitIndex!=INVALID_BYTE) return;

	//按钮搜索
	for (INT i=0;i<CountArray(m_cbButtonState);i++)
	{
		if ((m_cbButtonState[i]&BUT_EXIST)&&(m_rcButton[i].PtInRect(Point)))
		{
			//当前判断
			if (m_cbNowHotIndex==i) return;

			//设置状态
			if (m_cbNowHotIndex!=INVALID_BYTE)
			{
				m_cbButtonState[m_cbNowHotIndex]|=BUT_NORMAL;
				m_cbNowHotIndex=INVALID_BYTE;
			}

			//清除状态
			if ((m_cbButtonState[i]&BUT_EXIST)&&(!(m_cbButtonState[i]&BUT_DISABLE)))
			{
				m_cbNowHotIndex=i;
				m_cbButtonState[m_cbNowHotIndex]&=~BUT_NORMAL;
			}

			//过渡设置
			if (m_bTransition==false)
			{
				//设置变量
				m_bTransition=true;

				//设置时间
				SetTimer(IDI_TRANSITION,TIME_TRANSITION,NULL);
			}

			return;
		}
	}

	//清理焦点
	if (m_cbNowHotIndex!=INVALID_BYTE)
	{
		//设置变量
		m_cbButtonState[m_cbNowHotIndex]|=BUT_NORMAL;
		m_cbNowHotIndex=INVALID_BYTE;

		//过渡设置
		if (m_bTransition==false)
		{
			//设置变量
			m_bTransition=true;

			//设置时间
			SetTimer(IDI_TRANSITION,TIME_TRANSITION,NULL);
		}
	}

	return;
}

//鼠标消息
VOID CSkinPngDialog::OnLButtonDown(UINT nFlags, CPoint Point)
{
	//设置焦点
	SetFocus();

	//按钮测试
	UINT nHitCode=ControlHitTest(Point);

	//按钮处理
	if (m_cbNowHitIndex==INVALID_BYTE)
	{
		//关闭按钮
		if ((nHitCode==HTCLOSE)&&(m_cbButtonState[BST_CLOSE]&BUT_EXIST)&&((m_cbButtonState[BST_CLOSE]&BUT_DISABLE)==0))
		{
			m_cbNowHitIndex=BST_CLOSE;
		}

		//最大按钮
		if ((nHitCode==HTMAXBUTTON)&&(m_cbButtonState[BST_MAX_SIZE]&BUT_EXIST)&&((m_cbButtonState[BST_MAX_SIZE]&BUT_DISABLE)==0))
		{
			m_cbNowHitIndex=BST_MAX_SIZE;
		}

		//最小按钮
		if ((nHitCode==HTMINBUTTON)&&(m_cbButtonState[BST_MIN_SIZE]&BUT_EXIST)&&((m_cbButtonState[BST_MIN_SIZE]&BUT_DISABLE)==0))
		{
			m_cbNowHitIndex=BST_MIN_SIZE;
		}

		//结果判断
		if (m_cbNowHitIndex!=INVALID_BYTE)
		{
			//设置状态
			SetCapture();
			RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

			return;
		}
	}

	//模拟标题
	if ((IsZoomed()==FALSE)&&(nHitCode==HTCAPTION))
	{
		//模拟标题
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(Point.x,Point.y));

		return;
	}

	__super::OnNcLButtonDown(nFlags,Point);
}

//绘画背景
BOOL CSkinPngDialog::OnEraseBkgnd(CDC * pDC)
{
	//获取位置
	CRect rcClient;
	GetClientRect(&rcClient);

	//建立缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//创建 DC
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//绘画界面
	DrawControlView(pBufferDC,rcClient.Width(),rcClient.Height());

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//时间消息
VOID CSkinPngDialog::OnTimer(UINT_PTR nIDEvent)
{
	//过渡变量
	if (nIDEvent==IDI_TRANSITION)
	{
		//变量定义
		bool bWantContinue=false;

		//按钮搜索
		for (BYTE i=0;i<3;i++)
		{
			//盘旋过渡
			if ((m_cbNowHotIndex==i)&&(m_wImageIndex[i]<MAX_TRANSITION_INDEX))
			{
				m_wImageIndex[i]++;
			}

			//常态过渡
			if ((m_cbNowHotIndex!=i)&&(m_wImageIndex[i]>MIN_TRANSITION_INDEX))
			{
				m_wImageIndex[i]--;
			}

			//状态判断
			if ((m_wImageIndex[i]>MIN_TRANSITION_INDEX)&&(m_wImageIndex[i]<MAX_TRANSITION_INDEX))
			{
				bWantContinue=true;
			}
		}

		//删除时间
		if (bWantContinue==false)
		{
			//设置变量
			m_bTransition=false;

			//删除时间
			KillTimer(IDI_TRANSITION);
		}

		//获取位置
		CRect rcClient;
		GetClientRect(&rcClient);

		//绘画按钮
		CClientDC ClientDC(this);
		DrawSystemButton(&ClientDC,rcClient.Width(),rcClient.Height());

		return;
	}

	__super::OnTimer(nIDEvent);
}

//位置消息
VOID CSkinPngDialog::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType,cx,cy);

	//调整资源
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyResource(rcClient.Width(),rcClient.Height());

	return;
}

//显示消息
VOID CSkinPngDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
	__super::OnShowWindow(bShow, nStatus);

	//显示分层
	if (m_SkinLayered.m_hWnd!=NULL)
	{
		m_SkinLayered.ShowWindow((bShow==FALSE)?SW_HIDE:SW_SHOW);
	}

	return;
}

//位置改变
VOID CSkinPngDialog::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
	__super::OnWindowPosChanged(lpWndPos);

	//移动分层
	if ((m_SkinLayered.m_hWnd!=NULL)&&(lpWndPos->cx>=0)&&(lpWndPos->cy>0))
	{
		m_SkinLayered.SetWindowPos(NULL,lpWndPos->x,lpWndPos->y,lpWndPos->cx,lpWndPos->cy,SWP_NOZORDER);
	}

	return;
}

//鼠标消息
VOID CSkinPngDialog::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//按钮处理
	if (m_cbNowHitIndex!=INVALID_BYTE)
	{
		//锁定释放
		ReleaseCapture();

		//按钮测试
		UINT nHitCode=ControlHitTest(Point);

		//关闭按钮
		if ((nHitCode==HTCLOSE)&&(m_cbNowHitIndex==BST_CLOSE))
		{
			PostMessage(WM_CLOSE,0,0);
		}

		//最大按钮
		if ((nHitCode==HTMAXBUTTON)&&(m_cbNowHitIndex==BST_MAX_SIZE))
		{
			ShowWindow((IsZoomed()==FALSE)?SW_MAXIMIZE:SW_RESTORE);
		}

		//最小按钮
		if ((nHitCode==HTMINBUTTON)&&(m_cbNowHitIndex==BST_MIN_SIZE))
		{
			ShowWindow(SW_MINIMIZE);
		}

		//设置数据
		m_cbNowHitIndex=INVALID_BYTE;

		//更新界面
		RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);
	}

	return;
}

//控件颜色
HBRUSH CSkinPngDialog::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_SkinAttribute.m_crControlText);
			return m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//标题消息
LRESULT	CSkinPngDialog::OnSetTextMesage(WPARAM wParam, LPARAM lParam)
{
	//默认调用
	LRESULT lResult=DefWindowProc(WM_SETTEXT,wParam,lParam);

	//更新界面
	RedrawWindow(NULL,NULL,RDW_FRAME|RDW_INVALIDATE|RDW_ERASE|RDW_ERASENOW);

	return lResult;
}

//////////////////////////////////////////////////////////////////////////////////





















