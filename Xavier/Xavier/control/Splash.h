#pragma once

#include <atlbase.h>
#include <afxpriv2.h>

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-03-08
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CPicture 
{
public:
   /**
    *
    * \return 
    */
   CPicture();

   /**
    *
    * \return 
    */
   ~CPicture();

   // Load from various resources
   /**
    *
    * \param nIDRes 
    * \return 
    */
   BOOL			Load(UINT nIDRes);

   /**
    *
    * \param pszPathName 
    * \return 
    */
   BOOL			Load(LPCTSTR pszPathName);

   /**
    *
    * \param file 
    * \return 
    */
   BOOL			Load(CFile& file);

   /**
    *
    * \param ar 
    * \return 
    */
   BOOL			Load(CArchive& ar);

   /**
    *
    * \param pstm 
    * \return 
    */
   BOOL			Load(IStream* pstm);

   // render to device context
   /**
    *
    * \param pDC 
    * \return 
    */
   CSize		GetImageSize(CDC* pDC=NULL) const;

   /**
    *
    * \return 
    */
   operator IPicture*() {
      return m_spIPicture;
   }

   /**
    *
    * \param cx 
    * \param cy 
    */
   void			GetHIMETRICSize(OLE_XSIZE_HIMETRIC& cx, OLE_YSIZE_HIMETRIC& cy) const 
   {
      cx = cy = 0;
      const_cast<CPicture*>(this)->m_hr = m_spIPicture->get_Width(&cx);
      ASSERT(SUCCEEDED(m_hr));
      const_cast<CPicture*>(this)->m_hr = m_spIPicture->get_Height(&cy);
      ASSERT(SUCCEEDED(m_hr));
   }

	/**
	 *
	 * \param pDC 
	 * \param rc 
	 * \param prcMFBounds 
	 * \return 
	 */
	BOOL		Render(CDC* pDC,CRect rc,LPCRECT prcMFBounds=NULL) const;

	/**
	 *
	 */
	void		Free() 
	{
      if (m_spIPicture) 
	  {
         m_spIPicture.Release();
      }
   }

protected:
   CComQIPtr<IPicture>m_spIPicture;     // ATL smart pointer to IPicture
   HRESULT m_hr;                        // last error code
};

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-03-08
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CSplashWnd : public CWnd
{
public:
	CSplashWnd(LPCTSTR lpszFileName);

public:
	/**
	 *
	 * \return 
	 */
	BOOL ShowSplash();

	/**
	 *
	 * \param pMsg 
	 * \return 
	 */
	BOOL PreTranslateAppMessage(MSG* pMsg);   

	/**
	 *
	 * \param lpStr 
	 */
	void ShowText(LPCTSTR lpStr);

	/**
	 *
	 */
	void CloseSplash();

public:
	/**
	 *
	 * \return 
	 */
	~CSplashWnd();

	/**
	 *
	 */
	virtual void PostNcDestroy();

private:
	/**
	 *
	 * \param pParentWnd 
	 * \return 
	 */
	BOOL				Create(CWnd* pParentWnd = NULL);

private:
	/**
	 *
	 * \param lpCreateStruct 
	 * \return 
	 */
	afx_msg int			OnCreate(LPCREATESTRUCT lpCreateStruct);

	/**
	 *
	 */
	afx_msg void		OnPaint();
	DECLARE_MESSAGE_MAP()
private:
	int					height;//the height of the displayed picture
	int					width;//the width of the displayed picture
	CPicture			pic;//used to operate the picture
	BOOL				fileIsValid;
};

