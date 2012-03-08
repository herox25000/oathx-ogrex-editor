/////////////////////////////////////////////////////////////////////////////
//Written by Liu Zhengxi
//May 5,2003
//Compiles with Visual C++ 6.0 for Windows 98 and probably Windows 2000 
// too.
/////////////////////////////////////////////////////////////////////////////
#ifndef _SPLASH
#define _SPLASH
#include <atlbase.h>
#include <afxpriv2.h>

// Splash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class
#pragma once

///////////////////////////////////////////////////////////////////////////
// Picture object-encapsulates IPicture
//Written by Paul DiLascia.
//used to display picture
//
// declare CPicture class
//
class CPicture {
public:
   CPicture();
   ~CPicture();

   // Load from various resources
   BOOL Load(UINT nIDRes);
   BOOL Load(LPCTSTR pszPathName);
   BOOL Load(CFile& file);
   BOOL Load(CArchive& ar);
   BOOL Load(IStream* pstm);

   // render to device context
   

   CSize GetImageSize(CDC* pDC=NULL) const;

   operator IPicture*() {
      return m_spIPicture;
   }

   void GetHIMETRICSize(OLE_XSIZE_HIMETRIC& cx, OLE_YSIZE_HIMETRIC& cy) 
      const {
      cx = cy = 0;
      const_cast<CPicture*>(this)->m_hr = m_spIPicture->get_Width(&cx);
      ASSERT(SUCCEEDED(m_hr));
      const_cast<CPicture*>(this)->m_hr = m_spIPicture->get_Height(&cy);
      ASSERT(SUCCEEDED(m_hr));
   }

	BOOL Render(CDC* pDC,CRect rc,LPCRECT prcMFBounds=NULL) const;
	void Free() {
      if (m_spIPicture) {
         m_spIPicture.Release();
      }
   }

protected:
   CComQIPtr<IPicture>m_spIPicture;     // ATL smart pointer to IPicture
   HRESULT m_hr;                        // last error code
};


///////////////////////////////////////////////////////////////////
//
//declare CSplashWnd
//
class CSplashWnd : public CWnd
{
// Construction
public:
	CSplashWnd(LPCTSTR lpszFileName);

// Operations
public:
	BOOL ShowSplash();
	BOOL PreTranslateAppMessage(MSG* pMsg);   
	void ShowText(LPCTSTR lpStr);
	void CloseSplash();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	~CSplashWnd();
	virtual void PostNcDestroy();

private:
	BOOL Create(CWnd* pParentWnd = NULL);

// Generated message map functions
private:
	//{{AFX_MSG(CSplashWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int height;//the height of the displayed picture
	int width;//the width of the displayed picture
	CPicture pic;//used to operate the picture
   BOOL fileIsValid;
};

#endif
