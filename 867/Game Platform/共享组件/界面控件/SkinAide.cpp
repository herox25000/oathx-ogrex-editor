#include "StdAfx.h"
#include "Resource.h"
#include "SkinAide.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CSkinAide::CSkinAide()
{
}

//析构函数
CSkinAide::~CSkinAide()
{
}

//环绕信息
bool CSkinAide::GetEncircleInfo(tagEncircleInfo & EncircleInfo, tagEncircleImage & EncircleImage)
{
	//加载资源
	tagEncircleHandle EncircleHandle;
	EncircleHandle.ImageHandleML.AttachResource(&EncircleImage.ImageML);
	EncircleHandle.ImageHandleMR.AttachResource(&EncircleImage.ImageMR);
	EncircleHandle.ImageHandleTM.AttachResource(&EncircleImage.ImageTM);
	EncircleHandle.ImageHandleBM.AttachResource(&EncircleImage.ImageBM);

	//获取信息
	EncircleInfo.nLBorder=EncircleImage.ImageML.GetWidth();
	EncircleInfo.nRBorder=EncircleImage.ImageMR.GetWidth();
	EncircleInfo.nTBorder=EncircleImage.ImageTM.GetHeight();
	EncircleInfo.nBBorder=EncircleImage.ImageBM.GetHeight();

	return true;
}

//资源标识
bool CSkinAide::SetEncircleResource(tagEncircleImage & EncircleImage, tagEncircleResource & EncircleResource, HINSTANCE hResInstance)
{
	//设置变量
	EncircleImage.ImageTL.SetLoadInfo(EncircleResource.pszImageTL);//,hResInstance
	EncircleImage.ImageTM.SetLoadInfo(EncircleResource.pszImageTM);//,hResInstance
	EncircleImage.ImageTR.SetLoadInfo(EncircleResource.pszImageTR);//,hResInstance
	EncircleImage.ImageML.SetLoadInfo(EncircleResource.pszImageML);//,hResInstance
	EncircleImage.ImageMR.SetLoadInfo(EncircleResource.pszImageMR);//,hResInstance
	EncircleImage.ImageBL.SetLoadInfo(EncircleResource.pszImageBL);//,hResInstance
	EncircleImage.ImageBM.SetLoadInfo(EncircleResource.pszImageBM);//,hResInstance
	EncircleImage.ImageBR.SetLoadInfo(EncircleResource.pszImageBR);//,hResInstance

	return true;
}

//绘画环绕
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage)
{
	//构造信息
	tagEncircleHandle EncircleHandle;
	EncircleHandle.ImageHandleML.AttachResource(&EncircleImage.ImageML);
	EncircleHandle.ImageHandleMR.AttachResource(&EncircleImage.ImageMR);
	EncircleHandle.ImageHandleTL.AttachResource(&EncircleImage.ImageTL);
	EncircleHandle.ImageHandleTM.AttachResource(&EncircleImage.ImageTM);
	EncircleHandle.ImageHandleTR.AttachResource(&EncircleImage.ImageTR);
	EncircleHandle.ImageHandleBL.AttachResource(&EncircleImage.ImageBL);
	EncircleHandle.ImageHandleBM.AttachResource(&EncircleImage.ImageBM);
	EncircleHandle.ImageHandleBR.AttachResource(&EncircleImage.ImageBR);

	//绘画环绕
	DrawEncircleFrame(pDC,rcEncircle,EncircleHandle);

	return true;
}

//绘画环绕
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle)
{
	//变量定义
	INT nXTerminate=0;
	INT nYTerminate=0;

	//获取位置
	CSize SizeImageTL,SizeImageTR,SizeImageBL,SizeImageBR;
	SizeImageTL.SetSize(EncircleHandle.ImageHandleTL->GetWidth(),EncircleHandle.ImageHandleTL->GetHeight());
	SizeImageTR.SetSize(EncircleHandle.ImageHandleTR->GetWidth(),EncircleHandle.ImageHandleTR->GetHeight());
	SizeImageBL.SetSize(EncircleHandle.ImageHandleBL->GetWidth(),EncircleHandle.ImageHandleBL->GetHeight());
	SizeImageBR.SetSize(EncircleHandle.ImageHandleBR->GetWidth(),EncircleHandle.ImageHandleBR->GetHeight());

	//获取位置
	CSize SizeImageMR,SizeImageML,SizeImageTM,SizeImageBM;
	SizeImageMR.SetSize(EncircleHandle.ImageHandleMR->GetWidth(),EncircleHandle.ImageHandleMR->GetHeight());
	SizeImageML.SetSize(EncircleHandle.ImageHandleML->GetWidth(),EncircleHandle.ImageHandleML->GetHeight());
	SizeImageTM.SetSize(EncircleHandle.ImageHandleTM->GetWidth(),EncircleHandle.ImageHandleTM->GetHeight());
	SizeImageBM.SetSize(EncircleHandle.ImageHandleBM->GetWidth(),EncircleHandle.ImageHandleBM->GetHeight());

	//绘画上边
	nXTerminate=rcEncircle.right-SizeImageTR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageTL.cx;nXPos<nXTerminate;nXPos+=SizeImageTM.cx)
	{
		EncircleHandle.ImageHandleTM->BitBlt(pDC->m_hDC,nXPos,rcEncircle.top,__min(nXTerminate-nXPos,SizeImageTM.cx),SizeImageTM.cy,0,0);
	}

	//绘画下边
	nXTerminate=rcEncircle.right-SizeImageBR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageBL.cx;nXPos<nXTerminate;nXPos+=SizeImageBM.cx)
	{
		EncircleHandle.ImageHandleBM->BitBlt(pDC->m_hDC,nXPos,rcEncircle.bottom-SizeImageBM.cy,__min(nXTerminate-nXPos,SizeImageBM.cx),SizeImageBM.cy,0,0);
	}

	//绘画左边
	nYTerminate=rcEncircle.bottom-SizeImageBL.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTL.cy;nYPos<nYTerminate;nYPos+=SizeImageML.cy)
	{
		EncircleHandle.ImageHandleML->BitBlt(pDC->m_hDC,rcEncircle.left,nYPos,SizeImageML.cx,__min(nYTerminate-nYPos,SizeImageML.cy),0,0);
	}

	//绘画右边
	nYTerminate=rcEncircle.bottom-SizeImageBR.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTR.cy;nYPos<nYTerminate;nYPos+=SizeImageMR.cy)
	{
		EncircleHandle.ImageHandleMR->BitBlt(pDC->m_hDC,rcEncircle.right-SizeImageMR.cx,nYPos,SizeImageMR.cx,__min(nYTerminate-nYPos,SizeImageMR.cy),0,0);
	}

	//绘画四角
	EncircleHandle.ImageHandleTL->BitBlt(pDC->m_hDC,rcEncircle.left,rcEncircle.top);
	EncircleHandle.ImageHandleTR->BitBlt(pDC->m_hDC,rcEncircle.right-SizeImageTR.cx,rcEncircle.top);
	EncircleHandle.ImageHandleBL->BitBlt(pDC->m_hDC,rcEncircle.left,rcEncircle.bottom-SizeImageBL.cy);
	EncircleHandle.ImageHandleBR->BitBlt(pDC->m_hDC,rcEncircle.right-SizeImageBR.cx,rcEncircle.bottom-SizeImageBR.cy);

	return true;
}

//绘画环绕
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage, COLORREF crTrans)
{
	//构造信息
	tagEncircleHandle EncircleHandle;
	EncircleHandle.ImageHandleML.AttachResource(&EncircleImage.ImageML);
	EncircleHandle.ImageHandleMR.AttachResource(&EncircleImage.ImageMR);
	EncircleHandle.ImageHandleTL.AttachResource(&EncircleImage.ImageTL);
	EncircleHandle.ImageHandleTM.AttachResource(&EncircleImage.ImageTM);
	EncircleHandle.ImageHandleTR.AttachResource(&EncircleImage.ImageTR);
	EncircleHandle.ImageHandleBL.AttachResource(&EncircleImage.ImageBL);
	EncircleHandle.ImageHandleBM.AttachResource(&EncircleImage.ImageBM);
	EncircleHandle.ImageHandleBR.AttachResource(&EncircleImage.ImageBR);

	//绘画环绕
	DrawEncircleFrame(pDC,rcEncircle,EncircleHandle,crTrans);

	return true;
}

//绘画环绕
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle, COLORREF crTrans)
{
	//变量定义
	INT nXTerminate=0;
	INT nYTerminate=0;

	//获取位置
	CSize SizeImageTL,SizeImageTR,SizeImageBL,SizeImageBR;
	SizeImageTL.SetSize(EncircleHandle.ImageHandleTL->GetWidth(),EncircleHandle.ImageHandleTL->GetHeight());
	SizeImageTR.SetSize(EncircleHandle.ImageHandleTR->GetWidth(),EncircleHandle.ImageHandleTR->GetHeight());
	SizeImageBL.SetSize(EncircleHandle.ImageHandleBL->GetWidth(),EncircleHandle.ImageHandleBL->GetHeight());
	SizeImageBR.SetSize(EncircleHandle.ImageHandleBR->GetWidth(),EncircleHandle.ImageHandleBR->GetHeight());

	//获取位置
	CSize SizeImageMR,SizeImageML,SizeImageTM,SizeImageBM;
	SizeImageMR.SetSize(EncircleHandle.ImageHandleMR->GetWidth(),EncircleHandle.ImageHandleMR->GetHeight());
	SizeImageML.SetSize(EncircleHandle.ImageHandleML->GetWidth(),EncircleHandle.ImageHandleML->GetHeight());
	SizeImageTM.SetSize(EncircleHandle.ImageHandleTM->GetWidth(),EncircleHandle.ImageHandleTM->GetHeight());
	SizeImageBM.SetSize(EncircleHandle.ImageHandleBM->GetWidth(),EncircleHandle.ImageHandleBM->GetHeight());

	//绘画上边
	nXTerminate=rcEncircle.right-SizeImageTR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageTL.cx;nXPos<nXTerminate;nXPos+=SizeImageTM.cx)
	{
		EncircleHandle.ImageHandleTM->AlphaDrawImage(pDC,nXPos,rcEncircle.top,__min(nXTerminate-nXPos,SizeImageTM.cx),SizeImageTM.cy,0,0,crTrans);
	}

	//绘画下边
	nXTerminate=rcEncircle.right-SizeImageBR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageBL.cx;nXPos<nXTerminate;nXPos+=SizeImageBM.cx)
	{
		EncircleHandle.ImageHandleBM->AlphaDrawImage(pDC,nXPos,rcEncircle.bottom-SizeImageBM.cy,__min(nXTerminate-nXPos,SizeImageBM.cx),SizeImageBM.cy,0,0,crTrans);
	}

	//绘画左边
	nYTerminate=rcEncircle.bottom-SizeImageBL.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTL.cy;nYPos<nYTerminate;nYPos+=SizeImageML.cy)
	{
		EncircleHandle.ImageHandleML->AlphaDrawImage(pDC,rcEncircle.left,nYPos,SizeImageML.cx,__min(nYTerminate-nYPos,SizeImageML.cy),0,0,crTrans);
	}

	//绘画右边
	nYTerminate=rcEncircle.bottom-SizeImageBR.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTR.cy;nYPos<nYTerminate;nYPos+=SizeImageMR.cy)
	{
		EncircleHandle.ImageHandleMR->AlphaDrawImage(pDC,rcEncircle.right-SizeImageMR.cx,nYPos,SizeImageMR.cx,__min(nYTerminate-nYPos,SizeImageMR.cy),0,0,crTrans);
	}

	//绘画四角
	EncircleHandle.ImageHandleTL->AlphaDrawImage(pDC,rcEncircle.left,rcEncircle.top,crTrans);
	EncircleHandle.ImageHandleTR->AlphaDrawImage(pDC,rcEncircle.right-SizeImageTR.cx,rcEncircle.top,crTrans);
	EncircleHandle.ImageHandleBL->AlphaDrawImage(pDC,rcEncircle.left,rcEncircle.bottom-SizeImageBL.cy,crTrans);
	EncircleHandle.ImageHandleBR->AlphaDrawImage(pDC,rcEncircle.right-SizeImageBR.cx,rcEncircle.bottom-SizeImageBR.cy,crTrans);

	return true;
}

//计算位置
bool CSkinAide::CaleWindowRect(CRect & rcEncircle, tagEncircleInfo & EncircleInfo, CRect & rcControl)
{
	//计算位置
	rcControl.top=rcEncircle.top+EncircleInfo.nTBorder;
	rcControl.left=rcEncircle.left+EncircleInfo.nLBorder;
	rcControl.right=rcEncircle.right-EncircleInfo.nRBorder;
	rcControl.bottom=rcEncircle.bottom-EncircleInfo.nBBorder;

	return true;
}

//计算位置
bool CSkinAide::CaleWindowRect(CRect & rcEncircle, tagEncircleImage & EncircleImage, CRect & rcControl)
{
	//获取信息
	tagEncircleInfo EncircleInfo;
	GetEncircleInfo(EncircleInfo,EncircleImage);

	//计算位置
	rcControl.top=rcEncircle.top+EncircleInfo.nTBorder;
	rcControl.left=rcEncircle.left+EncircleInfo.nLBorder;
	rcControl.right=rcEncircle.right-EncircleInfo.nRBorder;
	rcControl.bottom=rcEncircle.bottom-EncircleInfo.nBBorder;

	return true;
}

//计算位置
bool CSkinAide::CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo, CRect & rcControl)
{
	//计算位置
	rcControl.top=nYPos+EncircleInfo.nTBorder;
	rcControl.left=nXPos+EncircleInfo.nLBorder;
	rcControl.right=nXPos+nWidth-EncircleInfo.nRBorder;
	rcControl.bottom=nYPos+nHeight-EncircleInfo.nBBorder;

	return true;
}

//计算位置
bool CSkinAide::CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage, CRect & rcControl)
{
	//获取信息
	tagEncircleInfo EncircleInfo;
	GetEncircleInfo(EncircleInfo,EncircleImage);

	//计算位置
	rcControl.top=nYPos+EncircleInfo.nTBorder;
	rcControl.left=nXPos+EncircleInfo.nLBorder;
	rcControl.right=nXPos+nWidth-EncircleInfo.nRBorder;
	rcControl.bottom=nYPos+nHeight-EncircleInfo.nBBorder;

	return true;
}

//环绕调整
bool CSkinAide::SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleInfo & EncircleInfo)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleInfo,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return true;
}

//环绕调整
bool CSkinAide::SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleImage & EncircleImage)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleImage,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//环绕调整
bool CSkinAide::SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleInfo,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//环绕调整
bool CSkinAide::SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleImage,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//环绕调整
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleInfo & EncircleInfo)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleInfo,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//环绕调整
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleImage & EncircleImage)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleImage,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//环绕调整
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleInfo,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//环绕调整
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleImage,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}



//////////////////////////////////////////////////////////////////////////////////

//构造函数
CEncirclePNG::CEncirclePNG()
{
	//设置变量
	m_hResInstance=NULL;
	ZeroMemory(&m_EncircleInfo,sizeof(m_EncircleInfo));
	ZeroMemory(&m_EncircleResource,sizeof(m_EncircleResource));

	return;
}

//析构函数
CEncirclePNG::~CEncirclePNG()
{
}

//加载资源
bool CEncirclePNG::LoadEncircleImage(tagEncirclePNG & EncircleImage)
{
	//加载资源
	if (m_hResInstance==NULL)
	{
		//文件加载
		EncircleImage.ImageTL.LoadImage(m_EncircleResource.pszImageTL);
		EncircleImage.ImageTM.LoadImage(m_EncircleResource.pszImageTM);
		EncircleImage.ImageTR.LoadImage(m_EncircleResource.pszImageTR);
		EncircleImage.ImageML.LoadImage(m_EncircleResource.pszImageML);
		EncircleImage.ImageMR.LoadImage(m_EncircleResource.pszImageMR);
		EncircleImage.ImageBL.LoadImage(m_EncircleResource.pszImageBL);
		EncircleImage.ImageBM.LoadImage(m_EncircleResource.pszImageBM);
		EncircleImage.ImageBR.LoadImage(m_EncircleResource.pszImageBR);
	}
	else
	{
		//资源加载
		EncircleImage.ImageTL.LoadImage(m_hResInstance,m_EncircleResource.pszImageTL);
		EncircleImage.ImageTM.LoadImage(m_hResInstance,m_EncircleResource.pszImageTM);
		EncircleImage.ImageTR.LoadImage(m_hResInstance,m_EncircleResource.pszImageTR);
		EncircleImage.ImageML.LoadImage(m_hResInstance,m_EncircleResource.pszImageML);
		EncircleImage.ImageMR.LoadImage(m_hResInstance,m_EncircleResource.pszImageMR);
		EncircleImage.ImageBL.LoadImage(m_hResInstance,m_EncircleResource.pszImageBL);
		EncircleImage.ImageBM.LoadImage(m_hResInstance,m_EncircleResource.pszImageBM);
		EncircleImage.ImageBR.LoadImage(m_hResInstance,m_EncircleResource.pszImageBR);
	}

	return true;
}

//默认资源
bool CEncirclePNG::InitDefaultResource()
{
	//变量定义
	tagEncircleResource EncircleResource;
	ZeroMemory(&EncircleResource,sizeof(EncircleResource));

	//设置变量
	EncircleResource.pszImageTL=MAKEINTRESOURCE(IDB_ENCIRCLE_TL);
	EncircleResource.pszImageTM=MAKEINTRESOURCE(IDB_ENCIRCLE_TM);
	EncircleResource.pszImageTR=MAKEINTRESOURCE(IDB_ENCIRCLE_TR);
	EncircleResource.pszImageML=MAKEINTRESOURCE(IDB_ENCIRCLE_ML);
	EncircleResource.pszImageMR=MAKEINTRESOURCE(IDB_ENCIRCLE_MR);
	EncircleResource.pszImageBL=MAKEINTRESOURCE(IDB_ENCIRCLE_BL);
	EncircleResource.pszImageBM=MAKEINTRESOURCE(IDB_ENCIRCLE_BM);
	EncircleResource.pszImageBR=MAKEINTRESOURCE(IDB_ENCIRCLE_BR);

	//设置信息
	return InitEncircleResource(EncircleResource,GetModuleHandle(SKIN_CONTROL_DLL_NAME));
}

//设置信息
bool CEncirclePNG::InitEncircleResource(tagEncircleResource & EncircleResource, HINSTANCE hResInstance)
{
	//变量定义
	CPngImage ImageTM;
	CPngImage ImageML;
	CPngImage ImageMR;
	CPngImage ImageBM;

	//设置变量
	m_hResInstance=hResInstance;
	m_EncircleResource=EncircleResource;

	//加载资源
	if (hResInstance==NULL)
	{
		//文件加载
		ImageTM.LoadImage(m_EncircleResource.pszImageTM);
		ImageML.LoadImage(m_EncircleResource.pszImageML);
		ImageMR.LoadImage(m_EncircleResource.pszImageMR);
		ImageBM.LoadImage(m_EncircleResource.pszImageBM);
	}
	else
	{
		//资源加载
		ImageTM.LoadImage(hResInstance,m_EncircleResource.pszImageTM);
		ImageML.LoadImage(hResInstance,m_EncircleResource.pszImageML);
		ImageMR.LoadImage(hResInstance,m_EncircleResource.pszImageMR);
		ImageBM.LoadImage(hResInstance,m_EncircleResource.pszImageBM);
	}

	//效验资源
	ASSERT(ImageTM.IsNull()==false);
	ASSERT(ImageML.IsNull()==false);
	ASSERT(ImageMR.IsNull()==false);
	ASSERT(ImageBM.IsNull()==false);

	//获取信息
	m_EncircleInfo.nLBorder=ImageML.GetWidth();
	m_EncircleInfo.nRBorder=ImageMR.GetWidth();
	m_EncircleInfo.nTBorder=ImageTM.GetHeight();
	m_EncircleInfo.nBBorder=ImageBM.GetHeight();

	return true;
}

//绘画环绕
bool CEncirclePNG::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle)
{
	//变量定义
	INT nXTerminate=0;
	INT nYTerminate=0;

	//加载资源
	tagEncirclePNG EncircleImage;
	LoadEncircleImage(EncircleImage);

	//资源处理
	PreDrawEncircleImage(EncircleImage);

	//获取位置
	CSize SizeImageTL,SizeImageTR,SizeImageBL,SizeImageBR;
	SizeImageTL.SetSize(EncircleImage.ImageTL.GetWidth(),EncircleImage.ImageTL.GetHeight());
	SizeImageTR.SetSize(EncircleImage.ImageTR.GetWidth(),EncircleImage.ImageTR.GetHeight());
	SizeImageBL.SetSize(EncircleImage.ImageBL.GetWidth(),EncircleImage.ImageBL.GetHeight());
	SizeImageBR.SetSize(EncircleImage.ImageBR.GetWidth(),EncircleImage.ImageBR.GetHeight());

	//获取位置
	CSize SizeImageMR,SizeImageML,SizeImageTM,SizeImageBM;
	SizeImageMR.SetSize(EncircleImage.ImageMR.GetWidth(),EncircleImage.ImageMR.GetHeight());
	SizeImageML.SetSize(EncircleImage.ImageML.GetWidth(),EncircleImage.ImageML.GetHeight());
	SizeImageTM.SetSize(EncircleImage.ImageTM.GetWidth(),EncircleImage.ImageTM.GetHeight());
	SizeImageBM.SetSize(EncircleImage.ImageBM.GetWidth(),EncircleImage.ImageBM.GetHeight());

	//绘画上边
	nXTerminate=rcEncircle.right-SizeImageTR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageTL.cx;nXPos<nXTerminate;nXPos+=SizeImageTM.cx)
	{
		EncircleImage.ImageTM.DrawImage(pDC,nXPos,rcEncircle.top,__min(nXTerminate-nXPos,SizeImageTM.cx),SizeImageTM.cy,0,0);
	}

	//绘画下边
	nXTerminate=rcEncircle.right-SizeImageBR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageBL.cx;nXPos<nXTerminate;nXPos+=SizeImageBM.cx)
	{
		EncircleImage.ImageBM.DrawImage(pDC,nXPos,rcEncircle.bottom-SizeImageBM.cy,__min(nXTerminate-nXPos,SizeImageBM.cx),SizeImageBM.cy,0,0);
	}

	//绘画左边
	nYTerminate=rcEncircle.bottom-SizeImageBL.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTL.cy;nYPos<nYTerminate;nYPos+=SizeImageML.cy)
	{
		EncircleImage.ImageML.DrawImage(pDC,rcEncircle.left,nYPos,SizeImageML.cx,__min(nYTerminate-nYPos,SizeImageML.cy),0,0);
	}

	//绘画右边
	nYTerminate=rcEncircle.bottom-SizeImageBR.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTR.cy;nYPos<nYTerminate;nYPos+=SizeImageMR.cy)
	{
		EncircleImage.ImageMR.DrawImage(pDC,rcEncircle.right-SizeImageMR.cx,nYPos,SizeImageMR.cx,__min(nYTerminate-nYPos,SizeImageMR.cy),0,0);
	}

	//绘画四角
	EncircleImage.ImageTL.DrawImage(pDC,rcEncircle.left,rcEncircle.top);
	EncircleImage.ImageTR.DrawImage(pDC,rcEncircle.right-SizeImageTR.cx,rcEncircle.top);
	EncircleImage.ImageBL.DrawImage(pDC,rcEncircle.left,rcEncircle.bottom-SizeImageBL.cy);
	EncircleImage.ImageBR.DrawImage(pDC,rcEncircle.right-SizeImageBR.cx,rcEncircle.bottom-SizeImageBR.cy);

	return true;
}

//获取位置
bool CEncirclePNG::GetEncircleInfo(tagEncircleInfo & EncircleInfo)
{
	//设置变量
	EncircleInfo=m_EncircleInfo;

	return true;
}

//获取位置
bool CEncirclePNG::GetEncircleRect(CRect & rcEncircleBorad, CRect & rcControl)
{
	//计算位置
	rcControl.top=rcEncircleBorad.top+m_EncircleInfo.nTBorder;
	rcControl.left=rcEncircleBorad.left+m_EncircleInfo.nLBorder;
	rcControl.right=rcEncircleBorad.right-m_EncircleInfo.nRBorder;
	rcControl.bottom=rcEncircleBorad.bottom-m_EncircleInfo.nBBorder;

	return true;
}

//环绕调整
bool CEncirclePNG::SetWindowPos(CWnd * pWnd, CRect & rcEncircleBorad)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		GetEncircleRect(rcEncircleBorad,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//环绕调整
bool CEncirclePNG::DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircleBorad)
{
	//调整窗口
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//构造位置
		CRect rcControl;
		GetEncircleRect(rcEncircleBorad,rcControl);

		//调整窗口
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////
