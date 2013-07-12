#include "StdAfx.h"
#include "ExDispID.h"
#include "GamePlaza.h"
#include "PlazaViewItem.h"
#include "PlatformFrame.h"

//////////////////////////////////////////////////////////////////////////////////

//�ؼ���ʶ
#define IDC_PLAZA_BROWSER			100									//����ؼ�

//ͼƬλ��
#define GAME_TITLE_CY				81									//����߶�
#define GAME_TITLE_CX				786									//������

//����λ��
#define GAME_KIND_ITEM_PX			2									//���ͼ��
#define GAME_KIND_ITEM_PY			5									//���ͼ��
#define GAME_KIND_ITEM_CX			187									//���Ϳ��
#define GAME_KIND_ITEM_CY			251									//���͸߶�

//����λ��
#define GAME_SERVER_ITEM_PX			2									//������
#define GAME_SERVER_ITEM_PY			5									//������
#define GAME_SERVER_ITEM_CX			187									//������
#define GAME_SERVER_ITEM_CY			210									//����߶�

//��ť��ʶ
#define IDC_BT_LAST_KIND			100									//��ҳ��ť
#define IDC_BT_NEXT_KIND			101									//��ҳ��ť
#define IDC_BT_RETURN_HALL          102                                 //���ذ�ť  
#define IDC_BT_LAST_SERVER			103 								//��ҳ��ť
#define IDC_BT_NEXT_SERVER			104									//��ҳ��ť

//////////////////////////////////////////////////////////////////////////////////

//��̬����
CPlazaViewItem * CPlazaViewItem::m_pPlazaViewItem=NULL;					//�㳡ָ��

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CPlazaViewItem, CDialog)

	//ϵͳ��Ϣ
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)

	//��ť��Ϣ
	ON_BN_CLICKED(IDC_BT_LAST_KIND, OnBnClickedLastKind)
	ON_BN_CLICKED(IDC_BT_NEXT_KIND, OnBnClickedNextKind)
	ON_BN_CLICKED(IDC_BT_RETURN_HALL,OnBnClickedReturnHall)
	ON_BN_CLICKED(IDC_BT_LAST_SERVER, OnBnClickedLastServer)
	ON_BN_CLICKED(IDC_BT_NEXT_SERVER, OnBnClickedNextServer)	

END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CPlazaViewItem::CPlazaViewItem() : CDialog(IDD_GAME_PLAZA)
{
	//���ñ���
	m_bHovering=false;
	m_bCreateFlag=false;
	m_cbShowItemMode=VIEW_MODE_NONE;

	//�ƶ�λ��
	m_cbButtonDown=0;
	m_cbButtonHover=0;
	m_wViewItemDown=INVALID_WORD;
	m_wViewItemHover=INVALID_WORD;

	//λ�ñ���
	m_wKindXCount=0;
	m_wKindYCount=0;
	m_wKindExcursion=0;
	m_wKindPageCount=0;
	m_wKindPageCurrent=0;
	m_wKindTypeCurrentID=0;

	//λ�ñ���
	m_wServerXCount=0;
	m_wServerYCount=0;
	m_wServerExcursion=0;
	m_wServerPageCount=0;
	m_wServerPageCurrent=0;

	//���ö���
	ASSERT(m_pPlazaViewItem==NULL);
	if (m_pPlazaViewItem==NULL) m_pPlazaViewItem=this;

	return;
}

//��������
CPlazaViewItem::~CPlazaViewItem()
{
	//ɾ������
	for (INT i=0;i<m_GameKindInfoActive.GetCount();i++)
	{
		SafeDelete(m_GameKindInfoActive[i]);
	}

	//ɾ������
	for (INT i=0;i<m_GameKindInfoBuffer.GetCount();i++)
	{
		SafeDelete(m_GameKindInfoBuffer[i]);
	}

	//ɾ������
	for (INT i=0;i<m_GameKindInfoActive.GetCount();i++)
	{
		SafeDelete(m_GameKindInfoActive[i]);
	}

	//ɾ������
	for (INT i=0;i<m_GameServerInfoBuffer.GetCount();i++)
	{
		SafeDelete(m_GameServerInfoBuffer[i]);
	}

	return;
}

//�ӿڲ�ѯ
VOID * CPlazaViewItem::QueryInterface(REFGUID Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE_IUNKNOWNEX(IUnknownEx,Guid,dwQueryVer);
	return NULL;
}

//��������
BOOL CPlazaViewItem::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	m_bCreateFlag=true;

	//������ť
	CRect rcCreate(0,0,0,0);
	m_btLastKind.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_LAST_KIND);
	m_btNextKind.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_NEXT_KIND);
	m_btReturnHall.Create(NULL,WS_CHILD,rcCreate,this,IDC_BT_RETURN_HALL);
	m_btLastServer.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_LAST_SERVER);
	m_btNextServer.Create(NULL,WS_CHILD|WS_DISABLED,rcCreate,this,IDC_BT_NEXT_SERVER);

	//���ð�ť
	HINSTANCE hInstance=AfxGetInstanceHandle();
	m_btLastKind.SetButtonImage(IDB_BT_KIND_ITEM_VIEW,TEXT("BT_LAST_KIND"),hInstance,true,false);
	m_btNextKind.SetButtonImage(IDB_BT_KIND_ITEM_VIEW,TEXT("BT_NEXT_KIND"),hInstance,true,false);
	m_btReturnHall.SetButtonImage(IDB_BT_KIND_ITEM_VIEW,TEXT("BT_RETURN_HALL"),hInstance,true,false);
	m_btLastServer.SetButtonImage(IDB_BT_SERVER_ITEM_VIEW,TEXT("BT_LAST_SERVER"),hInstance,true,false);
	m_btNextServer.SetButtonImage(IDB_BT_SERVER_ITEM_VIEW,TEXT("BT_NEXT_SERVER"),hInstance,true,false);

	return TRUE;
}

//��ʾ����
VOID CPlazaViewItem::ShowKindItemView(WORD wTypeID,BOOL bResetPageIndex)
{
	//��ȡ����
	ASSERT(CServerListData::GetInstance()!=NULL);
	CServerListData * pServerListData=CServerListData::GetInstance();

	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//��������
	POSITION Position=NULL;
	CGameKindItem * pGameKindItem=NULL;
	tagGameKindInfo * pGameKindInfo=NULL;

	//ɾ������
	for (INT i=0;i<m_GameKindInfoActive.GetCount();i++)
	{
		//��ȡ����
		ASSERT(m_GameKindInfoActive[i]!=NULL);
		pGameKindInfo=m_GameKindInfoActive[i];

		//���ñ���
		pGameKindInfo->wSortID=0;
		pGameKindInfo->pGameKindItem=NULL;

		//�������
		if (pGameKindInfo->ImageKindItem.IsNull()==false)
		{
			pGameKindInfo->ImageKindItem.DestroyImage();
		}
	}

	//ɾ������
	m_GameKindInfoBuffer.Append(m_GameKindInfoActive);
	m_GameKindInfoActive.RemoveAll();

	//�������
	while (true)
	{
		//��ȡ����
		pGameKindItem=pServerListData->EmunGameKindItem(Position);

		//�����ж�
		if (pGameKindItem==NULL) break;

		//�����ж�
		if ((wTypeID!=0)&&(pGameKindItem->m_GameKind.wTypeID!=wTypeID))
		{
			if (Position==NULL) break;
			if (Position!=NULL) continue;
		}

		//��ȡ����
		if (m_GameKindInfoBuffer.GetCount()>0L)
		{
			//��ȡ����
			INT_PTR nCount=m_GameKindInfoBuffer.GetCount();
			pGameKindInfo=m_GameKindInfoBuffer[nCount-1L];

			//ɾ������
			ASSERT(pGameKindInfo!=NULL);
			m_GameKindInfoBuffer.RemoveAt(nCount-1L);
		}
		else
		{
			try
			{
				pGameKindInfo=new tagGameKindInfo;
				if (pGameKindInfo==NULL) throw TEXT("��������ʧ��");
			}
			catch (...)
			{
				ASSERT(FALSE);
				break;
			}
		}

		//���ö���
		pGameKindInfo->pGameKindItem=pGameKindItem;
		pGameKindInfo->wSortID=pGameKindItem->m_GameKind.wSortID;

		//��ȡĿ¼
		TCHAR szGameDirectory[LEN_PROCESS]=TEXT("");
		GetGameDirectory(szGameDirectory,CountArray(szGameDirectory),pGameKindItem->m_GameKind);

		//����·��
		TCHAR szImagePath[MAX_PATH]=TEXT("");
		_sntprintf(szImagePath,CountArray(szImagePath),TEXT("%s\\ADImage\\GameKind\\GameKind_%s.PNG"),szDirectory,szGameDirectory);

		//����ͼƬ
		if (pGameKindInfo->ImageKindItem.LoadImage(szImagePath)==false)
		{
			HINSTANCE hInstance=AfxGetInstanceHandle();
			pGameKindInfo->ImageKindItem.LoadImage(hInstance,TEXT("UNKNOWN_KIND"));
		}

		//�������
		for (INT nItem=0;nItem<m_GameKindInfoActive.GetCount();nItem++)
		{
			//��ȡ����
			ASSERT(m_GameKindInfoActive[nItem]!=NULL);
			tagGameKindInfo * pGameKindTemp=m_GameKindInfoActive[nItem];

			//�����ж�
			if (pGameKindInfo->wSortID<pGameKindTemp->wSortID)
			{
				m_GameKindInfoActive.InsertAt(nItem,pGameKindInfo);
				break;
			}
		}

		//Ĭ�ϲ���
		if (nItem==m_GameKindInfoActive.GetCount())
		{
			m_GameKindInfoActive.Add(pGameKindInfo);
		}

		//�����ж�
		if (Position==NULL)
		{
			break;
		}
	}

	//���ñ���
	m_cbButtonDown=0;
	m_cbButtonHover=0;
	m_wKindTypeCurrentID=wTypeID;
	m_wViewItemDown=INVALID_WORD;
	m_wViewItemHover=INVALID_WORD;
	m_cbShowItemMode=VIEW_MODE_KIND;

	//��������
	if(bResetPageIndex==TRUE) m_wKindPageCurrent=0;

	//��������
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//��ʾ����
VOID CPlazaViewItem::ShowServerItemView(WORD wKindID,BOOL bResetPageIndex)
{
	//��ȡ����
	ASSERT(CServerListData::GetInstance()!=NULL);
	CServerListData * pServerListData=CServerListData::GetInstance();

	//��������
	ASSERT(pServerListData->SearchGameKind(wKindID)!=NULL);
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	CWHService::GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//��ȡĿ¼
	TCHAR szGameDirectory[LEN_PROCESS]=TEXT("");
	GetGameDirectory(szGameDirectory,CountArray(szGameDirectory),pGameKindItem->m_GameKind);

	//����·��
	TCHAR szImageTitle[MAX_PATH]=TEXT("");
	TCHAR szImageServer[MAX_PATH]=TEXT("");
	_sntprintf(szImageTitle,CountArray(szImageTitle),TEXT("%s\\ADImage\\GameTitle\\GameTitle_%s.PNG"),szDirectory,szGameDirectory);
	_sntprintf(szImageServer,CountArray(szImageServer),TEXT("%s\\ADImage\\GameTitle\\GameServer_%s.PNG"),szDirectory,szGameDirectory);

	//����ͼƬ
	if (m_ImageTitle.IsNull()==false) m_ImageTitle.DestroyImage();
	if (m_ImageServer.IsNull()==false) m_ImageServer.DestroyImage();

	//����ͼƬ
	if (m_ImageTitle.LoadImage(szImageTitle)==false)
	{
		HINSTANCE hInstance=AfxGetInstanceHandle();
		m_ImageTitle.LoadImage(hInstance,TEXT("UNKNOWN_TITLE"));
	}

	//����ͼƬ
	if (m_ImageServer.LoadImage(szImageServer)==false)
	{
		HINSTANCE hInstance=AfxGetInstanceHandle();
		m_ImageServer.LoadImage(hInstance,TEXT("UNKNOWN_SERVER"));
	}

	//��������
	POSITION Position=NULL;
	CGameServerItem * pGameServerItem=NULL;
	tagGameServerInfo * pGameServerInfo=NULL;

	//ɾ������
	for (INT i=0;i<m_GameServerInfoActive.GetCount();i++)
	{
		//��ȡ����
		ASSERT(m_GameServerInfoActive[i]!=NULL);
		pGameServerInfo=m_GameServerInfoActive[i];

		//���ñ���
		pGameServerInfo->wSortID=0;
		pGameServerInfo->wServerID=0;
		pGameServerInfo->pGameServerItem=NULL;
	}

	//ɾ������
	m_GameServerInfoBuffer.Append(m_GameServerInfoActive);
	m_GameServerInfoActive.RemoveAll();

	//�������
	while (true)
	{
		//��ȡ����
		pGameServerItem=pServerListData->EmunGameServerItem(Position);

		//�����ж�
		if (pGameServerItem==NULL) break;

		//�����ж�
		if (pGameServerItem->m_GameServer.wKindID!=wKindID)
		{
			if (Position==NULL) break;
			if (Position!=NULL) continue;
		}

		//��ȡ����
		if (m_GameServerInfoBuffer.GetCount()>0L)
		{
			//��ȡ����
			INT_PTR nCount=m_GameServerInfoBuffer.GetCount();
			pGameServerInfo=m_GameServerInfoBuffer[nCount-1L];

			//ɾ������
			ASSERT(pGameServerInfo!=NULL);
			m_GameServerInfoBuffer.RemoveAt(nCount-1L);
		}
		else
		{
			try
			{
				pGameServerInfo=new tagGameServerInfo;
				if (pGameServerInfo==NULL) throw TEXT("��������ʧ��");
			}
			catch (...)
			{
				ASSERT(FALSE);
				break;
			}
		}

		//���ö���
		pGameServerInfo->pGameServerItem=pGameServerItem;
		pGameServerInfo->wSortID=pGameServerItem->m_GameServer.wSortID;
		pGameServerInfo->wServerID=pGameServerItem->m_GameServer.wServerID;

		//�������
		for (INT nItem=0;nItem<m_GameServerInfoActive.GetCount();nItem++)
		{
			//��ȡ����
			ASSERT(m_GameServerInfoActive[nItem]!=NULL);
			tagGameServerInfo * pGameServerTemp=m_GameServerInfoActive[nItem];

			//�����ж�
			if (pGameServerInfo->wSortID<pGameServerTemp->wSortID)
			{
				m_GameServerInfoActive.InsertAt(nItem,pGameServerInfo);
				break;
			}
		}

		//Ĭ�ϲ���
		if (nItem==m_GameServerInfoActive.GetCount())
		{
			m_GameServerInfoActive.Add(pGameServerInfo);
		}

		//�����ж�
		if (Position==NULL)
		{
			break;
		}
	}

	//��Ч�ж�
	if (m_GameServerInfoActive.GetCount()==0)
	{
		//��ʾ��Ϣ
		CInformation Information;
		Information.ShowMessageBox(TEXT("����Ϸ��ʱû�п��Խ������Ϸ���䣬��ѡ��������Ϸ��"),MB_ICONINFORMATION,30L);

		return;
	}

	//���ñ���
	m_cbButtonDown=0;
	m_cbButtonHover=0;
	m_wViewItemDown=INVALID_WORD;
	m_wViewItemHover=INVALID_WORD;
	m_cbShowItemMode=VIEW_MODE_SERVER;

	//��������
	if(bResetPageIndex==TRUE) m_wServerPageCurrent=0;

	//��������
	CRect rcClient;
	GetClientRect(&rcClient);
	RectifyControl(rcClient.Width(),rcClient.Height());

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//λ����Ϣ
VOID CPlazaViewItem::OnSize(UINT nType, INT cx, INT cy)
{
	__super::OnSize(nType, cx, cy);

	//�����ؼ�
	RectifyControl(cx,cy);

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);

	return;
}

//��������
WORD CPlazaViewItem::GetHoverIndex(CPoint MousePoint)
{
	switch (m_cbShowItemMode)
	{
	case VIEW_MODE_KIND:	//������ͼ
		{
			//��Ч�ж�
			if (MousePoint.x<m_wKindExcursion) return INVALID_WORD;
			if (MousePoint.y<GAME_KIND_ITEM_PY) return INVALID_WORD;

			//λ�ü���
			INT nXItem=(MousePoint.x-m_wKindExcursion)/(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX);
			INT nYItem=(MousePoint.y-GAME_KIND_ITEM_PY)/(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY);

			//����ж�
			if ((MousePoint.x-m_wKindExcursion-(nXItem*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX)))>GAME_KIND_ITEM_CX) return INVALID_WORD;
			if ((MousePoint.y-GAME_KIND_ITEM_PY-(nYItem*(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY)))>GAME_KIND_ITEM_CY) return INVALID_WORD;

			//����ж�
			if ((nYItem>=0)&&(nXItem>=0)&&(nYItem<m_wKindYCount)&&(nXItem<m_wKindXCount))
			{
				WORD wViewCount=m_wKindXCount*m_wKindYCount;
				WORD wResultItem=nYItem*m_wKindXCount+nXItem;
				if ((m_wKindPageCurrent*wViewCount+wResultItem)<m_GameKindInfoActive.GetCount()) return wResultItem;
			}

			return INVALID_WORD;
		}
	case VIEW_MODE_SERVER:	//������ͼ
		{
			//��Ч�ж�
			if (MousePoint.x<m_wServerExcursion) return INVALID_WORD;
			if (MousePoint.y<GAME_SERVER_ITEM_PY) return INVALID_WORD;

			//λ�ü���
			INT nXItem=(MousePoint.x-m_wServerExcursion)/(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX);
			INT nYItem=(MousePoint.y-GAME_SERVER_ITEM_PY-GAME_TITLE_CY)/(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY);

			//����ж�
			if ((MousePoint.x-m_wServerExcursion-(nXItem*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX)))>GAME_SERVER_ITEM_CX) return INVALID_WORD;
			if ((MousePoint.y-GAME_SERVER_ITEM_PY-GAME_TITLE_CY-(nYItem*(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY)))>GAME_SERVER_ITEM_CY) return INVALID_WORD;

			//����ж�
			if ((nYItem>=0)&&(nXItem>=0)&&(nYItem<m_wServerYCount)&&(nXItem<m_wServerXCount))
			{
				WORD wViewCount=m_wServerXCount*m_wServerYCount;
				WORD wResultItem=nYItem*m_wServerXCount+nXItem;
				if ((m_wServerPageCurrent*wViewCount+wResultItem)<m_GameServerInfoActive.GetCount()) return wResultItem;
			}

			return INVALID_WORD;
		}
	}

	return INVALID_WORD;
}

//��ť����
BYTE CPlazaViewItem::GetHoverButton(WORD wViewIndex, CPoint MousePoint)
{
	//��Ч�ж�
	if (wViewIndex==INVALID_WORD) return 0;

	//��ť���
	switch (m_cbShowItemMode)
	{
	case VIEW_MODE_KIND:	//������ͼ
		{
			//����λ��
			MousePoint.x-=(m_wKindExcursion+(wViewIndex%m_wKindXCount)*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX));
			MousePoint.y-=(GAME_SERVER_ITEM_PY+(wViewIndex/m_wKindXCount)*(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY));

			//����λ��
			CRect rcViewRule(9,203,92,242);
			if (rcViewRule.PtInRect(MousePoint)==TRUE) return BT_VIEW_RULE;

			//���뷿��
			CRect rcEnterKind(94,203,176,242);
			if (rcEnterKind.PtInRect(MousePoint)==TRUE) return BT_ENTER_KIND;

			break;
		}
	case VIEW_MODE_SERVER:	//������ͼ
		{
			//����λ��
			MousePoint.x-=(m_wServerExcursion+(wViewIndex%m_wServerXCount)*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX));
			MousePoint.y-=(GAME_SERVER_ITEM_PY+GAME_TITLE_CY+(wViewIndex/m_wServerXCount)*(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY));

			//���뷿��
			CRect rcEnterServer(9,164,178,204);
			if (rcEnterServer.PtInRect(MousePoint)==TRUE) return BT_ENTER_SERVER;

			break;
		}
	}

	return 0;
}

//�鿴����
VOID CPlazaViewItem::OnButtonViewRule(WORD wKindID)
{
	//�����ַ
	TCHAR szRuleLink[MAX_PATH]=TEXT("");
	_sntprintf(szRuleLink,CountArray(szRuleLink),TEXT("%sGameDetails.aspx?KID=%ld"),szPlatformLink,wKindID);

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szRuleLink,NULL,NULL,SW_NORMAL);

	return;
}

//��������
VOID CPlazaViewItem::OnButtonEnterKind(WORD wKindID)
{
	//���Ҷ���
	CServerListData * pServerListData=CServerListData::GetInstance();
	CGameKindItem * pGameKindItem=pServerListData->SearchGameKind(wKindID);

	//�¼�����
	if (pGameKindItem!=NULL)
	{
		if (pGameKindItem->m_dwProcessVersion==0L)
		{
			//��װ��Ϸ
			CGlobalUnits * pGlobalUnits=CGlobalUnits::GetInstance();
			pGlobalUnits->DownLoadClient(pGameKindItem->m_GameKind.szKindName,wKindID,0);
		}
		else
		{
			//��ʾ����
			ShowServerItemView(wKindID);
		}
	}

	return;
}

//���뷿��
VOID CPlazaViewItem::OnButtonEnterServer(WORD wServerID)
{
	//��ȡ����
	CPlatformFrame * pPlatformFrame=CPlatformFrame::GetInstance();
	CServerListData * pServerListData=CServerListData::GetInstance();

	//���뷿��
	CGameServerItem * pGameServerItem=pServerListData->SearchGameServer(wServerID);
	if (pGameServerItem!=NULL) pPlatformFrame->EntranceServerItem(pGameServerItem);

	return;
}

//��ҳ��ť
VOID CPlazaViewItem::OnBnClickedLastKind()
{
	//Ч��״̬
	ASSERT(m_wKindPageCurrent>0);
	if (m_wKindPageCurrent==0) return;

	//��������
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//���ñ���
	m_wKindPageCurrent--;

	//���ư�ť
	m_btLastKind.EnableWindow((m_wKindPageCurrent>0)?TRUE:FALSE);
	m_btNextKind.EnableWindow(((m_wKindPageCurrent+1)<m_wKindPageCount)?TRUE:FALSE);

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//��ҳ��ť
VOID CPlazaViewItem::OnBnClickedNextKind()
{
	//Ч��״̬
	ASSERT((m_wKindPageCurrent+1)<m_wKindPageCount);
	if ((m_wKindPageCurrent+1)>=m_wKindPageCount) return;

	//��������
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//���ñ���
	m_wKindPageCurrent++;

	//���ư�ť
	m_btLastKind.EnableWindow((m_wKindPageCurrent>0)?TRUE:FALSE);
	m_btNextKind.EnableWindow(((m_wKindPageCurrent+1)<m_wKindPageCount)?TRUE:FALSE);

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//���ذ�ť
VOID CPlazaViewItem::OnBnClickedReturnHall()
{
	//��������
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//���ش���
	ShowKindItemView(m_wKindTypeCurrentID,FALSE);

	return;
}

//��ҳ��ť
VOID CPlazaViewItem::OnBnClickedLastServer()
{
	//Ч��״̬
	ASSERT(m_wServerPageCurrent>0);
	if (m_wServerPageCurrent==0) return;

	//��������
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//���ñ���
	m_wServerPageCurrent--;

	//���ư�ť
	m_btLastServer.EnableWindow((m_wServerPageCurrent>0)?TRUE:FALSE);
	m_btNextServer.EnableWindow(((m_wServerPageCurrent+1)<m_wServerPageCount)?TRUE:FALSE);

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//��ҳ��ť
VOID CPlazaViewItem::OnBnClickedNextServer()
{
	//Ч��״̬
	ASSERT((m_wServerPageCurrent+1)<m_wServerPageCount);
	if ((m_wServerPageCurrent+1)>=m_wServerPageCount) return;

	//��������
	CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
	if(pGlobalUnits!=NULL)
	{
		pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
	}

	//���ñ���
	m_wServerPageCurrent++;

	//���ư�ť
	m_btLastServer.EnableWindow((m_wServerPageCurrent>0)?TRUE:FALSE);
	m_btNextServer.EnableWindow(((m_wServerPageCurrent+1)<m_wServerPageCount)?TRUE:FALSE);

	//���½���
	RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);

	return;
}

//�滭����
BOOL CPlazaViewItem::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CBitImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//�����豸
	CImageDC BufferDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(BufferDC);

	//�滭����
	CBitImage ImageGround;
	ImageGround.LoadFromResource(AfxGetInstanceHandle(),IDB_PLAZA_GROUND);
	ImageGround.DrawImageTile(pBufferDC,0,0,rcClient.Width(),rcClient.Height());

	//�滭����
	switch (m_cbShowItemMode)
	{
	case VIEW_MODE_KIND:	//������ͼ
		{
			//��������
			WORD wViewCount=m_wKindXCount*m_wKindYCount;
			WORD wStartIndex=wViewCount*m_wKindPageCurrent;

			//�滭����
			for (WORD i=0;i<wViewCount;i++)
			{
				//����ж�
				if ((wStartIndex+i)>=m_GameKindInfoActive.GetCount())
				{
					break;
				}

				//����λ��
				INT nXDrawPos=m_wKindExcursion+(i%m_wKindXCount)*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX);
				INT nYDrawPos=GAME_KIND_ITEM_PY+(i/m_wKindXCount)*(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY);

				//�滭����
				tagGameKindInfo * pGameKindInfo=m_GameKindInfoActive[wStartIndex+i];
				if (pGameKindInfo!=NULL) DrawKindItem(pBufferDC,i,nXDrawPos,nYDrawPos,pGameKindInfo);
			}

			break;
		}
	case VIEW_MODE_SERVER:	//������ͼ
		{
			//��������
			WORD wViewCount=m_wServerXCount*m_wServerYCount;
			WORD wStartIndex=wViewCount*m_wServerPageCurrent;

			//�滭����
			m_ImageTitle.DrawImage(pBufferDC,(rcClient.Width()-GAME_TITLE_CX)/2,0,GAME_TITLE_CX,GAME_TITLE_CY,0,0);

			//�滭����
			for (WORD i=0;i<wViewCount;i++)
			{
				//����ж�
				if ((wStartIndex+i)>=m_GameServerInfoActive.GetCount())
				{
					break;
				}

				//����λ��
				INT nXDrawPos=m_wServerExcursion+(i%m_wServerXCount)*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX);
				INT nYDrawPos=GAME_TITLE_CY+GAME_SERVER_ITEM_PY+(i/m_wServerXCount)*(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY);

				//�滭����
				tagGameServerInfo * pGameServerInfo=m_GameServerInfoActive[wStartIndex+i];
				if (pGameServerInfo!=NULL) DrawServerItem(pBufferDC,i,nXDrawPos,nYDrawPos,pGameServerInfo);
			}

			break;
		}
	}

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	return TRUE;
}

//�������
VOID CPlazaViewItem::InValidateWndView(BYTE cbViewType)
{
	//ģʽ�ж�
	if(m_cbShowItemMode==cbViewType) InvalidateRect(NULL);

	return;
}

//�滭����
VOID CPlazaViewItem::DrawKindItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameKindInfo * pGameKindInfo)
{
	//Ч�����
	ASSERT(pGameKindInfo!=NULL);
	if (pGameKindInfo==NULL) return;

	//��װ�ж�
	bool bInstall=false;
	if (pGameKindInfo->pGameKindItem->m_dwProcessVersion!=0L) bInstall=true;

	//������Դ
	CPngImage ImageViewRule;
	CPngImage ImageEnterKind;
	ImageViewRule.LoadImage(AfxGetInstanceHandle(),TEXT("BT_VIEW_RULE"));
	ImageEnterKind.LoadImage(AfxGetInstanceHandle(),(bInstall==true)?TEXT("BT_ENTER_KIND"):TEXT("BT_INSTALL_GAME"));

	//��ȡ��С
	CSize SizeViewRule;
	CSize SizeEnterKind;
	SizeViewRule.SetSize(ImageViewRule.GetWidth()/5L,ImageViewRule.GetHeight());
	SizeEnterKind.SetSize(ImageEnterKind.GetWidth()/5L,ImageEnterKind.GetHeight());

	//�滭����
	if (pGameKindInfo->ImageKindItem.IsNull()==false)
	{
		CSize SizeImage;
		SizeImage.SetSize(pGameKindInfo->ImageKindItem.GetWidth(),pGameKindInfo->ImageKindItem.GetHeight());
		pGameKindInfo->ImageKindItem.DrawImage(pDC,nXPos,nYPos,GAME_KIND_ITEM_CX,GAME_KIND_ITEM_CY,0,0,SizeImage.cx,SizeImage.cy);
	}

	//�鿴����
	INT nXRuleIndex=0;
	bool bRuleButtonDown=((m_wViewItemDown==wViewIndex)&&(m_cbButtonDown==BT_VIEW_RULE));
	bool bRuleButtonHover=((m_wViewItemHover==wViewIndex)&&(m_cbButtonHover==BT_VIEW_RULE));

	//�鿴����
	if ((bRuleButtonHover==true)&&(bRuleButtonDown==true)) nXRuleIndex=1;
	if ((bRuleButtonHover==true)&&(bRuleButtonDown==false)) nXRuleIndex=2;
	ImageViewRule.DrawImage(pDC,nXPos+9,nYPos+203,SizeViewRule.cx,SizeViewRule.cy,nXRuleIndex*SizeViewRule.cx,0);

	//������Ϸ
	INT nXEnterIndex=0;
	bool bEnterButtonDown=((m_wViewItemDown==wViewIndex)&&(m_cbButtonDown==BT_ENTER_KIND));
	bool bEnterButtonHover=((m_wViewItemHover==wViewIndex)&&(m_cbButtonHover==BT_ENTER_KIND));

	//������Ϸ
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==true)) nXEnterIndex=1;
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==false)) nXEnterIndex=2;
	ImageEnterKind.DrawImage(pDC,nXPos+94,nYPos+203,SizeEnterKind.cx,SizeEnterKind.cy,nXEnterIndex*SizeEnterKind.cx,0);

	return;
}

//�滭����
VOID CPlazaViewItem::DrawServerItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameServerInfo * pGameServerInfo)
{
	//Ч�����
	ASSERT(pGameServerInfo!=NULL);
	if (pGameServerInfo==NULL) return;

	//������Դ
	CPngImage ImageEnterServer;
	ImageEnterServer.LoadImage(AfxGetInstanceHandle(),TEXT("BT_ENTER_SERVER"));

	//��ȡ��С
	CSize SizeEnterServer;
	SizeEnterServer.SetSize(ImageEnterServer.GetWidth()/5L,ImageEnterServer.GetHeight());

	//�滭����
	if (m_ImageServer.IsNull()==false)
	{
		CSize SizeImage;
		SizeImage.SetSize(m_ImageServer.GetWidth(),m_ImageServer.GetHeight());
		m_ImageServer.DrawImage(pDC,nXPos,nYPos,GAME_SERVER_ITEM_CX,GAME_SERVER_ITEM_CY,0,0,SizeImage.cx,SizeImage.cy);
	}

	//������Ϸ
	INT nXEnterIndex=0;
	bool bEnterButtonDown=((m_wViewItemDown==wViewIndex)&&(m_cbButtonDown==BT_ENTER_SERVER));
	bool bEnterButtonHover=((m_wViewItemHover==wViewIndex)&&(m_cbButtonHover==BT_ENTER_SERVER));

	//������Ϸ
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==true)) nXEnterIndex=1;
	if ((bEnterButtonHover==true)&&(bEnterButtonDown==false)) nXEnterIndex=2;
	ImageEnterServer.DrawImage(pDC,nXPos+9,nYPos+164,SizeEnterServer.cx,SizeEnterServer.cy,nXEnterIndex*SizeEnterServer.cx,0);

	//��������
	LPCTSTR szOnLineStatus[] = { TEXT("����"),TEXT("��æ"),TEXT("ӵ��"),TEXT("����") };
	INT nOnLineLevel[] = {20,100,200,0xfff};
	INT nOnLinetCount = pGameServerInfo->pGameServerItem->m_GameServer.dwOnLineCount;

	//����״̬
	TCHAR szServerOnLine[16]=TEXT("");
	for(BYTE cbIndex=0;cbIndex<CountArray(szOnLineStatus);++cbIndex)
	{
		if(nOnLinetCount<nOnLineLevel[cbIndex])
		{
			_sntprintf(szServerOnLine,CountArray(szServerOnLine),szOnLineStatus[cbIndex]);
			break;
		}
	}

	//��Ԫ����
	TCHAR szServerScore[32]=TEXT("");
	_sntprintf(szServerScore,CountArray(szServerScore),SCORE_STRING,pGameServerInfo->pGameServerItem->m_GameServer.lServerScore);

	//��Ҫ���
	TCHAR szMinServerScore[32]=TEXT("");
	_sntprintf(szMinServerScore,CountArray(szMinServerScore),SCORE_STRING,pGameServerInfo->pGameServerItem->m_GameServer.lMinServerScore);

	//��������
	TCHAR szServerName[LEN_SERVER]=TEXT("");
	_sntprintf(szServerName,CountArray(szServerName),TEXT("%s"),pGameServerInfo->pGameServerItem->m_GameServer.szServerName);

	//���û���
	pDC->SetBkColor(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭��Ϣ
	CRect rcOnlineCount(nXPos+78,nYPos+64,nXPos+168,nYPos+80);
	CRect rcServerName(nXPos+22,nYPos+133,nXPos+168,nYPos+149);
	CRect rcServerScore(nXPos+78,nYPos+87,nXPos+168,nYPos+103);
	CRect rcMinServerScore(nXPos+78,nYPos+110,nXPos+168,nYPos+126);
	pDC->DrawText(szServerName,lstrlen(szServerName),rcServerName,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);
	pDC->DrawText(szServerOnLine,lstrlen(szServerOnLine),rcOnlineCount,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);
	pDC->DrawText(szServerScore,lstrlen(szServerScore),rcServerScore,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);
	pDC->DrawText(szMinServerScore,lstrlen(szMinServerScore),rcMinServerScore,DT_SINGLELINE|DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS);

	return;
}

//�����ؼ�
VOID CPlazaViewItem::RectifyControl(INT nWidth, INT nHeight)
{
	//״̬�ж�
	if (m_bCreateFlag==false) return;
	if ((nWidth==0)||(nHeight==0)) return;

	//��ť��С
	CRect rcButton;
	m_btLastKind.GetWindowRect(&rcButton);

	//����λ��
	m_wKindXCount=(nWidth+GAME_KIND_ITEM_PX)/(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX);
	m_wKindYCount=(nHeight+GAME_KIND_ITEM_PY)/(GAME_KIND_ITEM_CY+GAME_KIND_ITEM_PY);
	m_wKindExcursion=(nWidth+GAME_KIND_ITEM_PX-m_wKindXCount*(GAME_KIND_ITEM_CX+GAME_KIND_ITEM_PX))/2;

	//����ҳ��
	WORD wViewCountKind=m_wKindXCount*m_wKindYCount;
	m_wKindPageCount=(WORD)(m_GameKindInfoActive.GetCount()+wViewCountKind-1)/wViewCountKind;
	m_wKindPageCurrent=(WORD)__min(m_GameKindInfoActive.GetCount()/wViewCountKind,m_wKindPageCurrent);

	//����λ��
	m_wServerXCount=(nWidth+GAME_SERVER_ITEM_PX)/(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX);
	m_wServerYCount=(nHeight+GAME_SERVER_ITEM_PY)/(GAME_SERVER_ITEM_CY+GAME_SERVER_ITEM_PY);
	m_wServerExcursion=(nWidth+GAME_SERVER_ITEM_PX-m_wServerXCount*(GAME_SERVER_ITEM_CX+GAME_SERVER_ITEM_PX))/2;

	//����ҳ��
	WORD wViewCountServer=m_wServerXCount*m_wServerYCount;
	m_wServerPageCount=(WORD)(m_GameServerInfoActive.GetCount()+wViewCountServer-1)/(m_wServerXCount*m_wServerYCount);
	m_wServerPageCurrent=(WORD)__min(m_GameServerInfoActive.GetCount()/(m_wServerXCount*m_wServerYCount),m_wServerPageCurrent);

	//��ť����
	m_btLastKind.EnableWindow((m_wKindPageCurrent>0)?TRUE:FALSE);
	m_btNextKind.EnableWindow(((m_wKindPageCurrent+1)<m_wKindPageCount)?TRUE:FALSE);

	//��ť����
	m_btLastServer.EnableWindow((m_wServerPageCurrent>0)?TRUE:FALSE);
	m_btNextServer.EnableWindow(((m_wServerPageCurrent+1)<m_wServerPageCount)?TRUE:FALSE);

	//��������
	HDWP hDwp=BeginDeferWindowPos(64);
	UINT uFlags=SWP_NOACTIVATE|SWP_NOCOPYBITS|SWP_NOZORDER|SWP_NOSIZE;

	//���Ͱ�ť
	UINT uKindFlags=(m_cbShowItemMode==VIEW_MODE_KIND)?SWP_SHOWWINDOW:SWP_HIDEWINDOW;
	DeferWindowPos(hDwp,m_btLastKind,NULL,m_wKindExcursion+2,nHeight-rcButton.Height()-2,0,0,uFlags|uKindFlags);
	DeferWindowPos(hDwp,m_btNextKind,NULL,nWidth-rcButton.Width()-m_wKindExcursion-2,nHeight-rcButton.Height()-2,0,0,uFlags|uKindFlags);

	//���䰴ť
	CRect rcButtonServer;
	m_btLastServer.GetWindowRect(&rcButtonServer);
	UINT uServerFlags=(m_cbShowItemMode==VIEW_MODE_SERVER)?SWP_SHOWWINDOW:SWP_HIDEWINDOW;
	DeferWindowPos(hDwp,m_btReturnHall,NULL,m_wServerExcursion+2,nHeight-rcButton.Height()-2,0,0,uFlags|uServerFlags);
	DeferWindowPos(hDwp,m_btLastServer,NULL,nWidth/2+2,nHeight-rcButtonServer.Height()-2,0,0,uFlags|uServerFlags);
	DeferWindowPos(hDwp,m_btNextServer,NULL,nWidth/2+rcButtonServer.Width()+6,nHeight-rcButtonServer.Height()-2,0,0,uFlags|uServerFlags);

	//��������
	EndDeferWindowPos(hDwp);

	return;
}

//��ԴĿ¼
VOID CPlazaViewItem::GetGameDirectory(TCHAR szDirectory[], WORD wBufferCount, tagGameKind & GameKind)
{
	//��������
	WORD wStringIndex=0;

	//����Ŀ¼
	ZeroMemory(szDirectory,wBufferCount*sizeof(TCHAR));
	lstrcpyn(szDirectory,GameKind.szProcessName,wBufferCount);

	//����Ŀ¼
	while ((szDirectory[wStringIndex]!=0)&&(szDirectory[wStringIndex]!=TEXT('.')))
	{
		wStringIndex++;
	}

	//�ַ���ֹ
	szDirectory[wStringIndex]=0;

	return;
}

//�����Ϣ
VOID CPlazaViewItem::OnMouseMove(UINT nFlags, CPoint Point)
{
	__super::OnMouseMove(nFlags, Point);

	//����λ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//λ�ü���
	WORD wViewItemHover=GetHoverIndex(Point);
	BYTE cbButtonHover=GetHoverButton(wViewItemHover,Point);

	//���ݵ���
	if ((m_wViewItemDown!=INVALID_WORD)&&(m_cbButtonDown!=0))
	{
		if (cbButtonHover!=m_cbButtonDown) cbButtonHover=0;
		if (wViewItemHover!=m_wViewItemDown) wViewItemHover=INVALID_WORD;
	}

	//��������
	if ((wViewItemHover!=m_wViewItemHover)||(m_cbButtonHover!=cbButtonHover))
	{
		//���ñ���
		m_cbButtonHover=cbButtonHover;
		m_wViewItemHover=wViewItemHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE|RDW_UPDATENOW|RDW_ERASENOW);
	}

	//�����ж�
	if (m_bHovering==false)
	{
		//���ñ���
		m_bHovering=true;

		//��������
		TRACKMOUSEEVENT TrackMouseEvent;
		ZeroMemory(&TrackMouseEvent,sizeof(TrackMouseEvent));

		//ע����Ϣ
		TrackMouseEvent.hwndTrack=m_hWnd;
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);

		//ע���¼�
		_TrackMouseEvent(&TrackMouseEvent);
	}

	return;
}

//�����Ϣ
VOID CPlazaViewItem::OnLButtonUp(UINT nFlags, CPoint Point)
{
	__super::OnLButtonUp(nFlags,Point);

	//�������
	BYTE cbButtonDown=0;
	WORD wViewItemDown=INVALID_WORD;

	//���ñ���
	if ((m_wViewItemDown!=INVALID_WORD)&&(m_wViewItemDown==m_wViewItemHover)&&(m_cbButtonDown==m_cbButtonHover))
	{
		cbButtonDown=m_cbButtonDown;
		wViewItemDown=m_wViewItemDown;
	}

	//������
	if ((m_wViewItemDown!=INVALID_WORD)&&(m_cbButtonDown!=0))
	{
		//�ͷ����
		ReleaseCapture();

		//���ñ���
		m_cbButtonDown=0;
		m_wViewItemDown=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);
	}

	//ִ�ж���
	if ((wViewItemDown!=INVALID_WORD)&&(cbButtonDown!=0))
	{
		//��������
		CGlobalUnits * pGlobalUnits = CGlobalUnits::GetInstance();
		if(pGlobalUnits!=NULL)
		{
			pGlobalUnits->PlayPlazaSound(AfxGetInstanceHandle(), TEXT("BUTTON_MOVE"));
		}

		switch (cbButtonDown)
		{
		case BT_VIEW_RULE:		//�鿴����
			{
				//�鿴����
				WORD wViewCount=m_wKindXCount*m_wKindYCount*m_wKindPageCurrent;
				tagGameKindInfo * pGameKindInfo=m_GameKindInfoActive[wViewCount+wViewItemDown];
				if (pGameKindInfo!=NULL) OnButtonViewRule(pGameKindInfo->pGameKindItem->m_GameKind.wKindID);

				break;
			}
		case BT_ENTER_KIND:		//��������
			{
				//��������
				WORD wViewCount=m_wKindXCount*m_wKindYCount*m_wKindPageCurrent;
				tagGameKindInfo * pGameKindInfo=m_GameKindInfoActive[wViewCount+wViewItemDown];
				if (pGameKindInfo!=NULL) OnButtonEnterKind(pGameKindInfo->pGameKindItem->m_GameKind.wKindID);

				break;
			}
		case BT_ENTER_SERVER:	//���뷿��
			{
				//���뷿��
				WORD wViewCount=m_wServerXCount*m_wServerYCount*m_wServerPageCurrent;
				tagGameServerInfo * pGameServerInfo=m_GameServerInfoActive[wViewCount+wViewItemDown];
				if (pGameServerInfo!=NULL) OnButtonEnterServer(pGameServerInfo->pGameServerItem->m_GameServer.wServerID);

				break;
			}
		}
	}

	return;
}

//�����Ϣ
VOID CPlazaViewItem::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//���ý���
	SetFocus();

	//���´���
	if ((m_wViewItemHover!=INVALID_WORD)&&(m_cbButtonHover!=0))
	{
		//����˻�
		SetCapture();

		//���ñ���
		m_cbButtonDown=m_cbButtonHover;
		m_wViewItemDown=m_wViewItemHover;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);
	}

	return;
}

//�����Ϣ
LRESULT CPlazaViewItem::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//����״̬
	m_bHovering=false;

	//���½���
	if (m_wViewItemHover!=INVALID_WORD)
	{
		//���ñ���
		m_cbButtonDown=0;
		m_cbButtonHover=0;
		m_wViewItemDown=INVALID_WORD;
		m_wViewItemHover=INVALID_WORD;

		//���½���
		RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_ERASE);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
