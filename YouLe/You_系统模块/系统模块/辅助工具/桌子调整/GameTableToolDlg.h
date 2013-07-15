// GameTableToolDlg.h : 头文件
//

#pragma once

#include "stdafx.h"
#include <atlimage.h>

#define RESOURCE_VER					1									//资源版本
#define MAX_CHAIR_NORMAL                8                                   //最多的桌子数为8

//显示格式
#define	NT_RIGHT						0x01								//右对齐
#define	NT_CENTER						0x02								//中对齐
#define	NT_LEFT							0x04								//左对齐
#define	NT_TOP							0x10								//上对齐
#define	NT_VCENTER						0x20								//中对齐
#define	NT_BOTTOM						0x40								//下对齐

//资源配置结构
struct tagTableResourceInfo
{
	COLORREF							crName;								//名字颜色
	COLORREF							crNote;								//备注颜色
	COLORREF							crTableID;							//号码颜色

	POINT								ptLock;								//锁位置
	RECT								rcNote;								//备注位置
	RECT								rcTableID;							//桌号位置

	RECT								rcName[MAX_CHAIR_NORMAL];			//名字位置
	RECT								rcChair[MAX_CHAIR_NORMAL];			//椅子位置
	POINT								ptReady[MAX_CHAIR_NORMAL];			//准备位置
	INT									nDrawStyle[MAX_CHAIR_NORMAL];		//输出格式
};

//配置文件结构
struct tagTableConfigFile
{
	WORD								wFileSize;							//文件大小
	WORD								wStructVer;							//结构版本
	tagTableResourceInfo			    TableResourceInfo;					//配置参数
};


// CGameTableToolDlg 对话框
class CGameTableToolDlg : public CDialog
{
	//位置变量
public:
	CPoint								m_ptLock;							//锁位置
	CRect								m_rcNote;							//备注位置
	CRect								m_rcTableID;						//桌号位置
	CPoint								m_ptReady[8];				        //准备位置
	CRect								m_rcName[8];				        //名字位置
	CRect								m_rcChair[8];				        //椅子位置

	//颜色参数
public:
	COLORREF							m_crName;							//名字颜色
	COLORREF							m_crNote;							//备注颜色
	COLORREF							m_crTableID;						//号码颜色
	int									m_nDrawStyle[8];			        //输出格式

	bool                                m_bLoadParameter;                   //是否成功加载了参数
	//调整过程中的控制变量
public:
	int                 m_CurrentChairID;                                  //当前调整的椅子号
	int                 m_ChairCount;                                      //当前总共的椅子数

	CDC                 m_MemDC;                                           //内存缓冲区
	CBitmap             m_MemBitmap;


	//位图资源
public:
	CSkinImage							m_ImageLock;						//桌锁位图
	CSkinImage							m_ImageReady;						//准备位图
	CSkinImage							m_ImageTable;						//桌子位图
	CSkinImage							m_ImagePeople[8];					//用户位图
	

public:
	void CreateMyBitMap(CBitmap *pBitmap);
	void UpdateShow();
	void DrawTableImage(CDC *pDC);
	void DrawParameter(CDC *pDC);
// 构造
public:
	CGameTableToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CBitmap   m_pBitmap;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	//底排的按钮
	afx_msg void OnLoadImage();
	afx_msg void OnLoadParameter();
	afx_msg void OnSaveParameter();
	afx_msg void OnTableNocolor();
	afx_msg void OnAccountColor();
	virtual void OnOK();

	//调整方位的按钮
	afx_msg void OnUp();
	afx_msg void OnLeft();
	afx_msg void OnRight();
	afx_msg void OnDown();
//	afx_msg void OnFourPixel();

	//调整方框的按钮
	afx_msg void OnAddWidth();
	afx_msg void OnReduceWidth();
	afx_msg void OnAddHeight();
	afx_msg void OnReduceHeight();

	//三个下拉列表框的内容变化处理
//	afx_msg void OnEditchangeCurrentSeat();
//	afx_msg void OnEditchangeUserName();

    afx_msg void OnCbnSelendokSeatCount();

	//文本垂直方向上的对齐处理
	afx_msg void OnValignmetUp();
	afx_msg void OnValignmetDown();
	afx_msg void OnValignmetCenter();

	//文本水平方向上的对齐处理
	afx_msg void OnHalignmetRight();
	afx_msg void OnHalignmetCenter();
	afx_msg void OnHalignmetLeft();

	//复选框项的处理
	afx_msg void OnHaveAccount();
	afx_msg void OnHaveHead();
	afx_msg void OnHaveLock();

	//复选框项的处理
	afx_msg void OnFrameAccount();
	afx_msg void OnFrameHead();
	afx_msg void OnFrameTableno();

	//当前处理项的单选按钮的处理
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
