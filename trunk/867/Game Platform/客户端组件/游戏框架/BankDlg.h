#pragma once

class CFrameDlgBank : public CSkinPngDialog
{
public:
	CFrameDlgBank();
	virtual ~CFrameDlgBank();
	//��ʼ������
	virtual BOOL OnInitDialog();

protected:
	IClientKernel*			m_pIClientKernel;				//��Ϸ�ں�
	CSkinButton				m_btOK;								//ȷ����ť
	CSkinButton				m_btAll;							//ȫ��
	CString					m_strGameGold;						//Я�����
	CString					m_strBankGold;						//���н��

	BYTE					m_BankType;		//1 ��Ǯ  2ȡǮ
	//���ܺ���
public:
	void		SetClientKernel(IClientKernel *pClientKernel){m_pIClientKernel = pClientKernel;}
	void		UpdateView();
	void		SetBankType(BYTE Type){m_BankType = Type;}
	//��ʾ��Ϣ
	int			ShowMessageBox(LPCTSTR pszMessage);
	//��64λ������ʾΪ�����Ž��
	CString		GetString(__int64 nNumber);
	//�õ�һ���ռ��64λֵ
	__int64 GetDlgItemInt64(UINT uID);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//������Ϣ
	afx_msg void OnClose();
	afx_msg void OnCancel();
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	DECLARE_MESSAGE_MAP()
};
