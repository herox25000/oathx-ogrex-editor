#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	///////////////////////////////////////////////////////////////////
	//������Դ
	//////////////////////////////////////////////////////////////////
	class CTableResource
	{
		//��������
	public:
		CSize							m_SizeChair;						//���ӳߴ�
		CSize							m_SizeTable;						//���ӳߴ�
		CSize							m_SizeEnter;						//����ߴ�

		//���Ա���
	public:
		bool							m_bShowUser;						//��ʾ�û�
		bool							m_bShowEnter;						//��ʾ����
		bool							m_bShowChair;						//��ʾ����
		bool							m_bShowTable;						//��ʾ����
		bool							m_bShowFocus;						//��ʾ����
		bool							m_bCustomUser;						//�Զ��û�
		bool							m_bShowTableID;						//��ʾ����
		bool							m_bRenderImage;						//��Ⱦ��־

		//��Ŀ����
	public:
		WORD							m_wTableItemCount;					//������Ŀ
		WORD							m_wChairItemCount;					//������Ŀ

		//������Ŀ
	public:
		WORD							m_wUserGenreCount;					//������Ŀ
		WORD							m_wTableGenreCount;					//������Ŀ
		WORD							m_wChairGenreCount;					//������Ŀ

		//λ������
	public:
		CPoint							m_ptLock;							//����λ��
		CPoint							m_ptEnter;							//����λ��
		CPoint							m_ptTableID;						//����λ��
		CPoint							m_ptReadyArray[MAX_CHAIR];			//׼��λ��

		//���λ��
	public:
		CRect							m_rcNameArray[MAX_CHAIR];			//����λ��
		CRect							m_rcChairArray[MAX_CHAIR];			//����λ��

		//��ɫ����
	public:
		COLORREF						m_crName;							//������ɫ
		COLORREF						m_crMember;							//��Ա��ɫ
		COLORREF						m_crMaster;							//������ɫ

		//��������
	public:
		INT								m_nDrawStyle[MAX_CHAIR];			//�����ʽ
		TCHAR							m_szDirectory[MAX_PATH];			//��Դ·��

		//��Դ����
	public:
		CSize							m_SizeBackSurface;					//�����С
		CImage							m_ImageBackSurface;					//�������

		//�ⲿ��Դ
	public:
		CPngImage                       m_ImageChair;						//����λͼ 
		CPngImage						m_ImageEnter;						//����λͼ
		CPngImage                       m_ImageTable;						//����λͼ
		//CBitImage						m_ImageGround;						//����λͼ
		CPngImage						m_ImageGround;	
		CPngImage						m_ImageCustomUser;					//�Զ�λͼ

		//�ڲ���Դ
	public:
		CPngImage						m_ImageReady;						//׼��λͼ
		CPngImage						m_ImageLocker;						//����λͼ
		CPngImage						m_ImageNumberNB;					//����λͼ
		CPngImage						m_ImageNumberBK;					//���뱳��
		//CBitImage						m_ImageUserFace;					//�û�ͷ��
		CPngImage						m_ImageUserFace;					//�û�ͷ��
		//��������
	public:
		//���캯��
		CTableResource();
		//��������
		virtual ~CTableResource();

		//���ܺ���
	public:
		//�ͷ���Դ
		VOID DestroyResource();
		//������Դ
		bool LoadResource(LPCTSTR szGameName, WORD wChairCount, bool bAvertCheatMode);
		//������Դ
		//bool UpdateResource(CSkinRenderManager * pSkinRenderManager);
		//����ͼƬ
		bool LoadResourceImages();

		//��������
	protected:
		//��ȡ��ֵ
		LONG ReadStringValue(LPCTSTR & pszSring);
		//��ȡ����
		bool ReadRect(RECT & ValueRect, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile);
		//��ȡ����
		bool ReadPoint(POINT & ValuePoint, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile);
		//��ȡ��ɫ
		bool ReadColor(COLORREF & ValueColor, LPCTSTR pszItem, LPCTSTR pszSubItem, LPCTSTR pszIniFile);
	};

	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ���ӹ���
	//////////////////////////////////////////////////////////////////////////
	class UITableItem : public UIWidget, public UIProcess
	{
	public:
		UITableItem(void);

		virtual ~UITableItem(void);

		// UIWidget �̳�
	public:
		// �����ؼ�
		virtual	BOOL		Create(INT nID, INT nDestX, INT nDestY,
			CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		// ����
		virtual BOOL		Draw(CDC* pDC);
		// ����ƶ�
		virtual BOOL		OnMouseMove(const CPoint& cPt);
		// ����뿪
		virtual BOOL		OnMouseLeave(const CPoint& cPt);
		// ������
		virtual BOOL		OnMouseEnter(const CPoint& cPt);
		// �������
		virtual BOOL		OnLeftDown(const CPoint& cPt);
		// �������
		virtual BOOL		OnLeftUp(const CPoint& cPt);

	//	// UIProcess�̳�
	//public:
	//	// �������
	//	virtual BOOL		OnLeftDown(UIWidget* pWidget,const CPoint& cPt);
	//	// �������
	//	virtual BOOL		OnLeftUp(UIWidget* pWidget,const CPoint& cPt);

		// ���ܺ���
	public:
		// ��������
		void				DrawTableView(CDC * pDC,INT nXTablePos,INT nYTablePos);
		// ���������û���Ϣ
		void				DrawAllUserInfo(CDC* pDC,INT nXTablePos,INT nYTablePos);
		// ��������
		void				DrawUserName(CDC * pDC, WORD wChairID, LPCTSTR pszNickName);		
		// ����ͷ��
		void				DrawUserAvatar(CDC * pDC, INT nXPos, INT nYPos,tagUserData* pUserData);
		// ��ѯ����
		WORD				SwitchChairID(POINT MousePoint);

	protected:
		CPngImage			m_PngBill;
	

	public:
		TableInfo*			m_pTableInfo;	//������Ϣ
		CTableResource*		m_pTableRes;	//������Դ��Ϣ	
		CPngImage			m_UserHead;
		CFont				m_DrawFont;	
		WORD				m_wHoverChairID;
		bool				m_bMouseDown;
		bool				m_bFocus;		// �Ƿ��ǽ���
	};


	//////////////////////////////////////////////////////////////////////////
	// ��Ϸ������ͼ����
	//////////////////////////////////////////////////////////////////////////
	class UITablePage : public UIWidget, public UIProcess
	{
	public:
		UITablePage(void);

		virtual ~UITablePage(void);

		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);
		
		// ����
		virtual BOOL		Draw(CDC* pDC);

		// �̳к���
	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);
		// ��ʾʱ��Ӧ����
		virtual void		VisibleTrigger();
		// ���ɼ�ʱ��������
		virtual void		InvisibleTrigger();	
		// ���ܺ���
	public:
		// ��Ӧ��һҳ
		void				OnClickLastPage();
		// ��Ӧ��һҳ
		void				OnClickNextPage();
		// ����Item�Ƿ���ʾ
		void				VisibleAllTableItem(bool bVisible);				
		// ö��GameItem
		bool				EnumTableItem();
		// ��ʾ��ҳ
		void				ShowFirstTablePage();
		// ���ټ���
		bool				OnFastJoin();
		// ���÷�����Ϣ
		void				SetRoomInfo();
		// ��ȡ������Դ
		void				LoadTableRes();
		// ��ȡ������ͼƬ
		void				LoadNoCheatImage();	
		// �������ӵĴ�С��������
		bool				CreateTable();
	public:
		// ������ͼƬ
		CPngImage			m_NoCheatImage;
		// �������� 
		std::vector<UITableItem*>		m_TableItemVector;
		// ����
		CFont				m_DrawFont;
		// ������Դ
		CTableResource		m_TableResource;					
		// ö������
		int					m_EnumIndex;
		// ���ذ�ť
		UIPngButton*		m_pBtBack;
		// ����
		CPngImage			m_TilteImage;
		// 
		CListServer*		m_pListServer;
		//
		WORD				m_wTableCount;
		//
		WORD				m_wChairCount;
		// X���ܴ�������������
		INT					m_nXTableCount;
		// Y���ܴ������ӵ�����
		INT					m_nYTableCount;
	};
}