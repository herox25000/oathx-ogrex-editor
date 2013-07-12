#include "Stdafx.h"
#include "Resource.h"
#include "MiddleFrameControl.h"


//////////////////////////////////////////////////////////////////////////////////

//构造函数
CMiddleFrameControl::CMiddleFrameControl()
{
	//设置区域
	m_rcControl.SetRect(0,0,0,0);

	//设置变量
	m_bAfficheTitle = true;
}

//析构函数
CMiddleFrameControl::~CMiddleFrameControl()
{
}

//设置区域
VOID CMiddleFrameControl::SetControlRect(INT nLeftPos,INT nTopPos,INT nRightPos,INT nBottomPos)
{
	//设置区域
	m_rcControl.SetRect(nLeftPos,nTopPos,nRightPos,nBottomPos);

	return;
}

//绘画背景
BOOL CMiddleFrameControl::OnDrawFrameControl(CDC * pDC)
{
	//变量定义
	HINSTANCE hInstance=AfxGetInstanceHandle();
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	//加载资源
	CBitImage ImageTitleL;
	CBitImage ImageTitleM;
	CBitImage ImageTitleR;
	ImageTitleL.LoadFromResource(hInstance,IDB_MID_FRAME_TL);
	ImageTitleM.LoadFromResource(hInstance,IDB_MID_FRAME_TM);
	ImageTitleR.LoadFromResource(hInstance,IDB_MID_FRAME_TR);

	//渲染资源
	pSkinRenderManager->RenderImage(ImageTitleL);
	pSkinRenderManager->RenderImage(ImageTitleM);
	pSkinRenderManager->RenderImage(ImageTitleR);

	//绘画背景
	ImageTitleL.BitBlt(*pDC,m_rcControl.left,m_rcControl.top);

	//填充中间
	for (INT nXPos=ImageTitleL.GetWidth();nXPos<m_rcControl.Width()-ImageTitleM.GetWidth();nXPos+=ImageTitleM.GetWidth())
	{
		ImageTitleM.BitBlt(*pDC,m_rcControl.left+nXPos,m_rcControl.top);
	}

	//绘画背景
	ImageTitleR.BitBlt(*pDC,m_rcControl.left+m_rcControl.Width()-ImageTitleR.GetWidth(),m_rcControl.top);

	//绘画标题
	if(m_bAfficheTitle==true)
	{
		CPngImage ImageTitle;
		ImageTitle.LoadImage(AfxGetInstanceHandle(),TEXT("USER_INFO_TITLE"));
		ImageTitle.DrawImage(pDC,m_rcControl.left+88,m_rcControl.top+9);
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////
