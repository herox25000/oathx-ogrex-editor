#include "StdAfx.h"
#include "PngImageEx.h"
#include "D2DEngine.h"

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPngImageEx::CPngImageEx()
{
	//���ñ���
	m_pImage = NULL;
	m_pWnd = NULL;
	ZeroMemory(m_strImageName, sizeof(m_strImageName) );

	return;
}

//��������
CPngImageEx::~CPngImageEx()
{
	//����ͼƬ
	DestroyImage(); 

	return;
}

//�Ƿ����
bool CPngImageEx::IsNull()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
		return m_pWnd == NULL;

	//�����ж�
	if (m_pImage==NULL) return true;
	if (m_pImage->GetLastStatus()!=Ok) return true;

	return false;
}

//��ȡ���
INT CPngImageEx::GetWidth()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetWidth(m_pWnd, m_strImageName);

	//�����ж�
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//��ȡ���
	return m_pImage->GetWidth();
}

//��ȡ�߶�
INT CPngImageEx::GetHeight()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
		return CD2DEngine::GetD2DEngine()->GetHeight(m_pWnd, m_strImageName);

	//�����ж�
	ASSERT(IsNull()==false);
	if (IsNull()==true) return 0;

	//��ȡ�߶�
	return m_pImage->GetHeight();
}

//����ͼƬ
bool CPngImageEx::DestroyImage()
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() && m_pWnd!= NULL )
	{
		CD2DEngine::GetD2DEngine()->DeleteImage(m_pWnd, m_strImageName);
		m_pWnd = NULL;
		return true;
	}

	//ɾ������
	if (m_pImage!=NULL) SafeDelete(m_pImage);

	return true;
}

//����ͼƬ
bool CPngImageEx::LoadImage(CWnd* pWnd, LPCTSTR pszFileName)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		m_pWnd = pWnd;
		CD2DEngine::GetD2DEngine()->LaodImage(pWnd, pszFileName, m_strImageName);
		return true;
	}

	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//�����ļ�
	CT2CW strFileName(pszFileName);
	m_pImage=Image::FromFile((LPCWSTR)strFileName);

	//�����ж�
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok)) 
	{
		DestroyImage();
		return false;
	}

	return true;
}

//����ͼƬ
bool CPngImageEx::LoadImage(CWnd* pWnd, HINSTANCE hInstance, LPCTSTR pszResourceName)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		m_pWnd = pWnd;
		CD2DEngine::GetD2DEngine()->LaodImage(pWnd, hInstance, pszResourceName, TEXT("PNG"), m_strImageName);
		return true;
	}

	//�����ж�
	ASSERT(m_pImage==NULL);
	if (m_pImage!=NULL) return false;

	//������Դ
	HRSRC hResource=FindResource(hInstance,pszResourceName,TEXT("PNG"));
	if (hResource==NULL) return false;

	//��ȡ��Դ
	DWORD dwImageSize=SizeofResource(hInstance,hResource);
	LPVOID pImageBuffer=LoadResource(hInstance,hResource);

	//��������
	IStream * pIStream=NULL;
	if (CreateStreamOnHGlobal(NULL,TRUE,&pIStream)!=S_OK)
	{
		ASSERT(FALSE);
		return false;
	}

	//д������
	pIStream->Write(pImageBuffer,dwImageSize,NULL);

	//����λͼ
	m_pImage=Image::FromStream(pIStream);

	//�ͷ���Դ
	SafeRelease(pIStream);

	//�����ж�
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//�滭ͼ��
bool CPngImageEx::DrawImage(CDC * pDC, INT nXPos, INT nYPos)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->DrawImage(m_pWnd, m_strImageName, nXPos, nYPos, 255  );
		return true;
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//��ȡ����
	INT nImageWidth=m_pImage->GetWidth();
	INT nImageHeight=m_pImage->GetHeight();

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXPos;
	rcDrawRect.Y=(REAL)nYPos;
	rcDrawRect.Width=(REAL)nImageWidth;
	rcDrawRect.Height=(REAL)nImageHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,0,0,(REAL)nImageWidth,(REAL)nImageHeight,UnitPixel);

	return true;
}

//�滭ͼ��
bool CPngImageEx::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->DrawImage(m_pWnd, m_strImageName, nXDest, nYDest, nDestWidth, nDestHeight, nXScr, nYSrc, 255  );
		return true;
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nDestWidth,(REAL)nDestHeight,UnitPixel);

	return true;
}

//�滭ͼ��
bool CPngImageEx::DrawImage(CDC * pDC, INT nXDest, INT nYDest, INT nDestWidth, INT nDestHeight, INT nXScr, INT nYSrc, INT nSrcWidth, INT nSrcHeight)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->DrawImage(m_pWnd, m_strImageName, nXDest, nYDest, nDestWidth, nDestHeight, nXScr, nYSrc, nSrcWidth, nSrcHeight, 255 );
		return true;
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDC!=NULL);
	Graphics graphics(pDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)nXDest;
	rcDrawRect.Y=(REAL)nYDest;
	rcDrawRect.Width=(REAL)nDestWidth;
	rcDrawRect.Height=(REAL)nDestHeight;

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)nXScr,(REAL)nYSrc,(REAL)nSrcWidth,(REAL)nSrcHeight,UnitPixel);

	return true;
}

//��ϻ滭
bool CPngImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, BYTE cbAlphaDepth)
{
	//͸���滭
	AlphaDrawImage(pDestDC,xDest,yDest,GetWidth(),GetHeight(),0,0,cbAlphaDepth);

	return true;
}

//��ϻ滭
bool CPngImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, BYTE cbAlphaDepth)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->DrawImage(m_pWnd, m_strImageName, xDest, yDest, cxDest, cyDest, xSrc, ySrc, cbAlphaDepth  );
		return true;
	}

	//�����ж�
	ASSERT(m_pImage!=NULL);
	if (m_pImage==NULL) return false;

	//������Ļ
	ASSERT(pDestDC!=NULL);
	Graphics graphics(pDestDC->GetSafeHdc());

	//����λ��
	RectF rcDrawRect;
	rcDrawRect.X=(REAL)xDest;
	rcDrawRect.Y=(REAL)yDest;
	rcDrawRect.Width=(REAL)cxDest;
	rcDrawRect.Height=(REAL)cyDest;

	//͸������
	ColorMatrix Matrix=
	{
		1.0f,0.0f,0.0f,0.0f,0.0f, 
			0.0f,1.0f,0.0f,0.0f,0.0f, 
			0.0f,0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f, 
			0.0f,0.0f,0.0f,0.0f,1.0f
	};

	//��������
	ImageAttributes Attributes; 
	Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap); 

	//�滭ͼ��
	graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxDest,(REAL)cyDest,UnitPixel,&Attributes);

	return true;
}

//��ϻ滭
bool CPngImageEx::AlphaDrawImage(CDC * pDestDC, INT xDest, INT yDest, INT cxDest, INT cyDest, INT xSrc, INT ySrc, INT cxSrc, INT cySrc, BYTE cbAlphaDepth)
{
	//WIN 7 ִ��
	if ( CD2DEngine::GetD2DEngine() )
	{
		CD2DEngine::GetD2DEngine()->DrawImage(m_pWnd, m_strImageName, xDest, yDest, cxDest, cyDest, xSrc, ySrc, cxSrc, cySrc, cbAlphaDepth  );
		return true;
	}

	//��������
	if ((cxDest!=cxSrc)||(cyDest!=cySrc))
	{
		//�����ж�
		ASSERT(m_pImage!=NULL);
		if (m_pImage==NULL) return false;

		//������Ļ
		ASSERT(pDestDC!=NULL);
		Graphics graphics(pDestDC->GetSafeHdc());

		//����λ��
		RectF rcDrawRect;
		rcDrawRect.X=(REAL)xDest;
		rcDrawRect.Y=(REAL)yDest;
		rcDrawRect.Width=(REAL)cxDest;
		rcDrawRect.Height=(REAL)cyDest;

		//͸������
		ColorMatrix Matrix=
		{
			1.0f,0.0f,0.0f,0.0f,0.0f, 
				0.0f,1.0f,0.0f,0.0f,0.0f, 
				0.0f,0.0f,1.0f,0.0f,0.0f,
				0.0f,0.0f,0.0f,cbAlphaDepth/255.0f,0.0f, 
				0.0f,0.0f,0.0f,0.0f,1.0f
		};

		//��������
		ImageAttributes Attributes; 
		Attributes.SetColorMatrix(&Matrix,ColorMatrixFlagsDefault,ColorAdjustTypeBitmap); 

		//�滭ͼ��
		graphics.DrawImage(m_pImage,rcDrawRect,(REAL)xSrc,(REAL)ySrc,(REAL)cxSrc,(REAL)cySrc,UnitPixel,&Attributes);	
	}
	else
	{
		//��ͨ����
		AlphaDrawImage(pDestDC,xDest,yDest,cxDest,cyDest,xSrc,ySrc,cbAlphaDepth);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////
