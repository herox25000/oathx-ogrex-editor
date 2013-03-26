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

class DlgBank : public CSkinDialogEx
{
public:
	DlgBank();
	virtual ~DlgBank();

	//��ʼ������
	virtual BOOL OnInitDialog();

	enum{
		OPT_SAVE,	// ����
		OPT_GET,	// ȡ��
		OPT_PTN,	// ����
	};
	
	// ��ȡ��������
	WORD					GetOptType() const;
	void					SetOptType(WORD wType);
protected:
	CTabCtrlBank			m_TabBank;
	CSkinButton				m_btOK;							//ȷ����ť
	CSkinButton				m_btAll;						//ȫ����ť
	WORD					m_wOpt;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	//���͸ı�
	afx_msg void OnTcnSelchange(NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnButtonOK();
	afx_msg void OnButtonAll();
	afx_msg void OnEnUserIDChange();
	DECLARE_MESSAGE_MAP()
};
