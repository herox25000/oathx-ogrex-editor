#ifndef SKIN_RICH_EDIT_HEAD_FILE
#define SKIN_RICH_EDIT_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "SkinControls.h"
#include "SkinAttribute.h"

//////////////////////////////////////////////////////////////////////////

//ͼ�� OLE ��
class CImageDataObject : IDataObject
{
	//��������
private:
	ULONG								m_ulRef;						//���ü���
	FORMATETC 							m_Format;						//�ṹ��Ϣ
	STGMEDIUM 							m_Stgmed;						//�ṹ��Ϣ

	//�������� 
public:
	//���캯��
	CImageDataObject();
	//��������
	~CImageDataObject();

	//���ܺ���
public:
	//����ͼƬ
	void SetBitmap(HBITMAP hBitmap);
	//��ȡ����
	IOleObject * GetOleObject(IOleClientSite * pOleClientSite, IStorage * pStorage);

	//�ӿں���
public:
	//��ѯ�ӿ�
	STDMETHOD(QueryInterface)(REFIID iid, void * * ppvObject)
	{
		if ((iid==IID_IUnknown)||(iid==IID_IDataObject))
		{
			*ppvObject=this;
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}
	//��������
	STDMETHOD_(ULONG, AddRef)(void)
	{
		m_ulRef++;
		return m_ulRef;
	}
	//�ͷŶ���
	STDMETHOD_(ULONG, Release)(void)
	{
		if (--m_ulRef==0) delete this;
		return m_ulRef;
	}
	//��������
	STDMETHOD(SetData)(FORMATETC * pformatetc, STGMEDIUM * pmedium, BOOL fRelease) 
	{
		m_Format=*pformatetc;
		m_Stgmed=*pmedium;
		return S_OK;
	}
	//��ȡ����
	STDMETHOD(GetData)(FORMATETC * pformatetcIn, STGMEDIUM * pmedium) 
	{
		HANDLE hDst =OleDuplicateData(m_Stgmed.hBitmap,CF_BITMAP,NULL);
		if (hDst==NULL) return E_HANDLE;
		pmedium->tymed=TYMED_GDI;
		pmedium->hBitmap=(HBITMAP)hDst;
		pmedium->pUnkForRelease=NULL;
		return S_OK;
	}
	STDMETHOD(EnumFormatEtc)(DWORD dwDirection, IEnumFORMATETC * *  ppenumFormatEtc ) {	return E_NOTIMPL; }
	STDMETHOD(DAdvise)(FORMATETC * pformatetc, DWORD advf, IAdviseSink * pAdvSink,DWORD * pdwConnection) { return E_NOTIMPL; }
	STDMETHOD(DUnadvise)(DWORD dwConnection) { return E_NOTIMPL; }
	STDMETHOD(EnumDAdvise)(IEnumSTATDATA * * ppenumAdvise) { return E_NOTIMPL; }
	STDMETHOD(GetDataHere)(FORMATETC * pformatetc, STGMEDIUM *  pmedium ) { return E_NOTIMPL;	}
	STDMETHOD(QueryGetData)(FORMATETC * pformatetc) { return E_NOTIMPL; }
	STDMETHOD(GetCanonicalFormatEtc)(FORMATETC * pformatectIn, FORMATETC * pformatetcOut) { return E_NOTIMPL; }
};

//////////////////////////////////////////////////////////////////////////

//��Ϣ����
class SKIN_CONTROL_CLASS CSkinRichEdit : public CRichEditCtrl
{
	//��������
protected:
	bool								m_bScroll;						//�Ƿ����
	CString								m_strFontName;					//��������
	IRichEditOle *						m_pIRichEditOle;				//OLE ָ��

	//��������
public:
	//���캯��
	CSkinRichEdit();
	//��������
	virtual ~CSkinRichEdit();

	//���غ���
protected:
	//�ؼ���
	virtual void PreSubclassWindow();

	//���ܺ��� 
public:
	//�����Ļ
	void CleanScreen();
	//�Ƿ����
	bool IsAutoScroll() { return m_bScroll; }
	//���ù���
	void SetAutoScroll(bool bScroll) { m_bScroll=bScroll; }
	//������Ϣ
	bool LoadMessage(LPCTSTR pszFileName);
	//������Ϣ
	bool SaveMessage(LPCTSTR pszFileName);

	//��Ϣ����
public:
	//����ͼƬ
	bool InsertImage(CBitmap * pBitmap);
	//�����ַ�
	bool InsertString(LPCTSTR pszString, COLORREF crColor, bool bLink=false, WORD wSize=0, LPCTSTR pszFont=NULL);

	//�ڲ�����
public:
	//���ػص�
	static DWORD CALLBACK LoadCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);
	//����ص�
	static DWORD CALLBACK SaveCallBack(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG * pcb);

	//��Ϣӳ��
public:
	//������Ϣ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//������Ϣ
	afx_msg void OnDestroy();
	//��������
	afx_msg void OnEnLink(NMHDR * pNMHDR, LRESULT * pResult);
	//���ù��
	afx_msg BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message);
	//�Ҽ���Ϣ
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//����
	afx_msg void OnCopy() { Copy(); }
	//ȫ��ѡ��
	afx_msg void OnSelectAll() { SetSel(0, -1); }
	//���
	afx_msg void OnClear() { ReplaceSel(TEXT("")); }
	//�����Ļ
	afx_msg void OnClearAll() { SetSel(0,GetWindowTextLength()); ReplaceSel(NULL); }
	//����
	afx_msg void OnSave();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif