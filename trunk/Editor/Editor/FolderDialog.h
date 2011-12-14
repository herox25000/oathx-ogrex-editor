#if !defined(AFX_MYFD_H__F9CB9441_F91B_11D1_8610_0040055C08D9__INCLUDED_)
#define AFX_MYFD_H__F9CB9441_F91B_11D1_8610_0040055C08D9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

/**
* \ingroup : Editor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2011-12-14
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CFolderDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CFolderDialog)

public:
	/**
	 *
	 * \param pPath 
	 * \return 
	 */
	CFolderDialog(CString* pPath);

public:
	static WNDPROC		m_wndProc;
	virtual void		OnInitDone( );
	CString*			m_pPath;

protected:
	DECLARE_MESSAGE_MAP()
};

#endif
