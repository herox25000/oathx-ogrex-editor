// GameTableToolDlg.h : ͷ�ļ�
//

#pragma once

#include "stdafx.h"
#include <atlimage.h>

#define RESOURCE_VER					1									//��Դ�汾
#define MAX_CHAIR_NORMAL                8                                   //����������Ϊ8

//��ʾ��ʽ
#define	NT_RIGHT						0x01								//�Ҷ���
#define	NT_CENTER						0x02								//�ж���
#define	NT_LEFT							0x04								//�����
#define	NT_TOP							0x10								//�϶���
#define	NT_VCENTER						0x20								//�ж���
#define	NT_BOTTOM						0x40								//�¶���

//��Դ���ýṹ
struct tagTableResourceInfo
{
	COLORREF							crName;								//������ɫ
	COLORREF							crNote;								//��ע��ɫ
	COLORREF							crTableID;							//������ɫ

	POINT								ptLock;								//��λ��
	RECT								rcNote;								//��עλ��
	RECT								rcTableID;							//����λ��

	RECT								rcName[MAX_CHAIR_NORMAL];			//����λ��
	RECT								rcChair[MAX_CHAIR_NORMAL];			//����λ��
	POINT								ptReady[MAX_CHAIR_NORMAL];			//׼��λ��
	INT									nDrawStyle[MAX_CHAIR_NORMAL];		//�����ʽ
};

//�����ļ��ṹ
struct tagTableConfigFile
{
	WORD								wFileSize;							//�ļ���С
	WORD								wStructVer;							//�ṹ�汾
	tagTableResourceInfo			    TableResourceInfo;					//���ò���
};


// CGameTableToolDlg �Ի���
class CGameTableToolDlg : public CDialog
{
	//λ�ñ���
public:
	CPoint								m_ptLock;							//��λ��
	CRect								m_rcNote;							//��עλ��
	CRect								m_rcTableID;						//����λ��
	CPoint								m_ptReady[8];				        //׼��λ��
	CRect								m_rcName[8];				        //����λ��
	CRect								m_rcChair[8];				        //����λ��

	//��ɫ����
public:
	COLORREF							m_crName;							//������ɫ
	COLORREF							m_crNote;							//��ע��ɫ
	COLORREF							m_crTableID;						//������ɫ
	int									m_nDrawStyle[8];			        //�����ʽ

	bool                                m_bLoadParameter;                   //�Ƿ�ɹ������˲���
	//���������еĿ��Ʊ���
public:
	int                 m_CurrentChairID;                                  //��ǰ���������Ӻ�
	int                 m_ChairCount;                                      //��ǰ�ܹ���������

	CDC                 m_MemDC;                                           //�ڴ滺����
	CBitmap             m_MemBitmap;


	//λͼ��Դ
public:
	CSkinImage							m_ImageLock;						//����λͼ
	CSkinImage							m_ImageReady;						//׼��λͼ
	CSkinImage							m_ImageTable;						//����λͼ
	CSkinImage							m_ImagePeople[8];					//�û�λͼ
	

public:
	void CreateMyBitMap(CBitmap *pBitmap);
	void UpdateShow();
	void DrawTableImage(CDC *pDC);
	void DrawParameter(CDC *pDC);
// ����
public:
	CGameTableToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GAMETABLETOOL_DIALOG };
	CStatic	m_ShowWnd;
	CButton	m_AccountColor;
	CButton	m_TableNoColor;
	CButton	m_SaveParameter;
	CButton	m_LoadParameter;
	CButton	m_ReduceWidth;
	CButton	m_ReduceHeight;
	CButton	m_AddWidth;
	CButton	m_AddHeight;
	CComboBox	m_CurrentSeat;
	CComboBox	m_UserName;
	CComboBox	m_SeatCount;
	BOOL	m_bFourPixel;
	BOOL	m_bFrameAccount;
	BOOL	m_bFrameHead;
	BOOL	m_bFrameTableNo;
	BOOL	m_bHaveAccount;
	BOOL	m_bHaveHead;
	BOOL	m_bHaveLock;
	int		m_CurrentItem;
	int		m_CurrentHAlignmet;
	int		m_CurrentVAlignmet;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CBitmap   m_pBitmap;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//���ŵİ�ť
	afx_msg void OnLoadImage();
	afx_msg void OnLoadParameter();
	afx_msg void OnSaveParameter();
	afx_msg void OnTableNocolor();
	afx_msg void OnAccountColor();
	virtual void OnOK();

	//������λ�İ�ť
	afx_msg void OnUp();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnDown();
//	afx_msg void OnFourPixel();

	//��������İ�ť
	afx_msg void OnAddWidth();
	afx_msg void OnReduceWidth();
	afx_msg void OnAddHeight();
	afx_msg void OnReduceHeight();

	//���������б������ݱ仯����
//	afx_msg void OnEditchangeCurrentSeat();
//	afx_msg void OnEditchangeUserName();

    afx_msg void OnCbnSelendokSeatCount();

	//�ı���ֱ�����ϵĶ��봦��
	afx_msg void OnValignmetUp();
	afx_msg void OnValignmetDown();
	afx_msg void OnValignmetCenter();

	//�ı�ˮƽ�����ϵĶ��봦��
	afx_msg void OnHalignmetRight();
	afx_msg void OnHalignmetCenter();
	afx_msg void OnHalignmetLeft();

	//��ѡ����Ĵ���
	afx_msg void OnHaveAccount();
	afx_msg void OnHaveHead();
	afx_msg void OnHaveLock();

	//��ѡ����Ĵ���
	afx_msg void OnFrameAccount();
	afx_msg void OnFrameHead();
	afx_msg void OnFrameTableno();

	//��ǰ������ĵ�ѡ��ť�Ĵ���
	afx_msg void OnLocalLock();
	afx_msg void OnLocalHand();
	afx_msg void OnLocalTableno();
	afx_msg void OnLocalAccount();
	afx_msg void OnLocalHead();

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnCbnSelendokUserName();
	afx_msg void OnCbnSelendokCurrentSeat();
	afx_msg void OnBnClickedFourPixel();
};
