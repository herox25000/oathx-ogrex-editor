#pragma once

//////////////////////////////////////////////////////////////////////////
// ��Ϸ�б���
//////////////////////////////////////////////////////////////////////////
class CGameItemWnd : public CWnd
{
	DECLARE_DYNAMIC(CGameItemWnd)
public:
	// ���캯��
	CGameItemWnd();
	// ��������
	virtual ~CGameItemWnd();

	// ��������
	virtual BOOL	Create(UINT nID, INT nDestX, INT nDestY, 
		CWnd* pParent, HINSTANCE hInstance, LPCTSTR lpszBackResourceName, LPCTSTR lpszBillResouceName);

	// ��ɫ����
	virtual	BOOL	EnableWindow(BOOL bEnable /* = TRUE */);
public:
	// ���ñ���
	virtual void	SetBackImage(HINSTANCE hInstance, LPCTSTR lpszBackResouceName);
	// ���ù��
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

// ��Ϸ���б�
typedef CArray<CGameItemWnd*>	GameItemList;


