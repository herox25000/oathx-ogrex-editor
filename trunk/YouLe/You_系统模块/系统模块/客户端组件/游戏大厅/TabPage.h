#pragma once

//////////////////////////////////////////////////////////////////////////
// �����߼�ҳ��ؼ�
//////////////////////////////////////////////////////////////////////////
class CTabPage
{
public:
	// ���캯��
	CTabPage();
	// ��������
	virtual ~CTabPage(void);
	// ����ҳ
	virtual BOOL	Create(INT nID, const RECT& rect, CWnd* pParent);
	// ��ȡID
	virtual	INT		GetID() const;
	// ��ʾ״̬
	virtual void	ShowWindow(int nCmdShow);
protected:
	// ҳID
	INT				m_nID;
	// ҳ������
	CWnd*			m_pWnd;
	// ��������
	CRect			m_rect;
};
