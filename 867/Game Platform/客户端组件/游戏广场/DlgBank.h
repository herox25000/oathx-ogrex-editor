#pragma once

class CDlgBank : public CSkinPngDialog,ITCPSocketSink 
{
public:
	CDlgBank();
	virtual ~CDlgBank();

	//初始化函数
	virtual BOOL OnInitDialog();

	enum BANKDLG
	{
		BANK_DLG_SAVE=0,
		BANK_DLG_GET,
		BANK_DLG_PTN,
		BANK_DLG_MODIFYBANKPW,
		BANK_DLG_MODIFYLOGINPW,
	};

	enum OPT
	{
		OPT_SAVE=0,	// 存入
		OPT_GET,	// 取出
		OPT_PTN,	// 赠送
	};	
	// 获取操作类似
	WORD					GetOptType() const;
	void					SetOptType(WORD wType);
protected:
	CTCPSocketHelper		m_BankSocketHelper;					//网络连接
	ITCPSocket*				m_BankSocket;						//网络连接
	CSkinTabCtrl			m_TabBank;
	CSkinButton				m_btOK;								//确定按钮
	CSkinButton				m_btAll;							//全部按钮
	WORD					m_wOpt;
	CString					m_strGameGold;						//携带金币
	CString					m_strBankGold;						//银行金币
	tagUserData				*m_pMeUserData;						//用户信息
	//窗口函数
protected:
	//绘画消息
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);
	//基础接口
public:
	//释放对象
	virtual void __cdecl Release() { delete this; }
	//接口查询
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//接口函数
public:
	//连接事件
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//关闭事件
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//读取事件
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);

	//消息函数
public:
	//设置socket指针
	bool SetClientSocket(ITCPSocket* Socket);
	//socket 连接
	bool __cdecl ConnectToServer();
	//发送登陆函数
	void SendLogonPacket();
	//登录消息
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//用户消息
	bool OnSocketMainUser(CMD_Command Command, void * pData, WORD wDataSize);
	//框架消息
	bool OnSocketToolBox(CMD_Command Command, void * pData, WORD wDataSize);

	//消息处理辅助函数
private:
	//用户进入
	bool OnSocketSubUserCome(CMD_Command Command, void * pData, WORD wDataSize);
	//用户分数
	bool OnSocketSubScore(CMD_Command Command, void * pData, WORD wDataSize);
	//系统消息
	bool OnSystemMessage( CMD_Command Command,void * pData, WORD wDataSize);
	//查询用户名
	bool OnQueryUserName(void * pData, WORD wDataSize);
	//转账完成处理
	bool OnTransferMoney(void * pData, WORD wDataSize);
	//银行操作完成处理
	bool OnBankTask(void * pData, WORD wDataSize);
	//功能函数
public:
	//更新用户的分数
	void UpdataUserScore(__int64 Score,__int64 BankScore);
	//显示消息
	int ShowMessageBox(LPCTSTR pszMessage);
	//将64位数字显示为带逗号金币
	CString GetString(__int64 nNumber);
	//得到一个空间的64位值
	__int64 GetDlgItemInt64(UINT uID);
	//将64为数字显示于一个控件
	void SetDlgItemInt64(UINT uID, __int64 value);
	//存钱确定
	void SaveGoldOk();
	//取钱确定
	void GetGoldOk();
	//转账确定
	void PtnGoldOK();
	//修改登录密码确定
	void ModifyLoginPWOK();
	//修改银行密码OK
	void ModifyBankPWOK();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//销毁消息
	afx_msg void OnClose();
	afx_msg void OnCancel();
	//类型改变
	afx_msg void OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	afx_msg void OnEnUserIDChange();
	DECLARE_MESSAGE_MAP()
};
