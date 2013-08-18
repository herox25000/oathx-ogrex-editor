#pragma once

#include "GdipButton.h"
#include "DlgLogon.h"

class KeyManage  
{
public:
	KeyManage();
	virtual ~KeyManage();

public:
	BOOL GetKeyAllState(string &str);
	int GetKeyState(UINT vKey);
	void PreTranslateKey();
	CString GetKeyName(UINT vk, BOOL fExtended);

protected:
	BYTE m_key[256];
};

// CFrameSet �Ի���
class CFrameSet : public CDialog
{
	DECLARE_DYNAMIC(CFrameSet)

public:
	CFrameSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFrameSet();

// �Ի�������
	enum { IDD = IDD_FRAMESET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	//�����
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

protected:
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	//ͼƬ��Դ
protected:
	CPngImage			m_ImageBack;			//����ͼ

	//��ť�ؼ�
protected:
	CGdipButton					m_btClose;
	CGdipButton					m_btConfirn;
	CGdipButton					m_btCancel;

	CControlCheckButton			m_btNotUse;
	CControlCheckButton			m_btUserQuick;

protected:
	std::string					m_strCtrl;
	std::string					m_strKey;
	KeyManage					m_keys;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
