#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	/////////////////////////////////////////////////////////
	//���乹��
	////////////////////////////////////////////////////////
	class UIRoomItem : public UIWidget, public UIProcess
	{
	public:
		UIRoomItem(void);

		virtual ~UIRoomItem(void);

		// �����ؼ�
		virtual	BOOL		Create(INT nID, INT nDestX, INT nDestY, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		// ���ƿؼ�
		virtual BOOL		Draw(CDC* pDC);
	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);
	
		// ���ܺ���
	public:
		//
		bool				OnClickedEnterRoom();

	protected:
		CPngImage			m_PngBill;
		UIPngButton*		m_pJoinBtn; 

	public:
		CListServer*		m_pListServer;
	};


	/////////////////////////////////////////////////////////
	//������ͼ����
	////////////////////////////////////////////////////////
	class UIRoomPage : public UIWidget, public UIProcess
	{
	public:
		UIRoomPage(void);

		virtual ~UIRoomPage(void);

		// �����ؼ�
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);
		
		// ����
		virtual BOOL		Draw(CDC* pDC);

	public:
		// ��Ӧҳ�ؼ�
		virtual	BOOL		OnLeftDown(UIWidget* pWidget, const CPoint& cPt);

		// ���ܺ���
	public:
		// ��ʾ�����б�
		bool				ShowRoomList(CListKind* ListKind);

	public:
		// �����б�ָ��
		UIRoomItem*			m_pRoomItem[MAX_GICOL*MAX_GIROW];
		// ���ذ�ť
		UIPngButton*		m_pBtBack;
		// ����
		CPngImage			m_TilteImage;
		// �������ƣ���Ϸ���֣�
		TCHAR				szKindName[KIND_LEN];
	};


}