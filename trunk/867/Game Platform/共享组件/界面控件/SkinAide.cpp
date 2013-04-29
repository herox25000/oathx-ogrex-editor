#include "StdAfx.h"
#include "Resource.h"
#include "SkinAide.h"

//////////////////////////////////////////////////////////////////////////

//���캯��
CSkinAide::CSkinAide()
{
}

//��������
CSkinAide::~CSkinAide()
{
}

//������Ϣ
bool CSkinAide::GetEncircleInfo(tagEncircleInfo & EncircleInfo, tagEncircleImage & EncircleImage)
{
	//������Դ
	tagEncircleHandle EncircleHandle;
	EncircleHandle.ImageHandleML.AttachResource(&EncircleImage.ImageML);
	EncircleHandle.ImageHandleMR.AttachResource(&EncircleImage.ImageMR);
	EncircleHandle.ImageHandleTM.AttachResource(&EncircleImage.ImageTM);
	EncircleHandle.ImageHandleBM.AttachResource(&EncircleImage.ImageBM);

	//��ȡ��Ϣ
	EncircleInfo.nLBorder=EncircleImage.ImageML.GetWidth();
	EncircleInfo.nRBorder=EncircleImage.ImageMR.GetWidth();
	EncircleInfo.nTBorder=EncircleImage.ImageTM.GetHeight();
	EncircleInfo.nBBorder=EncircleImage.ImageBM.GetHeight();

	return true;
}

//��Դ��ʶ
bool CSkinAide::SetEncircleResource(tagEncircleImage & EncircleImage, tagEncircleResource & EncircleResource, HINSTANCE hResInstance)
{
	//���ñ���
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

//�滭����
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage)
{
	//������Ϣ
	tagEncircleHandle EncircleHandle;
	EncircleHandle.ImageHandleML.AttachResource(&EncircleImage.ImageML);
	EncircleHandle.ImageHandleMR.AttachResource(&EncircleImage.ImageMR);
	EncircleHandle.ImageHandleTL.AttachResource(&EncircleImage.ImageTL);
	EncircleHandle.ImageHandleTM.AttachResource(&EncircleImage.ImageTM);
	EncircleHandle.ImageHandleTR.AttachResource(&EncircleImage.ImageTR);
	EncircleHandle.ImageHandleBL.AttachResource(&EncircleImage.ImageBL);
	EncircleHandle.ImageHandleBM.AttachResource(&EncircleImage.ImageBM);
	EncircleHandle.ImageHandleBR.AttachResource(&EncircleImage.ImageBR);

	//�滭����
	DrawEncircleFrame(pDC,rcEncircle,EncircleHandle);

	return true;
}

//�滭����
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle)
{
	//��������
	INT nXTerminate=0;
	INT nYTerminate=0;

	//��ȡλ��
	CSize SizeImageTL,SizeImageTR,SizeImageBL,SizeImageBR;
	SizeImageTL.SetSize(EncircleHandle.ImageHandleTL->GetWidth(),EncircleHandle.ImageHandleTL->GetHeight());
	SizeImageTR.SetSize(EncircleHandle.ImageHandleTR->GetWidth(),EncircleHandle.ImageHandleTR->GetHeight());
	SizeImageBL.SetSize(EncircleHandle.ImageHandleBL->GetWidth(),EncircleHandle.ImageHandleBL->GetHeight());
	SizeImageBR.SetSize(EncircleHandle.ImageHandleBR->GetWidth(),EncircleHandle.ImageHandleBR->GetHeight());

	//��ȡλ��
	CSize SizeImageMR,SizeImageML,SizeImageTM,SizeImageBM;
	SizeImageMR.SetSize(EncircleHandle.ImageHandleMR->GetWidth(),EncircleHandle.ImageHandleMR->GetHeight());
	SizeImageML.SetSize(EncircleHandle.ImageHandleML->GetWidth(),EncircleHandle.ImageHandleML->GetHeight());
	SizeImageTM.SetSize(EncircleHandle.ImageHandleTM->GetWidth(),EncircleHandle.ImageHandleTM->GetHeight());
	SizeImageBM.SetSize(EncircleHandle.ImageHandleBM->GetWidth(),EncircleHandle.ImageHandleBM->GetHeight());

	//�滭�ϱ�
	nXTerminate=rcEncircle.right-SizeImageTR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageTL.cx;nXPos<nXTerminate;nXPos+=SizeImageTM.cx)
	{
		EncircleHandle.ImageHandleTM->BitBlt(pDC->m_hDC,nXPos,rcEncircle.top,__min(nXTerminate-nXPos,SizeImageTM.cx),SizeImageTM.cy,0,0);
	}

	//�滭�±�
	nXTerminate=rcEncircle.right-SizeImageBR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageBL.cx;nXPos<nXTerminate;nXPos+=SizeImageBM.cx)
	{
		EncircleHandle.ImageHandleBM->BitBlt(pDC->m_hDC,nXPos,rcEncircle.bottom-SizeImageBM.cy,__min(nXTerminate-nXPos,SizeImageBM.cx),SizeImageBM.cy,0,0);
	}

	//�滭���
	nYTerminate=rcEncircle.bottom-SizeImageBL.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTL.cy;nYPos<nYTerminate;nYPos+=SizeImageML.cy)
	{
		EncircleHandle.ImageHandleML->BitBlt(pDC->m_hDC,rcEncircle.left,nYPos,SizeImageML.cx,__min(nYTerminate-nYPos,SizeImageML.cy),0,0);
	}

	//�滭�ұ�
	nYTerminate=rcEncircle.bottom-SizeImageBR.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTR.cy;nYPos<nYTerminate;nYPos+=SizeImageMR.cy)
	{
		EncircleHandle.ImageHandleMR->BitBlt(pDC->m_hDC,rcEncircle.right-SizeImageMR.cx,nYPos,SizeImageMR.cx,__min(nYTerminate-nYPos,SizeImageMR.cy),0,0);
	}

	//�滭�Ľ�
	EncircleHandle.ImageHandleTL->BitBlt(pDC->m_hDC,rcEncircle.left,rcEncircle.top);
	EncircleHandle.ImageHandleTR->BitBlt(pDC->m_hDC,rcEncircle.right-SizeImageTR.cx,rcEncircle.top);
	EncircleHandle.ImageHandleBL->BitBlt(pDC->m_hDC,rcEncircle.left,rcEncircle.bottom-SizeImageBL.cy);
	EncircleHandle.ImageHandleBR->BitBlt(pDC->m_hDC,rcEncircle.right-SizeImageBR.cx,rcEncircle.bottom-SizeImageBR.cy);

	return true;
}

//�滭����
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleImage & EncircleImage, COLORREF crTrans)
{
	//������Ϣ
	tagEncircleHandle EncircleHandle;
	EncircleHandle.ImageHandleML.AttachResource(&EncircleImage.ImageML);
	EncircleHandle.ImageHandleMR.AttachResource(&EncircleImage.ImageMR);
	EncircleHandle.ImageHandleTL.AttachResource(&EncircleImage.ImageTL);
	EncircleHandle.ImageHandleTM.AttachResource(&EncircleImage.ImageTM);
	EncircleHandle.ImageHandleTR.AttachResource(&EncircleImage.ImageTR);
	EncircleHandle.ImageHandleBL.AttachResource(&EncircleImage.ImageBL);
	EncircleHandle.ImageHandleBM.AttachResource(&EncircleImage.ImageBM);
	EncircleHandle.ImageHandleBR.AttachResource(&EncircleImage.ImageBR);

	//�滭����
	DrawEncircleFrame(pDC,rcEncircle,EncircleHandle,crTrans);

	return true;
}

//�滭����
bool CSkinAide::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle, tagEncircleHandle & EncircleHandle, COLORREF crTrans)
{
	//��������
	INT nXTerminate=0;
	INT nYTerminate=0;

	//��ȡλ��
	CSize SizeImageTL,SizeImageTR,SizeImageBL,SizeImageBR;
	SizeImageTL.SetSize(EncircleHandle.ImageHandleTL->GetWidth(),EncircleHandle.ImageHandleTL->GetHeight());
	SizeImageTR.SetSize(EncircleHandle.ImageHandleTR->GetWidth(),EncircleHandle.ImageHandleTR->GetHeight());
	SizeImageBL.SetSize(EncircleHandle.ImageHandleBL->GetWidth(),EncircleHandle.ImageHandleBL->GetHeight());
	SizeImageBR.SetSize(EncircleHandle.ImageHandleBR->GetWidth(),EncircleHandle.ImageHandleBR->GetHeight());

	//��ȡλ��
	CSize SizeImageMR,SizeImageML,SizeImageTM,SizeImageBM;
	SizeImageMR.SetSize(EncircleHandle.ImageHandleMR->GetWidth(),EncircleHandle.ImageHandleMR->GetHeight());
	SizeImageML.SetSize(EncircleHandle.ImageHandleML->GetWidth(),EncircleHandle.ImageHandleML->GetHeight());
	SizeImageTM.SetSize(EncircleHandle.ImageHandleTM->GetWidth(),EncircleHandle.ImageHandleTM->GetHeight());
	SizeImageBM.SetSize(EncircleHandle.ImageHandleBM->GetWidth(),EncircleHandle.ImageHandleBM->GetHeight());

	//�滭�ϱ�
	nXTerminate=rcEncircle.right-SizeImageTR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageTL.cx;nXPos<nXTerminate;nXPos+=SizeImageTM.cx)
	{
		EncircleHandle.ImageHandleTM->AlphaDrawImage(pDC,nXPos,rcEncircle.top,__min(nXTerminate-nXPos,SizeImageTM.cx),SizeImageTM.cy,0,0,crTrans);
	}

	//�滭�±�
	nXTerminate=rcEncircle.right-SizeImageBR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageBL.cx;nXPos<nXTerminate;nXPos+=SizeImageBM.cx)
	{
		EncircleHandle.ImageHandleBM->AlphaDrawImage(pDC,nXPos,rcEncircle.bottom-SizeImageBM.cy,__min(nXTerminate-nXPos,SizeImageBM.cx),SizeImageBM.cy,0,0,crTrans);
	}

	//�滭���
	nYTerminate=rcEncircle.bottom-SizeImageBL.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTL.cy;nYPos<nYTerminate;nYPos+=SizeImageML.cy)
	{
		EncircleHandle.ImageHandleML->AlphaDrawImage(pDC,rcEncircle.left,nYPos,SizeImageML.cx,__min(nYTerminate-nYPos,SizeImageML.cy),0,0,crTrans);
	}

	//�滭�ұ�
	nYTerminate=rcEncircle.bottom-SizeImageBR.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTR.cy;nYPos<nYTerminate;nYPos+=SizeImageMR.cy)
	{
		EncircleHandle.ImageHandleMR->AlphaDrawImage(pDC,rcEncircle.right-SizeImageMR.cx,nYPos,SizeImageMR.cx,__min(nYTerminate-nYPos,SizeImageMR.cy),0,0,crTrans);
	}

	//�滭�Ľ�
	EncircleHandle.ImageHandleTL->AlphaDrawImage(pDC,rcEncircle.left,rcEncircle.top,crTrans);
	EncircleHandle.ImageHandleTR->AlphaDrawImage(pDC,rcEncircle.right-SizeImageTR.cx,rcEncircle.top,crTrans);
	EncircleHandle.ImageHandleBL->AlphaDrawImage(pDC,rcEncircle.left,rcEncircle.bottom-SizeImageBL.cy,crTrans);
	EncircleHandle.ImageHandleBR->AlphaDrawImage(pDC,rcEncircle.right-SizeImageBR.cx,rcEncircle.bottom-SizeImageBR.cy,crTrans);

	return true;
}

//����λ��
bool CSkinAide::CaleWindowRect(CRect & rcEncircle, tagEncircleInfo & EncircleInfo, CRect & rcControl)
{
	//����λ��
	rcControl.top=rcEncircle.top+EncircleInfo.nTBorder;
	rcControl.left=rcEncircle.left+EncircleInfo.nLBorder;
	rcControl.right=rcEncircle.right-EncircleInfo.nRBorder;
	rcControl.bottom=rcEncircle.bottom-EncircleInfo.nBBorder;

	return true;
}

//����λ��
bool CSkinAide::CaleWindowRect(CRect & rcEncircle, tagEncircleImage & EncircleImage, CRect & rcControl)
{
	//��ȡ��Ϣ
	tagEncircleInfo EncircleInfo;
	GetEncircleInfo(EncircleInfo,EncircleImage);

	//����λ��
	rcControl.top=rcEncircle.top+EncircleInfo.nTBorder;
	rcControl.left=rcEncircle.left+EncircleInfo.nLBorder;
	rcControl.right=rcEncircle.right-EncircleInfo.nRBorder;
	rcControl.bottom=rcEncircle.bottom-EncircleInfo.nBBorder;

	return true;
}

//����λ��
bool CSkinAide::CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo, CRect & rcControl)
{
	//����λ��
	rcControl.top=nYPos+EncircleInfo.nTBorder;
	rcControl.left=nXPos+EncircleInfo.nLBorder;
	rcControl.right=nXPos+nWidth-EncircleInfo.nRBorder;
	rcControl.bottom=nYPos+nHeight-EncircleInfo.nBBorder;

	return true;
}

//����λ��
bool CSkinAide::CaleWindowRect(INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage, CRect & rcControl)
{
	//��ȡ��Ϣ
	tagEncircleInfo EncircleInfo;
	GetEncircleInfo(EncircleInfo,EncircleImage);

	//����λ��
	rcControl.top=nYPos+EncircleInfo.nTBorder;
	rcControl.left=nXPos+EncircleInfo.nLBorder;
	rcControl.right=nXPos+nWidth-EncircleInfo.nRBorder;
	rcControl.bottom=nYPos+nHeight-EncircleInfo.nBBorder;

	return true;
}

//���Ƶ���
bool CSkinAide::SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleInfo & EncircleInfo)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleInfo,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return true;
}

//���Ƶ���
bool CSkinAide::SetWindowPos(CWnd * pWnd, CRect & rcEncircle, tagEncircleImage & EncircleImage)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleImage,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//���Ƶ���
bool CSkinAide::SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleInfo,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//���Ƶ���
bool CSkinAide::SetWindowPos(CWnd * pWnd, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleImage,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//���Ƶ���
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleInfo & EncircleInfo)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleInfo,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//���Ƶ���
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircle, tagEncircleImage & EncircleImage)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(rcEncircle,EncircleImage,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//���Ƶ���
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleInfo & EncircleInfo)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleInfo,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//���Ƶ���
bool CSkinAide::DeferWindowPos(CWnd * pWnd, HDWP hDwp, INT nXPos, INT nYPos, INT nWidth, INT nHeight, tagEncircleImage & EncircleImage)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		CaleWindowRect(nXPos,nYPos,nWidth,nHeight,EncircleImage,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}



//////////////////////////////////////////////////////////////////////////////////

//���캯��
CEncirclePNG::CEncirclePNG()
{
	//���ñ���
	m_hResInstance=NULL;
	ZeroMemory(&m_EncircleInfo,sizeof(m_EncircleInfo));
	ZeroMemory(&m_EncircleResource,sizeof(m_EncircleResource));

	return;
}

//��������
CEncirclePNG::~CEncirclePNG()
{
}

//������Դ
bool CEncirclePNG::LoadEncircleImage(tagEncirclePNG & EncircleImage)
{
	//������Դ
	if (m_hResInstance==NULL)
	{
		//�ļ�����
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
		//��Դ����
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

//Ĭ����Դ
bool CEncirclePNG::InitDefaultResource()
{
	//��������
	tagEncircleResource EncircleResource;
	ZeroMemory(&EncircleResource,sizeof(EncircleResource));

	//���ñ���
	EncircleResource.pszImageTL=MAKEINTRESOURCE(IDB_ENCIRCLE_TL);
	EncircleResource.pszImageTM=MAKEINTRESOURCE(IDB_ENCIRCLE_TM);
	EncircleResource.pszImageTR=MAKEINTRESOURCE(IDB_ENCIRCLE_TR);
	EncircleResource.pszImageML=MAKEINTRESOURCE(IDB_ENCIRCLE_ML);
	EncircleResource.pszImageMR=MAKEINTRESOURCE(IDB_ENCIRCLE_MR);
	EncircleResource.pszImageBL=MAKEINTRESOURCE(IDB_ENCIRCLE_BL);
	EncircleResource.pszImageBM=MAKEINTRESOURCE(IDB_ENCIRCLE_BM);
	EncircleResource.pszImageBR=MAKEINTRESOURCE(IDB_ENCIRCLE_BR);

	//������Ϣ
	return InitEncircleResource(EncircleResource,GetModuleHandle(SKIN_CONTROL_DLL_NAME));
}

//������Ϣ
bool CEncirclePNG::InitEncircleResource(tagEncircleResource & EncircleResource, HINSTANCE hResInstance)
{
	//��������
	CPngImage ImageTM;
	CPngImage ImageML;
	CPngImage ImageMR;
	CPngImage ImageBM;

	//���ñ���
	m_hResInstance=hResInstance;
	m_EncircleResource=EncircleResource;

	//������Դ
	if (hResInstance==NULL)
	{
		//�ļ�����
		ImageTM.LoadImage(m_EncircleResource.pszImageTM);
		ImageML.LoadImage(m_EncircleResource.pszImageML);
		ImageMR.LoadImage(m_EncircleResource.pszImageMR);
		ImageBM.LoadImage(m_EncircleResource.pszImageBM);
	}
	else
	{
		//��Դ����
		ImageTM.LoadImage(hResInstance,m_EncircleResource.pszImageTM);
		ImageML.LoadImage(hResInstance,m_EncircleResource.pszImageML);
		ImageMR.LoadImage(hResInstance,m_EncircleResource.pszImageMR);
		ImageBM.LoadImage(hResInstance,m_EncircleResource.pszImageBM);
	}

	//Ч����Դ
	ASSERT(ImageTM.IsNull()==false);
	ASSERT(ImageML.IsNull()==false);
	ASSERT(ImageMR.IsNull()==false);
	ASSERT(ImageBM.IsNull()==false);

	//��ȡ��Ϣ
	m_EncircleInfo.nLBorder=ImageML.GetWidth();
	m_EncircleInfo.nRBorder=ImageMR.GetWidth();
	m_EncircleInfo.nTBorder=ImageTM.GetHeight();
	m_EncircleInfo.nBBorder=ImageBM.GetHeight();

	return true;
}

//�滭����
bool CEncirclePNG::DrawEncircleFrame(CDC * pDC, CRect & rcEncircle)
{
	//��������
	INT nXTerminate=0;
	INT nYTerminate=0;

	//������Դ
	tagEncirclePNG EncircleImage;
	LoadEncircleImage(EncircleImage);

	//��Դ����
	PreDrawEncircleImage(EncircleImage);

	//��ȡλ��
	CSize SizeImageTL,SizeImageTR,SizeImageBL,SizeImageBR;
	SizeImageTL.SetSize(EncircleImage.ImageTL.GetWidth(),EncircleImage.ImageTL.GetHeight());
	SizeImageTR.SetSize(EncircleImage.ImageTR.GetWidth(),EncircleImage.ImageTR.GetHeight());
	SizeImageBL.SetSize(EncircleImage.ImageBL.GetWidth(),EncircleImage.ImageBL.GetHeight());
	SizeImageBR.SetSize(EncircleImage.ImageBR.GetWidth(),EncircleImage.ImageBR.GetHeight());

	//��ȡλ��
	CSize SizeImageMR,SizeImageML,SizeImageTM,SizeImageBM;
	SizeImageMR.SetSize(EncircleImage.ImageMR.GetWidth(),EncircleImage.ImageMR.GetHeight());
	SizeImageML.SetSize(EncircleImage.ImageML.GetWidth(),EncircleImage.ImageML.GetHeight());
	SizeImageTM.SetSize(EncircleImage.ImageTM.GetWidth(),EncircleImage.ImageTM.GetHeight());
	SizeImageBM.SetSize(EncircleImage.ImageBM.GetWidth(),EncircleImage.ImageBM.GetHeight());

	//�滭�ϱ�
	nXTerminate=rcEncircle.right-SizeImageTR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageTL.cx;nXPos<nXTerminate;nXPos+=SizeImageTM.cx)
	{
		EncircleImage.ImageTM.DrawImage(pDC,nXPos,rcEncircle.top,__min(nXTerminate-nXPos,SizeImageTM.cx),SizeImageTM.cy,0,0);
	}

	//�滭�±�
	nXTerminate=rcEncircle.right-SizeImageBR.cx;
	for (INT nXPos=rcEncircle.left+SizeImageBL.cx;nXPos<nXTerminate;nXPos+=SizeImageBM.cx)
	{
		EncircleImage.ImageBM.DrawImage(pDC,nXPos,rcEncircle.bottom-SizeImageBM.cy,__min(nXTerminate-nXPos,SizeImageBM.cx),SizeImageBM.cy,0,0);
	}

	//�滭���
	nYTerminate=rcEncircle.bottom-SizeImageBL.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTL.cy;nYPos<nYTerminate;nYPos+=SizeImageML.cy)
	{
		EncircleImage.ImageML.DrawImage(pDC,rcEncircle.left,nYPos,SizeImageML.cx,__min(nYTerminate-nYPos,SizeImageML.cy),0,0);
	}

	//�滭�ұ�
	nYTerminate=rcEncircle.bottom-SizeImageBR.cy;
	for (INT nYPos=rcEncircle.top+SizeImageTR.cy;nYPos<nYTerminate;nYPos+=SizeImageMR.cy)
	{
		EncircleImage.ImageMR.DrawImage(pDC,rcEncircle.right-SizeImageMR.cx,nYPos,SizeImageMR.cx,__min(nYTerminate-nYPos,SizeImageMR.cy),0,0);
	}

	//�滭�Ľ�
	EncircleImage.ImageTL.DrawImage(pDC,rcEncircle.left,rcEncircle.top);
	EncircleImage.ImageTR.DrawImage(pDC,rcEncircle.right-SizeImageTR.cx,rcEncircle.top);
	EncircleImage.ImageBL.DrawImage(pDC,rcEncircle.left,rcEncircle.bottom-SizeImageBL.cy);
	EncircleImage.ImageBR.DrawImage(pDC,rcEncircle.right-SizeImageBR.cx,rcEncircle.bottom-SizeImageBR.cy);

	return true;
}

//��ȡλ��
bool CEncirclePNG::GetEncircleInfo(tagEncircleInfo & EncircleInfo)
{
	//���ñ���
	EncircleInfo=m_EncircleInfo;

	return true;
}

//��ȡλ��
bool CEncirclePNG::GetEncircleRect(CRect & rcEncircleBorad, CRect & rcControl)
{
	//����λ��
	rcControl.top=rcEncircleBorad.top+m_EncircleInfo.nTBorder;
	rcControl.left=rcEncircleBorad.left+m_EncircleInfo.nLBorder;
	rcControl.right=rcEncircleBorad.right-m_EncircleInfo.nRBorder;
	rcControl.bottom=rcEncircleBorad.bottom-m_EncircleInfo.nBBorder;

	return true;
}

//���Ƶ���
bool CEncirclePNG::SetWindowPos(CWnd * pWnd, CRect & rcEncircleBorad)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		GetEncircleRect(rcEncircleBorad,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		pWnd->SetWindowPos(NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//���Ƶ���
bool CEncirclePNG::DeferWindowPos(CWnd * pWnd, HDWP hDwp, CRect & rcEncircleBorad)
{
	//��������
	if (pWnd->GetSafeHwnd()!=NULL)
	{
		//����λ��
		CRect rcControl;
		GetEncircleRect(rcEncircleBorad,rcControl);

		//��������
		UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER;
		::DeferWindowPos(hDwp,pWnd->m_hWnd,NULL,rcControl.left,rcControl.top,rcControl.Width(),rcControl.Height(),uFlags);

		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////////
