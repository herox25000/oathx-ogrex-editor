#pragma once

#ifndef SKIN_DIALOG_HEAD_FILE
#define SKIN_DIALOG_HEAD_FILE

#include "SkinControls.h"
#include "SkinWndObject.h"
#include "PngImage.h"
#include "SkinAide.h"


//////////////////////////////////////////////////////////////////////////

//�Ի�����
class SKIN_CONTROL_CLASS CSkinDialog : public CDialog, public CSkinWndObject
{
	//��������
public:
	//���캯��
	CSkinDialog(UINT nIDTemplate, CWnd * pParentWnd=NULL);
	//��������
	virtual ~CSkinDialog();

	//���غ���
public:
	//��ʼ����Ϣ
	virtual BOOL OnInitDialog();

	//��Ϣӳ��
protected:
	//������Ϣ
	afx_msg void OnActivate(UINT nState, CWnd * pWndOther, BOOL bMinimized);
	//������Ϣ
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
	//�����Ϣ
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//�����Ϣ
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//�滭��Ϣ
	afx_msg void OnPaint();
	//�ı���Ϣ
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//�滭����
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	//λ�øı�
	afx_msg void OnWindowPosChanged(WINDOWPOS * lpwndpos);
	//�ؼ���ɫ
	afx_msg HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);
	//������Ϣ
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinDialog)
};

//////////////////////////////////////////////////////////////////////////

//�Ի�����
class SKIN_CONTROL_CLASS CSkinDialogEx : public CSkinDialog
{
	//��������
public:
	//���캯��
	CSkinDialogEx(UINT nIDTemplate, CWnd * pParentWnd=NULL);
	//��������
	virtual ~CSkinDialogEx();

	//�滭����
protected:
	//�滭�߿�
	void DrawBorder(CDC * pDC);
	//�滭����
	void DrawCaption(CDC * pDC);
	//�滭����
	void DrawBackGround(CDC * pDC);

	//��Ϣ����
protected:
	//�ػ���Ϣ
	afx_msg void OnPaint();
	//λ����Ϣ
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinDialogEx)
};

//////////////////////////////////////////////////////////////////////////

//����Ի�����
class SKIN_CONTROL_CLASS CRgnDialog : public CDialog
{
	//��������
protected:
	CRgn							m_DialogRgn;						//��������
	CSkinImage						m_ImageBack;						//����λͼ

	//��������
public:
	//���캯��
	CRgnDialog(UINT uTemplate, CWnd * pParent=NULL);
	//��������
	virtual ~CRgnDialog();
	//��ʼ������
	virtual BOOL OnInitDialog();

	//���ܺ���
public:
	//����λͼ
	bool LoadRgnImage(LPCTSTR pszFileName, COLORREF crTrans);
	//����λͼ
	bool LoadRgnImage(HINSTANCE hInstance, UINT uBitmapID, COLORREF crTrans);

	//�ڲ����� 
private:
	//��������
	bool CreateControlRgn(COLORREF crTrans);

	//��Ϣ����
public:
	//�ػ�����
	afx_msg void OnPaint();
	//����Ҽ�������Ϣ
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//������Ϣ
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CRgnDialog)
};

//////////////////////////////////////////////////////////////////////////

//�ֲ㴰��
class SKIN_CONTROL_CLASS CSkinLayered : public CWnd
{
	//��������
protected:
	CWnd *							m_pWndControl;						//�ؼ�����

	//��������
public:
	//���캯��
	CSkinLayered();
	//��������
	virtual ~CSkinLayered();

	//���ܺ���
public:
	//��������
	VOID CreateLayered(CWnd * pWndControl, CRect & rcWindow);
	//��������
	VOID InitLayeredArea(CDC * pDCImage, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);
	//��������
	VOID InitLayeredArea(CPngImage & Image, BYTE cbAlpha, CRect & rcUnLayered, CPoint & PointRound, bool bUnLayeredChild);

	//��Ϣӳ��
protected:
	//�ر���Ϣ
	VOID OnClose();
	//������Ϣ
	VOID OnSetFocus(CWnd * pOldWnd);

	//��̬����
protected:
	//ö�ٺ���
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};




//������Դ�ĶԻ���

//������Դ
class SKIN_CONTROL_CLASS CSkinDialogAttribute
{
	//��ɫ����
public:
	COLORREF						m_crTitleText;						//������ɫ
	COLORREF						m_crTitleFrame;						//������ɫ
	COLORREF						m_crBackGround;						//������ɫ
	COLORREF						m_crControlText;					//������ɫ

	//��Դ����
public:
	CSize							m_SizeButton;						//��ť��С
	CBrush							m_brBackGround;						//������ˢ
	CEncirclePNG					m_PNGEncircleFrame;					//�����Դ

	//λ�ñ���
public:
	tagEncircleInfo					m_EncircleInfoView;					//��ͼ����
	tagEncircleInfo					m_EncircleInfoFrame;				//��ܻ���

	//��������
public:
	//���캯��
	CSkinDialogAttribute();
	//��������
	virtual ~CSkinDialogAttribute();

	//������
public:
	//������Դ
	bool Initialization(CSkinRenderManager * pSkinRenderManager);
};


//////////////////////////////////////////////////////////////////////////////////

//�Ի�����
class SKIN_CONTROL_CLASS CSkinPngDialog : public CDialog
{
	//��ť״̬
private:
	BYTE							m_cbNowHotIndex;					//���ڽ���
	BYTE							m_cbNowHitIndex;					//���°�ť
	BYTE							m_cbButtonState[3];					//��ť״̬

	//����״̬
private:
	bool							m_bTransition;						//����״̬
	WORD							m_wImageIndex[3];					//��������

	//���ڱ���
private:
	CRect							m_rcButton[3];						//��ťλ��
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��

	//��Դ����
public:
	static CSkinDialogAttribute		m_SkinAttribute;					//��Դ����

	//��������
public:
	//���캯��
	CSkinPngDialog(UINT nIDTemplate, CWnd * pParentWnd=NULL);
	//��������
	virtual ~CSkinPngDialog();

	//���غ���
public:
	//������Ϣ
	virtual BOOL OnInitDialog();
	//�滭��Ϣ
	virtual VOID OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight);

	//��������
private:
	//��������
	UINT ControlHitTest(CPoint Point);
	//������Դ
	VOID RectifyResource(INT nWidth, INT nHeight);
	//������ť
	VOID CaleTitleButton(INT nWidth, INT nHeight);

	//�滭����
private:
	//�滭�ؼ�
	VOID DrawControlView(CDC * pDC, INT nWdith, INT nHeight);
	//�滭����
	VOID DrawSystemTitle(CDC * pDC, INT nWdith, INT nHeight);
	//�滭��ť
	VOID DrawSystemButton(CDC * pDC, INT nWdith, INT nHeight);

	//��Ϣӳ��
protected:
	//�����Ϣ
	VOID OnMouseMove(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonUp(UINT nFlags, CPoint Point);
	//�����Ϣ
	VOID OnLButtonDown(UINT nFlags, CPoint Point);

	//��Ϣӳ��
protected:
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//ʱ����Ϣ
	VOID OnTimer(UINT_PTR nIDEvent);
	//λ����Ϣ
	VOID OnSize(UINT nType, INT cx, INT cy);
	//��ʾ��Ϣ
	VOID OnShowWindow(BOOL bShow, UINT nStatus);
	//λ�øı�
	VOID OnWindowPosChanged(WINDOWPOS * lpWndPos);
	//�ؼ���ɫ
	HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

	//�Զ���Ϣ
protected:
	//������Ϣ
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinPngDialog)
};


#endif