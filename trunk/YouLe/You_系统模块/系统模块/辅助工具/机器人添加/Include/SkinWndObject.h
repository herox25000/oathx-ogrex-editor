#ifndef SKIN_WND_OBJECT_HEAD_FILE
#define SKIN_WND_OBJECT_HEAD_FILE

#pragma once

#include "SkinImage.h"
#include "SkinControls.h"
#include "SkinAttribute.h"

//////////////////////////////////////////////////////////////////////////

//��������
#define SKIN_WND_CRBACKFRAME		TEXT("��������ɫ")			// COLORREF ���� ����д��
#define SKIN_WND_CRBACKGROUND		TEXT("���屳����ɫ")			// COLORREF ���� ����д��
#define SKIN_WND_CRINSIDEBORDER		TEXT("�����ڿ���ɫ")			// COLORREF ���� ����д��
#define SKIN_WND_CRCAPTIONTXCOLOR	TEXT("���������ɫ")			// COLORREF ���� ����д��
#define SKIN_WND_CRCONTROLTXCOLOR	TEXT("����ؼ�������ɫ")		// COLORREF ���� ����д��
#define SKIN_WND_STRBUTTONMINPATH	TEXT("������С��λͼ")			// CString  ���� ����д��
#define SKIN_WND_STRBUTTONMAXPATH	TEXT("�������λͼ")			// CString  ���� ����д��
#define SKIN_WND_STRBUTTONRESPATH	TEXT("���廹ԭλͼ")			// CString  ���� ����д��
#define SKIN_WND_STRBUTTONCLOSEPATH	TEXT("����ر�λͼ")			// CString  ���� ����д��
#define SKIN_WND_STRTITLELEFTPATH	TEXT("���������")				// CString  ���� ����д��
#define SKIN_WND_STRTITLEMIDPATH	TEXT("�����б���")				// CString  ���� ����д��
#define SKIN_WND_STRTITLERIGHTPATH	TEXT("�����ұ���")				// CString  ���� ����д��

//////////////////////////////////////////////////////////////////////////

//����������
class CSkinWndAttribute : public CSkinAttribute
{
	friend class CSkinWndObject;

	//���ò���
public:
	COLORREF						m_crBackFrame;						//��ܱ���
	COLORREF						m_crBackGround;						//������ɫ
	COLORREF						m_crInsideBorder;					//�ڿ���ɫ
	COLORREF						m_crCaptionTXColor;					//������ɫ
	COLORREF						m_crControlTXColor;					//������ɫ
	CString							m_strButtonMinPath;					//λͼ·��
	CString							m_strButtonMaxPath;					//λͼ·��
	CString							m_strButtonResPath;					//λͼ·��
	CString							m_strButtonClosePath;				//λͼ·��
	CString							m_strTitleLeftPath;					//����·��
	CString							m_strTitleMidPath;					//����·��
	CString							m_strTitleRightPath;				//����·��

	//���Ա���
public:
	int								m_nButtonWidth;						//��ť���
	int								m_nButtonHeigth;					//��ť�߶�
	int								m_nCaptionHeigth;					//����߶�

	//GDI ����
public:
	CBrush							m_brBackFrame;						//����ˢ
	CBrush							m_brBackGround;						//����ˢ
	CSkinImage						m_ButtonMin;						//��С����ť
	CSkinImage						m_ButtonMax;						//��󻯰�ť
	CSkinImage						m_ButtonRes;						//��ԭ��ť
	CSkinImage						m_ButtonClose;						//�رհ�ť	
	CSkinImage						m_TitleLeft;						//����ͼƬ
	CSkinImage						m_TitleMid;							//����ͼƬ
	CSkinImage						m_TitleRight;						//����ͼƬ

	//��������
protected:
	//���캯��
	CSkinWndAttribute();
	//��������
	virtual ~CSkinWndAttribute();

	//�ӿں���
public:
	//��������
	virtual bool __cdecl LoadSkinOption();
	//��������
	virtual bool __cdecl SaveSkinOption();
};

//////////////////////////////////////////////////////////////////////////

//���������
class SKIN_CONTROL_CLASS CSkinWndObject
{
	//״̬����
protected:
	bool							m_bActive;							//�Ƿ񼤻�
	bool							m_bMaxSize;							//����־
	int								m_nXExcursionPos;					//X ƫ��
	int								m_nYExcursionPos;					//Y ƫ��
	BYTE							m_cbNowHotButton;					//���ڽ���
	BYTE							m_cbNowDownButton;					//���°�ť
	BYTE							m_cbButtonState[3];					//��ť״̬
	CRect							m_rcButton[3];						//��ťλ��

	//�ڲ�����
private:
	CWnd							* m_pWndHook;						//�ҽӴ���
	CRect							m_crNormalSize;						//����λ��

	//��̬����
public:
	static CSkinWndAttribute		m_SkinAttribute;					//��������

	//��������
public:
	//���캯��
	CSkinWndObject(CWnd * pWndSkin);
	//��������
	virtual ~CSkinWndObject(void);

	//���ܺ���
public:
	//�滭����
	void DrawSkinView(CDC * pDC);
	//��󴰿�
	void MaxSizeWindow();
	//��ԭ����
	void RestoreWindow();
	//��ȡƫ��
	int GetXExcursionPos() { return m_nXExcursionPos; }
	//��ȡƫ��
	int GetYExcursionPos() { return m_nYExcursionPos; }
	//��ȡ���Խӿ�
	static CSkinWndAttribute * GetSkinAttribute() { return &m_SkinAttribute; };

	//�ڲ�����
protected:
	//��ʼ��
	void InitSkinObject();
	//������ť
	void AdjustTitleButton(int nCXWindow, int nCYWindow);
	//�滭����
	bool DrawCaption(CDC * pDC, int cx, int cy);

	//�¼�����
protected:
	//���øı��¼�
	void OnSettingChange();
	//����ƶ��¼�
	bool OnMouseMoveEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseDownEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseUpEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseDoubleEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseDownEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseUpEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseDoubleEvent(CPoint ClientPoint);
};

//////////////////////////////////////////////////////////////////////////

#endif