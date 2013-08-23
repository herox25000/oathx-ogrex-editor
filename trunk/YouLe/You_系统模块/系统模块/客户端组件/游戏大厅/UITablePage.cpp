#include "StdAfx.h"
#include "UITablepage.h"

namespace YouLe
{
	//���и�ʽ
#define	NT_LEFT						0x01								//�����
#define	NT_RIGHT					0x02								//�Ҷ���
	//�����ʽ
#define	NT_TOP						0x10								//�϶���
#define	NT_BOTTOM					0x20								//�¶���

#define INDEX_ENTER_CHAIR			MAX_CHAIR							//��������(���˷�)

	//////////////////////////////////////////////////////////////////////////
	//������Դ
	//////////////////////////////////////////////////////////////////////////
	//���캯��
	CTableResource::CTableResource()
	{
		//���Ա���
		m_bShowUser=true;
		m_bShowChair=true;
		m_bShowTable=true;
		m_bShowFocus=true;
		m_bShowEnter=false;
		m_bCustomUser=false;
		m_bShowTableID=true;
		m_bRenderImage=true;

		//��Ŀ����
		m_wTableItemCount=0;
		m_wChairItemCount=0;

		//������Ŀ
		m_wUserGenreCount=0;
		m_wTableGenreCount=0;
		m_wChairGenreCount=0;

		//��ɫ����
		m_crName=RGB(0,0,0);
		m_crMember=RGB(0,0,0);
		m_crMaster=RGB(0,0,0);

		//��������
		m_SizeChair.SetSize(0,0);
		m_SizeTable.SetSize(0,0);
		m_SizeEnter.SetSize(0,0);

		//λ�ñ���
		m_ptLock.SetPoint(0,0);
		m_ptEnter.SetPoint(0,0);
		m_ptTableID.SetPoint(0,0);

		//λ�ñ���
		for (WORD i=0;i<MAX_CHAIR;i++)
		{
			m_ptReadyArray[i].SetPoint(0,0);
			m_rcNameArray[i].SetRect(0,0,0,0);
			m_rcChairArray[i].SetRect(0,0,0,0);
		}

		//��������
		ZeroMemory(m_nDrawStyle,sizeof(m_nDrawStyle));
		ZeroMemory(m_szDirectory,sizeof(m_szDirectory));

		//���ñ���
		m_SizeBackSurface.SetSize(0,0);

		//������Դ
		//m_ImageNumberBK.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_NUMBER_BK"));
		//m_ImageNumberNB.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_NUMBER_NB"));

		return;
	}

	//��������
	CTableResource::~CTableResource()
	{
		//�ͷ���Դ
		DestroyResource();

		return;
	}

	//�ͷ���Դ
	VOID CTableResource::DestroyResource()
	{
		//��������
		m_SizeChair.SetSize(0,0);
		m_SizeTable.SetSize(0,0);

		//��Ŀ����
		m_wTableItemCount=0;
		m_wChairItemCount=0;

		//�������
		ZeroMemory(m_nDrawStyle,sizeof(m_nDrawStyle));

		//λ������
		ZeroMemory(&m_ptLock,sizeof(m_ptLock));
		ZeroMemory(m_rcNameArray,sizeof(m_rcNameArray));
		ZeroMemory(m_rcChairArray,sizeof(m_rcChairArray));
		ZeroMemory(m_ptReadyArray,sizeof(m_ptReadyArray));

		//��ɫ����
		m_crName=RGB(0,0,0);
		m_crMember=RGB(0,0,0);
		m_crMaster=RGB(0,0,0);

		//�ͷ�λͼ
		m_ImageGround.DestroyImage();

		//�ͷ�λͼ
		m_ImageTable.DestroyImage();
		m_ImageChair.DestroyImage();
		m_ImageEnter.DestroyImage();
		m_ImageCustomUser.DestroyImage();

		//�ͷ�λͼ
		if(m_ImageBackSurface.IsNull()==false)
			m_ImageBackSurface.Destroy();

		m_ImageReady.DestroyImage();
		m_ImageLocker.DestroyImage();
		m_ImageNumberNB.DestroyImage();
		m_ImageNumberBK.DestroyImage();
		m_ImageUserFace.DestroyImage();

		return;
	}

	//������Դ
	bool CTableResource::LoadResource(LPCTSTR szGameName, WORD wChairCount, bool bAvertCheatMode)
	{
		DestroyResource();

		//Ч�����
		ASSERT((szGameName!=NULL)&&(wChairCount<=MAX_CHAIR));
		if ((szGameName==NULL)||(wChairCount>MAX_CHAIR)) return false;

		//��Դ·��
		TCHAR szDirectory[MAX_PATH]=TEXT("");



		if(bAvertCheatMode)
			_sntprintf(m_szDirectory,CountArray(m_szDirectory),"%s\\GameLobby\\GameKind\\%s\\AvertCheatMode", 
											CString(g_GlobalUnits.GetWorkDirectory()),szGameName);
		else
			_sntprintf(m_szDirectory,CountArray(m_szDirectory),"%s\\GameLobby\\GameKind\\%s", 
											CString(g_GlobalUnits.GetWorkDirectory()),szGameName);

		//����·��
		TCHAR szParameterFile[MAX_PATH]=TEXT("");
		_sntprintf(szParameterFile,CountArray(szParameterFile),TEXT("%s\\TableResource.INI"),m_szDirectory);

		//��Դ�ж�
		if(bAvertCheatMode)
		{
			//����·��
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Table.png"),m_szDirectory);

			//������Դ
			CPngImage ImageTable;
			if (ImageTable.LoadImage(szImagePath)==false)
			{
				//��Դ·��
				ZeroMemory(m_szDirectory, sizeof(m_szDirectory));
				_sntprintf(m_szDirectory,CountArray(m_szDirectory),TEXT("%s\\AvertCheatMode"),szDirectory);

				//����·��
				ZeroMemory(szParameterFile, sizeof(szParameterFile));
				_sntprintf(szParameterFile,CountArray(szParameterFile),TEXT("%s\\TableResource.INI"),m_szDirectory);
			}
		}

		//��ɫ����
		ReadColor(m_crName,TEXT("Color"),TEXT("Color_Name"),szParameterFile);
		ReadColor(m_crMember,TEXT("Color"),TEXT("Color_Member"),szParameterFile);
		ReadColor(m_crMaster,TEXT("Color"),TEXT("Color_Master"),szParameterFile);

		//λ������
		ReadPoint(m_ptLock,TEXT("Position"),TEXT("Point_Lock"),szParameterFile);
		ReadPoint(m_ptEnter,TEXT("Position"),TEXT("Point_Enter"),szParameterFile);
		ReadPoint(m_ptTableID,TEXT("Position"),TEXT("Point_TableID"),szParameterFile);

		//��ʾ����
		m_bShowUser=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowUser"),1L,szParameterFile)==TRUE);
		m_bShowChair=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowChair"),1L,szParameterFile)==TRUE);
		m_bShowTable=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowTable"),1L,szParameterFile)==TRUE);
		m_bShowFocus=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowFocus"),1L,szParameterFile)==TRUE);
		m_bShowEnter=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowEnter"),0L,szParameterFile)==TRUE);
		m_bCustomUser=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("CustomUser"),0L,szParameterFile)==TRUE);
		m_bShowTableID=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowTableID"),1L,szParameterFile)==TRUE);
		m_bRenderImage=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("RenderImage"),1L,szParameterFile)==TRUE);

		//��Ŀ����
		m_wTableItemCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("TableItemCount"),2L,szParameterFile);
		m_wChairItemCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("ChairItemCount"),wChairCount,szParameterFile);

		//������Ŀ
		m_wUserGenreCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("UserGenreCount"),1L,szParameterFile);
		m_wTableGenreCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("TableGenreCount"),1L,szParameterFile);
		m_wChairGenreCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("ChairGenreCount"),1L,szParameterFile);

		////������Դ
		//if(UpdateResource(CSkinRenderManager::GetInstance())==false)
		//{
		//	return false;
		//}
		//����ͼƬ
		if(LoadResourceImages() == false)
			return false;

		//����ߴ�
		if (m_ImageEnter.IsNull()==false)
		{
			m_SizeEnter.SetSize(m_ImageEnter.GetWidth()/4,m_ImageEnter.GetHeight());
		}

		//���ӳߴ�
		if (m_ImageChair.IsNull()==false)
		{
			m_SizeChair.SetSize(m_ImageChair.GetWidth()/m_wChairItemCount,m_ImageChair.GetHeight()/m_wChairGenreCount);
		}

		//���ӳߴ�
		if (m_ImageTable.IsNull()==false)
		{
			m_SizeTable.SetSize(m_ImageTable.GetWidth()/m_wTableItemCount,m_ImageTable.GetHeight()/m_wTableGenreCount);
		}

		//�û��ߴ�
		if (m_ImageCustomUser.IsNull()==false)
		{
			m_SizeChair.SetSize(m_ImageCustomUser.GetWidth()/m_wChairItemCount,m_ImageCustomUser.GetHeight()/m_wUserGenreCount);
		}

		//λ������
		if (m_bShowTable==true && m_bShowUser==true)
		{
			for (WORD i=0;i<wChairCount;i++)
			{
				//��������
				TCHAR szSubItem[64]=TEXT("");
				//����λ��
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("Rect_Name%d"),i+1);
				ReadRect(m_rcNameArray[i],TEXT("Position"),szSubItem,szParameterFile);

				//׼��λ��
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("Point_Ready%d"),i+1);
				ReadPoint(m_ptReadyArray[i],TEXT("Position"),szSubItem,szParameterFile);

				//�������
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("DrawStyle%d"),i+1);
				m_nDrawStyle[i]=GetPrivateProfileInt(TEXT("Position"),szSubItem,0L,szParameterFile);

				//����λ��
				POINT ChairPoint;
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("Point_Chair%d"),i+1);
				ReadPoint(ChairPoint,TEXT("Position"),szSubItem,szParameterFile);

				//���ӿ��
				m_rcChairArray[i].top=ChairPoint.y;
				m_rcChairArray[i].left=ChairPoint.x;
				m_rcChairArray[i].right=m_rcChairArray[i].left+m_SizeChair.cx;
				m_rcChairArray[i].bottom=m_rcChairArray[i].top+m_SizeChair.cy;
			}
		}

		return true;
	}

	//������Դ
	bool CTableResource::LoadResourceImages()
	{
		////����·��
		//TCHAR szImageGround[MAX_PATH]=TEXT("");
		//_sntprintf(szImageGround,CountArray(szImageGround),TEXT("%s\\Ground.bmp"),m_szDirectory);

		////���ر���
		//if (m_ImageGround.IsNull()==false)
		//{
		//	m_ImageGround.Destroy();
		//}

		////������Դ
		//if (FAILED(m_ImageGround.Load(szImageGround)))
		//{
		//	m_ImageGround.LoadFromResource(AfxGetInstanceHandle(),IDB_TABLE_GROUND);
		//}

		////��Ⱦ��Դ
		//if (m_bRenderImage==true)
		//{
		//	pSkinRenderManager->RenderImage(m_ImageGround);
		//}

		//����λͼ

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
		if(!m_ImageReady.LoadImage(hInstance,PlazaViewImage.pszTableReady))
			return false;
		if(!m_ImageLocker.LoadImage(hInstance,PlazaViewImage.pszTableLocker))
			return false;

		if ((m_bShowEnter==true)&&(m_ImageEnter.IsNull()==true))
		{
			//����·��
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Enter.png"),m_szDirectory);

			//������Դ
			if (m_ImageEnter.LoadImage(szImagePath)==false) return false;
		}

		//�û�λͼ
		if ((m_bCustomUser==true)&&(m_ImageCustomUser.IsNull()==true))
		{
			//����·��
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\CustomUser.png"),m_szDirectory);

			//������Դ
			if (m_ImageCustomUser.LoadImage(szImagePath)==false) return false;
		}

		//��������
		if (m_bShowTable==true)
		{
			//����·��
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Table.png"),m_szDirectory);

			//������Դ
			if (m_ImageTable.LoadImage(szImagePath)==false) return false;
		}

		//��������
		if ((m_bShowChair==true)&&(m_bShowTable==true))
		{
			//����·��
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Chair.png"),m_szDirectory);

			//������Դ
			if (m_ImageChair.LoadImage(szImagePath)==false) return false;
		}

		////ͷ��
		//{
		//	//������Դ
		//	CPngImage ImageUserFace;
		//	if (ImageUserFace.LoadImage(GetModuleHandle(AVATAR_CONTROL_DLL_NAME),TEXT("USER_FACE_IMAGE"))==false) return false;

		//	//������Դ
		//	if (m_ImageUserFace.IsNull()==true)
		//	{
		//		m_ImageUserFace.Create(ImageUserFace.GetWidth(),ImageUserFace.GetHeight(),32);
		//	}

		//	//��䱳��
		//	CImageDC UserFaceDC(m_ImageUserFace);
		//	CDC * pUserFaceDC=CDC::FromHandle(UserFaceDC);
		//	m_ImageGround.DrawImageTile(pUserFaceDC,0,0,ImageUserFace.GetWidth(),ImageUserFace.GetHeight());

		//	//��������
		//	ImageUserFace.DrawImage(pUserFaceDC,0,0,ImageUserFace.GetWidth(),ImageUserFace.GetHeight(),0,0);
		//}

		return true;
	}

	//��ȡ��ֵ
	LONG CTableResource::ReadStringValue(LPCTSTR & pszSring)
	{
		//Ч�����
		ASSERT((pszSring!=NULL)&&(pszSring[0]!=0));
		if ((pszSring==NULL)||(pszSring[0]==0)) return 0L;

		//Ѱ�ҿ�ʼ
		while (((pszSring[0]>0)&&(pszSring[0]<TEXT('0')))||(pszSring[0]>TEXT('9'))) pszSring++;

		//��ȡ��ֵ
		LONG lValue=0L;
		while ((pszSring[0]>=TEXT('0'))&&(pszSring[0]<=TEXT('9')))
		{
			lValue=lValue*10L+pszSring[0]-TEXT('0');
			++pszSring;
		}

		return lValue;
	}

	//��ȡ����
	bool CTableResource::ReadRect(RECT & ValueRect, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile)
	{
		//���ñ���
		TCHAR szReadData[64]=TEXT("");
		ZeroMemory(&ValueRect,sizeof(ValueRect));

		//��ȡ�ַ�
		GetPrivateProfileString(pszItem,pszSubItem,TEXT(""),szReadData,CountArray(szReadData),pszIniFile);
		if (szReadData[0]!=0)
		{
			//��ȡ����
			LPCTSTR pszString=szReadData;
			ValueRect.left=ReadStringValue(pszString);
			ValueRect.top=ReadStringValue(pszString);
			ValueRect.right=ReadStringValue(pszString);
			ValueRect.bottom=ReadStringValue(pszString);

			return true;
		}

		return false;
	}

	//��ȡ����
	bool CTableResource::ReadPoint(POINT & ValuePoint, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile)
	{
		//���ñ���
		TCHAR szReadData[64]=TEXT("");
		ZeroMemory(&ValuePoint,sizeof(ValuePoint));

		//��ȡ�ַ�
		GetPrivateProfileString(pszItem,pszSubItem,TEXT(""),szReadData,CountArray(szReadData),pszIniFile);
		if (szReadData[0]!=0)
		{
			//��ȡ����
			LPCTSTR pszString=szReadData;
			ValuePoint.x=ReadStringValue(pszString);
			ValuePoint.y=ReadStringValue(pszString);

			return true;
		}

		return false;
	}

	//��ȡ��ɫ
	bool CTableResource::ReadColor(COLORREF & ValueColor, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile)
	{
		//���ñ���
		TCHAR szReadData[64]=TEXT("");
		ZeroMemory(&ValueColor,sizeof(ValueColor));

		//��ȡ�ַ�
		GetPrivateProfileString(pszItem,pszSubItem,TEXT(""),szReadData,CountArray(szReadData),pszIniFile);
		if (szReadData[0]!=0)
		{
			//��ȡ����
			LPCTSTR pszString=szReadData;
			ValueColor=RGB(ReadStringValue(pszString),ReadStringValue(pszString),ReadStringValue(pszString));

			return true;
		}

		return false;
	}


	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ���ӹ���
	//////////////////////////////////////////////////////////////////////////
	UITableItem::UITableItem(void)
	{
		//��������
		m_DrawFont.CreateFont(18,0,0,0,300,0,0,0,134,3,2,1,2,TEXT("����"));
		m_pTableInfo = NULL;
		m_pTableRes  = NULL;
		m_wHoverChairID = INVALID_CHAIR;
		m_bMouseDown = false;
		m_bFocus = false;
	}

	UITableItem::~UITableItem(void)
	{

	}

	// �����ؼ�
	BOOL	UITableItem::Create(INT nID, INT nDestX, INT nDestY,
								CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent)
	{
		CRect rect;
		rect.SetRect(nDestX, nDestY, nDestX + m_pTableRes->m_SizeTable.cx, nDestY + m_pTableRes->m_SizeTable.cy);

		if(m_UserHead.IsNull())
		{
			tagPlatformFrameImageNew & PlazaViewImage = g_GlobalUnits.m_PlatformFrameImage;
			HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
			m_UserHead.LoadImage(hInstance, PlazaViewImage.pszBtUserSexHead);
		}

		if (!UIWidget::Create(nID, rect, pAttach, pProcess, pParent))
			return FALSE;

		return TRUE;
	}

	// ���ƿؼ�
	BOOL	UITableItem::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;
		pDC->SelectObject(&m_DrawFont);
		CPoint cPt = m_rect.TopLeft();
		
		DrawTableView(pDC,cPt.x,cPt.y);

		return UIWidget::Draw(pDC);
	}
	
	// ��������
	void	UITableItem::DrawTableView(CDC * pDC,INT nXTablePos,INT nYTablePos)
	{
		CSize SizeChair=m_pTableRes->m_SizeChair;
		CSize SizeTable=m_pTableRes->m_SizeTable;
		
		// ����
		if(!m_pTableInfo->bPlayStatus)
			m_pTableRes->m_ImageTable.DrawImage(pDC,nXTablePos,nYTablePos,SizeTable.cx,SizeTable.cy,0,0);
		else
			m_pTableRes->m_ImageTable.DrawImage(pDC,nXTablePos,nYTablePos,SizeTable.cx,SizeTable.cy,SizeTable.cx,0);

		// ���˷�����
		if ((m_pTableRes->m_bShowEnter==true)&&(m_pTableRes->m_ImageEnter.IsNull()==false))
		{
			//����λ��
			INT nImageIndex=0;
			if (m_pTableInfo->bPlayStatus == true)
				nImageIndex=1;
			if ((m_wHoverChairID==INDEX_ENTER_CHAIR)&&(m_pTableInfo->bPlayStatus==false)&&(m_bMouseDown==true))
				nImageIndex=2;
			if ((m_wHoverChairID==INDEX_ENTER_CHAIR)&&(m_pTableInfo->bPlayStatus==false)&&(m_bMouseDown==false))
				nImageIndex=3;

			//�滭��־
			CSize SizeEnter=m_pTableRes->m_SizeEnter;
			m_pTableRes->m_ImageEnter.DrawImage(pDC,nXTablePos + m_pTableRes->m_ptEnter.x,
				nYTablePos + m_pTableRes->m_ptEnter.y,SizeEnter.cx,SizeEnter.cy,SizeEnter.cx*nImageIndex,0);
			return ;
		}

		// ����ID
		TCHAR szTableID[256];
		sprintf(szTableID,_T("%d"),m_pTableInfo->wTableID);
		pDC->TextOut(nXTablePos+SizeTable.cx/2-3,nYTablePos+SizeTable.cy-17,szTableID);

		// ��
		if (m_pTableInfo->bTableLock == true)
		{
			INT nXPos = nXTablePos + m_pTableRes->m_ptLock.x;
			INT nYPos = nYTablePos + m_pTableRes->m_ptLock.y;
			m_pTableRes->m_ImageLocker.DrawImage(pDC,nXPos,nYPos);
		}

		// ����
		if(m_pTableInfo->wChairCount < MAX_CHAIR)
		{
			for (WORD i=0;i<m_pTableInfo->wChairCount;i++)
			{
				//��������
				CRect rcChair=m_pTableRes->m_rcChairArray[i];
				////�滭����
				//if ((bAvertCheatMode==true)&&(m_pTableRes->m_bShowChair==true)&&(m_pTableRes->wTableID==0))
				//{
				//	ASSERT(m_pTableRes->m_ImageChair.IsNull()==false);
				//	m_pTableRes->m_ImageChair.DrawImage(pDC,rcChair.left,rcChair.top,SizeChair.cx,SizeChair.cy,SizeChair.cx*i,0);
				//}

				//�滭����
				if (/*(bAvertCheatMode==false)&&*/(m_pTableRes->m_bShowChair==true)&&(m_pTableInfo->pIUserItem[i]==NULL))
				{
					ASSERT(m_pTableRes->m_ImageChair.IsNull()==false);
					m_pTableRes->m_ImageChair.DrawImage(pDC,nXTablePos + rcChair.left, nYTablePos + rcChair.top,
						SizeChair.cx,SizeChair.cy,SizeChair.cx*i,0);
				}

				// �������ӵı߿�
				if ((m_pTableRes->m_bCustomUser==true)&&(m_wHoverChairID==i))
				{
					pDC->Draw3dRect(nXTablePos + rcChair.left,nYTablePos + rcChair.top,
						rcChair.Width(),rcChair.Height(),RGB(125,125,125),RGB(125,125,125));
				}
			}
		}

		// �û���Ϣ
		DrawAllUserInfo(pDC,nXTablePos,nYTablePos);
		
		////���������
		//if(m_bFocus && (m_pTableRes->m_bShowFocus==true))
		//	pDC->Draw3dRect(nXTablePos,nYTablePos,SizeTable.cx,SizeTable.cy,RGB(125,125,125),RGB(125,125,125));
	}

	// ���������û�������
	void	UITableItem::DrawAllUserInfo(CDC* pDC,INT nXTablePos,INT nYTablePos)
	{
		if(m_pTableRes->m_bShowUser)
		{
			for (int i = 0; i < m_pTableInfo->wChairCount; i++)
			{
				if(m_pTableInfo->pIUserItem[i] != NULL)
				{	
					tagUserData* pUserData = m_pTableInfo->pIUserItem[i]->GetUserData();
					if(pUserData == NULL)
						continue;
					// ��������
					CRect rcChair=m_pTableRes->m_rcChairArray[i];

					// ׼����־
					if((m_pTableInfo->bPlayStatus == false) && (US_READY == pUserData->cbUserStatus))
					{
						INT nXPos=m_pTableRes->m_ptReadyArray[i].x;
						INT nYPos=m_pTableRes->m_ptReadyArray[i].y;
						m_pTableRes->m_ImageReady.DrawImage(pDC,nXTablePos + nXPos, nYTablePos + nYPos);
					}

					// �û�ͷ��
					if (m_pTableRes->m_bCustomUser==false)
					{
						//����λ��
						INT nXExcursion=(rcChair.Width()-FACE_CX)/2;
						INT nYExcursion=(rcChair.Height()-FACE_CY)/2;

						//�滭ͷ��
						DrawUserAvatar(pDC,nXTablePos + rcChair.left+nXExcursion, nYTablePos + rcChair.top+nYExcursion,pUserData);
					}
					else
					{
						//�Զ�ͷ��
						INT nXImagePos=(i*rcChair.Width() >= m_pTableRes->m_ImageCustomUser.GetWidth())?0:i*rcChair.Width();
						INT nYImagePos=(pUserData->cbGender == GENDER_FEMALE)?rcChair.Height():0;
						m_pTableRes->m_ImageCustomUser.DrawImage(pDC,nXTablePos + rcChair.left,nYTablePos + rcChair.top,
							rcChair.Width(),rcChair.Height(),nXImagePos,nYImagePos);
					}

					// �û���
					DrawUserName(pDC,i,pUserData->szName);
				}
			}
		}
	}

	// ��������
	void	UITableItem::DrawUserName(CDC * pDC, WORD wChairID, LPCTSTR pszNickName)
	{
		//�û�����
		CRect rcName=m_pTableRes->m_rcNameArray[wChairID];
		POINT pot = m_rect.TopLeft();
		rcName += pot;
		//��ͼ����
		CRect rcDrawRect=rcName;
		INT nNameLength=lstrlen(pszNickName);
		INT nDrawStyte=m_pTableRes->m_nDrawStyle[wChairID];
		INT nDrawFormat=DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS;
		INT nNameHeight=pDC->DrawText(pszNickName,nNameLength,&rcDrawRect,nDrawFormat|DT_CALCRECT);

		//����λ��
		if (nNameHeight<=12)
		{
			if (nDrawStyte&NT_LEFT) nDrawFormat|=DT_LEFT;
			else if (nDrawStyte&NT_RIGHT) nDrawFormat|=DT_RIGHT;
			else nDrawFormat|=(DT_CENTER|DT_SINGLELINE);
		}
		else nDrawFormat|=DT_LEFT;

		//����λ��
		INT nYPos=0;
		if (nDrawStyte&NT_BOTTOM) nYPos=rcName.Height()-nNameHeight;
		else if (nDrawStyte&NT_TOP) nYPos=0;
		else nYPos=(rcName.Height()-nNameHeight)/2;

		//����λ��
		rcDrawRect=rcName;
		rcDrawRect.left=rcName.left;
		rcDrawRect.right=rcName.right;
		rcDrawRect.top=__max(rcName.top,rcName.top+nYPos);
		rcDrawRect.bottom=__min(rcName.bottom,rcDrawRect.top+nNameHeight);

		//�û�����
		pDC->SetTextColor(m_pTableRes->m_crName);
		pDC->DrawText(pszNickName,nNameLength,&rcDrawRect,nDrawFormat);
	}

	// ����ͷ��
	void	UITableItem::DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, tagUserData* pUserData)
	{
		int nHeadNumberWidth	= m_UserHead.GetWidth() / 2;
		int nHeadNumberHeight	= m_UserHead.GetHeight(); 
		//// ����
		//if(pUserData->cbUserStatus == US_OFFLINE)
		//{
		//}
		//else
		{
			if (pUserData->cbGender)
			{
				m_UserHead.DrawImage(pDC, nXPos, nYPos, nHeadNumberWidth, nHeadNumberHeight, 0, 0);
			}
			else
			{
				m_UserHead.DrawImage(pDC, nXPos, nYPos, nHeadNumberWidth, nHeadNumberHeight, nHeadNumberWidth, 0);
			}
		}
	}

	// ��ѯ����
	WORD	UITableItem::SwitchChairID(POINT MousePoint)
	{
		TCHAR strLog[256];
		sprintf(strLog,"λ��x��%d,y:%d \r\n",MousePoint.x,MousePoint.y);
		OutputDebugString(strLog);

		POINT Point =  m_rect.TopLeft();
		//λ������
		if ((m_pTableRes->m_bShowUser==true)||(m_pTableRes->m_bShowChair==true))
		{
			for (WORD i=0;i<m_pTableInfo->wChairCount;i++)
			{
				CRect ChairRC = m_pTableRes->m_rcChairArray[i] + Point;
				//�����ж�
				if (MousePoint.x<ChairRC.left) continue;
				if (MousePoint.x>ChairRC.right) continue;

				//�����ж�
				if (MousePoint.y<ChairRC.top) continue;
				if (MousePoint.y>ChairRC.bottom) continue;

				return i;
			}
		}

		//��������
		if (m_pTableRes->m_bShowEnter==true)
		{
			//��������
			bool bOutSide=false;

			//�����ж�
			if (MousePoint.x < (Point.x + m_pTableRes->m_ptEnter.x)) bOutSide=true;
			if (MousePoint.x > (Point.x + m_pTableRes->m_ptEnter.x + m_pTableRes->m_SizeEnter.cx)) bOutSide=true;

			//�����ж�
			if (MousePoint.y < (Point.y + m_pTableRes->m_ptEnter.y)) bOutSide=true;
			if (MousePoint.y > (Point.y + m_pTableRes->m_ptEnter.y + m_pTableRes->m_SizeEnter.cy)) bOutSide=true;

			//����ж�
			if (bOutSide==false)
			{
				return INDEX_ENTER_CHAIR;
			}
		}

		return INVALID_CHAIR;
	}

	// ����ƶ�
	BOOL	UITableItem::OnMouseMove(const CPoint& cPt)
	{
		m_wHoverChairID = SwitchChairID(cPt);
		if(m_wHoverChairID != INVALID_CHAIR)
		{
			// �������ΪС��
			m_pAttach->PostMessage(WM_COMMAND,IDM_SETHANDCUR,1);
		}
		else
		{
			// �����������
			m_pAttach->PostMessage(WM_COMMAND,IDM_SETHANDCUR,0);
		}

		return TRUE;
	}

	// ����뿪
	BOOL	UITableItem::OnMouseLeave(const CPoint& cPt)
	{
		m_bFocus = false;
		return TRUE;
	}

	// ������
	BOOL	UITableItem::OnMouseEnter(const CPoint& cPt)
	{
		m_bFocus = true;
		return TRUE;
	}

	// �������
	BOOL	UITableItem::OnLeftDown(const CPoint& cPt)
	{
		m_bMouseDown = true;
		return TRUE;
	}

	// �������
	BOOL	UITableItem::OnLeftUp(const CPoint& cPt)
	{
		m_bMouseDown = false;
		if(m_wHoverChairID != INVALID_CHAIR)
			g_GlobalUnits.m_GameRoomManager.RequestSitdown(m_pTableInfo->wTableID,m_wHoverChairID);
		return TRUE;
	}


	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ������ͼ����
	//////////////////////////////////////////////////////////////////////////
	UITablePage::UITablePage(void)
	{
		//��������
		m_DrawFont.CreateFont(18,0,0,0,300,0,0,0,134,3,2,1,2,TEXT("����"));
	}

	UITablePage::~UITablePage(void)
	{
	}

	// �����ؼ�
	BOOL	UITablePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//������Դ
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		// ����ͼƬ
		m_TilteImage.LoadImage(hInstance,PlazaViewImage.pszTilteImage);

		// ���ټ���
		UIPngButton* pBtFastJoin = new UIPngButton();
		pBtFastJoin->Create(102, rect.right - 150, 2, pAttach, this, hInstance, PlazaViewImage.pszBtFastJoin, 4, this);

		CRect rc;
		GetClientRect(&rc);
		// ���Ʒ�ҳ��ť����һҳ
		UIPngButton* pBtLast = new UIPngButton();
		pBtLast->Create(100, rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);

		// ���Ʒ�ҳ��ť����һҳ
		UIPngButton* pBtNext = new UIPngButton();
		pBtNext->Create(101, rc.right/2 ,	  rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLNext, 4, this);

		VisibleWidget(FALSE);
		return TRUE;
	}

	// ����
	BOOL	UITablePage::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;

		CPoint cPt = m_rect.TopLeft();
		m_TilteImage.DrawImage(pDC, cPt.x + GTP_OFFSETX, cPt.y);

		if(m_pListServer)
		{
			TCHAR	szTempStr[32];
			pDC->SelectObject(m_DrawFont);
			pDC->SetTextColor(RGB(255,255,255));
			CopyMemory(szTempStr,m_pListServer->m_GameServer.szServerName,sizeof(szTempStr));
			pDC->DrawText(szTempStr,lstrlen(szTempStr),CRect(cPt.x + GTP_OFFSETX,cPt.y+8,cPt.x+150+GTP_OFFSETX,cPt.y+30),DT_CENTER);
		}

		// ����Ƿ����׷�
		if(!m_NoCheatImage.IsNull())
		{
			m_NoCheatImage.DrawImage(pDC,cPt.x + GTP_OFFSETX,cPt.y + GTP_OFFSETY-10);
		}
		return UIWidget::Draw(pDC);
	}

	// ��Ӧҳ�ؼ�
	BOOL	UITablePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			switch(pWidget->GetID())
			{
			case 100:	// ��һҳ
				{
					OnClickLastPage();
					return TRUE;
				}
			case 101:	// ��һҳ
				{
					OnClickNextPage();
					return TRUE;
				}
			case 102:	//���ټ���
				{
					if(!OnFastJoin())
						ShowMessageBox(_T("û���ҵ����ʵ�λ�ã�"),MB_ICONQUESTION);
					return TRUE;
				}

			}
		}
		return TRUE;
	}

	// ��ʾʱ��Ӧ����
	void	UITablePage::VisibleTrigger()
	{
		SetRoomInfo();
		WORD wSeverRule = m_pListServer->m_GameServer.RoomConfig.wServerRule;
		if( wSeverRule == ROOM_NOCHEAT)
		{
			LoadNoCheatImage();
			g_GlobalUnits.m_GameRoomManager.RequestSitdown(INVALID_TABLE,INVALID_CHAIR);
		}
		else
		{
			LoadTableRes();
			CreateTable();
			ShowFirstTablePage();
		}
		// ���˷��ͷ����׳�����ʾ��һҳ
		if(wSeverRule == ROOM_BAIREN || wSeverRule == ROOM_NOCHEAT)
		{
			Search(100)->VisibleWidget(false);
			Search(101)->VisibleWidget(false);
		}
	}

	// ���ɼ�ʱ��������
	void	UITablePage::InvisibleTrigger()	
	{
		m_TableResource.DestroyResource();
		std::vector<UITableItem*>::iterator it = m_TableItemVector.begin();
		while(it != m_TableItemVector.end())
		{
			Remove((*it),TRUE);
			it = m_TableItemVector.erase(it);
		}
		m_NoCheatImage.DestroyImage();
	}

	// ��Ӧ��һҳ
	void	UITablePage::OnClickLastPage()
	{
		m_EnumIndex -= m_nXTableCount*m_nYTableCount;
		if(m_EnumIndex < 0)
		{
			m_EnumIndex = 0;
			return;
		}
		EnumTableItem();
	}

	// ��Ӧ��һҳ
	void	UITablePage::OnClickNextPage()
	{
		m_EnumIndex += m_nXTableCount*m_nYTableCount;
		// �������Ƿ���
		TableInfo*  pTableInfo = NULL;
		pTableInfo = g_GlobalUnits.m_GameRoomManager.EnumTableItem(m_EnumIndex);
		if (pTableInfo == NULL) 
		{
			m_EnumIndex -= m_nXTableCount*m_nYTableCount;
			return ;
		}
		EnumTableItem();
	}

	// ����Item�Ƿ���ʾ
	void	UITablePage::VisibleAllTableItem(bool bVisible)			
	{
		std::vector<UITableItem*>::iterator it = m_TableItemVector.begin();
		while(it != m_TableItemVector.end())
		{
			(*it)->VisibleWidget(bVisible);
			it++;
		}
	}

	// ö��GameItem
	bool	UITablePage::EnumTableItem()
	{
		VisibleAllTableItem(false);
		TableInfo*  pTableInfo = NULL;
		int			TableIndex = 0;
		for (int nIndex = m_EnumIndex; nIndex < (m_EnumIndex+m_nXTableCount*m_nYTableCount); nIndex++)
		{
			pTableInfo = g_GlobalUnits.m_GameRoomManager.EnumTableItem(nIndex);
			if (pTableInfo == NULL) 
				return false;
			UITableItem* pTableItem = m_TableItemVector[TableIndex];
			if(pTableItem)
			{
				pTableItem->VisibleWidget(true);
				pTableItem->m_pTableInfo = pTableInfo;
				pTableItem->m_pTableRes = &m_TableResource;
			}
			TableIndex++;
		}
		return true;
	}

	// ��ʾ��ҳ
	void	UITablePage::ShowFirstTablePage()
	{
		m_EnumIndex = 0;
		EnumTableItem();
	}

	// ���ټ���
	bool	UITablePage::OnFastJoin()
	{
		return g_GlobalUnits.m_GameRoomManager.OnFastJoin();
	}

	//���÷�����Ϣ
	void	UITablePage::SetRoomInfo()
	{
		m_pListServer = g_GlobalUnits.m_GameRoomManager.m_pListServer;
		m_wTableCount = g_GlobalUnits.m_GameRoomManager.m_wTableCount;
		m_wChairCount = g_GlobalUnits.m_GameRoomManager.m_wChairCount;
	}

	//��ȡ������Դ
	void	UITablePage::LoadTableRes()
	{
		TCHAR szGameName[128]=TEXT("");
		g_GlobalUnits.RemoveEXE(m_pListServer->GetListKind()->GetItemInfo()->szProcessName,
			szGameName,CountArray(szGameName));
		m_TableResource.LoadResource(szGameName,m_wChairCount,false);
	}

	//��ȡ������ͼƬ
	void	UITablePage::LoadNoCheatImage()
	{
		if(m_NoCheatImage.IsNull())
		{
			TCHAR szGameName[128]=TEXT("");
			g_GlobalUnits.RemoveEXE(m_pListServer->GetListKind()->GetItemInfo()->szProcessName,
				szGameName,CountArray(szGameName));
			TCHAR	szDirectory[256] = _T("");
			_sntprintf(szDirectory,CountArray(szDirectory),"%s\\GameLobby\\GameKind\\%s\\NoCheat.png", 
				CString(g_GlobalUnits.GetWorkDirectory()),szGameName);
			m_NoCheatImage.LoadImage(szDirectory);
		}
	}

	// �������ӵĴ�С��������
	bool	UITablePage::CreateTable()
	{	
		CRect rc;
		GetClientRect(&rc);
		INT nWidth	= rc.Width();
		INT	nHeight = rc.Height();

		if ((m_wTableCount == 0) || (m_TableResource.m_SizeTable.cx <= 0L) || (m_TableResource.m_SizeTable.cy <= 0L))
			return false;

		//��������
		INT nViewWidth  = __max(m_TableResource.m_SizeTable.cx,nWidth);
		INT nViewHeight = __max(m_TableResource.m_SizeTable.cy,nHeight);
		nViewHeight -= GTP_OFFSETY;

		//��ͼ����
		m_nXTableCount = nViewWidth  / m_TableResource.m_SizeTable.cx;
		m_nYTableCount = nViewHeight / m_TableResource.m_SizeTable.cy;

		INT nYExcursion = (nViewHeight-m_nYTableCount*m_TableResource.m_SizeTable.cy)/2;
		INT nXExcursion = (nViewWidth-m_nXTableCount*m_TableResource.m_SizeTable.cx)/2;
		nYExcursion += GTP_OFFSETY;

		// �����б�
		for (int c=0; c<m_nYTableCount; c++)
		{
			for (int r=0; r<m_nXTableCount; r++)
			{
				int index = c*m_nXTableCount + r;
				UITableItem* pItem = new UITableItem();
				INT posX = nXExcursion + m_TableResource.m_SizeTable.cx*r;
				INT	posY = nYExcursion + m_TableResource.m_SizeTable.cy*c;
				pItem->m_pTableRes = &m_TableResource;
				pItem->Create(index , posX, posY,m_pAttach, m_pProcess, this);
				pItem->VisibleWidget(true);

				m_TableItemVector.push_back(pItem);
			}
		}
		return true;
	}
}