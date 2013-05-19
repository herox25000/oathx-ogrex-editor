#pragma once

#define  UPDATE_TIMER  1

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
	__int64					m_lGameGold;						//携带金币
	__int64					m_lBankGold;						//银行金币

	BYTE					m_BankType;		//1 存钱  2取钱
	bool					m_bInitInfo;
	//功能函数
public:
	//转换字符
	VOID SwitchScoreFormat(__int64 lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);
	//窗口函数
protected:
	//绘画消息
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);
	//绘画数字
	VOID DrawNumberString(CDC * pDC, __int64 lScore, INT nXPos, INT nYPos);

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
	//时间消息
	VOID OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnCancel();
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	DECLARE_MESSAGE_MAP()
};
