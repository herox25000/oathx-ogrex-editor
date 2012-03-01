#pragma once

#include "ogre.h"
#include "EditorLogListener.h"


class CEditorView : public CView
{
protected:
	CEditorView();
	DECLARE_DYNCREATE(CEditorView)

protected:
	Ogre::Root*				m_pRoot;
	Ogre::RenderWindow*		m_pWindow;
	Ogre::SceneManager*		m_pSceneManager;
	Ogre::Camera*			m_pCamera;
	Ogre::Viewport*			m_pViewport;

	EditorLogListener*		m_pEditorLogListener;

	BOOL					m_bMouseDown;
	CPoint					m_cLastPt;
public:
	CEditorDoc*				GetDocument() const;

public:
	virtual void			OnDraw(CDC* pDC);
	virtual BOOL			PreCreateWindow(CREATESTRUCT& cs);

	virtual BOOL			Setup();
	virtual void			Update();

protected:
	virtual BOOL			OnPreparePrinting(CPrintInfo* pInfo);
	virtual void			OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void			OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	afx_msg void			OnFilePrintPreview();
	afx_msg void			OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void			OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void			OnTimer(UINT_PTR nIDEvent);
	afx_msg void			OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void			OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void			OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void			OnDestroy();
	afx_msg void			OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG
inline CEditorDoc* CEditorView::GetDocument() const
   { return reinterpret_cast<CEditorDoc*>(m_pDocument); }
#endif

