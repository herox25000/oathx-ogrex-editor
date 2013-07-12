#include "StdAfx.h"
#include "Resource.h"
#include "SkinMenu.h"

//////////////////////////////////////////////////////////////////////////////////
//��������

//��϶����
#define SPACE_LEFT					8									//��϶��С
#define SPACE_RIGHT					3									//��϶��С

//��С����
#define MENU_BAR_CX					0									//����߶�
#define MENU_ITEM_CY				22									//����߶�
#define SEPARATOR_CY				3									//��ָ߶�

//����ƫ��
#define FRAME_OUT_CX                8                                  //��ܴ�С
#define FRAME_OUT_CY                8                                  //��ܴ�С
#define FRAME_IN_CX                 3                                  //��ܴ�С
#define FRAME_IN_CY                 3                                  //��ܴ�С 

//////////////////////////////////////////////////////////////////////////////////

//�˵�����
CMenuImageArray						CSkinMenu::m_MenuItemImage;			//ͼ������
CMenuStringArray					CSkinMenu::m_MenuItemString;		//�ַ�����
CMenuSeparatorArray					CSkinMenu::m_MenuItemSeparator;		//�������

//�ں˱���
CSkinMenuAttribute					CSkinMenuKernel::m_SkinAttribute;	//�˵�����
HWND								CSkinMenuKernel::m_hWnd=NULL;		//���ھ��
WNDPROC								CSkinMenuKernel::m_OldWndProc=NULL; //���ڹ��� 

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinMenuAttribute::CSkinMenuAttribute()
{
	//������ɫ
	m_crNormalText=RGB(0,0,0);	
	m_crSelectText=RGB(0,0,0);	

	//�߿���ɫ
	m_crMenuBar=RGB(0,0,0);	
	m_crSeparator=RGB(0,0,0);	
	m_crNormalBack=RGB(0,0,0);
	m_crSelectBack=RGB(0,0,0);	
	m_crSelectBorder=RGB(0,0,0);

	return;
}

//��������
CSkinMenuAttribute::~CSkinMenuAttribute() 
{
}

//������Դ
bool CSkinMenuAttribute::Initialization(CSkinRenderManager * pSkinRenderManager)
{
	//������ɫ
	m_crNormalText=pSkinRenderManager->RenderColor(0.99,0.29);
	m_crSelectText=pSkinRenderManager->RenderColor(1.95,0.75);

	//�߿���ɫ
	m_crMenuBar=pSkinRenderManager->RenderColor(0.35,0.51);
	m_crSeparator=pSkinRenderManager->RenderColor(0.95,0.90);
	m_crNormalBack=pSkinRenderManager->RenderColor(0.00,1.00);
	m_crSelectBack=pSkinRenderManager->RenderColor(0.23,0.88);
	m_crSelectBorder=pSkinRenderManager->RenderColor(0.66,0.87);
	m_crOutFrame = RGB(234,203,60);
	m_crInFrame = RGB(165,113,0);

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinMenuKernel::CSkinMenuKernel()
{
	//��ʶ����
	m_bRemoveBorder = FALSE;
	m_Messagehook = NULL;
}

//��������
CSkinMenuKernel::~CSkinMenuKernel()
{
	//ж�ع���
	if(m_bRemoveBorder==TRUE)
	{
		UnhookWindowsHookEx(m_Messagehook);
	}
}

//��ʶ����
VOID CSkinMenuKernel::SetRemoveBorder(HINSTANCE hInstance, BOOL bRemove) 
{ 
	//���ñ���
	m_bRemoveBorder=bRemove; 

	//���ù���
	if (m_bRemoveBorder==TRUE)
	{
		DWORD dwThreadID = ::GetCurrentThreadId();
		m_Messagehook = SetWindowsHookEx(WH_CALLWNDPROC,CallWndProc,hInstance,dwThreadID);
	}

	return;
}

//���ڹ���
LRESULT WINAPI CSkinMenuKernel::CallWndProc(INT code, WPARAM wParam, LPARAM lParam)
{
	//��������
	CWPSTRUCT* pStruct = (CWPSTRUCT*)lParam;	

	while (code == HC_ACTION)
	{
		// ɸѡ��Ϣ
		if ( pStruct->message != WM_CREATE)	break;

		//��������
		HWND hWnd = pStruct->hwnd;
		TCHAR sClassName[10];
		
		//��ȡ����
		int nCount = ::GetClassName(hWnd, sClassName, CountArray(sClassName));

		// �������
		if ( nCount != 6 ||  _tcscmp(sClassName, TEXT("#32768")) != 0 ) break;  

		//��������
		WNDPROC lastWndProc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);   
		if (lastWndProc != MenuWndProc)   
		{   
			// �滻���ڹ���  
			SetWindowLong(hWnd, GWL_WNDPROC, (long)MenuWndProc); 

			//���ñ���
			m_hWnd = hWnd;

			// ���洰�ڹ���   
			m_OldWndProc = lastWndProc;   
		}
		break;   
	}

	//���ù���
	return CallNextHookEx((HHOOK)WH_CALLWNDPROC, code, wParam, lParam); 
}

// �˵����ڹ���
LRESULT WINAPI CSkinMenuKernel::MenuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
	//��������
	LRESULT lResult;
	switch (message)   
	{      
	case WM_CREATE:  //������Ϣ
		{   
			//�޸���ʽ
			lResult = CallWindowProc(m_OldWndProc, hWnd, message, wParam, lParam);   
			DWORD dwStyle = ::GetWindowLong(hWnd,   GWL_STYLE);   
			DWORD dwNewStyle = (dwStyle & ~WS_BORDER);
			::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);   
			DWORD dwExStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
			DWORD dwNewExStyle = (dwExStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE));   
			::SetWindowLong(hWnd, GWL_EXSTYLE, dwNewExStyle);

			//ˢ�´���
			InvalidateRect(hWnd,NULL,TRUE);

			return lResult; 
		}   
	case WM_WINDOWPOSCHANGING:   
		{   
			LPWINDOWPOS lpPos = (LPWINDOWPOS)lParam;  
			lpPos->cx -= 2*GetSystemMetrics(SM_CXBORDER)+4-2*(FRAME_OUT_CX+FRAME_IN_CX);   
			lpPos->cy -= 2*GetSystemMetrics(SM_CYBORDER)+4-2*(FRAME_OUT_CY+FRAME_IN_CY);   
			lResult = CallWindowProc(m_OldWndProc, hWnd, message, wParam, lParam); 
		
			return 0;
		}
	case WM_PRINT: 
		{
			return CallWindowProc( m_OldWndProc, hWnd, WM_PRINTCLIENT, wParam, lParam);
		}
	case WM_GETICON:
		{
			return 0;    
		}
	default:
		{
			return  CallWindowProc( m_OldWndProc, hWnd, message, wParam, lParam);   
		}
	}   
}  

//�滭����
VOID CSkinMenuKernel::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//Ч�����
	ASSERT(lpDrawItemStruct->CtlType==ODT_MENU);
	if (lpDrawItemStruct->CtlType!=ODT_MENU) return;

	//��������
	CRect rcItem=lpDrawItemStruct->rcItem;
	CDC * pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CSkinMenuItem * pSkinMenuItem=(CSkinMenuItem *)lpDrawItemStruct->itemData;

	//�Ի���
	if(m_bRemoveBorder==TRUE)
	{
		//����ƫ��
		rcItem.OffsetRect(FRAME_OUT_CX+FRAME_IN_CX,FRAME_OUT_CY+FRAME_IN_CY);

		//��������
		CRect rcClient(0,0,0,0);		
		GetClientRect(m_hWnd,rcClient);

		//�������
		pDC->FillSolidRect(0,0,rcClient.Width(),FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);
		pDC->FillSolidRect(rcClient.right-FRAME_OUT_CX,FRAME_OUT_CY,FRAME_OUT_CX,rcClient.Height()-FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);
		pDC->FillSolidRect(0,rcClient.Height()-FRAME_OUT_CY,rcClient.Width()-FRAME_OUT_CX,FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);
		pDC->FillSolidRect(0,FRAME_OUT_CY,FRAME_OUT_CX,rcClient.Height()-FRAME_OUT_CY,m_SkinAttribute.m_crOutFrame);

		//�����ڿ�
		pDC->FillSolidRect(FRAME_OUT_CX,FRAME_OUT_CY,rcClient.Width()-2*FRAME_OUT_CX,FRAME_IN_CY,m_SkinAttribute.m_crInFrame);
		pDC->FillSolidRect(rcClient.right-FRAME_OUT_CX-FRAME_IN_CX,FRAME_OUT_CY,FRAME_IN_CX,rcClient.Height()-2*FRAME_OUT_CY,m_SkinAttribute.m_crInFrame);
		pDC->FillSolidRect(FRAME_OUT_CX,rcClient.Height()-FRAME_OUT_CY-FRAME_IN_CY,rcClient.Width()-2*FRAME_OUT_CX,FRAME_IN_CY,m_SkinAttribute.m_crInFrame);
		pDC->FillSolidRect(FRAME_OUT_CX,FRAME_OUT_CY,FRAME_IN_CX,rcClient.Height()-2*FRAME_OUT_CY,m_SkinAttribute.m_crInFrame);
	}

	//״̬����
	bool bChecked=((lpDrawItemStruct->itemState&ODS_CHECKED)!=0);
	bool bSelected=((lpDrawItemStruct->itemState&ODS_SELECTED)!=0);
	bool bGrayed=((lpDrawItemStruct->itemState&ODS_DISABLED)||(lpDrawItemStruct->itemState&ODS_GRAYED));

	//�滭����
	COLORREF crMenuBar=m_SkinAttribute.m_crMenuBar;
	COLORREF crBorder=m_SkinAttribute.m_crSelectBorder;
	COLORREF crNormalBack=m_SkinAttribute.m_crNormalBack;
	pDC->FillSolidRect(rcItem.left,rcItem.top,MENU_BAR_CX,rcItem.Height(),m_SkinAttribute.m_crMenuBar);
	pDC->FillSolidRect(rcItem.left+MENU_BAR_CX,rcItem.top,rcItem.Width()-MENU_BAR_CX,rcItem.Height(),m_SkinAttribute.m_crNormalBack);	

	//����߿�
	if ((bSelected==true)&&(bGrayed==false)&&(pSkinMenuItem!=NULL)&&(pSkinMenuItem->m_MenuItemType!=MenuItemType_Separator))
	{
		pDC->Draw3dRect(rcItem.left+1,rcItem.top+1,rcItem.Width()-2,rcItem.Height()-2,crBorder,crBorder);
		pDC->FillSolidRect(rcItem.left+2,rcItem.top+2,rcItem.Width()-4,rcItem.Height()-4,m_SkinAttribute.m_crSelectBack);
	}

	//ѡ���־
	if (bChecked==true)
	{
		//������Դ
		CBitImage ImageMenuFlags;
		ImageMenuFlags.LoadFromResource(GetModuleHandle(SKIN_CONTROL_DLL_NAME),IDB_SKIN_MENU_FLAGS);

		//��Ⱦ��Դ
		CSkinRenderManager * pSkinRenderManager=CSkinRenderManager::GetInstance();
		if (pSkinRenderManager!=NULL) pSkinRenderManager->RenderImage(ImageMenuFlags);

		//�滭����
		ImageMenuFlags.BitBlt(pDC->m_hDC,rcItem.left+1,rcItem.top+1,ImageMenuFlags.GetWidth()/2,
			ImageMenuFlags.GetHeight(),((bSelected==true)&&(bGrayed==false))?ImageMenuFlags.GetWidth()/2:0,0);
	}

	//�����˵�
	if (pSkinMenuItem==NULL)
	{
		//��ȡ��Ϣ
		MENUITEMINFO MenuItemInfo;
		MenuItemInfo.cbSize=sizeof(MenuItemInfo);
		MenuItemInfo.fMask=MIIM_FTYPE|MIIM_BITMAP;
		GetMenuItemInfo(lpDrawItemStruct->itemID,&MenuItemInfo);

		return;
	}

	//����˵�
	switch (pSkinMenuItem->m_MenuItemType)
	{
	case MenuItemType_Image:		//ͼ�β˵�
		{
			//��������
			CSkinMenuImage * pSkinMenuImage=(CSkinMenuImage *)pSkinMenuItem;

			//���� DC
			CDC ImageDC;
			ImageDC.CreateCompatibleDC(pDC);
			ImageDC.SelectObject(pSkinMenuImage->m_hBitmap);

			//��ȡ��Ϣ
			BITMAP BitmapInfo;
			GetObject(pSkinMenuImage->m_hBitmap,sizeof(BitmapInfo),&BitmapInfo);

			//�滭λͼ
			INT nYPos=rcItem.top+3;
			INT nXPos=rcItem.left+MENU_BAR_CX+SPACE_LEFT;
			pDC->BitBlt(nXPos,nYPos,BitmapInfo.bmWidth,BitmapInfo.bmHeight,&ImageDC,0,0,SRCCOPY);

			//�ͷ� DC
			ImageDC.DeleteDC();

			break;
		}
	case MenuItemType_String:		//�ַ��˵�
		{
			//��������
			CSkinMenuString * pSkinMenuString=(CSkinMenuString *)pSkinMenuItem;

			//������ɫ
			pDC->SetBkMode(TRANSPARENT);
			pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

			//������ɫ
			if (bGrayed==true) pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
			else if (bSelected==true) pDC->SetTextColor(m_SkinAttribute.m_crSelectText);
			else pDC->SetTextColor(m_SkinAttribute.m_crNormalText);

			//�滭�ַ�
			CRect rcString;
			rcString.top=rcItem.top;
			rcString.bottom=rcItem.bottom;
			rcString.right=rcItem.right-SPACE_RIGHT;
			rcString.left=rcItem.left+MENU_BAR_CX+SPACE_LEFT;
			pDC->DrawText(pSkinMenuString->m_strString,pSkinMenuString->m_strString.GetLength(),&rcString,DT_SINGLELINE|DT_VCENTER|DT_NOCLIP);

			break;
		}
	case MenuItemType_Separator:	//��ֲ˵�
		{
			//�滭���
			pDC->FillSolidRect(rcItem.left+MENU_BAR_CX+SPACE_LEFT,rcItem.top+1,rcItem.Width()-MENU_BAR_CX-SPACE_LEFT-SPACE_RIGHT,
				rcItem.Height()-2,m_SkinAttribute.m_crSeparator);

			break;
		}
	}

	return;
}

//����λ��
VOID CSkinMenuKernel::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	//Ч�����
	ASSERT(lpMeasureItemStruct->CtlType==ODT_MENU);
	if (lpMeasureItemStruct->CtlType!=ODT_MENU) return;

	//��ȡ����
	CSkinMenuItem * pSkinMenuItem=(CSkinMenuItem *)lpMeasureItemStruct->itemData;
	if (pSkinMenuItem==NULL)
	{
		//��ȡ��Ϣ
		MENUITEMINFO MenuItemInfo;
		MenuItemInfo.cbSize=sizeof(MenuItemInfo);
		MenuItemInfo.fMask=MIIM_FTYPE|MIIM_STRING;
		GetMenuItemInfo(lpMeasureItemStruct->itemID,&MenuItemInfo);

		return;
	}

	//����˵�
	switch (pSkinMenuItem->m_MenuItemType)
	{
	case MenuItemType_Image:		//ͼ�β˵�
		{
			//��������
			CSkinMenuImage * pSkinMenuImage=(CSkinMenuImage *)pSkinMenuItem;

			//��ȡ��Ϣ
			BITMAP BitmapInfo;
			GetObject(pSkinMenuImage->m_hBitmap,sizeof(BitmapInfo),&BitmapInfo);

			//�����С
			lpMeasureItemStruct->itemHeight=BitmapInfo.bmHeight+6;
			lpMeasureItemStruct->itemWidth=BitmapInfo.bmWidth+MENU_BAR_CX+SPACE_LEFT+SPACE_RIGHT;

			break;
		}
	case MenuItemType_String:		//�ַ��˵�
		{
			//��������
			CSkinMenuString * pSkinMenuString=(CSkinMenuString *)pSkinMenuItem;

			//���� DC
			HDC hDC=GetDC(NULL);
			SelectObject(hDC,CSkinResourceManager::GetInstance()->GetDefaultFont());

			//���㳤��
			CSize SizeString;
			GetTextExtentPoint32(hDC,pSkinMenuString->m_strString,pSkinMenuString->m_strString.GetLength(),&SizeString);

			//����λ��
			lpMeasureItemStruct->itemHeight=MENU_ITEM_CY;
			lpMeasureItemStruct->itemWidth=SizeString.cx+MENU_BAR_CX+SPACE_LEFT+SPACE_RIGHT;

			//�ͷ���Դ
			ReleaseDC(NULL,hDC);

			break;
		}
	case MenuItemType_Separator:	//��ֲ˵�
		{
			lpMeasureItemStruct->itemWidth=0;
			lpMeasureItemStruct->itemHeight=SEPARATOR_CY;

			break;
		}
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CSkinMenu::CSkinMenu()
{	
}

//��������
CSkinMenu::~CSkinMenu()
{
	DestroyMenu();
}

//�����˵�
bool CSkinMenu::CreateMenu()
{
	return m_SkinMenuKernel.CreatePopupMenu()?true:false;
}

//���ٲ˵�
bool CSkinMenu::DestroyMenu()
{
	//���ٲ˵�
	m_SkinMenuKernel.DestroyMenu();

	//�ͷ�����
	for (INT_PTR i=0;i<m_MenuItemActive.GetCount();i++)
	{
		FreeMenuItem(m_MenuItemActive[i]);
	}
	m_MenuItemActive.RemoveAll();

	return true;
}

//�����˵�
bool CSkinMenu::TrackPopupMenu(CWnd * pWnd)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);

	//�����˵�
	m_SkinMenuKernel.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,MousePoint.x,MousePoint.y,pWnd);

	return true;
}

//�����˵�
bool CSkinMenu::TrackPopupMenu(INT nXPos, INT nYPos, CWnd * pWnd)
{
	//�����˵�
	m_SkinMenuKernel.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,nXPos,nYPos,pWnd,NULL)?true:false;

	return true;
}

//������
bool CSkinMenu::AppendSeparator()
{
	//��ȡ����
	CSkinMenuSeparator * pSkinMenuItem=(CSkinMenuSeparator *)AcitveMenuItem(MenuItemType_Separator);

	//����˵�
	if (pSkinMenuItem!=NULL)
	{
		m_SkinMenuKernel.AppendMenu(MF_OWNERDRAW,0,(LPCTSTR)(pSkinMenuItem));
		return true;
	}

	return false;
}

//����λͼ
bool CSkinMenu::AppendMenu(UINT nMenuID, HBITMAP hBitmap, UINT nFlags)
{
	//�����ж�
	ASSERT((nFlags&MF_SEPARATOR)==0);
	if ((nFlags&MF_SEPARATOR)!=0) return false;

	//��ȡ����
	CSkinMenuImage * pSkinMenuItem=(CSkinMenuImage *)AcitveMenuItem(MenuItemType_Image);

	//����˵�
	if (pSkinMenuItem!=NULL)
	{
		pSkinMenuItem->m_hBitmap=hBitmap;
		m_SkinMenuKernel.AppendMenu(MF_OWNERDRAW|nFlags,nMenuID,(LPCTSTR)(pSkinMenuItem));
		return true;
	}

	return false;
}

//�����ַ�
bool CSkinMenu::AppendMenu(UINT nMenuID, LPCTSTR pszString, UINT nFlags)
{
	//�����ж�
	ASSERT((nFlags&MF_SEPARATOR)==0);
	if ((nFlags&MF_SEPARATOR)!=0) return false;

	//��ȡ����
	CSkinMenuString * pSkinMenuItem=(CSkinMenuString *)AcitveMenuItem(MenuItemType_String);

	//����˵�
	if (pSkinMenuItem!=NULL)
	{
		pSkinMenuItem->m_strString=pszString;
		m_SkinMenuKernel.AppendMenu(MF_OWNERDRAW|nFlags,nMenuID,(LPCTSTR)(pSkinMenuItem));
		return true;
	}

	return false;
}

//������
bool CSkinMenu::InsertSeparator(UINT nPosition)
{
	//��ȡ����
	CSkinMenuSeparator * pSkinMenuItem=(CSkinMenuSeparator *)AcitveMenuItem(MenuItemType_Separator);

	//����˵�
	if (pSkinMenuItem!=NULL)
	{
		m_SkinMenuKernel.InsertMenu(nPosition,MF_OWNERDRAW,0,(LPCTSTR)(pSkinMenuItem));
		return true;
	}

	return false;
}

//����λͼ
bool CSkinMenu::InsertMenu(UINT nMenuID, HBITMAP hBitmap, UINT nPosition, UINT nFlags)
{
	//�����ж�
	ASSERT((nFlags&MF_SEPARATOR)==0);
	if ((nFlags&MF_SEPARATOR)!=0) return false;

	//��ȡ����
	CSkinMenuImage * pSkinMenuItem=(CSkinMenuImage *)AcitveMenuItem(MenuItemType_Image);

	//����˵�
	if (pSkinMenuItem!=NULL)
	{
		pSkinMenuItem->m_hBitmap=hBitmap;
		m_SkinMenuKernel.InsertMenu(nPosition,MF_OWNERDRAW|nFlags,nMenuID,(LPCTSTR)(pSkinMenuItem));
		return true;
	}

	return false;
}

//�����ַ�
bool CSkinMenu::InsertMenu(UINT nMenuID, LPCTSTR pszString, UINT nPosition, UINT nFlags)
{
	//�����ж�
	ASSERT((nFlags&MF_SEPARATOR)==0);
	if ((nFlags&MF_SEPARATOR)!=0) return false;

	//��ȡ����
	CSkinMenuString * pSkinMenuItem=(CSkinMenuString *)AcitveMenuItem(MenuItemType_String);

	//����˵�
	if (pSkinMenuItem!=NULL)
	{
		pSkinMenuItem->m_strString=pszString;
		m_SkinMenuKernel.InsertMenu(nPosition,MF_OWNERDRAW|nFlags,nMenuID,(LPCTSTR)(pSkinMenuItem));
		return true;
	}

	return false;
}

//ɾ���˵�
bool CSkinMenu::RemoveMenu(UINT nPosition, UINT nFlags)
{
	return m_SkinMenuKernel.RemoveMenu(nPosition,nFlags)?true:false;
}

//�޸Ĳ˵�
bool CSkinMenu::ModifyMenu(UINT nMenuID, HBITMAP hBitmap, UINT nPosition, UINT nFlags)
{
	return 0;
}

//�޸Ĳ˵�
bool CSkinMenu::ModifyMenu(UINT nMenuID, LPCTSTR pszString, UINT nPosition, UINT nFlags)
{
	return 0;
}

//����Ĭ��
bool CSkinMenu::SetDefaultItem(UINT uItem, BOOL fByPos)
{
	return m_SkinMenuKernel.SetDefaultItem(uItem,fByPos)?true:false;
}

//ѡ�����
UINT CSkinMenu::CheckMenuItem(UINT nMenuID, UINT nCheck)
{
	return m_SkinMenuKernel.CheckMenuItem(nMenuID,nCheck)?true:false;
}

//���ÿ���
UINT CSkinMenu::EnableMenuItem(UINT nMenuID, UINT nEnable)
{
	return m_SkinMenuKernel.EnableMenuItem(nMenuID,nEnable)?true:false;
}

//�߿����
VOID CSkinMenu::RemoveMenuBorder(HINSTANCE hInstance, BOOL bRemove)
{
	//���ñ�ʶ
	m_SkinMenuKernel.SetRemoveBorder(hInstance,bRemove);

	return;
}

//�ͷ�����
VOID CSkinMenu::FreeMenuItem(CSkinMenuItem * pSkinMenuItem)
{
	//Ч�����
	ASSERT(pSkinMenuItem!=NULL);
	if (pSkinMenuItem==NULL) return;

	//�������
	switch (pSkinMenuItem->m_MenuItemType)
	{
	case MenuItemType_Image:		//ͼ������
		{
			//��������
			CSkinMenuImage * pSkinMenuImage=(CSkinMenuImage *)pSkinMenuItem;

			//���ñ���
			pSkinMenuImage->m_hBitmap=NULL;
			m_MenuItemImage.Add(pSkinMenuImage);

			break;
		}
	case MenuItemType_String:		//�ַ�����
		{
			//��������
			CSkinMenuString * pSkinMenuString=(CSkinMenuString *)pSkinMenuItem;

			//���ñ���
			pSkinMenuString->m_strString.Empty();
			m_MenuItemString.Add(pSkinMenuString);

			break;
		}
	case MenuItemType_Separator:	//�������
		{
			//��������
			CSkinMenuSeparator * pSkinMenuSeparator=(CSkinMenuSeparator *)pSkinMenuItem;

			//���ñ���
			m_MenuItemSeparator.Add(pSkinMenuSeparator);

			break;
		}
	}

	return;
}

//��ȡ����
CSkinMenuItem * CSkinMenu::AcitveMenuItem(enMenuItemType MenuItemType)
{
	//��������
	CSkinMenuItem * pSkinMenuItem=NULL;

	//��������
	switch (MenuItemType)
	{
	case MenuItemType_Image:		//ͼ������
		{
			if (m_MenuItemImage.GetCount()>0)
			{
				INT_PTR nItemCount=m_MenuItemImage.GetCount();
				pSkinMenuItem=m_MenuItemImage[nItemCount-1];
				m_MenuItemImage.RemoveAt(nItemCount-1);
			}
			else
			{
				pSkinMenuItem=new CSkinMenuImage;
				if (pSkinMenuItem==NULL) return NULL;
			}

			break;
		}
	case MenuItemType_String:		//�ַ�����
		{
			if (m_MenuItemString.GetCount()>0)
			{
				INT_PTR nItemCount=m_MenuItemString.GetCount();
				pSkinMenuItem=m_MenuItemString[nItemCount-1];
				m_MenuItemString.RemoveAt(nItemCount-1);
			}
			else
			{
				pSkinMenuItem=new CSkinMenuString;
				if (pSkinMenuItem==NULL) return NULL;
			}

			break;
		}
	case MenuItemType_Separator:	//�������
		{
			if (m_MenuItemSeparator.GetCount()>0)
			{
				INT_PTR nItemCount=m_MenuItemSeparator.GetCount();
				pSkinMenuItem=m_MenuItemSeparator[nItemCount-1];
				m_MenuItemSeparator.RemoveAt(nItemCount-1);
			}
			else
			{
				pSkinMenuItem=new CSkinMenuSeparator;
				if (pSkinMenuItem==NULL) return NULL;
			}

			break;
		}
	default:
		{
			ASSERT(FALSE);
			return NULL;
		}
	}

	//�������
	m_MenuItemActive.Add(pSkinMenuItem);

	return pSkinMenuItem;
}

//////////////////////////////////////////////////////////////////////////////////
