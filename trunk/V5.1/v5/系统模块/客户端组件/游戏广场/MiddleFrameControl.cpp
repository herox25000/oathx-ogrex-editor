#include "Stdafx.h"
#include "Resource.h"
#include "MiddleFrameControl.h"


//////////////////////////////////////////////////////////////////////////////////

//���캯��
CMiddleFrameControl::CMiddleFrameControl()
{
	//��������
	m_rcControl.SetRect(0,0,0,0);

	//���ñ���
	m_bAfficheTitle = true;
}

//��������
CMiddleFrameControl::~CMiddleFrameControl()
{
}

//��������
VOID CMiddleFrameControl::SetControlRect(INT nLeftPos,INT nTopPos,INT nRightPos,INT nBottomPos)
{
	//��������
	m_rcControl.SetRect(nLeftPos,nTopPos,nRightPos,nBottomPos);

	return;
}

//�滭����
BOOL CMiddleFrameControl::OnDrawFrameControl(CDC * pDC)
{
	//��������
	HINSTANCE hInstance=AfxGetInstanceHandle();
	CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();

	//������Դ
	CBitImage ImageTitleL;
	CBitImage ImageTitleM;
	CBitImage ImageTitleR;
	ImageTitleL.LoadFromResource(hInstance,IDB_MID_FRAME_TL);
	ImageTitleM.LoadFromResource(hInstance,IDB_MID_FRAME_TM);
	ImageTitleR.LoadFromResource(hInstance,IDB_MID_FRAME_TR);

	//��Ⱦ��Դ
	pSkinRenderManager->RenderImage(ImageTitleL);
	pSkinRenderManager->RenderImage(ImageTitleM);
	pSkinRenderManager->RenderImage(ImageTitleR);

	//�滭����
	ImageTitleL.BitBlt(*pDC,m_rcControl.left,m_rcControl.top);

	//����м�
	for (INT nXPos=ImageTitleL.GetWidth();nXPos<m_rcControl.Width()-ImageTitleM.GetWidth();nXPos+=ImageTitleM.GetWidth())
	{
		ImageTitleM.BitBlt(*pDC,m_rcControl.left+nXPos,m_rcControl.top);
	}

	//�滭����
	ImageTitleR.BitBlt(*pDC,m_rcControl.left+m_rcControl.Width()-ImageTitleR.GetWidth(),m_rcControl.top);

	//�滭����
	if(m_bAfficheTitle==true)
	{
		CPngImage ImageTitle;
		ImageTitle.LoadImage(AfxGetInstanceHandle(),TEXT("USER_INFO_TITLE"));
		ImageTitle.DrawImage(pDC,m_rcControl.left+88,m_rcControl.top+9);
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////
