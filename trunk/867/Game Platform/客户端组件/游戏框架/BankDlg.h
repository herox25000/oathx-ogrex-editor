#pragma once

class CFrameDlgBank : public CSkinPngDialog
{
public:
	CFrameDlgBank();
	virtual ~CFrameDlgBank();
	//初始化函数
	virtual BOOL OnInitDialog();

protected:
	IClientKernel*			m_pIClientKernel;				//游戏内核
	CSkinButton				m_btOK;								//确定按钮
	CSkinButton				m_btAll;							//全部
	CString					m_strGameGold;						//携带金币
	CString					m_strBankGold;						//银行金币

	BYTE					m_BankType;		//1 存钱  2取钱
	//功能函数
public:
	void		SetClientKernel(IClientKernel *pClientKernel){m_pIClientKernel = pClientKernel;}
	void		UpdateView();
	void		SetBankType(BYTE Type){m_BankType = Type;}
	//显示消息
	int			ShowMessageBox(LPCTSTR pszMessage);
	//将64位数字显示为带逗号金币
	CString		GetString(__int64 nNumber);
	//得到一个空间的64位值
	__int64 GetDlgItemInt64(UINT uID);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//销毁消息
	afx_msg void OnClose();
	afx_msg void OnCancel();
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	DECLARE_MESSAGE_MAP()
};
