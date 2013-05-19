#pragma once

#define  UPDATE_TIMER  1

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
	__int64					m_lGameGold;						//Я�����
	__int64					m_lBankGold;						//���н��

	BYTE					m_BankType;		//1 ��Ǯ  2ȡǮ
	bool					m_bInitInfo;
	//���ܺ���
public:
	//ת���ַ�
	VOID SwitchScoreFormat(__int64 lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize);
	//���ں���
protected:
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);
	//�滭����
	VOID DrawNumberString(CDC * pDC, __int64 lScore, INT nXPos, INT nYPos);

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
	//ʱ����Ϣ
	VOID OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnCancel();
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	DECLARE_MESSAGE_MAP()
};
