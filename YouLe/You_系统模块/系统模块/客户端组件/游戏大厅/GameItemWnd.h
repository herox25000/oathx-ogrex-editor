#pragma once

//////////////////////////////////////////////////////////////////////////
// 游戏列表项
//////////////////////////////////////////////////////////////////////////
class CGameItemWnd : public CWnd
{
	DECLARE_DYNAMIC(CGameItemWnd)
public:
	// 构造函数
	CGameItemWnd();
	// 析构函数
	virtual ~CGameItemWnd();

	// 创建窗口
	virtual BOOL	Create(UINT nID, INT nDestX, INT nDestY, 
		CWnd* pParent, HINSTANCE hInstance, LPCTSTR lpszBackResourceName, LPCTSTR lpszBillResouceName);

	// 灰色窗口
	virtual	BOOL	EnableWindow(BOOL bEnable /* = TRUE */);
public:
	// 设置背景
	virtual void	SetBackImage(HINSTANCE hInstance, LPCTSTR lpszBackResouceName);
	// 设置广告
	virtual void	SetBillImage(HINSTANCE hInstance, LPCTSTR lpszBillResouceName);
protected:
	CPngImage		m_PngBack;
	CPngImage		m_PngBill;

	CGdipButton		m_Regular;
	CGdipButton		m_JoinBtn;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL	OnEraseBkgnd(CDC* pDC);
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
};

// 游戏项列表
typedef CArray<CGameItemWnd*>	GameItemList;


