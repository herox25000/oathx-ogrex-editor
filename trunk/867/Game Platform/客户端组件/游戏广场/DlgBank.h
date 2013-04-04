#pragma once


//////////////////////////////////////////////////////////////////////////
//���� TAB �ؼ�
class CTabCtrlBank : public CTabCtrl
{
public:
	//���캯��
	CTabCtrlBank();
	//��������
	virtual ~CTabCtrlBank();

	//��Ϣ����
protected:
	//�ػ�����	
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};

class CDlgBank : public CSkinDialogEx,ITCPSocketSink 
{
public:
	CDlgBank();
	virtual ~CDlgBank();

	//��ʼ������
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
		OPT_SAVE=0,	// ����
		OPT_GET,	// ȡ��
		OPT_PTN,	// ����
	};	
	// ��ȡ��������
	WORD					GetOptType() const;
	void					SetOptType(WORD wType);
protected:
	CTCPSocketHelper		m_BankSocketHelper;					//��������
	ITCPSocket*				m_BankSocket;						//��������
	CTabCtrlBank			m_TabBank;
	CSkinButton				m_btOK;								//ȷ����ť
	CSkinButton				m_btAll;							//ȫ����ť
	WORD					m_wOpt;
	CString					m_strGameGold;						//Я�����
	CString					m_strBankGold;						//���н��
	tagUserData				*m_pMeUserData;						//�û���Ϣ
	//�����ӿ�
public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�ӿں���
public:
	//�����¼�
	virtual bool __cdecl OnEventTCPSocketLink(WORD wSocketID, INT nErrorCode);
	//�ر��¼�
	virtual bool __cdecl OnEventTCPSocketShut(WORD wSocketID, BYTE cbShutReason);
	//��ȡ�¼�
	virtual bool __cdecl OnEventTCPSocketRead(WORD wSocketID, CMD_Command Command, VOID * pData, WORD wDataSize);

	//��Ϣ����
public:
	//����socketָ��
	bool SetClientSocket(ITCPSocket* Socket);
	//socket ����
	bool __cdecl ConnectToServer();
	//���͵�½����
	void SendLogonPacket();
	//��¼��Ϣ
	bool OnSocketMainLogon(CMD_Command Command, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool OnSocketMainUser(CMD_Command Command, void * pData, WORD wDataSize);
	//�����Ϣ
	bool OnSocketToolBox(CMD_Command Command, void * pData, WORD wDataSize);

	//��Ϣ����������
private:
	//�û�����
	bool OnSocketSubUserCome(CMD_Command Command, void * pData, WORD wDataSize);
	//�û�����
	bool OnSocketSubScore(CMD_Command Command, void * pData, WORD wDataSize);
	//ϵͳ��Ϣ
	bool OnSystemMessage( CMD_Command Command,void * pData, WORD wDataSize);
	//��ѯ�û���
	bool OnQueryUserName(void * pData, WORD wDataSize);
	//ת����ɴ���
	bool OnTransferMoney(void * pData, WORD wDataSize);
	//���в�����ɴ���
	bool OnBankTask(void * pData, WORD wDataSize);
	//���ܺ���
public:
	//�����û��ķ���
	void UpdataUserScore(__int64 Score,__int64 BankScore);
	//��ʾ��Ϣ
	int ShowMessageBox(LPCTSTR pszMessage);
	//��64λ������ʾΪ�����Ž��
	CString GetString(__int64 nNumber);
	//�õ�һ���ռ��64λֵ
	__int64 GetDlgItemInt64(UINT uID);
	//��64Ϊ������ʾ��һ���ؼ�
	void SetDlgItemInt64(UINT uID, __int64 value);
	//��Ǯȷ��
	void SaveGoldOk();
	//ȡǮȷ��
	void GetGoldOk();
	//ת��ȷ��
	void PtnGoldOK();
	//�޸ĵ�¼����ȷ��
	void ModifyLoginPWOK();
	//�޸���������OK
	void ModifyBankPWOK();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//������Ϣ
	afx_msg void OnClose();
	afx_msg void OnCancel();
	//���͸ı�
	afx_msg void OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	afx_msg void OnEnUserIDChange();
	DECLARE_MESSAGE_MAP()
};
