#include "StdAfx.h"
#include "GlobalUnits.h"
#include "GameFrameAvatar.h"

//////////////////////////////////////////////////////////////////////////////////
//��̬����

CGameFrameAvatar *	CGameFrameAvatar::m_pGameFrameAvatar=NULL;			//����ӿ�

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGameFrameAvatar::CGameFrameAvatar()
{
	//���ñ���
	m_wD3DLineCount=0;
	m_wD3DFullCount=0;

	//���ýӿ�
	ASSERT(m_pGameFrameAvatar==NULL);
	if (m_pGameFrameAvatar==NULL) m_pGameFrameAvatar=this;

	return;
}

//��������
CGameFrameAvatar::~CGameFrameAvatar()
{
	//���ýӿ�
	ASSERT(m_pGameFrameAvatar==this);
	if (m_pGameFrameAvatar==this) m_pGameFrameAvatar=NULL;

	//������Դ
	if (m_D3DTextureAvatar.IsNull()==false) m_D3DTextureAvatar.Destory();

	return;
}

//���ú���
VOID CGameFrameAvatar::Initialization(CD3DDevice * pD3DDevice)
{
	//��ȡ����
	ASSERT(CGlobalUnits::GetInstance()!=NULL);
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();

	//��ȡ��Դ
	tagAvatarResource AvatarResource;
	pGlobalUnits->m_FaceItemControlModule->GetAvatarResource(AvatarResource);

	//������Դ
	m_D3DTextureAvatar.LoadImage(pD3DDevice,AvatarResource.hResInstance,AvatarResource.pszResource,TEXT("PNG"));

	//���ñ���
	m_wD3DLineCount=m_D3DTextureAvatar.GetWidth()/FACE_CX;
	m_wD3DFullCount=m_wD3DLineCount*m_D3DTextureAvatar.GetHeight()/(FACE_CY*2);

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, WORD wFaceID)
{
	//�滭ͷ��
	DrawUserAvatar(pDC,nXPos,nYPos,FACE_CX,FACE_CX,wFaceID);

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, IClientUserItem * pIClientUserItem)
{
	//�滭ͷ��
	DrawUserAvatar(pDC,nXPos,nYPos,FACE_CX,FACE_CX,pIClientUserItem);

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight, WORD wFaceID)
{
	//��ȡ����
	ASSERT(CGlobalUnits::GetInstance()!=NULL);
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();

	//��ȡ�ӿ�
	IFaceItemControl * pIFaceItemControl=pGlobalUnits->m_FaceItemControlModule.GetInterface();

	//�滭ͷ��
	ASSERT(pIFaceItemControl!=NULL);
	if (pIFaceItemControl!=NULL) pIFaceItemControl->DrawFaceNormal(pDC,nXPos,nYPos,nWidth,nHeight,wFaceID);

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, INT nWidth, INT nHeight, IClientUserItem * pIClientUserItem)
{
	//��ȡ����
	ASSERT(CGlobalUnits::GetInstance()!=NULL);
	CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();

	//��ȡ�ӿ�
	IFaceItemControl * pIFaceItemControl=pGlobalUnits->m_FaceItemControlModule.GetInterface();

#ifdef _DEBUG

	//����ͷ��
	if (pIClientUserItem==NULL)
	{
		pIFaceItemControl->DrawFaceNormal(pDC,nXPos,nYPos,nWidth,nHeight,WORD(0));
		return;
	}

#endif

	//Ч�����
	ASSERT(pIClientUserItem!=NULL);
	if (pIClientUserItem==NULL) return;

	//��������
	tagUserInfo * pUserInfo=pIClientUserItem->GetUserInfo();
	tagCustomFaceInfo * pCustomFaceInfo=pIClientUserItem->GetCustomFaceInfo();

	WORD wFaceID=pIClientUserItem->GetFaceID();
	bool bOffLine=(pIClientUserItem->GetUserStatus()==US_OFFLINE);

	//�滭ͷ��
	if ((pUserInfo->dwCustomID!=0)&&(pCustomFaceInfo->dwDataSize!=0))
	{
		//�滭ͷ��
		if (bOffLine==false)
		{
			pIFaceItemControl->DrawFaceNormal(pDC,nXPos,nYPos,nWidth,nHeight,pCustomFaceInfo->dwCustomFace);
		}
		else
		{
			pIFaceItemControl->DrawFaceOffLine(pDC,nXPos,nYPos,nWidth,nHeight,pCustomFaceInfo->dwCustomFace);
		}
	}
	else
	{
		//��������
		WORD wFaceID=pUserInfo->wFaceID;
		if (wFaceID>=pIFaceItemControl->GetFaceCount()) wFaceID=0;

		//�滭ͷ��
		if (bOffLine==false)
		{
			pIFaceItemControl->DrawFaceNormal(pDC,nXPos,nYPos,nWidth,nHeight,wFaceID);
		}
		else
		{
			pIFaceItemControl->DrawFaceOffLine(pDC,nXPos,nYPos,nWidth,nHeight,wFaceID);
		}
	}

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, WORD wFaceID)
{
	//�滭ͷ��
	DrawUserAvatar(pD3DDevice,nXPos,nYPos,FACE_CX,FACE_CY,wFaceID);

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, IClientUserItem * pIClientUserItem)
{
	//�滭ͷ��
	DrawUserAvatar(pD3DDevice,nXPos,nYPos,FACE_CX,FACE_CY,pIClientUserItem);

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, INT nWidth, INT nHeight, WORD wFaceID)
{
	//Ч�����
	ASSERT(m_D3DTextureAvatar.IsNull()==false);
	if (m_D3DTextureAvatar.IsNull()==true) return;

	//��������
	if (wFaceID>=m_wD3DFullCount) wFaceID=0;

	//�滭ͷ��
	INT nXImagePos=wFaceID%m_wD3DLineCount;
	INT nYImagePos=(wFaceID/m_wD3DLineCount)*2L;
	m_D3DTextureAvatar.DrawImage(pD3DDevice,nXPos,nYPos,nWidth,nHeight,nXImagePos*nWidth,nYImagePos*nHeight,FACE_CX,FACE_CY);

	return;
}

//�滭ͷ��
VOID CGameFrameAvatar::DrawUserAvatar(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, INT nWidth, INT nHeight, IClientUserItem * pIClientUserItem)
{
	//Ч�����
	ASSERT(m_D3DTextureAvatar.IsNull()==false);
	if (m_D3DTextureAvatar.IsNull()==true) return;

#ifdef _DEBUG

	//����ͷ��
	if (pIClientUserItem==NULL)
	{
		m_D3DTextureAvatar.DrawImage(pD3DDevice,nXPos,nYPos,nWidth,nHeight,0,0,FACE_CX,FACE_CY);
		return;
	}

#endif

	//Ч�����
	ASSERT(pIClientUserItem!=NULL);
	if (pIClientUserItem==NULL) return;

	//��������
	tagUserInfo * pUserInfo=pIClientUserItem->GetUserInfo();
	tagCustomFaceInfo * pCustomFaceInfo=pIClientUserItem->GetCustomFaceInfo();

	//�滭ͷ��
	if ((pUserInfo->dwCustomID!=0)&&(pCustomFaceInfo->dwDataSize!=0))
	{
		if (pUserInfo->cbUserStatus!=US_OFFLINE)
		{
			DWORD dwTempCustomFace[FACE_CX*FACE_CY]={0};

			//��������
			for (INT nYImagePos=0;nYImagePos<FACE_CY;nYImagePos++)
			{
				for (INT nXImagePos=0;nXImagePos<FACE_CX;nXImagePos++)
				{
					//������ɫ
					DWORD dwImageTarget=nYImagePos*FACE_CX+nXImagePos;
					COLORREF crImageTarget=pCustomFaceInfo->dwCustomFace[dwImageTarget];

					//��ȡ��ɫ
					BYTE cbColorR=GetRValue(crImageTarget);
					BYTE cbColorG=GetGValue(crImageTarget);
					BYTE cbColorB=GetBValue(crImageTarget);

					//������ɫ
					dwTempCustomFace[dwImageTarget]=RGB(cbColorB,cbColorG,cbColorR);
				}
			}
			CD3DTexture::DrawImage(pD3DDevice,nXPos,nYPos,nWidth,nHeight,dwTempCustomFace,FACE_CX,FACE_CY);
		}
		else
		{
			DWORD dwTempCustomFace[FACE_CX*FACE_CY]={0};

			//��������
			for (INT nYImagePos=0;nYImagePos<FACE_CY;nYImagePos++)
			{
				for (INT nXImagePos=0;nXImagePos<FACE_CX;nXImagePos++)
				{
					//������ɫ
					DWORD dwImageTarget=nYImagePos*FACE_CX+nXImagePos;
					COLORREF crImageTarget=pCustomFaceInfo->dwCustomFace[dwImageTarget];

					//��ȡ��ɫ
					BYTE cbColorR=GetRValue(crImageTarget);
					BYTE cbColorG=GetGValue(crImageTarget);
					BYTE cbColorB=GetBValue(crImageTarget);
					BYTE cbColorGray=(BYTE)(cbColorR*0.30+cbColorG*0.59+cbColorB*0.11);

					//������ɫ
					dwTempCustomFace[dwImageTarget]=RGB(cbColorGray,cbColorGray,cbColorGray);
				}
			}

			//����ͷ��
			CD3DTexture::DrawImage(pD3DDevice,nXPos,nYPos,nWidth,nHeight,dwTempCustomFace,FACE_CX,FACE_CY);
		}
	}
	else
	{
		//��������
		WORD wFaceID=pUserInfo->wFaceID;
		if (wFaceID>=m_wD3DFullCount) wFaceID=0;

		//�滭ͷ��
		if (pUserInfo->cbUserStatus!=US_OFFLINE)
		{
			INT nXImagePos=wFaceID%m_wD3DLineCount;
			INT nYImagePos=(wFaceID/m_wD3DLineCount)*2L;
			m_D3DTextureAvatar.DrawImage(pD3DDevice,nXPos,nYPos,nWidth,nHeight,nXImagePos*FACE_CX,nYImagePos*FACE_CY,FACE_CX,FACE_CY);
		}
		else
		{
			INT nXImagePos=wFaceID%m_wD3DLineCount;
			INT nYImagePos=(wFaceID/m_wD3DLineCount)*2L;
			m_D3DTextureAvatar.DrawImage(pD3DDevice,nXPos,nYPos,nWidth,nHeight,nXImagePos*FACE_CX,nYImagePos*FACE_CY+FACE_CY,FACE_CX,FACE_CY);
		}
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////
