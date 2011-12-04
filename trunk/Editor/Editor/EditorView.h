#pragma once

#include "ogre.h"

class CEditorView : public CView
{
protected:
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

public:
	CEditorDoc*			GetDocument() const;

public:
	virtual void		OnDraw(CDC* pDC);
	virtual BOOL		PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL		InitOgreEngine();
	virtual void		Update();

protected:
	virtual BOOL		OnPreparePrinting(CPrintInfo* pInfo);
	virtual void		OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void		OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	Ogre::Root*			m_pRoot;
	Ogre::RenderWindow*	m_pWindow;
	Ogre::SceneManager*	m_pSceneManager;
	Ogre::Camera*		m_pCamera;
	BOOL				m_bFirst;

protected:
	afx_msg void		OnFilePrintPreview();
	afx_msg void		OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void		OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG
inline CEditorDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CEditorDoc*>(m_pDocument); }
#endif

