#include "StdAfx.h"
#include "UITablepage.h"

namespace YouLe
{
	//横行格式
#define	NT_LEFT						0x01								//左对齐
#define	NT_RIGHT					0x02								//右对齐
	//纵向格式
#define	NT_TOP						0x10								//上对齐
#define	NT_BOTTOM					0x20								//下对齐

#define INDEX_ENTER_CHAIR			MAX_CHAIR							//进入区域(百人房)

	//////////////////////////////////////////////////////////////////////////
	//桌子资源
	//////////////////////////////////////////////////////////////////////////
	//构造函数
	CTableResource::CTableResource()
	{
		//属性变量
		m_bShowUser=true;
		m_bShowChair=true;
		m_bShowTable=true;
		m_bShowFocus=true;
		m_bShowEnter=false;
		m_bCustomUser=false;
		m_bShowTableID=true;
		m_bRenderImage=true;

		//数目定义
		m_wTableItemCount=0;
		m_wChairItemCount=0;

		//类型数目
		m_wUserGenreCount=0;
		m_wTableGenreCount=0;
		m_wChairGenreCount=0;

		//颜色属性
		m_crName=RGB(0,0,0);
		m_crMember=RGB(0,0,0);
		m_crMaster=RGB(0,0,0);

		//桌子属性
		m_SizeChair.SetSize(0,0);
		m_SizeTable.SetSize(0,0);
		m_SizeEnter.SetSize(0,0);

		//位置变量
		m_ptLock.SetPoint(0,0);
		m_ptEnter.SetPoint(0,0);
		m_ptTableID.SetPoint(0,0);

		//位置变量
		for (WORD i=0;i<MAX_CHAIR;i++)
		{
			m_ptReadyArray[i].SetPoint(0,0);
			m_rcNameArray[i].SetRect(0,0,0,0);
			m_rcChairArray[i].SetRect(0,0,0,0);
		}

		//辅助变量
		ZeroMemory(m_nDrawStyle,sizeof(m_nDrawStyle));
		ZeroMemory(m_szDirectory,sizeof(m_szDirectory));

		//设置变量
		m_SizeBackSurface.SetSize(0,0);

		//加载资源
		//m_ImageNumberBK.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_NUMBER_BK"));
		//m_ImageNumberNB.LoadImage(AfxGetInstanceHandle(),TEXT("TABLE_NUMBER_NB"));

		return;
	}

	//析构函数
	CTableResource::~CTableResource()
	{
		//释放资源
		DestroyResource();

		return;
	}

	//释放资源
	VOID CTableResource::DestroyResource()
	{
		//桌子属性
		m_SizeChair.SetSize(0,0);
		m_SizeTable.SetSize(0,0);

		//数目定义
		m_wTableItemCount=0;
		m_wChairItemCount=0;

		//输出控制
		ZeroMemory(m_nDrawStyle,sizeof(m_nDrawStyle));

		//位置属性
		ZeroMemory(&m_ptLock,sizeof(m_ptLock));
		ZeroMemory(m_rcNameArray,sizeof(m_rcNameArray));
		ZeroMemory(m_rcChairArray,sizeof(m_rcChairArray));
		ZeroMemory(m_ptReadyArray,sizeof(m_ptReadyArray));

		//颜色属性
		m_crName=RGB(0,0,0);
		m_crMember=RGB(0,0,0);
		m_crMaster=RGB(0,0,0);

		//释放位图
		m_ImageGround.DestroyImage();

		//释放位图
		m_ImageTable.DestroyImage();
		m_ImageChair.DestroyImage();
		m_ImageEnter.DestroyImage();
		m_ImageCustomUser.DestroyImage();

		//释放位图
		if(m_ImageBackSurface.IsNull()==false)
			m_ImageBackSurface.Destroy();

		m_ImageReady.DestroyImage();
		m_ImageLocker.DestroyImage();
		m_ImageNumberNB.DestroyImage();
		m_ImageNumberBK.DestroyImage();
		m_ImageUserFace.DestroyImage();

		return;
	}

	//加载资源
	bool CTableResource::LoadResource(LPCTSTR szGameName, WORD wChairCount, bool bAvertCheatMode)
	{
		DestroyResource();

		//效验参数
		ASSERT((szGameName!=NULL)&&(wChairCount<=MAX_CHAIR));
		if ((szGameName==NULL)||(wChairCount>MAX_CHAIR)) return false;

		//资源路径
		TCHAR szDirectory[MAX_PATH]=TEXT("");



		if(bAvertCheatMode)
			_sntprintf(m_szDirectory,CountArray(m_szDirectory),"%s\\GameLobby\\GameKind\\%s\\AvertCheatMode", 
											CString(g_GlobalUnits.GetWorkDirectory()),szGameName);
		else
			_sntprintf(m_szDirectory,CountArray(m_szDirectory),"%s\\GameLobby\\GameKind\\%s", 
											CString(g_GlobalUnits.GetWorkDirectory()),szGameName);

		//参数路径
		TCHAR szParameterFile[MAX_PATH]=TEXT("");
		_sntprintf(szParameterFile,CountArray(szParameterFile),TEXT("%s\\TableResource.INI"),m_szDirectory);

		//资源判断
		if(bAvertCheatMode)
		{
			//构造路径
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Table.png"),m_szDirectory);

			//加载资源
			CPngImage ImageTable;
			if (ImageTable.LoadImage(szImagePath)==false)
			{
				//资源路径
				ZeroMemory(m_szDirectory, sizeof(m_szDirectory));
				_sntprintf(m_szDirectory,CountArray(m_szDirectory),TEXT("%s\\AvertCheatMode"),szDirectory);

				//参数路径
				ZeroMemory(szParameterFile, sizeof(szParameterFile));
				_sntprintf(szParameterFile,CountArray(szParameterFile),TEXT("%s\\TableResource.INI"),m_szDirectory);
			}
		}

		//颜色变量
		ReadColor(m_crName,TEXT("Color"),TEXT("Color_Name"),szParameterFile);
		ReadColor(m_crMember,TEXT("Color"),TEXT("Color_Member"),szParameterFile);
		ReadColor(m_crMaster,TEXT("Color"),TEXT("Color_Master"),szParameterFile);

		//位置坐标
		ReadPoint(m_ptLock,TEXT("Position"),TEXT("Point_Lock"),szParameterFile);
		ReadPoint(m_ptEnter,TEXT("Position"),TEXT("Point_Enter"),szParameterFile);
		ReadPoint(m_ptTableID,TEXT("Position"),TEXT("Point_TableID"),szParameterFile);

		//显示属性
		m_bShowUser=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowUser"),1L,szParameterFile)==TRUE);
		m_bShowChair=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowChair"),1L,szParameterFile)==TRUE);
		m_bShowTable=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowTable"),1L,szParameterFile)==TRUE);
		m_bShowFocus=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowFocus"),1L,szParameterFile)==TRUE);
		m_bShowEnter=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowEnter"),0L,szParameterFile)==TRUE);
		m_bCustomUser=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("CustomUser"),0L,szParameterFile)==TRUE);
		m_bShowTableID=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("ShowTableID"),1L,szParameterFile)==TRUE);
		m_bRenderImage=(GetPrivateProfileInt(TEXT("Attribute"),TEXT("RenderImage"),1L,szParameterFile)==TRUE);

		//数目属性
		m_wTableItemCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("TableItemCount"),2L,szParameterFile);
		m_wChairItemCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("ChairItemCount"),wChairCount,szParameterFile);

		//类型数目
		m_wUserGenreCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("UserGenreCount"),1L,szParameterFile);
		m_wTableGenreCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("TableGenreCount"),1L,szParameterFile);
		m_wChairGenreCount=GetPrivateProfileInt(TEXT("Attribute"),TEXT("ChairGenreCount"),1L,szParameterFile);

		////更新资源
		//if(UpdateResource(CSkinRenderManager::GetInstance())==false)
		//{
		//	return false;
		//}
		//加载图片
		if(LoadResourceImages() == false)
			return false;

		//进入尺寸
		if (m_ImageEnter.IsNull()==false)
		{
			m_SizeEnter.SetSize(m_ImageEnter.GetWidth()/4,m_ImageEnter.GetHeight());
		}

		//椅子尺寸
		if (m_ImageChair.IsNull()==false)
		{
			m_SizeChair.SetSize(m_ImageChair.GetWidth()/m_wChairItemCount,m_ImageChair.GetHeight()/m_wChairGenreCount);
		}

		//桌子尺寸
		if (m_ImageTable.IsNull()==false)
		{
			m_SizeTable.SetSize(m_ImageTable.GetWidth()/m_wTableItemCount,m_ImageTable.GetHeight()/m_wTableGenreCount);
		}

		//用户尺寸
		if (m_ImageCustomUser.IsNull()==false)
		{
			m_SizeChair.SetSize(m_ImageCustomUser.GetWidth()/m_wChairItemCount,m_ImageCustomUser.GetHeight()/m_wUserGenreCount);
		}

		//位置坐标
		if (m_bShowTable==true && m_bShowUser==true)
		{
			for (WORD i=0;i<wChairCount;i++)
			{
				//变量定义
				TCHAR szSubItem[64]=TEXT("");
				//名字位置
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("Rect_Name%d"),i+1);
				ReadRect(m_rcNameArray[i],TEXT("Position"),szSubItem,szParameterFile);

				//准备位置
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("Point_Ready%d"),i+1);
				ReadPoint(m_ptReadyArray[i],TEXT("Position"),szSubItem,szParameterFile);

				//控制输出
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("DrawStyle%d"),i+1);
				m_nDrawStyle[i]=GetPrivateProfileInt(TEXT("Position"),szSubItem,0L,szParameterFile);

				//椅子位置
				POINT ChairPoint;
				_sntprintf(szSubItem,CountArray(szSubItem),TEXT("Point_Chair%d"),i+1);
				ReadPoint(ChairPoint,TEXT("Position"),szSubItem,szParameterFile);

				//椅子框架
				m_rcChairArray[i].top=ChairPoint.y;
				m_rcChairArray[i].left=ChairPoint.x;
				m_rcChairArray[i].right=m_rcChairArray[i].left+m_SizeChair.cx;
				m_rcChairArray[i].bottom=m_rcChairArray[i].top+m_SizeChair.cy;
			}
		}

		return true;
	}

	//更新资源
	bool CTableResource::LoadResourceImages()
	{
		////构造路径
		//TCHAR szImageGround[MAX_PATH]=TEXT("");
		//_sntprintf(szImageGround,CountArray(szImageGround),TEXT("%s\\Ground.bmp"),m_szDirectory);

		////加载背景
		//if (m_ImageGround.IsNull()==false)
		//{
		//	m_ImageGround.Destroy();
		//}

		////加载资源
		//if (FAILED(m_ImageGround.Load(szImageGround)))
		//{
		//	m_ImageGround.LoadFromResource(AfxGetInstanceHandle(),IDB_TABLE_GROUND);
		//}

		////渲染资源
		//if (m_bRenderImage==true)
		//{
		//	pSkinRenderManager->RenderImage(m_ImageGround);
		//}

		//进入位图

		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();
		if(!m_ImageReady.LoadImage(hInstance,PlazaViewImage.pszTableReady))
			return false;
		if(!m_ImageLocker.LoadImage(hInstance,PlazaViewImage.pszTableLocker))
			return false;

		if ((m_bShowEnter==true)&&(m_ImageEnter.IsNull()==true))
		{
			//构造路径
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Enter.png"),m_szDirectory);

			//加载资源
			if (m_ImageEnter.LoadImage(szImagePath)==false) return false;
		}

		//用户位图
		if ((m_bCustomUser==true)&&(m_ImageCustomUser.IsNull()==true))
		{
			//构造路径
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\CustomUser.png"),m_szDirectory);

			//加载资源
			if (m_ImageCustomUser.LoadImage(szImagePath)==false) return false;
		}

		//构造桌子
		if (m_bShowTable==true)
		{
			//构造路径
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Table.png"),m_szDirectory);

			//加载资源
			if (m_ImageTable.LoadImage(szImagePath)==false) return false;
		}

		//创建椅子
		if ((m_bShowChair==true)&&(m_bShowTable==true))
		{
			//构造路径
			TCHAR szImagePath[MAX_PATH]=TEXT("");
			_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\Chair.png"),m_szDirectory);

			//加载资源
			if (m_ImageChair.LoadImage(szImagePath)==false) return false;
		}

		////头像
		//{
		//	//加载资源
		//	CPngImage ImageUserFace;
		//	if (ImageUserFace.LoadImage(GetModuleHandle(AVATAR_CONTROL_DLL_NAME),TEXT("USER_FACE_IMAGE"))==false) return false;

		//	//创建资源
		//	if (m_ImageUserFace.IsNull()==true)
		//	{
		//		m_ImageUserFace.Create(ImageUserFace.GetWidth(),ImageUserFace.GetHeight(),32);
		//	}

		//	//填充背景
		//	CImageDC UserFaceDC(m_ImageUserFace);
		//	CDC * pUserFaceDC=CDC::FromHandle(UserFaceDC);
		//	m_ImageGround.DrawImageTile(pUserFaceDC,0,0,ImageUserFace.GetWidth(),ImageUserFace.GetHeight());

		//	//构造椅子
		//	ImageUserFace.DrawImage(pUserFaceDC,0,0,ImageUserFace.GetWidth(),ImageUserFace.GetHeight(),0,0);
		//}

		return true;
	}

	//读取数值
	LONG CTableResource::ReadStringValue(LPCTSTR & pszSring)
	{
		//效验参数
		ASSERT((pszSring!=NULL)&&(pszSring[0]!=0));
		if ((pszSring==NULL)||(pszSring[0]==0)) return 0L;

		//寻找开始
		while (((pszSring[0]>0)&&(pszSring[0]<TEXT('0')))||(pszSring[0]>TEXT('9'))) pszSring++;

		//读取数值
		LONG lValue=0L;
		while ((pszSring[0]>=TEXT('0'))&&(pszSring[0]<=TEXT('9')))
		{
			lValue=lValue*10L+pszSring[0]-TEXT('0');
			++pszSring;
		}

		return lValue;
	}

	//读取矩形
	bool CTableResource::ReadRect(RECT & ValueRect, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile)
	{
		//设置变量
		TCHAR szReadData[64]=TEXT("");
		ZeroMemory(&ValueRect,sizeof(ValueRect));

		//读取字符
		GetPrivateProfileString(pszItem,pszSubItem,TEXT(""),szReadData,CountArray(szReadData),pszIniFile);
		if (szReadData[0]!=0)
		{
			//读取变量
			LPCTSTR pszString=szReadData;
			ValueRect.left=ReadStringValue(pszString);
			ValueRect.top=ReadStringValue(pszString);
			ValueRect.right=ReadStringValue(pszString);
			ValueRect.bottom=ReadStringValue(pszString);

			return true;
		}

		return false;
	}

	//读取坐标
	bool CTableResource::ReadPoint(POINT & ValuePoint, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile)
	{
		//设置变量
		TCHAR szReadData[64]=TEXT("");
		ZeroMemory(&ValuePoint,sizeof(ValuePoint));

		//读取字符
		GetPrivateProfileString(pszItem,pszSubItem,TEXT(""),szReadData,CountArray(szReadData),pszIniFile);
		if (szReadData[0]!=0)
		{
			//读取变量
			LPCTSTR pszString=szReadData;
			ValuePoint.x=ReadStringValue(pszString);
			ValuePoint.y=ReadStringValue(pszString);

			return true;
		}

		return false;
	}

	//读取颜色
	bool CTableResource::ReadColor(COLORREF & ValueColor, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile)
	{
		//设置变量
		TCHAR szReadData[64]=TEXT("");
		ZeroMemory(&ValueColor,sizeof(ValueColor));

		//读取字符
		GetPrivateProfileString(pszItem,pszSubItem,TEXT(""),szReadData,CountArray(szReadData),pszIniFile);
		if (szReadData[0]!=0)
		{
			//读取变量
			LPCTSTR pszString=szReadData;
			ValueColor=RGB(ReadStringValue(pszString),ReadStringValue(pszString),ReadStringValue(pszString));

			return true;
		}

		return false;
	}


	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子构造
	//////////////////////////////////////////////////////////////////////////
	UITableItem::UITableItem(void)
	{
		//创建字体
		m_DrawFont.CreateFont(18,0,0,0,300,0,0,0,134,3,2,1,2,TEXT("黑体"));
		m_pTableInfo = NULL;
		m_pTableRes  = NULL;
		m_wHoverChairID = INVALID_CHAIR;
		m_bMouseDown = false;
		m_bFocus = false;
	}

	UITableItem::~UITableItem(void)
	{

	}

	// 创建控件
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

	// 绘制控件
	BOOL	UITableItem::Draw(CDC* pDC)
	{
		if (!IsWidgetVisible())
			return FALSE;
		pDC->SelectObject(&m_DrawFont);
		CPoint cPt = m_rect.TopLeft();
		
		DrawTableView(pDC,cPt.x,cPt.y);

		return UIWidget::Draw(pDC);
	}
	
	// 绘制桌子
	void	UITableItem::DrawTableView(CDC * pDC,INT nXTablePos,INT nYTablePos)
	{
		CSize SizeChair=m_pTableRes->m_SizeChair;
		CSize SizeTable=m_pTableRes->m_SizeTable;
		
		// 桌子
		if(!m_pTableInfo->bPlayStatus)
			m_pTableRes->m_ImageTable.DrawImage(pDC,nXTablePos,nYTablePos,SizeTable.cx,SizeTable.cy,0,0);
		else
			m_pTableRes->m_ImageTable.DrawImage(pDC,nXTablePos,nYTablePos,SizeTable.cx,SizeTable.cy,SizeTable.cx,0);

		// 百人房进入
		if ((m_pTableRes->m_bShowEnter==true)&&(m_pTableRes->m_ImageEnter.IsNull()==false))
		{
			//计算位置
			INT nImageIndex=0;
			if (m_pTableInfo->bPlayStatus == true)
				nImageIndex=1;
			if ((m_wHoverChairID==INDEX_ENTER_CHAIR)&&(m_pTableInfo->bPlayStatus==false)&&(m_bMouseDown==true))
				nImageIndex=2;
			if ((m_wHoverChairID==INDEX_ENTER_CHAIR)&&(m_pTableInfo->bPlayStatus==false)&&(m_bMouseDown==false))
				nImageIndex=3;

			//绘画标志
			CSize SizeEnter=m_pTableRes->m_SizeEnter;
			m_pTableRes->m_ImageEnter.DrawImage(pDC,nXTablePos + m_pTableRes->m_ptEnter.x,
				nYTablePos + m_pTableRes->m_ptEnter.y,SizeEnter.cx,SizeEnter.cy,SizeEnter.cx*nImageIndex,0);
			return ;
		}

		// 桌子ID
		TCHAR szTableID[256];
		sprintf(szTableID,_T("%d"),m_pTableInfo->wTableID);
		pDC->TextOut(nXTablePos+SizeTable.cx/2-3,nYTablePos+SizeTable.cy-17,szTableID);

		// 锁
		if (m_pTableInfo->bTableLock == true)
		{
			INT nXPos = nXTablePos + m_pTableRes->m_ptLock.x;
			INT nYPos = nYTablePos + m_pTableRes->m_ptLock.y;
			m_pTableRes->m_ImageLocker.DrawImage(pDC,nXPos,nYPos);
		}

		// 椅子
		if(m_pTableInfo->wChairCount < MAX_CHAIR)
		{
			for (WORD i=0;i<m_pTableInfo->wChairCount;i++)
			{
				//变量定义
				CRect rcChair=m_pTableRes->m_rcChairArray[i];
				////绘画椅子
				//if ((bAvertCheatMode==true)&&(m_pTableRes->m_bShowChair==true)&&(m_pTableRes->wTableID==0))
				//{
				//	ASSERT(m_pTableRes->m_ImageChair.IsNull()==false);
				//	m_pTableRes->m_ImageChair.DrawImage(pDC,rcChair.left,rcChair.top,SizeChair.cx,SizeChair.cy,SizeChair.cx*i,0);
				//}

				//绘画椅子
				if (/*(bAvertCheatMode==false)&&*/(m_pTableRes->m_bShowChair==true)&&(m_pTableInfo->pIUserItem[i]==NULL))
				{
					ASSERT(m_pTableRes->m_ImageChair.IsNull()==false);
					m_pTableRes->m_ImageChair.DrawImage(pDC,nXTablePos + rcChair.left, nYTablePos + rcChair.top,
						SizeChair.cx,SizeChair.cy,SizeChair.cx*i,0);
				}

				// 绘制椅子的边框
				if ((m_pTableRes->m_bCustomUser==true)&&(m_wHoverChairID==i))
				{
					pDC->Draw3dRect(nXTablePos + rcChair.left,nYTablePos + rcChair.top,
						rcChair.Width(),rcChair.Height(),RGB(125,125,125),RGB(125,125,125));
				}
			}
		}

		// 用户信息
		DrawAllUserInfo(pDC,nXTablePos,nYTablePos);
		
		////如果焦点在
		//if(m_bFocus && (m_pTableRes->m_bShowFocus==true))
		//	pDC->Draw3dRect(nXTablePos,nYTablePos,SizeTable.cx,SizeTable.cy,RGB(125,125,125),RGB(125,125,125));
	}

	// 绘制所有用户的名字
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
					// 变量定义
					CRect rcChair=m_pTableRes->m_rcChairArray[i];

					// 准备标志
					if((m_pTableInfo->bPlayStatus == false) && (US_READY == pUserData->cbUserStatus))
					{
						INT nXPos=m_pTableRes->m_ptReadyArray[i].x;
						INT nYPos=m_pTableRes->m_ptReadyArray[i].y;
						m_pTableRes->m_ImageReady.DrawImage(pDC,nXTablePos + nXPos, nYTablePos + nYPos);
					}

					// 用户头像
					if (m_pTableRes->m_bCustomUser==false)
					{
						//计算位置
						INT nXExcursion=(rcChair.Width()-FACE_CX)/2;
						INT nYExcursion=(rcChair.Height()-FACE_CY)/2;

						//绘画头像
						DrawUserAvatar(pDC,nXTablePos + rcChair.left+nXExcursion, nYTablePos + rcChair.top+nYExcursion,pUserData);
					}
					else
					{
						//自定头像
						INT nXImagePos=(i*rcChair.Width() >= m_pTableRes->m_ImageCustomUser.GetWidth())?0:i*rcChair.Width();
						INT nYImagePos=(pUserData->cbGender == GENDER_FEMALE)?rcChair.Height():0;
						m_pTableRes->m_ImageCustomUser.DrawImage(pDC,nXTablePos + rcChair.left,nYTablePos + rcChair.top,
							rcChair.Width(),rcChair.Height(),nXImagePos,nYImagePos);
					}

					// 用户名
					DrawUserName(pDC,i,pUserData->szName);
				}
			}
		}
	}

	// 绘制名字
	void	UITableItem::DrawUserName(CDC * pDC, WORD wChairID, LPCTSTR pszNickName)
	{
		//用户名字
		CRect rcName=m_pTableRes->m_rcNameArray[wChairID];
		POINT pot = m_rect.TopLeft();
		rcName += pot;
		//绘图计算
		CRect rcDrawRect=rcName;
		INT nNameLength=lstrlen(pszNickName);
		INT nDrawStyte=m_pTableRes->m_nDrawStyle[wChairID];
		INT nDrawFormat=DT_WORDBREAK|DT_EDITCONTROL|DT_END_ELLIPSIS;
		INT nNameHeight=pDC->DrawText(pszNickName,nNameLength,&rcDrawRect,nDrawFormat|DT_CALCRECT);

		//横向位置
		if (nNameHeight<=12)
		{
			if (nDrawStyte&NT_LEFT) nDrawFormat|=DT_LEFT;
			else if (nDrawStyte&NT_RIGHT) nDrawFormat|=DT_RIGHT;
			else nDrawFormat|=(DT_CENTER|DT_SINGLELINE);
		}
		else nDrawFormat|=DT_LEFT;

		//竖向位置
		INT nYPos=0;
		if (nDrawStyte&NT_BOTTOM) nYPos=rcName.Height()-nNameHeight;
		else if (nDrawStyte&NT_TOP) nYPos=0;
		else nYPos=(rcName.Height()-nNameHeight)/2;

		//构造位置
		rcDrawRect=rcName;
		rcDrawRect.left=rcName.left;
		rcDrawRect.right=rcName.right;
		rcDrawRect.top=__max(rcName.top,rcName.top+nYPos);
		rcDrawRect.bottom=__min(rcName.bottom,rcDrawRect.top+nNameHeight);

		//用户名字
		pDC->SetTextColor(m_pTableRes->m_crName);
		pDC->DrawText(pszNickName,nNameLength,&rcDrawRect,nDrawFormat);
	}

	// 绘制头像
	void	UITableItem::DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos, tagUserData* pUserData)
	{
		int nHeadNumberWidth	= m_UserHead.GetWidth() / 2;
		int nHeadNumberHeight	= m_UserHead.GetHeight(); 
		//// 掉线
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

	// 查询椅子
	WORD	UITableItem::SwitchChairID(POINT MousePoint)
	{
		TCHAR strLog[256];
		sprintf(strLog,"位置x：%d,y:%d \r\n",MousePoint.x,MousePoint.y);
		OutputDebugString(strLog);

		POINT Point =  m_rect.TopLeft();
		//位置搜索
		if ((m_pTableRes->m_bShowUser==true)||(m_pTableRes->m_bShowChair==true))
		{
			for (WORD i=0;i<m_pTableInfo->wChairCount;i++)
			{
				CRect ChairRC = m_pTableRes->m_rcChairArray[i] + Point;
				//横向判断
				if (MousePoint.x<ChairRC.left) continue;
				if (MousePoint.x>ChairRC.right) continue;

				//竖向判断
				if (MousePoint.y<ChairRC.top) continue;
				if (MousePoint.y>ChairRC.bottom) continue;

				return i;
			}
		}

		//进入区域
		if (m_pTableRes->m_bShowEnter==true)
		{
			//变量定义
			bool bOutSide=false;

			//横向判断
			if (MousePoint.x < (Point.x + m_pTableRes->m_ptEnter.x)) bOutSide=true;
			if (MousePoint.x > (Point.x + m_pTableRes->m_ptEnter.x + m_pTableRes->m_SizeEnter.cx)) bOutSide=true;

			//竖向判断
			if (MousePoint.y < (Point.y + m_pTableRes->m_ptEnter.y)) bOutSide=true;
			if (MousePoint.y > (Point.y + m_pTableRes->m_ptEnter.y + m_pTableRes->m_SizeEnter.cy)) bOutSide=true;

			//结果判断
			if (bOutSide==false)
			{
				return INDEX_ENTER_CHAIR;
			}
		}

		return INVALID_CHAIR;
	}

	// 鼠标移动
	BOOL	UITableItem::OnMouseMove(const CPoint& cPt)
	{
		m_wHoverChairID = SwitchChairID(cPt);
		if(m_wHoverChairID != INVALID_CHAIR)
		{
			// 设置鼠标为小手
			m_pAttach->PostMessage(WM_COMMAND,IDM_SETHANDCUR,1);
		}
		else
		{
			// 设置鼠标正常
			m_pAttach->PostMessage(WM_COMMAND,IDM_SETHANDCUR,0);
		}

		return TRUE;
	}

	// 鼠标离开
	BOOL	UITableItem::OnMouseLeave(const CPoint& cPt)
	{
		m_bFocus = false;
		return TRUE;
	}

	// 鼠标进入
	BOOL	UITableItem::OnMouseEnter(const CPoint& cPt)
	{
		m_bFocus = true;
		return TRUE;
	}

	// 左键按下
	BOOL	UITableItem::OnLeftDown(const CPoint& cPt)
	{
		m_bMouseDown = true;
		return TRUE;
	}

	// 左键弹起
	BOOL	UITableItem::OnLeftUp(const CPoint& cPt)
	{
		m_bMouseDown = false;
		if(m_wHoverChairID != INVALID_CHAIR)
			g_GlobalUnits.m_GameRoomManager.RequestSitdown(m_pTableInfo->wTableID,m_wHoverChairID);
		return TRUE;
	}


	//////////////////////////////////////////////////////////////////////////
	// 游戏桌子视图构造
	//////////////////////////////////////////////////////////////////////////
	UITablePage::UITablePage(void)
	{
		//创建字体
		m_DrawFont.CreateFont(18,0,0,0,300,0,0,0,134,3,2,1,2,TEXT("黑体"));
	}

	UITablePage::~UITablePage(void)
	{
	}

	// 创建控件
	BOOL	UITablePage::Create(INT nID, const RECT& rect, CWnd* pAttach, 
		UIProcess* pProcess, UIWidget* pParent)
	{
		BOOL bResult = UIWidget::Create(nID, rect, pAttach, pProcess, pParent);
		ASSERT(bResult == TRUE);

		//加载资源
		tagPlatViewImageNew & PlazaViewImage = g_GlobalUnits.m_PlazaViewImage;
		HINSTANCE hInstance = g_GlobalUnits.m_PlatformResourceModule->GetResInstance();

		// 标题图片
		m_TilteImage.LoadImage(hInstance,PlazaViewImage.pszTilteImage);

		// 快速加入
		UIPngButton* pBtFastJoin = new UIPngButton();
		pBtFastJoin->Create(102, rect.right - 150, 2, pAttach, this, hInstance, PlazaViewImage.pszBtFastJoin, 4, this);

		CRect rc;
		GetClientRect(&rc);
		// 绘制翻页按钮，上一页
		UIPngButton* pBtLast = new UIPngButton();
		pBtLast->Create(100, rc.right/2 - 84, rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLLast, 4, this);

		// 绘制翻页按钮，下一页
		UIPngButton* pBtNext = new UIPngButton();
		pBtNext->Create(101, rc.right/2 ,	  rc.bottom-28, pAttach, this, hInstance, PlazaViewImage.pszGLNext, 4, this);

		VisibleWidget(FALSE);
		return TRUE;
	}

	// 绘制
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

		// 如果是防作弊房
		if(!m_NoCheatImage.IsNull())
		{
			m_NoCheatImage.DrawImage(pDC,cPt.x + GTP_OFFSETX,cPt.y + GTP_OFFSETY-10);
		}
		return UIWidget::Draw(pDC);
	}

	// 响应页控件
	BOOL	UITablePage::OnClicked(UIWidget* pWidget, const CPoint& cPt)
	{
		if (pWidget)
		{
			switch(pWidget->GetID())
			{
			case 100:	// 上一页
				{
					OnClickLastPage();
					return TRUE;
				}
			case 101:	// 下一页
				{
					OnClickNextPage();
					return TRUE;
				}
			case 102:	//快速加入
				{
					if(!OnFastJoin())
						ShowMessageBox(_T("没能找到合适的位置！"),MB_ICONQUESTION);
					return TRUE;
				}

			}
		}
		return TRUE;
	}

	// 显示时响应函数
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
		// 百人房和防作弊场不显示下一页
		if(wSeverRule == ROOM_BAIREN || wSeverRule == ROOM_NOCHEAT)
		{
			Search(100)->VisibleWidget(false);
			Search(101)->VisibleWidget(false);
		}
	}

	// 不可见时触发函数
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

	// 响应上一页
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

	// 响应下一页
	void	UITablePage::OnClickNextPage()
	{
		m_EnumIndex += m_nXTableCount*m_nYTableCount;
		// 检查后面是否还有
		TableInfo*  pTableInfo = NULL;
		pTableInfo = g_GlobalUnits.m_GameRoomManager.EnumTableItem(m_EnumIndex);
		if (pTableInfo == NULL) 
		{
			m_EnumIndex -= m_nXTableCount*m_nYTableCount;
			return ;
		}
		EnumTableItem();
	}

	// 所有Item是否显示
	void	UITablePage::VisibleAllTableItem(bool bVisible)			
	{
		std::vector<UITableItem*>::iterator it = m_TableItemVector.begin();
		while(it != m_TableItemVector.end())
		{
			(*it)->VisibleWidget(bVisible);
			it++;
		}
	}

	// 枚举GameItem
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

	// 显示首页
	void	UITablePage::ShowFirstTablePage()
	{
		m_EnumIndex = 0;
		EnumTableItem();
	}

	// 快速加入
	bool	UITablePage::OnFastJoin()
	{
		return g_GlobalUnits.m_GameRoomManager.OnFastJoin();
	}

	//设置房间信息
	void	UITablePage::SetRoomInfo()
	{
		m_pListServer = g_GlobalUnits.m_GameRoomManager.m_pListServer;
		m_wTableCount = g_GlobalUnits.m_GameRoomManager.m_wTableCount;
		m_wChairCount = g_GlobalUnits.m_GameRoomManager.m_wChairCount;
	}

	//读取房间资源
	void	UITablePage::LoadTableRes()
	{
		TCHAR szGameName[128]=TEXT("");
		g_GlobalUnits.RemoveEXE(m_pListServer->GetListKind()->GetItemInfo()->szProcessName,
			szGameName,CountArray(szGameName));
		m_TableResource.LoadResource(szGameName,m_wChairCount,false);
	}

	//读取防作弊图片
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

	// 根据桌子的大小创建桌子
	bool	UITablePage::CreateTable()
	{	
		CRect rc;
		GetClientRect(&rc);
		INT nWidth	= rc.Width();
		INT	nHeight = rc.Height();

		if ((m_wTableCount == 0) || (m_TableResource.m_SizeTable.cx <= 0L) || (m_TableResource.m_SizeTable.cy <= 0L))
			return false;

		//变量定义
		INT nViewWidth  = __max(m_TableResource.m_SizeTable.cx,nWidth);
		INT nViewHeight = __max(m_TableResource.m_SizeTable.cy,nHeight);
		nViewHeight -= GTP_OFFSETY;

		//视图参数
		m_nXTableCount = nViewWidth  / m_TableResource.m_SizeTable.cx;
		m_nYTableCount = nViewHeight / m_TableResource.m_SizeTable.cy;

		INT nYExcursion = (nViewHeight-m_nYTableCount*m_TableResource.m_SizeTable.cy)/2;
		INT nXExcursion = (nViewWidth-m_nXTableCount*m_TableResource.m_SizeTable.cx)/2;
		nYExcursion += GTP_OFFSETY;

		// 桌子列表
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