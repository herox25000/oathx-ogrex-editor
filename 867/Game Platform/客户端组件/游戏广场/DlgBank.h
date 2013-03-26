#pragma once


//////////////////////////////////////////////////////////////////////////
//银行 TAB 控件
class CTabCtrlBank : public CTabCtrl
{
public:
	//构造函数
	CTabCtrlBank();
	//析够函数
	virtual ~CTabCtrlBank();

	//消息函数
protected:
	//重画函数	
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

class DlgBank : public CSkinDialogEx
{
public:
	DlgBank();
	virtual ~DlgBank();

	//初始化函数
	virtual BOOL OnInitDialog();

	enum{
		OPT_SAVE,	// 存入
		OPT_GET,	// 取出
		OPT_PTN,	// 赠送
	};
	
	// 获取操作类似
	WORD					GetOptType() const;
	void					SetOptType(WORD wType);
protected:
	CTabCtrlBank			m_TabBank;
	CSkinButton				m_btOK;							//确定按钮
	CSkinButton				m_btAll;						//全部按钮
	WORD					m_wOpt;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	//类型改变
	afx_msg void OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	afx_msg void OnEnUserIDChange();
	DECLARE_MESSAGE_MAP()
};
