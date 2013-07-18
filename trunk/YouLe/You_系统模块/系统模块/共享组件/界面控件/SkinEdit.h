#pragma once

#ifndef SKIN_EDIT_HEAD_FILE
#define SKIN_EDIT_HEAD_FILE

#include "SkinControls.h"
#include "SkinResourceManager.h"

//��������
//#define SKIN_EDIT_CRFOCUSTX			TEXT("�༭�򽹵���ɫ")				// COLORREF ���� ����д��
//#define SKIN_EDIT_CRFOCUSBK			TEXT("�༭�򽹵㱳��ɫ")			// COLORREF ���� ����д��
//#define SKIN_EDIT_CRNOFOCUSTX		TEXT("�༭��������ɫ")				// COLORREF ���� ����д��
//#define SKIN_EDIT_CRNOFOCUSBK		TEXT("�༭����������ɫ")			// COLORREF ���� ����д��
//#define SKIN_EDIT_CRDISFOCUSTX		TEXT("�༭���ֹ��ɫ")				// COLORREF ���� ����д��
//#define SKIN_EDIT_CRDISFOCUSBK		TEXT("�༭���ֹ����ɫ")			// COLORREF ���� ����д��

//////////////////////////////////////////////////////////////////////////

//�༭������
class CSkinEditAttribute : public CSkinResourceManager
{
	friend class CSkinEdit;

	//���ò���
public:
	COLORREF							m_crFocusTX;					//������ɫ
	COLORREF							m_crFocusBK;					//������ɫ
	COLORREF							m_crNoFocusTX;					//������ɫ
	COLORREF							m_crNoFocusBK;					//������ɫ
	COLORREF							m_crDisFocusTX;					//������ɫ
	COLORREF							m_crDisFocusBK;					//������ɫ

	//GDI ����
public:
	CBrush								m_brFocus;						//����ˢ
	CBrush								m_brNoFocus;					//����ˢ
	CBrush								m_brDisbale;					//����ˢ

	//��������
protected:
	//���캯��
	CSkinEditAttribute();
	//��������
	virtual ~CSkinEditAttribute();

	//�ӿں���
public:
	//��������
	bool UpdateSkinResource(ISkinResource * pISkinResource);
};

//////////////////////////////////////////////////////////////////////////

//�༭��
class SKIN_CONTROL_CLASS CSkinEdit : public CEdit
{
	//��������
protected:
	bool							m_bFocus;						//�����־

	//��̬����
public:
	static CSkinEditAttribute		m_SkinAttribute;				//��������

	//��������
public:
	//���캯��
	CSkinEdit();
	//��������
	virtual ~CSkinEdit();

	//��ѯ����
public:
	//��ȡ���Խӿ�
	static CSkinEditAttribute * GetSkinAttribute() { return &m_SkinAttribute; }
	//�ڲ�����
protected:
	//�滭�ؼ�
	VOID DrawControlView(CDC * pDC, COLORREF crColorBorad, COLORREF crColorBK);
	//��Ϣ���� 
protected:
	//�滭�ؼ�
	afx_msg HBRUSH CtlColor(CDC * pDC, UINT nCtlColor);
	//�õ�����
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	//ʧȥ����
	afx_msg void OnKillFocus(CWnd * pNewWnd);

	//��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinEdit)
};

//////////////////////////////////////////////////////////////////////////


//�༭��
class SKIN_CONTROL_CLASS CSkinEditEx : public CSkinEdit
{
	//��ˢ����
public:
	CBrush							m_brEnable;							//��ˢ��Դ
	CBrush							m_brDisable;						//��ˢ��Դ

	//������ɫ
public:
	COLORREF						m_crEnableBK;						//������ɫ
	COLORREF						m_crDisableBK;						//������ɫ

	//������ɫ
public:
	COLORREF						m_crEnableText;						//������ɫ
	COLORREF						m_crDisableText;					//������ɫ

	//�߿���ɫ
public:
	COLORREF						m_crEnableBorad;					//�߿���ɫ
	COLORREF						m_crDisableBorad;					//�߿���ɫ

	//��������
public:
	//���캯��
	CSkinEditEx();
	//��������
	virtual ~CSkinEditEx();

	//���ܺ���
public:
	//������ɫ
	VOID SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorad);
	//������ɫ
	VOID SetDisableColor(COLORREF crDisableText, COLORREF crDisableBK, COLORREF crDisableBorad);

	//��Ϣ���� 
protected:
	//�ػ���Ϣ
	VOID OnNcPaint();
	//�滭�ؼ�
	HBRUSH CtlColor(CDC * pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////////
#endif