#ifndef PLAZA_VIEW_ITEM_HEAD_FILE
#define PLAZA_VIEW_ITEM_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "ServerListData.h"

//////////////////////////////////////////////////////////////////////////////////

//��������
#define VIEW_MODE_NONE				0									//��Чģʽ
#define VIEW_MODE_KIND				1									//����ģʽ
#define VIEW_MODE_SERVER			2									//����ģʽ

//��ť��ʶ
#define BT_VIEW_RULE				1									//�鿴����
#define BT_ENTER_KIND				2									//��������
#define BT_ENTER_SERVER				3									//���뷿��

//////////////////////////////////////////////////////////////////////////////////

//���Ͷ���
struct tagGameKindInfo
{
	WORD							wSortID;							//�����ʶ
	CPngImage						ImageKindItem;						//����ͼƬ
	CGameKindItem *					pGameKindItem;						//���Ͷ���
};

//���䶨��
struct tagGameServerInfo
{
	WORD							wSortID;							//�����ʶ
	WORD							wServerID;							//�����ʶ
	CGameServerItem *				pGameServerItem;					//�������
};

//���鶨��
typedef CWHArray<tagGameKindInfo *>	CGameKindInfoArray;					//��������
typedef CWHArray<tagGameServerInfo *> CGameServerInfoArray;				//��������

//////////////////////////////////////////////////////////////////////////////////

//��Ϸ�㳡
class CPlazaViewItem : public CDialog, public IUnknownEx
{
	//״̬����
protected:
	bool							m_bHovering;						//������־
	bool							m_bCreateFlag;						//������־
	BYTE							m_cbShowItemMode;					//��ʾģʽ

	//�ƶ�λ��
protected:
	BYTE							m_cbButtonDown;						//��ť����
	BYTE							m_cbButtonHover;					//��ť����
	WORD							m_wViewItemDown;					//�������
	WORD							m_wViewItemHover;					//��������

	//λ�ñ���
protected:
	WORD							m_wKindXCount;						//��������
	WORD							m_wKindYCount;						//��������
	WORD							m_wKindExcursion;					//����ƫ��
	WORD							m_wKindPageCount;					//����ҳ��
	WORD							m_wKindPageCurrent;					//��ǰҳ��
	WORD                            m_wKindTypeCurrentID;               //��ǰ����

	//λ�ñ���
protected:
	WORD							m_wServerXCount;					//��������
	WORD							m_wServerYCount;					//��������
	WORD							m_wServerExcursion;					//����ƫ��
	WORD							m_wServerPageCount;					//����ҳ��
	WORD							m_wServerPageCurrent;				//��ǰҳ��

	//��Դ����
protected:
	CPngImage						m_ImageTitle;						//����ͼƬ
	CPngImage						m_ImageServer;						//����ͼƬ

	//��ť����
protected:
	CSkinButton						m_btLastKind;						//��ҳ��ť
	CSkinButton						m_btNextKind;						//��ҳ��ť
	CSkinButton                     m_btReturnHall;                     //���ذ�ť
	CSkinButton						m_btLastServer;						//��ҳ��ť
	CSkinButton						m_btNextServer;						//��ҳ��ť

	//��������
protected:
	CGameKindInfoArray				m_GameKindInfoActive;				//��������
	CGameKindInfoArray				m_GameKindInfoBuffer;				//��������
	CGameServerInfoArray			m_GameServerInfoActive;				//��������
	CGameServerInfoArray			m_GameServerInfoBuffer;				//��������

	//�ؼ�ָ��
protected:
	static CPlazaViewItem *			m_pPlazaViewItem;					//�㳡ָ��

	//��������
public:
	//���캯��
	CPlazaViewItem();
	//��������
	virtual ~CPlazaViewItem();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual VOID Release() { delete this; }
	//�ӿڲ�ѯ
	virtual VOID * QueryInterface(REFGUID Guid, DWORD dwQueryVer);

	//���غ���
protected:
	//��������
	virtual BOOL OnInitDialog();
	//ȷ������
	virtual VOID OnOK() { return; };
	//ȡ������
	virtual VOID OnCancel() { return; };

	//���ܺ���
public:
	//��ʾ����
	VOID ShowKindItemView(WORD wTypeID,BOOL bResetPageIndex=TRUE);
	//��ʾ����
	VOID ShowServerItemView(WORD wKindID,BOOL bResetPageIndex=FALSE);
	//�������
	VOID InValidateWndView(BYTE cbViewType);

	//���ܺ���
public:
	//��ȡʵ��
	static CPlazaViewItem * GetInstance() { return m_pPlazaViewItem; }	

	//�滭����
private:
	//�滭����
	VOID DrawKindItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameKindInfo * pGameKindInfo);
	//�滭����
	VOID DrawServerItem(CDC * pDC, WORD wViewIndex, INT nXPos, INT nYPos, tagGameServerInfo * pGameServerInfo);

	//�ڲ�����
protected:
	//�����ؼ�
	VOID RectifyControl(INT nWidth, INT nHeight);
	//��ԴĿ¼
	VOID GetGameDirectory(TCHAR szDirectory[], WORD wBufferCount, tagGameKind & GameKind);

	//λ�ò���
protected:
	//��������
	WORD GetHoverIndex(CPoint MousePoint);
	//��ť����
	BYTE GetHoverButton(WORD wViewIndex, CPoint MousePoint);

	//��ť��Ϣ
protected:
	//�鿴����
	VOID OnButtonViewRule(WORD wKindID);
	//��������
	VOID OnButtonEnterKind(WORD wKindID);
	//���뷿��
	VOID OnButtonEnterServer(WORD wServerID);

	//��ť��Ϣ
protected:
	//��ҳ��ť
	VOID OnBnClickedLastKind();
	//��ҳ��ť
	VOID OnBnClickedNextKind();
	//���ذ�ť
	VOID OnBnClickedReturnHall();
	//��ҳ��ť
	VOID OnBnClickedLastServer();
	//��ҳ��ť
	VOID OnBnClickedNextServer();	

	//��Ϣ����
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//����ƶ�
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//����뿪
	LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif